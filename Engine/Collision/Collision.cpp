#include "Collision.h"

#include <array>
#include <Math.h>

#include "..\GLib\_Console\ConsolePrint.h"
#include "..\Math\FloatOperations.h"
#include "..\GameObject\GameObject.h"
#include "..\Math\Matrix.h"
#include "..\Physics\PhysicsInfo.h"
#include "..\ProfileSystem\ProfileSystem.h"
#include "..\Math\Vector2.h"
#include "..\Math\Vector4.hpp"

namespace Engine
{
	namespace Collision
	{
		Collider::Collider(PhysicsInfo * i_pPhyInfo)
		{
			m_pPhyInfo = i_pPhyInfo;
			WeakPtr<GameObject> pGameObject(i_pPhyInfo->getGameObject());
			m_Translation = Engine::Math::Matrix::CreateTranslation(pGameObject.Acquire()->getPos());
			m_Rotation = Engine::Math::Matrix::CreateZRotation(pGameObject.Acquire()->getZRot());
			MtxLocalToWorld = m_Rotation * m_Translation;
			MtxWorldToLocal = MtxLocalToWorld.GetInverse();
		}

		Collider::~Collider()
		{
			m_pPhyInfo = nullptr;
			delete m_pPhyInfo;
		}

		CollisionPair * CollisionDetection(Collider * CollA, Collider * CollB, float dt)
		{
			PROFILE_UNSCOPED("Collision Detection non-SSE function");

			std::array<float, 4> tClose = { -1.f, -1.f, -1.f, -1.f };
			std::array<float, 4> tOpen = { 9999.f, 9999.f, 9999.f, 9999.f };

//Check A in B's Co-ordinate System
			//{
			for (unsigned int i = 0; i < 2; i++)
			{
				float DOpen = 0.f;
				float DClose = 0.f;

				Engine::Math::Matrix MtxAtoB = CollA->MtxLocalToWorld * CollB->MtxWorldToLocal;
				Engine::Math::Matrix MtxBtoA = MtxAtoB.GetInverse();//

				WeakPtr<GameObject> CollAGameObject(CollA->m_pPhyInfo->getGameObject());
				WeakPtr<GameObject> CollBGameObject(CollB->m_pPhyInfo->getGameObject());

				//Transform A's BB to B's Co-ordinate System
				Engine::Math::Vector4 ABBCenterInB = Engine::Math::Vector4(CollAGameObject.Acquire()->getBB().Center, 1.f) * MtxAtoB;
				Engine::Math::Vector4 AExtentsXInB = Engine::Math::Vector4(CollAGameObject.Acquire()->getBB().Extents.x, 0.f, 0.f, 0.f) * MtxAtoB;
				Engine::Math::Vector4 AExtentsYInB = Engine::Math::Vector4(0.f, CollAGameObject.Acquire()->getBB().Extents.y, 0.f, 0.f) * MtxAtoB;

				//Calculate A's Velocity in B's System
				Vector2 VelARelToB = CollAGameObject.Acquire()->getVelocity() - CollBGameObject.Acquire()->getVelocity();
				Engine::Math::Vector4 VelAInB = Engine::Math::Vector4(VelARelToB, 0.f) * CollB->MtxWorldToLocal;

				//Check along B's X axis
				//{
				//Calculate A's Projections onto B's Co-ordinate System Axes
				float AProjectionOntoB_X = float(fabs(AExtentsXInB.x()) + fabs(AExtentsYInB.x()));

				//B's extents in X considering A to be a point
				float BExtentsX = CollBGameObject.Acquire()->getBB().Extents.x + AProjectionOntoB_X;
				float BLeft = CollBGameObject.Acquire()->getBB().Center.x - BExtentsX;
				float BRight = CollBGameObject.Acquire()->getBB().Center.x + BExtentsX;

				//Edge Case 1 - Relative Velocity = 0
				if (AreAboutEqual(VelAInB.x(), 0.f))
				{
					if (ABBCenterInB.x() < BLeft || ABBCenterInB.x() > BRight)
					{
						return nullptr;
					}
				}
				else
				{
					//Distance to Open & Close
					DClose = BLeft - ABBCenterInB.x();
					DOpen = BRight - ABBCenterInB.x();

					//Calculate tOpen & tClose
					tClose[i * 2] = DClose / VelAInB.x();
					tOpen[i * 2] = DOpen / VelAInB.x();

					if (tOpen[i * 2] < tClose[i * 2])
					{
						float tTemp = tOpen[i * 2];
						tOpen[i * 2] = tClose[i * 2];
						tClose[i * 2] = tTemp;
					}

					//Edge Case 2 - Separation already in the past or Collision after frametime(in the future)
					if (tOpen[i * 2] < 0.f || tClose[i * 2] > dt)
					{
						return nullptr;
					}
				}
				//}	//End Check along B's X axis

				//Check along B's Y axis
				//{
				float AProjectionOntoB_Y = float(fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y()));

				//B's extents in Y considering A to be a point
				float BExtentsY = CollBGameObject.Acquire()->getBB().Extents.y + AProjectionOntoB_Y;
				float BBottom = CollBGameObject.Acquire()->getBB().Center.y - BExtentsY;
				float BTop = CollBGameObject.Acquire()->getBB().Center.y + BExtentsY;

				//Edge Case 1 - Relative Velocity = 0
				if (AreAboutEqual(VelAInB.y(), 0.f))
				{
					if (ABBCenterInB.y() < BBottom || ABBCenterInB.y() > BTop)
					{
						return nullptr;
					}
				}
				else
				{
					//Distance to Open & Close
					DClose = BBottom - ABBCenterInB.y();
					DOpen = BTop - ABBCenterInB.y();

					//Calculate tOpen & tClose
					tClose[(i * 2) + 1] = DClose / VelAInB.x();
					tOpen[(i * 2) + 1] = DOpen / VelAInB.x();

					if (tOpen[(i * 2) + 1] < tClose[(i * 2) + 1])
					{
						float tTemp = tOpen[(i * 2) + 1];
						tOpen[(i * 2) + 1] = tClose[(i * 2) + 1];
						tClose[(i * 2) + 1] = tTemp;
					}

					//Edge Case 2 - Separation already in the past or Collision after frametime(in the future)
					if (tOpen[(i * 2) + 1] < 0.f || tClose[(i * 2) + 1] > dt)
					{
						return nullptr;
					}
				}

				std::swap(CollA, CollB);
			}

			int LatestCollisionAxis = -1;
			float tOpenEarliest = 9999.f;
			float tCloseLatest = -1.f;

			for (unsigned int i = 0; i < 4; i++)
			{
				/*if (tClose[i] < 0 && tOpen[i] < 0)
				{
					tOpen[i] = 0;
				}*/
				if (tClose[i] > tCloseLatest)
				{
					tCloseLatest = tClose[i];
					LatestCollisionAxis = i;
				}
				if (tOpen[i] < tOpenEarliest && tOpen[i] >= 0)
				{
					tOpenEarliest = tOpen[i];
				}
			}

			if (tOpenEarliest < tCloseLatest)
			{
				//No Collision
				return nullptr;
			}
			else if (tCloseLatest <= tOpenEarliest && tCloseLatest <= dt)
			{
				//Collision happened during the frame
				DEBUG_PRINT("Collision happened\n");

				CollisionPair * CollPairToReturn (new CollisionPair());
				CollPairToReturn->m_CollisionTime = tCloseLatest;
				CollPairToReturn->m_CollisionNormal = (LatestCollisionAxis % 2 == 0) ? Vector2{ 1.f, 0.f } : Vector2{ 0.f, 1.f };
				//Collider pointers were swapped, so B becomes 1st object & A becomes 2nd
				//NO! They got swapped again (at the end) when the loop ran the second time after swapping them in the first run
				CollPairToReturn->m_CollisionObjects[0] = *CollA;
				CollPairToReturn->m_CollisionObjects[1] = *CollB;

				//delete CollPairToReturn;
				
				return CollPairToReturn;
				//return nullptr;
			}

			return nullptr;
		}	//end CollisionDetection()

		/*CollisionPair::CollisionPair() : m_CollisionTime(999999.f)
		{
		}

		CollisionPair::~CollisionPair()
		{
			//delete m_CollisionObjects;
		}*/


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//SSE Collision Detection

		ColliderSSE::ColliderSSE(PhysicsInfo * i_pPhyInfo)
		{
			m_pPhyInfo = i_pPhyInfo;
			WeakPtr<GameObject> pGameObject(i_pPhyInfo->getGameObject());
			m_Translation = Engine::Math::MatrixSSE::CreateTranslation(pGameObject.Acquire()->getPos());
			m_Rotation = Engine::Math::MatrixSSE::CreateZRotation(pGameObject.Acquire()->getZRot());
			MtxLocalToWorld = m_Rotation * m_Translation;
			MtxWorldToLocal = MtxLocalToWorld.GetInverse();
		}

		ColliderSSE::~ColliderSSE()
		{
			m_pPhyInfo = nullptr;
			delete m_pPhyInfo;
		}

		/*CollisionPairSSE::CollisionPairSSE() : m_CollisionTime(999999.f)
		{
		}

		CollisionPairSSE::~CollisionPairSSE()
		{
			//delete m_CollisionObjects;
		}*/

		/*CollisionPairSSE * CollisionDetectionSSE(ColliderSSE * CollA, ColliderSSE * CollB, float dt)
		{
			PROFILE_UNSCOPED("Collision Detection SSE function");

			std::array<float, 4> tClose = { 0.f, 0.f, 0.f, 0.f };
			std::array<float, 4> tOpen = { 9999.f, 9999.f, 9999.f, 9999.f };

			//Check A in B's Co-ordinate System
			//{
			for (unsigned int i = 0; i < 2; i++)
			{
				float DOpen = 0.f;
				float DClose = 0.f;

				Engine::Math::MatrixSSE MtxAtoB = CollA->MtxLocalToWorld * CollB->MtxWorldToLocal;
				Engine::Math::MatrixSSE MtxBtoA = MtxAtoB.GetInverse();//

				WeakPtr<GameObject> CollAGameObject(CollA->m_pPhyInfo->getGameObject());
				WeakPtr<GameObject> CollBGameObject(CollB->m_pPhyInfo->getGameObject());

				//Transform A's BB to B's Co-ordinate System
				Engine::Math::Vector4SSE ABBCenterInB = Engine::Math::Vector4SSE(CollAGameObject.Acquire()->getBB().Center, 1.f) * MtxAtoB;
				Engine::Math::Vector4SSE AExtentsXInB = Engine::Math::Vector4SSE(CollAGameObject.Acquire()->getBB().Extents.x, 0.f, 0.f, 0.f) * MtxAtoB;
				Engine::Math::Vector4SSE AExtentsYInB = Engine::Math::Vector4SSE(0.f, CollAGameObject.Acquire()->getBB().Extents.y, 0.f, 0.f) * MtxAtoB;

				//Calculate A's Velocity in B's System
				Vector2 VelARelToB = CollAGameObject.Acquire()->getVelocity() - CollBGameObject.Acquire()->getVelocity();
				Engine::Math::Vector4SSE VelAInB = Engine::Math::Vector4SSE(VelARelToB, 0.f) * CollB->MtxWorldToLocal;

				//Check along B's X axis
				//{
				//Calculate A's Projections onto B's Co-ordinate System Axes
				float AProjectionOntoB_X = float(fabs(AExtentsXInB.x()) + fabs(AExtentsYInB.x()));

				//B's extents in X considering A to be a point
				float BExtentsX = CollBGameObject.Acquire()->getBB().Extents.x + AProjectionOntoB_X;
				float BLeft = CollBGameObject.Acquire()->getBB().Center.x - BExtentsX;
				float BRight = CollBGameObject.Acquire()->getBB().Center.x + BExtentsX;

				//Edge Case 1 - Relative Velocity = 0
				if (AreAboutEqual(VelAInB.x(), 0.f))
				{
					if (ABBCenterInB.x() < BLeft || ABBCenterInB.x() > BRight)
					{
						return nullptr;
					}
				}
				else
				{
					//Distance to Open & Close
					DClose = BLeft - ABBCenterInB.x();
					DOpen = BRight - ABBCenterInB.x();

					//Calculate tOpen & tClose
					tClose[i * 2] = DClose / VelAInB.x();
					tOpen[i * 2] = DOpen / VelAInB.x();

					if (tOpen[i * 2] < tClose[i * 2])
					{
						float tTemp = tOpen[i * 2];
						tOpen[i * 2] = tClose[i * 2];
						tClose[i * 2] = tTemp;
					}

					//Edge Case 2 - Separation already in the past or Collision after frametime(in the future)
					if (tOpen[i * 2] < 0.f || tClose[i * 2] > dt)
					{
						return nullptr;
					}
				}
				//}	//End Check along B's X axis

				//Check along B's Y axis
				//{
				float AProjectionOntoB_Y = float(fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y()));

				//B's extents in Y considering A to be a point
				float BExtentsY = CollBGameObject.Acquire()->getBB().Extents.y + AProjectionOntoB_Y;
				float BBottom = CollBGameObject.Acquire()->getBB().Center.y - BExtentsY;
				float BTop = CollBGameObject.Acquire()->getBB().Center.y + BExtentsY;

				//Edge Case 1 - Relative Velocity = 0
				if (AreAboutEqual(VelAInB.y(), 0.f))
				{
					if (ABBCenterInB.y() < BBottom || ABBCenterInB.y() > BTop)
					{
						return nullptr;
					}
				}
				else
				{
					//Distance to Open & Close
					DClose = BBottom - ABBCenterInB.y();
					DOpen = BTop - ABBCenterInB.y();

					//Calculate tOpen & tClose
					tClose[(i * 2) + 1] = DClose / VelAInB.x();
					tOpen[(i * 2) + 1] = DOpen / VelAInB.x();

					if (tOpen[(i * 2) + 1] < tClose[(i * 2) + 1])
					{
						float tTemp = tOpen[(i * 2) + 1];
						tOpen[(i * 2) + 1] = tClose[(i * 2) + 1];
						tClose[(i * 2) + 1] = tTemp;
					}

					//Edge Case 2 - Separation already in the past or Collision after frametime(in the future)
					if (tOpen[(i * 2) + 1] < 0.f || tClose[(i * 2) + 1] > dt)
					{
						return nullptr;
					}
				}

				std::swap(CollA, CollB);
			}

			int LatestCollisionAxis = -1;
			float tOpenEarliest = 9999.f;
			float tCloseLatest = -1.f;

			for (unsigned int i = 0; i < 4; i++)
			{
				if (tClose[i] < 0 && tOpen[i] < 0)
				{
					tOpen[i] = 0;
				}
				if (tClose[i] >= tCloseLatest)
				{
					tCloseLatest = tClose[i];
					LatestCollisionAxis = i;
				}
				if (tOpen[i] < tOpenEarliest && tOpen[i] >= 0)
				{
					tOpenEarliest = tOpen[i];
				}
			}

			if (tOpenEarliest < tCloseLatest)
			{
				//No Collision
				return nullptr;
			}
			else if (tCloseLatest >= 0 && tCloseLatest <= tOpenEarliest && tCloseLatest <= dt)
			{
				//Collision happened during the frame
				DEBUG_PRINT("Collision happened\n");

				CollisionPairSSE * CollPairToReturn(new CollisionPairSSE());
				CollPairToReturn->m_CollisionTime = tCloseLatest;
				CollPairToReturn->m_CollisionNormal = (LatestCollisionAxis % 2 == 0) ? Vector2{ 1.f, 0.f } : Vector2{ 0.f, 1.f };
				//Collider pointers were swapped, so B becomes 1st object & A becomes 2nd
				//NO! They got swapped again (at the end) when the loop ran the second time after swapping them in the first run
				CollPairToReturn->m_CollisionObjects[0] = *CollA;
				CollPairToReturn->m_CollisionObjects[1] = *CollB;

				//delete CollPairToReturn;

				return CollPairToReturn;
				//return nullptr;
			}

			return nullptr;
		}	//end CollisionDetectionSSE()
		*/
}	//namespace Collision
}	//namespace Engine
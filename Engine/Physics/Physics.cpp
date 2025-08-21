#include "Physics.h"

#include <algorithm>
#include <assert.h>

//#include "..\Collision\Collision.h"
#include "..\Math\FloatOperations.h"
#include "..\GameObject\GameObject.h"
#include "..\Math\Vector2.h"

namespace Engine
{
	namespace Physics
	{
		std::vector<PhysicsInfo *> * PhysicsObjects = nullptr;
		std::vector<Engine::Collision::Collider *> * StationaryColliders = nullptr;
		PhysicsInfo * g_PongBallPhysics = nullptr;

		std::vector<PhysicsInfo *> & GetPhysicsObjects()
		{
			if (PhysicsObjects == nullptr)
			{
				PhysicsObjects = new std::vector<PhysicsInfo *>();
			}
			return *PhysicsObjects;
		}

		std::vector<Engine::Collision::Collider *> & GetStationaryColliders()
		{
			if (StationaryColliders == nullptr)
			{
				StationaryColliders = new std::vector<Engine::Collision::Collider *>();
			}
			return *StationaryColliders;
		}

		void SetPongBallPhysics(PhysicsInfo * i_BallPhysics)
		{
			assert(i_BallPhysics);
			g_PongBallPhysics = i_BallPhysics;
		}
		PhysicsInfo & GetPongBallPhysics()
		{
			assert(g_PongBallPhysics);
			return *g_PongBallPhysics;
		}

		MultiCastDelegate<WeakPtr<GameObject>> * BallDeathReceivers = nullptr;
		MultiCastDelegate<WeakPtr<GameObject>> & GetBallDeathReceivers()
		{
			assert(BallDeathReceivers != nullptr);
			return *BallDeathReceivers;
		}

		MultiCastDelegate<Vector2> * BallReboundReceivers = nullptr;
		MultiCastDelegate<Vector2> & GetBallReboundReceivers()
		{
			assert(BallReboundReceivers != nullptr);
			return *BallReboundReceivers;
		}

		
		bool StartUp()
		{
			if (PhysicsObjects == nullptr)
			{
				PhysicsObjects = new std::vector<PhysicsInfo *>();
			}
			if (StationaryColliders == nullptr)
			{
				StationaryColliders = new std::vector<Engine::Collision::Collider *>();
			}
			if (BallDeathReceivers == nullptr)
			{
				BallDeathReceivers = new MultiCastDelegate<WeakPtr<GameObject>>();
			}
			if (BallReboundReceivers == nullptr)
			{
				BallReboundReceivers = new MultiCastDelegate<Vector2>();
			}
			return true;
		}

		bool ShutDown()
		{
			g_PongBallPhysics = nullptr;
			delete BallReboundReceivers;
			delete BallDeathReceivers;

			for (auto StatCollider : GetStationaryColliders())
			{
				delete StatCollider;
			}
			GetStationaryColliders().clear();
			delete StationaryColliders;

			for (auto PhyObj : GetPhysicsObjects())
			{
				delete PhyObj;
			}
			GetPhysicsObjects().clear();
			delete PhysicsObjects;

			return true;
		}


		void ResolveCollision(Engine::Collision::CollisionPair & CollPair)
		{
			PhysicsInfo * PhyObjBall = CollPair.m_CollisionObjects[0].m_pPhyInfo;
			PhysicsInfo * PhyObj2 = CollPair.m_CollisionObjects[1].m_pPhyInfo;

			assert(PhyObjBall->getGameObject() == GetPongBallPhysics().getGameObject());

			Vector2 v1 = PhyObjBall->getVelocity();
			Vector2 Pos1 = PhyObjBall->getGameObject().Acquire()->getPos();
			if (PhyObj2->getCollisionKilling())
			{
				PhyObjBall->getGameObject().Acquire()->setPos(Vector2{ 0.f, 0.f });
				//GetPongBallPhysics().getGameObject().Acquire()->setPos(Vector2{ 0.f, 0.f });
				RemoveForces(PhyObjBall->getGameObject());

				GetBallDeathReceivers().ExecuteOnBound(PhyObj2->getGameObject());
			}
			else
			{
				//Ball Rebounds
				if (!AreAboutEqual(CollPair.m_CollisionNormal.x, 0.f))	//Collision along x-axis
				{
					GetPongBallPhysics().setVelocity(Vector2{ -v1.x, v1.y });
					//GetPongBallPhysics().setVelocity(v1 - (CollPair.m_CollisionNormal * 2 * (dot(v1, CollPair.m_CollisionNormal))));
				}
				if (!AreAboutEqual(CollPair.m_CollisionNormal.y, 0.f))	//Collision along y-axis
				{
					GetPongBallPhysics().setVelocity(Vector2{ v1.x, -v1.y });
					//GetPongBallPhysics().setVelocity(v1 - (CollPair.m_CollisionNormal * 2 * (dot(v1, CollPair.m_CollisionNormal))));
				}

				GetBallReboundReceivers().ExecuteOnBound(CollPair.m_CollisionNormal);
			}
			/*if (v1.x > 0)
			{
				PhyObj1->getGameObject().Acquire()->setPos(Pos1 - Vector2{ 0.1f, 0.f });
			}
			else if (v1.x < 0)
			{
				PhyObj1->getGameObject().Acquire()->setPos(Pos1 + Vector2{ 0.1f, 0.f });
			}
			if (v1.y > 0)
			{
				PhyObj1->getGameObject().Acquire()->setPos(Pos1 - Vector2{ 0.0f, 0.1f });
			}
			else if (v1.y < 0)
			{
				PhyObj1->getGameObject().Acquire()->setPos(Pos1 + Vector2{ 0.f, 0.1f });
			}
			PhyObj1->setVelocity(Vector2{ -(v1.x), -(v1.y) });*/

			//For Collideable 2
			/*Vector2 v2 = PhyObj2->getVelocity();
			Vector2 Pos2 = PhyObj2->getGameObject().Acquire()->getPos();
			if (v2.x > 0)
			{
				PhyObj2->getGameObject().Acquire()->setPos(Pos2 - Vector2{ 0.1f, 0.f });
			}
			else if(v2.x < 0)
			{
				PhyObj2->getGameObject().Acquire()->setPos(Pos2 + Vector2{ 0.1f, 0.f });
			}
			if (v2.y > 0)
			{
				PhyObj2->getGameObject().Acquire()->setPos(Pos2 - Vector2{ 0.0f, 0.1f });
			}
			else if(v2.y < 0)
			{
				PhyObj2->getGameObject().Acquire()->setPos(Pos2 + Vector2{ 0.f, 0.1f });
			}
			PhyObj2->setVelocity(Vector2{ -(v2.x), -(v2.y) });*/
		}


		void Update(float dt)
		{
			std::vector<PhysicsInfo *> PhyObjsReference = GetPhysicsObjects();
			//Engine::Collision::CollisionPair * CollisionDuringFrame = new Engine::Collision::CollisionPair;
			Engine::Collision::CollisionPair CollisionDuringFrame;
			bool bCollision = false;

			for (auto PhysicsObj : PhyObjsReference)
			{
				if (PhysicsObj->getGameObject().Acquire()->getMovable())
				{
					PhysicsObj->AttemptUpdateObject(dt);
				}
			}

			//Check for collision among all Physics Objects and get earliest one
			bCollision = CollisionRun(CollisionDuringFrame, dt);

			//If collision found during frame, update all objects to that point in time
			if (bCollision)
			{
				for (auto PhysicsObj : PhyObjsReference)
				{
					if (PhysicsObj->getGameObject().Acquire()->getMovable())
					{
						PhysicsObj->UpdateObject(CollisionDuringFrame.m_CollisionTime);
					}
				}

				//Resolve velocities for collision
				ResolveCollision(CollisionDuringFrame);

				dt -= CollisionDuringFrame.m_CollisionTime;

				for (auto PhysicsObj : PhyObjsReference)
				{
					if (PhysicsObj->getGameObject().Acquire()->getMovable())
					{
						PhysicsObj->UpdateObject(dt);
						PhysicsObj->ResetDrivingForces();
					}
				}
			}
			else
			{
				//No collision during this run
				for (auto PhysicsObj : PhyObjsReference)
				{
					if (PhysicsObj->getGameObject().Acquire()->getMovable())
					{
						PhysicsObj->FinalizeUpdate();
						PhysicsObj->ResetDrivingForces();
					}
				}

				//dt = 0;
			}

			/*while (dt > 0)
			{
				//Calculate projected position
				for (auto PhysicsObj : PhyObjsReference)
				{
					PhysicsObj->AttemptUpdateObject(dt);
				}

				//Check for collision among all Physics Objects and get earliest one
				bCollision = CollisionRun(CollisionDuringFrame, dt);

				//If collision found during frame, update all objects to that point in time
				if (bCollision)
				{
					for (auto PhysicsObj : PhyObjsReference)
					{
						PhysicsObj->UpdateObject(CollisionDuringFrame.m_CollisionTime);
					}
					//Resolve velocities for collision
					//CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->setPos(Vector2{ -180.f, -100.f });
					//CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->UpdateDrivingForces(Vector2{ -1.1f, 0.f });
					Vector2 v1 = CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getVelocity();
					if (v1.x > 0)
					{
						CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->setPos(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->getPos() - Vector2{ 0.01f, 0.f });
					}
					else
					{
						CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->setPos(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->getPos() + Vector2{ 0.01f, 0.f });
					}
					if (v1.y > 0)
					{
						CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->setPos(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->getPos() - Vector2{ 0.0f, 0.01f });
					}
					else
					{
						CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->setPos(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->getPos() - Vector2{ 0.f, 0.01f });
					}
					//CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->setPos(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getGameObject().Acquire()->getPos() - Vector2{0.001f, 0.001f});
					CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->setVelocity(Vector2{-(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getVelocity().x), -(CollisionDuringFrame.m_CollisionObjects[0].m_pPhyInfo->getVelocity().y) });
					//CollisionDuringFrame.m_CollisionObjects[1].m_pPhyInfo->getGameObject().Acquire()->setPos(Vector2{ 180.f, 50.f });
					//CollisionDuringFrame.m_CollisionObjects[1].m_pPhyInfo->UpdateDrivingForces(Vector2{ 0.f, 1.1f });
					//CollisionDuringFrame.m_CollisionObjects[1].m_pPhyInfo->setVelocity(Vector2{ 0.001f, -0.0f });
					//Reduce delta time by time of collision
					dt = dt - CollisionDuringFrame.m_CollisionTime;
				}
				else
				{
					//No collision during this run
					for (auto PhysicsObj : PhyObjsReference)
					{
						PhysicsObj->FinalizeUpdate();
						PhysicsObj->ResetDrivingForces();
					}

					dt = 0;
				}
			}*/

			/*for (auto PhysicsObj : PhyObjsReference)
			{
				PhysicsObj->UpdateObject(dt);
				PhysicsObj->ResetDrivingForces();
			}

			Engine::Collision::CollisionPair * oldCollPair = new Engine::Collision::CollisionPair;
			CollisionRun(*oldCollPair, dt);
			delete oldCollPair;*/

			/*Engine::Collision::CollisionPairSSE * oldCollPairSSE = new Engine::Collision::CollisionPairSSE;
			CollisionRunSSE(*oldCollPairSSE, dt);
			delete oldCollPairSSE;*/
		}

		bool CollisionRun(Engine::Collision::CollisionPair & o_CollPair, float dt)
		{
			//Engine::Collision::CollisionPair * CollPairToReturn(new Engine::Collision::CollisionPair());
			o_CollPair.m_CollisionTime = dt;
			bool bCollisionInFrame = false;

			std::vector<PhysicsInfo *> PhyObjRefList = GetPhysicsObjects();
			if (PhyObjRefList.size() > 1)
			{
				Engine::Collision::Collider * PongBallCollider = nullptr;
				std::vector<Engine::Collision::Collider *> ColliderList;

				for (auto PhyObj : PhyObjRefList)
				{
					if (PhyObj->getGameObject() == GetPongBallPhysics().getGameObject())
					{
						PongBallCollider = new Engine::Collision::Collider(PhyObj);
					}
					else if(PhyObj->getGameObject().Acquire()->getMovable())
					{
						ColliderList.push_back(new Engine::Collision::Collider(PhyObj));
					}
				}

				std::vector<Engine::Collision::Collider *> StatColliderReference = GetStationaryColliders();
				Engine::Collision::CollisionPair * CollPairCurrent = nullptr;

				//Check collision of Ball with Stationary/Non-Movable objects
				for (auto CollIt = StatColliderReference.begin(); CollIt != StatColliderReference.end(); CollIt++)
				{
					CollPairCurrent = Engine::Collision::CollisionDetection(PongBallCollider, *CollIt, dt);

					if (CollPairCurrent != nullptr && CollPairCurrent->m_CollisionTime < o_CollPair.m_CollisionTime)
					{
						o_CollPair = *CollPairCurrent;
						o_CollPair.m_CollisionTime = CollPairCurrent->m_CollisionTime;
						o_CollPair.m_CollisionNormal = CollPairCurrent->m_CollisionNormal;
						o_CollPair.m_CollisionObjects[0] = CollPairCurrent->m_CollisionObjects[0];
						o_CollPair.m_CollisionObjects[1] = CollPairCurrent->m_CollisionObjects[1];


						bCollisionInFrame = true;

					}

					if (CollPairCurrent)
					{
						delete CollPairCurrent;
					}
				}	//end Non-Movables collision check loop

				//Check collision of Ball with Movable objects
				for (auto CollIt = ColliderList.begin(); CollIt != ColliderList.end(); CollIt++)
				{
					CollPairCurrent = Engine::Collision::CollisionDetection(PongBallCollider, *CollIt, dt);

					if (CollPairCurrent != nullptr && CollPairCurrent->m_CollisionTime < o_CollPair.m_CollisionTime)
					{
						o_CollPair = *CollPairCurrent;
						o_CollPair.m_CollisionTime = CollPairCurrent->m_CollisionTime;
						o_CollPair.m_CollisionNormal = CollPairCurrent->m_CollisionNormal;
						o_CollPair.m_CollisionObjects[0] = CollPairCurrent->m_CollisionObjects[0];
						o_CollPair.m_CollisionObjects[1] = CollPairCurrent->m_CollisionObjects[1];


						bCollisionInFrame = true;

					}

					if (CollPairCurrent)
					{
						delete CollPairCurrent;
					}
				}	//end Movables collision check loop

				//CollPairCurrent = nullptr;
				//delete CollPairCurrent;
				for (auto CollObj : ColliderList)
				{
					delete CollObj;
				}

				ColliderList.clear();
				delete PongBallCollider;
			}	//end if

			return bCollisionInFrame;
		}	//end CollisionRun()



		/*void CollisionRunSSE(Engine::Collision::CollisionPairSSE & o_CollPair, float dt)
		{
			//Engine::Collision::CollisionPair * CollPairToReturn(new Engine::Collision::CollisionPair());
			//CollPairToReturn->m_CollisionTime = 999999.f;
			std::vector<PhysicsInfo *> PhyObjRefList = GetPhysicsObjects();
			if (PhyObjRefList.size() > 1)
			{
				std::vector<Engine::Collision::ColliderSSE *> ColliderList;
				for (auto PhyObj : PhyObjRefList)
				{
					ColliderList.push_back(new Engine::Collision::ColliderSSE(PhyObj));
				}

				Engine::Collision::CollisionPairSSE * CollPairCurrent = nullptr;
				for (auto CollIt = ColliderList.begin(); CollIt != ColliderList.end() - 1; CollIt++)
				{
					for (auto CollJt = CollIt + 1; CollJt != ColliderList.end(); CollJt++)
					{
						CollPairCurrent = Engine::Collision::CollisionDetectionSSE(*CollIt, *CollJt, dt);
						if (CollPairCurrent != nullptr && CollPairCurrent->m_CollisionTime < o_CollPair.m_CollisionTime)
						{
							//CollPairCurrent->m_CollisionObjects[0]->m_pPhyInfo->getGameObject().Acquire()->setPos(Vector2{ -180.f, -100.f });
							CollPairCurrent->m_CollisionObjects[0]->m_pPhyInfo->UpdateDrivingForces(Vector2{ -0.1f, 0.f });
							//CollPairCurrent->m_CollisionObjects[1]->m_pPhyInfo->getGameObject().Acquire()->setPos(Vector2{ 180.f, 50.f });
							CollPairCurrent->m_CollisionObjects[1]->m_pPhyInfo->UpdateDrivingForces(Vector2{ 0.f, 0.1f });
							o_CollPair = *CollPairCurrent;
						}
					}
				}	//end collision check loop

					//CollPairCurrent = nullptr;
				delete CollPairCurrent;
				for (auto CollObj : ColliderList)
				{
					delete CollObj;
				}

				ColliderList.clear();
			}	//end if

				/*if (CollPairToReturn->m_CollisionTime == 999999.f)
				{
				delete CollPairToReturn;
				return nullptr;
				}
				else
				{
				return CollPairToReturn;
				delete CollPairToReturn;
				}*/
		//}	//end CollisionRun()



		bool AddPhysicsObject(PhysicsInfo * i_PhysicsObject)
		{
			GetPhysicsObjects().push_back(i_PhysicsObject);

			if (i_PhysicsObject->getGameObject().Acquire()->getMovable() == false)
			{
				AddStationaryCollider(i_PhysicsObject);
			}

			return true;
		}

		void RemovePhysicsObject(WeakPtr<GameObject> i_WeakObject)
		{
			//GetPhysicsObjects().erase(std::remove_if(GetPhysicsObjects().begin(), GetPhysicsObjects().end(), [i_WeakObject](PhysicsInfo * i_Entry) {return i_Entry->getGameObject() == i_WeakObject;}),
			//	GetPhysicsObjects().end());

			std::vector<PhysicsInfo *> PhyObjsReference = GetPhysicsObjects();
			std::vector<PhysicsInfo *>::iterator IterBegin = PhyObjsReference.begin();
			std::vector<PhysicsInfo *>::iterator IterEnd = PhyObjsReference.end();
			std::vector<PhysicsInfo *>::iterator PhyIter = std::find_if(IterBegin, IterEnd, [i_WeakObject](PhysicsInfo * i_Entry) {return i_Entry->getGameObject() == i_WeakObject;});

			if (PhyIter != IterEnd)
			{
				if ((*PhyIter)->getGameObject().Acquire()->getMovable() == false)
				{
					RemoveStationaryCollider(i_WeakObject);
				}
				*PhyIter = PhyObjsReference.back();
				delete *PhyIter;
				PhyObjsReference.pop_back();
			}
		}


		void AddStationaryCollider(PhysicsInfo * i_PhysicsObject)
		{
			GetStationaryColliders().push_back(new Engine::Collision::Collider(i_PhysicsObject));
		}

		void RemoveStationaryCollider(WeakPtr<GameObject> i_WeakObject)
		{
			std::vector<Engine::Collision::Collider *> StatCollReference = GetStationaryColliders();
			std::vector<Engine::Collision::Collider *>::iterator IterBegin = StatCollReference.begin();
			std::vector<Engine::Collision::Collider *>::iterator IterEnd = StatCollReference.end();
			std::vector<Engine::Collision::Collider *>::iterator StatCollIter = std::find_if(IterBegin, IterEnd, [i_WeakObject](Engine::Collision::Collider * i_Entry) {return i_Entry->m_pPhyInfo->getGameObject() == i_WeakObject;});

			if (StatCollIter != IterEnd)
			{
				*StatCollIter = StatCollReference.back();
				delete *StatCollIter;
				StatCollReference.pop_back();
			}
		}


		void ApplyForce(WeakPtr<GameObject> i_WeakObject, Vector2 i_Force)
		{
			std::vector<PhysicsInfo *> PhyObjsReference = GetPhysicsObjects();
			std::vector<PhysicsInfo *>::iterator IterBegin = PhyObjsReference.begin();
			std::vector<PhysicsInfo *>::iterator IterEnd = PhyObjsReference.end();
			std::vector<PhysicsInfo *>::iterator PhyIter = std::find_if(IterBegin, IterEnd, [i_WeakObject](PhysicsInfo * i_Entry) {return i_Entry->getGameObject() == i_WeakObject;});
			
			if(PhyIter != IterEnd)
			{
				(*PhyIter)->setDrivingForceStopped(false);
				(*PhyIter)->UpdateDrivingForces(i_Force);
			}
		}

		void RemoveForces(WeakPtr<GameObject> i_WeakObject)
		{
			std::vector<PhysicsInfo *> PhyObjsReference = GetPhysicsObjects();
			std::vector<PhysicsInfo *>::iterator IterBegin = PhyObjsReference.begin();
			std::vector<PhysicsInfo *>::iterator IterEnd = PhyObjsReference.end();
			std::vector<PhysicsInfo *>::iterator PhyIter = std::find_if(IterBegin, IterEnd, [i_WeakObject](PhysicsInfo * i_Entry) {return i_Entry->getGameObject() == i_WeakObject;});
			
			if (PhyIter != IterEnd)
			{
				(*PhyIter)->setDrivingForceStopped(true);
			}
		}		

	}	//namespace Physics
}	//namespace Engine
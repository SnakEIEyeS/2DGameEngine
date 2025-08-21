#pragma once


#include "..\Math\Matrix.h"
#include "..\Math\MatrixSSE.h"
#include "..\Pointers\SmartPointer.h"
#include "..\Pointers\WeakPointer.h"
//class GameObject;
class PhysicsInfo;
struct Vector2;

namespace Engine
{
	namespace Collision
	{
		struct Collider
		{
			PhysicsInfo * m_pPhyInfo;
			Engine::Math::Matrix m_Translation;
			Engine::Math::Matrix m_Rotation;
			Engine::Math::Matrix MtxLocalToWorld;
			Engine::Math::Matrix MtxWorldToLocal;

			Collider(PhysicsInfo * i_pPhyInfo);
			Collider() {}
			~Collider();
		};

		struct CollisionPair
		{
			float m_CollisionTime;
			Vector2 m_CollisionNormal;
			//std::array<Collider *, 2> m_CollisionObjects;
			Collider m_CollisionObjects[2];

			//CollisionPair();
			//~CollisionPair();
		};
		
		CollisionPair * CollisionDetection(Collider * CollA, Collider * CollB, float dt);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//SSE Collision Detection

		struct ColliderSSE
		{
			PhysicsInfo * m_pPhyInfo;
			Engine::Math::MatrixSSE m_Translation;
			Engine::Math::MatrixSSE m_Rotation;
			Engine::Math::MatrixSSE MtxLocalToWorld;
			Engine::Math::MatrixSSE MtxWorldToLocal;

			ColliderSSE(PhysicsInfo * i_pPhyInfo);
			ColliderSSE() {}
			~ColliderSSE();
		};

		struct CollisionPairSSE
		{
			float m_CollisionTime;
			Vector2 m_CollisionNormal;
			//std::array<Collider *, 2> m_CollisionObjects;
			ColliderSSE m_CollisionObjects[2];

			//CollisionPairSSE();
			//~CollisionPairSSE();
		};

		//CollisionPairSSE * CollisionDetectionSSE(ColliderSSE * CollA, ColliderSSE * CollB, float dt);

	}
}

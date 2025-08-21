#pragma once

#include <vector>

#include "..\Collision\Collision.h"
#include "..\Messaging\Delegates.h"
#include "PhysicsInfo.h"
#include "..\Pointers\WeakPointer.h"

class GameObject;
//struct CollisionPair;
struct Vector2;

namespace Engine
{
	namespace Physics
	{
		extern std::vector<PhysicsInfo *> * PhysicsObjects;
		extern std::vector<Engine::Collision::Collider *> * StationaryColliders;
		extern PhysicsInfo * g_PongBallPhysics;

		std::vector<PhysicsInfo *> & GetPhysicsObjects();
		std::vector<Engine::Collision::Collider *> & GetStationaryColliders();
		
		void SetPongBallPhysics(PhysicsInfo * i_BallPhysics);
		PhysicsInfo & GetPongBallPhysics();
		
		typedef Delegate<WeakPtr<GameObject>> BallDeathReceiver_t;
		extern MultiCastDelegate<WeakPtr<GameObject>> * BallDeathReceivers;
		MultiCastDelegate<WeakPtr<GameObject>> & GetBallDeathReceivers();

		typedef Delegate<Vector2> BallReboundReceiver_t;
		extern MultiCastDelegate<Vector2> * BallReboundReceivers;
		MultiCastDelegate<Vector2> & GetBallReboundReceivers();

		
		bool StartUp();
		bool ShutDown();

		void ResolveCollision(Engine::Collision::CollisionPair & CollPair);
		
		void Update(float dt);
		
		//Engine::Collision::CollisionPair * CollisionRun(float dt);
		bool CollisionRun(Engine::Collision::CollisionPair &, float dt);
		//void CollisionRunSSE(Engine::Collision::CollisionPairSSE & o_CollPair, float dt);

		
		bool AddPhysicsObject(PhysicsInfo * i_PhysicsObject);
		void RemovePhysicsObject(WeakPtr<GameObject> i_WeakObject);

		void AddStationaryCollider(PhysicsInfo * i_PhysicsObject);
		void RemoveStationaryCollider(WeakPtr<GameObject> i_WeakObject);

		void ApplyForce(WeakPtr<GameObject> i_WeakObject, Vector2 i_Force);
		void RemoveForces(WeakPtr<GameObject> i_WeakObject);

	}
}

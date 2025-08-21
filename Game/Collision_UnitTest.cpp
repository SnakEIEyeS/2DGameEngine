#include <assert.h>

#include "Collision\Collision.h"
#include "_Console\ConsolePrint.h"
#include "GameObject\GameObject.h"
#include "Physics\PhysicsInfo.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"

bool Collision_UnitTest()
{
	Engine::Collision::CollisionPair * Collided = nullptr;

	//Collideable Object 1
	SmartPtr<GameObject> PrimeGO(new GameObject(Vector2{ 0.f, 0.f }));
	PrimeGO->setBB(AABB{ Vector2{0.f, 1.f}, Vector2{1.f, 1.f} });
	PrimeGO->setVelocity(Vector2{ 0.f, 0.f });
	PhysicsInfo * PhysicsPrime = new PhysicsInfo(PrimeGO, 1.f, 0.0001f);
	Engine::Collision::Collider * ColliderPrime(new Engine::Collision::Collider(PhysicsPrime));

	//Collideable Object 2
	SmartPtr<GameObject> SecGO(new GameObject(Vector2{ 10.f, 0.f }));
	SecGO->setBB(AABB{ Vector2{ 0.f, 1.f }, Vector2{ 1.f, 1.f } });
	SecGO->setVelocity(Vector2{ 0.f, 0.f });
	PhysicsInfo * PhysicsSec = new PhysicsInfo(SecGO, 1.f, 0.0001f);
	Engine::Collision::Collider * ColliderSec(new Engine::Collision::Collider(PhysicsSec));

	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderSec, (float)16.6);
	assert(Collided == nullptr);

	SecGO->setPos(Vector2{ 0.5f, 0.f });
	Engine::Collision::Collider * ColliderRightTrue(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderRightTrue, (float)16.6);
	assert(Collided != nullptr);
	delete Collided;

	SecGO->setPos(Vector2{ -0.5f, 0.f });
	Engine::Collision::Collider * ColliderLeftTrue(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderLeftTrue, (float)16.6);
	assert(Collided != nullptr);
	delete Collided;

	SecGO->setPos(Vector2{ 0.f, 0.f });
	Engine::Collision::Collider * ColliderCenterTrue(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderCenterTrue, (float)16.6);
	assert(Collided != nullptr);
	delete Collided;

	SecGO->setPos(Vector2{ -10.f, 0.f });
	Engine::Collision::Collider * ColliderLeftFalse(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderLeftFalse, (float)16.6);
	assert(Collided == nullptr);

	SecGO->setPos(Vector2{ 0.f, 10.f });
	Engine::Collision::Collider * ColliderTopFalse(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderTopFalse, (float)16.6);
	assert(Collided == nullptr);

	SecGO->setPos(Vector2{ 0.f, 0.5f });
	Engine::Collision::Collider * ColliderTopTrue(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderTopTrue, (float)16.6);
	assert(Collided != nullptr);
	delete Collided;

	SecGO->setPos(Vector2{ 0.f, -0.5f });
	Engine::Collision::Collider * ColliderBotTrue(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderBotTrue, (float)16.6);
	assert(Collided != nullptr);
	delete Collided;

	SecGO->setPos(Vector2{ 0.f, -10.f });
	Engine::Collision::Collider * ColliderBotFalse(new Engine::Collision::Collider(PhysicsSec));
	Collided = Engine::Collision::CollisionDetection(ColliderPrime, ColliderBotFalse, (float)16.6);
	assert(Collided == nullptr);

	delete ColliderBotFalse;
	delete ColliderBotTrue;
	delete ColliderTopTrue;
	delete ColliderTopFalse;
	delete ColliderLeftFalse;
	delete ColliderCenterTrue;
	delete ColliderLeftTrue;
	delete ColliderRightTrue;
	delete ColliderSec;
	delete PhysicsSec;
	delete ColliderPrime;
	delete PhysicsPrime;
	delete Collided;

	DEBUG_PRINT("Collision Detection Unit Test passed!\n\n");
	return true;
}
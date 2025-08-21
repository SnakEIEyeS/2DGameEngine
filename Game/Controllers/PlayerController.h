#pragma once

#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "GLib.h"
#include "Pointers\SmartPointer.h"
#include "Pointers\WeakPointer.h"
#include "Physics\PhysicsInfo.h"

//class GameObject;
struct Vector2;

class PlayerController : public GameObjectController
{
public:
	PlayerController(SmartPtr<GameObject> i_pGameObject);
	~PlayerController();

	WeakPtr<GameObject> getGameObject(); //override;

	void setGameObject(SmartPtr<GameObject> i_pGameObj); //override;

	void updateGameObject() override;

	void HandleInput(unsigned int i_VKeyID, bool bWentDown);

	Vector2 getMovementDirectionFromUser();

	//void setPhysicsObject(PhysicsInfo * i_PhysicsObject)
	//{
	//	GamePlayerPhysics = i_PhysicsObject;
	//}

private:
	WeakPtr<GameObject>  m_pGameObject;
	//PhysicsInfo * GamePlayerPhysics;
};
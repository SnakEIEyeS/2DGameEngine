#pragma once

//#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "GLib.h"
#include "Pointers\SmartPointer.h"
#include "Pointers\WeakPointer.h"

class GameObject;
struct Vector2;

class BallController : public GameObjectController
{
public:
	BallController(SmartPtr<GameObject> i_pGameObject);
	~BallController();

	WeakPtr<GameObject> getGameObject(); //override;

	void setGameObject(SmartPtr<GameObject> i_pGameObj); //override;

	void updateGameObject() override;

	//void setPhysicsObject(PhysicsInfo * i_PhysicsObject)
	//{
	//	GamePlayerPhysics = i_PhysicsObject;
	//}

private:
	WeakPtr<GameObject>  m_pGameObject;
};
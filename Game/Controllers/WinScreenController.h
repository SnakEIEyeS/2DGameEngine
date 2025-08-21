#pragma once

#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "GLib.h"
#include "Pointers\SmartPointer.h"
#include "Pointers\WeakPointer.h"

//class GameObject;
struct Vector2;

class WinScreenController : public GameObjectController
{
public:
	WinScreenController(SmartPtr<GameObject> i_pGameObject);
	~WinScreenController();

	inline WeakPtr<GameObject> getGameObject(); //override;

	inline void setGameObject(SmartPtr<GameObject> i_pGameObj); //override;

	void updateGameObject() override;

	//void setPhysicsObject(PhysicsInfo * i_PhysicsObject)
	//{
	//	GamePlayerPhysics = i_PhysicsObject;
	//}

private:
	WeakPtr<GameObject>  m_pGameObject;
};

WeakPtr<GameObject> WinScreenController::getGameObject() { return m_pGameObject; }

void WinScreenController::setGameObject(SmartPtr<GameObject> i_pGameObj) { m_pGameObject = i_pGameObj; }

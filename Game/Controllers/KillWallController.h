#pragma once

#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "GLib.h"
#include "Pointers\SmartPointer.h"
#include "Pointers\WeakPointer.h"

//class GameObject;
struct Vector2;

class KillWallController : public GameObjectController
{
public:
	KillWallController(SmartPtr<GameObject> i_pGameObject);
	~KillWallController();

	inline WeakPtr<GameObject> getGameObject(); //override;

	inline void setGameObject(SmartPtr<GameObject> i_pGameObj); //override;

	void updateGameObject() override;

	bool getIsLeftKillWall() const;
	void setIsLeftKillWall(bool i_bLeftKillWall);

	//void setPhysicsObject(PhysicsInfo * i_PhysicsObject)
	//{
	//	GamePlayerPhysics = i_PhysicsObject;
	//}

private:
	WeakPtr<GameObject>  m_pGameObject;
	bool m_bIsLeftKillWall;
};

WeakPtr<GameObject> KillWallController::getGameObject() { return m_pGameObject; }

void KillWallController::setGameObject(SmartPtr<GameObject> i_pGameObj) { m_pGameObject = i_pGameObj; }
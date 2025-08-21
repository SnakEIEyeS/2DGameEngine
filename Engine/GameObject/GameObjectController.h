#pragma once

//class GameObject;
#include "..\Pointers\SmartPointer.h"
#include "..\Pointers\WeakPointer.h"

class GameObjectController
{
public:
	//virtual SmartPtr<GameObject>  getGameObject() = 0;

	//virtual void setGameObject(SmartPtr<GameObject> pGameObj) = 0;

	virtual ~GameObjectController() {}

	virtual void updateGameObject() = 0;
};
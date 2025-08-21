#pragma once

//#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
//#include "GLib.h"
#include "Pointers\SmartPointer.h"
#include "Pointers\WeakPointer.h"

class GameObject;
struct Vector2;

class PaddleController : public GameObjectController
{
public:
	PaddleController(SmartPtr<GameObject> i_pGameObject);
	~PaddleController();

	WeakPtr<GameObject> getGameObject(); //override;

	void setGameObject(SmartPtr<GameObject> i_pGameObj); //override;

	void updateGameObject() override;

	void setPaddleControlKeys(unsigned int i_UpKey, unsigned int i_DownKey);
	unsigned int getUpKey() const;
	unsigned int getDownKey() const;
	
	void HandleInput(unsigned int i_VKeyID, bool bWentDown);

	//void setPhysicsObject(PhysicsInfo * i_PhysicsObject)
	//{
	//	GamePlayerPhysics = i_PhysicsObject;
	//}

private:
	WeakPtr<GameObject>  m_pGameObject;
	unsigned int m_PaddleUpKey;
	unsigned int m_PaddleDownKey;
};
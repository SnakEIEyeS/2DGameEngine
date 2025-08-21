#pragma once

#include "AABB.h"
#include "..\GLib\GLib.h"
#include "..\Pointers\SmartPointer.h"
#include "..\Math\Vector2.h"
#include "..\Pointers\WeakPointer.h"
#include "GameObjectController.h"
//class GameObjectController;

class GameObject
{
public:
	static SmartPtr<GameObject> Create(const Vector2 & i_InitialPosition);
	
	//TODO make constructor private
	//TODO update GameObject constructor
	GameObject(Vector2 i_Vector2);

	GameObject();

	~GameObject();
	
	inline Vector2 getPos() const;
	inline void setPos(Vector2 ipos);
	
	inline float getZRot() const;
	inline void setZRot(float i_ZRot);
	
	inline AABB getBB() const;
	inline void setBB(AABB i_AABB);

	inline Vector2 getVelocity() const;
	inline void setVelocity(Vector2 i_Velocity);
	inline Vector2 getMaxVelocity() const;
	inline void setMaxVelocity(Vector2 i_Velocity);

	//WeakPtr<GameObjectController> GetController() const;
	//void SetController(SmartPtr<GameObjectController> & i_NewController);	

	GameObjectController * GetController() const;
	void SetController(GameObjectController * i_NewController);	

	inline bool getMovable() const;
	inline void setMovable(bool i_bMovable);
	
private:
	AABB m_BB;
	Vector2 m_Position;
	Vector2 m_Velocity;
	Vector2 m_MaxVelocity;
	float m_ZRotation;
	//SmartPtr<GameObjectController> m_Controller;
	GameObjectController * m_Controller;
	bool m_bMovable;
};

#include "GameObject-inl.h"

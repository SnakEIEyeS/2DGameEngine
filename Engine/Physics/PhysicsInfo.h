#pragma once

#include "..\GLib\GLib.h"
#include "..\Math\Vector2.h"
#include "..\GameObject\GameObject.h"
#include "..\Pointers\SmartPointer.h"
#include "..\Pointers\WeakPointer.h"

class GameObject;

//TODO add maximum velocity
class PhysicsInfo
{
public:
	PhysicsInfo(SmartPtr<GameObject> i_pGameObject, float i_Mass, float i_Drag);
	~PhysicsInfo();

	WeakPtr<GameObject> getGameObject();

	float getMass() const;

	Vector2 getUpdatedPosition() const;
	void setUpdatedPosition(Vector2 i_UpdatedPosition);

	Vector2 getVelocity() const;
	void setVelocity(Vector2 i_Velocity);

	void UpdateDrivingForces(Vector2 DrivingForce);
	void ResetDrivingForces();

	void setDrivingForceStopped(bool i_bStopped);

	bool getCollisionKilling() const;
	void setCollisionKilling(bool i_bCollKilling);

	void CalcAcceleration();

	void UpdateObject(float dt);
	void AttemptUpdateObject(float dt);
	void FinalizeUpdate();

private:
	WeakPtr<GameObject> m_pGameObject;
	Vector2 m_PreviousPosition;
	Vector2 UpdatedPosition;
	Vector2 m_Velocity;
	Vector2 m_Acceleration;
	Vector2 sumDrivingForces;
	float m_Mass;
	float m_Drag;
	bool m_bDrivingForceStopped;
	bool m_bCollisionKilling;

	void setPosition(Vector2 newPos);
};
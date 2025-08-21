#include "PhysicsInfo.h"

#include <Math.h>

#include "..\GLib\_Console\ConsolePrint.h"
#include "..\Math\FloatOperations.h"
//#include "GameObject.h"

PhysicsInfo::PhysicsInfo(SmartPtr<GameObject> i_GameObject, float i_Mass, float i_Drag) : m_pGameObject(i_GameObject), m_Mass(i_Mass), m_Drag(i_Drag)
{
	m_PreviousPosition = m_pGameObject.Acquire()->getPos();
	m_bDrivingForceStopped = true;
}

PhysicsInfo::~PhysicsInfo()
{
}

WeakPtr<GameObject>  PhysicsInfo::getGameObject() { return m_pGameObject; }

float PhysicsInfo::getMass() const
{
	return m_Mass;
}

Vector2 PhysicsInfo::getUpdatedPosition() const
{
	return UpdatedPosition;
}

void PhysicsInfo::setUpdatedPosition(Vector2 i_UpdatedPosition)
{
	UpdatedPosition = i_UpdatedPosition;
}

Vector2 PhysicsInfo::getVelocity() const { return m_Velocity; }

void PhysicsInfo::setVelocity(Vector2 i_Velocity)
{
	m_Velocity = i_Velocity;
}

void PhysicsInfo::UpdateDrivingForces(Vector2 DrivingForce)
{
	sumDrivingForces.x += DrivingForce.x;
	sumDrivingForces.y += DrivingForce.y;
}

void PhysicsInfo::ResetDrivingForces()
{
	sumDrivingForces.x = 0.f;
	sumDrivingForces.y = 0.f;

	//m_Acceleration.x = 0.f;
	//m_Acceleration.y = 0.f;
}

void PhysicsInfo::setDrivingForceStopped(bool i_bStopped)
{
	m_bDrivingForceStopped = i_bStopped;
}

bool PhysicsInfo::getCollisionKilling() const { return m_bCollisionKilling; }

void PhysicsInfo::setCollisionKilling(bool i_bCollKilling) { m_bCollisionKilling = i_bCollKilling; }

void PhysicsInfo::CalcAcceleration()
{
	m_Acceleration.x = float((sumDrivingForces.x )/ m_Mass);
	m_Acceleration.y = float((sumDrivingForces.y )/ m_Mass);

	return;
}

void PhysicsInfo::UpdateObject(float dt)
{
	//Vector2 newPosition = m_pGameObject.Acquire()->getPos();
	/*if (!m_bDrivingForceStopped)
	{
		UpdateDrivingForces(Vector2{-(m_Drag*m_Velocity.x*m_Velocity.x), -(m_Drag*m_Velocity.y*m_Velocity.y)});
	}*/
	CalcAcceleration();

	if (m_bDrivingForceStopped)
	{
		m_PreviousPosition = m_pGameObject.Acquire()->getPos();
		m_Velocity.x = 0.f;
		m_Velocity.y = 0.f;
	}

	m_Velocity.x = m_Velocity.x + m_Acceleration.x * dt;
	m_Velocity.y = m_Velocity.y + m_Acceleration.y * dt;

	if (m_Velocity.x > m_pGameObject.Acquire()->getMaxVelocity().x)
	{
		m_Velocity.x = m_pGameObject.Acquire()->getMaxVelocity().x;
	}
	else if (m_Velocity.x < -(m_pGameObject.Acquire()->getMaxVelocity().x))
	{
		m_Velocity.x = -(m_pGameObject.Acquire()->getMaxVelocity().x);
	}
	if (m_Velocity.y > m_pGameObject.Acquire()->getMaxVelocity().y)
	{
		m_Velocity.y = m_pGameObject.Acquire()->getMaxVelocity().y;
	}
	else if (m_Velocity.y < -(m_pGameObject.Acquire()->getMaxVelocity().y))
	{
		m_Velocity.y = -(m_pGameObject.Acquire()->getMaxVelocity().y);
	}

	Vector2 newPosition(m_pGameObject.Acquire()->getPos().x + m_Velocity.x * dt, m_pGameObject.Acquire()->getPos().y + m_Velocity.y * dt);
	m_pGameObject.Acquire()->setPos(newPosition);
	m_pGameObject.Acquire()->setVelocity(m_Velocity);

	//Calculate the new position
	//* (2.f - m_Drag)
	/*if (!AreAboutEqual(sumDrivingForces.x, 0.f))
	{
		newPosition.x = (m_pGameObject.Acquire()->getPos().x) * (2.0f) - m_PreviousPosition.x + m_Acceleration.x * dt * dt;
	}
	if (!AreAboutEqual(sumDrivingForces.y, 0.f))
	{
		newPosition.y = (m_pGameObject.Acquire()->getPos().y) * (2.0f) - m_PreviousPosition.y + m_Acceleration.y * dt * dt;
	}
	//newPosition.x = (m_GameObject->getPos().x) * (2.0f) - m_PreviousPosition.x + m_Acceleration.x * dt * dt;
	//newPosition.y = (m_GameObject->getPos().y) * (2.0f) - m_PreviousPosition.y + m_Acceleration.y * dt * dt;
	//newPosition.x = m_GameObject->getPos().x + 0.0001f;
	//newPosition.y = m_GameObject->getPos().y + 0.0001f;

	m_PreviousPosition = m_pGameObject.Acquire()->getPos();	//Set the current position as previous position for next run

	//m_GameObject->setPos(newPosition);
	m_pGameObject.Acquire()->setPos(newPosition);	//Update GameObject's current position
	//setPosition(newPosition);	
	*/
	return;
}

void PhysicsInfo::AttemptUpdateObject(float dt)
{
	CalcAcceleration();

	if (m_bDrivingForceStopped)
	{
		m_PreviousPosition = m_pGameObject.Acquire()->getPos();
		m_Velocity.x = 0.f;
		m_Velocity.y = 0.f;

	}

	m_Velocity.x = m_Velocity.x + m_Acceleration.x * dt;
	m_Velocity.y = m_Velocity.y + m_Acceleration.y * dt;

	if (m_Velocity.x > m_pGameObject.Acquire()->getMaxVelocity().x)
	{
		m_Velocity.x = m_pGameObject.Acquire()->getMaxVelocity().x;
	}
	if (m_Velocity.y > m_pGameObject.Acquire()->getMaxVelocity().y)
	{
		m_Velocity.y = m_pGameObject.Acquire()->getMaxVelocity().y;
	}
	if (m_Velocity.y > m_pGameObject.Acquire()->getMaxVelocity().y)
	{
		m_Velocity.y = m_pGameObject.Acquire()->getMaxVelocity().y;
	}
	else if (m_Velocity.y < -(m_pGameObject.Acquire()->getMaxVelocity().y))
	{
		m_Velocity.y = -(m_pGameObject.Acquire()->getMaxVelocity().y);
	}

	//UpdatedPosition = Vector2(m_pGameObject.Acquire()->getPos().x + m_Velocity.x * dt, m_pGameObject.Acquire()->getPos().y + m_Velocity.y * dt);
	UpdatedPosition.x = m_pGameObject.Acquire()->getPos().x + m_Velocity.x * dt;
	UpdatedPosition.y = m_pGameObject.Acquire()->getPos().y + m_Velocity.y * dt;
}

void PhysicsInfo::FinalizeUpdate()
{
	m_pGameObject.Acquire()->setPos(UpdatedPosition);
	m_pGameObject.Acquire()->setVelocity(m_Velocity);
}

void PhysicsInfo::setPosition(Vector2 newPos)
{
	m_pGameObject.Acquire()->setPos(newPos);
	m_pGameObject.Acquire()->setVelocity(m_Velocity);

	return;
}
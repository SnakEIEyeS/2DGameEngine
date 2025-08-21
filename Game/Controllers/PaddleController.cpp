#include "PaddleController.h"

//#include <conio.h>
//#include <iostream>

#include "_Console\ConsolePrint.h"
#include "Messaging\Delegates.h"
#include "InputSystem\InputSystem.h"
#include "Physics\Physics.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"
#include "Pointers\WeakPointer.h"


PaddleController::PaddleController(SmartPtr<GameObject> i_pGameObject) : m_pGameObject(i_pGameObject)
{
	Engine::InputSystem::GetButtonChangeReceivers().AddDelegate(Engine::InputSystem::ButtonChangeReceiver_t::Create<PaddleController, &PaddleController::HandleInput>(this));
}

PaddleController::~PaddleController()
{
	Engine::InputSystem::GetButtonChangeReceivers().RemoveDelegate(Engine::InputSystem::ButtonChangeReceiver_t::Create<PaddleController, &PaddleController::HandleInput>(this));
}

WeakPtr<GameObject> PaddleController::getGameObject()
{
	return m_pGameObject;
}

void PaddleController::setGameObject(SmartPtr<GameObject> i_pGameObj)
{
	m_pGameObject = i_pGameObj;
}

void PaddleController::updateGameObject()
{
}

void PaddleController::setPaddleControlKeys(unsigned int i_UpKey, unsigned int i_DownKey)
{
	m_PaddleUpKey = i_UpKey;
	m_PaddleDownKey = i_DownKey;
}

unsigned int PaddleController::getUpKey() const
{
	return m_PaddleUpKey;
}

unsigned int PaddleController::getDownKey() const
{
	return m_PaddleDownKey;
}

void PaddleController::HandleInput(unsigned int i_VKeyID, bool bWentDown)
{
	//DEBUG_PRINT("Paddle's HandleInput called\n");

	if (bWentDown)
	{
		if (i_VKeyID == m_PaddleUpKey)
		{
			Engine::Physics::ApplyForce(m_pGameObject, Vector2{ 0.0f, 0.1f });
			//GamePlayerPhysics->setDrivingForceStopped(false);
			//GamePlayerPhysics->UpdateDrivingForces(Vector2{ 0.0f, 10.1f });
		}
		else if (i_VKeyID == m_PaddleDownKey)
		{
			Engine::Physics::ApplyForce(m_pGameObject, Vector2{ 0.f, -0.1f });
			//GamePlayerPhysics->setDrivingForceStopped(false);
			//GamePlayerPhysics->UpdateDrivingForces(Vector2{ 0.0f, -10.1f });
		}
	}

	else if (!bWentDown)
	{
		if (i_VKeyID == m_PaddleUpKey)
		{
			Engine::Physics::RemoveForces(m_pGameObject);
			//g_VKeyID = 0;
			//GamePlayerPhysics->setDrivingForceStopped(true);
		}
		else if (i_VKeyID == m_PaddleDownKey)
		{
			Engine::Physics::RemoveForces(m_pGameObject);
			//g_VKeyID = 0;
			//GamePlayerPhysics->setDrivingForceStopped(true);
		}

		//case 0x1b:	//Esc
		//	bQuit = true;
		//	break;

	}
}

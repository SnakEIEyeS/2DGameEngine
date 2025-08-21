#include "PlayerController.h"

#include <conio.h>
#include <iostream>

#include "_Console\ConsolePrint.h"
#include "Messaging\Delegates.h"
#include "InputSystem\InputSystem.h"
#include "Physics\Physics.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"
#include "Pointers\WeakPointer.h"


PlayerController::PlayerController(SmartPtr<GameObject> i_pGameObject) : m_pGameObject(i_pGameObject)
{
	Engine::InputSystem::GetButtonChangeReceivers().AddDelegate(Engine::InputSystem::ButtonChangeReceiver_t::Create<PlayerController, &PlayerController::HandleInput>(this));
}

PlayerController::~PlayerController()
{
	Engine::InputSystem::GetButtonChangeReceivers().RemoveDelegate(Engine::InputSystem::ButtonChangeReceiver_t::Create<PlayerController, &PlayerController::HandleInput>(this));
}

WeakPtr<GameObject> PlayerController::getGameObject()
{
	return m_pGameObject;
}

void PlayerController::setGameObject(SmartPtr<GameObject> i_pGameObj)
{
	m_pGameObject = i_pGameObj;
}

void PlayerController::updateGameObject()
{
	Vector2 iDirection = getMovementDirectionFromUser();

	/*if (128 >= mGameObject->getPos().getx() + iDirection.getx() && mGameObject->getPos().getx() + iDirection.getx() >= 0
		&& 128 >= mGameObject->getPos().gety() + iDirection.gety() && mGameObject->getPos().gety() + iDirection.gety() >= 0)
	{
		mGameObject->setPos(mGameObject->getPos() + iDirection);
	}
	else
	{
		std::cout << "You're at the edge of the grid! Can't go any further this way! Change directions, NOW!\n";
	}*/
}

void PlayerController::HandleInput(unsigned int i_VKeyID, bool bWentDown)
{
	DEBUG_PRINT("Player's HandleInput called\n");

	if (bWentDown)
	{
		switch (i_VKeyID)
		{
		case 0x57:	//W

			Engine::Physics::ApplyForce(m_pGameObject, Vector2{ 0.0f, 0.1f });
			//GamePlayerPhysics->setDrivingForceStopped(false);
			//GamePlayerPhysics->UpdateDrivingForces(Vector2{ 0.0f, 10.1f });


			break;

		case 0x53:	//S
		{
			Engine::Physics::ApplyForce(m_pGameObject, Vector2{ 0.f, -0.1f });
			//GamePlayerPhysics->setDrivingForceStopped(false);
			//GamePlayerPhysics->UpdateDrivingForces(Vector2{ 0.0f, -10.1f });
		}
		break;

		case 0x41:	//A
		{
			Engine::Physics::ApplyForce(m_pGameObject, Vector2{ -0.1f, 0.f });
			//GamePlayerPhysics->setDrivingForceStopped(false);
			//GamePlayerPhysics->UpdateDrivingForces(Vector2{ -10.1f, 0.0f });
		}
		break;

		case 0x44:	//D
		{
			Engine::Physics::ApplyForce(m_pGameObject, Vector2{ 0.1f, 0.f });
			//GamePlayerPhysics->setDrivingForceStopped(false);
			//GamePlayerPhysics->UpdateDrivingForces(Vector2{ 10.1f, 0.0f });
		}
		break;

		default:
			break;
		}
	}

	//TODO try applying force in reverse direction on key up instead of stopping completely
	else if (!bWentDown)
	{
		switch (i_VKeyID)
		{
		case 0x57:	//W
		{
			Engine::Physics::RemoveForces(m_pGameObject);
			//g_VKeyID = 0;
			//GamePlayerPhysics->setDrivingForceStopped(true);
		}
		break;

		case 0x53:	//S
		{
			Engine::Physics::RemoveForces(m_pGameObject);
			//g_VKeyID = 0;
			//GamePlayerPhysics->setDrivingForceStopped(true);
		}
		break;

		case 0x41:	//A
		{
			Engine::Physics::RemoveForces(m_pGameObject);
			//g_VKeyID = 0;
			//GamePlayerPhysics->setDrivingForceStopped(true);
		}
		break;

		case 0x44:	//D
		{
			Engine::Physics::RemoveForces(m_pGameObject);
			//g_VKeyID = 0;
			//GamePlayerPhysics->setDrivingForceStopped(true);
		}
		break;

		//case 0x1b:	//Esc
		//	bQuit = true;
		//	break;

		default:
			break;
		}
	}
}

Vector2 PlayerController::getMovementDirectionFromUser()
{
	char ip = _getch();
	switch (ip)
	{
		//Directional movement input
	case 'W':
	case 'w': std::cout << "Pressed w to move up.\n";
		return Vector2(0, -1);
		break;

	case 'S':
	case 's': std::cout << "Pressed s to move down.\n";
		return Vector2(0, 1);
		break;

	case 'A':
	case 'a': std::cout << "Pressed a to move left.\n";
		return Vector2(-1, 0);
		break;

	case 'D':
	case 'd': std::cout << "Pressed d to move right.\n";
		return Vector2(1, 0);
		break;

	default: std::cout << "Invalid input.\n";
		return Vector2(0, 0);
		break;
	}
}
#include "Pong.h"

#include <assert.h>
#include <stdlib.h>

#include "..\Controllers\BallController.h"
#include "_Console\ConsolePrint.h"
#include "ControllerStore\ControllerStore.h"
#include "Messaging\Delegates.h"
#include "Math\FloatOperations.h"
#include "..\Game.h"
#include "GameObject\GameObject.h"
#include "GameObject\GameObjectStore.h"
#include "InputSystem\InputSystem.h"
#include "..\Controllers\KillWallController.h"
#include "..\Controllers\PaddleController.h"
#include "Physics\Physics.h"
#include "..\ProcessObjects\ProcessGameObject.h"
#include "Renderer\Renderer.h"
#include "Pointers\SmartPointer.h"
#include "..\Controllers\WinScreenController.h"

namespace Game
{
	float const Pong::ForceValue = 0.0000001f;

	Pong::Pong() : PaddleCount(0), LeftPlayerScore(0), RightPlayerScore(0)
	{
		Engine::InputSystem::GetButtonChangeReceivers().AddDelegate(Engine::InputSystem::ButtonChangeReceiver_t::Create<Pong, &Pong::HandleRoundStart>(this));
		Engine::Physics::GetBallDeathReceivers().AddDelegate(Engine::Physics::BallDeathReceiver_t::Create<Pong, &Pong::HandleBallDeath>(this));
		Engine::Physics::GetBallReboundReceivers().AddDelegate(Engine::Physics::BallReboundReceiver_t::Create<Pong, &Pong::HandleBallRebound>(this));
	}

	Pong::~Pong()
	{
		Engine::InputSystem::GetButtonChangeReceivers().RemoveDelegate(Engine::InputSystem::ButtonChangeReceiver_t::Create<Pong, &Pong::HandleRoundStart>(this));
		Engine::Physics::GetBallDeathReceivers().RemoveDelegate(Engine::Physics::BallDeathReceiver_t::Create<Pong, &Pong::HandleBallDeath>(this));
		Engine::Physics::GetBallReboundReceivers().RemoveDelegate(Engine::Physics::BallReboundReceiver_t::Create<Pong, &Pong::HandleBallRebound>(this));
	}

	void Pong::Initialize()
	{
		ProcessGameObject("data\\PongBall.lua");
		ProcessGameObject("data\\PaddleLeft.lua");
		ProcessGameObject("data\\PaddleRight.lua");
		ProcessGameObject("data\\TopBounds.lua");
		ProcessGameObject("data\\BottomBounds.lua");
		ProcessGameObject("data\\LeftKillWall.lua");
		ProcessGameObject("data\\RightKillWall.lua");
	}

	void Pong::Tick()
	{
		Engine::Physics::ApplyForce(m_pBallController->getGameObject(), m_BallDrivingForce);
		CheckAndBoundPaddles();
	}

	void Pong::UpdateScore(WeakPtr<GameObject> i_KillWall)
	{
		KillWallController * pWallController = dynamic_cast<KillWallController *>(i_KillWall.Acquire()->GetController());
		assert(pWallController);
		if (pWallController->getIsLeftKillWall())
		{
			if (++RightPlayerScore >= m_WinningScore)
			{
				DEBUG_PRINT("\n\nPlayer Right Wins!\n\n");
				ProcessGameObject("..\\Game\\data\\RightWin.lua");
				m_bWinScreen = true;
			}
		}
		else
		{
			if (++LeftPlayerScore >= m_WinningScore)
			{
				DEBUG_PRINT("\n\nPlayer Left Wins!\n\n");
				ProcessGameObject("..\\Game\\data\\LeftWin.lua");
				m_bWinScreen = true;
			}
		}

		DEBUG_PRINT("Score: %d-%d\n", LeftPlayerScore, RightPlayerScore);
	}

	void Pong::RestartPong()
	{
		DEBUG_PRINT("\n\nRestarting Game\n\n");
		RemoveWinScreen();
		m_bWinScreen = false;

		LeftPlayerScore = 0;
		RightPlayerScore = 0;

		DEBUG_PRINT("Score: %d-%d\n", LeftPlayerScore, RightPlayerScore);
	}

	void Pong::HandleBallCreation(WeakPtr<GameObject> i_GameObject)
	{

	}

	void Pong::HandleRoundStart(unsigned int i_VKeyID, bool bWentDown)
	{
		//DEBUG_PRINT("VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
		if (!bWentDown)
		{
			if (i_VKeyID == m_RoundStartKey && !m_bRoundStarted)
			{
				DEBUG_PRINT("\n\nRound Start!\n");

				if (m_bWinScreen)
				{
					RestartPong();
				}
				else
				{
					RoundSetBallDirection();
					//m_BallDrivingForce = Vector2{ 0.0000001f, 0.0000001f };
					m_bRoundStarted = true;
				}
			}

			if (i_VKeyID == m_QuitKey)
			{
				DEBUG_PRINT("Exiting Game\n");
				//bQuit = true;
				Game::SetGQuit(true);
			}
		}
	}

	void Pong::HandleBallDeath(WeakPtr<GameObject> i_KillWall)
	{
		DEBUG_PRINT("Handle Death called\n");
		//Engine::Physics::RemoveForces(GetPongBallController().getGameObject());
		m_BallDrivingForce = Vector2{ 0.f, 0.f };
		m_bRoundStarted = false;

		UpdateScore(i_KillWall);
	}

	void Pong::HandleBallRebound(Vector2 i_CollisionNormal)
	{
		DEBUG_PRINT("Handle Rebound called\n");

		if (!AreAboutEqual(i_CollisionNormal.x, 0.f))	//Collision along x-axis
		{
			m_BallDrivingForce.x = -m_BallDrivingForce.x;
		}
		if (!AreAboutEqual(i_CollisionNormal.y, 0.f))
		{
			m_BallDrivingForce.y = -m_BallDrivingForce.y;
		}
	}

	void Pong::setBallController(BallController * i_pBallController) { m_pBallController = i_pBallController; }
	BallController * Pong::getBallController(void) const { return m_pBallController; }

	void Pong::AddPaddle(PaddleController * i_PaddleController)
	{
		//PaddleController * PaddleControllerRef = dynamic_cast<PaddleController *>(i_GOController);
		//assert(PaddleControllerRef);

		PaddleArray[PaddleCount++] = i_PaddleController;
	}

	void Pong::CheckAndBoundPaddles()
	{
		for (size_t i = 0; i < PaddleCount; i++)
		{
			SmartPtr<GameObject> PaddleGORef = (PaddleArray[i]->getGameObject().Acquire());
			if (PaddleGORef)
			{
				if (PaddleGORef->getPos().y > ScreenHeight / 2 - (2 * PaddleGORef->getBB().Extents.y))
				{
					PaddleGORef->setPos(Vector2{ PaddleGORef->getPos().x, static_cast<float>(ScreenHeight / 2) - (2 * PaddleGORef->getBB().Extents.y) });
				}
				else if (PaddleGORef->getPos().y < -(ScreenHeight / 2))
				{
					PaddleGORef->setPos(Vector2{ PaddleGORef->getPos().x, static_cast<float>(-ScreenHeight/2)});
				}
			}//end if
		}//end for loop
	}

	void Pong::RoundSetBallDirection()
	{
		unsigned int RandomDirection = rand() % 4 + 1;
		switch (RandomDirection)
		{
		case 1:
			m_BallDrivingForce = Vector2{ ForceValue, ForceValue };
			break;

		case 2:
			m_BallDrivingForce = Vector2{ ForceValue, -ForceValue };
			break;

		case 3:
			m_BallDrivingForce = Vector2{ -ForceValue, ForceValue };
			break;

		case 4:
			m_BallDrivingForce = Vector2{ -ForceValue, -ForceValue };
			break;

		default:
			break;
		}
	}

	void Pong::setWinScreen(WinScreenController * i_WinScreen) { pWinScreen = i_WinScreen; }	
	WinScreenController * Pong::getWinScreen() { return pWinScreen; }

	void Pong::RemoveWinScreen()
	{
		//Important: Get Ptr to WinScreen's GameObject. We need it later as Removing the Controller leaves us no way to get the GameObject.
		WeakPtr<GameObject> WinScreenGO(pWinScreen->getGameObject());

		Engine::Rendering::RemoveRenderable(WinScreenGO);
		Engine::ControllerStore::RemoveController(pWinScreen);
		Engine::GameObjectStore::RemoveGameObject(WinScreenGO);
		//pWinScreen = nullptr;
	}
}
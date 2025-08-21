#pragma once

#include "Math\Vector2.h"
#include "Pointers\WeakPointer.h"
class BallController;
class GameObject;
class GameObjectController;
class PaddleController;
class WinScreenController;

namespace Game
{
	class Pong
	{
	public:
		Pong();
		~Pong();

		void Initialize();
		void Tick();
		
		void UpdateScore(WeakPtr<GameObject> i_KillWall);
		void RestartPong();

		void HandleBallCreation(WeakPtr<GameObject> i_WeakObject);
		void HandleRoundStart(unsigned int i_VKeyID, bool bWentDown);
		void HandleBallDeath(WeakPtr<GameObject> i_KillWall);
		void HandleBallRebound(Vector2 i_CollisionNormal);

		void setBallController(BallController * i_pBallController);
		BallController * getBallController(void) const;
		
		void AddPaddle(PaddleController * i_PaddleController);
		void CheckAndBoundPaddles();

		void RoundSetBallDirection();
		inline void setBallDrivingForce(Vector2 i_Force);
		inline Vector2 getBallDrivingForce() const;

		void setWinScreen(WinScreenController * i_WinScreen);
		WinScreenController * getWinScreen();
		void RemoveWinScreen();

		//inline bool getQuitFlag() const;
		//inline void setQuitFlag(bool i_Quit);

	private:
		Vector2 m_BallDrivingForce;
		BallController * m_pBallController;
		WinScreenController * pWinScreen;
		PaddleController * PaddleArray[2];
		static float const ForceValue;
		static unsigned int const m_RoundStartKey = 0x20;
		static unsigned int const m_QuitKey = 0x1b;
		static unsigned int const m_WinningScore = 5;

		unsigned int PaddleCount;
		unsigned int LeftPlayerScore;
		unsigned int RightPlayerScore;

		bool m_bRoundStarted = false;
		bool m_bWinScreen = false;
		//bool bQuit = false;
	};



	void Pong::setBallDrivingForce(Vector2 i_Force) { m_BallDrivingForce = i_Force; }
	Vector2 Pong::getBallDrivingForce() const { return m_BallDrivingForce; }



	//bool Pong::getQuitFlag() const { return bQuit; }

	//void Pong::setQuitFlag(bool i_Quit) { bQuit = i_Quit; }
}

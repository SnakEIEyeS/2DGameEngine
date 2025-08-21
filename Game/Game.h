#pragma once

#include "Pong\Pong.h"

class BallController;

namespace Game
{
	extern bool g_bQuit;
	static int ScreenWidth = 1200;
	static int ScreenHeight = 800;

	bool StartUp();
	bool ShutDown();

	void Run(float dt);

	bool GetGQuit();
	void SetGQuit(bool i_bQuit);
	
	extern Pong * g_PongInstance;
	Pong & GetPongInstance();
	void SetPongInstance(Pong * i_PongInstance);

	void SetPongBallController(BallController * i_BallController);
}

#include "Game-inl.h"





/*#pragma once

#include <vector>
#include "GameObjectController.h"
#include "WeakPointer.h"
//add PlayerController
// probably make this into a class
/*
namespace Game
{
	extern std::vector<WeakPtr<GameObjectController>> * GameObjectControllerList;

	bool StartUp();
	bool ShutDown();

	std::vector<WeakPtr<GameObjectController>> & GetGOControllerList();
	void AddController(WeakPtr<GameObjectController> i_WeakController);
	void RemoveController(WeakPtr<GameObjectController> i_WeakController);

	//bool ReleaseControllers();
}*/
/*
namespace Game
{
	extern std::vector<GameObjectController *> * GameObjectControllerList;

	bool StartUp();
	bool ShutDown();

	std::vector<GameObjectController *> & GetGOControllerList();
	void AddController(GameObjectController * i_WeakController);
	void RemoveController(GameObjectController * i_WeakController);

	//bool ReleaseControllers();
}
*/
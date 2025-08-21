#include "Game.h"

#include <assert.h>
#include <vector>

#include "Controllers\BallController.h"
#include "Pong\Pong.h"

namespace Game
{
	bool g_bQuit = false;
	Pong * g_PongInstance = nullptr;

	bool StartUp()
	{
		Game::SetPongInstance(new Game::Pong());
		Game::GetPongInstance().Initialize();
		return true;
	}

	bool ShutDown()
	{
		delete g_PongInstance;
		
		return true;
	}


	void Run(float dt)
	{

		Game::GetPongInstance().Tick();

	}


	bool GetGQuit() { return g_bQuit; }
	void SetGQuit(bool i_bQuit) { g_bQuit = i_bQuit; }

	Pong & GetPongInstance()
	{
		assert(g_PongInstance != nullptr);
		return *g_PongInstance;
	}

	void SetPongInstance(Pong * i_PongInstance)
	{
		assert(i_PongInstance);
		g_PongInstance = i_PongInstance;
	}

	void SetPongBallController(BallController * i_BallController)
	{
		assert(i_BallController);
		GetPongInstance().setBallController(i_BallController);
	}
	
}





/*#include <algorithm>

namespace Game
{
	std::vector<WeakPtr<GameObjectController>> * GameObjectControllerList = nullptr;

	bool StartUp()
	{
		return false;
	}

	bool ShutDown()
	{
		GetGOControllerList().clear();
		delete GameObjectControllerList;

		return true;
	}

	std::vector<WeakPtr<GameObjectController>>& GetGOControllerList()
	{
		if (GameObjectControllerList == nullptr)
		{
			GameObjectControllerList = new std::vector<WeakPtr<GameObjectController>>();
		}

		return *GameObjectControllerList;
	}

	void AddController(WeakPtr<GameObjectController> i_WeakController)
	{
		GetGOControllerList().push_back(i_WeakController);
	}

	void RemoveController(WeakPtr<GameObjectController> i_WeakController)
	{
		GetGOControllerList().erase(std::remove_if(GetGOControllerList().begin(), GetGOControllerList().end(), [i_WeakController](WeakPtr<GameObjectController> i_Entry) {return i_Entry == i_WeakController;}),
			GetGOControllerList().end());
	}
}*/
/*
namespace Game
{
	std::vector<GameObjectController *> * GameObjectControllerList = nullptr;

	bool StartUp()
	{
		return false;
	}

	bool ShutDown()
	{
		std::vector<GameObjectController *> GOListRef = GetGOControllerList();
		for (auto GOController : GOListRef)
		{
			delete GOController;
		}

		GOListRef.clear();
		//GetGOControllerList().clear();
		delete GameObjectControllerList;

		return true;
	}

	std::vector<GameObjectController *>& GetGOControllerList()
	{
		if (GameObjectControllerList == nullptr)
		{
			GameObjectControllerList = new std::vector<GameObjectController *>();
		}

		return *GameObjectControllerList;
	}

	void AddController(GameObjectController * i_WeakController)
	{
		GetGOControllerList().push_back(i_WeakController);
	}

	void RemoveController(GameObjectController * i_WeakController)
	{
		GetGOControllerList().erase(std::remove_if(GetGOControllerList().begin(), GetGOControllerList().end(), [i_WeakController](GameObjectController * i_Entry) {return i_Entry == i_WeakController;}),
			GetGOControllerList().end());
	}
}*/
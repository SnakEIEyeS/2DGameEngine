#pragma once

#include <vector>

//#include "GameObjectController.h"
//#include "WeakPointer.h"
class GameObjectController;

namespace Engine
{
	namespace ControllerStore
	{
		extern std::vector<GameObjectController *> * GameObjectControllerList;

		bool StartUp();
		bool ShutDown();

		std::vector<GameObjectController *> & GetGOControllerList();
		void AddController(GameObjectController * i_WeakController);
		void RemoveController(GameObjectController * i_WeakController);

		//bool ReleaseControllers();
	}
}

/*
namespace ControllerStore
{
extern std::vector<WeakPtr<GameObjectController>> * GameObjectControllerList;

bool StartUp();
bool ShutDown();

std::vector<WeakPtr<GameObjectController>> & GetGOControllerList();
void AddController(WeakPtr<GameObjectController> i_WeakController);
void RemoveController(WeakPtr<GameObjectController> i_WeakController);

//bool ReleaseControllers();
}*/

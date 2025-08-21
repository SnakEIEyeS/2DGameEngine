#include "ControllerStore.h"

#include <algorithm>

#include "..\GameObject\GameObjectController.h"


namespace Engine
{
	namespace ControllerStore
	{
		std::vector<GameObjectController *> * GameObjectControllerList = nullptr;

		bool StartUp()
		{
			if (GameObjectControllerList == nullptr)
			{
				GameObjectControllerList = new std::vector<GameObjectController *>();
			}
			return true;
		}

		bool ShutDown()
		{
			std::vector<GameObjectController *> GOListRef = GetGOControllerList();
			for (auto GOController : GOListRef)
			{
				delete GOController;
			}

			//GOListRef.clear();
			GetGOControllerList().clear();
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
			//GetGOControllerList().erase(std::remove_if(GetGOControllerList().begin(), GetGOControllerList().end(), [i_WeakController](GameObjectController * i_Entry) {return i_Entry == i_WeakController;}),
			//	GetGOControllerList().end());
			std::vector<GameObjectController *> ControllerListRef = GetGOControllerList();
			std::vector<GameObjectController *>::iterator IterBegin = GetGOControllerList().begin();
			std::vector<GameObjectController *>::iterator IterEnd = GetGOControllerList().end();
			std::vector<GameObjectController *>::iterator ControllerIter = std::find_if(IterBegin, IterEnd, [i_WeakController](GameObjectController * i_Entry) {return i_Entry == i_WeakController;});
			if (ControllerIter != IterEnd)
			{
				*ControllerIter = GetGOControllerList().back();
				delete *ControllerIter;
				GetGOControllerList().pop_back();
			}
		}

	}	//namespace ControllerStore
}	//namespace Engine



/*
namespace ControllerStore
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
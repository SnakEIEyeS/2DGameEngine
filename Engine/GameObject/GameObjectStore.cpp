#include "GameObjectStore.h"

#include <algorithm>

#include "GameObject.h"

namespace Engine
{
	namespace GameObjectStore
	{
		std::vector<SmartPtr<GameObject>> * MasterGameObjects = nullptr;

		bool StartUp()
		{
			if (MasterGameObjects == nullptr)
			{
				MasterGameObjects = new std::vector<SmartPtr<GameObject>>();
			}
			return true;
		}

		bool ShutDown()
		{
			//GetMasterGameObjects().clear();
			delete MasterGameObjects;
			return true;
		}

		void Run()
		{
		}


		std::vector<SmartPtr<GameObject>> & GetMasterGameObjects()
		{
			return *MasterGameObjects;
		}

		void AddGameObject(SmartPtr<GameObject> i_GameObject)
		{
			GetMasterGameObjects().push_back(i_GameObject);
		}

		void RemoveGameObject(WeakPtr<GameObject> i_WeakObject)
		{
			//GetMasterGameObjects().erase(std::remove_if(GetMasterGameObjects().begin(), GetMasterGameObjects().end(), [i_WeakObject](SmartPtr<GameObject> i_Entry) {return i_Entry == i_WeakObject;}),
			//	GetMasterGameObjects().end());
			std::vector<SmartPtr<GameObject>> MasterGORef = GetMasterGameObjects();
			std::vector<SmartPtr<GameObject>>::iterator IterBegin = MasterGORef.begin();
			std::vector<SmartPtr<GameObject>>::iterator IterEnd = MasterGORef.end();
			std::vector<SmartPtr<GameObject>>::iterator GOIter = std::find_if(IterBegin, IterEnd, [i_WeakObject](SmartPtr<GameObject> i_Entry) {return i_Entry == i_WeakObject;});
			if (GOIter != IterEnd)
			{
				*GOIter = MasterGORef.back();
				MasterGORef.pop_back();
			}
		}
	}
}

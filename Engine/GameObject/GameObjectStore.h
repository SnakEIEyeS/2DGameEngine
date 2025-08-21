#pragma once

#include <vector>

#include "..\Pointers\SmartPointer.h"
#include "..\Pointers\WeakPointer.h"
class GameObject;

namespace Engine
{
	namespace GameObjectStore
	{
		extern std::vector<SmartPtr<GameObject>> * MasterGameObjects;

		bool StartUp();
		bool ShutDown();
		
		void Run();

		std::vector<SmartPtr<GameObject>> & GetMasterGameObjects();
		void AddGameObject(SmartPtr<GameObject> i_GameObject);
		void RemoveGameObject(WeakPtr<GameObject> i_WeakObject);
	}
}

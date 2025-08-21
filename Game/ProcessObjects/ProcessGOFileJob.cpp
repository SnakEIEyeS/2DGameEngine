#include "ProcessGOFileJob.h"

#include "_Console\ConsolePrint.h"
#include "ControllerStore\ControllerStore.h"
#include "FileHandling\FileHandleFunctions.h"
//#include "Game.h"
#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "GameObject\GameObjectStore.h"
#include "Physics\Physics.h"
#include "Physics\PhysicsInfo.h"
#include "..\Controllers\PaddleController.h"
#include "..\Controllers\PlayerController.h"
#include "Renderer\Renderer.h"
#include "Renderer\RenderInfo.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"

ProcessGOFileJob::ProcessGOFileJob(lua_State * i_pluaState, uint8_t * i_pFileContents) : IJob("ProcessGOFile"), pLuaState(i_pluaState), pFileContents(i_pFileContents)
{
	assert(pLuaState != nullptr);
}

void ProcessGOFileJob::Run()
{
	if (pFileContents)// && sizeFile)
	{
		int result = 0;

		result = lua_getglobal(pLuaState, "GameObject");
		assert(result == LUA_TTABLE);

		//get name
		const char * pName = nullptr;
		lua_pushstring(pLuaState, "name");
		result = lua_gettable(pLuaState, -2);
		if (result == LUA_TSTRING)
		{
			pName = lua_tostring(pLuaState, -1);
			assert(pName != nullptr);
			pName = _strdup(pName);
		}
		else
		{
			DEBUG_PRINT("Didn't find string looking for name.\n");
			pName = _strdup("None");
		}

		lua_pop(pLuaState, 1);

		//get class
		const char * pClass = nullptr;
		lua_pushstring(pLuaState, "class");
		result = lua_gettable(pLuaState, -2);
		if (result == LUA_TSTRING)
		{
			pClass = lua_tostring(pLuaState, -1);
			assert(pClass != nullptr);
			pClass = _strdup(pClass);
		}
		else
		{
			DEBUG_PRINT("Didn't find string looking for class.\n");
			pClass = _strdup("None");
		}

		lua_pop(pLuaState, 1);

		//get controller
		const char * pController = nullptr;
		lua_pushstring(pLuaState, "controller");
		result = lua_gettable(pLuaState, -2);
		if (result == LUA_TSTRING)
		{
			pController = lua_tostring(pLuaState, -1);
			assert(pController != nullptr);
			pController = _strdup(pController);
		}
		else
		{
			DEBUG_PRINT("Didn't find string looking for controller.\n");
			pController = _strdup("None");
		}

		lua_pop(pLuaState, 1);

		//get initial position
		lua_pushstring(pLuaState, "initial_position");
		result = lua_gettable(pLuaState, -2);
		assert(result == LUA_TTABLE);

		float Position[2];
		ReadFloatArray(pLuaState, -1, Position, 2);
		lua_pop(pLuaState, 1);

		//get bounding box
		lua_pushstring(pLuaState, "bounding_box");
		result = lua_gettable(pLuaState, -2);

		float BBCenter[2];
		float BBExtents[2];
		if (result == LUA_TTABLE)
		{
			//get bounding box center
			lua_pushstring(pLuaState, "center");
			result = lua_gettable(pLuaState, -2);

			ReadFloatArray(pLuaState, -1, BBCenter, 2);

			//get bounding box extents
			lua_pushstring(pLuaState, "extents");
			lua_gettable(pLuaState, -3);

			ReadFloatArray(pLuaState, -1, BBExtents, 2);

			//pop center & extents
			lua_pop(pLuaState, 2);
		}

		//pop bounding_box
		lua_pop(pLuaState, 1);

		//TODO update GameObject constructor
		SmartPtr<GameObject> PlayerGO = SmartPtr<GameObject>(new GameObject(Vector2{ Position[0], Position[1] }));
		Engine::GameObjectStore::AddGameObject(PlayerGO);
		PlayerGO->setBB(AABB{ Vector2{ BBCenter[0], BBCenter[1] }, Vector2{ BBExtents[0], BBExtents[1] } });

		//get physics settings
		lua_pushstring(pLuaState, "physics_settings");
		result = lua_gettable(pLuaState, -2);
		float PhysicsSettings[2];
		if (result == LUA_TTABLE)
		{
			ReadFloatArray(pLuaState, -1, PhysicsSettings, 2);
			//TODO check values of mass & drag read into Position - showed them interchanged
			Engine::Physics::AddPhysicsObject(new PhysicsInfo(PlayerGO, PhysicsSettings[0], PhysicsSettings[1]));
		}

		//pop physics_settings
		lua_pop(pLuaState, 1);

		//get render settings
		lua_pushstring(pLuaState, "render_settings");
		result = lua_gettable(pLuaState, -2);

		const char * SpriteFile = nullptr;
		float SpriteExtents[4];
		float SpriteColor[4];
		if (result == LUA_TTABLE)
		{
			//get sprite file
			lua_pushstring(pLuaState, "sprite_file");
			result = lua_gettable(pLuaState, -2);
			SpriteFile = lua_tostring(pLuaState, -1);
			assert(SpriteFile != nullptr);
			SpriteFile = _strdup(SpriteFile);

			//get sprite extents
			lua_pushstring(pLuaState, "sprite_extents");
			result = lua_gettable(pLuaState, -3);
			ReadFloatArray(pLuaState, -1, SpriteExtents, 4);

			//get sprite color
			lua_pushstring(pLuaState, "sprite_color");
			result = lua_gettable(pLuaState, -4);
			ReadFloatArray(pLuaState, -1, SpriteColor, 4);

			//pop sprite_extents & sprite_color
			lua_pop(pLuaState, 3);

			//TODO get the CreateSprite function and complete AddRenderable in ProcessPlayer
			Engine::Rendering::AddRenderable(new Engine::Rendering::RenderInfo(PlayerGO, Engine::File::CreateSprite(SpriteFile)));
		}
		//pop render_settings
		lua_pop(pLuaState, 1);

		//Create & Set Controller
		GameObjectController * PGOController = nullptr;
		if (strcmp(pController, "PlayerController") == 0)
		{
			Engine::ControllerStore::AddController(new PlayerController(PlayerGO));
		}
		else if (strcmp(pController, "PaddleController") == 0)
		{
			PaddleController * PaddleGOController = new PaddleController(PlayerGO);
			Engine::ControllerStore::AddController(PaddleGOController);
			PlayerGO->SetController(PaddleGOController);

			//get controls
			lua_pushstring(pLuaState, "controls");
			result = lua_gettable(pLuaState, -2);

			unsigned int Controls[2];
			if (result == LUA_TTABLE)
			{
				ReadIntArray(pLuaState, -1, Controls, 2);
				PaddleGOController->setPaddleControlKeys(Controls[0], Controls[1]);
			}

			//pop Controls
			lua_pop(pLuaState, 1);

			PaddleGOController = nullptr;
			delete PaddleGOController;
		}

		//pop GameObject
		lua_pop(pLuaState, 1);

		int stack_items = lua_gettop(pLuaState);
		assert(stack_items == 0);

		//delete[] SpriteColor;
		//delete[] SpriteExtents;
		delete SpriteFile;
		//PGOController = nullptr;
		//delete PGOController;
		//delete[] PhysicsSettings;
		//delete[] BBExtents;
		//delete[] BBCenter;
		//delete[] Position;
		delete pController;
		PGOController = nullptr;
		delete PGOController;
		delete pClass;
		delete pName;

	}

	delete pFileContents;

	lua_close(pLuaState);
	//delete pLuaState;
}

#include "ProcessGameObject.h"

#include "..\Controllers\BallController.h"
#include "..\Controllers\BoundsController.h"
#include "ControllerStore\ControllerStore.h"
#include "..\FileHandling\FileHandleFunctions.h"
#include "..\Game.h"
#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "GameObject\GameObjectStore.h"
#include "GLib\GLib.h"
#include "GLib\_Console\ConsolePrint.h"
#include "JobSystem\JobSystem.h"
#include "..\Controllers\KillWallController.h"
#include "LoadGOFileJob.h"
#include "..\Controllers\PaddleController.h"
#include "Physics\Physics.h"
#include "Physics\PhysicsInfo.h"
#include "..\Controllers\PlayerController.h"
#include "Renderer\Renderer.h"
#include "Renderer\RenderInfo.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"
#include "..\Controllers\WinScreenController.h"


void CreateGameObject(const char * i_pFileName, const char * i_JobQueueName)
{
	Engine::JobSystem::RunJob(new LoadGOFileJob(i_pFileName), i_JobQueueName);
}


size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
{
	lua_pushnil(i_pState);

	size_t index = 0;
	while (lua_next(i_pState, i_index - 1) != 0)
	{
		assert(lua_type(i_pState, -1) == LUA_TNUMBER);

		o_pFloats[index++] = float(lua_tonumber(i_pState, -1));
		//pop value
		lua_pop(i_pState, 1);

		if (index >= i_numFloats)
		{
			lua_pop(i_pState, 1);
			break;
		}
	}

	return index;
}

size_t ReadIntArray(lua_State * i_pState, int i_index, unsigned int * o_pInts, size_t i_numInts)
{
	lua_pushnil(i_pState);

	size_t index = 0;
	while (lua_next(i_pState, i_index - 1) != 0)
	{
		assert(lua_type(i_pState, -1) == LUA_TNUMBER);

		o_pInts[index++] = static_cast<unsigned int>(lua_tointeger(i_pState, -1));
		//pop value
		lua_pop(i_pState, 1);

		if (index >= i_numInts)
		{
			lua_pop(i_pState, 1);
			break;
		}
	}

	return index;
}

void ProcessGameObject(const char * pFileName)
{
	//Initialize a lua_State
	lua_State * pLuaState = luaL_newstate();
	assert(pLuaState);

	luaL_openlibs(pLuaState);

	//Read in a file
	size_t sizeFile = 0;
	uint8_t * pFileContents = Engine::File::LoadFile(pFileName, sizeFile);

	if (pFileContents && sizeFile)
	{
		int result = 0;

		//Do the initial buffer parsing
		result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
		assert(result == 0);
		lua_pcall(pLuaState, 0, 0, 0);
		assert(result == 0);

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

		SmartPtr<GameObject> CreatedGO = SmartPtr<GameObject>(new GameObject(Vector2{ Position[0], Position[1] }));
		Engine::GameObjectStore::AddGameObject(CreatedGO);

		//get movable
		lua_pushstring(pLuaState, "movable");
		result = lua_gettable(pLuaState, -2);
		bool bCreatedMovable = false;
		if (result == LUA_TNUMBER)
		{
			unsigned int intMovable = static_cast<unsigned int>(lua_tointeger(pLuaState, -1));

			if (intMovable == 0)
			{
				bCreatedMovable = false;
			}
			else if (intMovable == 1)
			{
				bCreatedMovable = true;
			}

			CreatedGO->setMovable(bCreatedMovable);
		}
		//pop movable
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

			CreatedGO->setBB(AABB{ Vector2{ BBCenter[0], BBCenter[1] }, Vector2{ BBExtents[0], BBExtents[1] } });

			//pop center & extents
			lua_pop(pLuaState, 2);
		}

		//pop bounding_box
		lua_pop(pLuaState, 1);
		

		//get physics settings
		lua_pushstring(pLuaState, "physics_settings");
		result = lua_gettable(pLuaState, -2);
		PhysicsInfo * CreatedPhysics = nullptr;
		float PhysicsSettings[2];
		if (result == LUA_TTABLE)
		{
			ReadFloatArray(pLuaState, -1, PhysicsSettings, 2);
			//TODO check values of mass & drag read into Position - showed them interchanged
			CreatedPhysics = new PhysicsInfo(CreatedGO, PhysicsSettings[0], PhysicsSettings[1]);
			Engine::Physics::AddPhysicsObject(CreatedPhysics);
		}

		//pop physics_settings
		lua_pop(pLuaState, 1);

		//get collision type - killing or not killing
		if (CreatedPhysics)
		{
			lua_pushstring(pLuaState, "collision_killing");
			result = lua_gettable(pLuaState, -2);
			if (result == LUA_TNUMBER)
			{
				unsigned int collision_killing = static_cast<unsigned int>(lua_tointeger(pLuaState, -1));

				if (collision_killing == 0)
				{
					CreatedPhysics->setCollisionKilling(false);
				}
				else if (collision_killing == 1)
				{
					CreatedPhysics->setCollisionKilling(true);
				}

				//pop collision_killing
				lua_pop(pLuaState, 1);
			}
		}
		

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

			Engine::Rendering::AddRenderable(new Engine::Rendering::RenderInfo(CreatedGO, Engine::File::CreateSprite(SpriteFile)));
		}
		//pop render_settings
		lua_pop(pLuaState, 1);

		//Create & Set Controller
		GameObjectController * PGOController = nullptr;
		if (strcmp(pController, "PlayerController") == 0)
		{
			Engine::ControllerStore::AddController(new PlayerController(CreatedGO));
		}

		else if (strcmp(pController, "PaddleController") == 0)
		{
			PaddleController * PaddleGOController = new PaddleController(CreatedGO);
			Engine::ControllerStore::AddController(PaddleGOController);
			CreatedGO->SetController(PaddleGOController);

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

			Game::GetPongInstance().AddPaddle(PaddleGOController);
		}

		else if (strcmp(pController, "BallController") == 0)
		{
			BallController * PongBallController = new BallController(CreatedGO);
			Engine::ControllerStore::AddController(PongBallController);
			CreatedGO->SetController(PongBallController);

			Game::SetPongBallController(PongBallController);
			Engine::Physics::SetPongBallPhysics(CreatedPhysics);
		}

		else if (strcmp(pController, "BoundsController") == 0)
		{
			BoundsController * BndController = new BoundsController(CreatedGO);
			Engine::ControllerStore::AddController(BndController);
			CreatedGO->SetController(BndController);
		}

		else if (strcmp(pController, "KillWallController") == 0)
		{
			KillWallController * KWallController = new KillWallController(CreatedGO);
			Engine::ControllerStore::AddController(KWallController);
			CreatedGO->SetController(KWallController);

			//get is_leftkillwall
			lua_pushstring(pLuaState, "is_leftkillwall");
			result = lua_gettable(pLuaState, -2);
			if (result == LUA_TNUMBER)
			{
				unsigned int leftkillwall = static_cast<unsigned int>(lua_tointeger(pLuaState, -1));

				if (leftkillwall == 0)
				{
					KWallController->setIsLeftKillWall(false);
				}
				else if (leftkillwall == 1)
				{
					KWallController->setIsLeftKillWall(true);
				}

				//pop is_leftkillwall
				lua_pop(pLuaState, 1);
			}
		}

		else if (strcmp(pController, "WinScreenController") == 0)
		{
			WinScreenController * CreatedWinScreen = new WinScreenController(CreatedGO);
			Engine::ControllerStore::AddController(CreatedWinScreen);
			Game::GetPongInstance().setWinScreen(CreatedWinScreen);
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

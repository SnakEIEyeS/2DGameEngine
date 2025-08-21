#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "ControllerStore\ControllerStore.h"
#include "Engine_init.h"
#include "EngineRun.h"
#include "FrameTime\FrameTime.h"
#include "Game.h"
#include "GameObject\GameObjectStore.h"
#include "GLib.h"
#include "InputSystem\InputSystem.h"
#include "JobSystem\JobSystem.h"
#include "Physics\Physics.h"
#include "Pong\Pong.h"
#include "ProfileSystem\ProfileSystem.h"
#include "Renderer\Renderer.h"

/*extern bool Collision_UnitTest();
extern bool SIMDVecMtx_UnitTest();
extern bool SmartPtr_UnitTest();
extern bool WeakPtr_UnitTest();
extern bool Vec4Matrix_UnitTest();*/



int WINAPI wWinMain( HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow )
{

	Engine::StartUp();
	Engine::Profiling::StartUp();
	Engine::JobSystem::StartUp();


	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize( i_hInstance, i_nCmdShow, "Shantanu's Game", -1, Game::ScreenWidth, Game::ScreenHeight );
	
	if( bSuccess )
	{

		Engine::GameObjectStore::StartUp();

		Engine::InputSystem::StartUp();

		Engine::Physics::StartUp();
		Engine::Rendering::StartUp();
		Engine::ControllerStore::StartUp();

		//TODO refactor & add to appropriate function
		Engine::JobSystem::CreateQueue("Default", 2);
		

		Game::StartUp();

		
		/*bool bUnitTester = SmartPtr_UnitTest();
		assert(bUnitTester);

		bUnitTester = WeakPtr_UnitTest();
		assert(bUnitTester);

		bUnitTester = Vec4Matrix_UnitTest();
		assert(bUnitTester);

		bUnitTester = Collision_UnitTest();
		assert(bUnitTester);

		bUnitTester = SIMDVecMtx_UnitTest();
		assert(bUnitTester);*/

		//CreateGameObject("..\\Game\\data\\Kunkka.lua", "Default");
		


		bool bQuit = false;
		
		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
			
			if( !bQuit )
			{
				float dt = Timing::GetLastFrameTime_ms();

				Game::Run(dt);

				Engine::Physics::Update(dt);

				Engine::Rendering::Present();
			}

			bQuit = Game::GetGQuit();
		} while( bQuit == false );

		

		Game::ShutDown();


		Engine::ControllerStore::ShutDown();
		//Engine::Rendering::ReleaseSprites();
		Engine::Rendering::ShutDown();
		Engine::Physics::ShutDown();

		Engine::InputSystem::ShutDown();

		Engine::GameObjectStore::ShutDown();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();

	}

	Engine::JobSystem::Shutdown();
	Engine::Profiling::ShutDown();
	Engine::ShutDown();

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}

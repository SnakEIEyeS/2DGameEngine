#include "LoadGOFileJob.h"

#include "FileHandling\FileHandleFunctions.h"
#include "ProcessGOFileJob.h"

LoadGOFileJob::LoadGOFileJob(const char * i_pFileName) : IJob("LoadGOFile"), pFileName(i_pFileName)
{}

LoadGOFileJob::~LoadGOFileJob()
{
	//delete pFileName;
}

void LoadGOFileJob::Run()
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

		ProcessGOFileJob * pProcessGOFile = new ProcessGOFileJob(pLuaState, pFileContents);
		Engine::JobSystem::RunJob(pProcessGOFile, "Default");
	}

	//delete pFileContents;
}

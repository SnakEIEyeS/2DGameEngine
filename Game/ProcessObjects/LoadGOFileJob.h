#pragma once

#include "JobSystem\IJob.h"

#include "JobSystem\JobSystem.h"
#include "Lua\lua.hpp"
#include "ProcessGOFileJob.h"

class LoadGOFileJob : public Engine::JobSystem::IJob
{
public:
	LoadGOFileJob(const char * i_pFileName);
	~LoadGOFileJob();
	void Run();

private:
	const char * pFileName;
	//size_t * sizeFile;
};

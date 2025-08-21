#include "EngineRun.h"

#include "FrameTime\FrameTime.h"

namespace Engine
{
	bool StartUp()
	{
		Timing::CalcCPUFrequency();

		return true;
	}

	bool Run()
	{
		return true;
	}

	bool ShutDown()
	{
		return true;
	}
}

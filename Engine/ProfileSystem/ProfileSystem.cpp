#include "ProfileSystem.h"

#include "Profiler.h"

namespace Engine
{
	namespace Profiling
	{
		Profiler * g_Profiler = nullptr;

		bool StartUp()
		{
			if (g_Profiler == nullptr)
			{
				g_Profiler = new Profiler();
			}
			return true;
		}

		bool ShutDown()
		{
			delete g_Profiler;
			return true;
		}

		Profiler & Engine::Profiling::GetProfiler()
		{
			if (g_Profiler == nullptr)
			{
				g_Profiler = new Profiler();
			}

			return *g_Profiler;
		}

	}	//namespace Profiling
}	//namespace Engine
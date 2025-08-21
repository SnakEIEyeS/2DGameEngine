#pragma once

#include "Accumulator.h"
#include "ScopedTimer.h"

#define CONCAT_HELPER(left, right) left##right
#define CONCAT(left, right) CONCAT_HELPER(left, right)

#if defined( ENABLE_PROFILING )

#define PROFILE_UNSCOPED(name)				\
	static Engine::Profiling::Accumulator CONCAT(__Accumulator, __LINE__)(name); Engine::Profiling::ScopedTimer CONCAT(__Timer, __LINE__)(CONCAT(__Accumulator, __LINE__));

#define PROFILE_SCOPE_BEGIN(name)	{		\
	static Engine::Profiling::Accumulator CONCAT(__Accumulator, __LINE__)(name); Engine::Profiling::ScopedTimer CONCAT(__Timer, __LINE__)(CONCAT(__Accumulator, __LINE__));

#define PROFILE_SCOPE_END()			}

#else	//ENABLE_PROFILING not defined

#define PROFILE_SCOPE_BEGIN(str)	__noop
#define PROFILE_SCOPE_END			__noop
#define PROFILE_UNSCOPED(str)		__noop

#endif	//ENABLE_PROFILING

namespace Engine
{
	namespace Profiling
	{
		class Profiler;

		extern Engine::Profiling::Profiler * g_Profiler;

		bool StartUp();
		bool ShutDown();

		Profiler & GetProfiler();

	}	//namespace Profiling
}	//namespace Engine

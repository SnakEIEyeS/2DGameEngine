#pragma once

#include "..\FrameTime\FrameTime.h"

namespace Engine
{
	namespace Profiling
	{
		struct Accumulator;

		class ScopedTimer
		{
			Timing::tick m_Start;
			Accumulator * m_pAccumulator;
			const char * m_pScopeName;

		public:
			ScopedTimer(Accumulator & i_MyAccumulator);
			~ScopedTimer();
		};

	}	//namespace Profiling
}	//namespace Engine

#pragma once

#include <map>

namespace Engine
{
	namespace Profiling
	{
		struct Accumulator;
		class Profiler
		{
			std::map<const char *, Accumulator *> m_AllAccumulators;

		public:
			Profiler();
			~Profiler();

			void RegisterAccumulator(const char * i_pName, Accumulator * i_Accumulator);
		};
	}
}

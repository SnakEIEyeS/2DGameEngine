#pragma once

#include <stdint.h>

namespace Engine
{
	namespace Profiling
	{
		struct Accumulator
		{
			double m_Sum;
			uint64_t m_Count;
			float m_Min, m_Max;
			
			Accumulator(const char * i_pName);
			~Accumulator();

			void operator+=(float i_time);

			float average();
		};

	}	//namespace Profiling
}	//namespace Engine

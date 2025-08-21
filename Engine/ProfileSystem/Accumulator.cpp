#include "Accumulator.h"

#include <limits>

#include "..\GLib\_Console\ConsolePrint.h"
#include "Profiler.h"
#include "ProfileSystem.h"

Engine::Profiling::Accumulator::Accumulator(const char * i_pName) : m_Sum(0.f), m_Count(0), m_Min(std::numeric_limits<float>::max()), m_Max(std::numeric_limits<float>::min())
{
	GetProfiler().RegisterAccumulator(i_pName, this);
}

Engine::Profiling::Accumulator::~Accumulator()
{
	DEBUG_PRINT("Avg Time AccDestructor:%f\n\n", average());
}

void Engine::Profiling::Accumulator::operator+=(float i_time)
{
	m_Sum += i_time;
	m_Count++;

	if (i_time > m_Max)
	{
		m_Max = i_time;
	}
	else if (i_time < m_Min)
	{
		m_Min = i_time;
	}
}

float Engine::Profiling::Accumulator::average()
{
	return static_cast<float>(m_Sum / m_Count);
}

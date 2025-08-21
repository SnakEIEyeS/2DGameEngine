#include "ScopedTimer.h"

#include "Accumulator.h"

Engine::Profiling::ScopedTimer::ScopedTimer(Accumulator & i_MyAccumulator) : 
	m_Start(Timing::GetCurrentTickCounter()), m_pAccumulator(&i_MyAccumulator)
{
}

Engine::Profiling::ScopedTimer::~ScopedTimer()
{
	*m_pAccumulator += Timing::GetTimeDiff_ms(m_Start);
}

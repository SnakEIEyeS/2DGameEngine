#include "Profiler.h"

#include <iostream>
#include <fstream>

#include "Accumulator.h"
#include "..\GLib\_Console\ConsolePrint.h"

Engine::Profiling::Profiler::Profiler()
{
}

Engine::Profiling::Profiler::~Profiler()
{
	//TODO clear map of Accumulators
	for (std::map<const char *, Accumulator *>::iterator it = m_AllAccumulators.begin(); it != m_AllAccumulators.end(); it++)
	{
		//DEBUG_PRINT("%s - Avg Time :%f\n", it->first, it->second->average());

		std::ofstream ProfilingResultsFile;
		ProfilingResultsFile.open("..\\ProfilingResults.txt", std::ofstream::out | std::ofstream::app);

		ProfilingResultsFile << "\nProfiled Name: " << it->first << " - \nTotal Time Taken: " << it->second->m_Sum;
		ProfilingResultsFile << "\nNumber of Times Run : " << it->second->m_Count;
		ProfilingResultsFile << "\nMinimum Execution Time : " << it->second->m_Min;
		ProfilingResultsFile << "\nMaximum Execution Time : " << it->second->m_Max;
		ProfilingResultsFile << "\nAverage Execution Time : " << it->second->average() << "\n";

		ProfilingResultsFile.close();
		//delete it->second;
		//delete it->first;
		//m_AllAccumulators.erase(it);
	}

	m_AllAccumulators.clear();
}

void Engine::Profiling::Profiler::RegisterAccumulator(const char * i_pName, Accumulator * i_Accumulator)
{
	m_AllAccumulators.insert(std::pair<const char *, Accumulator *>(i_pName, i_Accumulator));
}

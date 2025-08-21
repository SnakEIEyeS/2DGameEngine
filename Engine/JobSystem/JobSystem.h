#ifndef __JOB_SYSTEM_H
#define __JOB_SYSTEM_H

#include "..\HashedString\HashedString.h"

namespace Engine
{
namespace JobSystem
{
class IJob;

void StartUp();

void CreateQueue( const char * i_pName, unsigned int i_numRunners );
void AddRunner( const HashedString & i_QueueName );

void RunJob( IJob * i_pJob, const HashedString & i_QueueName );
void Shutdown();

} // namespace JobSystem
} // namespace Engine

#endif // __JOB_SYSTEM_H
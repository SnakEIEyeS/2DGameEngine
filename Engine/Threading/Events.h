#ifndef __EVENTS_H
#define __EVENTS_H

#include <Windows.h>

#include "WaitableObject.h"

namespace Engine
{

class ManualResetEvent : public WaitableObject
{
public:
	ManualResetEvent( const char * i_pName, bool i_bInitiallySignaled );
	~ManualResetEvent();

	void Reset();

	bool Wait( wait_t i_WaitMilliseconds );
	void Signal();
};

class AutoResetEvent : public WaitableObject
{
public:
	AutoResetEvent( const char * i_pName, bool i_bInitiallySignaled );
	~AutoResetEvent();

	bool Wait( wait_t i_WaitMilliseconds );
	void Signal();
};

} // namespace Engine

#endif // __EVENTS_H


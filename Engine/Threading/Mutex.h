#ifndef __MUTEX_H
#define __MUTEX_H

#include "WaitableObject.h"

namespace Engine
{

class Mutex : public WaitableObject
{
public:
	Mutex( bool i_bTakeOwnership = false, const char * i_pName = nullptr );
	~Mutex();

	bool TryAcquire();
	void Acquire();
	bool Acquire( wait_t i_WaitMilliseconds );
	void Release();

};

} // namespace Engine

#endif // __MUTEX_H

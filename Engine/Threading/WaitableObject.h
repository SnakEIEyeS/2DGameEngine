#ifndef __WAITABLE_OBJECT_H
#define __WAITABLE_OBJECT_H

#include <Windows.h>

namespace Engine
{

class WaitableObject
{
public:
	typedef DWORD wait_t;

	static const wait_t			WaitInfinite = INFINITE;

	WaitableObject() :
		m_Handle( INVALID_HANDLE_VALUE )
	{}
	virtual ~WaitableObject() {}

	HANDLE GetHandle( void ) { return m_Handle; }

protected:
	HANDLE					m_Handle;

private:
	WaitableObject( const WaitableObject & i_other );
	WaitableObject & operator=( const WaitableObject & i_other );
};

} // namespace Engine

#endif // __WAITABLE_OBJECT_H
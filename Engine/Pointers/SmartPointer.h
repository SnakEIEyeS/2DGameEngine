#pragma once

//#include "GameObject.h"
//#include "WeakPointer.h"

struct Counters
{
	long refCount;
	long weakCount;
};

template<class T>
class WeakPtr;

template<class T>
class SmartPtr
{
	//friend class WeakPtr;

public:
	//Standard Constructors
	SmartPtr() {}

	SmartPtr(T * i_pObject) : m_pObject(i_pObject), m_pCounters(new Counters{1, 0})
	{}

	//Destructor
	~SmartPtr()
	{
		ReleaseCurrentReference();
	}
	
	//Copy Constructor
	SmartPtr(const SmartPtr & i_other) : m_pObject(i_other.m_pObject), m_pCounters(i_other.m_pCounters)
	{
		if (m_pCounters)
		{
			((*m_pCounters).refCount)++;
		}
	}

	template<class U>
	SmartPtr(WeakPtr<U> i_other) : m_pObject(i_other.getObject()), m_pCounters(i_other.getCounters())
	{
		if (m_pCounters)
		{
			((*m_pCounters).refCount)++;
		}
	}

	//Assignment Operator
	SmartPtr & operator=(const SmartPtr & i_other)
	{
		if (m_pObject != i_other.m_pObject)		//Check for self-assignment
		{
			ReleaseCurrentReference();
			AcquireNewReference(i_other);
		}

		return *this;
	}

	//Boolean Operator
	operator bool() const { return m_pObject != nullptr; }

	//Comparison Operators
	bool operator==(const SmartPtr & i_other) const
	{
		if (i_other.m_pObject == nullptr)
		{
			return m_pObject == nullptr;
		}	

		return m_pObject == i_other.m_pObject;
	}

	template<class U>
	bool operator==(const WeakPtr<U> & i_other) const
	{
		return m_pObject == i_other.getObject();
	}

	bool operator!=(const SmartPtr & i_other) const
	{
		if (i_other.m_pObject == nullptr)
		{
			return m_pObject != nullptr;
		}

		return m_pObject != i_other.m_pObject;
	}

	template<class U>
	bool operator!=(const WeakPtr<U> & i_other) const
	{
		return m_pObject != i_other.m_pObject;
	}

	//member access operator
	inline T * operator->() { return m_pObject; }

	//indirection operator
	inline T & operator*()
	{
		assert(m_pObject != nullptr);

		return *m_pObject;
	}

	T * getObject() const { return m_pObject; }
	Counters * getCounters() const { return m_pCounters; }
	
private:

	void ReleaseCurrentReference()
	{
		if (m_pCounters && --((*m_pCounters).refCount) == 0)
		{
			if (m_pObject != nullptr)
			{
				delete m_pObject;
			}

			if ((*m_pCounters).weakCount == 0)
			{
				delete m_pCounters;
			}
		}
	}

	void AcquireNewReference(const SmartPtr & i_other)
	{
		m_pObject = i_other.m_pObject;
		m_pCounters = i_other.m_pCounters;

		if (m_pCounters)
		{
			((*m_pCounters).refCount)++;
		}	
	}

	T * m_pObject;
	Counters * m_pCounters;
};
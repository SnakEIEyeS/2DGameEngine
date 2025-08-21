#pragma once

#include <assert.h>

#include "SmartPointer.h"

template<class T>
class WeakPtr
{
public:
	//Destructor
	~WeakPtr()
	{
		//Stop pointing to current Object
		//m_pObject = nullptr;

		ReleaseCurrentObserver();
	}

	//Copy Constructors
	template<class U>
	WeakPtr(const SmartPtr<U> & i_other) : m_pObject(i_other.getObject()), m_pCounters(i_other.getCounters())
	{
		if (m_pCounters)
		{
			assert(m_pObject != nullptr);
			m_pCounters->weakCount++;
		}
	}

	WeakPtr(const WeakPtr & i_other) : m_pObject(i_other.m_pObject), m_pCounters(i_other.m_pCounters)
	{
		if (m_pCounters)
		{
			assert(m_pObject != nullptr);
			((*m_pCounters).weakCount)++;
		}
	}

	//Assignment Operators
	template<class U>
	WeakPtr & operator=(const SmartPtr<U> & i_other)
	{
		if (m_pObject != i_other.getObject())
		{
			ReleaseCurrentObserver();
			AcquireNewObserver(i_other);
		}

		return *this;
	}
	
	WeakPtr & operator=(const WeakPtr & i_other)
	{
		if (m_pObject != i_other.getObject())
		{
			ReleaseCurrentObserver();
			AcquireNewObserver(i_other);
		}

		return *this;
	}

	//Boolean Operator
	operator bool() const { return m_pObject != nullptr; }
	
	//Comparison Operators
	template<class U>
	bool operator==(const SmartPtr<U> & i_other) const
	{
		return m_pObject == i_other.getObject();
	}

	bool operator==(const WeakPtr & i_other) const
	{
		return m_pObject == i_other.getObject();
	}

	template<class U>
	bool operator!=(const SmartPtr<U> & i_other) const
	{
		return m_pObject != i_other.getObject();
	}

	bool operator!=(const WeakPtr & i_other) const
	{
		return m_pObject != i_other.getObject();
	}

	SmartPtr<T> Acquire() //const
	{
		if (m_pObject)
		{
			//Return SmartPtr to current Object
			return SmartPtr<T>(*this);
		}

		else
		{
			ReleaseCurrentObserver();
			return nullptr;
		}		
	}

	T * getObject() const { return m_pObject; }
	Counters * getCounters() const { return m_pCounters; }

private:
	//Decrement current Observer count, possibly Release the current Counter
	void ReleaseCurrentObserver()
	{
		if (m_pCounters && --((*m_pCounters).weakCount) == 0)	//Decrements Observer count
		{
			if ((*m_pCounters).refCount == 0)	//Check if Counter can be deleted
			{
				delete m_pCounters;
			}
		}
	}

	template<class U>
	void AcquireNewObserver(const SmartPtr<U> & i_other)
	{
		m_pObject = i_other.getObject();
		m_pCounters = i_other.getCounters();

		if (m_pCounters)
		{
			((*m_pCounters).weakCount)++;	//Increment new Observer Count
		}
	}

	void AcquireNewObserver(const WeakPtr & i_other)
	{
		m_pObject = i_other.getObject();
		m_pCounters = i_other.getCounters();

		if (m_pCounters)
		{
			((*m_pCounters).weakCount)++;	//Increment new Observer Count
		}
	}

	T * m_pObject;
	Counters * m_pCounters;
};
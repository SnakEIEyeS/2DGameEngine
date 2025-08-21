#include <assert.h>

#include "_Console\ConsolePrint.h"
#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"
#include "Pointers\WeakPointer.h"

bool WeakPtr_UnitTest()
{
	SmartPtr<GameObject> MasterPlayer = SmartPtr<GameObject>(new GameObject(Vector2{ 0.0f, 0.0f }));
	SmartPtr<GameObject> SecondPlayer = SmartPtr<GameObject>(new GameObject(Vector2{ 100.0f, 100.0f }));
	SmartPtr<GameObject> NullPlayer;

	//Construction via copying SmartPtr
	WeakPtr<GameObject> WeakPlayer(MasterPlayer);
	assert(WeakPlayer);

	WeakPtr<GameObject> ScaredPlayer(WeakPlayer);
	assert(ScaredPlayer);

	//Construction by assignment
	WeakPtr<GameObject> AssignedSmartPlayer = MasterPlayer;
	assert(AssignedSmartPlayer);

	WeakPtr<GameObject> AssignedWeakPlayer = WeakPlayer;
	assert(AssignedWeakPlayer);

	//Boolean operator check
	if (WeakPlayer)
	{
		DEBUG_PRINT("WeakPlayer is not equal to nullptr\n");
	}

	//Equate to SmartPtr
	if (WeakPlayer == MasterPlayer)
	{
		DEBUG_PRINT("WeakPlayer equated to MasterPlayer\n");
	}

	if (WeakPlayer != SecondPlayer)
	{
		DEBUG_PRINT("WeakPlayer did not equate to SecondPlayer\n");
	}

	//Equate to WeakPtr
	if (WeakPlayer == ScaredPlayer)
	{
		DEBUG_PRINT("WeakPlayer equated to SecondPlayer\n");
	}

	ScaredPlayer = SecondPlayer;
	if (WeakPlayer != ScaredPlayer && !(WeakPlayer == ScaredPlayer))
	{
		DEBUG_PRINT("WeakPlayer did not equate to ScaredPlayer\n");
	}

	//Test Acquire() function
	assert(MasterPlayer == WeakPlayer.Acquire());
	assert(SecondPlayer == ScaredPlayer.Acquire());
	assert(WeakPlayer.Acquire() != ScaredPlayer.Acquire());

	DEBUG_PRINT("WeakPtr Unit Test passed!\n\n");

	return true;
}
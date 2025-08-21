#include "_Console\ConsolePrint.h"
//#include <vector>

#include "GameObject\GameObject.h"
#include "GameObject\GameObjectController.h"
#include "Physics\PhysicsInfo.h"
//#include "Renderer\RenderInfo.h"
#include "Pointers\SmartPointer.h"
#include "Math\Vector2.h"

bool SmartPtr_UnitTest()
{
	//std::vector<SmartPtr<GameObject>> GameObjectVector;
	//GameObjectVector.push_back(SmartPtr<GameObject>(new GameObject(Vector2{ 0.0f, 0.0f })));

	SmartPtr<GameObject> MasterPlayer = SmartPtr<GameObject>(new GameObject(Vector2{ 0.0f, 0.0f }));
	SmartPtr<GameObject> SecondPlayer = SmartPtr<GameObject>(new GameObject(Vector2{ 100.0f, 100.0f }));
	SmartPtr<GameObject> NullPlayer;

	PhysicsInfo * GamePlayerPhysics = new PhysicsInfo(MasterPlayer, 135.f, 0.00005f);

	if (NullPlayer == nullptr)
	{
		DEBUG_PRINT("NullPlayer equated to nullptr\n");
	}

	if (!NullPlayer)
	{
		DEBUG_PRINT("!NullPlayer returned true\n");
	}

	if (NullPlayer)
	{
		DEBUG_PRINT("if(NullPlayer) returned true when NullPlayer == nullptr. \nSmartPointer Unit Test failed\n");
		return false;
	}

	NullPlayer = MasterPlayer;

	if (NullPlayer)
	{
		DEBUG_PRINT("if(NullPlayer) returned true after assigning NullPlayer = MasterPlayer\n");
	}

	SecondPlayer = MasterPlayer;

	DEBUG_PRINT("SmartPtr Unit Test passed!\n\n");

	//free allocations
	delete GamePlayerPhysics;

	return true;
}
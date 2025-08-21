#include "BallController.h"

#include "GameObject\GameObject.h"

BallController::BallController(SmartPtr<GameObject> i_pGameObject) : m_pGameObject(i_pGameObject)
{
}

BallController::~BallController()
{
}

WeakPtr<GameObject> BallController::getGameObject()
{
	return m_pGameObject;
}

void BallController::setGameObject(SmartPtr<GameObject> i_pGameObj)
{
	m_pGameObject = i_pGameObj;
}

void BallController::updateGameObject()
{
}

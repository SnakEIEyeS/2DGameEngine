#include "KillWallController.h"

KillWallController::KillWallController(SmartPtr<GameObject> i_pGameObject) : m_pGameObject(i_pGameObject)
{
}

KillWallController::~KillWallController()
{
}

void KillWallController::updateGameObject()
{
}

bool KillWallController::getIsLeftKillWall() const { return m_bIsLeftKillWall; }

void KillWallController::setIsLeftKillWall(bool i_bLeftKillWall) { m_bIsLeftKillWall = i_bLeftKillWall; }

#include "GameObject.h"

#include "GameObjectController.h"
#include "..\Pointers\SmartPointer.h"
#include "..\Pointers\WeakPointer.h"

SmartPtr<GameObject> GameObject::Create(const Vector2 & i_InitialPosition)
{
	return SmartPtr<GameObject>(new GameObject(i_InitialPosition));
}

GameObject::GameObject(Vector2 i_Vector2) : m_Position(i_Vector2), m_ZRotation(0.f), m_MaxVelocity(Vector2{0.0065f, 0.0065f})
{}

GameObject::GameObject() {}

GameObject::~GameObject()
{
	//delete m_Controller;
}

/*void GameObject::SetController(SmartPtr<GameObjectController>& i_NewController) { m_Controller = i_NewController; }

WeakPtr<GameObjectController> GameObject::GetController() const
{
	return m_Controller;
}*/

void GameObject::SetController(GameObjectController * i_NewController) { m_Controller = i_NewController; }

GameObjectController * GameObject::GetController() const { return m_Controller; }

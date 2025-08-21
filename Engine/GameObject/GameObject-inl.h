#include "GameObject.h"
#pragma once

inline Vector2 GameObject::getPos() const { return m_Position; }
inline void GameObject::setPos(Vector2 ipos) { m_Position = ipos; }

inline float GameObject::getZRot() const { return m_ZRotation; }
inline void GameObject::setZRot(float i_ZRot) { m_ZRotation = i_ZRot; }

inline AABB GameObject::getBB() const { return m_BB; }
inline void GameObject::setBB(AABB i_AABB) { m_BB = i_AABB; }

inline Vector2 GameObject::getVelocity() const { return m_Velocity; }
inline void GameObject::setVelocity(Vector2 i_Velocity) { m_Velocity = i_Velocity; }

inline Vector2 GameObject::getMaxVelocity() const { return m_MaxVelocity; }
inline void GameObject::setMaxVelocity(Vector2 i_Velocity) { m_MaxVelocity = i_Velocity; }

inline bool GameObject::getMovable() const { return m_bMovable; }
inline void GameObject::setMovable(bool i_bMovable) { m_bMovable = i_bMovable; }
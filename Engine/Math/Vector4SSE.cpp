#include "Vector4SSE.h"

#include "Vector2.h"
#include "Vector4.hpp"

Engine::Math::Vector4SSE::Vector4SSE(float i_x, float i_y, float i_z, float i_w) : m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w)
{
}

Engine::Math::Vector4SSE::Vector4SSE(const __m128 i_vec) : m_vec(i_vec)
{
}

Engine::Math::Vector4SSE::Vector4SSE(const Vector4 & i_other) : m_x(i_other.x()), m_y(i_other.y()), m_z(i_other.z()), m_w(i_other.w())
{
}

Engine::Math::Vector4SSE::Vector4SSE(const Vector4SSE & i_other) : m_vec(i_other.m_vec)
{
}

Engine::Math::Vector4SSE::Vector4SSE(const Vector2 & i_other, float i_w) : m_x(i_other.x), m_y(i_other.y), m_z(0.f), m_w(i_w)
{
}

bool Engine::Math::Vector4SSE::operator==(Vector4SSE & i_other)
{
	__m128 result = _mm_cmpeq_ps(m_vec, i_other.m_vec);
	if (_mm_movemask_ps(result) != 15)
		return false;

	return true;
}

bool Engine::Math::Vector4SSE::operator!=(Vector4SSE & i_other)
{
	__m128 result = _mm_cmpeq_ps(m_vec, i_other.m_vec);
	if (_mm_movemask_ps(result) != 15)
		return true;

	return false;
}

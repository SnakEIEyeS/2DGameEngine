#pragma once

//#include "Matrix.h"
#include "Vector4.hpp"

Engine::Math::Vector4 Engine::Math::operator*(const Engine::Math::Vector4 & i_vec, const Engine::Math::Matrix & i_mtx)
{
	float Vec4X = i_vec.x();
	float Vec4Y = i_vec.y();
	float Vec4Z = i_vec.z();
	float Vec4W = i_vec.w();

	return Vector4(
		Vec4X * i_mtx.m_11 + Vec4Y * i_mtx.m_21 + Vec4Z * i_mtx.m_31 + Vec4W * i_mtx.m_41,	//x
		Vec4X * i_mtx.m_12 + Vec4Y * i_mtx.m_22 + Vec4Z * i_mtx.m_32 + Vec4W * i_mtx.m_42,	//y
		Vec4X * i_mtx.m_13 + Vec4Y * i_mtx.m_23 + Vec4Z * i_mtx.m_33 + Vec4W * i_mtx.m_43,	//z
		Vec4X * i_mtx.m_14 + Vec4Y * i_mtx.m_24 + Vec4Z * i_mtx.m_34 + Vec4W * i_mtx.m_44	//w
	);
}
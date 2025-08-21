#pragma once

Engine::Math::Vector4SSE Engine::Math::operator*(const Engine::Math::Vector4SSE & i_Vector, const Engine::Math::MatrixSSE & i_mtx)
{
	MatrixSSE MtxTranspose = i_mtx.GetTranspose();

	return Vector4SSE( dot(i_Vector, MtxTranspose.m_vec[0]), dot(i_Vector, MtxTranspose.m_vec[1]), dot(i_Vector, MtxTranspose.m_vec[2]), dot(i_Vector, MtxTranspose.m_vec[3]) );
}

Engine::Math::MatrixSSE Engine::Math::operator*(const float & i_float, const Engine::Math::MatrixSSE & i_mtx)
{
	__m128 multiplier = { i_float, i_float, i_float, i_float };

	MatrixSSE MtxToReturn;

	MtxToReturn.m_vec[0] = _mm_mul_ps(i_mtx.m_vec[0], multiplier);
	MtxToReturn.m_vec[1] = _mm_mul_ps(i_mtx.m_vec[1], multiplier);
	MtxToReturn.m_vec[2] = _mm_mul_ps(i_mtx.m_vec[2], multiplier);
	MtxToReturn.m_vec[3] = _mm_mul_ps(i_mtx.m_vec[3], multiplier);

	return MtxToReturn;
}

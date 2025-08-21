#pragma once

#include <intrin.h>

#include "Vector4.hpp"
#include "Vector4SSE.h"

struct Vector2;

namespace Engine
{
	namespace Math
	{
		struct eleArray;
		union MatrixSSE;
		//create an alias for cache alignment
		typedef __declspec(align(64)) MatrixSSE FastMatrixSSE;

		union MatrixSSE
		{
			friend Vector4SSE operator*(const Vector4SSE & i_vec, const MatrixSSE & i_mtx);
			friend MatrixSSE operator*(const float & i_float, const MatrixSSE & i_mtx);
		public:
			MatrixSSE();

			MatrixSSE(
				float i_11, float i_12, float i_13, float i_14,
				float i_21, float i_22, float i_23, float i_24,
				float i_31, float i_32, float i_33, float i_34,
				float i_41, float i_42, float i_43, float i_44);

			MatrixSSE(Vector4 i_vecArray[4]);
			MatrixSSE(Vector4 i_vec1, Vector4 i_vec2, Vector4 i_vec3, Vector4 i_vec4);
//			MatrixSSE(__m128 i_vec1, __m128 i_vec2, __m128 i_vec3, __m128 i_vec4);

			//Copy constructor & assigment operator
			MatrixSSE(const MatrixSSE & i_other);
			MatrixSSE & operator=(const MatrixSSE & i_other);

			//Useful matrix creators
			static MatrixSSE CreateIdentity(void);
			static MatrixSSE CreateXRotation(float i_RotationRadians);
			static MatrixSSE CreateYRotation(float i_RotationRadians);
			static MatrixSSE CreateZRotation(float i_RotationRadians);

			static MatrixSSE CreateTranslation(Vector2 i_trans);
			static MatrixSSE CreateTranslation(float i_transX, float i_transY);
			static MatrixSSE CreateScale(float i_scaleX, float i_scaleY);

			//Invert this instance
			void Invert(void);
			//Return a matrix that is the inverse of this instance but don't modify this instance
			MatrixSSE GetInverse(void);

			//Transpose this instance
			void Transpose(void);
			//return a matrix that is the transpose of this instance but don't modify this instance
			MatrixSSE GetTranspose(void) const;

			//Multiply Matrix * Matrix
			//return *this * i_other
			MatrixSSE operator*(const MatrixSSE & i_other) const;
			//MatrixSSE operator*(float i_float) const;

			//Multiply Vector by Matrix
			//return v * M
			Vector4SSE MultiplyLeft(const Vector4SSE & i_Vector) const;

			bool operator==(const MatrixSSE & i_other) const;
			bool operator!=(const MatrixSSE & i_other) const;

			MatrixSSE operator+(const MatrixSSE & i_other) const;
			MatrixSSE operator-(const MatrixSSE & i_other) const;

			Vector4SSE & operator[](int index);

			static const FastMatrixSSE Identity;

		private:
			float Determinant(eleArray ele);

			Vector4 m_Vec4[4];
			Vector4SSE m_Vec4SSE[4];
			__m128 m_vec[4];
		};

		inline Vector4SSE operator*(const Vector4SSE & i_vec, const MatrixSSE & i_mtx);
		inline MatrixSSE operator*(const float & i_float, const MatrixSSE & i_mtx);

		struct eleArray
		{
			float m_11, m_12, m_13, m_14,
				m_21, m_22, m_23, m_24,
				m_31, m_32, m_33, m_34,
				m_41, m_42, m_43, m_44;

			eleArray(Vector4 i_vec1, Vector4 i_vec2, Vector4 i_vec3, Vector4 i_vec4) :
				m_11(i_vec1.x()), m_12(i_vec1.y()), m_13(i_vec1.z()), m_14(i_vec1.w()),
				m_21(i_vec2.x()), m_22(i_vec2.y()), m_23(i_vec2.z()), m_24(i_vec2.w()),
				m_31(i_vec3.x()), m_32(i_vec3.y()), m_33(i_vec3.z()), m_34(i_vec3.w()),
				m_41(i_vec4.x()), m_42(i_vec4.y()), m_43(i_vec4.z()), m_44(i_vec4.w())
			{}
		};

	}	//namespace Math
}	//namespace Engine

#include "MatrixSSE-inl.h"

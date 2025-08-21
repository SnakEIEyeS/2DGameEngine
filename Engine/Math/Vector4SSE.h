#pragma once

#include <intrin.h>

struct Vector2;

namespace Engine
{
	namespace Math
	{
		class Vector4;
		union Vector4SSE;
			typedef __declspec(align(64)) Vector4SSE FastVectorSSE;
		union Vector4SSE
		{
			friend float dot(const Vector4SSE & i_lhs, const Vector4SSE & i_rhs);
		public:
			Vector4SSE(float i_x, float i_y, float i_z, float i_w);

			Vector4SSE(const __m128 i_vec);

			Vector4SSE(const Vector4 & i_other);
			Vector4SSE(const Vector4SSE & i_other);
			Vector4SSE(const Vector2 & i_other, float i_w);

			inline float x();
			inline float y();
			inline float z();
			inline float w();

			bool operator==(Vector4SSE & i_other);
			bool operator!=(Vector4SSE & i_other);

		private:
			struct {
				float m_x, m_y, m_z, m_w;
			};
			__m128 m_vec;
		};

		inline float dot(const Vector4SSE & i_lhs, const Vector4SSE & i_rhs)
		{
			return _mm_cvtss_f32(_mm_dp_ps(i_lhs.m_vec, i_rhs.m_vec, 0xF1));
		}

		inline float Vector4SSE::x() { return m_x; }

		inline float Vector4SSE::y() { return m_y; }

		inline float Vector4SSE::z() { return m_z; }

		inline float Vector4SSE::w() { return m_w; }

	}	//namespace Math
}	//namespace Engine

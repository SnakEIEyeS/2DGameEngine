#pragma once

#include "FloatOperations.h"
#include "Vector2.h"

namespace Engine
{
	namespace Math
	{
		class Vector4
		{
		public:
			Vector4()
			{}

			//Standard constructor
			Vector4(float i_x, float i_y, float i_z, float i_w) : m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w)
			{}

			//Copy constructor
			inline Vector4(const Vector4 & i_other) : m_x(i_other.x()), m_y(i_other.y()), m_z(i_other.z()), m_w(i_other.w())
			{}

			//Copy constructor from Vector2
			inline Vector4(const Vector2 & i_other, float i_w) : m_x(i_other.getx()), m_y(i_other.gety()), m_z(0.0f), m_w(i_w)
			{}

			//Assignment operator
			inline const Vector4 & operator=(const Vector4 & i_rhs)
			{
				m_x = i_rhs.x();
				m_y = i_rhs.y();
				m_z = i_rhs.z();
				m_w = i_rhs.w();

				return *this;
			}

			//Element accessors
			// - get individual element
			float x() const { return m_x; }
			float y() const { return m_y; }
			float z() const { return m_z; }
			float w() const { return m_w; }

			// - set individual element
			inline void x(float i_x) { m_x = i_x; }
			inline void y(float i_y) { m_y = i_y; }
			inline void z(float i_z) { m_z = i_z; }
			inline void w(float i_w) { m_w = i_w; }

			const Vector4 & operator+=(const Vector4 & i_rhs)
			{
				m_x += i_rhs.x();
				m_y += i_rhs.y();
				m_z += i_rhs.z();
				m_w += i_rhs.w();
			}

			const Vector4 & operator-=(const Vector4 & i_rhs)
			{
				m_x -= i_rhs.x();
				m_y -= i_rhs.y();
				m_z -= i_rhs.z();
				m_w -= i_rhs.w();
			}

			const Vector4 & operator*=(float i_val)
			{
				m_x *= i_val;
				m_y *= i_val;
				m_z *= i_val;
				m_w *= i_val;
			}

			const Vector4 & operator/=(float i_val)
			{
				m_x = (float)m_x / i_val;
				m_y = (float)m_y / i_val;
				m_z = (float)m_z / i_val;
				m_w = (float)m_w / i_val;
			}

			//negate
			const Vector4 & operator-(void)
			{
				m_x = -m_x;
				m_y = -m_y;
				m_z = -m_z;
				m_w = -m_w;
			}

		private:
			float m_x, m_y, m_z, m_w;
		};

		inline Vector4 operator+(const Vector4 & i_lhs, const Vector4 & i_rhs)
		{
			return Vector4(i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y(), i_lhs.z() + i_rhs.z(), i_lhs.w() + i_rhs.w());
		}

		inline Vector4 operator-(const Vector4 & i_lhs, const Vector4 & i_rhs)
		{
			return Vector4(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y(), i_lhs.z() - i_rhs.z(), i_lhs.w() - i_rhs.w());
		}

		inline Vector4 operator*(const Vector4 & i_lhs, float i_rhs)
		{
			return Vector4(i_lhs.x() * i_rhs, i_lhs.y() * i_rhs, i_lhs.z() * i_rhs, i_lhs.w() * i_rhs);
		}

		inline Vector4 operator/(const Vector4 & i_lhs, float i_rhs)
		{
			return Vector4(i_lhs.x() / i_rhs, i_lhs.y() / i_rhs, i_lhs.z() / i_rhs, i_lhs.w() / i_rhs);
		}

		inline bool operator==(const Vector4 & i_lhs, const Vector4 & i_rhs)
		{
			return (AreAboutEqual(i_lhs.x(), i_rhs.x()) && AreAboutEqual(i_lhs.y(), i_rhs.y()) && AreAboutEqual(i_lhs.z(), i_rhs.z()) && AreAboutEqual(i_lhs.w(), i_rhs.w()));
		}

		inline bool operator!=(const Vector4 & i_lhs, const Vector4 & i_rhs)
		{
			return !(AreAboutEqual(i_lhs.x(), i_rhs.x()) && AreAboutEqual(i_lhs.y(), i_rhs.y()) && AreAboutEqual(i_lhs.z(), i_rhs.z()) && AreAboutEqual(i_lhs.w(), i_rhs.w()));
		}

		inline float dot(const Vector4 & i_lhs, const Vector4 & i_rhs)
		{
			return (i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y() + i_lhs.z() * i_rhs.z() + i_lhs.w() * i_rhs.w());
		}

	}	//namespace Math
}	//namespace Engine

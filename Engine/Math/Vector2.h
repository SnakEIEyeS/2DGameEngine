#pragma once

#include <assert.h>

#include "FloatOperations.h"

struct Vector2
{
	inline Vector2() : x(0.f), y(0.f)
	{}

	inline Vector2(float i_x, float i_y)
	{
		x = i_x;
		y = i_y;
	}

	float getx() const
	{
		return x;
	}

	float gety() const
	{
		return y;
	}

	void setx(float i_x)
	{
		x = i_x;
	}

	void sety(float i_y)
	{
		y = i_y;
	}

	float x;
	float y;
};


inline Vector2 operator+(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	Vector2 fi_lhs = i_lhs;
	Vector2 fi_rhs = i_rhs;
	return Vector2(fi_lhs.getx() + fi_rhs.getx(), fi_lhs.gety() + fi_rhs.gety());
}

inline Vector2 operator-(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	Vector2 fi_lhs = i_lhs;
	Vector2 fi_rhs = i_rhs;
	return Vector2(fi_lhs.getx() - fi_rhs.getx(), fi_lhs.gety() - fi_rhs.gety());
}

inline Vector2 operator*(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	Vector2 fi_lhs = i_lhs;
	Vector2 fi_rhs = i_rhs;
	return Vector2(fi_lhs.getx() * fi_rhs.getx(), fi_lhs.gety() * fi_rhs.gety());
}

inline Vector2 operator*(const Vector2 & i_lhs, const float & i_float)
{
	return Vector2(i_lhs.getx() * i_float, i_lhs.gety() * i_float);
}
inline Vector2 operator*(const float & i_float, const Vector2 & i_lhs)
{
	return Vector2(i_lhs.getx() * i_float, i_lhs.gety() * i_float);
}

inline void operator+=(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	Vector2 fi_lhs = i_lhs;
	Vector2 fi_rhs = i_rhs;
	fi_lhs.setx(fi_lhs.getx() + fi_rhs.getx());
	fi_lhs.sety(fi_lhs.gety() + fi_rhs.gety());
}

inline void operator-=(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	Vector2 fi_lhs = i_lhs;
	Vector2 fi_rhs = i_rhs;
	fi_lhs.setx(fi_lhs.getx() - fi_rhs.getx());
	fi_lhs.sety(fi_lhs.gety() - fi_rhs.gety());
}

inline bool operator==(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	return (AreAboutEqual(i_lhs.x, i_rhs.x) && AreAboutEqual(i_lhs.y, i_rhs.y));
}

inline bool operator!=(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	return !(AreAboutEqual(i_lhs.x, i_rhs.x) && AreAboutEqual(i_lhs.y, i_rhs.y));
}

inline float dot(const Vector2 & i_lhs, const Vector2 & i_rhs)
{
	return (i_lhs.getx() * i_rhs.getx() + i_lhs.gety() * i_rhs.gety());
}
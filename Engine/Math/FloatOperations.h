#pragma once

#include <Math.h>

inline bool IsNaN(float i_value)
{
	volatile float val = i_value;

	//this will return true if val == NaN
	return val != val;
}

inline bool IsNaNOrIsInfinity(float i_value)
{
	volatile float val = i_value;

	return (val * 0) != 0;
}

inline bool AreAboutEqual(float i_lhs, float i_rhs, float epsilon = .0001f)
{
	//const float epsilon = .0001f;

	return fabs(i_rhs - i_lhs) < epsilon;
}

inline bool AreEqual_Rel(float i_lhs, float i_rhs, float i_maxDiff)
{
	//Don't waste time if they happen to be equal (bit-wise)
	if (i_lhs == i_rhs)
		return true;

	//Calculate a relative difference between the two numbers
	float relDiff;

	if (fabs(i_rhs) > fabs(i_lhs))
		relDiff = static_cast<float>(fabs((i_lhs - i_rhs) / i_rhs));
	else
		relDiff = static_cast<float>(fabs((i_lhs - i_rhs) / i_lhs));

	//Is it less than the maximum tolerable difference
	return relDiff <= i_maxDiff;
}

inline bool IsZero(float i_value)
{
	return AreAboutEqual(i_value, .000000001f);
}

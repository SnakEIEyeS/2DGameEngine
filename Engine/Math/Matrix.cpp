#include "Matrix.h"

#include <math.h>

#include "FloatOperations.h"

const Engine::Math::FastMatrix Engine::Math::Matrix::Identity = Matrix(
	1,	0,	0,	0,
	0,	1,	0,	0,
	0,	0,	1,	0,
	0,	0,	0,	1	);

Engine::Math::Matrix::Matrix() {}

Engine::Math::Matrix::Matrix(
	float i_11, float i_12, float i_13, float i_14, 
	float i_21, float i_22, float i_23, float i_24, 
	float i_31, float i_32, float i_33, float i_34, 
	float i_41, float i_42, float i_43, float i_44) :
	m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
	m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
	m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
	m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
{
}

Engine::Math::Matrix::Matrix(const Engine::Math::Matrix & i_other) :
	m_11(i_other.m_11), m_12(i_other.m_12), m_13(i_other.m_13), m_14(i_other.m_14),
	m_21(i_other.m_21), m_22(i_other.m_22), m_23(i_other.m_23), m_24(i_other.m_24),
	m_31(i_other.m_31), m_32(i_other.m_32), m_33(i_other.m_33), m_34(i_other.m_34),
	m_41(i_other.m_41), m_42(i_other.m_42), m_43(i_other.m_43), m_44(i_other.m_44)
{
}

Engine::Math::Matrix & Engine::Math::Matrix::operator=(const Engine::Math::Matrix & i_other)
{
	m_11 = i_other.m_11; m_12 = i_other.m_12; m_13 = i_other.m_13; m_14 = i_other.m_14;
	m_21 = i_other.m_21; m_22 = i_other.m_22; m_23 = i_other.m_23; m_24 = i_other.m_24;
	m_31 = i_other.m_31; m_32 = i_other.m_32; m_33 = i_other.m_33; m_34 = i_other.m_34;
	m_41 = i_other.m_41; m_42 = i_other.m_42; m_43 = i_other.m_43; m_44 = i_other.m_44;

	return *this;
}

Engine::Math::Matrix Engine::Math::Matrix::CreateIdentity(void)
{
	return Matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Engine::Math::Matrix Engine::Math::Matrix::CreateXRotation(float i_RotationRadians)
{
	return Matrix(
		1,								0,							0,			0,
		0,	(float)cos(i_RotationRadians), (float)sin(i_RotationRadians),		0,
		0, (float)-sin(i_RotationRadians), (float)cos(i_RotationRadians),		0,
		0,								0,							0,			1
	);
}

Engine::Math::Matrix Engine::Math::Matrix::CreateYRotation(float i_RotationRadians)
{
	return Matrix(
		(float)cos(i_RotationRadians),		0, (float)-sin(i_RotationRadians),	0,
		0,									1,							0,		0,
		(float)sin(i_RotationRadians),		0,	(float)cos(i_RotationRadians),		0,
		0,									0,							0,		1
	);
}

Engine::Math::Matrix Engine::Math::Matrix::CreateZRotation(float i_RotationRadians)
{
	return Matrix(
		(float)cos(i_RotationRadians), (float)sin(i_RotationRadians),		0,	0,
		(float)-sin(i_RotationRadians), (float)cos(i_RotationRadians),		0,	0,
		0,														0,			1,	0,
		0,														0,			0,	1
	);
}

Engine::Math::Matrix Engine::Math::Matrix::CreateTranslation(Vector2 i_trans)
{
	return Matrix(
		1,					0,	0,	0,
		0,					1,	0,	0,
		0,					0,	1,	0,
		i_trans.x,	i_trans.y,	0,	1
	);
}

Engine::Math::Matrix Engine::Math::Matrix::CreateTranslation(float i_transX, float i_transY)
{
	return Matrix(
		1,					0,	0,	0,
		0,					1,	0,	0,
		0,					0,	1,	0,
		i_transX,	 i_transY,	0,	1
	);
}

Engine::Math::Matrix Engine::Math::Matrix::CreateScale(float i_scaleX, float i_scaleY)
{
	return Matrix(
		i_scaleX,	0,			0,	0,
		0,			i_scaleY,	0,	0,
		0,			0,			1,	0,
		0,			0,			0,	1
	);
}

void Engine::Math::Matrix::Invert(void)
{
	float scale = 1 / Determinant();

	*this = Matrix(
		(m_23*m_34*m_42 - m_24*m_33*m_42 + m_24*m_32*m_43 - m_22*m_34*m_43 - m_23*m_32*m_44 + m_22*m_33*m_44) * scale,
		(m_14*m_33*m_42 - m_13*m_34*m_42 - m_14*m_32*m_43 + m_12*m_34*m_43 + m_13*m_32*m_44 - m_12*m_33*m_44) * scale,
		(m_13*m_24*m_42 - m_14*m_23*m_42 + m_14*m_22*m_43 - m_12*m_24*m_43 - m_13*m_22*m_44 + m_12*m_23*m_44) * scale,
		(m_14*m_23*m_32 - m_13*m_24*m_32 - m_14*m_22*m_33 + m_12*m_24*m_33 + m_13*m_22*m_34 - m_12*m_23*m_34) * scale,
		(m_24*m_33*m_41 - m_23*m_34*m_41 - m_24*m_31*m_43 + m_21*m_34*m_43 + m_23*m_31*m_44 - m_21*m_33*m_44) * scale,
		(m_13*m_34*m_41 - m_14*m_33*m_41 + m_14*m_31*m_43 - m_11*m_34*m_43 - m_13*m_31*m_44 + m_11*m_33*m_44) * scale,
		(m_14*m_23*m_41 - m_13*m_24*m_41 - m_14*m_21*m_43 + m_11*m_24*m_43 + m_13*m_21*m_44 - m_11*m_23*m_44) * scale,
		(m_13*m_24*m_31 - m_14*m_23*m_31 + m_14*m_21*m_33 - m_11*m_24*m_33 - m_13*m_21*m_34 + m_11*m_23*m_34) * scale,
		(m_22*m_34*m_41 - m_24*m_32*m_41 + m_24*m_31*m_42 - m_21*m_34*m_42 - m_22*m_31*m_44 + m_21*m_32*m_44) * scale,
		(m_14*m_32*m_41 - m_12*m_34*m_41 - m_14*m_31*m_42 + m_11*m_34*m_42 + m_12*m_31*m_44 - m_11*m_32*m_44) * scale,
		(m_12*m_24*m_41 - m_14*m_22*m_41 + m_14*m_21*m_42 - m_11*m_24*m_42 - m_12*m_21*m_44 + m_11*m_22*m_44) * scale,
		(m_14*m_22*m_31 - m_12*m_24*m_31 - m_14*m_21*m_32 + m_11*m_24*m_32 + m_12*m_21*m_34 - m_11*m_22*m_34) * scale,
		(m_23*m_32*m_41 - m_22*m_33*m_41 - m_23*m_31*m_42 + m_21*m_33*m_42 + m_22*m_31*m_43 - m_21*m_32*m_43) * scale,
		(m_12*m_33*m_41 - m_13*m_32*m_41 + m_13*m_31*m_42 - m_11*m_33*m_42 - m_12*m_31*m_43 + m_11*m_32*m_43) * scale,
		(m_13*m_22*m_41 - m_12*m_23*m_41 - m_13*m_21*m_42 + m_11*m_23*m_42 + m_12*m_21*m_43 - m_11*m_22*m_43) * scale,
		(m_12*m_23*m_31 - m_13*m_22*m_31 + m_13*m_21*m_32 - m_11*m_23*m_32 - m_12*m_21*m_33 + m_11*m_22*m_33) * scale
	);
}

Engine::Math::Matrix Engine::Math::Matrix::GetInverse(void) 
{
	float scale = 1 / Determinant();

	return Matrix(
	(m_23*m_34*m_42 - m_24*m_33*m_42 + m_24*m_32*m_43 - m_22*m_34*m_43 - m_23*m_32*m_44 + m_22*m_33*m_44) * scale,
	(m_14*m_33*m_42 - m_13*m_34*m_42 - m_14*m_32*m_43 + m_12*m_34*m_43 + m_13*m_32*m_44 - m_12*m_33*m_44) * scale,
	(m_13*m_24*m_42 - m_14*m_23*m_42 + m_14*m_22*m_43 - m_12*m_24*m_43 - m_13*m_22*m_44 + m_12*m_23*m_44) * scale,
	(m_14*m_23*m_32 - m_13*m_24*m_32 - m_14*m_22*m_33 + m_12*m_24*m_33 + m_13*m_22*m_34 - m_12*m_23*m_34) * scale,
	(m_24*m_33*m_41 - m_23*m_34*m_41 - m_24*m_31*m_43 + m_21*m_34*m_43 + m_23*m_31*m_44 - m_21*m_33*m_44) * scale,
	(m_13*m_34*m_41 - m_14*m_33*m_41 + m_14*m_31*m_43 - m_11*m_34*m_43 - m_13*m_31*m_44 + m_11*m_33*m_44) * scale,
	(m_14*m_23*m_41 - m_13*m_24*m_41 - m_14*m_21*m_43 + m_11*m_24*m_43 + m_13*m_21*m_44 - m_11*m_23*m_44) * scale,
	(m_13*m_24*m_31 - m_14*m_23*m_31 + m_14*m_21*m_33 - m_11*m_24*m_33 - m_13*m_21*m_34 + m_11*m_23*m_34) * scale,
	(m_22*m_34*m_41 - m_24*m_32*m_41 + m_24*m_31*m_42 - m_21*m_34*m_42 - m_22*m_31*m_44 + m_21*m_32*m_44) * scale,
	(m_14*m_32*m_41 - m_12*m_34*m_41 - m_14*m_31*m_42 + m_11*m_34*m_42 + m_12*m_31*m_44 - m_11*m_32*m_44) * scale,
	(m_12*m_24*m_41 - m_14*m_22*m_41 + m_14*m_21*m_42 - m_11*m_24*m_42 - m_12*m_21*m_44 + m_11*m_22*m_44) * scale,
	(m_14*m_22*m_31 - m_12*m_24*m_31 - m_14*m_21*m_32 + m_11*m_24*m_32 + m_12*m_21*m_34 - m_11*m_22*m_34) * scale,
	(m_23*m_32*m_41 - m_22*m_33*m_41 - m_23*m_31*m_42 + m_21*m_33*m_42 + m_22*m_31*m_43 - m_21*m_32*m_43) * scale,
	(m_12*m_33*m_41 - m_13*m_32*m_41 + m_13*m_31*m_42 - m_11*m_33*m_42 - m_12*m_31*m_43 + m_11*m_32*m_43) * scale,
	(m_13*m_22*m_41 - m_12*m_23*m_41 - m_13*m_21*m_42 + m_11*m_23*m_42 + m_12*m_21*m_43 - m_11*m_22*m_43) * scale,
	(m_12*m_23*m_31 - m_13*m_22*m_31 + m_13*m_21*m_32 - m_11*m_23*m_32 - m_12*m_21*m_33 + m_11*m_22*m_33) * scale
	);
}

void Engine::Math::Matrix::Transpose(void)
{
	*this = Matrix(
		m_11, m_21, m_31, m_41,
		m_12, m_22, m_32, m_42,
		m_13, m_23, m_33, m_43,
		m_14, m_24, m_34, m_44
	);
}

Engine::Math::Matrix Engine::Math::Matrix::GetTranspose(void) const
{
	return Matrix(
		m_11, m_21, m_31, m_41,
		m_12, m_22, m_32, m_42,
		m_13, m_23, m_33, m_43,
		m_14, m_24, m_34, m_44
	);
}

Engine::Math::Matrix Engine::Math::Matrix::operator*(const Matrix & i_other) const
{
	return Matrix(
		m_11 * i_other.m_11		+	m_12 * i_other.m_21		+	m_13 * i_other.m_31		+	m_14 * i_other.m_41,	//m_11
		m_11 * i_other.m_12		+	m_12 * i_other.m_22		+	m_13 * i_other.m_32		+	m_14 * i_other.m_42,	//m_12
		m_11 * i_other.m_13		+	m_12 * i_other.m_23		+	m_13 * i_other.m_33		+	m_14 * i_other.m_43,	//m_13
		m_11 * i_other.m_14		+	m_12 * i_other.m_24		+	m_13 * i_other.m_34		+	m_14 * i_other.m_44,	//m_14

		m_21 * i_other.m_11		+	m_22 * i_other.m_21		+	m_23 * i_other.m_31		+	m_24 * i_other.m_41,	//m_21
		m_21 * i_other.m_12		+	m_22 * i_other.m_22		+	m_23 * i_other.m_32		+	m_24 * i_other.m_42,	//m_22
		m_21 * i_other.m_13		+	m_22 * i_other.m_23		+	m_23 * i_other.m_33		+	m_24 * i_other.m_43,	//m_23
		m_21 * i_other.m_14		+	m_22 * i_other.m_24		+	m_23 * i_other.m_34		+	m_24 * i_other.m_44,	//m_24

		m_31 * i_other.m_11		+	m_32 * i_other.m_21		+	m_33 * i_other.m_31		+	m_34 * i_other.m_41,	//m_31
		m_31 * i_other.m_12		+	m_32 * i_other.m_22		+	m_33 * i_other.m_32		+	m_34 * i_other.m_42,	//m_32
		m_31 * i_other.m_13		+	m_32 * i_other.m_23		+	m_33 * i_other.m_33		+	m_34 * i_other.m_43,	//m_33
		m_31 * i_other.m_14		+	m_32 * i_other.m_24		+	m_33 * i_other.m_34		+	m_34 * i_other.m_44,	//m_34

		m_41 * i_other.m_11		+	m_42 * i_other.m_21		+	m_43 * i_other.m_31		+	m_44 * i_other.m_41,	//m_41
		m_41 * i_other.m_12		+	m_42 * i_other.m_22		+	m_43 * i_other.m_32		+	m_44 * i_other.m_42,	//m_42
		m_41 * i_other.m_13		+	m_42 * i_other.m_23		+	m_43 * i_other.m_33		+	m_44 * i_other.m_43,	//m_43
		m_41 * i_other.m_14		+	m_42 * i_other.m_24		+	m_43 * i_other.m_34		+	m_44 * i_other.m_44		//m_44
	);
}

Engine::Math::Vector4 Engine::Math::Matrix::MultiplyLeft(const Vector4 & i_Vector) const
{
	float Vec4X = i_Vector.x();
	float Vec4Y = i_Vector.y();
	float Vec4Z = i_Vector.z();
	float Vec4W = i_Vector.w();

	return Vector4(
		Vec4X * m_11	+	Vec4Y * m_21	+	Vec4Z * m_31	+	Vec4W * m_41,	//x
		Vec4X * m_12	+	Vec4Y * m_22	+	Vec4Z * m_32	+	Vec4W * m_42,	//y
		Vec4X * m_13	+	Vec4Y * m_23	+	Vec4Z * m_33	+	Vec4W * m_43,	//z
		Vec4X * m_14	+	Vec4Y * m_24	+	Vec4Z * m_34	+	Vec4W * m_44		//w
	);
}

bool Engine::Math::Matrix::operator==(const Matrix & i_other) const
{
	return (AreAboutEqual(m_11, i_other.m_11) && AreAboutEqual(m_12, i_other.m_12) && AreAboutEqual(m_13, i_other.m_13) && AreAboutEqual(m_14, i_other.m_14) &&
		AreAboutEqual(m_21, i_other.m_21) && AreAboutEqual(m_22, i_other.m_22) && AreAboutEqual(m_23, i_other.m_23) && AreAboutEqual(m_24, i_other.m_24) &&
		AreAboutEqual(m_31, i_other.m_31) && AreAboutEqual(m_32, i_other.m_32) && AreAboutEqual(m_33, i_other.m_33) && AreAboutEqual(m_34, i_other.m_34) &&
		AreAboutEqual(m_41, i_other.m_41) && AreAboutEqual(m_42, i_other.m_42) && AreAboutEqual(m_43, i_other.m_43) && AreAboutEqual(m_44, i_other.m_44));
}

/*Engine::Math::Matrix Engine::Math::Matrix::Multiply(const Matrix & i_other, Matrix & o_out) const
{
	return Matrix();
}*/

float Engine::Math::Matrix::Determinant()
{
	float determinant = m_14*m_23*m_32*m_41 - m_13*m_24*m_32*m_41 - m_14*m_22*m_33*m_41 + m_12*m_24*m_33*m_41 +
						m_13*m_22*m_34*m_41 - m_12*m_23*m_34*m_41 - m_14*m_23*m_31*m_42 + m_13*m_24*m_31*m_42 +
						m_14*m_21*m_33*m_42 - m_11*m_24*m_33*m_42 - m_13*m_21*m_34*m_42 + m_11*m_23*m_34*m_42 +
						m_14*m_22*m_31*m_43 - m_12*m_24*m_31*m_43 - m_14*m_21*m_32*m_43 + m_11*m_24*m_32*m_43 +
						m_12*m_21*m_34*m_43 - m_11*m_22*m_34*m_43 - m_13*m_22*m_31*m_44 + m_12*m_23*m_31*m_44 +
						m_13*m_21*m_32*m_44 - m_11*m_23*m_32*m_44 - m_12*m_21*m_33*m_44 + m_11*m_22*m_33*m_44;
	
	return determinant;
}

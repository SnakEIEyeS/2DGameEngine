#include "MatrixSSE.h"

#include <math.h>

const Engine::Math::FastMatrixSSE Engine::Math::MatrixSSE::Identity = MatrixSSE(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

Engine::Math::MatrixSSE::MatrixSSE()
{
}

Engine::Math::MatrixSSE::MatrixSSE(float i_11, float i_12, float i_13, float i_14, 
	float i_21, float i_22, float i_23, float i_24, 
	float i_31, float i_32, float i_33, float i_34, 
	float i_41, float i_42, float i_43, float i_44) :
	m_Vec4{ Vector4(i_11, i_12, i_13, i_14), 
			Vector4(i_21, i_22, i_23, i_24) , 
			Vector4(i_31, i_32, i_33, i_34) , 
			Vector4(i_41, i_42, i_43, i_44) }
{
}

Engine::Math::MatrixSSE::MatrixSSE(Vector4 i_vecArray[4]) :
	m_Vec4{i_vecArray[0], i_vecArray[1], i_vecArray[2], i_vecArray[3]}
{
}

Engine::Math::MatrixSSE::MatrixSSE(Vector4 i_vec1, Vector4 i_vec2, Vector4 i_vec3, Vector4 i_vec4) :
	m_Vec4{ i_vec1, i_vec2, i_vec3, i_vec4 }, m_Vec4SSE{ i_vec1, i_vec2, i_vec3, i_vec4 }
{
}

/*Engine::Math::MatrixSSE::MatrixSSE(__m128 i_vec1, __m128 i_vec2, __m128 i_vec3, __m128 i_vec4) : m_vec{ i_vec1, i_vec2, i_vec3, i_vec4 }
{
}*/

Engine::Math::MatrixSSE::MatrixSSE(const Engine::Math::MatrixSSE & i_other) :
	m_Vec4SSE{i_other.m_Vec4SSE[0], i_other.m_Vec4SSE[1], i_other.m_Vec4SSE[2],  i_other.m_Vec4SSE[3]}
{
}

Engine::Math::MatrixSSE & Engine::Math::MatrixSSE::operator=(const Engine::Math::MatrixSSE & i_other)
{
	m_Vec4SSE[0] = i_other.m_Vec4SSE[0];
	m_Vec4SSE[1] = i_other.m_Vec4SSE[1];
	m_Vec4SSE[2] = i_other.m_Vec4SSE[2];
	m_Vec4SSE[3] = i_other.m_Vec4SSE[3];
	
	return *this;
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateIdentity(void)
{
	return MatrixSSE(	Vector4(1.f, 0.f, 0.f, 0.f),
						Vector4(0.f, 1.f, 0.f, 0.f), 
						Vector4(0.f, 0.f, 1.f, 0.f), 
						Vector4(0.f, 0.f, 0.f, 1.f) );
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateXRotation(float i_RotationRadians)
{
	return MatrixSSE(	Vector4(1.f,					0.f,							0.f,			0.f),
						Vector4(0.f, (float)cos(i_RotationRadians), (float)sin(i_RotationRadians),	0.f),
						Vector4(0.f, (float)-sin(i_RotationRadians), (float)cos(i_RotationRadians),	0.f),
						Vector4(0.f,					0.f,							0.f,			1.f));
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateYRotation(float i_RotationRadians)
{
	return MatrixSSE(	Vector4((float)cos(i_RotationRadians), 0.f, (float)-sin(i_RotationRadians),	0.f),
						Vector4(			0.f,				1.f,					0.f,			0.f),
						Vector4((float)sin(i_RotationRadians), 0.f, (float)cos(i_RotationRadians),	0.f),
						Vector4(			0.f,				0.f,					0.f,			1.f));
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateZRotation(float i_RotationRadians)
{
	return MatrixSSE(	Vector4((float)cos(i_RotationRadians), (float)sin(i_RotationRadians),	0.f, 0.f),
						Vector4((float)-sin(i_RotationRadians), (float)cos(i_RotationRadians),	0.f, 0.f),
						Vector4(			0.f,									0.f,			1.f, 0.f),
						Vector4(			0.f,									0.f,			0.f, 1.f));
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateTranslation(Vector2 i_trans)
{
	return MatrixSSE(	Vector4(	1.f,			0.f,	0.f, 0.f),
						Vector4(0.f,				1.f,	0.f, 0.f),
						Vector4(0.f,				0.f,	1.f, 0.f),
						Vector4(i_trans.x, i_trans.y,	0.f, 1.f));
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateTranslation(float i_transX, float i_transY)
{
	return MatrixSSE(	Vector4(1.f,			0.f,	0.f, 0.f),
						Vector4(0.f,			1.f,	0.f, 0.f),
						Vector4(0.f,			0.f,	1.f, 0.f),
						Vector4(i_transX, i_transY,	0.f, 1.f));
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::CreateScale(float i_scaleX, float i_scaleY)
{
	return MatrixSSE(	Vector4(i_scaleX,	0.f,	0.f,	0.f),
						Vector4(0.f,		i_scaleY,	0.f,	0.f),
						Vector4(0.f,			0.f,	1.f,	0.f),
						Vector4(0.f,			0.f,	0.f,	1.f));
}

void Engine::Math::MatrixSSE::Invert(void)
{
	/*MatrixSSE I = CreateIdentity();

	MatrixSSE MtxSquare = *this * *this;
	MatrixSSE MtxCube = *this * MtxSquare;

	float TraceOfThis = m_Vec4[0].x() + m_Vec4[1].y() + m_Vec4[2].z() + m_Vec4[3].w();
	float TraceOfSquare = MtxSquare.m_Vec4[0].x() + MtxSquare.m_Vec4[1].y() + MtxSquare.m_Vec4[2].z() + MtxSquare.m_Vec4[3].w();
	float TraceOfCube = MtxCube.m_Vec4[0].x() + MtxCube.m_Vec4[1].y() + MtxCube.m_Vec4[2].z() + MtxCube.m_Vec4[3].w();

	float S1 = static_cast<float>(((TraceOfThis * TraceOfThis * TraceOfThis) - (3 * TraceOfThis * TraceOfSquare) + (2 * TraceOfCube)) / 6);
	float S2 = static_cast<float>(0.5 * ((TraceOfThis * TraceOfThis) - TraceOfSquare));

	*this = (S1 * I) - (S2 * *this) + (TraceOfThis * MtxSquare) - MtxCube;*/
	eleArray ele(m_Vec4[0], m_Vec4[1], m_Vec4[2], m_Vec4[3]);
	float scale = 1 / Determinant(ele);

	/**this = MatrixSSE(
		scale * (m_Vec4[1].z()*m_Vec4[2].w()*m_Vec4[3].y() - m_Vec4[1].w()*m_Vec4[2].z()*m_Vec4[3].y() + m_Vec4[1].w()*m_Vec4[2].y()*m_Vec4[3].z() - m_Vec4[1].y()*m_Vec4[2].w()*m_Vec4[3].z() - m_Vec4[1].z()*m_Vec4[2].y()*m_Vec4[3].w() + m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[2].z()*m_Vec4[3].y() - m_Vec4[0].z()*m_Vec4[2].w()*m_Vec4[3].y() - m_Vec4[0].w()*m_Vec4[2].y()*m_Vec4[3].z() + m_Vec4[0].y()*m_Vec4[2].w()*m_Vec4[3].z() + m_Vec4[0].z()*m_Vec4[2].y()*m_Vec4[3].w() - m_Vec4[0].y()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[3].y() - m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[3].y() + m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[3].z() - m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[3].z() - m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[3].w() + m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[2].y() - m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[2].y() - m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[2].z() + m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[2].z() + m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[2].w() - m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[2].w()),
		scale * (m_Vec4[1].w()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[1].z()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[1].w()*m_Vec4[2].x()*m_Vec4[3].z() + m_Vec4[1].x()*m_Vec4[2].w()*m_Vec4[3].z() + m_Vec4[1].z()*m_Vec4[2].x()*m_Vec4[3].w() - m_Vec4[1].x()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].z()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[2].z()*m_Vec4[3].x() + m_Vec4[0].w()*m_Vec4[2].x()*m_Vec4[3].z() - m_Vec4[0].x()*m_Vec4[2].w()*m_Vec4[3].z() - m_Vec4[0].z()*m_Vec4[2].x()*m_Vec4[3].w() + m_Vec4[0].x()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[3].z() + m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[3].z() + m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[3].w() - m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[2].x() - m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[2].x() + m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[2].z() - m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[2].z() - m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[2].w() + m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[2].w()),
		scale * (m_Vec4[1].y()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[1].w()*m_Vec4[2].y()*m_Vec4[3].x() + m_Vec4[1].w()*m_Vec4[2].x()*m_Vec4[3].y() - m_Vec4[1].x()*m_Vec4[2].w()*m_Vec4[3].y() - m_Vec4[1].y()*m_Vec4[2].x()*m_Vec4[3].w() + m_Vec4[1].x()*m_Vec4[2].y()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[2].y()*m_Vec4[3].x() - m_Vec4[0].y()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[2].x()*m_Vec4[3].y() + m_Vec4[0].x()*m_Vec4[2].w()*m_Vec4[3].y() + m_Vec4[0].y()*m_Vec4[2].x()*m_Vec4[3].w() - m_Vec4[0].x()*m_Vec4[2].y()*m_Vec4[3].w()),
		scale * (m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[3].x() + m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[3].y() - m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[3].y() - m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[3].w() + m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[2].x() - m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[2].x() - m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[2].y() + m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[2].y() + m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[2].w() - m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[2].w()),
		scale * (m_Vec4[1].z()*m_Vec4[2].y()*m_Vec4[3].x() - m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[1].z()*m_Vec4[2].x()*m_Vec4[3].y() + m_Vec4[1].x()*m_Vec4[2].z()*m_Vec4[3].y() + m_Vec4[1].y()*m_Vec4[2].x()*m_Vec4[3].z() - m_Vec4[1].x()*m_Vec4[2].y()*m_Vec4[3].z()),
		scale * (m_Vec4[0].y()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[2].y()*m_Vec4[3].x() + m_Vec4[0].z()*m_Vec4[2].x()*m_Vec4[3].y() - m_Vec4[0].x()*m_Vec4[2].z()*m_Vec4[3].y() - m_Vec4[0].y()*m_Vec4[2].x()*m_Vec4[3].z() + m_Vec4[0].x()*m_Vec4[2].y()*m_Vec4[3].z()),
		scale * (m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[3].x() - m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[3].y() + m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[3].y() + m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[3].z() - m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[3].z()),
		scale * (m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[2].x() - m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[2].x() + m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[2].y() - m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[2].y() - m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[2].z() + m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[2].z())
	);*/

	*this =  MatrixSSE(
		(ele.m_23*ele.m_34*ele.m_42 - ele.m_24*ele.m_33*ele.m_42 + ele.m_24*ele.m_32*ele.m_43 - ele.m_22*ele.m_34*ele.m_43 - ele.m_23*ele.m_32*ele.m_44 + ele.m_22*ele.m_33*ele.m_44) * scale,
		(ele.m_14*ele.m_33*ele.m_42 - ele.m_13*ele.m_34*ele.m_42 - ele.m_14*ele.m_32*ele.m_43 + ele.m_12*ele.m_34*ele.m_43 + ele.m_13*ele.m_32*ele.m_44 - ele.m_12*ele.m_33*ele.m_44) * scale,
		(ele.m_13*ele.m_24*ele.m_42 - ele.m_14*ele.m_23*ele.m_42 + ele.m_14*ele.m_22*ele.m_43 - ele.m_12*ele.m_24*ele.m_43 - ele.m_13*ele.m_22*ele.m_44 + ele.m_12*ele.m_23*ele.m_44) * scale,
		(ele.m_14*ele.m_23*ele.m_32 - ele.m_13*ele.m_24*ele.m_32 - ele.m_14*ele.m_22*ele.m_33 + ele.m_12*ele.m_24*ele.m_33 + ele.m_13*ele.m_22*ele.m_34 - ele.m_12*ele.m_23*ele.m_34) * scale,
		(ele.m_24*ele.m_33*ele.m_41 - ele.m_23*ele.m_34*ele.m_41 - ele.m_24*ele.m_31*ele.m_43 + ele.m_21*ele.m_34*ele.m_43 + ele.m_23*ele.m_31*ele.m_44 - ele.m_21*ele.m_33*ele.m_44) * scale,
		(ele.m_13*ele.m_34*ele.m_41 - ele.m_14*ele.m_33*ele.m_41 + ele.m_14*ele.m_31*ele.m_43 - ele.m_11*ele.m_34*ele.m_43 - ele.m_13*ele.m_31*ele.m_44 + ele.m_11*ele.m_33*ele.m_44) * scale,
		(ele.m_14*ele.m_23*ele.m_41 - ele.m_13*ele.m_24*ele.m_41 - ele.m_14*ele.m_21*ele.m_43 + ele.m_11*ele.m_24*ele.m_43 + ele.m_13*ele.m_21*ele.m_44 - ele.m_11*ele.m_23*ele.m_44) * scale,
		(ele.m_13*ele.m_24*ele.m_31 - ele.m_14*ele.m_23*ele.m_31 + ele.m_14*ele.m_21*ele.m_33 - ele.m_11*ele.m_24*ele.m_33 - ele.m_13*ele.m_21*ele.m_34 + ele.m_11*ele.m_23*ele.m_34) * scale,
		(ele.m_22*ele.m_34*ele.m_41 - ele.m_24*ele.m_32*ele.m_41 + ele.m_24*ele.m_31*ele.m_42 - ele.m_21*ele.m_34*ele.m_42 - ele.m_22*ele.m_31*ele.m_44 + ele.m_21*ele.m_32*ele.m_44) * scale,
		(ele.m_14*ele.m_32*ele.m_41 - ele.m_12*ele.m_34*ele.m_41 - ele.m_14*ele.m_31*ele.m_42 + ele.m_11*ele.m_34*ele.m_42 + ele.m_12*ele.m_31*ele.m_44 - ele.m_11*ele.m_32*ele.m_44) * scale,
		(ele.m_12*ele.m_24*ele.m_41 - ele.m_14*ele.m_22*ele.m_41 + ele.m_14*ele.m_21*ele.m_42 - ele.m_11*ele.m_24*ele.m_42 - ele.m_12*ele.m_21*ele.m_44 + ele.m_11*ele.m_22*ele.m_44) * scale,
		(ele.m_14*ele.m_22*ele.m_31 - ele.m_12*ele.m_24*ele.m_31 - ele.m_14*ele.m_21*ele.m_32 + ele.m_11*ele.m_24*ele.m_32 + ele.m_12*ele.m_21*ele.m_34 - ele.m_11*ele.m_22*ele.m_34) * scale,
		(ele.m_23*ele.m_32*ele.m_41 - ele.m_22*ele.m_33*ele.m_41 - ele.m_23*ele.m_31*ele.m_42 + ele.m_21*ele.m_33*ele.m_42 + ele.m_22*ele.m_31*ele.m_43 - ele.m_21*ele.m_32*ele.m_43) * scale,
		(ele.m_12*ele.m_33*ele.m_41 - ele.m_13*ele.m_32*ele.m_41 + ele.m_13*ele.m_31*ele.m_42 - ele.m_11*ele.m_33*ele.m_42 - ele.m_12*ele.m_31*ele.m_43 + ele.m_11*ele.m_32*ele.m_43) * scale,
		(ele.m_13*ele.m_22*ele.m_41 - ele.m_12*ele.m_23*ele.m_41 - ele.m_13*ele.m_21*ele.m_42 + ele.m_11*ele.m_23*ele.m_42 + ele.m_12*ele.m_21*ele.m_43 - ele.m_11*ele.m_22*ele.m_43) * scale,
		(ele.m_12*ele.m_23*ele.m_31 - ele.m_13*ele.m_22*ele.m_31 + ele.m_13*ele.m_21*ele.m_32 - ele.m_11*ele.m_23*ele.m_32 - ele.m_12*ele.m_21*ele.m_33 + ele.m_11*ele.m_22*ele.m_33) * scale
	);
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::GetInverse(void)
{
	/*MatrixSSE I = CreateIdentity();
	
	MatrixSSE MtxSquare = *this * *this;
	MatrixSSE MtxCube = *this * MtxSquare;

	float TraceOfThis = m_Vec4[0].x() + m_Vec4[1].y() + m_Vec4[2].z() + m_Vec4[3].w();
	float TraceOfSquare = MtxSquare.m_Vec4[0].x() + MtxSquare.m_Vec4[1].y() + MtxSquare.m_Vec4[2].z() + MtxSquare.m_Vec4[3].w();
	float TraceOfCube = MtxCube.m_Vec4[0].x() + MtxCube.m_Vec4[1].y() + MtxCube.m_Vec4[2].z() + MtxCube.m_Vec4[3].w();

	float S1 = static_cast<float>(((TraceOfThis * TraceOfThis * TraceOfThis) - (3 * TraceOfThis * TraceOfSquare) + (2 * TraceOfCube)) / 6);
	float S2 = static_cast<float>(0.5 * ((TraceOfThis * TraceOfThis) - TraceOfSquare));

	MatrixSSE MtxInverse = (S1 * I) - (S2 * *this) + (TraceOfThis * MtxSquare) - MtxCube;
	return MtxInverse;*/

	eleArray ele(m_Vec4[0], m_Vec4[1], m_Vec4[2], m_Vec4[3]);

	float scale = 1 / Determinant(ele);

	/*return MatrixSSE(
		scale * (m_Vec4[1].z()*m_Vec4[2].w()*m_Vec4[3].y() - m_Vec4[1].w()*m_Vec4[2].z()*m_Vec4[3].y() + m_Vec4[1].w()*m_Vec4[2].y()*m_Vec4[3].z() - m_Vec4[1].y()*m_Vec4[2].w()*m_Vec4[3].z() - m_Vec4[1].z()*m_Vec4[2].y()*m_Vec4[3].w() + m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[2].z()*m_Vec4[3].y() - m_Vec4[0].z()*m_Vec4[2].w()*m_Vec4[3].y() - m_Vec4[0].w()*m_Vec4[2].y()*m_Vec4[3].z() + m_Vec4[0].y()*m_Vec4[2].w()*m_Vec4[3].z() + m_Vec4[0].z()*m_Vec4[2].y()*m_Vec4[3].w() - m_Vec4[0].y()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[3].y() - m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[3].y() + m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[3].z() - m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[3].z() - m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[3].w() + m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[2].y() - m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[2].y() - m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[2].z() + m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[2].z() + m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[2].w() - m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[2].w()),
		scale * (m_Vec4[1].w()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[1].z()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[1].w()*m_Vec4[2].x()*m_Vec4[3].z() + m_Vec4[1].x()*m_Vec4[2].w()*m_Vec4[3].z() + m_Vec4[1].z()*m_Vec4[2].x()*m_Vec4[3].w() - m_Vec4[1].x()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].z()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[2].z()*m_Vec4[3].x() + m_Vec4[0].w()*m_Vec4[2].x()*m_Vec4[3].z() - m_Vec4[0].x()*m_Vec4[2].w()*m_Vec4[3].z() - m_Vec4[0].z()*m_Vec4[2].x()*m_Vec4[3].w() + m_Vec4[0].x()*m_Vec4[2].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[3].z() + m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[3].z() + m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[3].w() - m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[3].w()),
		scale * (m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[2].x() - m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[2].x() + m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[2].z() - m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[2].z() - m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[2].w() + m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[2].w()),
		scale * (m_Vec4[1].y()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[1].w()*m_Vec4[2].y()*m_Vec4[3].x() + m_Vec4[1].w()*m_Vec4[2].x()*m_Vec4[3].y() - m_Vec4[1].x()*m_Vec4[2].w()*m_Vec4[3].y() - m_Vec4[1].y()*m_Vec4[2].x()*m_Vec4[3].w() + m_Vec4[1].x()*m_Vec4[2].y()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[2].y()*m_Vec4[3].x() - m_Vec4[0].y()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[2].x()*m_Vec4[3].y() + m_Vec4[0].x()*m_Vec4[2].w()*m_Vec4[3].y() + m_Vec4[0].y()*m_Vec4[2].x()*m_Vec4[3].w() - m_Vec4[0].x()*m_Vec4[2].y()*m_Vec4[3].w()),
		scale * (m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[3].x() + m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[3].y() - m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[3].y() - m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[3].w() + m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[3].w()),
		scale * (m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[2].x() - m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[2].x() - m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[2].y() + m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[2].y() + m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[2].w() - m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[2].w()),
		scale * (m_Vec4[1].z()*m_Vec4[2].y()*m_Vec4[3].x() - m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[1].z()*m_Vec4[2].x()*m_Vec4[3].y() + m_Vec4[1].x()*m_Vec4[2].z()*m_Vec4[3].y() + m_Vec4[1].y()*m_Vec4[2].x()*m_Vec4[3].z() - m_Vec4[1].x()*m_Vec4[2].y()*m_Vec4[3].z()),
		scale * (m_Vec4[0].y()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[2].y()*m_Vec4[3].x() + m_Vec4[0].z()*m_Vec4[2].x()*m_Vec4[3].y() - m_Vec4[0].x()*m_Vec4[2].z()*m_Vec4[3].y() - m_Vec4[0].y()*m_Vec4[2].x()*m_Vec4[3].z() + m_Vec4[0].x()*m_Vec4[2].y()*m_Vec4[3].z()),
		scale * (m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[3].x() - m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[3].y() + m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[3].y() + m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[3].z() - m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[3].z()),
		scale * (m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[2].x() - m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[2].x() + m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[2].y() - m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[2].y() - m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[2].z() + m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[2].z())
	);*/

	return MatrixSSE(
		(ele.m_23*ele.m_34*ele.m_42 - ele.m_24*ele.m_33*ele.m_42 + ele.m_24*ele.m_32*ele.m_43 - ele.m_22*ele.m_34*ele.m_43 - ele.m_23*ele.m_32*ele.m_44 + ele.m_22*ele.m_33*ele.m_44) * scale,
		(ele.m_14*ele.m_33*ele.m_42 - ele.m_13*ele.m_34*ele.m_42 - ele.m_14*ele.m_32*ele.m_43 + ele.m_12*ele.m_34*ele.m_43 + ele.m_13*ele.m_32*ele.m_44 - ele.m_12*ele.m_33*ele.m_44) * scale,
		(ele.m_13*ele.m_24*ele.m_42 - ele.m_14*ele.m_23*ele.m_42 + ele.m_14*ele.m_22*ele.m_43 - ele.m_12*ele.m_24*ele.m_43 - ele.m_13*ele.m_22*ele.m_44 + ele.m_12*ele.m_23*ele.m_44) * scale,
		(ele.m_14*ele.m_23*ele.m_32 - ele.m_13*ele.m_24*ele.m_32 - ele.m_14*ele.m_22*ele.m_33 + ele.m_12*ele.m_24*ele.m_33 + ele.m_13*ele.m_22*ele.m_34 - ele.m_12*ele.m_23*ele.m_34) * scale,
		(ele.m_24*ele.m_33*ele.m_41 - ele.m_23*ele.m_34*ele.m_41 - ele.m_24*ele.m_31*ele.m_43 + ele.m_21*ele.m_34*ele.m_43 + ele.m_23*ele.m_31*ele.m_44 - ele.m_21*ele.m_33*ele.m_44) * scale,
		(ele.m_13*ele.m_34*ele.m_41 - ele.m_14*ele.m_33*ele.m_41 + ele.m_14*ele.m_31*ele.m_43 - ele.m_11*ele.m_34*ele.m_43 - ele.m_13*ele.m_31*ele.m_44 + ele.m_11*ele.m_33*ele.m_44) * scale,
		(ele.m_14*ele.m_23*ele.m_41 - ele.m_13*ele.m_24*ele.m_41 - ele.m_14*ele.m_21*ele.m_43 + ele.m_11*ele.m_24*ele.m_43 + ele.m_13*ele.m_21*ele.m_44 - ele.m_11*ele.m_23*ele.m_44) * scale,
		(ele.m_13*ele.m_24*ele.m_31 - ele.m_14*ele.m_23*ele.m_31 + ele.m_14*ele.m_21*ele.m_33 - ele.m_11*ele.m_24*ele.m_33 - ele.m_13*ele.m_21*ele.m_34 + ele.m_11*ele.m_23*ele.m_34) * scale,
		(ele.m_22*ele.m_34*ele.m_41 - ele.m_24*ele.m_32*ele.m_41 + ele.m_24*ele.m_31*ele.m_42 - ele.m_21*ele.m_34*ele.m_42 - ele.m_22*ele.m_31*ele.m_44 + ele.m_21*ele.m_32*ele.m_44) * scale,
		(ele.m_14*ele.m_32*ele.m_41 - ele.m_12*ele.m_34*ele.m_41 - ele.m_14*ele.m_31*ele.m_42 + ele.m_11*ele.m_34*ele.m_42 + ele.m_12*ele.m_31*ele.m_44 - ele.m_11*ele.m_32*ele.m_44) * scale,
		(ele.m_12*ele.m_24*ele.m_41 - ele.m_14*ele.m_22*ele.m_41 + ele.m_14*ele.m_21*ele.m_42 - ele.m_11*ele.m_24*ele.m_42 - ele.m_12*ele.m_21*ele.m_44 + ele.m_11*ele.m_22*ele.m_44) * scale,
		(ele.m_14*ele.m_22*ele.m_31 - ele.m_12*ele.m_24*ele.m_31 - ele.m_14*ele.m_21*ele.m_32 + ele.m_11*ele.m_24*ele.m_32 + ele.m_12*ele.m_21*ele.m_34 - ele.m_11*ele.m_22*ele.m_34) * scale,
		(ele.m_23*ele.m_32*ele.m_41 - ele.m_22*ele.m_33*ele.m_41 - ele.m_23*ele.m_31*ele.m_42 + ele.m_21*ele.m_33*ele.m_42 + ele.m_22*ele.m_31*ele.m_43 - ele.m_21*ele.m_32*ele.m_43) * scale,
		(ele.m_12*ele.m_33*ele.m_41 - ele.m_13*ele.m_32*ele.m_41 + ele.m_13*ele.m_31*ele.m_42 - ele.m_11*ele.m_33*ele.m_42 - ele.m_12*ele.m_31*ele.m_43 + ele.m_11*ele.m_32*ele.m_43) * scale,
		(ele.m_13*ele.m_22*ele.m_41 - ele.m_12*ele.m_23*ele.m_41 - ele.m_13*ele.m_21*ele.m_42 + ele.m_11*ele.m_23*ele.m_42 + ele.m_12*ele.m_21*ele.m_43 - ele.m_11*ele.m_22*ele.m_43) * scale,
		(ele.m_12*ele.m_23*ele.m_31 - ele.m_13*ele.m_22*ele.m_31 + ele.m_13*ele.m_21*ele.m_32 - ele.m_11*ele.m_23*ele.m_32 - ele.m_12*ele.m_21*ele.m_33 + ele.m_11*ele.m_22*ele.m_33) * scale
	);
}

void Engine::Math::MatrixSSE::Transpose(void)
{
	//_MM_TRANSPOSE4_PS(m_vec[0], m_vec[1], m_vec[2], m_vec[3]);

	eleArray ele(m_Vec4[0], m_Vec4[1], m_Vec4[2], m_Vec4[3]);

	*this = MatrixSSE(
		ele.m_11, ele.m_21, ele.m_31, ele.m_41,
		ele.m_12, ele.m_22, ele.m_32, ele.m_42,
		ele.m_13, ele.m_23, ele.m_33, ele.m_43,
		ele.m_14, ele.m_24, ele.m_34, ele.m_44
	);
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::GetTranspose(void) const
{
	//MatrixSSE MtxToReturn = *this;
	//_MM_TRANSPOSE4_PS(MtxToReturn.m_vec[0], MtxToReturn.m_vec[1], MtxToReturn.m_vec[2], MtxToReturn.m_vec[3]);

	eleArray ele(m_Vec4[0], m_Vec4[1], m_Vec4[2], m_Vec4[3]);

	return MatrixSSE(
		ele.m_11, ele.m_21, ele.m_31, ele.m_41,
		ele.m_12, ele.m_22, ele.m_32, ele.m_42,
		ele.m_13, ele.m_23, ele.m_33, ele.m_43,
		ele.m_14, ele.m_24, ele.m_34, ele.m_44
	);
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::operator*(const MatrixSSE & i_other) const
{
	MatrixSSE other_Transpose = i_other.GetTranspose();
	return MatrixSSE( dot(m_Vec4[0], other_Transpose.m_Vec4[0]), dot(m_Vec4[0], other_Transpose.m_Vec4[1]), dot(m_Vec4[0], other_Transpose.m_Vec4[2]), dot(m_Vec4[0], other_Transpose.m_Vec4[3]),
					dot(m_Vec4[1], other_Transpose.m_Vec4[0]), dot(m_Vec4[1], other_Transpose.m_Vec4[1]), dot(m_Vec4[1], other_Transpose.m_Vec4[2]), dot(m_Vec4[1], other_Transpose.m_Vec4[3]),
					dot(m_Vec4[2], other_Transpose.m_Vec4[0]), dot(m_Vec4[2], other_Transpose.m_Vec4[1]), dot(m_Vec4[2], other_Transpose.m_Vec4[2]), dot(m_Vec4[2], other_Transpose.m_Vec4[3]),
					dot(m_Vec4[3], other_Transpose.m_Vec4[0]), dot(m_Vec4[3], other_Transpose.m_Vec4[1]), dot(m_Vec4[3], other_Transpose.m_Vec4[2]), dot(m_Vec4[3], other_Transpose.m_Vec4[3]) );
}

/*Engine::Math::MatrixSSE Engine::Math::MatrixSSE::operator*(float i_float) const
{
	__m128 multiplier = { i_float, i_float, i_float, i_float };

	MatrixSSE MtxToReturn = *this;

	MtxToReturn.m_vec[0] = _mm_mul_ps(MtxToReturn.m_vec[0], multiplier);
	MtxToReturn.m_vec[1] = _mm_mul_ps(MtxToReturn.m_vec[1], multiplier);
	MtxToReturn.m_vec[2] = _mm_mul_ps(MtxToReturn.m_vec[2], multiplier);
	MtxToReturn.m_vec[3] = _mm_mul_ps(MtxToReturn.m_vec[3], multiplier);

	return MtxToReturn;
}*/

Engine::Math::Vector4SSE Engine::Math::MatrixSSE::MultiplyLeft(const Engine::Math::Vector4SSE & i_Vector) const
{
	MatrixSSE MtxTranspose = this->GetTranspose();
	return Vector4SSE( dot(i_Vector, MtxTranspose.m_vec[0]), dot(i_Vector, MtxTranspose.m_vec[1]), dot(i_Vector, MtxTranspose.m_vec[2]), dot(i_Vector, MtxTranspose.m_vec[3]) );
}

bool Engine::Math::MatrixSSE::operator==(const MatrixSSE & i_other) const
{
	__m128 result;
	
	for (unsigned int i = 0; i < 4; i++)
	{
		result = _mm_cmpeq_ps(m_vec[i], i_other.m_vec[i]);
		if (_mm_movemask_ps(result) != 15)
			return false;
	}

	return true;
}

bool Engine::Math::MatrixSSE::operator!=(const MatrixSSE & i_other) const
{
	return !(*this == i_other);
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::operator+(const MatrixSSE & i_other) const
{
	//return MatrixSSE(_mm_add_ps(m_vec[0], i_other.m_vec[0]), _mm_add_ps(m_vec[1], i_other.m_vec[1]), _mm_add_ps(m_vec[2], i_other.m_vec[2]), _mm_add_ps(m_vec[3], i_other.m_vec[3]));
	return MatrixSSE(m_Vec4[0] + i_other.m_Vec4[0], m_Vec4[1] + i_other.m_Vec4[1], m_Vec4[2] + i_other.m_Vec4[2], m_Vec4[3] + i_other.m_Vec4[3]);
}

Engine::Math::MatrixSSE Engine::Math::MatrixSSE::operator-(const MatrixSSE & i_other) const
{
	//return MatrixSSE( _mm_sub_ps(m_vec[0], i_other.m_vec[0]), _mm_sub_ps(m_vec[1], i_other.m_vec[1]), _mm_sub_ps(m_vec[2], i_other.m_vec[2]), _mm_sub_ps(m_vec[3], i_other.m_vec[3]) );
	return MatrixSSE(m_Vec4[0] - i_other.m_Vec4[0], m_Vec4[1] - i_other.m_Vec4[1], m_Vec4[2] - i_other.m_Vec4[2], m_Vec4[3] - i_other.m_Vec4[3]);
}

Engine::Math::Vector4SSE & Engine::Math::MatrixSSE::operator[](int index)
{
	return m_Vec4SSE[index];
}

float Engine::Math::MatrixSSE::Determinant(eleArray ele)
{
	/*float determinant = 
		m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[2].y()*m_Vec4[3].x() - m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[2].y()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].x() + m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[2].z()*m_Vec4[3].x() +
		m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].x() - m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[2].w()*m_Vec4[3].x() - m_Vec4[0].w()*m_Vec4[1].z()*m_Vec4[2].x()*m_Vec4[3].y() + m_Vec4[0].z()*m_Vec4[1].w()*m_Vec4[2].x()*m_Vec4[3].y() +
		m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[2].z()*m_Vec4[3].y() - m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[2].z()*m_Vec4[3].y() - m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[2].w()*m_Vec4[3].y() + m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[2].w()*m_Vec4[3].y() +
		m_Vec4[0].w()*m_Vec4[1].y()*m_Vec4[2].x()*m_Vec4[3].z() - m_Vec4[0].y()*m_Vec4[1].w()*m_Vec4[2].x()*m_Vec4[3].z() - m_Vec4[0].w()*m_Vec4[1].x()*m_Vec4[2].y()*m_Vec4[3].z() + m_Vec4[0].x()*m_Vec4[1].w()*m_Vec4[2].y()*m_Vec4[3].z() +
		m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[2].w()*m_Vec4[3].z() - m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[2].w()*m_Vec4[3].z() - m_Vec4[0].z()*m_Vec4[1].y()*m_Vec4[2].x()*m_Vec4[3].w() + m_Vec4[0].y()*m_Vec4[1].z()*m_Vec4[2].x()*m_Vec4[3].w() +
		m_Vec4[0].z()*m_Vec4[1].x()*m_Vec4[2].y()*m_Vec4[3].w() - m_Vec4[0].x()*m_Vec4[1].z()*m_Vec4[2].y()*m_Vec4[3].w() - m_Vec4[0].y()*m_Vec4[1].x()*m_Vec4[2].z()*m_Vec4[3].w() + m_Vec4[0].x()*m_Vec4[1].y()*m_Vec4[2].z()*m_Vec4[3].w();*/

	float determinant = ele.m_14*ele.m_23*ele.m_32*ele.m_41 - ele.m_13*ele.m_24*ele.m_32*ele.m_41 - ele.m_14*ele.m_22*ele.m_33*ele.m_41 + ele.m_12*ele.m_24*ele.m_33*ele.m_41 +
		ele.m_13*ele.m_22*ele.m_34*ele.m_41 - ele.m_12*ele.m_23*ele.m_34*ele.m_41 - ele.m_14*ele.m_23*ele.m_31*ele.m_42 + ele.m_13*ele.m_24*ele.m_31*ele.m_42 +
		ele.m_14*ele.m_21*ele.m_33*ele.m_42 - ele.m_11*ele.m_24*ele.m_33*ele.m_42 - ele.m_13*ele.m_21*ele.m_34*ele.m_42 + ele.m_11*ele.m_23*ele.m_34*ele.m_42 +
		ele.m_14*ele.m_22*ele.m_31*ele.m_43 - ele.m_12*ele.m_24*ele.m_31*ele.m_43 - ele.m_14*ele.m_21*ele.m_32*ele.m_43 + ele.m_11*ele.m_24*ele.m_32*ele.m_43 +
		ele.m_12*ele.m_21*ele.m_34*ele.m_43 - ele.m_11*ele.m_22*ele.m_34*ele.m_43 - ele.m_13*ele.m_22*ele.m_31*ele.m_44 + ele.m_12*ele.m_23*ele.m_31*ele.m_44 +
		ele.m_13*ele.m_21*ele.m_32*ele.m_44 - ele.m_11*ele.m_23*ele.m_32*ele.m_44 - ele.m_12*ele.m_21*ele.m_33*ele.m_44 + ele.m_11*ele.m_22*ele.m_33*ele.m_44;

		
	return determinant;
}

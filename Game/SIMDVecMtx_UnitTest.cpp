#include <assert.h>

#include "_Console\ConsolePrint.h"
#include "Math\FloatOperations.h"
#include "Math\Vector2.h"
#include "Math\Vector4.hpp"
#include "Math\Vector4SSE.h"
#include "Math\Matrix.h"
#include "Math\MatrixSSE.h"

bool SIMDVecMtx_UnitTest()
{
	Engine::Math::Vector4SSE OneVec(1.f, 2.f, 3.f, 4.f);
	Engine::Math::Vector4SSE TwoVec = OneVec;

	assert(OneVec == TwoVec);

	Engine::Math::Vector4SSE ThreeVec(OneVec);
	assert(OneVec == ThreeVec);

	Engine::Math::Vector4SSE Vec4FromVec2(Vector2{ 2.f, 5.f }, 1.f);
	assert(Vec4FromVec2 == Engine::Math::Vector4SSE(2.f, 5.f, 0.f, 1.f));

	assert(Vec4FromVec2 != OneVec);

	//Vector4 dot product
	float dotResult = Engine::Math::dot(OneVec, Vec4FromVec2);	//1.0*2.0 + 2.0*5.0 + 3.0*0.0 + 4.0*1.0 = 16.0
	assert(AreAboutEqual(dotResult, 16.f));

	//Vector4 Matrix Multiplication & Translation, Scale, Rotation
	//Translation
	Engine::Math::Vector4SSE TranslatedVec = Engine::Math::Vector4SSE(1.f, 2.f, 3.f, 1.f) * Engine::Math::MatrixSSE::CreateTranslation(Vector2{ 1.f, 2.f });
	assert(TranslatedVec == Engine::Math::Vector4SSE(2.f, 4.f, 3.f, 1.f));

	TranslatedVec = Engine::Math::Vector4SSE(1.f, 2.f, 3.f, 1.f) * Engine::Math::MatrixSSE::CreateTranslation(2.f, 3.f);
	assert(TranslatedVec == Engine::Math::Vector4SSE(3.f, 5.f, 3.f, 1.f));

	//Scale
	Engine::Math::Vector4SSE ScaledVec = Engine::Math::Vector4SSE(2.f, 3.f, 3.f, 1.f) * Engine::Math::MatrixSSE::CreateScale(2.f, 4.f);
	assert(ScaledVec == Engine::Math::Vector4SSE(4.f, 12.f, 3.f, 1.f));

	Engine::Math::Vector4SSE VecMultiplyLeft = Engine::Math::MatrixSSE::CreateScale(2.f, 4.f).MultiplyLeft(Engine::Math::Vector4SSE(2.f, 3.f, 3.f, 1.f));
	assert(VecMultiplyLeft == Engine::Math::Vector4SSE(4.f, 12.f, 3.f, 1.f));

	//XRotation
	Engine::Math::Vector4SSE RotateVec(5.f, 3.f, 6.f, 9.f);
	RotateVec = RotateVec * Engine::Math::MatrixSSE::CreateXRotation(0);
	assert(RotateVec == Engine::Math::Vector4SSE(5.f, 3.f, 6.f, 9.f));

	//YRotation
	RotateVec = RotateVec * Engine::Math::MatrixSSE::CreateYRotation(0);
	assert(RotateVec == Engine::Math::Vector4SSE(5.f, 3.f, 6.f, 9.f));

	//ZRotation
	RotateVec = RotateVec * Engine::Math::MatrixSSE::CreateZRotation(0);
	assert(RotateVec == Engine::Math::Vector4SSE(5.f, 3.f, 6.f, 9.f));

	//Identity Matrix
	Engine::Math::MatrixSSE IdentityTest = Engine::Math::MatrixSSE::CreateIdentity();
	assert(IdentityTest == Engine::Math::MatrixSSE::Identity);

	//Matrix Constructors
	Engine::Math::MatrixSSE StandardMatrix(
		1.f, 3.f, 2.f, 0.f,
		2.f, 5.f, 0.f, 1.f,
		1.f, 1.f, 2.f, 7.f,
		3.f, 2.f, 0.f, 0.f
	);

	Engine::Math::MatrixSSE CopiedMatrix(StandardMatrix);
	assert(CopiedMatrix == StandardMatrix);

	//Matrix Matrix Multiplication
	Engine::Math::MatrixSSE MultMatrix = StandardMatrix * CopiedMatrix;
	assert(
		MultMatrix == Engine::Math::MatrixSSE(
			9.f, 20.f, 6.f, 17.f,
			15.f, 33.f, 4.f, 5.f,
			26.f, 24.f, 6.f, 15.f,
			7.f, 19.f, 6.f, 2.f));

	//Matrix Transpose
	Engine::Math::MatrixSSE TransposeMatrix = StandardMatrix.GetTranspose();
	assert(
		TransposeMatrix == Engine::Math::MatrixSSE(
			1.f, 2.f, 1.f, 3.f,
			3.f, 5.f, 1.f, 2.f,
			2.f, 0.f, 2.f, 0.f,
			0.f, 1.f, 7.f, 0.f));

	CopiedMatrix.Transpose();
	assert(
		CopiedMatrix == Engine::Math::MatrixSSE(
			1.f, 2.f, 1.f, 3.f,
			3.f, 5.f, 1.f, 2.f,
			2.f, 0.f, 2.f, 0.f,
			0.f, 1.f, 7.f, 0.f));

	//Matrix Inverse
	Engine::Math::MatrixSSE InverseMatrix = StandardMatrix.GetInverse();
	assert(
		InverseMatrix == Engine::Math::MatrixSSE(
			-0.0240963846f, -0.168674693f, 0.0240963846f, 0.445783108f,
			0.0361445770f, 0.253012031f, -0.0361445770f, -0.168674693f,
			0.457831323f, -0.295180708f, 0.0421686731f, 0.0301204808f,
			-0.132530123f, 0.0722891539f, 0.132530123f, -0.0481927693f));

	//Inverse of Transposed Matrix
	CopiedMatrix.Invert();
	assert(
		CopiedMatrix == Engine::Math::MatrixSSE(
			-0.0240963846f, 0.0361445770f, 0.457831323f, -0.132530123f,
			-0.168674693f, 0.253012031f, -0.295180708f, 0.0722891539f,
			0.0240963846f, -0.0361445770f, 0.0421686731f, 0.132530123f,
			0.445783108f, -0.168674693f, 0.0301204808f, -0.0481927693f));

	DEBUG_PRINT("SIMD Vector Matrix Unit Test passed!\n\n");

	return true;
}
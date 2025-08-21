#include <assert.h>

#include "_Console\ConsolePrint.h"
#include "Math\FloatOperations.h"
#include "Math\Vector2.h"
#include "Math\Vector4.hpp"
#include "Math\Matrix.h"

bool Vec4Matrix_UnitTest()
{
	Engine::Math::Vector4 OneVec(1.f, 2.f, 3.f, 4.f);
	Engine::Math::Vector4 TwoVec = OneVec;

	assert(OneVec == TwoVec);

	Engine::Math::Vector4 ThreeVec(OneVec);
	assert(OneVec == ThreeVec);

	Engine::Math::Vector4 Vec4FromVec2(Vector2{2.f, 5.f}, 1.f);
	assert(Vec4FromVec2 == Engine::Math::Vector4(2.f, 5.f, 0.f, 1.f));

	assert(Vec4FromVec2 != OneVec);

	//Vector4 dot product
	float dotResult = Engine::Math::dot(OneVec, Vec4FromVec2);	//1.0*2.0 + 2.0*5.0 + 3.0*0.0 + 4.0*1.0 = 16.0
	assert(AreAboutEqual(dotResult, 16.f));

	//Vector4 Matrix Multiplication & Translation, Scale, Rotation
	//Translation
	Engine::Math::Vector4 TranslatedVec = Engine::Math::Vector4(1.f, 2.f, 3.f, 1.f) * Engine::Math::Matrix::CreateTranslation(Vector2{ 1.f, 2.f });
	assert(TranslatedVec == Engine::Math::Vector4(2.f, 4.f, 3.f, 1.f));

	TranslatedVec = Engine::Math::Vector4(1.f, 2.f, 3.f, 1.f) * Engine::Math::Matrix::CreateTranslation(2.f, 3.f);
	assert(TranslatedVec == Engine::Math::Vector4(3.f, 5.f, 3.f, 1.f));

	//Scale
	Engine::Math::Vector4 ScaledVec = Engine::Math::Vector4(2.f, 3.f, 3.f, 1.f) * Engine::Math::Matrix::CreateScale(2.f, 4.f);
	assert(ScaledVec == Engine::Math::Vector4(4.f, 12.f, 3.f, 1.f));

	Engine::Math::Vector4 VecMultiplyLeft = Engine::Math::Matrix::CreateScale(2.f, 4.f).MultiplyLeft(Engine::Math::Vector4(2.f, 3.f, 3.f, 1.f));
	assert(VecMultiplyLeft == Engine::Math::Vector4(4.f, 12.f, 3.f, 1.f));

	//XRotation
	Engine::Math::Vector4 RotateVec(5.f, 3.f, 6.f, 9.f);
	RotateVec = RotateVec * Engine::Math::Matrix::CreateXRotation(0);
	assert(RotateVec == Engine::Math::Vector4(5.f, 3.f, 6.f, 9.f));

	//YRotation
	RotateVec = RotateVec * Engine::Math::Matrix::CreateYRotation(0);
	assert(RotateVec == Engine::Math::Vector4(5.f, 3.f, 6.f, 9.f));

	//ZRotation
	RotateVec = RotateVec * Engine::Math::Matrix::CreateZRotation(0);
	assert(RotateVec == Engine::Math::Vector4(5.f, 3.f, 6.f, 9.f));

	//Identity Matrix
	Engine::Math::Matrix IdentityTest = Engine::Math::Matrix::CreateIdentity();
	assert(IdentityTest == Engine::Math::Matrix::Identity);

	//Matrix Constructors
	Engine::Math::Matrix StandardMatrix(
		1.f, 3.f, 2.f, 0.f,
		2.f, 5.f, 0.f, 1.f,
		1.f, 1.f, 2.f, 7.f,
		3.f, 2.f, 0.f, 0.f
	);
	
	Engine::Math::Matrix CopiedMatrix(StandardMatrix);
	assert(CopiedMatrix == StandardMatrix);

	//Matrix Matrix Multiplication
	Engine::Math::Matrix MultMatrix = StandardMatrix * CopiedMatrix;
	assert(
		MultMatrix == Engine::Math::Matrix(
			9.f, 20.f, 6.f, 17.f,
			15.f, 33.f, 4.f, 5.f,
			26.f, 24.f, 6.f, 15.f,
			7.f, 19.f, 6.f, 2.f));

	//Matrix Transpose
	Engine::Math::Matrix TransposeMatrix = StandardMatrix.GetTranspose();
	assert(
		TransposeMatrix == Engine::Math::Matrix(
			1.f, 2.f, 1.f, 3.f,
			3.f, 5.f, 1.f, 2.f,
			2.f, 0.f, 2.f, 0.f,
			0.f, 1.f, 7.f, 0.f));

	CopiedMatrix.Transpose();
	assert(
		CopiedMatrix == Engine::Math::Matrix(
			1.f, 2.f, 1.f, 3.f,
			3.f, 5.f, 1.f, 2.f,
			2.f, 0.f, 2.f, 0.f,
			0.f, 1.f, 7.f, 0.f));

	//Matrix Inverse
	Engine::Math::Matrix InverseMatrix = StandardMatrix.GetInverse();
	assert(
		InverseMatrix == Engine::Math::Matrix(
			-0.0240963f, -0.1686746f, 0.0240963f, 0.4457831f,
			0.0361445f, 0.2530120f, -0.0361445f, -0.1686746f,
			0.4578313f, -0.2951807f, 0.0421686f, 0.0301204f,
			-0.1325301f, 0.0722891f, 0.1325301f, -0.0481927f));

	//Inverse of Transposed Matrix
	CopiedMatrix.Invert();
	assert(
		CopiedMatrix == Engine::Math::Matrix(
			-0.0240963f, 0.0361445f, 0.4578313f, -0.1325301f,
			-0.1686746f, 0.2530120f, -0.2951807f, 0.0722891f,
			0.0240963f, -0.0361445f, 0.0421686f, 0.1325301f,
			0.4457831f, -0.1686746f, 0.0301204f, -0.0481927f));

	DEBUG_PRINT("Vec4 Matrix Unit Test passed!\n\n");
	
	return true;
}

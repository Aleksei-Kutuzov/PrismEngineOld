#include "matrix.h"

void PRISM_Matrix_4X4::print()
{
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Matrix_4X4([[%f, %f, %f, %f],\n\t\t\t\t\t\t  [%f, %f, %f, %f],\n\t\t\t\t\t\t  [%f, %f, %f, %f],\n\t\t\t\t\t\t  [%f, %f, %f, %f]])",
		m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
}

PRISM_Matrix_4X4 Matrix_MakeIdentity()
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MakeRotationX(float fAngleRad)
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[1][2] = sinf(fAngleRad);
	matrix.m[2][1] = -sinf(fAngleRad);
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MakeRotationY(float fAngleRad)
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][2] = sinf(fAngleRad);
	matrix.m[2][0] = -sinf(fAngleRad);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MakeRotationZ(float fAngleRad)
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][1] = sinf(fAngleRad);
	matrix.m[1][0] = -sinf(fAngleRad);
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MakeTranslation(float x, float y, float z)
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	matrix.m[3][2] = z;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MakeScale(float x, float y, float z)
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = x;
	matrix.m[1][1] = y;
	matrix.m[2][2] = z;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
{
//	float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
	float fFovRad = fFovDegrees;
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = fAspectRatio * fFovRad;
	matrix.m[1][1] = fFovRad;
	matrix.m[2][2] = fFar / (fFar - fNear);
	matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return matrix;
}

PRISM_Matrix_4X4 Matrix_MultiplyMatrix(PRISM_Matrix_4X4 &m1, PRISM_Matrix_4X4 &m2)
{
	PRISM_Matrix_4X4 matrix;
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
	return matrix;
}

PRISM_Matrix_4X4 Matrix_PointAt(PRISM_Vector3d &pos, PRISM_Vector3d &target, PRISM_Vector3d &up)
{
	// Calculate new forward direction
	PRISM_Vector3d newForward = target - pos;
	newForward = Vector_Normalise(newForward);
	
	// Calculate new Up direction
	PRISM_Vector3d a = newForward * Vector_DotProduct(up, newForward);
	PRISM_Vector3d newUp = up - a;
	newUp = Vector_Normalise(newUp);
	
	// New Right direction is easy, its just cross product
	PRISM_Vector3d newRight = Vector_CrossProduct(newUp, newForward);
	
	// Construct Dimensioning and Translation Matrix	
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	return matrix;
	
}

PRISM_Matrix_4X4 Matrix_QuickInverse(PRISM_Matrix_4X4 &m) // Only for Rotation/Translation Matrices
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}
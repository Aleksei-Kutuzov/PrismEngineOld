#include "math.h"



float Math::degToRad(float degrees) {
	return degrees * (float)M_PI / 180.0f;
}

float Math::Vector_DotProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2)
{
	return v1.x * v2.x +
		v1.y * v2.y +
		v1.z * v2.z;
}

float Math::Vector_Length(PRISM_Vector3d& v)
{
	return sqrtf(Vector_DotProduct(v, v));
}

PRISM_Vector3d Math::Vector_Normalise(PRISM_Vector3d& v)
{
	float l = Vector_Length(v);
	return { v.x / l,
			 v.y / l,
			 v.z / l };
}

PRISM_Vector3d Math::Vector_CrossProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2)
{
	PRISM_Vector3d v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

PRISM_Vector3d Math::Vector_IntersectPlane(PRISM_Vector3d& plane_p, PRISM_Vector3d& plane_n, PRISM_Vector3d& lineStart, PRISM_Vector3d& lineEnd)
{
	plane_n = Vector_Normalise(plane_n);
	float plane_d = -Vector_DotProduct(plane_n, plane_p);
	float ad = Vector_DotProduct(lineStart, plane_n);
	float bd = Vector_DotProduct(lineEnd, plane_n);
	float t = (-plane_d - ad) / (bd - ad);
	PRISM_Vector3d lineStartToEnd = lineEnd - lineStart;
	PRISM_Vector3d lineToIntersect = lineStartToEnd * t;
	return lineStart + lineToIntersect;
}

PRISM_Matrix_4X4 Math::Matrix_MakeIdentity()
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Math::Matrix_MakeRotationX(float fAngleRad)
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

PRISM_Matrix_4X4 Math::Matrix_MakeRotationY(float fAngleRad)
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

PRISM_Matrix_4X4 Math::Matrix_MakeRotationZ(float fAngleRad)
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

PRISM_Matrix_4X4 Math::Matrix_MakeTranslation(float x, float y, float z)
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

PRISM_Matrix_4X4 Math::Matrix_MakeScale(float x, float y, float z)
{
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = x;
	matrix.m[1][1] = y;
	matrix.m[2][2] = z;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Math::Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
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

PRISM_Matrix_4X4 Math::Matrix_MultiplyMatrix(PRISM_Matrix_4X4& m1, PRISM_Matrix_4X4& m2)
{
	PRISM_Matrix_4X4 matrix;
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
	return matrix;
}

PRISM_Matrix_4X4 Math::Matrix_PointAt(PRISM_Vector3d& pos, PRISM_Vector3d& target, PRISM_Vector3d& up)
{
	// Calculate new forward direction
	PRISM_Vector3d newForward = target - pos;
	newForward = Math::Vector_Normalise(newForward);

	// Calculate new Up direction
	PRISM_Vector3d a = newForward * Math::Vector_DotProduct(up, newForward);
	PRISM_Vector3d newUp = up - a;
	newUp = Math::Vector_Normalise(newUp);

	// New Right direction is easy, its just cross product
	PRISM_Vector3d newRight = Math::Vector_CrossProduct(newUp, newForward);

	// Construct Dimensioning and Translation Matrix	
	PRISM_Matrix_4X4 matrix;
	matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	return matrix;
}

PRISM_Matrix_4X4 Math::Matrix_QuickInverse(PRISM_Matrix_4X4& m)
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

void Math::MultiplyMatrixVector(PRISM_Vector3d& i, PRISM_Vector3d& o, PRISM_Matrix_4X4& m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
}

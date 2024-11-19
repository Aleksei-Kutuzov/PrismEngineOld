#pragma once
#ifndef PRISM_MATH_H
#define PRISM_MATH_H


#include <vector>
#include <SDL_stdinc.h>
#include <SDL.h>
#include "vector3D.h"
#include "matrix.h"

class Math {
public:
	static float degToRad(float degrees);
	static float Vector_DotProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2);
	static float Vector_Length(PRISM_Vector3d& v);
	static PRISM_Vector3d Vector_Normalise(PRISM_Vector3d& v);
	static PRISM_Vector3d Vector_CrossProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2);
	static PRISM_Vector3d Vector_IntersectPlane(PRISM_Vector3d& plane_p, PRISM_Vector3d& plane_n, PRISM_Vector3d& lineStart, PRISM_Vector3d& lineEnd);
	static PRISM_Matrix_4X4 Matrix_MakeIdentity();
	static PRISM_Matrix_4X4 Matrix_MakeRotationX(float fAngleRad);
	static PRISM_Matrix_4X4 Matrix_MakeRotationY(float fAngleRad);
	static PRISM_Matrix_4X4 Matrix_MakeRotationZ(float fAngleRad);
	static PRISM_Matrix_4X4 Matrix_MakeTranslation(float x, float y, float z);
	static PRISM_Matrix_4X4 Matrix_MakeScale(float x, float y, float z);
	static PRISM_Matrix_4X4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
	static PRISM_Matrix_4X4 Matrix_MultiplyMatrix(PRISM_Matrix_4X4& m1, PRISM_Matrix_4X4& m2);
	static PRISM_Matrix_4X4 Matrix_PointAt(PRISM_Vector3d& pos, PRISM_Vector3d& target, PRISM_Vector3d& up);
	static PRISM_Matrix_4X4 Matrix_QuickInverse(PRISM_Matrix_4X4& m);
	static void MultiplyMatrixVector(PRISM_Vector3d& i, PRISM_Vector3d& o, PRISM_Matrix_4X4& m);
};

#endif // PRISM_MATH_H
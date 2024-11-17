#ifndef PRISM_MATRIX_H
#define PRISM_MATRIX_H

#include "vector3D.h"
#include <cmath>
#include <SDL.h>

struct PRISM_Matrix_4X4
{
	float m[4][4] = {0};
	void print();
};



PRISM_Matrix_4X4 Matrix_MakeIdentity();
PRISM_Matrix_4X4 Matrix_MakeRotationX(float fAngleRad);
PRISM_Matrix_4X4 Matrix_MakeRotationY(float fAngleRad);
PRISM_Matrix_4X4 Matrix_MakeRotationZ(float fAngleRad);
PRISM_Matrix_4X4 Matrix_MakeTranslation(float x, float y, float z);
PRISM_Matrix_4X4 Matrix_MakeScale(float x, float y, float z);
PRISM_Matrix_4X4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
PRISM_Matrix_4X4 Matrix_MultiplyMatrix(PRISM_Matrix_4X4 &m1, PRISM_Matrix_4X4 &m2);
PRISM_Matrix_4X4 Matrix_PointAt(PRISM_Vector3d &pos, PRISM_Vector3d &target, PRISM_Vector3d &up);
PRISM_Matrix_4X4 Matrix_QuickInverse(PRISM_Matrix_4X4 &m);




#endif // MATRIX_H
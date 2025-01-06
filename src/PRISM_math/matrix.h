#ifndef PRISM_MATRIX_H
#define PRISM_MATRIX_H

#include "vector3D.h"
#include <cmath>
#include <SDL.h>

struct PRISM_Matrix_4X4
{
	float m[4][4] = {0};
	void print();
	float* operator[](int index);
	bool operator==(PRISM_Matrix_4X4& other);

};


#endif // MATRIX_H
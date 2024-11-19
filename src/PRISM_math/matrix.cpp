#include "matrix.h"
#include "math.h"

void PRISM_Matrix_4X4::print()
{
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Matrix_4X4([[%f, %f, %f, %f],\n\t\t\t\t\t\t  [%f, %f, %f, %f],\n\t\t\t\t\t\t  [%f, %f, %f, %f],\n\t\t\t\t\t\t  [%f, %f, %f, %f]])",
		m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
}

float* PRISM_Matrix_4X4::operator[](int index)
{
	return m[index];
}

bool PRISM_Matrix_4X4::operator==(PRISM_Matrix_4X4& other)
{
	return m == other.m;
}

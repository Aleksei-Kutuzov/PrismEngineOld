#include <cmath>
#include "Vector3d.h"
#include <SDL.h>


void PRISM_Vector3d::print()
{
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Vector3d(%f, %f, %f, %f)", x, y, z, w);
}

PRISM_Vector3d PRISM_Vector3d::operator+(PRISM_Vector3d& other) {
	return { x + other.x,
			y + other.y,
			z + other.z };
}

PRISM_Vector3d PRISM_Vector3d::operator-(PRISM_Vector3d& other) {
	return { x - other.x,
			y - other.y,
			z - other.z };
}


PRISM_Vector3d PRISM_Vector3d::operator*(float k)
{
	return { x * k,
			y * k,
			z * k };
}

PRISM_Vector3d PRISM_Vector3d::operator/(float k)
{
	return { x / k,
			y / k,
			z / k };
}

float PRISM_Vector3d::operator[](int index) {
	if (index == 0) return x;
	else if (index == 1) return y;
	else if (index == 2) return z;
	else if (index == 3) return w;
	else return -1.0f;
}

bool PRISM_Vector3d::operator==(PRISM_Vector3d& other) {
	if (other.x == x && other.y == y && other.z == z) {
		return true;
	}
	return false;
}
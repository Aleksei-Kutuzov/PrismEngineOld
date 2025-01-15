#include <cmath>
#include "Vector3d.h"
#include <SDL.h>
#include <stdexcept>


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
	if (k == 0) { throw std::invalid_argument("Division by zero is not allowed."); }
	return { x / k,
			y / k,
			z / k };
}

float PRISM_Vector3d::operator[](int index) {
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		throw std::out_of_range("Index out of range. Valid indices are 0, 1, 2, 3.");
	}
}

bool PRISM_Vector3d::operator==(PRISM_Vector3d& other) {
	if (other.x == x && other.y == y && other.z == z) {
		return true;
	}
	return false;
}
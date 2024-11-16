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

float Vector_DotProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2)
{
	return v1.x * v2.x +
		v1.y * v2.y +
		v1.z * v2.z;
}

float Vector_Length(PRISM_Vector3d& v)
{
	return sqrtf(Vector_DotProduct(v, v));
}

PRISM_Vector3d Vector_Normalise(PRISM_Vector3d& v)
{
	float l = Vector_Length(v);
	return { v.x / l,
			 v.y / l,
			 v.z / l };
}

PRISM_Vector3d Vector_CrossProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2)
{
	PRISM_Vector3d v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

PRISM_Vector3d Vector_IntersectPlane(PRISM_Vector3d& plane_p, PRISM_Vector3d& plane_n, PRISM_Vector3d& lineStart, PRISM_Vector3d& lineEnd)
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
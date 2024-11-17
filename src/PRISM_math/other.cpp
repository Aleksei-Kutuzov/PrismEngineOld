// Created by Alexey on 15.09.2024.
//
#include <cmath>
#include "other.h"



inline float Math::degToRad(float degrees) {
	return degrees * M_PI / 180.0f;
}

void PRISM_Triangle::print() {
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Triangle(a:(%f, %f, %f, %f),\n\t\t\t\t\t       b:(%f, %f, %f, %f)\n\t\t\t\t\t       c:(%f, %f, %f, %f))",
		a.x, a.y, a.z, a.w, b.x, b.y, b.z, b.w, c.x, c.y, c.z, c.w);
}

void PRISM_Mesh::print() {
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Mesh(tris.size: %d)", tris.size());
}

void PRISM_Color::print() {
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Color(r: %d, g: %d, b: %d, a: %d)", r, g, b, a);
}

void PRISM_Light::print() {
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_Light(position: %d, %d, %d, %d\n\t\t\t\t\t    color: %d, %d, %d, %d)",
		position.x, position.y, position.z, position.w, color.r, color.g, color.b, color.a);
}

void PRISM_RenderMode::print() {
	SDL_Log("PRISM_ENGINE::PRISM_math::PRISM_RenderMode(boolFlags: |%d|%d|%d|%d|%d|%d|, ContourWidth: %d)",
		DisplayDimming1, DisplayDimming2, DisplayTriangleContours, Z_Buffer, ShowBackMesh, FillMesh, ContourWidth);
}

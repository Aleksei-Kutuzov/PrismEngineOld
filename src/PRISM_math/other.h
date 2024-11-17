#ifndef OTHER_H
#define OTHER_H


#include "vector3D.h"
#include <vector>
#include <SDL_stdinc.h>
#include <SDL.h>

class Math {
	public:
		float degToRad(float degrees);
};

struct PRISM_Triangle
{
	PRISM_Vector3d a;
	PRISM_Vector3d b;
	PRISM_Vector3d c;
	PRISM_Triangle(PRISM_Vector3d a_ = {0.0f, 0.0f, 0.0f}, PRISM_Vector3d b_ = {0.0f, 0.0f, 0.0f}, PRISM_Vector3d c_ = {0.0f, 0.0f, 0.0f}) : a(a_), b(b_), c(c_) {}
	void print();
};

struct PRISM_Mesh
{
	std::vector<PRISM_Triangle> tris;
	void print();
};


struct PRISM_Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a=255;
	void print();
};

struct PRISM_Light {
	PRISM_Vector3d position;
	PRISM_Color color = {255, 255, 255};
	void print();
};

struct PRISM_RenderMode {
	bool DisplayDimming1 = true; //затемнения
	bool DisplayDimming2 = false; //затемнения
	bool DisplayTriangleContours = false; //контуры
	bool Z_Buffer = true;
	bool ShowBackMesh = false;
	bool FillMesh = true;
	int ContourWidth = 5;
	void print();
};


void save_texture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture);

#endif // OTHER_H
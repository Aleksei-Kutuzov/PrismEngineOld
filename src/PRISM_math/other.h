#ifndef OTHER_H
#define OTHER_H


#include "vector3D.h"
#include <vector>
#include <SDL_stdinc.h>
#include <SDL.h>


struct PRISM_Triangle
{
	PRISM_Vector3d a;
	PRISM_Vector3d b;
	PRISM_Vector3d c;
	PRISM_Vector3d a_norlmal = { 0, 0, 0, 0 }; //нормаль точки a треугольника если w == 1 то она есть
	PRISM_Vector3d b_norlmal = { 0, 0, 0, 0 }; //нормаль точки b треугольника если w == 1 то она есть
	PRISM_Vector3d c_norlmal = { 0, 0, 0, 0 }; //нормаль точки c треугольника если w == 1 то она есть
	PRISM_Triangle(PRISM_Vector3d a_ = {0.0f, 0.0f, 0.0f}, PRISM_Vector3d b_ = {0.0f, 0.0f, 0.0f}, PRISM_Vector3d c_ = {0.0f, 0.0f, 0.0f}) : a(a_), b(b_), c(c_) {}
	void print();
};

struct PRISM_Mesh
{
	std::vector<PRISM_Triangle> tris;
	void print();
};


struct PRISM_Color {
	unsigned char r=0;
	unsigned char g=0;
	unsigned char b=0;
	unsigned char a=255;
	void print();
	PRISM_Color(unsigned char r, unsigned char g, unsigned char b) { this->r = r;  this->g = g; this->b = b; this->a = 255; }
	PRISM_Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { this->r = r;  this->g = g; this->b = b; this->a = a; }
	PRISM_Color(float r, float g, float b) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = 255; }
	PRISM_Color(float r, float g, float b, float a) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = (unsigned char)a; }
	PRISM_Color(int r, int g, int b) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = 255; }
	PRISM_Color(int r, int g, int b, int a) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = (unsigned char)a; }
	PRISM_Color() { this->r = 0;  this->g = 0; this->b = 0, this->a = 255; }
};

struct PRISM_GL_fColor {
	float r=0;
	float g=0;
	float b=0;
};

struct PRISM_Light {
	PRISM_Vector3d position;
	PRISM_Color color = {255, 255, 255};
	float lightIntensity = 1.0f;          // Интенсивность света
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
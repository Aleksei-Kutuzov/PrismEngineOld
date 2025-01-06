#ifndef PRISM_PAINTER_H
#define PRISM_PAINTER_H

#include "SDL.h"
#include "PRISM_Window.h"
#include "../PRISM_math/other.h"

class PRISM_Painter
{
public:
	
	static void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
	static void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
							 SDL_Renderer* SDL_renderer, short rgba[4], int thickness);

	static void DrawPoint(PRISM_Window* window, int x, int y);
	static void DrawPoint(PRISM_Window* window, int x, int y, int r, int g, int b);
	
	static void DrawThickLine(PRISM_Window* window, int x1, int y1, int x2, int y2, int thickness);
	static void DrawThickLine(PRISM_Window* window, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b);

	static void DrawTriangle(PRISM_Window* window, int x1, int y1, int x2, int y2, int x3, int y3);
	static void DrawTriangle(PRISM_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b);

	static void DrawRectangle(PRISM_Window* window, int x1, int y1, int x2, int y2);
	static void DrawRectangle(PRISM_Window* window, int x1, int y1, int x2, int y2, int r, int g, int b);
	
	static void DrawTriangle3D(PRISM_Window* window, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float r, float g, float b);
	static void DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, float r, float g, float b);
	static void DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, PRISM_Color color);
private:

};



#endif //PRISM_PAINTER_H
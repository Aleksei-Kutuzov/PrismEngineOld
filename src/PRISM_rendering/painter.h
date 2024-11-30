#ifndef PRISM_PAINTER_H
#define PRISM_PAINTER_H

#include "SDL.h"

class PRISM_Painter
{
public:
	static void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
	static void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
							 SDL_Renderer* SDL_renderer, short rgba[4], int thickness);
private:

};



#endif //PRISM_PAINTER_H
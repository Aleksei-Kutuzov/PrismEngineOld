#include "painter.h"

void PRISM_Painter::DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness) {
	// Вычисление разности координат
	int dx = x2 - x1;
	int dy = y2 - y1;

	// Вычисление нормализованного вектора перпендикулярного линии
	float length = (float)sqrtf(dx * dx + dy * dy);
	float nx = -dy / length;
	float ny = dx / length;

	// Рисование параллельных линий
	for (int i = -thickness / 2; i <= thickness / 2; ++i) {
		int offsetX = (int)(nx * i);
		int offsetY = (int)(ny * i);
		SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
	}
}

void PRISM_Painter::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Renderer* SDL_renderer,
	short rgba[4], int thickness = 1) {
	SDL_SetRenderDrawColor(SDL_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
	DrawThickLine(SDL_renderer, x1, y1, x2, y2, thickness);
	DrawThickLine(SDL_renderer, x2, y2, x3, y3, thickness);
	DrawThickLine(SDL_renderer, x3, y3, x1, y1, thickness);
}
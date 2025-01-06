#include "painter.h"
#include "../PRISM_math/math.h"





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

void PRISM_Painter::DrawPoint(PRISM_Window* window, int x, int y)
{
	if (!window->isRunning()) {
		return;
	}

	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
	
	//отображаем поверх
	glDepthFunc(GL_ALWAYS);

	//начало
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	//конец
	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}

void PRISM_Painter::DrawPoint(PRISM_Window* window, int x, int y, int r, int g, int b)
{
	if (!window->isRunning()) {
		return;
	}
	
	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
	//отображаем поверх
	glDepthFunc(GL_ALWAYS);
	//начало
	glBegin(GL_POINTS);
	//цвет
	glColor3f(r, g, b);

	glVertex2f(x, y);
	//конец
	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}


void PRISM_Painter::DrawThickLine(PRISM_Window* window, int x1, int y1, int x2, int y2, int thickness)
{
	if (!window->isRunning()) {
		return;
	}

	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	//отображаем поверх
	glDepthFunc(GL_ALWAYS);
	// задаём ширину
	glLineWidth(thickness);

	//начало
	glBegin(GL_LINES);
	glVertex2f(x1, y1); // Начальная точка линии
	glVertex2f(x2, y2);  // Конечная точка линии
	//конец
	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
	
}

void PRISM_Painter::DrawThickLine(PRISM_Window* window, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b)
{
	if (!window->isRunning()) {
		return;
	}

	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	//отображаем поверх
	glDepthFunc(GL_ALWAYS);
	// задаём ширину
	glLineWidth(thickness);

	//начало
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex2f(x1, y1); // Начальная точка линии
	glVertex2f(x2, y2);  // Конечная точка линии
	//конец
	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}

void PRISM_Painter::DrawTriangle(PRISM_Window* window, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	//отображаем поверх
	glDepthFunc(GL_ALWAYS);

	// Рисуем 2D-треугольник
	glBegin(GL_TRIANGLES);

	// Вершина 1
	glVertex2f(x1, y1);

	// Вершина 2
	glVertex2f(x2, y2);

	// Вершина 3
	glVertex2f(x3, y3);

	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}

void PRISM_Painter::DrawTriangle(PRISM_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	//отображаем поверх
	glDepthFunc(GL_ALWAYS);

	// Рисуем 2D-треугольник
	glBegin(GL_TRIANGLES);

	// Вершина 1
	glColor3f(r, g, b);
	glVertex2f(x1, y1);

	// Вершина 2
	glColor3f(r, g, b);
	glVertex2f(x2, y2);

	// Вершина 3
	glColor3f(r, g, b);
	glVertex2f(x3, y3);

	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}

void PRISM_Painter::DrawRectangle(PRISM_Window* window, int x1, int y1, int x2, int y2)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	//отображаем поверх
	glDepthFunc(GL_ALWAYS);
	
	// Рисуем 2D-квадрат
	glBegin(GL_QUADS);

	// верхний левый
	glVertex2f(x1, y1);

	// верхний правый
	glVertex2f(x2, y1);

	// нижний правый
	glVertex2f(x2, y2);

	// нижний левый
	glVertex2f(x1, y2);

	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}

void PRISM_Painter::DrawRectangle(PRISM_Window* window, int x1, int y1, int x2, int y2, int r, int g, int b)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	//отображаем поверх
	glDepthFunc(GL_ALWAYS);

	// Рисуем 2D-квадрат
	glBegin(GL_QUADS);

	//цвет
	glColor3f(r, g, b);

	// верхний левый
	glVertex2f(x1, y1);

	// верхний правый
	glVertex2f(x2, y1);

	// нижний правый
	glVertex2f(x2, y2);

	// нижний левый
	glVertex2f(x1, y2);

	glEnd();
	//возврат режима глубин
	glDepthFunc(GL_LESS);
}

void PRISM_Painter::DrawTriangle3D(PRISM_Window* window,
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float r, float g, float b) {
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
	
	// Рисуем 3D-треугольник
	glBegin(GL_TRIANGLES);

	// Вершина 1
	glColor3f(r, g, b);
	glVertex3f(x1, y1, z1);

	// Вершина 2
	glColor3f(r, g, b);
	glVertex3f(x2, y2, z2);

	// Вершина 3
	glColor3f(r, g, b);
	glVertex3f(x3, y3, z3);

	glEnd();

}

void PRISM_Painter::DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, float r, float g, float b)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Рисуем 3D-треугольник
	glBegin(GL_TRIANGLES);

	// Вершина 1
	glColor3f(r, g, b);
	glVertex3f(triangle.a.x, triangle.a.y, triangle.a.z);

	// Вершина 2
	glColor3f(r, g, b);
	glVertex3f(triangle.b.x, triangle.b.y, triangle.b.z);

	// Вершина 3
	glColor3f(r, g, b);
	glVertex3f(triangle.c.x, triangle.c.y, triangle.c.z);

	glEnd();
}

void PRISM_Painter::DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, PRISM_Color color)
{
	if (!window || !window->isRunning()) {
		return;
	}

	PRISM_GL_fColor gl_color = Math::convertToGlColor(color);

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Рисуем 3D-треугольник
	glBegin(GL_TRIANGLES);

	// Вершина 1
	glColor3f(gl_color.r, gl_color.g, gl_color.b);
	glVertex3f(triangle.a.x, triangle.a.y, triangle.a.z);

	// Вершина 2
	glColor3f(gl_color.r, gl_color.g, gl_color.b);
	glVertex3f(triangle.b.x, triangle.b.y, triangle.b.z);

	// Вершина 3
	glColor3f(gl_color.r, gl_color.g, gl_color.b);
	glVertex3f(triangle.c.x, triangle.c.y, triangle.c.z);
	
	//DrawThickLine(window, triangle.a.x, triangle.a.y, triangle.b.x, triangle.b.y, 2, 0, 255, 0);
	//DrawThickLine(window, triangle.b.x, triangle.b.y, triangle.c.x, triangle.c.y, 2, 0, 255, 0);
	//DrawThickLine(window, triangle.c.x, triangle.c.y, triangle.a.x, triangle.a.y, 2, 0, 255, 0);

	glEnd();
}

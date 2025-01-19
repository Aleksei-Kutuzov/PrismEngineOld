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

void PRISM_Painter::DrawPoint(PRISM_Window* window, float x, float y)
{
	if (!window->isRunning()) {
		return;
	}

	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
	
	// Координаты и цвет точки
	float pointVertices[] = {
		// Координаты         // Цвет
		x, y, 0.0f,           1.0f, 1.0f, 1.0f  // Одна точка
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);

	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else {
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STREAM_DRAW);

	// Позиция точки
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет точки
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Установка размера точки
	glPointSize(2.0f); // Размер точки в пикселях

	// Рисуем точку
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_POINTS, 0, 1); // Указываем 1 вершину для точки
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawPoint(PRISM_Window* window, float x, float y, int r, int g, int b)
{
	if (!window->isRunning()) {
		return;
	}
	
	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
	
	// Преобразовываем из RGB 0-255 в RGB 0-1
	PRISM_GL_fColor color = Math::convertToGlColor({r, g, b});

	// Координаты и цвет точки
	float pointVertices[] = {
		// Координаты         // Цвет
		x, y, 0.0f,           color.r, color.g, color.b  // Одна точка
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);

	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else {
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STREAM_DRAW);

	// Позиция точки
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет точки
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Установка размера точки
	glPointSize(2.0f); // Размер точки в пикселях

	// Рисуем точку
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_POINTS, 0, 1); // Указываем 1 вершину для точки
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);

}


void PRISM_Painter::DrawThickLine(PRISM_Window* window, float x1, float y1, float x2, float y2, int thickness)
{
	if (!window->isRunning()) {
		return;
	}

	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Координаты вершин и цвета для линии (две точки)
	float lineVertices[] = {
		// Координаты         // Цвета
		x1, y1, 0.0f,   1.0f, 1.0f, 1.0f, // Начальная точка линии
		x2, y2, 0.0f,   1.0f, 1.0f, 1.0f  // Конечная точка линии
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);

	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else {
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Установка толщины линии
	glLineWidth(thickness); // Задаём толщину линии 5 пикселей
	
	// Рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_LINES, 0, 2); // Указываем 2 вершины для линии
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawThickLine(PRISM_Window* window, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b)
{
	if (!window->isRunning()) {
		return;
	}

	// переключаем контекст OpenGL окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Преобразовываем из RGB 0-255 в RGB 0-1
	PRISM_GL_fColor color = Math::convertToGlColor({ r, g, b });
	
	// Координаты вершин и цвета для линии (две точки)
	float lineVertices[] = {
		// Координаты         // Цвета
		x1, y1, 0.0f,   color.r, color.g, color.b, // Начальная точка линии
		x2, y2, 0.0f,   color.r, color.g, color.b  // Конечная точка линии
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);

	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else {
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Установка толщины линии
	glLineWidth(thickness); // Задаём толщину линии 5 пикселей

	// Рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_LINES, 0, 2); // Указываем 2 вершины для линии
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawTriangle(PRISM_Window* window, float x1, float y1, float x2, float y2, float x3, float y3)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL - контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	float vertices[] = {
        // Координаты         // Цвета
         x1, y1, 0.0f,   1.0f, 0.0f, 0.0f, // Верхняя вершина (красный)
         x2, y2, 0.0f,   0.0f, 1.0f, 0.0f, // Левая вершина (зеленый)
         x3, y3, 0.0f,   0.0f, 0.0f, 1.0f  // Правая вершина (синий)
    };

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);
	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else
	{
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawTriangle(PRISM_Window* window, float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL - контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Преобразовываем из RGB 0-255 в RGB 0-1
	PRISM_GL_fColor color = Math::convertToGlColor({ r, g, b });

	float vertices[] = {
        // Координаты         // Цвета
         x1, y1, 0.f,   color.r, color.g, color.b, // Верхняя вершина (красный)
		 x2, y2, 0.f,   color.r, color.g, color.b, // Левая вершина (зеленый)
         x3, y3, 0.0f,  color.r, color.g, color.b  // Правая вершина (синий)
    };

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);
	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else
	{
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawRectangle(PRISM_Window* window, float x1, float y1, float x2, float y2)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	float r = 1.0f; float g = 1.0f; float b = 1.0f;

	// Координаты вершин и цвета для прямоугольника (два треугольника)
	float vertices[] = {
		// Координаты         // Цвета
		x1, y1, 0.0f,   r, g, b, // Верхний левый угол
		x1, y2, 0.0f,   r, g, b, // Нижний левый угол
		x2, y2, 0.0f,   r, g, b, // Нижний правый угол

		x1, y1, 0.0f,   r, g, b, // Верхний левый угол
		x2, y2, 0.0f,   r, g, b, // Нижний правый угол
		x2, y1, 0.0f,   r, g, b  // Верхний правый угол
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);

	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else {
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_TRIANGLES, 0, 6); // Указываем 6 вершин для прямоугольника
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);

}

void PRISM_Painter::DrawRectangle(PRISM_Window* window, float x1, float y1, float x2, float y2, int r, int g, int b)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Преобразовываем из RGB 0-255 в RGB 0-1
	PRISM_GL_fColor color = Math::convertToGlColor({ r, g, b });

	// Координаты вершин и цвета для прямоугольника (два треугольника)
	float vertices[] = {
		// Координаты         // Цвета
		x1, y1, 0.0f,   color.r, color.g, color.b, // Верхний левый угол
		x1, y2, 0.0f,   color.r, color.g, color.b, // Нижний левый угол
		x2, y2, 0.0f,   color.r, color.g, color.b, // Нижний правый угол

		x1, y1, 0.0f,   color.r, color.g, color.b, // Верхний левый угол
		x2, y2, 0.0f,   color.r, color.g, color.b, // Нижний правый угол
		x2, y1, 0.0f,   color.r, color.g, color.b  // Верхний правый угол
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);

	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else {
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	glDepthFunc(GL_ALWAYS); // Рисуем поверх
	glDrawArrays(GL_TRIANGLES, 0, 6); // Указываем 6 вершин для прямоугольника
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawTriangle3D(PRISM_Window* window,
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	int r, int g, int b) {
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
	
	// Преобразовываем из RGB 0-255 в RGB 0-1
	PRISM_GL_fColor color = Math::convertToGlColor({ r, g, b });

	float vertices[] = {
		// Координаты         // Цвета
		 x1, y1, z1, color.r, color.g, color.b, // Верхняя вершина (красный)
		 x2, y2, z2, color.r, color.g, color.b, // Левая вершина (зеленый)
		 x3, y3, z3, color.r, color.g, color.b  // Правая вершина (синий)
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);
	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else
	{
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);
	
	//Z буфер
	glDepthFunc(GL_LESS);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	

	glBindVertexArray(0);
	glUseProgram(0);

}

void PRISM_Painter::DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, int r, int g, int b)
{
	if (!window || !window->isRunning()) {
		return;
	}

	// Активируем OpenGL-контекст окна
	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Преобразовываем из RGB 0-255 в RGB 0-1
	PRISM_GL_fColor color = Math::convertToGlColor({ r, g, b });

	float vertices[] = {
		// Координаты         // Цвета
		 triangle.a.x, triangle.a.y, triangle.a.z, color.r, color.g, color.b, // Верхняя вершина (красный)
		 triangle.b.x, triangle.b.y, triangle.b.z, color.r, color.g, color.b, // Левая вершина (зеленый)
		 triangle.c.x, triangle.c.y, triangle.c.z, color.r, color.g, color.b  // Правая вершина (синий)
	};

	GLuint VBO;
	glGenVertexArrays(1, &window->shaderManager.VAO);
	glGenBuffers(1, &VBO);
	if (window->shaderManager.shaderIsActive) {
		glBindVertexArray(window->shaderManager.VAO);
	}
	else
	{
		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	// Позиция вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цвет вершин
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//рисуем
	glUseProgram(window->shaderManager.shaderProgram);
	glBindVertexArray(window->shaderManager.VAO);

	//Z буфер
	glDepthFunc(GL_LESS);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	glBindVertexArray(0);
	glUseProgram(0);
}

void PRISM_Painter::DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, PRISM_Color color) {
	if (!window || !window->isRunning()) {
		return;
	}

	PRISM_GL_fColor gl_color = Math::convertToGlColor(color);

	SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());

	// Инициализация VAO и VBO, если они ещё не созданы
	if (window->shaderManager.VAO == 0 || window->shaderManager.VBO == 0) {
		glGenVertexArrays(1, &window->shaderManager.VAO);
		glGenBuffers(1, &window->shaderManager.VBO);

		glBindVertexArray(window->shaderManager.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, window->shaderManager.VBO);

		// Резервируем память под буфер
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, nullptr, GL_DYNAMIC_DRAW);

		// Позиция вершин
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Цвет вершин
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// Данные для треугольника
	float vertices[] = {
		triangle.a.x, triangle.a.y, triangle.a.z, gl_color.r, gl_color.g, gl_color.b,
		triangle.b.x, triangle.b.y, triangle.b.z, gl_color.r, gl_color.g, gl_color.b,
		triangle.c.x, triangle.c.y, triangle.c.z, gl_color.r, gl_color.g, gl_color.b
	};

	// Обновляем только содержимое буфера
	glBindBuffer(GL_ARRAY_BUFFER, window->shaderManager.VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glBindVertexArray(window->shaderManager.VAO);

	glUseProgram(window->shaderManager.shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

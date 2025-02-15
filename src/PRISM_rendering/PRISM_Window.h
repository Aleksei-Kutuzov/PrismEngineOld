#pragma once
#include <string>
#include "GL\glew.h"
#include "GL/freeglut.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "shaderManager.h"

#ifndef GL_MULTISAMPLE 
#define GL_MULTISAMPLE 0x809D // включаем сглаживание
#endif


/// <summary>
/// Класс, представляющий окно PRISM_ENDINE.
/// </summary>
class PRISM_Window
{
public:
	/// <summary>
	/// Конструктор окна PRISM_Window.
	/// </summary>
	/// <param name="w">Ширина окна.</param>
	/// <param name="h">Высота окна.</param>
	/// <param name="title">Заголовок окна.</param>
	PRISM_Window(int w, int h, const char* title);

	PRISM_Window(int width, int height, const char* title, const char* vertexShaderSource, const char* fragmentShaderSource);

	/// <summary>
	/// Указывает, выполняется ли приложение.
	/// </summary>
	bool running;

	/// <summary>
	/// Деструктор окна PRISM_Window.
	/// Освобождает выделенные ресурсы.
	/// </summary>
	~PRISM_Window();

	/// <summary>
	/// Проверяет, выполняется ли приложение.
	/// </summary>
	/// <returns>Возвращает true, если приложение активно, иначе false.</returns>
	bool isRunning() const { return running; }
	
	/// <summary>
	/// Возвращяет контекст SDL_Window.
	/// </summary>
	/// <returns>Указатель на объект SDL_Window.</returns>
	SDL_Window* GetSDLWindow() const {	return window;}
	
	/// <summary>
	/// Получает текущий OpenGL-контекст.
	/// </summary>
	/// <returns>Контекст SDL_GLContext.</returns>
	SDL_GLContext GetGLContext() const { return glContext; }

	/// <summary>
	/// Обрабатывает события окна (например, ввод с клавиатуры или мыши).
	/// </summary>
	void handleEvents();

	/// <summary>
	/// Обрабатывает события окна (например, ввод с клавиатуры или мыши) как handleEvents() но принимает функцию которая будет вызываться в момент события.
	/// <param name="event_foo">Функция принимающая событие</param>
	/// </summary>
	void handleEvents(void(*event_foo)(SDL_Event));

	
	/// <summary>
	/// Обновляет содержимое окна.
	/// </summary>
	void update();

	/// <summary>
	/// Очищает содержимое окна.
	/// </summary>
	void clear();

	/// <summary>
	/// Освобождает ресурсы и завершает работу окна.
	/// </summary>
	void cleanUp();

	/// <summary>
	/// Получает заголовок окна.
	/// </summary>
	/// <returns>Строка с текущим заголовком окна.</returns>
	const char* GetTitle();

	/// <summary>
	/// Устанавливает новый заголовок окна.
	/// </summary>
	/// <param name="title">Новый заголовок окна.</param>
	void SetTitle(const char*);

	/// <summary>
	/// Устанавливает новый заголовок окна с использованием строки std::string.
	/// </summary>
	/// <param name="t">Строка std::string с новым заголовком окна.</param>
	void SetTitle(const std::string& t);

	/// <summary>
	/// Получает текущую позицию окна по оси X.
	/// </summary>
	/// <returns>Координата X окна.</returns>
	int GetX() const { return x; }
	
	/// <summary>
	/// Получает текущую позицию окна по оси Y.
	/// </summary>
	/// <returns>Координата Y окна.</returns>
	int GetY() const { return y; }
	
	/// <summary>
	/// Получает текущую ширину окна.
	/// </summary>
	/// <returns>Ширина окна.</returns>
	int GetW() const { return w; }
	
	/// <summary>
	/// Получает текущую высоту окна.
	/// </summary>
	/// <returns>Высота окна.</returns>
	int GetH() const { return h; }

	/// <summary>
	/// Класс управления шейдерами.
	/// </summary>
	ShaderManager shaderManager;

private:
	/// <summary>
	/// Координата X окна.
	/// </summary>
	int x;

	/// <summary>
	/// Координата Y окна.
	/// </summary>
	int y;

	/// <summary>
	/// Ширина окна.
	/// </summary>
	int w;

	/// <summary>
	/// Высота окна.
	/// </summary>
	int h;

	/// <summary>
	/// Указатель на объект SDL_Window.
	/// </summary>
	SDL_Window* window;

	/// <summary>
	/// Контекст OpenGL для отрисовки.
	/// </summary>
	SDL_GLContext glContext;
};
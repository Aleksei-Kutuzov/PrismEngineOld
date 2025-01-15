#pragma once
#include <string>
#include "GL\glew.h"
#include "GL/freeglut.h"
#include "SDL.h"
#include "SDL_opengl.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

class PRISM_Window
{
public:
	PRISM_Window(int w, int h, const char* title);
	bool running;
	~PRISM_Window();


	bool isRunning() const { return running; }
	SDL_Window* GetSDLWindow() const {	return window;}
	SDL_GLContext GetGLContext() const { return glContext; }
	void handleEvents();
	
	void update();
	void clear();

	void cleanUp();

	const char* GetTitle();
	void SetTitle(const char*);

	void SetTitle(const std::string& t);

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetW() const { return w; }
	int GetH() const { return h; }

private:
	int x, y, w, h;
	SDL_Window* window;
	SDL_GLContext glContext;

	GLuint shaderProgram;
	GLuint VAO;
};
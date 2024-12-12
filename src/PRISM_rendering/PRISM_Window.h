#pragma once
#include "GL/freeglut.h"
#include "SDL.h"

class PRISM_Window
{
public:
	PRISM_Window(int w, int h, const char* title);
	~PRISM_Window();


	bool isRunning() const { return running; }
	void handleEvents();
	void render();
	void cleanUp();

private:
	int x, y, w, h;
	bool running;
	SDL_Window* window;
	SDL_GLContext glContext;
};

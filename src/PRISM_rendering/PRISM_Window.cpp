#include "PRISM_Window.h"



PRISM_Window::PRISM_Window(int width, int height, const char* title)
                  : window(nullptr), glContext(nullptr), running(true)
{
    // ������������� SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
        running = false;
        return;
    }

    // �������� ���� � ���������� OpenGL
    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Window could not be created! SDL_Error: %s", SDL_GetError());
        running = false;
        return;
    }

    // �������� ��������� OpenGL
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "OpenGL context could not be created! SDL_Error: %s", SDL_GetError());
        running = false;
        return;
    }

    // ������������� OpenGL ����� freeGLUT (�������������, �� ������� ��� ����������� ������������)
    int argc = 0;
    glutInit(&argc, nullptr);

    // ��������� OpenGL (��������, ��� ������������� �������)
    glEnable(GL_DEPTH_TEST);

    SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "Window created successfully, OpenGL context initialized.");

}

PRISM_Window::~PRISM_Window()
{
    cleanUp();
}

void PRISM_Window::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }
}

void PRISM_Window::render() {
    // ������� ������
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ������� �����������
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // �������
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f); // �������
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f); // �����
    glVertex2f(0.0f, 0.5f);
    glEnd();

    // ���������� ������
    SDL_GL_SwapWindow(window);

    SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "Frame rendered successfully.");
}

void PRISM_Window::cleanUp() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
        SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "OpenGL context deleted.");
    }
    if (window) {
        SDL_DestroyWindow(window);
        SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "Window destroyed.");
    }
    SDL_Quit();
}
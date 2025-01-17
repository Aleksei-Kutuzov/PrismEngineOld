#include "PRISM_Window.h"




PRISM_Window::PRISM_Window(int width, int height, const char* title)
                  : window(nullptr), glContext(nullptr), running(true)
{
    this->w = width;
    this->h = height;
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
        running = false;
        return;
    }

    // Установка кодировки UTF-8
    if (!SDL_SetHint(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, "1") ||
        !SDL_SetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER, "d3dcompiler_47.dll") ||
        !SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1") ||
        !SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0") ||
        !SDL_SetHint(SDL_HINT_VIDEO_X11_XRANDR, "1")) {
        SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "Failed to set SDL hints!");
    }
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);  // Количество сэмплов (4x MSAA)


    SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "SDL initialized successfully.");

    // Создание окна с поддержкой OpenGL
    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Window could not be created! SDL_Error: %s", SDL_GetError());
        running = false;
        return;
    }

    // Создание контекста OpenGL
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "OpenGL context could not be created! SDL_Error: %s", SDL_GetError());
        running = false;
        return;
    }

    // Инициализация OpenGL через freeGLUT (необязательно, но полезно для расширенных возможностей)
    int argc = 0;
    glutInit(&argc, nullptr);

    // Настройка OpenGL (например, для использования глубины)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Инициализация GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_Log("Failed to initialize GLEW!");
        return ;
    }

    SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "Window created successfully, OpenGL context initialized.");
    SDL_LogInfo(SDL_LOG_PRIORITY_INFO, (char*)glGetString(GL_VERSION));
    //glEnable(GL_MULTISAMPLE); не все версии поддерживают версиях

    // Настройка ортографической проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    // Сброс модели
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Устанавливаем единичную модельно-видовую матрицу
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

const char* PRISM_Window::GetTitle() {
    return SDL_GetWindowTitle(window);
}

void PRISM_Window::SetTitle(const char* t)
{
    SDL_SetWindowTitle(window, t);
}

void PRISM_Window::SetTitle(const std::string& t) {
    SDL_SetWindowTitle(window, t.c_str());
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
        else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            int newWidth = e.window.data1;
            int newHeight = e.window.data2;

            // Обновляем видовой порт и проекцию
            glViewport(0, 0, newWidth, newHeight);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, -1, 1);  // если надо как в SDL glOrtho(0, newWidth, newHeight, 0, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            w = newWidth; h = newHeight;
        }
    }
}



void PRISM_Window::update() {


    // Обновление экрана
    SDL_GL_SwapWindow(window);

    SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "Frame rendered successfully.");
}

void PRISM_Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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


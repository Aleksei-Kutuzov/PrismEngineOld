#include "src/PrismEngine.h"

static int test_2() {
    // Создаем окно
    PRISM_Window window(600, 400, u8"♦PRISME♦|TEST 2");

    // Проверяем, удалось ли создать окно
    if (!window.isRunning()) {
        return -1;
    }

    Scene scene;
    AbstractCamera3D MainCamera(0.1, 1000.0f, 90.0f, window.GetW(), window.GetH());
    MainCamera.SetPosition({ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 1 });

    AbstractObject3D planet{ {0, 0, 2}, {0, 0, 0}, {1, 1, 1}, MainCamera };
    planet.SetMesh(MeshLoader::LoadOBJ("test_res/objs/Planet.obj", MainCamera));

    AbstractObject3D spase{ {2, 0, 1}, {0, -90, 0}, {0.1, 0.1, 0.1}, MainCamera };
    spase.SetMesh(MeshLoader::LoadOBJ("test_res/objs/Tesla Laser.obj", MainCamera));

    scene.AddObject(&planet);
    scene.AddObject(&spase);
    scene.SetCamera(&MainCamera);

    // Переменные для управления камерой
    bool isMousePressed = false;
    int lastMouseX = 0, lastMouseY = 0;
    float yaw = 0.0f, pitch = 0.0f; // Углы камеры
    const float mouseSensitivity = 0.1f; // Чувствительность мыши

    // Главный цикл
    while (window.isRunning()) {
        // Обработка событий
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = true;
                    SDL_GetMouseState(&lastMouseX, &lastMouseY); // Запоминаем начальное положение мыши
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = false;
                }
                break;

            case SDL_MOUSEMOTION:
                if (isMousePressed) {
                    int currentMouseX = event.motion.x;
                    int currentMouseY = event.motion.y;

                    // Вычисляем разницу в положении мыши
                    int deltaX = currentMouseX - lastMouseX;
                    int deltaY = currentMouseY - lastMouseY;

                    // Обновляем углы камеры
                    yaw += deltaX * mouseSensitivity;
                    pitch -= deltaY * mouseSensitivity;

                    // Ограничиваем угол pitch, чтобы камера не переворачивалась
                    if (pitch > 89.0f) pitch = 89.0f;
                    if (pitch < -89.0f) pitch = -89.0f;

                    // Обновляем направление камеры
                    MainCamera.SetPosition({0, 0, 0}, { pitch, yaw, 0 }, MainCamera.viewDir);

                    // Обновляем последнее положение мыши
                    lastMouseX = currentMouseX;
                    lastMouseY = currentMouseY;
                }
                break;
            }
        }

        // Очистка экрана
        window.clear();

        // Отрисовка сцены
        scene.Render(&window);

        // Вращение и перемещение объектов
        planet.Rotation.y += 0.1;
        planet.SetRotateXYZ(planet.Rotation);

        spase.Rotation.z += 0.1;
        spase.SetRotateXYZ(spase.Rotation);
        spase.Translate.x -= 0.01;
        spase.SetMoveXYZ(spase.Translate);

        // Обновление окна
        window.update();
    }

    return 0;
}
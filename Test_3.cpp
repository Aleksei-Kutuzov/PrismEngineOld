#include "src/PrismEngine.h"




static int test_3() {

    // Исходный код фрагментного шейдера
    const char* test_3FragmentShader = R"(
#version 330 core
out vec4 FragColor;

in vec2 fragCoord;

uniform float uTime;

mat2 rot(float a) {
    float s = sin(a), c = cos(a);
    return mat2(c, -s, s, c);
}

// Функция определения расстояния до поверхности туннеля
float map(vec3 p) {
    p.xz *= rot(sin(uTime * 0.2) * 0.3);
    p.yz *= rot(cos(uTime * 0.15) * 0.3);
    
    vec3 q = abs(mod(p, 4.0) - 2.0); // Повторяющаяся структура туннеля
    float d = max(q.x, max(q.y, q.z)) - 0.9; // Уменьшил размер кубов
    
    return d;
}

// Трассировка лучей
vec3 raymarch(vec3 ro, vec3 rd) {
    float t = 0.0;
    vec3 col = vec3(0.0);

    for (int i = 0; i < 100; i++) {
        vec3 p = ro + rd * t;
        float d = map(p);
        
        if (d < 0.02) { // Уменьшил минимальную дистанцию, чтобы избежать артефактов
            col = mix(vec3(1.0, 0.6, 0.3), vec3(0.2, 0.1, 0.7), sin(uTime + t * 0.1));
            break;
        }

        d = max(d, 0.08); // Ограничиваем шаг трассировки, чтобы не проходить через кубы
        
        t += d * 0.5; // Жёстко зафиксированная скорость движения

        if (t > 50.0) break; // Дальность обзора ограничена
    }

    return col;
}

void main() {
    vec2 uv = fragCoord * 2.0 - 1.0;
    uv.x *= 1.777; // Аспектное соотношение 16:9
    
    vec3 ro = vec3(0.0, 0.0, uTime * 2.0); // Камера летит с фиксированной скоростью 2.0
    vec3 rd = normalize(vec3(uv, -1.5)); // Чуть приподнял камеру для лучшего обзора

    vec3 col = raymarch(ro, rd);
    
    FragColor = vec4(col, 1.0);
}

)";
    // Создаем окно
    PRISM_Window window(600, 400, u8"♦PRISME♦|TEST 3", ShaderManager().baseVertexShader, test_3FragmentShader);

    // Проверяем, удалось ли создать окно
    if (!window.isRunning()) {
        return -1;
    }

    // Главный цикл
    while (window.isRunning()) {

        // Обработка событий
        window.handleEvents();
        PRISM_Painter painter;

        //Отрисовка сцены
        window.clear();


        // Фон (небо и трава)
        painter.DrawRectangle(&window, 1, 1, -1, -1, 255, 255, 255); // Небо (голубой)

        window.update();
        Sleep(1);

    }

    return 0;
}
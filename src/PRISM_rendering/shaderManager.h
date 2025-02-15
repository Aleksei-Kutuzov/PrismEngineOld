#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "SDL.h"
#include "SDL_opengl.h"


class ShaderManager
{
public:
    ShaderManager();
    GLuint compileShader(GLenum type, const char* source);
    void initShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    void useShader(bool q);
    void initBuffers();
    

    bool shaderIsActive = true;
    
    /// <summary>
    /// Программный шейдер для OpenGL.
    /// </summary>
    GLuint shaderProgram;

    /// <summary>
    /// Вершинный массивный объект (VAO) для OpenGL.
    /// </summary>
    GLuint VAO = 0; // Vertex Array Object
    GLuint VBO = 0; // Vertex Buffer Object

    // Исходный код вершинного шейдера
    const char* baseVertexShader = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;    // Координаты вершины
    layout(location = 1) in vec3 aColor; // Цвет вершины

    out vec3 vertexColor; // Передаем цвет во фрагментный шейдер
    out vec2 fragCoord;   // Передаем нормализованные координаты

    void main() {
        // Преобразуем координаты из [-1.0, 1.0] в [0.0, 1.0]
        fragCoord = aPos.xy * 0.5 + 0.5;

        gl_Position = vec4(aPos, 1.0); // Устанавливаем позицию
        vertexColor = aColor;         // Передаем цвет
    }
)";

    // Исходный код фрагментного шейдера
    const char* baseFragmentShader = R"(
    #version 330 core
    in vec3 vertexColor;
    out vec4 FragColor;

    void main() {
        FragColor = vec4(vertexColor, 1.0); // Используем переданный цвет
    }
    )";

    // Исходный код фрагментного шейдера
    const char* _testFragmentShader = R"(
#version 330 core
out vec4 FragColor; // Выходной цвет

in vec3 vertexColor; // Цвет вершины
in vec2 fragCoord;   // Нормализованные координаты [0.0, 1.0]

uniform float uTime; // Время для анимации

void main()
{
    // Нормализуем координаты
    vec2 uv = fragCoord;

    // Создаем плавные цветовые переходы с использованием времени
    float colorFactor = sin(uTime + uv.x * 5.0 + uv.y * 5.0) * 0.5 + 0.5;
    vec3 baseColor = mix(vec3(0.1, 0.3, 0.8), vec3(0.8, 0.1, 0.3), colorFactor);

    // Эффект "голограммы" (полосы)
    float stripePattern = sin(uv.y * 10.0 + uTime * 2.0) * 0.5 + 0.5;
    vec3 stripeColor = mix(baseColor, vec3(1.0), stripePattern);

    // Эффект свечения (зависит от расстояния от центра)
    float glow = smoothstep(0.5, 0.8, length(uv - vec2(0.5)));
    vec3 glowColor = mix(stripeColor, vec3(1.0, 1.0, 1.0), glow);

    // Итоговый цвет с учетом свечения
    FragColor = vec4(glowColor, 1.0);
}
    )";

    // Исходный код фрагментного шейдера
    const char* testFragmentShader = R"(
    #version 330 core
    in vec3 vertexColor;  // Цвет из вершины
    in vec2 fragCoord;    // Нормализованные координаты фрагмента
    out vec4 FragColor;

    uniform float uTime;  // Время для анимации

    // Функция для генерации псевдошума
    float hash(vec2 p) {
        return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
    }

    // Функция для сглаживания шума
    float smoothNoise(vec2 p) {
        vec2 i = floor(p);
        vec2 f = fract(p);

        float a = hash(i);
        float b = hash(i + vec2(1.0, 0.0));
        float c = hash(i + vec2(0.0, 1.0));
        float d = hash(i + vec2(1.0, 1.0));

        vec2 u = f * f * (3.0 - 2.0 * f);
        return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
    }

    void main() {
        // Центр экрана
        vec2 center = vec2(0.5, 0.5);

        // Координаты относительно центра
        vec2 coord = fragCoord - center;

        // Расстояние от центра
        float dist = length(coord);

        // Создаем пульсирующий эффект
        float pulse = sin(uTime + dist * 10.0) * 0.5 + 0.5;

        // Генерируем шум для текстуры
        float noise = smoothNoise(coord * 10.0 + uTime);

        // Смешиваем базовые цвета с эффектами
        vec3 dynamicColor = vec3(
            0.5 + 0.5 * cos(uTime + dist * 10.0 + noise),
            0.5 + 0.5 * sin(uTime + dist * 15.0 - noise),
            pulse
        );

        // Итоговый цвет: смешиваем цвет вершины с динамическим цветом
        vec3 finalColor = mix(vertexColor, dynamicColor, 0.7);

        // Устанавливаем итоговый цвет фрагмента
        FragColor = vec4(finalColor, 1.0);
    }
)";




private:
    
};
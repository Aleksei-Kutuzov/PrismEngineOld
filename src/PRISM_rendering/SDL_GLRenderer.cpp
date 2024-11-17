#include "SDL_GLRenderer.h"



bool initOpenGL(GLuint shaderProgram, GLuint vbo) {
    // Шейдеры вершин и фрагментов
    const char* vertexShaderSource = R"(
        attribute vec4 aPosition;
        uniform mat4 uMVPMatrix;
        void main() {
            gl_Position = uMVPMatrix * aPosition;
        }
    )";

    const char* fragmentShaderSource = R"(
        precision mediump float;
        void main() {
            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);  // Красный цвет
        }
    )";

    // Компиляция и привязка шейдеров
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Создаем VBO для хранения вершин
    glGenBuffers(1, &vbo);

    return true;
}



//void cleanUp() {
//    SDL_GL_DeleteContext(glContext);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}

void drawTriangleWithOpenGL(Vector3d v1, Vector3d v2, Vector3d v3, GLuint shaderProgram, GLuint vbo) {
	// Активация шейдерной программы
    glUseProgram(shaderProgram);

    // Передача матрицы преобразования (единичная матрица для примера)
    float mvpMatrix[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    GLuint mvpLoc = glGetUniformLocation(shaderProgram, "uMVPMatrix");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvpMatrix);

    // Передача вершин в VBO
    Vector3d vertices[3] = { v1, v2, v3 };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Настройка атрибута позиции
    GLuint positionLoc = glGetAttribLocation(shaderProgram, "aPosition");
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vector3d), (void*)0);

    // Рисуем треугольник
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Отключаем атрибуты после отрисовки
    glDisableVertexAttribArray(positionLoc);

    // Отключение шейдера
    glUseProgram(0);
}

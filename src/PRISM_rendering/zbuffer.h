#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <vector>
#include <limits>
#include <SDL.h>

class Z_Buffer {
public:
    // Конструктор
    Z_Buffer(int screenW, int screenH);

    // Метод для обновления Z-буфера
    void update(int x, int y, int z);

    // Метод для получения значения Z-буфера
    int get(int x, int y) const;

    // Метод для очистки Z-буфера
    void clear(SDL_Renderer* renderer);

private:
    int ScreenW, ScreenH;
    std::vector<int> zMatrix;
	std::vector<int> zMatrixСleared;
	bool isCleared;
};

#endif // ZBUFFER_H
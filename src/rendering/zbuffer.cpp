#include <SDL.h>
#include <vector>
#include <limits>
#include "zbuffer.h"

// Конструктор
Z_Buffer::Z_Buffer(int screenW, int screenH) : ScreenW(screenW), ScreenH(screenH),
                   zMatrix(screenW * screenH, std::numeric_limits<int>::max()),
                   zMatrixСleared(screenW * screenH, std::numeric_limits<int>::max()) {}
		
// Метод для обновления Z-буфера
void Z_Buffer::Z_Buffer::update(int x, int y, int z) {
	if (x >= 0 && x < ScreenW && y >= 0 && y < ScreenH) {
            zMatrix[x + y * ScreenW] = z;
	}
}

// Метод для получения значения Z-буфера
int Z_Buffer::get(int x, int y) const {
	if (x >= 0 && x < ScreenW && y >= 0 && y < ScreenH) {
            return zMatrix[x + y * ScreenW];
        }
        return std::numeric_limits<int>::max();
    }

void Z_Buffer::clear(SDL_Renderer * renderer){
        std::fill(zMatrix.begin(), zMatrix.end(), std::numeric_limits<int>::max());
//        SDL_Log("Clear z_buffer");
		
}
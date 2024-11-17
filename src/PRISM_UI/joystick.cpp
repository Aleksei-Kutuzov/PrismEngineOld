#include "SDL.h"
#include "SDL_image.h"
#include <cmath>
#include <vector>

// Структура для хранения состояния джойстика
struct Joystick {
	SDL_Rect base_rect;
	SDL_Rect stick_rect;
	SDL_Point center;
	int max_distance;
	SDL_FingerID fingerId;
	bool active;
	SDL_Texture *background;
	SDL_Texture *image;
};

// Функция для загрузки текстуры из файла
SDL_Texture* loadTexture(const char* file, SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load(file);
    if (!surface) {
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Функция для рендеринга текстуры
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

// Функция для инициализации джойстика
void InitJoystick(Joystick &joystick, int x, int y, int base_size, int stick_size, SDL_Renderer *renderer) {
	SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
	
	base_size = (float)base_size / 2179.f * (float)mode.w;
	stick_size = (float)stick_size / 1080.f * (float)mode.h;
	x = (float)x / 2179.f * (float)mode.w;
	y = (float)y / 1080.f * (float)mode.h;

	x = (int)x;
	y = (int)y;
	base_size = (int)base_size;
	stick_size = (int)stick_size;
	
	joystick.base_rect = {x - base_size / 2, y - base_size / 2, base_size, base_size};
	joystick.stick_rect = {x - stick_size / 2, y - stick_size / 2, stick_size, stick_size};
	joystick.center = {x, y};
	joystick.max_distance = base_size / 2 - stick_size / 2;
	joystick.active = false;
	joystick.background = loadTexture("Circle Joystick/subpacks/Type1/textures/ui/joystick_frame.png", renderer);
	joystick.image = loadTexture("Circle Joystick/subpacks/Type1/textures/ui/joystick_knob.png", renderer);
}

// Функция для получения нормализованных координат джойстика
void GetJoystickPosition(Joystick &joystick, float &norm_x, float &norm_y) {
	int dx = joystick.stick_rect.x + joystick.stick_rect.w / 2 - joystick.center.x;
	int dy = joystick.stick_rect.y + joystick.stick_rect.h / 2 - joystick.center.y;
	norm_x = static_cast<float>(dx) / joystick.max_distance;
	norm_y = static_cast<float>(dy) / joystick.max_distance;
}


// Функция для обновления состояния джойстика
void UpdateJoystick(Joystick &joystick, int x, int y) {
	int dx = x - joystick.center.x;
	int dy = y - joystick.center.y;
	float distance = std::sqrt(dx * dx + dy * dy);
	
	if (distance < joystick.max_distance) {
		joystick.stick_rect.x = x - joystick.stick_rect.w / 2;
		joystick.stick_rect.y = y - joystick.stick_rect.h / 2;
	} else {
		float angle = std::atan2(dy, dx);
		joystick.stick_rect.x = joystick.center.x + std::cos(angle) * joystick.max_distance - joystick.stick_rect.w / 2;
		joystick.stick_rect.y = joystick.center.y + std::sin(angle) * joystick.max_distance - joystick.stick_rect.h / 2;
	}
}

// Функция для обработки ввода
void HandleInput(SDL_Event &e, std::vector<Joystick> &joysticks, int window_width, int window_height) {
	switch (e.type) {
		case SDL_FINGERDOWN: {
			SDL_Point touch_point = {
					static_cast<int>(e.tfinger.x * window_width),
					static_cast<int>(e.tfinger.y * window_height)
			};
			// Поиск неактивного джойстика для активации
			for (auto& joystick : joysticks) {
				if (!joystick.active && SDL_PointInRect(&touch_point, &joystick.base_rect)) {
					joystick.active = true;
					joystick.fingerId = e.tfinger.fingerId;
					UpdateJoystick(joystick, touch_point.x, touch_point.y);
					break;
				}
			}
			break;
		}
		case SDL_FINGERUP:
			// Поиск активного джойстика для деактивации
			for (auto& joystick : joysticks) {
				if (joystick.active && e.tfinger.fingerId == 0) { // Проверка fingerId может варьироваться
					joystick.active = false;
					joystick.stick_rect.x = joystick.center.x - joystick.stick_rect.w / 2;
					joystick.stick_rect.y = joystick.center.y - joystick.stick_rect.h / 2;
					break;
				}
			}
			break;
		case SDL_FINGERMOTION:
			// Обновление позиции активного джойстика
			SDL_Point touch_point = {
					static_cast<int>(e.tfinger.x * window_width),
					static_cast<int>(e.tfinger.y * window_height)
			};
			for (auto& joystick : joysticks) {
				if (joystick.active) {
					UpdateJoystick(joystick, touch_point.x, touch_point.y);
					break; // Обработка только одного активного джойстика на данный момент
				}
			}
			break;
	}
}

// Функция для рендеринга джойстика
void RenderJoystick(SDL_Renderer *renderer, Joystick &joystick) {
	renderTexture(joystick.background, renderer, joystick.base_rect.x, joystick.base_rect.y, joystick.base_rect.w, joystick.base_rect.h);
	renderTexture(joystick.image, renderer, joystick.stick_rect.x, joystick.stick_rect.y, joystick.stick_rect.w, joystick.stick_rect.h);
}

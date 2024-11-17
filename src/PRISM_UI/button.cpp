#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <string>
#include <SDL2_gfxPrimitives.h>

// Структура для хранения состояния кнопки
struct ToggleButton {
	SDL_Texture *image;
	SDL_Renderer *renderer;
	SDL_Rect rect;
	std::string text;
	bool active;
	bool FD;
	
};


void InitToggleButton(ToggleButton &toggle_button, int x, int y, int w, int h,
					  bool IsActive, SDL_Renderer *renderer) {
	SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
	
	w = ((float)x + (float)w) / 2179.f * (float)mode.w;
	h = ((float)y + (float)h) / 1080.f * (float)mode.h;
	x = (float)x / 2179.f * (float)mode.w;
	y = (float)y / 1080.f * (float)mode.h;

	toggle_button.rect.x = (int)x;
	toggle_button.rect.y = (int)y;
	toggle_button.rect.w = (int)w;
	toggle_button.rect.h = (int)h;

	toggle_button.active = IsActive;
	toggle_button.renderer = renderer;
}


void SetToggleButtonTexture(ToggleButton &toggle_button, const char *filename) {
	SDL_Surface *surface = IMG_Load(filename);
    if (!surface) {
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return ;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(toggle_button.renderer, surface);
    SDL_FreeSurface(surface);
	toggle_button.image = texture;
}

void ToggleButtonInput(ToggleButton &toggle_button, SDL_Event &e) {
	SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
	int window_width = mode.w;
	int window_height = mode.h;
	SDL_Point touch_point = {
		static_cast<int>((float)e.tfinger.x * (float)window_width),
		static_cast<int>((float)e.tfinger.y * (float)window_height)
	};
	SDL_Rect _rect = {toggle_button.rect.x, toggle_button.rect.y, toggle_button.rect.w - toggle_button.rect.x, toggle_button.rect.h - toggle_button.rect.y};

	switch (e.type) {
		case SDL_FINGERDOWN:
			if (!toggle_button.active && SDL_PointInRect(&touch_point, &_rect)) {
				toggle_button.FD = true;
				break;
			}
			if (toggle_button.active && SDL_PointInRect(&touch_point, &_rect)) {
				toggle_button.FD = true;
				break;
			}
			
		case SDL_FINGERUP:
			if (!toggle_button.active && SDL_PointInRect(&touch_point, &_rect) && toggle_button.FD) {
				toggle_button.active = true;
				toggle_button.FD = false;
				break;
			}
			if (toggle_button.active && SDL_PointInRect(&touch_point, &_rect) && toggle_button.FD) {
				toggle_button.active = false;
				toggle_button.FD = false;
				break;
			}
			toggle_button.FD = false;
	}
}

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
        //Открываем шрифт
        TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == nullptr){
                SDL_Log("Failed to load font: %s", fontFile.c_str());
                return nullptr;
        }
        //Сначала нужно отобразить на поверхность с помощью TTF_RenderText,
        //затем загрузить поверхность в текстуру
        SDL_Surface *surf = TTF_RenderUTF8_Blended_Wrapped(font, message.c_str(), color, 1000);
        if (surf == nullptr){
                TTF_CloseFont(font);
				SDL_Log("Failed to TTF_RenderText");
                return nullptr;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == nullptr){
				SDL_Log("Failed to create texture font");
        }
        //Очистка поверхности и шрифта
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        return texture;
}


void SetToggleButtonText(ToggleButton &toggle_button, const std::string text,
						 const std::string &fontFile, SDL_Color color, int fontSize) {
	toggle_button.text = text;
	toggle_button.image = renderText(toggle_button.text, fontFile, color, fontSize, toggle_button.renderer);
}



void RenderToggleButton(ToggleButton &toggle_button) {
	SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
	
	
	int W, H;
	SDL_QueryTexture(toggle_button.image, NULL, NULL, &W, &H);
	SDL_Rect dst;
	dst.x = toggle_button.rect.x + ((toggle_button.rect.w - toggle_button.rect.x) - W) / 2;
	dst.y = toggle_button.rect.y + ((toggle_button.rect.h - toggle_button.rect.y) - H) / 2;
	dst.w = W;
	dst.h = H;
	if (!toggle_button.active) {
		roundedBoxRGBA(toggle_button.renderer, toggle_button.rect.x, toggle_button.rect.y, toggle_button.rect.w, toggle_button.rect.h,
				   10, 255, 0, 0, 255);
	}
	else {
		roundedBoxRGBA(toggle_button.renderer, toggle_button.rect.x, toggle_button.rect.y, toggle_button.rect.w, toggle_button.rect.h,
				   10, 0, 255, 0, 255);
	}
	SDL_RenderCopy(toggle_button.renderer, toggle_button.image, NULL, &dst);
	
}
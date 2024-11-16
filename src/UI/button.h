#ifndef BUTTON_H
#define BUTTON_H
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <SDL2_gfxPrimitives.h>


struct ToggleButton {
	SDL_Texture *image;
	SDL_Renderer *renderer;
	SDL_Rect rect;
	std::string text;
	bool active;
	
};


void InitToggleButton(ToggleButton &toggle_button, int x, int y, int w, int h,
					  bool IsActive, SDL_Renderer *renderer);
void SetToggleButtonTexture(ToggleButton &toggle_button, const char *filename);
SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
        SDL_Color color, int fontSize, SDL_Renderer *renderer);
void SetToggleButtonText(ToggleButton &toggle_button, const std::string text,
						 const std::string &fontFile, SDL_Color color, int fontSize);
void ToggleButtonInput(ToggleButton &toggle_button, SDL_Event &e);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void RenderToggleButton(ToggleButton &toggle_button);


#endif
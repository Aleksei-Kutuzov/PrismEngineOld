#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <vector>
struct Joystick {
	SDL_Rect base_rect;
	SDL_Rect stick_rect;
	SDL_Point center;
	int max_distance;
	bool active;
//	SDL_Texture *texture;
	SDL_Texture *background;
	SDL_Texture *image;
};


void InitJoystick(Joystick &joystick, int x, int y, int base_size, int stick_size, SDL_Renderer *renderer);
void UpdateJoystick(Joystick &joystick, int x, int y);
void HandleInput(SDL_Event &e, std::vector<Joystick> &joysticks, int window_width, int window_height);
void GetJoystickPosition(Joystick &joystick, float &norm_x, float &norm_y);
void RenderJoystick(SDL_Renderer *renderer, Joystick &joystick);


#endif
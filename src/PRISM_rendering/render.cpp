#include "render.h"

std::string getInternalStoragePath() {
    return "output_files";
}

bool saveTexture(SDL_Renderer* renderer, SDL_Texture* texture, const std::string& filePath) {
    // Получаем размер текстуры
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SDL_Log("WH: %d, %d", width, height);
    // Создаем поверхность для сохранения
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

    if (!surface) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        return false;
    }

    // Рендерим текстуру в поверхность
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch);
    SDL_Log("ПОЧТИ");
	SDL_SetRenderTarget(renderer, NULL);
    // Сохраняем поверхность как изображение
    if (IMG_SavePNG(surface, filePath.c_str()) != 0) {
        SDL_Log("Failed to save PNG: %s", IMG_GetError());
        SDL_FreeSurface(surface);
        return false;
    }

    SDL_FreeSurface(surface);
    return true;
}

PRISME_Render::PRISME_Render(SDL_Renderer *rend) {
	renderer = rend;
}
void PRISME_Render::AddInRender(AbstractObject3D object3d) {
	Object3DList.push_back(object3d);
}
//RemInRender(AbstractObject3D object3d);
SDL_Texture * PRISME_Render::ReturnFrameTexture(int DWidth, int DHeight, PRISM_RenderMode rm) {
	SDL_Texture *target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DWidth, DHeight);
	
	SDL_SetRenderTarget(renderer, target);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderClear(renderer);
	for (auto Object3D : Object3DList) {
		Object3D.DrawMeshTriangles(renderer, {true, false, false, true, false, true, 5});
	}


	SDL_RenderCopy(renderer, target, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);
		std::string savePath = getInternalStoragePath() + "/texture1.png";
		saveTexture(renderer, target, savePath);
		int w, h;
		SDL_QueryTexture(target, nullptr, nullptr, &w, &h);
		SDL_Log("%d %d", w, h);
	SDL_RenderPresent(renderer);
		
	return target;
}
void PRISME_Render::RenderFrameSurfase(int DWidth, int DHeight, PRISM_RenderMode rm = {true, false, false, true, false, true, 5}) {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (auto Object3D : Object3DList) {
		Object3D.DrawMeshTriangles(renderer, { true, false, false, true, false, true, 5 });
	}
	SDL_RenderPresent(renderer);
}

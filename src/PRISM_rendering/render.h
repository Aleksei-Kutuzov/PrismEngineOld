#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "/PrismEngine/src/PRISM_objects3D/AbstractObject3D.h"
#include <string>
std::string getInternalStoragePath();

bool saveTexture(SDL_Renderer* renderer, SDL_Texture* texture, const std::string& filePath);

enum RasterizationMode {
	ZBufferComparison,
	AverageZFigureComparison
};

class PRISME_Render {
public:
	PRISME_Render(SDL_Renderer *rend);
	void AddInRender(AbstractObject3D object3d);
//	RemInRender(AbstractObject3D object3d);
	SDL_Texture * ReturnFrameTexture(int DWidth, int DHeight, PRISM_RenderMode rm);
	void RenderFrameSurfase(int DWidth, int DHeight, PRISM_RenderMode rm);
	
	
private:
	std::vector <AbstractObject3D> Object3DList;
	SDL_Renderer *renderer;
};

#endif // RENDER_H
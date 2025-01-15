#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "../PRISM_objects3D/AbstractObject3D.h"
#include <string>


//enum RasterizationMode {
//	ZBufferComparison,
//	AverageZFigureComparison
//};

class PRISM_Render {
public:
	PRISM_Vector3d cameraCoordinate = {0, 0, 0};
	PRISM_Vector3d lightAmbient = { 0.1f, 0.1f, 0.1f }; // интенсивность окружающего света в сцене(задаётся для всего пространства).

	PRISM_Color CalculatePixelAmbient(PRISM_Color originalСolor, AbstractObject3D obj) const; // Окружающее освещение (ambient lighting) симулирует свет, равномерно распространяющийся в пространстве. Оно добавляет объекту базовую освещённость, даже если на него напрямую не падает свет.
	PRISM_Color CalculatePixelDiffuse(PRISM_Color originalСolor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle); // Диффузное освещение моделирует рассеивание света на матовой поверхности.
	PRISM_Color CalculatePixelSpecular(PRISM_Color originalСolor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle, PRISM_Vector3d cameraCoordinate);
	
	

	void Rendering(PRISM_Window* window, AbstractObject3D* obj);
	void SetScreenSize(int w, int h);
	
private:
	int ScreenW, ScreenH;
};

#endif // RENDER_H
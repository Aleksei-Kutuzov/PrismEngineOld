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
	PRISM_Vector3d lightAmbient = { 0.1f, 0.1f, 0.1f }; // ������������� ����������� ����� � �����(������� ��� ����� ������������).

	PRISM_Color CalculatePixelAmbient(PRISM_Color original�olor, AbstractObject3D obj) const; // ���������� ��������� (ambient lighting) ���������� ����, ���������� ������������������ � ������������. ��� ��������� ������� ������� ������������, ���� ���� �� ���� �������� �� ������ ����.
	PRISM_Color CalculatePixelDiffuse(PRISM_Color original�olor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle); // ��������� ��������� ���������� ����������� ����� �� ������� �����������.
	PRISM_Color CalculatePixelSpecular(PRISM_Color original�olor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle, PRISM_Vector3d cameraCoordinate);
	
	

	void Rendering(PRISM_Window* window, AbstractObject3D* obj);
	void SetScreenSize(int w, int h);
	
private:
	int ScreenW, ScreenH;
};

#endif // RENDER_H
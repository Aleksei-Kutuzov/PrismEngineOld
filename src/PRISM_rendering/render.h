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


/// <summary>
/// Класс PRISM_Render предоставляет функциональность для обработки рендеринга объектов, освещения и управления параметрами сцены.
/// </summary>
class PRISM_Render {
public:
	/// <summary>
	/// Координаты камеры в пространстве.
	/// </summary>
	PRISM_Vector3d cameraCoordinate = {0, 0, 0};

	/// <summary>
	/// Интенсивность окружающего света в сцене.
	/// Определяет базовую освещённость пространства.
	/// Так же является коэфицентом дифузного освещения
	/// </summary>
	PRISM_Vector3d lightAmbient = { 0.1f, 0.1f, 0.1f };

	/// <summary>
	/// Рассчитывает конечный цвет пикселя с учётом окружающего освещения (ambient lighting).
	/// </summary>
	/// <param name="originalСolor">Исходный цвет пикселя.</param>
	/// <param name="obj">Объект, к которому принадлежит пиксель.</param>
	/// <returns>Цвет пикселя с учётом окружающего освещения.</returns>
	PRISM_Color CalculatePixelAmbient(PRISM_Color originalСolor, AbstractObject3D obj) const; // Окружающее освещение (ambient lighting) симулирует свет, равномерно распространяющийся в пространстве. Оно добавляет объекту базовую освещённость, даже если на него напрямую не падает свет.
	
	/// <summary>
	/// Рассчитывает конечный цвет пикселя с учётом диффузного освещения (diffuse lighting).
	/// </summary>
	/// <param name="originalСolor">Исходный цвет пикселя.</param>
	/// <param name="light">Источник света.</param>
	/// <param name="obj">Объект, к которому принадлежит пиксель.</param>
	/// <param name="triangle">Треугольник, к которому принадлежит пиксель.</param>
	/// <returns>Цвет пикселя с учётом диффузного освещения.</returns>
	PRISM_Color CalculatePixelDiffuse(PRISM_Color originalСolor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle); // Диффузное освещение моделирует рассеивание света на матовой поверхности.
	
	/// <summary>
	/// Рассчитывает конечный цвет пикселя с учётом зеркального отражения (specular lighting).
	/// </summary>
	/// <param name="originalСolor">Исходный цвет пикселя.</param>
	/// <param name="light">Источник света.</param>
	/// <param name="obj">Объект, к которому принадлежит пиксель.</param>
	/// <param name="triangle">Треугольник, к которому принадлежит пиксель.</param>
	/// <param name="cameraCoordinate">Координаты камеры.</param>
	/// <returns>Цвет пикселя с учётом зеркального отражения.</returns>
	PRISM_Color CalculatePixelSpecular(PRISM_Color originalСolor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle, PRISM_Vector3d cameraCoordinate);
	
	
	/// <summary>
	/// Выполняет рендеринг указанного объекта в заданном окне.
	/// </summary>
	/// <param name="window">Указатель на объект окна, в котором происходит рендеринг.</param>
	/// <param name="obj">Объект для рендеринга.</param>
	void Rendering(PRISM_Window* window, AbstractObject3D* obj);
	
	/// <summary>
	/// Устанавливает размеры экрана для рендеринга.
	/// </summary>
	/// <param name="w">Ширина экрана.</param>
	/// <param name="h">Высота экрана.</param>
	void SetScreenSize(int w, int h);
	
private:
	/// <summary>
	/// Текущая ширина экрана.
	/// </summary>
	int ScreenW;

	/// <summary>
	/// Текущая высота экрана.
	/// </summary>
	int ScreenH;
};

#endif // RENDER_H
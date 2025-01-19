#ifndef PRISM_PAINTER_H
#define PRISM_PAINTER_H

#include "SDL.h"
#include "PRISM_Window.h"
#include "../PRISM_math/other.h"


/// <summary>
/// Класс для отрисовки различных графических примитивов, включая 2D и 3D объекты.
/// </summary>
class PRISM_Painter
{
public:
	/// <summary>
	/// Рисует толстую линию на указанном SDL-рендерере.
	/// </summary>
	/// <param name="renderer">Указатель на SDL_Renderer для отрисовки.</param>
	/// <param name="x1">Координата X начальной точки линии.</param>
	/// <param name="y1">Координата Y начальной точки линии.</param>
	/// <param name="x2">Координата X конечной точки линии.</param>
	/// <param name="y2">Координата Y конечной точки линии.</param>
	/// <param name="thickness">Толщина линии.</param>
	static void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);

	/// <summary>
	/// Рисует треугольник на указанном SDL-рендерере.
	/// </summary>
	/// <param name="x1">Координата X первой вершины треугольника.</param>
	/// <param name="y1">Координата Y первой вершины треугольника.</param>
	/// <param name="x2">Координата X второй вершины треугольника.</param>
	/// <param name="y2">Координата Y второй вершины треугольника.</param>
	/// <param name="x3">Координата X третьей вершины треугольника.</param>
	/// <param name="y3">Координата Y третьей вершины треугольника.</param>
	/// <param name="SDL_renderer">Указатель на SDL_Renderer для отрисовки.</param>
	/// <param name="rgba">Массив из 4 элементов, задающий цвет в формате RGBA.</param>
	/// <param name="thickness">Толщина границ треугольника.</param>
	static void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
							 SDL_Renderer* SDL_renderer, short rgba[4], int thickness);



	/// <summary>
	/// Рисует точку в указанном окне.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x">Координата X точки.</param>
	/// <param name="y">Координата Y точки.</param>
	static void DrawPoint(PRISM_Window* window, float x, float y);

	
	/// <summary>
	/// Рисует точку в указанном окне с заданным цветом.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x">Координата X точки.</param>
	/// <param name="y">Координата Y точки.</param>
	/// <param name="r">Интенсивность красного цвета (0-255).</param>
	/// <param name="g">Интенсивность зеленого цвета (0-255).</param>
	/// <param name="b">Интенсивность синего цвета (0-255).</param>
	static void DrawPoint(PRISM_Window* window, float x, float y, int r, int g, int b);
	


	/// <summary>
	/// Рисует линию в указанном окне.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X начальной точки линии.</param>
	/// <param name="y1">Координата Y начальной точки линии.</param>
	/// <param name="x2">Координата X конечной точки линии.</param>
	/// <param name="y2">Координата Y конечной точки линии.</param>
	/// <param name="thickness">Толщина линии.</param>
	static void DrawThickLine(PRISM_Window* window, float x1, float y1, float x2, float y2, int thickness);
	

	/// <summary>
	/// Рисует линию в указанном окне с заданным цветом.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X начальной точки линии.</param>
	/// <param name="y1">Координата Y начальной точки линии.</param>
	/// <param name="x2">Координата X конечной точки линии.</param>
	/// <param name="y2">Координата Y конечной точки линии.</param>
	/// <param name="thickness">Толщина линии.</param>
	/// <param name="r">Интенсивность красного цвета (0-255).</param>
	/// <param name="g">Интенсивность зеленого цвета (0-255).</param>
	/// <param name="b">Интенсивность синего цвета (0-255).</param>
	static void DrawThickLine(PRISM_Window* window, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b);

	
	
	/// <summary>
	/// Рисует треугольник в указанном окне.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X первой вершины треугольника.</param>
	/// <param name="y1">Координата Y первой вершины треугольника.</param>
	/// <param name="x2">Координата X второй вершины треугольника.</param>
	/// <param name="y2">Координата Y второй вершины треугольника.</param>
	/// <param name="x3">Координата X третьей вершины треугольника.</param>
	/// <param name="y3">Координата Y третьей вершины треугольника.</param>
	static void DrawTriangle(PRISM_Window* window, float x1, float y1, float x2, float y2, float x3, float y3);

	/// <summary>
	/// Рисует треугольник в указанном окне с заданным цветом.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X первой вершины треугольника.</param>
	/// <param name="y1">Координата Y первой вершины треугольника.</param>
	/// <param name="x2">Координата X второй вершины треугольника.</param>
	/// <param name="y2">Координата Y второй вершины треугольника.</param>
	/// <param name="x3">Координата X третьей вершины треугольника.</param>
	/// <param name="y3">Координата Y третьей вершины треугольника.</param>
	/// <param name="r">Интенсивность красного цвета (0-255).</param>
	/// <param name="g">Интенсивность зеленого цвета (0-255).</param>
	/// <param name="b">Интенсивность синего цвета (0-255).</param>
	static void DrawTriangle(PRISM_Window* window, float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b);



	/// <summary>
	/// Рисует прямоугольник в указанном окне.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X верхнего левого угла прямоугольника.</param>
	/// <param name="y1">Координата Y верхнего левого угла прямоугольника.</param>
	/// <param name="x2">Координата X нижнего правого угла прямоугольника.</param>
	/// <param name="y2">Координата Y нижнего правого угла прямоугольника.</param>
	static void DrawRectangle(PRISM_Window* window, float x1, float y1, float x2, float y2);

	
	/// <summary>
	/// Рисует прямоугольник в указанном окне с заданным цветом.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X верхнего левого угла прямоугольника.</param>
	/// <param name="y1">Координата Y верхнего левого угла прямоугольника.</param>
	/// <param name="x2">Координата X нижнего правого угла прямоугольника.</param>
	/// <param name="y2">Координата Y нижнего правого угла прямоугольника.</param>
	/// <param name="r">Интенсивность красного цвета (0-255).</param>
	/// <param name="g">Интенсивность зеленого цвета (0-255).</param>
	/// <param name="b">Интенсивность синего цвета (0-255).</param>
	static void DrawRectangle(PRISM_Window* window, float x1, float y1, float x2, float y2, int r, int g, int b);
	


	/// <summary>
	/// Рисует 3D-треугольник в указанном окне с заданным цветом.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="x1">Координата X первой вершины треугольника.</param>
	/// <param name="y1">Координата Y первой вершины треугольника.</param>
	/// <param name="z1">Координата Z первой вершины треугольника.</param>
	/// <param name="x2">Координата X второй вершины треугольника.</param>
	/// <param name="y2">Координата Y второй вершины треугольника.</param>
	/// <param name="z2">Координата Z второй вершины треугольника.</param>
	/// <param name="x3">Координата X третьей вершины треугольника.</param>
	/// <param name="y3">Координата Y третьей вершины треугольника.</param>
	/// <param name="z3">Координата Z третьей вершины треугольника.</param>
	/// <param name="r">Интенсивность красного цвета (0-255).</param>
	/// <param name="g">Интенсивность зеленого цвета (0-255).</param>
	/// <param name="b">Интенсивность синего цвета (0-255).</param>
	static void DrawTriangle3D(PRISM_Window* window, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int r, int g, int b);
	
	/// <summary>
	/// Рисует 3D-треугольник в указанном окне с заданным цветом.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="triangle">Объект типа PRISM_Triangle, содержащий вершины треугольника.</param>
	/// <param name="r">Интенсивность красного цвета (0-255).</param>
	/// <param name="g">Интенсивность зеленого цвета (0-255).</param>
	/// <param name="b">Интенсивность синего цвета (0-255).</param>
	static void DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, int r, int g, int b);
	
	/// <summary>
	/// Рисует 3D-треугольник в указанном окне с использованием заданного цвета.
	/// </summary>
	/// <param name="window">Указатель на окно PRISM_Window для отрисовки.</param>
	/// <param name="triangle">Объект типа PRISM_Triangle, содержащий вершины треугольника.</param>
	/// <param name="color">Объект типа PRISM_Color, задающий цвет треугольника.</param>
	static void DrawTriangle3D(PRISM_Window* window, PRISM_Triangle triangle, PRISM_Color color);
private:

};



#endif //PRISM_PAINTER_H
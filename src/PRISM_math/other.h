#ifndef OTHER_H
#define OTHER_H


#include "vector3D.h"
#include <vector>
#include <SDL_stdinc.h>
#include <SDL.h>

/// <summary>
/// Структура, представляющая цвет в формате RGBA (красный, зелёный, синий, альфа).
/// Поддерживает различные форматы ввода: целочисленные и вещественные значения.
/// </summary>
struct PRISM_Color {
	/// <summary>
	/// Красная компонента цвета (0-255).
	/// </summary>
	unsigned char r = 0;

	/// <summary>
	/// Красная компонента цвета (0-255).
	/// </summary>
	unsigned char g = 0;

	/// <summary>
	/// Синяя компонента цвета (0-255).
	/// </summary>
	unsigned char b = 0;

	/// <summary>
	/// Альфа-канал (0-255), определяющий прозрачность. 
	/// Значение по умолчанию: 255 (непрозрачный).
	/// </summary>
	unsigned char a = 255;

	/// <summary>
	/// Выводит цвет в формате RGBA в консоль.
	/// </summary>
	void print();

	/// <summary>
	/// Конструктор для создания цвета из целых чисел.
	/// </summary>
	/// <param name="r">Красная компонента.</param>
	/// <param name="g">Зелёная компонента.</param>
	/// <param name="b">Синяя компонента.</param>
	PRISM_Color(unsigned char r, unsigned char g, unsigned char b) { this->r = r;  this->g = g; this->b = b; this->a = 255; }

	/// <summary>
	/// Конструктор для создания цвета из целых чисел с альфа-каналом.
	/// </summary>
	/// <param name="r">Красная компонента.</param>
	/// <param name="g">Зелёная компонента.</param>
	/// <param name="b">Синяя компонента.</param>
	/// <param name="a">Альфа-канал.</param>
	PRISM_Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { this->r = r;  this->g = g; this->b = b; this->a = a; }

	/// <summary>
	/// Конструктор для создания цвета из вещественных чисел (0.0f - 255.0f).
	/// </summary>
	/// <param name="r">Красная компонента.</param>
	/// <param name="g">Зелёная компонента.</param>
	/// <param name="b">Синяя компонента.</param>
	PRISM_Color(float r, float g, float b) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = 255; }

	/// <summary>
	/// Конструктор для создания цвета из вещественных чисел с альфа-каналом.
	/// </summary>
	/// <param name="r">Красная компонента.</param>
	/// <param name="g">Зелёная компонента.</param>
	/// <param name="b">Синяя компонента.</param>
	/// <param name="a">Альфа-канал.</param>
	PRISM_Color(float r, float g, float b, float a) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = (unsigned char)a; }

	/// <summary>
	/// Конструктор для создания цвета из целых чисел.
	/// </summary>
	/// <param name="r">Красная компонента (0-255).</param>
	/// <param name="g">Зелёная компонента (0-255).</param>
	/// <param name="b">Синяя компонента (0-255).</param>
	PRISM_Color(int r, int g, int b) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = 255; }

	/// <summary>
	/// Конструктор для создания цвета из целых чисел с альфа-каналом.
	/// </summary>
	/// <param name="r">Красная компонента (0-255).</param>
	/// <param name="g">Зелёная компонента (0-255).</param>
	/// <param name="b">Синяя компонента (0-255).</param>
	/// <param name="a">Альфа-канал (0-255).</param>
	PRISM_Color(int r, int g, int b, int a) { this->r = (unsigned char)r;  this->g = (unsigned char)g; this->b = (unsigned char)b; this->a = (unsigned char)a; }

	/// <summary>
	/// Конструктор по умолчанию.
	/// Создаёт чёрный цвет с непрозрачным альфа-каналом.
	/// </summary>
	PRISM_Color() { this->r = 0;  this->g = 0; this->b = 0, this->a = 255; }

	PRISM_Color operator+(PRISM_Color other) { return { this->r + other.r, this->g + other.g, this->b + other.b }; };
};

/// <summary>
/// Структура, представляющая треугольник в 3D пространстве.
/// Содержит три вершины и их нормали для расчёта освещения и других эффектов.
/// </summary>
struct PRISM_Triangle
{
	/// <summary>
	/// Первая вершина треугольника.
	/// Хранит координаты точки в пространстве.
	/// </summary>
	PRISM_Vector3d a;

	/// <summary>
	/// Вторая вершина треугольника.
	/// Хранит координаты точки в пространстве.
	/// </summary>
	PRISM_Vector3d b;
	
	/// <summary>
	/// Третья вершина треугольника.
	/// Хранит координаты точки в пространстве.
	/// </summary>
	PRISM_Vector3d c;
	
	/// <summary>
	/// Нормаль первой вершины треугольника.
	/// Используется для расчёта освещения.
	/// Если w == 1, нормаль активна.
	/// </summary>
	PRISM_Vector3d a_normal = { 0, 0, 0, 0 }; //нормаль точки a треугольника если w == 1 то она есть
	
	/// <summary>
	/// Нормаль второй вершины треугольника.
	/// Используется для расчёта освещения.
	/// Если w == 1, нормаль активна.
	/// </summary>
	PRISM_Vector3d b_normal = { 0, 0, 0, 0 }; //нормаль точки b треугольника если w == 1 то она есть
	
	/// <summary>
	/// Нормаль третьей вершины треугольника.
	/// Используется для расчёта освещения.
	/// Если w == 1, нормаль активна.
	/// </summary>
	PRISM_Vector3d c_normal = { 0, 0, 0, 0 }; //нормаль точки c треугольника если w == 1 то она есть
	
	/// <summary>
	/// Коэфициэнт диффузного освещения объекта.
	/// Диффузное освещение моделирует рассеивание света на матовой поверхности, при этом интенсивность освещенности зависит от угла падения света.
	/// </summary>
	PRISM_Vector3d diffuseColor;

	/// <summary>
	/// Коэффициент окружающего освещения объекта.
	/// Окружающее освещение равномерно распределяется по всему пространству и добавляет базовую освещенность объекту, даже если на него напрямую не падает свет.
	/// </summary>
	PRISM_Vector3d ambientColor;

	/// <summary>
	/// Коэффициент зеркального отражения объекта.
	/// Зеркальное отражение моделирует яркие блики, создаваемые на поверхности объекта, отражающего световый источник.
	/// </summary>
	PRISM_Vector3d specularColor;


	float shininess = 3.f;
	/// <summary>
	/// Степень блеска (shininess) для спекулярного отражения в треугольнике.
	/// </summary>
	/// <remarks>
	/// Значение определяет резкость блика на поверхности треугольника при использовании спекулярного освещения.
	/// Чем выше значение, тем более сфокусированным и острым будет блик.
	/// По умолчанию значение равно 3.0f.
	/// </remarks>
	/// <value>Положительное число с плавающей запятой.</value>
	
	
	/// <summary>
	/// Конструктор для создания треугольника с указанными вершинами.
	/// </summary>
	/// <param name="a_">Координаты первой вершины (по умолчанию {0, 0, 0}).</param>
	/// <param name="b_">Координаты второй вершины (по умолчанию {0, 0, 0}).</param>
	/// <param name="c_">Координаты третьей вершины (по умолчанию {0, 0, 0}).</param>
	PRISM_Triangle(PRISM_Vector3d a_ = {0.0f, 0.0f, 0.0f}, PRISM_Vector3d b_ = {0.0f, 0.0f, 0.0f}, PRISM_Vector3d c_ = {0.0f, 0.0f, 0.0f}) : a(a_), b(b_), c(c_) {}
	
	/// <summary>
	/// Выводит информацию о треугольнике в консоль.
	/// Отображает координаты вершин и значения нормалей.
	/// </summary>
	void print();
};

/// <summary>
/// Структура, представляющая 3D-меш, состоящий из набора треугольников.
/// Используется для моделирования объектов в трёхмерной графике.
/// </summary>
struct PRISM_Mesh
{
	/// <summary>
	/// Вектор треугольников, составляющих меш.
	/// Каждый треугольник содержит свои вершины и нормали.
	/// </summary>
	std::vector<PRISM_Triangle> tris;


	/// <summary>
	/// Выводит информацию о всех треугольниках меша в консоль.
	/// </summary>
	void print();
};



/// <summary>
/// Структура, представляющая цвет с компонентами в формате float (0.0 - 1.0).
/// Используется для OpenGL и других графических API.
/// </summary>
struct PRISM_GL_fColor {
	
	/// <summary>
	/// Красная компонента цвета (значение от 0.0 до 1.0).
	/// </summary>
	float r=0;

	/// <summary>
	/// Зелёная компонента цвета (значение от 0.0 до 1.0).
	/// </summary>
	float g=0;
	
	/// <summary>
	/// Синяя компонента цвета (значение от 0.0 до 1.0).
	/// </summary>
	float b=0;
};

/// <summary>
/// Структура, представляющая источник света в 3D пространстве.
/// Поддерживает настройку положения, цвета и интенсивности.
/// </summary>
struct PRISM_Light {
	/// <summary>
	/// Позиция источника света в 3D пространстве.
	/// </summary>
	PRISM_Vector3d position;

	/// <summary>
	/// Цвет света. Значение по умолчанию: белый (255, 255, 255).
	/// </summary>
	PRISM_Color color = {255, 255, 255};

	/// <summary>
	/// Интенсивность света (значение >= 0.0f). 
	/// Значение по умолчанию: 1.0f.
	/// </summary>
	float lightIntensity = 1.0f;          // Интенсивность света

	/// <summary>
	/// Выводит параметры света в консоль.
	/// </summary>
	void print();
};

struct PRISM_RenderMode {
	bool DisplayDimming1 = true; //затемнения
	bool DisplayDimming2 = false; //затемнения
	bool DisplayTriangleContours = false; //контуры
	bool Z_Buffer = true;
	bool ShowBackMesh = false;
	bool FillMesh = true;
	int ContourWidth = 5;
	void print();
};

#endif // OTHER_H
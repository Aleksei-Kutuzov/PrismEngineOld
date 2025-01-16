#ifndef ABSTRACTOBJECT3D_H
#define ABSTRACTOBJECT3D_H

// Created by Alexey on 15.06.2024.
//
#include "SDL.h"
#include "SDL_image.h"
#include "../PRISM_math/vector3D.h"
#include "../PRISM_math/matrix.h"
#include "../PRISM_math/other.h"
#include "../PRISM_math/math.h"
#include "../PRISM_rendering/painter.h"
#include "../PRISM_UI/joystick.h"
#include "../PRISM_rendering/zbuffer.h"
#include "../PRISM_objects3D/AbstractCamera3D.h"
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>
#include <ctime>
#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <chrono>


/// <summary>
/// Класс AbstractObject3D представляет собой базовый класс для работы с 3D-объектами.
/// Предоставляет функционал для управления трансформациями, работы с сеткой (mesh) и освещением.
/// </summary>
class AbstractObject3D {
		private:
			/// <summary>
			/// Матрица поворота обьекта по X
			/// </summary>
			struct PRISM_Matrix_4X4 matrixRotX;
			
			/// <summary>
			/// Матрица поворота обьекта по Y
			/// </summary>
			struct PRISM_Matrix_4X4 matrixRotY;
			
			/// <summary>
			/// Матрица поворота обьекта по Z
			/// </summary>
			struct PRISM_Matrix_4X4 matrixRotZ;
			
			/// <summary>
			/// Матрицы переноса обьекта (определяет положение по мировым координатам)
			/// </summary>
			struct PRISM_Matrix_4X4 matrixTranslate;
			
			/// <summary>
			/// Матрица масштаба обьекта.
			/// </summary>
			struct PRISM_Matrix_4X4 matrixScale; //transform
			
			/// <summary>
			/// Матрица вида.
			/// </summary>
			struct PRISM_Matrix_4X4 matrixView;
		public:
			/// <summary>
			/// Матрица проекции объекта.
			/// </summary>
			struct PRISM_Matrix_4X4 ProjectionMatrix;
			
			/// <summary>
			/// Координаты объекта.
			/// </summary>
			struct PRISM_Vector3d Translate;

			/// <summary>
			/// Углы поворота объекта (в градусах).
			/// </summary>
			struct PRISM_Vector3d Rotation;
			
			/// <summary>
			/// Масштаб объекта.
			/// </summary>
			struct PRISM_Vector3d Scale;

			/// <summary>
			/// Сетка (mesh) объекта.
			/// </summary>
			struct PRISM_Mesh mesh;
			
			
			/// <summary>
			/// Коэффициент отражения материала для окружающего света (в пределах от 0 до 1 для каждого цветового канала RGB).
			/// Ещё используется как коэфициэнт для дифузного света.
			/// </summary>
			struct PRISM_Vector3d materialAmbient={0.5f, 0.5f, 0.5f};

			/// <summary>
			/// Коэффициент зеркального отражения материала (от 0 для матовых поверхностей до 1 для блестящих).
			/// </summary>
			float kSpecular = 0.5;

			/// <summary>
			/// Ширина экрана.
			/// </summary>
			float ScreenW;

			/// <summary>
			/// Высота экрана.
			/// </summary>
			float ScreenH;

			/// <summary>
			/// Ссылка на камеру, связанную с объектом.
			/// </summary>
			AbstractCamera3D &Camera;

			/// <summary>
			/// Конструктор объекта.
			/// </summary>
			/// <param name="Coord">Начальные координаты объекта.</param>
			/// <param name="Rot">Начальные углы поворота.</param>
			/// <param name="Sc">Начальный масштаб.</param>
			/// <param name="camera">Ссылка на объект камеры.</param>
			AbstractObject3D(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d Sc, AbstractCamera3D &camera):Camera(camera) {
				Translate = Coord;
				Rotation = Rot;
				Scale = Sc;
				InitProjection(camera);
				SetMoveXYZ(Translate);
				SetRotateXYZ(Rotation);
				SetScaleXYZ(Scale);
			
			}

			/// <summary>
			/// Деструктор объекта.
			/// </summary>
			~AbstractObject3D() {

			}
		
			/// <summary>
			/// Устанавливает сетку (mesh) для объекта.
			/// </summary>
			/// <param name="m">Полигональная сетка.</param>
			void SetMesh(struct PRISM_Mesh m);
			
			/// <summary>
			/// Возвращает сетку объекта.
			/// </summary>
			/// <returns>Сетка объекта.</returns>
			struct PRISM_Mesh GetMesh();
		
			/// <summary>
			/// Инициализирует матрицу проекции с использованием камеры.
			/// </summary>
			/// <param name="camera">Объект камеры.</param>
			void InitProjection(AbstractCamera3D camera);
		
			/// <summary>
			/// Устанавливает углы поворота объекта.
			/// </summary>
			/// <param name="rotVect">Вектор углов поворота.</param>
			void SetRotateXYZ(struct PRISM_Vector3d rotVect);
			
			/// <summary>
			/// Устанавливает координаты объекта.
			/// </summary>
			/// <param name="moveVect">Вектор координат.</param>
			void SetMoveXYZ(struct PRISM_Vector3d moveVect);

			/// <summary>
			/// Устанавливает масштаб объекта.
			/// </summary>
			/// <param name="scaleVect">Вектор масштаба.</param>
			void SetScaleXYZ(struct PRISM_Vector3d scaleVect);

			/// <summary>
			/// Печатает информацию об объекте.
			/// </summary>
			void PrintInfo();
		
			/// <summary>
			/// Выполняет вращение треугольника.
			/// </summary>
			/// <param name="Triangle_">Треугольник.</param>
			/// <returns>Вращенный треугольник.</returns>
			PRISM_Triangle RotateTriangle(struct PRISM_Triangle Triangle_);
			
			/// <summary>
			/// Выполняет перенос треугольника.
			/// </summary>
			/// <param name="Triangle_">Треугольник.</param>
			/// <returns>Перемещенный треугольник.</returns>
			PRISM_Triangle TranslateTriangle(struct PRISM_Triangle Triangle_);

			/// <summary>
			/// Выполняет масштабирование треугольника.
			/// </summary>
			/// <param name="Triangle_">Треугольник.</param>
			/// <returns>Масштабированный треугольник.</returns>
			PRISM_Triangle ScaleTriangle(struct PRISM_Triangle Triangle_);
			
			/// <summary>
			/// Преобразует треугольник в координаты вида.
			/// </summary>
			/// <param name="Triangle_">Треугольник.</param>
			/// <returns>Треугольник в координатах вида.</returns>
			PRISM_Triangle ViewTriangle(struct PRISM_Triangle Triangle_);
		
			/// <summary>
			/// Вычисляет цвет с использованием модели освещения Фонга.
			/// </summary>
			///@deprecated Этот метод больше не рекомендуется к использованию. Используйте класс render для затемнений.
			/// <param name="normal">Нормаль к поверхности.</param>
			/// <param name="viewDir">Направление взгляда.</param>
			/// <param name="light">Источник света.</param>
			/// <param name="fragPos">Позиция фрагмента.</param>
			/// <returns>Цвет в формате PRISM_Color.</returns>
			PRISM_Color CalculatePhongShadingColor(const PRISM_Vector3d& normal, const PRISM_Vector3d& viewDir, const PRISM_Light& light, const PRISM_Vector3d& fragPos);
		
			/// <summary>
			/// Вычисляет барицентрические координаты.
			/// </summary>
			/// <param name="x">X-координата точки.</param>
			/// <param name="y">Y-координата точки.</param>
			/// <param name="v0">Вершина треугольника 0.</param>
			/// <param name="v1">Вершина треугольника 1.</param>
			/// <param name="v2">Вершина треугольника 2.</param>
			/// <param name="u">Результат для координаты u.</param>
			/// <param name="v">Результат для координаты v.</param>
			/// <param name="w">Результат для координаты w.</param>
			/// <returns>True, если координаты вычислены успешно.</returns>
			bool ComputeBarycentricCoords(float x, float y,
										  const PRISM_Vector3d& v0, const PRISM_Vector3d& v1, const PRISM_Vector3d& v2,
										  float& u, float& v, float& w);

			/// <summary>
			/// Отрисовывает треугольники сетки объекта.
			/// </summary>
			/// <param name="renderer">Указатель на SDL_Renderer для рендеринга.</param>
			/// <param name="rm">Режим рендеринга (линии, заполнение и т.д.).</param>
			void DrawMeshTriangles(SDL_Renderer* renderer, PRISM_RenderMode rm);

			/// <summary>
			/// Однопоточный, медленный метод для растеризации треугольника.
			/// </summary>
			/// <remarks>
			/// Используйте вместо этого TileRasterisation или Rasterisation.
			/// </remarks>
			///@deprecated Этот метод больше не рекомендуется к использованию. Используйте класс render для отрисовки.
			/// <param name="x1">Координата X первой точки треугольника.</param>
			/// <param name="y1">Координата Y первой точки треугольника.</param>
			/// <param name="x2">Координата X второй точки треугольника.</param>
			/// <param name="y2">Координата Y второй точки треугольника.</param>
			/// <param name="x3">Координата X третьей точки треугольника.</param>
			/// <param name="y3">Координата Y третьей точки треугольника.</param>
			/// <param name="z1">Глубина (Z-координата) первой точки.</param>
			/// <param name="z2">Глубина (Z-координата) второй точки.</param>
			/// <param name="z3">Глубина (Z-координата) третьей точки.</param>
			/// <param name="SDL_renderer">Указатель на SDL_Renderer для рендеринга.</param>
			/// <param name="light">Параметры освещения.</param>
			/// <param name="rgba">Цвет в формате RGBA.</param>
			/// <param name="RendMode">Режим рендеринга.</param>
			void OldRasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
							   SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
			
			/// <summary>
			/// Оптимизированный метод растеризации треугольника с использованием рёбер.
			/// </summary>
			///@deprecated Этот метод больше не рекомендуется к использованию. Используйте класс render для отрисовки.
			/// <param name="x1">Координата X первой точки треугольника.</param>
			/// <param name="y1">Координата Y первой точки треугольника.</param>
			/// <param name="x2">Координата X второй точки треугольника.</param>
			/// <param name="y2">Координата Y второй точки треугольника.</param>
			/// <param name="x3">Координата X третьей точки треугольника.</param>
			/// <param name="y3">Координата Y третьей точки треугольника.</param>
			/// <param name="z1">Глубина (Z-координата) первой точки.</param>
			/// <param name="z2">Глубина (Z-координата) второй точки.</param>
			/// <param name="z3">Глубина (Z-координата) третьей точки.</param>
			/// <param name="SDL_renderer">Указатель на SDL_Renderer для рендеринга.</param>
			/// <param name="light">Параметры освещения.</param>
			/// <param name="rgba">Цвет в формате RGBA.</param>
			/// <param name="RendMode">Режим рендеринга.</param>
			void OptimizedEdgeRasterization(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
			SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
			
			/// <summary>
			/// Растеризация треугольника для слабых мобильных устройств.
			/// </summary>
			///@deprecated Этот метод больше не рекомендуется к использованию. Используйте класс render для отрисовки.
			/// <param name="minX">Минимальное значение X плитки.</param>
			/// <param name="maxX">Максимальное значение X плитки.</param>
			/// <param name="minY">Минимальное значение Y плитки.</param>
			/// <param name="maxY">Максимальное значение Y плитки.</param>
			/// <param name="v0">Вершина треугольника 1.</param>
			/// <param name="v1">Вершина треугольника 2.</param>
			/// <param name="v2">Вершина треугольника 3.</param>
			/// <param name="SDL_renderer">Указатель на SDL_Renderer для рендеринга.</param>
			/// <param name="light">Параметры освещения.</param>
			/// <param name="rgba">Цвет в формате RGBA.</param>
			/// <param name="RendMode">Режим рендеринга.</param>
			/// <param name="surfaces">Список SDL_Surface для буферизации.</param>
			void RasterizeTile(int minX, int maxX, int minY, int maxY,
							   const PRISM_Vector3d& v0, const PRISM_Vector3d& v1, const PRISM_Vector3d& v2,
							   SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4],
							   PRISM_RenderMode RendMode, std::vector<SDL_Surface*>& surfaces);

			/// <summary>
			/// Устаревший метод растеризации треугольника.
			/// </summary>
			///@deprecated Этот метод больше не рекомендуется к использованию. Используйте класс render для отрисовки.
			/// <remarks>
			/// Используйте TileRasterisation для большей производительности.
			/// </remarks>
			/// <param name="x1">Координата X первой точки треугольника.</param>
			/// <param name="y1">Координата Y первой точки треугольника.</param>
			/// <param name="x2">Координата X второй точки треугольника.</param>
			/// <param name="y2">Координата Y второй точки треугольника.</param>
			/// <param name="x3">Координата X третьей точки треугольника.</param>
			/// <param name="y3">Координата Y третьей точки треугольника.</param>
			/// <param name="z1">Глубина (Z-координата) первой точки.</param>
			/// <param name="z2">Глубина (Z-координата) второй точки.</param>
			/// <param name="z3">Глубина (Z-координата) третьей точки.</param>
			/// <param name="SDL_renderer">Указатель на SDL_Renderer для рендеринга.</param>
			/// <param name="light">Параметры освещения.</param>
			/// <param name="rgba">Цвет в формате RGBA.</param>
			/// <param name="RendMode">Режим рендеринга.</param>
			void Rasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
							   SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);

			/// <summary>
			/// Метод растеризации с использованием плиток для оптимизации.
			/// </summary>
			///@deprecated Этот метод больше не рекомендуется к использованию. Используйте класс render для отрисовки.
			/// <param name="x1">Координата X первой точки треугольника.</param>
			/// <param name="y1">Координата Y первой точки треугольника.</param>
			/// <param name="x2">Координата X второй точки треугольника.</param>
			/// <param name="y2">Координата Y второй точки треугольника.</param>
			/// <param name="x3">Координата X третьей точки треугольника.</param>
			/// <param name="y3">Координата Y третьей точки треугольника.</param>
			/// <param name="z1">Глубина (Z-координата) первой точки.</param>
			/// <param name="z2">Глубина (Z-координата) второй точки.</param>
			/// <param name="z3">Глубина (Z-координата) третьей точки.</param>
			/// <param name="SDL_renderer">Указатель на SDL_Renderer для рендеринга.</param>
			/// <param name="light">Параметры освещения.</param>
			/// <param name="rgba">Цвет в формате RGBA.</param>
			/// <param name="RendMode">Режим рендеринга.</param>
			void TileRasterisation(int x1, int y1, int x2, int y2, int x3, int y3,
								   float z1, float z2, float z3, SDL_Renderer* SDL_renderer,
								   PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
		
};

#endif // ABSTRACTOBJECT3D_H
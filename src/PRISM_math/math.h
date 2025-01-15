#pragma once
#ifndef PRISM_MATH_H
#define PRISM_MATH_H


#include <vector>
#include <SDL_stdinc.h>
#include <SDL.h>
#include "vector3D.h"
#include "matrix.h"
#include "other.h"


/// <summary>
/// Класс Math предоставляет набор статических методов для выполнения математических операций,
/// связанных с векторами, матрицами и цветами.
/// </summary>
class Math {
public:
    /// <summary>
    /// Преобразует угол из градусов в радианы.
    /// </summary>
    /// <param name="degrees">Угол в градусах.</param>
    /// <returns>Угол в радианах.</returns>
    static float degToRad(float degrees);

    /// <summary>
    /// Вычисляет скалярное произведение двух векторов.
    /// </summary>
    /// <param name="v1">Первый вектор.</param>
    /// <param name="v2">Второй вектор.</param>
    /// <returns>Скалярное произведение.</returns>
    static float Vector_DotProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2);

    /// <summary>
    /// Вычисляет длину вектора.
    /// </summary>
    /// <param name="v">Вектор.</param>
    /// <returns>Длина вектора.</returns>
    static float Vector_Length(PRISM_Vector3d& v);

    /// <summary>
    /// Нормализует вектор, делая его длину равной 1.
    /// </summary>
    /// <param name="v">Вектор для нормализации.</param>
    /// <returns>Нормализованный вектор.</returns>
    static PRISM_Vector3d Vector_Normalise(PRISM_Vector3d& v);

    /// <summary>
    /// Вычисляет векторное произведение двух векторов.
    /// </summary>
    /// <param name="v1">Первый вектор.</param>
    /// <param name="v2">Второй вектор.</param>
    /// <returns>Вектор, являющийся результатом векторного произведения.</returns>
    static PRISM_Vector3d Vector_CrossProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2);

    /// <summary>
    /// Вычисляет точку пересечения линии и плоскости.
    /// </summary>
    /// <param name="plane_p">Точка на плоскости.</param>
    /// <param name="plane_n">Нормаль плоскости.</param>
    /// <param name="lineStart">Начальная точка линии.</param>
    /// <param name="lineEnd">Конечная точка линии.</param>
    /// <returns>Точка пересечения.</returns>
    static PRISM_Vector3d Vector_IntersectPlane(PRISM_Vector3d& plane_p, PRISM_Vector3d& plane_n, PRISM_Vector3d& lineStart, PRISM_Vector3d& lineEnd);

    /// <summary>
    /// Создает единичную матрицу 4x4.
    /// </summary>
    /// <returns>Единичная матрица.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeIdentity();

    /// <summary>
    /// Создает матрицу поворота вокруг оси X.
    /// </summary>
    /// <param name="fAngleRad">Угол поворота в радианах.</param>
    /// <returns>Матрица поворота вокруг оси X.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeRotationX(float fAngleRad);

    /// <summary>
    /// Создает матрицу поворота вокруг оси Y.
    /// </summary>
    /// <param name="fAngleRad">Угол поворота в радианах.</param>
    /// <returns>Матрица поворота вокруг оси Y.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeRotationY(float fAngleRad);

    /// <summary>
    /// Создает матрицу поворота вокруг оси Z.
    /// </summary>
    /// <param name="fAngleRad">Угол поворота в радианах.</param>
    /// <returns>Матрица поворота вокруг оси Z.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeRotationZ(float fAngleRad);

    /// <summary>
    /// Создает матрицу переноса.
    /// </summary>
    /// <param name="x">Смещение по оси X.</param>
    /// <param name="y">Смещение по оси Y.</param>
    /// <param name="z">Смещение по оси Z.</param>
    /// <returns>Матрица переноса.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeTranslation(float x, float y, float z);

    /// <summary>
    /// Создает матрицу масштабирования.
    /// </summary>
    /// <param name="x">Масштабирование по оси X.</param>
    /// <param name="y">Масштабирование по оси Y.</param>
    /// <param name="z">Масштабирование по оси Z.</param>
    /// <returns>Матрица масштабирования.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeScale(float x, float y, float z);

    /// <summary>
    /// Создает матрицу проекции.
    /// </summary>
    /// <param name="fFovDegrees">Угол обзора в градусах.</param>
    /// <param name="fAspectRatio">Соотношение сторон экрана.</param>
    /// <param name="fNear">Ближняя плоскость отсечения.</param>
    /// <param name="fFar">Дальняя плоскость отсечения.</param>
    /// <returns>Матрица проекции.</returns>
    static PRISM_Matrix_4X4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);

    /// <summary>
    /// Умножает две матрицы 4x4.
    /// </summary>
    /// <param name="m1">Первая матрица.</param>
    /// <param name="m2">Вторая матрица.</param>
    /// <returns>Результирующая матрица.</returns>
    static PRISM_Matrix_4X4 Matrix_MultiplyMatrix(PRISM_Matrix_4X4& m1, PRISM_Matrix_4X4& m2);

    /// <summary>
    /// Создает матрицу, указывающую из одной точки в другую.
    /// </summary>
    /// <param name="pos">Начальная точка.</param>
    /// <param name="target">Целевая точка.</param>
    /// <param name="up">Вектор "вверх".</param>
    /// <returns>Матрица направления.</returns>
    static PRISM_Matrix_4X4 Matrix_PointAt(PRISM_Vector3d& pos, PRISM_Vector3d& target, PRISM_Vector3d& up);

    /// <summary>
    /// Быстрое обратное преобразование матрицы 4x4.
    /// </summary>
    /// <param name="m">Матрица для инверсии.</param>
    /// <returns>Инверсированная матрица.</returns>
    static PRISM_Matrix_4X4 Matrix_QuickInverse(PRISM_Matrix_4X4& m);

    /// <summary>
    /// Умножает вектор на матрицу.
    /// </summary>
    /// <param name="i">Исходный вектор.</param>
    /// <param name="o">Результирующий вектор.</param>
    /// <param name="m">Матрица.</param>
    static void MultiplyMatrixVector(PRISM_Vector3d& i, PRISM_Vector3d& o, PRISM_Matrix_4X4& m);

    /// <summary>
    /// Вычисляет нормали треугольника.
    /// </summary>
    /// <param name="triang">Треугольник.</param>
    /// <returns>Нормаль треугольника.</returns>
    static PRISM_Vector3d CalculateNormals(struct PRISM_Triangle triang);

    /// <summary>
    /// Конвертирует цвет в формат OpenGL.
    /// </summary>
    /// <param name="color">Цвет в формате PRISM_Color.</param>
    /// <returns>Цвет в формате OpenGL.</returns>
    static PRISM_GL_fColor convertToGlColor(const PRISM_Color& color);
};


#endif // PRISM_MATH_H
#ifndef PRISM_MATRIX_H
#define PRISM_MATRIX_H

#include "vector3D.h"
#include <cmath>
#include <stdexcept>
#include <SDL.h>
/// <summary>
/// Структура PRISM_Matrix_4X4 представляет 4x4 матрицу, которая может быть 
/// использована для различных линейных преобразований, таких как масштабирование, 
/// вращение, перенос, а также для работы с однородными координатами.
/// </summary>
struct PRISM_Matrix_4X4
{
	/// <summary>
	/// Двумерный массив, представляющий элементы матрицы. 
	/// Индексы: m[row][column].
	/// Инициализируется нулями.
	/// </summary>
	float m[4][4] = {0};

	/// <summary>
	/// Выводит содержимое матрицы в консоль.
	/// </summary>
	void print();

	/// <summary>
	/// Оператор доступа к строкам матрицы по индексу.
	/// </summary>
	/// <param name="index">Индекс строки (0-3).</param>
	/// <returns>Указатель на строку матрицы.</returns>
	/// <exception cref="std::out_of_range">Бросает исключение, если индекс выходит за пределы [0, 3].</exception>
	float* operator[](int index);

	/// <summary>
	/// Оператор сравнения двух матриц на равенство.
	/// </summary>
	/// <param name="other">Другая матрица для сравнения.</param>
	/// <returns>True, если все элементы матриц равны; иначе False.</returns>
	bool operator==(PRISM_Matrix_4X4& other);

};


#endif // MATRIX_H
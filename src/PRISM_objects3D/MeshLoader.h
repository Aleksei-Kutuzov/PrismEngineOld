#pragma once


#include "AbstractObject3D.h"


    /// <summary>
    /// Класс для загрузки 3D-моделей из файлов.
    /// </summary>
class MeshLoader
{
public:
    /// <summary>
    /// Загружает 3D-модель из файла в формате OBJ.
    /// </summary>
    /// <remarks>
    /// Материалы (MTL) также обрабатываются обрабатываются этим методом.
    /// Информация о текстурах не поддерживается на даннный момент.
    /// Если файл не найден или имеет неверный формат, метод может вернуть пустую или некорректную сетку.
    /// Если вы экспортируете из blender поставьте галочку на Normals (если нужно освещение по Фонгу и похожие системы освещенияя)
    /// </remarks>
    /// <param name="filename">Путь к файлу OBJ для загрузки.</param>
    /// <param name="camera">Камера, которая будет использоваться для преобразования модели.</param>
    /// <returns>Объект типа <c>PRISM_Mesh</c>, содержащий данные загруженной модели.</returns>
    static PRISM_Mesh LoadOBJ(const char* filename, AbstractCamera3D camera);
private:

};




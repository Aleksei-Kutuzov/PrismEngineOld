#pragma once
#include <vector>
#include <map>
#include "AbstractCamera3D.h"
#include "AbstractObject3D.h"
#include "../PRISM_rendering/render.h"

/// <summary>
/// Класс, представляющий 3D-сцену, содержащую камеры, объекты и параметры освещения.
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Конструктор по умолчанию.
	/// </summary>
	Scene();

	/// <summary>
	/// Деструктор сцены. Очищает все объекты и камеры, добавленные в сцену.
	/// </summary>
	~Scene();

	/// <summary>
	/// Добавляет камеру в сцену.
	/// </summary>
	/// <param name="obj">Указатель на объект камеры, который нужно добавить.</param>
	/// <returns>Указатель на добавленную камеру.</returns>
	AbstractCamera3D* AddObject(AbstractCamera3D *obj);

	/// <summary>
	/// Добавляет 3D-объект в сцену.
	/// </summary>
	/// <param name="obj">Указатель на объект, который нужно добавить.</param>
	/// <returns>Указатель на добавленный объект.</returns>
	AbstractObject3D* AddObject(AbstractObject3D *obj);


	/// <summary>
	/// Удаляет камеру из сцены.
	/// </summary>
	/// <param name="obj">Указатель на объект камеры, который нужно удалить.</param>
	/// <returns>Указатель на удалённую камеру или nullptr, если камера не найдена.</returns>
	AbstractCamera3D* DelObject(AbstractCamera3D* obj);

	/// <summary>
	/// Удаляет 3D-объект из сцены.
	/// </summary>
	/// <param name="obj">Указатель на объект, который нужно удалить.</param>
	/// <returns>Указатель на удалённый объект или nullptr, если объект не найден.</returns>
	AbstractObject3D* DelObject(AbstractObject3D* obj);

	/// <summary>
	/// Выводит информацию о сцене.
	/// </summary>
	void PrintInfo();

	/// <summary>
	/// Устанавливает активную камеру для рендера сцены.
	/// </summary>
	/// <param name="obj">Указатель на камеру, которую нужно сделать активной.</param>
	/// <returns>Указатель на установленную активную камеру.</returns>
	AbstractCamera3D* SetCamera(AbstractCamera3D* obj);

	AbstractCamera3D* GetCamera();

	/// <summary>
	/// Устанавливает окружающий свет (ambient light) а также коэффициент дифузного света (diffuse light) для сцены (это один коэффициент для двух частей освещения).
	/// </summary>
	/// <param name="L_Ambient">Вектор с коэффициентами освещения для R, G и B каналов (значения от 0 до 1).</param>
	void SetLightAmbient(PRISM_Vector3d L_Ambient);
	
	/// <summary>
	/// Возвращает текущие настройки окружающего света (ambient light) или дифузного света (diffuse light) сцены (это один коэффициент для двух частей освещения).
	/// </summary>
	/// <returns>Вектор с коэффициентами освещения для R, G и B каналов.</returns>
	PRISM_Vector3d GetLightAmbient() const;

	/// <summary>
	/// Выполняет рендер сцены.
	/// </summary>
	/// <param name="win">Указатель на объект окна для рендера.</param>
	void Render(PRISM_Window* win);

private:
	/// <summary>
	/// Вектор указателей на 3D-объекты, добавленные в сцену.
	/// </summary>
	std::vector<AbstractObject3D*> objects;        

	/// <summary>
	/// Вектор указателей на камеры, добавленные в сцену.
	/// </summary>
	std::vector<AbstractCamera3D*> cameras;

	/// <summary>
	/// Указатель на текущую активную камеру для рендера.
	/// </summary>
	AbstractCamera3D* enabledCamera;

	/// <summary>
	/// Объект для выполнения операций рендеринга.
	/// </summary>
	PRISM_Render render;

};
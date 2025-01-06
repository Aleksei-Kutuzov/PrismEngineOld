#pragma once
#include <vector>
#include <map>
#include "AbstractCamera3D.h"
#include "AbstractObject3D.h"
#include "../PRISM_rendering/render.h"


class Scene
{
public:
	Scene();
	~Scene();
	AbstractCamera3D* AddObject(AbstractCamera3D *obj);
	AbstractObject3D* AddObject(AbstractObject3D *obj);
	//bool AddObject(AbstractCamera3D* obj, int id);
	//bool AddObject(AbstractObject3D* obj, int id);
	//bool AddObject(AbstractCamera3D* obj, char name);
	//bool AddObject(AbstractObject3D* obj, char name);	


	AbstractCamera3D* DelObject(AbstractCamera3D* obj);
	AbstractObject3D* DelObject(AbstractObject3D* obj);
	//bool DelObject(AbstractCamera3D* obj, int id);
	//bool DelObject(AbstractObject3D* obj, int id);
	//bool DelObject(AbstractCamera3D* obj, char name);
	//bool DelObject(AbstractObject3D* obj, char name);

	void PrintInfo();
	AbstractCamera3D* SetCamera(AbstractCamera3D* obj);

	void SetLightAmbient(PRISM_Vector3d L_Ambient);
	PRISM_Vector3d GetLightAmbient() const;

	void Render(PRISM_Window* win);

private:
	std::vector<AbstractObject3D*> objects;        // Вектор указателей на 3D объекты
	std::vector<AbstractCamera3D*> cameras;        // Вектор указателей на камеры
	AbstractCamera3D* enabledCamera;

	PRISM_Render render;
	//	std::map<_CamObj, >;
	//	std::map<_3dObj, >;

};
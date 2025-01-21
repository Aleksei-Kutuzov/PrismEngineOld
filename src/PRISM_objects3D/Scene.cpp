#include "Scene.h"



Scene::Scene()
{
}

Scene::~Scene()
{	
	for (AbstractObject3D* object : objects) {
		if (object) {
			//delete object;
		}
	}
	objects.clear();

	for (AbstractCamera3D* camera : cameras) {
		//delete camera;
	}
	cameras.clear();
}

AbstractCamera3D* Scene::AddObject(AbstractCamera3D* obj)
{
	cameras.push_back(obj);
	return obj;
}

AbstractObject3D* Scene::AddObject(AbstractObject3D* obj)
{
	objects.push_back(obj);
	return obj;
}

AbstractCamera3D* Scene::DelObject(AbstractCamera3D* obj)
{
	cameras.erase(remove(cameras.begin(), cameras.end(), obj), cameras.end());
	return obj;
}

AbstractObject3D* Scene::DelObject(AbstractObject3D* obj)
{
	objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());
	return obj;
}


void Scene::PrintInfo()
{
	for (const auto& object : objects) {
		SDL_Log("objects in Scene:");
		object->PrintInfo();  
	}

}

AbstractCamera3D* Scene::SetCamera(AbstractCamera3D* obj)
{
	enabledCamera = obj;
	render.cameraCoordinate = obj->Translate;
	return obj;
}

void Scene::SetLightAmbient(PRISM_Vector3d L_Ambient)
{
	render.lightAmbient = L_Ambient;
}

PRISM_Vector3d Scene::GetLightAmbient() const
{
	return render.lightAmbient;
}

void Scene::Render(PRISM_Window* win)
{
	glOrtho(-1, 1, -1, 1, -enabledCamera->FNear, enabledCamera->FFar);
	render.SetScreenSize(win->GetW(), win->GetH());
	for (AbstractObject3D* object :objects) {
		render.Rendering(win, object);
	}
}


#include "render.h"

PRISM_Color PRISM_Render::CalculatePixelAmbient(PRISM_Color originalСolor, AbstractObject3D obj, PRISM_Triangle triangle) const
{
	unsigned char r = (unsigned char)((float)originalСolor.r * triangle.ambientColor.x * lightAmbient.x);
	unsigned char g = (unsigned char)((float)originalСolor.g * triangle.ambientColor.y * lightAmbient.y);
	unsigned char b = (unsigned char)((float)originalСolor.b * triangle.ambientColor.z * lightAmbient.z);

	return PRISM_Color{r, g, b};
}

PRISM_Color PRISM_Render::CalculatePixelDiffuse(PRISM_Color originalСolor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle)
{
	PRISM_Color lightDiffuse = light.color;
	PRISM_Vector3d materialDiffuse = triangle.diffuseColor;
	PRISM_Vector3d normal = Math::CalculateNormals(triangle);
	PRISM_Vector3d lightDir = { .0f, .0f, -1.0f };

	PRISM_Vector3d centroid = { (triangle.a.x + triangle.b.x + triangle.c.x) / 3,
								(triangle.a.y + triangle.b.y + triangle.c.y) / 3,
								(triangle.a.z + triangle.b.z + triangle.c.z) / 3 };

	lightDir = { light.position.x - centroid.x, light.position.y - centroid.y, light.position.z - centroid.z };
	lightDir = Math::Vector_Normalise(lightDir);
	

	float cosNL = std::max(0.f, Math::Vector_DotProduct(normal, lightDir)); // косинус угла между нормалью и направлением света, с отсечением отрицательных значений
	
	return PRISM_Color((unsigned char)(lightDiffuse.r * materialDiffuse.x * cosNL),
					   (unsigned char)(lightDiffuse.g * materialDiffuse.y * cosNL),
					   (unsigned char)(lightDiffuse.b * materialDiffuse.z * cosNL));
}

PRISM_Color PRISM_Render::CalculatePixelSpecular(PRISM_Color originalСolor, PRISM_Light light, AbstractObject3D obj, PRISM_Triangle triangle, PRISM_Vector3d cameraCoordinate)
{

	PRISM_Vector3d normal = Math::CalculateNormals(triangle);
	PRISM_Vector3d centroid = { (triangle.a.x + triangle.b.x + triangle.c.x) / 3,
								(triangle.a.y + triangle.b.y + triangle.c.y) / 3,
								(triangle.a.z + triangle.b.z + triangle.c.z) / 3 };

	PRISM_Vector3d notNormalLightDir = { light.position.x - centroid.x, light.position.y - centroid.y, light.position.z - centroid.z };
	PRISM_Vector3d lightDir = Math::Vector_Normalise(notNormalLightDir);

	PRISM_Vector3d reflectDir = (normal * (2.0f * Math::Vector_DotProduct(normal, lightDir))) - lightDir;
	reflectDir = Math::Vector_Normalise(reflectDir);

	PRISM_Vector3d viewDir = { cameraCoordinate.x - centroid.x, cameraCoordinate.y - centroid.y, cameraCoordinate.z - centroid.z };
	viewDir = Math::Vector_Normalise(viewDir);

	float spec = std::max(0.f, Math::Vector_DotProduct(reflectDir, viewDir));
	float shininess = triangle.shininess;
	float specular = (unsigned char)std::min(255.0f, light.lightIntensity * 255/2 * std::pow(spec, shininess));

	
	PRISM_Color specularСolor = { originalСolor.r * specular * 1.f / 255.f * triangle.specularColor.x, originalСolor.g * specular * 1.f/255.f * triangle.specularColor.y, originalСolor.b * specular * 1.f / 255.f * triangle.specularColor.y };
	return specularСolor;
}

void PRISM_Render::UpdateVertexAmbient(PRISM_Window* window, PRISM_Color originalСolor, PRISM_Triangle triangle) const
{
	return ;
}

void PRISM_Render::Rendering(PRISM_Window* window, AbstractObject3D* obj)
{
	for (auto& triangle : obj->mesh.tris) {
		struct PRISM_Triangle TriangleRotated, TriangleTranslated, TriangleScaled, TriangleProjected, TriangleViewed;

		TriangleScaled = obj->ScaleTriangle(triangle);
		TriangleRotated = obj->RotateTriangle(TriangleScaled);
		TriangleTranslated = obj->TranslateTriangle(TriangleRotated);
		TriangleViewed = obj->ViewTriangle(TriangleTranslated);

		Math::MultiplyMatrixVector(TriangleViewed.a, TriangleProjected.a,
			obj->ProjectionMatrix);
		Math::MultiplyMatrixVector(TriangleViewed.b, TriangleProjected.b,
			obj->ProjectionMatrix);
		Math::MultiplyMatrixVector(TriangleViewed.c, TriangleProjected.c,
			obj->ProjectionMatrix);
		PRISM_Vector3d normal = Math::CalculateNormals(TriangleProjected);

		if (normal.x * (TriangleProjected.a.x - obj->Camera.Translate.x) +
			normal.y * (TriangleProjected.a.y - obj->Camera.Translate.y) +
			normal.z * (TriangleProjected.a.z - obj->Camera.Translate.z) < 0.0f) {

			// Цветовые параметры треугольника
			TriangleViewed.ambientColor = triangle.ambientColor;
			TriangleViewed.diffuseColor = triangle.diffuseColor;
			TriangleViewed.specularColor = triangle.specularColor;
			

			PRISM_Vector3d Z_values = { TriangleTranslated.a.z / 100,
										TriangleTranslated.b.z / 100,
										TriangleTranslated.c.z / 100 };

			TriangleProjected.a.z = Z_values.x; TriangleProjected.b.z = Z_values.y; TriangleProjected.c.z = Z_values.z;

			PRISM_Light light; light.color = { 255, 255, 255 }; light.position = {0, 0, -2};
			PRISM_Color colorDiffuse = CalculatePixelDiffuse({ 1, 1, 1 }, light, *obj, TriangleViewed);
			//PRISM_Color color = CalculatePixelAmbient({ 255, 255, 255 }, *obj);
			PRISM_Color collorAmbient = CalculatePixelAmbient({ 1, 1, 1 }, *obj, TriangleViewed);
			PRISM_Color collorSpecular = CalculatePixelSpecular({ 1, 1, 1 }, light, *obj, TriangleViewed, cameraCoordinate);

			

			PRISM_Painter::DrawTriangle3D(window, TriangleProjected, { colorDiffuse.r + collorAmbient.r + collorSpecular.r,
																	   colorDiffuse.g + collorAmbient.g + collorSpecular.g,
																	   colorDiffuse.b + collorAmbient.b + collorSpecular.b });
		}


	}
}

void PRISM_Render::SetScreenSize(int w, int h)
{
	ScreenW = w;
	ScreenH = h;
}

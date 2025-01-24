#include "render.h"

PRISM_Color PRISM_Render::CalculatePixelAmbient(PRISM_Color originalСolor, PRISM_Triangle triangle) const
{
	unsigned char r = (unsigned char)((float)originalСolor.r * triangle.ambientColor.x * lightAmbient.x);
	unsigned char g = (unsigned char)((float)originalСolor.g * triangle.ambientColor.y * lightAmbient.y);
	unsigned char b = (unsigned char)((float)originalСolor.b * triangle.ambientColor.z * lightAmbient.z);

	return PRISM_Color{r, g, b};
}


PRISM_Color* PRISM_Render::CalculatePixelDiffuse(PRISM_Color originalСolor, PRISM_Light light, PRISM_Triangle triangle) const
{
	PRISM_Color lightDiffuse = light.color;
	PRISM_Vector3d materialDiffuse = triangle.diffuseColor;
	PRISM_Vector3d normal = Math::CalculateNormals(triangle);
	PRISM_Vector3d normal_a = triangle.a_normal; 	PRISM_Vector3d normal_b = triangle.b_normal;PRISM_Vector3d normal_c = triangle.c_normal;

	PRISM_Vector3d centroid = { (triangle.a.x + triangle.b.x + triangle.c.x) / 3,
								(triangle.a.y + triangle.b.y + triangle.c.y) / 3,
								(triangle.a.z + triangle.b.z + triangle.c.z) / 3 };

	PRISM_Vector3d lightDir = { light.position.x - centroid.x, light.position.y - centroid.y, light.position.z - centroid.z };
	lightDir = Math::Vector_Normalise(lightDir);

	PRISM_Vector3d lightDir_a = { light.position.x - triangle.a.x, light.position.y - triangle.a.y, light.position.z - triangle.a.z };
	lightDir_a = Math::Vector_Normalise(lightDir_a);

	PRISM_Vector3d lightDir_b = { light.position.x - triangle.b.x, light.position.y - triangle.b.y, light.position.z - triangle.b.z };
	lightDir_b = Math::Vector_Normalise(lightDir_b);

	PRISM_Vector3d lightDir_c = { light.position.x - triangle.c.x, light.position.y - triangle.c.y, light.position.z - triangle.c.z };
	lightDir_c = Math::Vector_Normalise(lightDir_c);

	float cosNL_a = std::max(0.f, Math::Vector_DotProduct(normal_a, lightDir_a)); float cosNL_b = std::max(0.f, Math::Vector_DotProduct(normal_b, lightDir_b)); float cosNL_c = std::max(0.f, Math::Vector_DotProduct(normal_c, lightDir_c));
	float cosNL = std::max(0.f, Math::Vector_DotProduct(normal, lightDir)); // косинус угла между нормалью и направлением света, с отсечением отрицательных значений
	
	


	
	
	return new PRISM_Color[3]{ PRISM_Color((unsigned char)(lightDiffuse.r * materialDiffuse.x * cosNL_a), (unsigned char)(lightDiffuse.g * materialDiffuse.y * cosNL_a), (unsigned char)(lightDiffuse.b * materialDiffuse.z * cosNL_a)),
								PRISM_Color((unsigned char)(lightDiffuse.r * materialDiffuse.x * cosNL_b), (unsigned char)(lightDiffuse.g * materialDiffuse.y * cosNL_b), (unsigned char)(lightDiffuse.b * materialDiffuse.z * cosNL_b)),
								PRISM_Color((unsigned char)(lightDiffuse.r * materialDiffuse.x * cosNL_c), (unsigned char)(lightDiffuse.g * materialDiffuse.y * cosNL_c), (unsigned char)(lightDiffuse.b * materialDiffuse.z * cosNL_c)) };
}

PRISM_Color PRISM_Render::CalculatePixelSpecular(PRISM_Color originalСolor, PRISM_Light light, PRISM_Triangle triangle, PRISM_Vector3d cameraCoordinate) const
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
	PRISM_Light light; light.color = { 255, 255, 255 }; light.position = { 0, 0, -15 };
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
			

			PRISM_Vector3d Z_values = { TriangleTranslated.a.z,
										TriangleTranslated.b.z,
										TriangleTranslated.c.z  };

			//TriangleProjected.a.z = Z_values.x; TriangleProjected.b.z = Z_values.y; TriangleProjected.c.z = Z_values.z;
			PRISM_Color collorAmbient = CalculatePixelAmbient({ 1, 1, 1 }, TriangleViewed);
			PRISM_Color* colorDiffuse = CalculatePixelDiffuse({ 1, 1, 1 }, light, TriangleViewed);
			PRISM_Color collorSpecular = CalculatePixelSpecular({ 1, 1, 1 }, light, TriangleViewed, cameraCoordinate);
			PRISM_Color color_a = colorDiffuse[0]; PRISM_Color color_b = colorDiffuse[1]; PRISM_Color color_c = colorDiffuse[2];

			PRISM_Painter::DrawInterpolatedTriangle3D(window, TriangleProjected, color_a + collorAmbient + collorSpecular,
																				 color_b + collorAmbient + collorSpecular,
				                                                                 color_c + collorAmbient + collorSpecular);
		}
	}
}

void PRISM_Render::SetScreenSize(int w, int h)
{
	ScreenW = w;
	ScreenH = h;
}
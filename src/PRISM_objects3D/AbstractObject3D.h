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


class AbstractObject3D {
		private:
		struct PRISM_Matrix_4X4 matrixRotZ, matrixRotX, matrixRotY, matrixTranslate, matrixScale; //transform
		struct PRISM_Matrix_4X4 matrixView;
		public:
		struct PRISM_Matrix_4X4 ProjectionMatrix;
		struct PRISM_Vector3d Coordinate;
		struct PRISM_Vector3d Rotation;
		struct PRISM_Vector3d Scale;
		struct PRISM_Mesh mesh;
		struct PRISM_Vector3d materialAmbient={0.5f, 0.5f, 0.5f};// коэффициент отражения материала для окружающего света(в пределах от 0 до 1 для каждого цветового канала RGB)
		float kSpecular = 0.5; // коэффициент зеркального отражения материала (0 для матовых поверхностей, до 1 для блестящих).
		float ScreenW;
		float ScreenH;
		AbstractCamera3D &Camera;

		AbstractObject3D(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d Sc, AbstractCamera3D &camera):Camera(camera) {
			Coordinate = Coord;
			Rotation = Rot;
			Scale = Sc;
			InitProjection(camera);
			SetMoveXYZ(Coordinate);
			SetRotateXYZ(Rotation);
			SetScaleXYZ(Scale);
			
		}

		~AbstractObject3D() {

		}
		
		void SetMesh(struct PRISM_Mesh m);
		struct PRISM_Mesh GetMesh();
		
		
		void InitProjection(AbstractCamera3D camera);
		
		void SetRotateXYZ(struct PRISM_Vector3d rotVect);
		void SetMoveXYZ(struct PRISM_Vector3d moveVect);
		void SetScaleXYZ(struct PRISM_Vector3d scaleVect);

		void PrintInfo();
		
		PRISM_Triangle RotateTriangle(struct PRISM_Triangle Triangle_);
		PRISM_Triangle TranslateTriangle(struct PRISM_Triangle Triangle_);
		PRISM_Triangle ScaleTriangle(struct PRISM_Triangle Triangle_);
		PRISM_Triangle ViewTriangle(struct PRISM_Triangle Triangle_);
		

		PRISM_Color CalculatePhongShadingColor(const PRISM_Vector3d& normal, const PRISM_Vector3d& viewDir, const PRISM_Light& light, const PRISM_Vector3d& fragPos);
		
		bool ComputeBarycentricCoords(float x, float y,
									  const PRISM_Vector3d& v0, const PRISM_Vector3d& v1, const PRISM_Vector3d& v2,
									  float& u, float& v, float& w);


		/*
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			these methods have been removed from header because they are outdated and irrelevant, they will be rewritten
		*/
		
		void DrawMeshTriangles(SDL_Renderer* renderer, PRISM_RenderMode rm);
		void OldRasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
						   SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
		void OptimizedEdgeRasterization(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
		SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
		void RasterizeTile(int minX, int maxX, int minY, int maxY,
						   const PRISM_Vector3d& v0, const PRISM_Vector3d& v1, const PRISM_Vector3d& v2,
						   SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4],
			               PRISM_RenderMode RendMode, std::vector<SDL_Surface*>& surfaces);
		void Rasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
						   SDL_Renderer* SDL_renderer, PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
		void TileRasterisation(int x1, int y1, int x2, int y2, int x3, int y3,
							   float z1, float z2, float z3, SDL_Renderer* SDL_renderer,
			                   PRISM_Light light, short rgba[4], PRISM_RenderMode RendMode);
		
		/*
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		*/
};

#endif // ABSTRACTOBJECT3D_H
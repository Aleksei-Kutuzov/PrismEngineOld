#ifndef ABSTRACTOBJECT3D_H
#define ABSTRACTOBJECT3D_H

// Created by Alexey on 15.06.2024.
//
#include "SDL.h"
#include "SDL_image.h"
#include "/PrismEngine/src/PRISM_math/vector3D.h"
#include "/PrismEngine/src/PRISM_math/matrix.h"
#include "/PrismEngine/src/PRISM_math/other.h"
#include "/PrismEngine/src/PRISM_UI/joystick.h"
#include "/PrismEngine/src/PRISM_rendering/zbuffer.h"
#include "/PrismEngine/src/PRISM_objects3D/AbstractCamera3D.h"
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
		struct PRISM_Matrix_4X4 ProjectionMatrix;
		struct PRISM_Matrix_4X4 matrixRotZ, matrixRotX, matrixRotY, matrixTranslate, matrixScale; //transform
		struct PRISM_Matrix_4X4 matrixView;
		public:
		struct PRISM_Vector3d Coordinate;
		struct PRISM_Vector3d Rotation;
		struct PRISM_Vector3d Scale;
		struct PRISM_Mesh mesh;
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
		
		void SetMesh(struct PRISM_Mesh m);
		struct PRISM_Mesh GetMesh();
		
		void MultiplyMatrixVector(PRISM_Vector3d &i, PRISM_Vector3d &o, PRISM_Matrix_4X4 &m);
		
		void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
		void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
						  SDL_Renderer* SDL_renderer, short rgba[4], int thickness);
		
		void InitProjection(AbstractCamera3D camera);
		
		void SetRotateXYZ(struct PRISM_Vector3d rotVect);
		void SetMoveXYZ(struct PRISM_Vector3d moveVect);
		void SetScaleXYZ(struct PRISM_Vector3d scaleVect);
		
		PRISM_Triangle RotateTriangle(struct PRISM_Triangle Triangle_);
		PRISM_Triangle TranslateTriangle(struct PRISM_Triangle Triangle_);
		PRISM_Triangle ScaleTriangle(struct PRISM_Triangle Triangle_);
		PRISM_Triangle ViewTriangle(struct PRISM_Triangle Triangle_);
		
		PRISM_Vector3d CalculateNormals(struct PRISM_Triangle triang);
		PRISM_Color CalculatePhongShadingColor(const PRISM_Vector3d& normal, const PRISM_Vector3d& viewDir, const PRISM_Light& light, const PRISM_Vector3d& fragPos);
		
		void DownloadFromOBJ(const char* filename);
		
		void DrawMeshTriangles(SDL_Renderer* renderer, PRISM_RenderMode rm);
		bool ComputeBarycentricCoords(float x, float y,
									  const PRISM_Vector3d& v0, const PRISM_Vector3d& v1, const PRISM_Vector3d& v2,
									  float& u, float& v, float& w);
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
};

#endif // ABSTRACTOBJECT3D_H
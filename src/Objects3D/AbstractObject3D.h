#ifndef ABSTRACTOBJECT3D_H
#define ABSTRACTOBJECT3D_H

// Created by Alexey on 15.06.2024.
//
#include "SDL.h"
#include "SDL_image.h"
#include "/../math/vectors3D.h"
#include "/../math/matrix.h"
#include "/../math/other.h"
#include "/../UI/joystick.h"
#include "/../rendering/zbuffer.h"
#include "/../Objects3D/AbstractCamera3D.h"
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
		struct Matrix_4X4 ProjectionMatrix;
		struct Matrix_4X4 matrixRotZ, matrixRotX, matrixRotY, matrixTranslate, matrixScale; //transform
		struct Matrix_4X4 matrixView;
		public:
		struct Vector3d Coordinate;
		struct Vector3d Rotation;
		struct Vector3d Scale;
		struct Mesh mesh;
		float ScreenW;
		float ScreenH;
		AbstractCamera3D &Camera;
		AbstractObject3D(struct Vector3d Coord, struct Vector3d Rot, struct Vector3d Sc, AbstractCamera3D &camera):Camera(camera) {
			Coordinate = Coord;
			Rotation = Rot;
			Scale = Sc;
			InitProjection(camera);
			SetMoveXYZ(Coordinate);
			SetRotateXYZ(Rotation);
			SetScaleXYZ(Scale);
			
		}
		
		void SetMesh(struct Mesh m);
		struct Mesh GetMesh();
		
		void MultiplyMatrixVector(Vector3d &i, Vector3d &o, Matrix_4X4 &m);
		
		void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
		void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
						  SDL_Renderer* SDL_renderer, short rgba[4], int thickness);
		
		void InitProjection(AbstractCamera3D camera);
		
		void SetRotateXYZ(struct Vector3d rotVect);
		void SetMoveXYZ(struct Vector3d moveVect);
		void SetScaleXYZ(struct Vector3d scaleVect);
		
		Triangle RotateTriangle(struct Triangle Triangle_);
		Triangle TranslateTriangle(struct Triangle Triangle_);
		Triangle ScaleTriangle(struct Triangle Triangle_);
		Triangle ViewTriangle(struct Triangle Triangle_);
		
		Vector3d CalculateNormals(struct Triangle triang);
		Color CalculatePhongShadingColor(const Vector3d& normal, const Vector3d& viewDir, const Light& light, const Vector3d& fragPos);
		
		void DownloadFromOBJ(const char* filename);
		
		void DrawMeshTriangles(SDL_Renderer* renderer, RenderMode rm);
		bool ComputeBarycentricCoords(float x, float y,
									  const Vector3d& v0, const Vector3d& v1, const Vector3d& v2,
									  float& u, float& v, float& w);
		void OldRasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
						   SDL_Renderer* SDL_renderer, Light light, short rgba[4], RenderMode RendMode);
		void OptimizedEdgeRasterization(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
		SDL_Renderer* SDL_renderer, Light light, short rgba[4], RenderMode RendMode);
		void RasterizeTile(int minX, int maxX, int minY, int maxY,
						   const Vector3d& v0, const Vector3d& v1, const Vector3d& v2,
						   SDL_Renderer* SDL_renderer, Light light, short rgba[4],
						   RenderMode RendMode, std::vector<SDL_Surface*>& surfaces);
		void Rasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
						   SDL_Renderer* SDL_renderer, Light light, short rgba[4], RenderMode RendMode);
		void TileRasterisation(int x1, int y1, int x2, int y2, int x3, int y3,
							   float z1, float z2, float z3, SDL_Renderer* SDL_renderer,
							   Light light, short rgba[4], RenderMode RendMode);
};

#endif // ABSTRACTOBJECT3D_H
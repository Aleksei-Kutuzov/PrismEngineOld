#include "AbstractObject3D.h"


void AbstractObject3D::SetMesh(struct Mesh m) {
	mesh = m;
}

struct Mesh AbstractObject3D::GetMesh() {
	return mesh;
}

void AbstractObject3D::MultiplyMatrixVector(Vector3d &i, Vector3d &o, Matrix_4X4 &m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	
	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
}

void AbstractObject3D::DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness) {
	// Вычисление разности координат
	int dx = x2 - x1;
	int dy = y2 - y1;
	
	// Вычисление нормализованного вектора перпендикулярного линии
	float length = sqrtf(dx * dx + dy * dy);
	float nx = -dy / length;
	float ny = dx / length;
	
	// Рисование параллельных линий
	for (int i = -thickness / 2; i <= thickness / 2; ++i) {
		int offsetX = (int)(nx * i);
		int offsetY = (int)(ny * i);
		SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
	}
}

// отрисовываем треугольники
void AbstractObject3D::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Renderer* SDL_renderer,
short rgba[4], int thickness = 1) {
	clock_t start = clock();
	SDL_SetRenderDrawColor(SDL_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
	DrawThickLine(SDL_renderer, x1, y1, x2, y2, thickness);
	DrawThickLine(SDL_renderer, x2, y2, x3, y3, thickness);
	DrawThickLine(SDL_renderer, x3, y3, x1, y1, thickness);
}

void AbstractObject3D::InitProjection(AbstractCamera3D camera) {
	ProjectionMatrix = Matrix_MakeProjection(camera.FFovRad, camera.FAspectRatio, camera.FNear, camera.FFar);
	ScreenW = (float)camera.ScreenW;
	ScreenH = (float)camera.ScreenH;
	Camera = camera;
}

void AbstractObject3D::SetRotateXYZ(struct Vector3d rotVect) {
    Rotation = rotVect;
	
	rotVect.x = degToRad(rotVect.x);
	rotVect.y = degToRad(rotVect.y);
	rotVect.z = degToRad(rotVect.z);
	
	// Rotation X
	matrixRotX = Matrix_MakeRotationX(rotVect.x);

	// Rotation Y
	matrixRotY = Matrix_MakeRotationY(rotVect.y);
	
	// Rotation Z
	matrixRotZ = Matrix_MakeRotationZ(rotVect.z);
}

void AbstractObject3D::SetMoveXYZ(struct Vector3d moveVect) {
    Coordinate = moveVect;
	matrixTranslate = Matrix_MakeTranslation(moveVect.x, moveVect.y, moveVect.z);
}

void AbstractObject3D::SetScaleXYZ(struct Vector3d scaleVect) {
	Scale = scaleVect;
	matrixScale = Matrix_MakeScale(scaleVect.x, scaleVect.y, scaleVect.z);
}

Triangle AbstractObject3D::RotateTriangle(struct Triangle Triangle_) {
	struct Triangle TriangleRotatedZ, TriangleRotatedZX, TriangleRotatedZXY;
	// Rotate in Z-Axis
	MultiplyMatrixVector(Triangle_.a, TriangleRotatedZ.a, matrixRotZ);
	MultiplyMatrixVector(Triangle_.b, TriangleRotatedZ.b, matrixRotZ);
	MultiplyMatrixVector(Triangle_.c, TriangleRotatedZ.c, matrixRotZ);
	
	// Rotate in X-Axis
	MultiplyMatrixVector(TriangleRotatedZ.a, TriangleRotatedZX.a, matrixRotX);
	MultiplyMatrixVector(TriangleRotatedZ.b, TriangleRotatedZX.b, matrixRotX);
	MultiplyMatrixVector(TriangleRotatedZ.c, TriangleRotatedZX.c, matrixRotX);
	
	// Rotate in Y-Axis
	MultiplyMatrixVector(TriangleRotatedZX.a, TriangleRotatedZXY.a, matrixRotY);
	MultiplyMatrixVector(TriangleRotatedZX.b, TriangleRotatedZXY.b, matrixRotY);
	MultiplyMatrixVector(TriangleRotatedZX.c, TriangleRotatedZXY.c, matrixRotY);
	return TriangleRotatedZXY;
}

Triangle AbstractObject3D::TranslateTriangle(struct Triangle Triangle_) {
    struct Triangle TriangleTranslated;
	MultiplyMatrixVector(Triangle_.a, TriangleTranslated.a, matrixTranslate);
	MultiplyMatrixVector(Triangle_.b, TriangleTranslated.b, matrixTranslate);
	MultiplyMatrixVector(Triangle_.c, TriangleTranslated.c, matrixTranslate);
	
	return TriangleTranslated;
}

Triangle AbstractObject3D::ScaleTriangle(struct Triangle Triangle_) {
	struct Triangle TriangleScaled;
	MultiplyMatrixVector(Triangle_.a, TriangleScaled.a, matrixScale);
	MultiplyMatrixVector(Triangle_.b, TriangleScaled.b, matrixScale);
	MultiplyMatrixVector(Triangle_.c, TriangleScaled.c, matrixScale);
	
	return TriangleScaled;
}

Triangle AbstractObject3D::ViewTriangle(struct Triangle Triangle_) {
	struct Triangle TriangleViewed;
	MultiplyMatrixVector(Triangle_.a, TriangleViewed.a, Camera.matrixView);
	MultiplyMatrixVector(Triangle_.b, TriangleViewed.b, Camera.matrixView);
	MultiplyMatrixVector(Triangle_.c, TriangleViewed.c, Camera.matrixView);
	
	return TriangleViewed;
}

Vector3d AbstractObject3D::CalculateNormals(struct Triangle triang) {
	Vector3d normal, lineAB, lineAC;
	lineAB = triang.b - triang.a;
	lineAC = triang.c - triang.a;
	
	normal = Vector_CrossProduct(lineAB, lineAC);
	Vector3d r = Vector_Normalise(normal);
	return r;
}

Color AbstractObject3D::CalculatePhongShadingColor(const Vector3d& normal, const Vector3d& viewDir,
												   const Light& light, const Vector3d& fragPos) {
	// Ambient component
	float ambientStrength = 0.1f;
	Color ambient = { static_cast<Uint8>(light.color.r * ambientStrength),
	                  static_cast<Uint8>(light.color.g * ambientStrength),
	                  static_cast<Uint8>(light.color.b * ambientStrength),
	                  light.color.a };
	
	// Light direction (from fragment position to light position)
	Vector3d lightDir = { light.position.x - fragPos.x, light.position.y - fragPos.y, light.position.z - fragPos.z };
	float lightLen = sqrt(lightDir.x * lightDir.x + lightDir.y * lightDir.y + lightDir.z * lightDir.z);
	lightDir = { lightDir.x / lightLen, lightDir.y / lightLen, lightDir.z / lightLen };
	
	// Diffuse component
	float diff = std::max(0.0f, lightDir.x * normal.x + lightDir.y * normal.y + lightDir.z * normal.z);
	Color diffuse = { static_cast<Uint8>(light.color.r * diff),
	                  static_cast<Uint8>(light.color.g * diff),
	                  static_cast<Uint8>(light.color.b * diff),
	                  light.color.a };
	
	// Reflect direction
	Vector3d reflectDir = { lightDir.x - 2 * normal.x * diff,
	                        lightDir.y - 2 * normal.y * diff,
	                        lightDir.z - 2 * normal.z * diff };
	float spec = std::pow(std::max(0.0f, reflectDir.x * viewDir.x + reflectDir.y * viewDir.y + reflectDir.z * viewDir.z), 32);
	Color specular = { static_cast<Uint8>(light.color.r * spec),
	                   static_cast<Uint8>(light.color.g * spec),
	                   static_cast<Uint8>(light.color.b * spec),
	                   light.color.a };
	
	// Final color
	Color result = { static_cast<Uint8>(std::min(255, ambient.r + diffuse.r + specular.r)),
	                 static_cast<Uint8>(std::min(255, ambient.g + diffuse.g + specular.g)),
	                 static_cast<Uint8>(std::min(255, ambient.b + diffuse.b + specular.b)),
	                 light.color.a };
	return result;
}

void AbstractObject3D::DownloadFromOBJ(const char* filename) {
	SDL_RWops* file = SDL_RWFromFile(filename, "r");
	if (!file) {
		SDL_Log("Could not open file: %s", SDL_GetError());
		return;
	}
	Sint64 fileSize = SDL_RWsize(file);
	char* buffer = new char[fileSize + 1];
	SDL_RWread(file, buffer, fileSize, 1);
	buffer[fileSize] = '\0';
	std::string line;
	std::istringstream fileContent(buffer);
	std::vector<Vector3d> Vertex;
	std::vector<Vector3d> Triangles;
	mesh.tris = {};
	while(getline(fileContent, line)) {
		struct Vector3d v;
		std::string identifier;
		std::istringstream iss(line);
		if (line.c_str()[0] == 'v') {
			iss >> identifier >> v.x >> v.y >> v.z;
			Vertex.push_back(v);
		}
		if (line[0] == 'f') {
			int f[3];
			iss >> identifier >> f[0] >> f[1] >> f[2];
			Triangle tri = {Vertex[f[0] - 1], Vertex[f[1] - 1], Vertex[f[2] - 1]};
			
			mesh.tris.push_back(tri);
		}
	}
	delete[] buffer;
	SDL_RWclose(file);
};

//		Vector3d CalculateVertexNormal(std::vector<Vector3d>& normals, Vector3d vertex, SDL_Renderer* renderer) {
//			SDL_Log("normals vector SIZE: %d", normals.size());
//			for (int i = 0; i < normals.size(); i++) {
//				SDL_Log("normal <%f ,%f ,%f>", normals.at(i).x, normals.at(i).y, normals.at(i).z);
//			}
//
//			Vector3d normalSum = {0, 0, 0};
//				int count = 0;
//				for (Vector3d& normal : normals) {
//					if (normal.x * (vertex.x - CoordinateCamera.x) + //НЕЗАБУДЬ ПОМЕНЯТЬ ВЫРООЖЕНИЕ КОГДА КАМЕРУ ДЕЛАТЬ БУДЕШ СЕЙЧАС ТО ОНА НА НУЛЕ
//						normal.y * (vertex.y - CoordinateCamera.y) +
//						normal.z * (vertex.z - CoordinateCamera.z) < 0.0f) {
//							normalSum = normalSum + normal;
//							count++;
//					}
//				}
//				SDL_Log("count: %d", count);
//				if (count > 0) {
//					normalSum = normalSum * (1.0f / count);
//					normalSum = Vector_Normalise(normalSum);
//				}
//
//				SDL_Log("normalSum: @<%f, %f, %f>@", normalSum.x, normalSum.y, normalSum.z);
//				Vector3d center = vertex;
//
//				// Calculate end point of the normal
//				Vector3d normalEnd = {
//				center.x + normalSum.x, // Adjust length as needed
//				center.y + normalSum.y,
//				center.z + normalSum.z
//				};
//
//				SDL_Log("normalEnd: @<%f, %f, %f>@", normalEnd.x, normalEnd.y, normalEnd.z);
//
//				// Project the center and normal end points
//				Vector3d centerProjected, normalEndProjected;
//
//				MultiplyMatrixVector(center, centerProjected, ProjectionMatrix);
//				MultiplyMatrixVector(normalEnd, normalEndProjected, ProjectionMatrix);
//
//				centerProjected.x = (centerProjected.x + 1.0f) * 0.5f * (float)ScreenW;
//				centerProjected.y = (centerProjected.y + 1.0f) * 0.5f * (float)ScreenH;
//				normalEndProjected.x = (normalEndProjected.x + 1.0f) * 0.5f * (float)ScreenW;
//				normalEndProjected.y = (normalEndProjected.y + 1.0f) * 0.5f * (float)ScreenH;
//				// Draw the normal
//				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for the normal
//
//				SDL_Log("centerProjected: @<%f, %f, %f>@", centerProjected.x, centerProjected.y, centerProjected.z);
//				SDL_Log("centerProjected: @<%f, %f, %f>@", normalSum.x, normalSum.y, normalSum.z);
//				SDL_RenderDrawLine(renderer, (int)centerProjected.x, (int)centerProjected.y,
//				(int)normalEndProjected.x, (int)normalEndProjected.y);
//
//				return normalSum;
//		}

void AbstractObject3D::DrawMeshTriangles(SDL_Renderer* renderer, RenderMode rm) {
	for (auto Triangle_ : mesh.tris) {
		struct Triangle TriangleRotated, TriangleTranslated, TriangleScaled, TriangleProjected, TriangleViewed;

		TriangleScaled = ScaleTriangle(Triangle_);
		TriangleRotated = RotateTriangle(TriangleScaled);
		TriangleTranslated = TranslateTriangle(TriangleRotated);
		TriangleViewed = ViewTriangle(TriangleTranslated);
		
		Vector3d normal = CalculateNormals(TriangleViewed);
		if (normal.x * (TriangleViewed.a.x - Camera.Coordinate.x) +
		    normal.y * (TriangleViewed.a.y - Camera.Coordinate.y) +
		    normal.z * (TriangleViewed.a.z - Camera.Coordinate.z) < 0.0f | rm.ShowBackMesh) {
			
			MultiplyMatrixVector(TriangleViewed.a, TriangleProjected.a,
			                     ProjectionMatrix);
			MultiplyMatrixVector(TriangleViewed.b, TriangleProjected.b,
			                     ProjectionMatrix);
			MultiplyMatrixVector(TriangleViewed.c, TriangleProjected.c,
			                     ProjectionMatrix);
			
			TriangleProjected.a.x += 1.0f;
			TriangleProjected.a.y += 1.0f;
			TriangleProjected.b.x += 1.0f;
			TriangleProjected.b.y += 1.0f;
			TriangleProjected.c.x += 1.0f;
			TriangleProjected.c.y += 1.0f;
			
			TriangleProjected.a.x *= 0.5f * (float) ScreenW;
			TriangleProjected.a.y *= 0.5f * (float) ScreenH;
			TriangleProjected.b.x *= 0.5f * (float) ScreenW;
			TriangleProjected.b.y *= 0.5f * (float) ScreenH;
			TriangleProjected.c.x *= 0.5f * (float) ScreenW;
			TriangleProjected.c.y *= 0.5f * (float) ScreenH;
			
			Light light = { { 0, 5, -10}, { 0, 0, 255, 255 }};
			Color color = light.color;
			
			if (rm.DisplayDimming1){
				
				float l = sqrtf(light.position.x * light.position.x +
				                light.position.y * light.position.y +
				                light.position.z * light.position.z);
				light.position.x /= l; light.position.y /= l; light.position.z /= l;
				float dp = normal.x * light.position.x
				           + normal.y * light.position.y
				           + normal.z * light.position.z;
				float factor;
				factor = dp;
				
				unsigned int newR = color.r * factor;
				unsigned int newG = color.g * factor;
				unsigned int newB = color.b * factor;
				unsigned int newA = color.a * factor;
				
				color.r = static_cast<unsigned char>(newR > 255 ? 255 : newR);
				color.g = static_cast<unsigned char>(newG > 255 ? 255 : newG);
				color.b = static_cast<unsigned char>(newB > 255 ? 255 : newB);
				color.a = static_cast<unsigned char>(newA > 255 ? 255 : newA);
				
				short rgba[4] = {color.r, color.g, color.b, color.a};
				
				
				
			}
			
			short rgba[4] = {color.r, color.g, color.b, color.a};
			
			if (rm.FillMesh) {
//				OldRasterisation(TriangleProjected.a.x, TriangleProjected.a.y,
//				                 TriangleProjected.b.x, TriangleProjected.b.y,
//				                 TriangleProjected.c.x, TriangleProjected.c.y,
//				                 TriangleTranslated.a.z, TriangleTranslated.b.z, TriangleTranslated.c.z,
//							     renderer, light, rgba, rm);
				TileRasterisation(TriangleProjected.a.x, TriangleProjected.a.y,
				                 TriangleProjected.b.x, TriangleProjected.b.y,
				                 TriangleProjected.c.x, TriangleProjected.c.y,
				                 TriangleTranslated.a.z, TriangleTranslated.b.z, TriangleTranslated.c.z,
							     renderer, light, rgba, rm);
			}
			if (rm.DisplayTriangleContours) {
				short nullColor[4] = {0x00, 0xFF, 0x00, 0xFF};
				DrawTriangle(TriangleProjected.a.x, TriangleProjected.a.y,
				             TriangleProjected.b.x, TriangleProjected.b.y,
				             TriangleProjected.c.x, TriangleProjected.c.y, renderer,
				             nullColor, rm.ContourWidth);
			}
		}
	}
	clock_t start = clock();
//			Camera.z_buffer.clear();
	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC * 1000;
}

// Функция для вычисления барицентрических координат
bool AbstractObject3D::ComputeBarycentricCoords(float x, float y, const Vector3d& v0, const Vector3d& v1, const Vector3d& v2, float& u, float& v, float& w) {
	float denom = (v1.y - v2.y)*(v0.x - v2.x) + (v2.x - v1.x)*(v0.y - v2.y);
	u = ((v1.y - v2.y)*(x - v2.x) + (v2.x - v1.x)*(y - v2.y)) / denom;
	v = ((v2.y - v0.y)*(x - v2.x) + (v0.x - v2.x)*(y - v2.y)) / denom;
	w = 1.0f - u - v;
	return u >= 0 && v >= 0 && w >= 0;
}

void AbstractObject3D::OldRasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
				   SDL_Renderer* SDL_renderer, Light light, short rgba[4], RenderMode RendMode) {
	Vector3d v0 = {static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(z1)};
	Vector3d v1 = {static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(z2)};
	Vector3d v2 = {static_cast<float>(x3), static_cast<float>(y3), static_cast<float>(z3)};
	
	Vector3d normal = CalculateNormals({v0, v1, v2});
	Vector3d viewDir = {0, 0, 1};  // Assuming the camera looks along the negative Z axis
	
	Color color0, color1, color2;
	if(RendMode.DisplayDimming2) {
		;
	}
	// Calculate color at each vertex
	
	// Замер времени
	auto start = std::chrono::high_resolution_clock::now();
	
	// Compute bounding box of the triangle
	float minX = std::min({v0.x, v1.x, v2.x});
	float maxX = std::max({v0.x, v1.x, v2.x});
	float minY = std::min({v0.y, v1.y, v2.y});
	float maxY = std::max({v0.y, v1.y, v2.y});

	
	for (int y = static_cast<int>(std::ceil(minY));
	     y <= static_cast<int>(std::floor(maxY)); ++y) {
		for (int x = static_cast<int>(std::ceil(minX));
		     x <= static_cast<int>(std::floor(maxX)); ++x) {
			float u, v, w;
			if (ComputeBarycentricCoords(static_cast<float>(x), static_cast<float>(y), v0,
			                             v1, v2, u, v, w)) {
				float z = u * v0.z + v * v1.z + w * v2.z;
				if (z < Camera.z_buffer.get(x, y) | !RendMode.Z_Buffer) {
					Uint8 r = rgba[0];
					Uint8 g = rgba[1];
					Uint8 b = rgba[2];
					Uint8 a = rgba[3];
					if(RendMode.DisplayDimming2) {
						;
					}

					SDL_SetRenderDrawColor(SDL_renderer, r, g, b, a);
					SDL_RenderDrawPoint(SDL_renderer, x, y);
					Camera.z_buffer.update(x, y, z);
				}
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	
	// Вывод времени через SDL_Log
	SDL_Log("Время выполнения: %.3f мс", duration.count());
}

void AbstractObject3D::OptimizedEdgeRasterization(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
                                                  SDL_Renderer* SDL_renderer, Light light, short rgba[4], RenderMode RendMode) {
	Vector3d v0 = {static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(z1)};
	Vector3d v1 = {static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(z2)};
	Vector3d v2 = {static_cast<float>(x3), static_cast<float>(y3), static_cast<float>(z3)};
	// Сортировка вершин по y (v0.y <= v1.y <= v2.y)
	if (v1.y < v0.y) std::swap(v0, v1);
	if (v2.y < v0.y) std::swap(v0, v2);
	if (v2.y < v1.y) std::swap(v1, v2);
	// Функция для интерполяции X-координаты по рёбрам треугольника
	auto interpolateX = [](float x0, float y0, float x1, float y1, float y) -> float {
	if (y0 == y1) return x0; // Избегаем деления на ноль
		return x0 + (x1 - x0) * (y - y0) / (y1 - y0);
	};
	
	// Инкрементальная растеризация: делим треугольник на два части (верхняя и нижняя)
	auto rasterize_half = [&](Vector3d v0, Vector3d v1, Vector3d v2) {
		for (int y = static_cast<int>(std::ceil(v0.y)); y <= static_cast<int>(std::floor(v2.y)); ++y) {
			float xStart = interpolateX(v0.x, v0.y, v2.x, v2.y, y);
			float xEnd = interpolateX(v1.x, v1.y, v2.x, v2.y, y);
			if (xStart > xEnd) std::swap(xStart, xEnd);
			for (int x = static_cast<int>(std::ceil(xStart)); x <= static_cast<int>(std::floor(xEnd)); ++x) {
				float u, v, w;
				if (ComputeBarycentricCoords(static_cast<float>(x), static_cast<float>(y), v0, v1, v2, u, v, w)) {
					float z = u * v0.z + v * v1.z + w * v2.z;
					if (z < Camera.z_buffer.get(x, y) || !RendMode.Z_Buffer) {
						Uint8 r = rgba[0];
						Uint8 g = rgba[1];
						Uint8 b = rgba[2];
						Uint8 a = rgba[3];
						
						SDL_SetRenderDrawColor(SDL_renderer, r, g, b, a);
						SDL_RenderDrawPoint(SDL_renderer, x, y);
						Camera.z_buffer.update(x, y, z);  // Обновляем Z-буфер
					}
				}
			}
		}
	};
	// Растеризуем верхний и нижний треугольники
	rasterize_half(v0, v1, v2);  // Нижняя часть треугольника
	rasterize_half(v1, v1, v2);  // Верхняя часть
}


// Обертка для вызова растеризации в отдельном потоке
void AbstractObject3D::RasterizeTile(int minX, int maxX, int minY, int maxY,
				   const Vector3d& v0, const Vector3d& v1, const Vector3d& v2,
				   SDL_Renderer* SDL_renderer, Light light, short rgba[4],
				   RenderMode RendMode, std::vector<SDL_Surface*>& surfaces) {
	
	std::mutex render_mutex;
	// Создание поверхности для текущего тайла
	SDL_Surface* RasterSurface = SDL_CreateRGBSurface(0, maxX - minX + 1, maxY - minY + 1, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (SDL_LockSurface(RasterSurface) != 0) {
		SDL_Log("Unable to lock surface: %s", SDL_GetError());
		SDL_FreeSurface(RasterSurface);
		return ;
	}
	Uint32* pixels = (Uint32*)RasterSurface->pixels;
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			float u, v, w;
			if (ComputeBarycentricCoords(static_cast<float>(x), static_cast<float>(y), v0, v1, v2, u, v, w)) {
				float z = u * v0.z + v * v1.z + w * v2.z;
				
				render_mutex.lock();
				int z_buff_point = Camera.z_buffer.get(x, y);
				if (z < z_buff_point | !RendMode.Z_Buffer) {
					Uint8 r = rgba[0];
					Uint8 g = rgba[1];
					Uint8 b = rgba[2];
					Uint8 a = rgba[3];
					
					if (RendMode.DisplayDimming2) {
						// Применение затемнения, если это необходимо
					}
					
					Uint32 color = SDL_MapRGB(RasterSurface->format, r, g, b);
					pixels[(y - minY) * RasterSurface->w + (x - minX)] = color;
					
					Camera.z_buffer.update(x, y, z);
				}
				render_mutex.unlock();
			}
		}
	}
	
	SDL_UnlockSurface(RasterSurface);
	
	render_mutex.lock();
	surfaces.push_back(RasterSurface);
	render_mutex.unlock();
}


void AbstractObject3D::Rasterisation(int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3,
				   SDL_Renderer* SDL_renderer, Light light, short rgba[4], RenderMode RendMode) {
	Vector3d v0 = {static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(z1)};
	Vector3d v1 = {static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(z2)};
	Vector3d v2 = {static_cast<float>(x3), static_cast<float>(y3), static_cast<float>(z3)};
	Vector3d normal = CalculateNormals({v0, v1, v2});
	Vector3d viewDir = {0, 0, 1};  // Предполагается, что камера смотрит вдоль отрицательной оси Z
	
	// Вычисление ограничивающего прямоугольника треугольника
	float minX = std::min({v0.x, v1.x, v2.x});
	float maxX = std::max({v0.x, v1.x, v2.x});
	float minY = std::min({v0.y, v1.y, v2.y});
	float maxY = std::max({v0.y, v1.y, v2.y});
	
	// Делим область на 4 части
	int midX = static_cast<int>((minX + maxX) / 2);
	int midY = static_cast<int>((minY + maxY) / 2);
	
//			// Векторы потоков
//			std::vector<std::thread> threads;
	std::vector<SDL_Surface*> surfaces;

	// Запускаем 4 потока для обработки четырех квадрантов
	std::thread ta(&AbstractObject3D::RasterizeTile, this, minX, midX, minY, midY, v0, v1, v2, SDL_renderer, light, rgba, RendMode, std::ref(surfaces));
	std::thread tb(&AbstractObject3D::RasterizeTile, this, midX + 1, maxX, minY, midY, v0, v1, v2, SDL_renderer, light, rgba, RendMode, std::ref(surfaces));
	std::thread tc(&AbstractObject3D::RasterizeTile, this, minX, midX, midY + 1, maxY, v0, v1, v2, SDL_renderer, light, rgba, RendMode, std::ref(surfaces));
	std::thread td(&AbstractObject3D::RasterizeTile, this, midX + 1, maxX, midY + 1, maxY, v0, v1, v2, SDL_renderer, light, rgba, RendMode, std::ref(surfaces));
	
	ta.join();
	tb.join();
	tc.join();
	td.join();
	
	// Ждем завершения всех потоков
//			for (auto& t : threads) {
//				t.join();
//			}
	
	int surfIndex = 0;
	// Теперь surfaces содержит surface, созданные в потоках
	for (SDL_Surface* surface : surfaces) {
		// Создание текстуры из поверхности
		SDL_Texture* texture = SDL_CreateTextureFromSurface(SDL_renderer, surface);
		
		// Освобождение поверхности
		SDL_FreeSurface(surface);
		SDL_Rect dstrect;
		switch (surfIndex) {
			case 0:
				dstrect = {(int)minX, (int)minY, (int)midX - (int)minX, (int)midY - (int)minY};
				break;
			case 1:
		        dstrect = {(int)midX + 1, (int)minY, (int)maxX - (int)midX + 1, (int)midY - (int)minY};
		        break;
		    case 2:
		        dstrect = {(int)minX, (int)midY + 1, (int)midX - (int)minX, (int)maxY - (int)midY + 1};
		        break;
		    case 3:
		        dstrect = {(int)midX + 1, (int)midY + 1, (int)maxX - (int)midX + 1, (int)maxY - (int)midY + 1};
		        break;
		}
	 
		SDL_RenderCopy(SDL_renderer, texture, nullptr, &dstrect);
		SDL_DestroyTexture(texture);
		surfIndex++;
	}
}

void AbstractObject3D::TileRasterisation(int x1, int y1, int x2, int y2, int x3, int y3,
                                        float z1, float z2, float z3, SDL_Renderer* SDL_renderer,
                                        Light light, short rgba[4], RenderMode RendMode) {
    Vector3d v0 = {static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(z1)};
    Vector3d v1 = {static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(z2)};
    Vector3d v2 = {static_cast<float>(x3), static_cast<float>(y3), static_cast<float>(z3)};
    
    // Calculate the normal and other necessary values
    Vector3d normal = CalculateNormals({v0, v1, v2});
    Vector3d viewDir = {0, 0, 1};  // Assuming the camera looks along the negative Z axis

    // Compute bounding box of the triangle
    float minX = std::min({v0.x, v1.x, v2.x});
    float maxX = std::max({v0.x, v1.x, v2.x});
    float minY = std::min({v0.y, v1.y, v2.y});
    float maxY = std::max({v0.y, v1.y, v2.y});
    
    // Размер плитки
    const int tileSize = 32;
    
    // Обработка каждого блока (плитки)
    for (int tileY = static_cast<int>(std::floor(minY)) / tileSize;
         tileY <= static_cast<int>(std::floor(maxY)) / tileSize; ++tileY) {
        for (int tileX = static_cast<int>(std::floor(minX)) / tileSize;
             tileX <= static_cast<int>(std::floor(maxX)) / tileSize; ++tileX) {
            
            // Координаты плитки в пространстве экрана
            int tileStartX = tileX * tileSize;
            int tileStartY = tileY * tileSize;
            int tileEndX = tileStartX + tileSize - 1;
            int tileEndY = tileStartY + tileSize - 1;

            // Ограничиваем плитку по границам треугольника
            tileStartX = std::max(tileStartX, static_cast<int>(std::ceil(minX)));
            tileEndX = std::min(tileEndX, static_cast<int>(std::floor(maxX)));
            tileStartY = std::max(tileStartY, static_cast<int>(std::ceil(minY)));
            tileEndY = std::min(tileEndY, static_cast<int>(std::floor(maxY)));
            
            // Теперь проходим по каждому пикселю внутри плитки
            for (int y = tileStartY; y <= tileEndY; ++y) {
                for (int x = tileStartX; x <= tileEndX; ++x) {
                    float u, v, w;
                    if (ComputeBarycentricCoords(static_cast<float>(x), static_cast<float>(y), v0, v1, v2, u, v, w)) {
                        float z = u * v0.z + v * v1.z + w * v2.z;
                        if (z < Camera.z_buffer.get(x, y) || !RendMode.Z_Buffer) {
                            Uint8 r = rgba[0];
                            Uint8 g = rgba[1];
                            Uint8 b = rgba[2];
                            Uint8 a = rgba[3];

                            SDL_SetRenderDrawColor(SDL_renderer, r, g, b, a);
                            SDL_RenderDrawPoint(SDL_renderer, x, y);
                            Camera.z_buffer.update(x, y, z);
                        }
                    }
                }
            }
        }
    }
}

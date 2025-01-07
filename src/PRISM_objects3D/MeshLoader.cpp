#include "MeshLoader.h"
#include "../PRISM_math/other.h"


PRISM_Mesh MeshLoader::LoadOBJ(const char* filename, AbstractCamera3D camera) {
	SDL_RWops* file = SDL_RWFromFile(filename, "r");
	
	PRISM_Mesh mesh = {};

	if (!file) {
		SDL_Log("Could not open file: %s", SDL_GetError());
		return mesh;
	}

	Sint64 fileSize = SDL_RWsize(file);
	char* buffer = new char[fileSize + 1];
	SDL_RWread(file, buffer, fileSize, 1);
	buffer[fileSize] = '\0';
	
	std::string line;
	std::istringstream fileContent(buffer);
	
	std::vector<PRISM_Vector3d> vertices;
	std::vector<PRISM_Vector3d> normals;
	std::vector<PRISM_Triangle> triangles;
	

	mesh.tris = {};
	while (getline(fileContent, line)) {
		if (line.empty() || line[0] == '#') {
			continue; // Пропускаем пустые строки и комментарии
		}

		std::istringstream iss(line);
		std::string identifier;
		iss >> identifier;

		if (identifier == "v") {
			// Вершина
			PRISM_Vector3d v;
			iss >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		else if (identifier == "vn") {
			// Нормаль
			PRISM_Vector3d n;
			iss >> n.x >> n.y >> n.z;
			normals.push_back(n);
		}
		else if (identifier == "f") {
			// Грань
			std::vector<int> vertexIndices;
			std::vector<int> normalIndices;

			std::string facePart;
			while (iss >> facePart) {
				// Разбиваем каждую часть грани (например, "1//1" или "1/1/1")
				size_t firstSlash = facePart.find('/');
				size_t secondSlash = facePart.find('/', firstSlash + 1);

				// Извлекаем индекс вершины (до первого '/')
				int vertexIndex = std::stoi(facePart.substr(0, firstSlash)) - 1;
				vertexIndices.push_back(vertexIndex);

				// Проверяем, есть ли индекс нормали (после второго '/')
				if (secondSlash != std::string::npos) {
					int normalIndex = std::stoi(facePart.substr(secondSlash + 1)) - 1;
					normalIndices.push_back(normalIndex);
				}
			}
			// Создаем треугольник, если индексы вершин определены
			if (vertexIndices.size() == 3) {
				PRISM_Triangle tri = {
					vertices[vertexIndices[0]],
					vertices[vertexIndices[1]],
					vertices[vertexIndices[2]]
				};
				// Если указаны нормали, добавляем их в треугольник
				if (!normalIndices.empty() && normalIndices.size() == 3) {
					tri.a_norlmal = normals[normalIndices[0]];
					tri.b_norlmal = normals[normalIndices[1]];
					tri.c_norlmal = normals[normalIndices[2]];
				}
				// Добавляем треугольник в объект
				mesh.tris.push_back(tri);
			}
		}
	}
	delete[] buffer;
	SDL_RWclose(file);

	return mesh;
};
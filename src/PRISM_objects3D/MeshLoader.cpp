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
			continue; // ���������� ������ ������ � �����������
		}

		std::istringstream iss(line);
		std::string identifier;
		iss >> identifier;

		if (identifier == "v") {
			// �������
			PRISM_Vector3d v;
			iss >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		else if (identifier == "vn") {
			// �������
			PRISM_Vector3d n;
			iss >> n.x >> n.y >> n.z;
			normals.push_back(n);
		}
		else if (identifier == "f") {
			// �����
			std::vector<int> vertexIndices;
			std::vector<int> normalIndices;

			std::string facePart;
			while (iss >> facePart) {
				// ��������� ������ ����� ����� (��������, "1//1" ��� "1/1/1")
				size_t firstSlash = facePart.find('/');
				size_t secondSlash = facePart.find('/', firstSlash + 1);

				// ��������� ������ ������� (�� ������� '/')
				int vertexIndex = std::stoi(facePart.substr(0, firstSlash)) - 1;
				vertexIndices.push_back(vertexIndex);

				// ���������, ���� �� ������ ������� (����� ������� '/')
				if (secondSlash != std::string::npos) {
					int normalIndex = std::stoi(facePart.substr(secondSlash + 1)) - 1;
					normalIndices.push_back(normalIndex);
				}
			}
			// ������� �����������, ���� ������� ������ ����������
			if (vertexIndices.size() == 3) {
				PRISM_Triangle tri = {
					vertices[vertexIndices[0]],
					vertices[vertexIndices[1]],
					vertices[vertexIndices[2]]
				};
				// ���� ������� �������, ��������� �� � �����������
				if (!normalIndices.empty() && normalIndices.size() == 3) {
					tri.a_norlmal = normals[normalIndices[0]];
					tri.b_norlmal = normals[normalIndices[1]];
					tri.c_norlmal = normals[normalIndices[2]];
				}
				// ��������� ����������� � ������
				mesh.tris.push_back(tri);
			}
		}
	}
	delete[] buffer;
	SDL_RWclose(file);

	return mesh;
};
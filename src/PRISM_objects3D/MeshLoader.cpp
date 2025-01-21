#include "MeshLoader.h"
#include "../PRISM_math/other.h"
#include "OBJ_Loader.h"

PRISM_Mesh MeshLoader::LoadOBJ(const char* filename, AbstractCamera3D camera) {
    PRISM_Mesh mesh = {};

    // Создаем объект загрузчика
    objl::Loader loader;

    // Загружаем файл
    if (!loader.LoadFile(filename)) {
        SDL_Log("Failed to load OBJ file: %s", filename);
        return mesh;
    }

    // Проверяем наличие мешей в файле
    if (loader.LoadedMeshes.empty()) {
        SDL_Log("No meshes found in OBJ file: %s", filename);
        return mesh;
    }

    // Проходим по всем мешам
    for (const objl::Mesh& loadedMesh : loader.LoadedMeshes) {
        // Вершины
        std::vector<PRISM_Vector3d> vertices;
        for (const objl::Vertex& vertex : loadedMesh.Vertices) {
            PRISM_Vector3d v;
            v.x = vertex.Position.X;
            v.y = vertex.Position.Y;
            v.z = vertex.Position.Z;
            vertices.push_back(v);
        }

        // Нормали
        std::vector<PRISM_Vector3d> normals;
        for (const objl::Vertex& vertex : loadedMesh.Vertices) {
            PRISM_Vector3d n;
            n.x = vertex.Normal.X;
            n.y = vertex.Normal.Y;
            n.z = vertex.Normal.Z;
            normals.push_back(n);
        }

        // Цвета материала
        PRISM_Vector3d diffuseColor = { 1.0f, 1.0f, 1.0f };   // Белый по умолчанию (диффузный)
        PRISM_Vector3d ambientColor = { 1.0f, 1.0f, 1.0f };   // Белый по умолчанию (амбиентный)
        PRISM_Vector3d specularColor = { 1.0f, 1.0f, 1.0f };  // Белый по умолчанию (спекулярный)

        if (!loader.LoadedMaterials.empty()) {
            // Диффузный цвет из MTL
            diffuseColor.x = loadedMesh.MeshMaterial.Kd.X;
            diffuseColor.y = loadedMesh.MeshMaterial.Kd.Y;
            diffuseColor.z = loadedMesh.MeshMaterial.Kd.Z;

            // Амбиентный цвет из MTL
            ambientColor.x = loadedMesh.MeshMaterial.Ka.X;
            ambientColor.y = loadedMesh.MeshMaterial.Ka.Y;
            ambientColor.z = loadedMesh.MeshMaterial.Ka.Z;

            // Спекулярный цвет из MTL
            specularColor.x = loadedMesh.MeshMaterial.Ks.X;
            specularColor.y = loadedMesh.MeshMaterial.Ks.Y;
            specularColor.z = loadedMesh.MeshMaterial.Ks.Z;
        }

        // Грани (треугольники)
        for (size_t i = 0; i < loadedMesh.Indices.size(); i += 3) {
            PRISM_Triangle tri;

            // Вершины треугольника
            tri.a = vertices[loadedMesh.Indices[i]];
            tri.b = vertices[loadedMesh.Indices[i + 1]];
            tri.c = vertices[loadedMesh.Indices[i + 2]];

            // Нормали треугольника
            tri.a_norlmal = normals[loadedMesh.Indices[i]];
            tri.b_norlmal = normals[loadedMesh.Indices[i + 1]];
            tri.c_norlmal = normals[loadedMesh.Indices[i + 2]];

            // Цвета треугольника
            tri.diffuseColor = diffuseColor;
            tri.ambientColor = ambientColor;
            tri.specularColor = specularColor;

            // Добавляем треугольник в меш
            mesh.tris.push_back(tri);
        }
    }

    return mesh;
};


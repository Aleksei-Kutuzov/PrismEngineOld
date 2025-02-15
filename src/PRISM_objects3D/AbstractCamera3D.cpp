#include "AbstractCamera3D.h"
#include "math.h"

void AbstractCamera3D::SetPosition(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d viewDir_) {
    // Устанавливаем положение и вращение камеры
    Translate = Coord;
    Rotation = Rot;

    // Обновляем направление взгляда на основе углов вращения
    UpdateViewDirection();

    // Устанавливаем вид камеры
    SetView(viewDir, { 0, 1, 0 });
}

void AbstractCamera3D::SetView(struct PRISM_Vector3d viewDirVect, struct PRISM_Vector3d upDirVect) {
    // Нормализуем векторы
    viewDir = Math::Vector_Normalise(viewDirVect);
    upDir = Math::Vector_Normalise(upDirVect);

    // Вычисляем вектор "вправо" (right)
    PRISM_Vector3d right = Math::Vector_CrossProduct(upDir, viewDir);
    right = Math::Vector_Normalise(right);

    // Вычисляем вектор "вверх" (up) для корректного ортогонального базиса
    PRISM_Vector3d up = Math::Vector_CrossProduct(viewDir, right);
    up = Math::Vector_Normalise(up);
    
    PRISM_Vector3d Tmp_V = { Translate.x + viewDir.x, Translate.y + viewDir.y, Translate.z + viewDir.z };
    // Создаём матрицу вида с помощью Matrix_PointAt и Matrix_QuickInverse
    PRISM_Matrix_4X4 matrixCamera = Math::Matrix_PointAt(Translate, Tmp_V, up);
    matrixView = Math::Matrix_QuickInverse(matrixCamera);
}

void AbstractCamera3D::ClearZ_Buffer(SDL_Renderer* renderer) {
    z_buffer.clear(renderer);
}

void AbstractCamera3D::UpdateViewDirection() {
    // Преобразуем углы вращения из градусов в радианы
    float yaw = Math::degToRad(Rotation.y);   // Угол поворота вокруг оси Y
    float pitch = Math::degToRad(Rotation.x); // Угол поворота вокруг оси X

    // Вычисляем новое направление взгляда
    PRISM_Matrix_4X4 matRotY = Math::Matrix_MakeRotationY(yaw);
    PRISM_Matrix_4X4 matRotX = Math::Matrix_MakeRotationX(pitch);

    // Исходное направление взгляда (вдоль оси Z)
    PRISM_Vector3d initialViewDir = { 0, 0, 1 };

    // Применяем вращение к направлению взгляда
    Math::MultiplyMatrixVector(initialViewDir, viewDir, matRotY);
    Math::MultiplyMatrixVector(viewDir, viewDir, matRotX);

    // Нормализуем вектор направления взгляда
    viewDir = Math::Vector_Normalise(viewDir);
}
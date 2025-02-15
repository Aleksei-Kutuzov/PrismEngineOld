#include "AbstractCamera3D.h"
#include "math.h"

void AbstractCamera3D::SetPosition(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d viewDir_) {
    // ������������� ��������� � �������� ������
    Translate = Coord;
    Rotation = Rot;

    // ��������� ����������� ������� �� ������ ����� ��������
    UpdateViewDirection();

    // ������������� ��� ������
    SetView(viewDir, { 0, 1, 0 });
}

void AbstractCamera3D::SetView(struct PRISM_Vector3d viewDirVect, struct PRISM_Vector3d upDirVect) {
    // ����������� �������
    viewDir = Math::Vector_Normalise(viewDirVect);
    upDir = Math::Vector_Normalise(upDirVect);

    // ��������� ������ "������" (right)
    PRISM_Vector3d right = Math::Vector_CrossProduct(upDir, viewDir);
    right = Math::Vector_Normalise(right);

    // ��������� ������ "�����" (up) ��� ����������� �������������� ������
    PRISM_Vector3d up = Math::Vector_CrossProduct(viewDir, right);
    up = Math::Vector_Normalise(up);
    
    PRISM_Vector3d Tmp_V = { Translate.x + viewDir.x, Translate.y + viewDir.y, Translate.z + viewDir.z };
    // ������ ������� ���� � ������� Matrix_PointAt � Matrix_QuickInverse
    PRISM_Matrix_4X4 matrixCamera = Math::Matrix_PointAt(Translate, Tmp_V, up);
    matrixView = Math::Matrix_QuickInverse(matrixCamera);
}

void AbstractCamera3D::ClearZ_Buffer(SDL_Renderer* renderer) {
    z_buffer.clear(renderer);
}

void AbstractCamera3D::UpdateViewDirection() {
    // ����������� ���� �������� �� �������� � �������
    float yaw = Math::degToRad(Rotation.y);   // ���� �������� ������ ��� Y
    float pitch = Math::degToRad(Rotation.x); // ���� �������� ������ ��� X

    // ��������� ����� ����������� �������
    PRISM_Matrix_4X4 matRotY = Math::Matrix_MakeRotationY(yaw);
    PRISM_Matrix_4X4 matRotX = Math::Matrix_MakeRotationX(pitch);

    // �������� ����������� ������� (����� ��� Z)
    PRISM_Vector3d initialViewDir = { 0, 0, 1 };

    // ��������� �������� � ����������� �������
    Math::MultiplyMatrixVector(initialViewDir, viewDir, matRotY);
    Math::MultiplyMatrixVector(viewDir, viewDir, matRotX);

    // ����������� ������ ����������� �������
    viewDir = Math::Vector_Normalise(viewDir);
}
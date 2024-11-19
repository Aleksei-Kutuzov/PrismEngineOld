#include "AbstractCamera3D.h"


void AbstractCamera3D::MultiplyMatrixVector(PRISM_Vector3d &i, PRISM_Vector3d &o, PRISM_Matrix_4X4 &m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	
	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
}

void AbstractCamera3D::SetPosition(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d viewDir_) {
	viewDir = viewDir_;
	PRISM_Matrix_4X4 matRX = Math::Matrix_MakeRotationX(Rot.x);
	PRISM_Matrix_4X4 matRY = Math::Matrix_MakeRotationY(Rot.y);
	PRISM_Matrix_4X4 matRZ = Math::Matrix_MakeRotationZ(Rot.z);

	MultiplyMatrixVector(viewDir, viewDir, matRX);
	MultiplyMatrixVector(viewDir, viewDir, matRY);
	MultiplyMatrixVector(viewDir, viewDir, matRZ);
	
	
	
	Coordinate = Coord;
	Rotation = Rot;
	SetView(viewDir, {0, 1, 0});
}

void AbstractCamera3D::SetView(struct PRISM_Vector3d viewDirVect, struct PRISM_Vector3d upDirVect) {
	struct PRISM_Vector3d viewDirTarget = Coordinate + viewDirVect;
	PRISM_Matrix_4X4 matrixCamera = Math::Matrix_PointAt(Coordinate, viewDirTarget, upDirVect);
	matrixView = Math::Matrix_QuickInverse(matrixCamera);
}

void AbstractCamera3D::ClearZ_Buffer(SDL_Renderer * renderer) {
	z_buffer.clear(renderer);
}

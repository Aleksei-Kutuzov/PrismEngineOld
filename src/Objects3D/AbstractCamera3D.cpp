#include "AbstractCamera3D.h"


void AbstractCamera3D::MultiplyMatrixVector(Vector3d &i, Vector3d &o, Matrix_4X4 &m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	
	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
}

void AbstractCamera3D::SetPosition(struct Vector3d Coord, struct Vector3d Rot, struct Vector3d viewDir_) {
	viewDir = viewDir_;
	Matrix_4X4 matRX = Matrix_MakeRotationX(Rot.x);
	Matrix_4X4 matRY = Matrix_MakeRotationY(Rot.y);
	Matrix_4X4 matRZ = Matrix_MakeRotationZ(Rot.z);

	MultiplyMatrixVector(viewDir, viewDir, matRX);
	MultiplyMatrixVector(viewDir, viewDir, matRY);
	MultiplyMatrixVector(viewDir, viewDir, matRZ);
	
	
	
	Coordinate = Coord;
	Rotation = Rot;
	SetView(viewDir, {0, 1, 0});
}

void AbstractCamera3D::SetView(struct Vector3d viewDirVect, struct Vector3d upDirVect) {
	struct Vector3d viewDirTarget = Coordinate + viewDirVect;
	Matrix_4X4 matrixCamera = Matrix_PointAt(Coordinate, viewDirTarget, upDirVect);
	matrixView = Matrix_QuickInverse(matrixCamera);
}

void AbstractCamera3D::ClearZ_Buffer(SDL_Renderer * renderer) {
	z_buffer.clear(renderer);
}

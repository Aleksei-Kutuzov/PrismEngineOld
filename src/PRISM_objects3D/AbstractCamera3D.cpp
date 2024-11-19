#include "AbstractCamera3D.h"


void AbstractCamera3D::SetPosition(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d viewDir_) {
	viewDir = viewDir_;
	PRISM_Matrix_4X4 matRX = Math::Matrix_MakeRotationX(Rot.x);
	PRISM_Matrix_4X4 matRY = Math::Matrix_MakeRotationY(Rot.y);
	PRISM_Matrix_4X4 matRZ = Math::Matrix_MakeRotationZ(Rot.z);

	Math::MultiplyMatrixVector(viewDir, viewDir, matRX);
	Math::MultiplyMatrixVector(viewDir, viewDir, matRY);
	Math::MultiplyMatrixVector(viewDir, viewDir, matRZ);
	
	
	
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

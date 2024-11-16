#ifndef ABSTRACTCAMERA3D_H
#define ABSTRACTCAMERA3D_H

#include "/../math/vectors3D.h"
#include "/../math/matrix.h"
#include "/../rendering/zbuffer.h"


class AbstractCamera3D {
private:

public:
	struct Vector3d Coordinate;
	struct Vector3d Rotation;
	//расстояние вблизь
	float FNear;
	//расстояние вдаль
	float FFar;
	//поле зрения
	float FFov;
	//H/W
	float FAspectRatio;
	//FFovRad
	float FFovRad;
	//
	int ScreenW;
	int	ScreenH;
	//
	struct Vector3d viewDir;
	//Z-buffer
	Z_Buffer z_buffer;
	//
	Matrix_4X4 matrixView;
	AbstractCamera3D(float Near = 0.1f, float Far = 1000.0f, float Fov = 90.0f, int displW = 800, int displH = 480):
		FNear(Near), FFar(Far), FFov(Fov),
		FAspectRatio(static_cast<float>(displH) / static_cast<float>(displW)),
		FFovRad(1.0f / tanf(FFov * 0.5f / 180.0f * 3.14159f)),
		ScreenW(displW), ScreenH(displH),
		z_buffer(ScreenW, ScreenH){}
	
	void MultiplyMatrixVector(Vector3d &i, Vector3d &o, Matrix_4X4 &m);
	void SetPosition(struct Vector3d Coord, struct Vector3d Rot, struct Vector3d viewDir_);
	void SetView(struct Vector3d viewDirVect, struct Vector3d upDirVect);
	void ClearZ_Buffer(SDL_Renderer * renderer);
	
};




#endif // ABSTRACTCAMERA3D_H
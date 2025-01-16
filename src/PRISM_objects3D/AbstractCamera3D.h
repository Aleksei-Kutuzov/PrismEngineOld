#ifndef ABSTRACTCAMERA3D_H
#define ABSTRACTCAMERA3D_H

#include "../PRISM_math/vector3D.h"
#include "../PRISM_math/matrix.h"
#include "../PRISM_math/math.h"
#include "../PRISM_rendering/zbuffer.h"

/// <summary>
/// Класс, представляющий 3D-камеру для работы с виртуальной сценой.
/// </summary>
class AbstractCamera3D {
private:

public:
	/// <summary>
	/// Положение камеры в пространстве.
	/// </summary>
	struct PRISM_Vector3d Translate;

	/// <summary>
	/// Угол вращения камеры (в градусах) относительно осей.
	/// </summary>
	struct PRISM_Vector3d Rotation;
	
	/// <summary>
	/// Расстояние до ближней плоскости отсечения.
	/// </summary>
	float FNear;

	/// <summary>
	/// Расстояние до дальней плоскости отсечения.
	/// </summary>
	float FFar;

	/// <summary>
	/// Угол поля зрения камеры (в градусах).
	/// </summary>
	float FFov;
	
	/// <summary>
	/// Соотношение сторон экрана (ширина/высота).
	/// </summary>
	float FAspectRatio;
	
	/// <summary>
	/// Значение угла поля зрения в радианах (вычисляется автоматически).
	/// </summary>
	float FFovRad;
	
	/// <summary>
	/// Ширина экрана в пикселях.
	/// </summary>
	int ScreenW;

	/// <summary>
	/// Высота экрана в пикселях.
	/// </summary>
	int	ScreenH;
	
	/// <summary>
	/// Направление взгляда камеры.
	/// </summary>
	struct PRISM_Vector3d viewDir;
	
	/// <summary>
	/// Z-буфер для хранения глубины каждого пикселя.
	/// </summary>
	/// @deprecated Не используется на устройствах с поддержкой GPU
	Z_Buffer z_buffer;
	
	/// <summary>
	/// Матрица вида, представляющая трансформацию камеры.
	/// </summary>
	PRISM_Matrix_4X4 matrixView;

	/// <summary>
	/// Конструктор камеры с заданными параметрами.
	/// </summary>
	/// <param name="Near">Расстояние до ближней плоскости отсечения (по умолчанию 0.1).</param>
	/// <param name="Far">Расстояние до дальней плоскости отсечения (по умолчанию 1000.0).</param>
	/// <param name="Fov">Угол поля зрения (по умолчанию 90.0 градусов).</param>
	/// <param name="displW">Ширина экрана в пикселях (по умолчанию 800).</param>
	/// <param name="displH">Высота экрана в пикселях (по умолчанию 480).</param>
	AbstractCamera3D(float Near = 0.1f, float Far = 1000.0f, float Fov = 90.0f, int displW = 800, int displH = 480):
		FNear(Near), FFar(Far), FFov(Fov),
		FAspectRatio(static_cast<float>(displH) / static_cast<float>(displW)),
		FFovRad(1.0f / tanf(FFov * 0.5f / 180.0f * 3.14159f)),
		ScreenW(displW), ScreenH(displH),
		z_buffer(ScreenW, ScreenH){}
	
	/// <summary>
	/// Деструктор камеры.
	/// </summary>
	~AbstractCamera3D() {}
	
	/// <summary>
	/// Устанавливает положение камеры, её вращение и направление взгляда.
	/// </summary>
	/// <param name="Coord">Положение камеры в пространстве.</param>
	/// <param name="Rot">Углы вращения камеры.</param>
	/// <param name="viewDir_">Направление взгляда камеры.</param>
	void SetPosition(struct PRISM_Vector3d Coord, struct PRISM_Vector3d Rot, struct PRISM_Vector3d viewDir_);
	
	/// <summary>
	/// Устанавливает матрицу взгляда камеры и вектор "вверх".
	/// </summary>
	/// <param name="viewDirVect">Вектор направления взгляда.</param>
	/// <param name="upDirVect">Вектор "вверх".</param>
	void SetView(struct PRISM_Vector3d viewDirVect, struct PRISM_Vector3d upDirVect);
	
	/// <summary>
	/// Очищает Z-буфер.
	/// </summary>
	/// <param name="renderer">Указатель на SDL_Renderer для рендеринга.</param>
	/// @deprecated Не используется на устройствах с поддержкой GPU
	void ClearZ_Buffer(SDL_Renderer * renderer);
	
};




#endif // ABSTRACTCAMERA3D_H
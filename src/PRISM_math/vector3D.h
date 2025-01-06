#ifndef PRISM_VECTORS3D_H
#define PRISM_VECTORS3D_H

struct PRISM_Vector3d
{
	float x;
	float y;
	float z;
	float w = 1;

	void setXYZ(float _x, float _y, float _z) {
		x = _x; y = _y; z = _z;
	};

	void print();
	PRISM_Vector3d operator+(PRISM_Vector3d& other);
	PRISM_Vector3d operator-(PRISM_Vector3d& other);
	PRISM_Vector3d operator*(float k);
	PRISM_Vector3d operator/(float k);
	float operator[](int index);
	bool operator==(PRISM_Vector3d& other);
};



#endif // VECTORS3D_H
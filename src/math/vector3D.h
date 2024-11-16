#ifndef PRISM_VECTORS3D_H
#define PRISM_VECTORS3D_H

struct PRISM_Vector3d
{
	float x;
	float y;
	float z;
	float w = 1;

	void set_XYZ(float _x, float _y, float _z) {
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




float Vector_DotProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2);
float Vector_Length(PRISM_Vector3d& v);
PRISM_Vector3d Vector_Normalise(PRISM_Vector3d& v);
PRISM_Vector3d Vector_CrossProduct(PRISM_Vector3d& v1, PRISM_Vector3d& v2);
PRISM_Vector3d Vector_IntersectPlane(PRISM_Vector3d& plane_p, PRISM_Vector3d& plane_n, PRISM_Vector3d& lineStart, PRISM_Vector3d& lineEnd);


#endif // VECTORS3D_H
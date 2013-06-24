#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Matrix4x4.h"

class Vector3D{
public:
	Vector3D();
	Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& v);
	bool operator == (const Vector3D& other) const;
	bool operator != (const Vector3D& other) const;
	Vector3D& operator+=(const Vector3D& c); // translate
	Vector3D& operator-=(const Vector3D& c); // translate
	Vector3D& operator*=(const double f); // scale
	Vector3D& operator/=(const double f); // scale
	Vector3D& operator*=(const Matrix4x4& m); // transform
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	double getX() const;
	double getY() const;
	double getZ() const;
//private:
    float pos[3];
    double x;
    double y;
    double z;
};

#endif // VECTOR3D_H

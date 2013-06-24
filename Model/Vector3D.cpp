#include "Vector3D.h"

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(double x, double y, double z) {
	setX(x);
	setY(y);
	setZ(z);
    pos[0]=x;
    pos[1]=y;
    pos[2]=z;
}

Vector3D::Vector3D(const Vector3D &v) {
    setX(v.x);
    setY(v.y);
    setZ(v.z);
    pos[0]=v.pos[0];
    pos[1]=v.pos[1];
    pos[2]=v.pos[2];
}

bool Vector3D::operator == (const Vector3D& other) const {
    return x == other.x && y == other.y && z == other.z;
}
bool Vector3D::operator != (const Vector3D& other) const {
    return x != other.x || y != other.y || z != other.z;
}

Vector3D& Vector3D::operator+=(const Vector3D& c) {
    setX(x+c.x);
    setY(y+c.y);
    setZ(z+c.z);
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& c){
    setX(x-c.x);
    setY(y-c.y);
    setZ(z-c.z);
	return *this;
}

Vector3D& Vector3D::operator*=(const double f){
    setX(x*f);
    setY(y*f);
    setZ(z*f);
	return *this;
}

Vector3D& Vector3D::operator/=(const double f){
    setX(x/f);
    setY(y/f);
    setZ(z/f);
	return *this;
}

Vector3D& Vector3D::operator*=(const Matrix4x4& m){
	/*TODO*/
	return *this;
}

void Vector3D::setX(double xVal) {
    x = xVal;
}

void Vector3D::setY(double yVal){
    y = yVal;
}

void Vector3D::setZ(double zVal){
    z = zVal;
}

double Vector3D::getX() const {
    return x;
}

double Vector3D::getY() const {
    return y;
}

double Vector3D::getZ() const {
    return z;
}

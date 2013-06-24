#include "Camera.h"
#include <assimp/vector3.h>

//default constructor
Camera::Camera()
    :aspect(0), clipPlaneFar(0), clipPlaneNear(0), horizontalFOV(0), lookAt(), position(), up(){
}

//constructor from 7 fields
Camera::Camera(QString n, double a, double cpf, double cpn, double hfov, Vector3D la, Vector3D p, Vector3D u)
    : SceneObject(n), aspect(a), clipPlaneFar(cpf), clipPlaneNear(cpn), horizontalFOV(hfov), lookAt(la), position(p), up(u){
}

//Questi son da riempire
void Camera::translate(Vector3D){
    return;
}
void Camera::rotate(double,Vector3D){
    return;
}
void Camera::remove(){
    return;
}
ObjectType Camera::getObjectType() const {
    return static_cast<ObjectType>(2);
}


double Camera::getAspect() const{
    return this->aspect;
}

double Camera::getClipPlaneFar() const{
    return this->clipPlaneFar;
}
double Camera::getClipPlaneNear() const{
    return this->clipPlaneNear;
}
double Camera::getHorizontalFOV() const{
    return this->horizontalFOV;
}
Vector3D Camera::getLookAt() const {
    return this->lookAt;
}

Vector3D Camera::getPosition() const{
    return this->position;
}
Vector3D Camera::getUp() const{
    return this->up;
}

void Camera::setAspect(double as){
    this->aspect=as;
}
void Camera::setClipPlaneFar(double cpf){
    this->clipPlaneFar=cpf;
}
void Camera::setClipPlaneNear(double cpn){
    this->clipPlaneNear=cpn;
}
void Camera::setHorizontalFOV(double Hf){
    this->horizontalFOV=Hf;
}
void Camera::setLookAt(Vector3D la){
    this->lookAt=la;
}
void Camera::setPosition(Vector3D ps){
    this->position=ps;
}
void Camera::setUp(Vector3D up){
    this->up=up;
}

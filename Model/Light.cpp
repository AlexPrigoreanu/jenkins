#include "Light.h"


//------------------------------------ATTENUATION---------------------------------//

//default constructor
Attenuation::Attenuation() :constant(0), linear(0), quadratic(0){
}

//constructor with 3 parameters
Attenuation::Attenuation(double c, double l, double q): constant(c), linear(l), quadratic(q){
}

//constructor with array[3]float
Attenuation::Attenuation(double arr[3]): constant(arr[0]), linear(arr[1]), quadratic(arr[2]){
}

double Attenuation::getConstant() const{
    return constant;
}

double Attenuation::getLinear() const {
    return linear;
}

double Attenuation::getQuadratic() const{
    return quadratic;
}

void Attenuation::getArray(double* & array) const{
    array[0]=constant;
    array[1]=linear;
    array[2]=quadratic;
}







//------------------------------------LIGHT---------------------------------//

//default constructor
Light::Light(){
}

float Light::getAngleInnerCone() const{
    return this->angleInnerCone;
}

float Light::getAngleOuterCone() const{
    return this->angleOuterCone;
}

float Light::getAttConstant() const{
    return this->att.getConstant();
}

float Light::getAttLinear() const{
    return this->att.getLinear();
}

float Light::getAttQuadratic() const{
    return this->att.getQuadratic();
}

Colour Light::getAmbient() const{
    return this->ambient;
}

Colour Light::getDiffuse() const{
    return this->diffuse;
}

Colour Light::getSpecular() const{
    return this->specular;
}

Vector3D Light::getPosition() const{
    return this->position;
}

LightType Light::gettype() const{
    return this->lType;
}


//constructor with parameters
Light::Light(QString nam, float aic, float aoc, Attenuation at, Colour amb, Colour diff, Colour spec, Vector3D pos, LightType lt)
    : SceneObject(nam), angleInnerCone(aic), angleOuterCone(aoc), att(at), ambient(amb), diffuse(diff), specular(spec), position(pos), lType(lt){
}


void Light::translate(Vector3D){}
void Light::rotate(double,Vector3D){}
void Light::remove(){}
ObjectType Light::getObjectType() const{
    return static_cast<ObjectType>(1);
}

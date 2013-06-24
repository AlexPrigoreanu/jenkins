#ifndef LIGHT_H
#define LIGHT_H

#include <string.h>
#include "Colour.h"
#include "SceneObject.h"
#include "../Model/Vector3D.h"
enum LightType {Default=0,
                Directional=1,
                Point=2,
                Spot=3};

//this class represent the 3-elements array that describes the attenuation of a light source
class Attenuation{
private:
    double constant;
    double linear;
    double quadratic;
public:
    Attenuation();
    Attenuation(double, double, double);
    Attenuation(double[3]);
    double getConstant() const;
    double getLinear() const;
    double getQuadratic() const;
    void getArray(double*&) const;
};



class Light : public SceneObject
{
private:
    float angleInnerCone;
    float angleOuterCone;
    Attenuation att;
    Colour ambient;
    Colour diffuse;
    Colour specular;
    Vector3D position;
    LightType lType;

public:

    //Constructors
    Light();
    Light(QString, float, float, Attenuation, Colour, Colour, Colour, Vector3D, LightType);

    //Getters
    float getAngleInnerCone() const;
    float getAngleOuterCone() const;
    float getAttConstant() const;
    float getAttLinear() const;
    float getAttQuadratic() const;
    Colour getAmbient() const;
    Colour getDiffuse() const;
    Colour getSpecular() const;
    Vector3D getPosition() const;
    LightType gettype() const;

    //queste sono da scrivere
    virtual void translate(Vector3D);
    virtual void rotate(double,Vector3D);
    virtual void remove();
    virtual ObjectType getObjectType() const;


};

#endif // LIGHT_H

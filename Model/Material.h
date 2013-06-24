#ifndef MATERIAL_H
#define MATERIAL_H
#include "Colour.h"
#include <string>

class Material
{
private:
    std::string name;
    Colour diffuse;
    Colour specular;
    Colour ambient;
    Colour emissive;
    Colour transparent;
    float opacity;
    float shininess;
    float shininessStrenght;
    //manca la parte di texture
public:
    Material();
    Material(std::string,Colour,Colour,Colour,Colour,Colour,float,float,float);
};

#endif // MATERIAL_H

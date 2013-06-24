#include "Material.h"

Material::Material()
    :name(""),diffuse(0,0,0),specular(0,0,0),ambient(0,0,0),emissive(0,0,0),transparent(0,0,0),opacity(1.0),shininess(0.f),shininessStrenght(1.0){
}
Material::Material(std::string nm,Colour d,Colour s,Colour a,Colour e,Colour t,float o,float sh,float ss)
    :name(nm),diffuse(d),specular(s),ambient(a),emissive(e),transparent(t),opacity(o),shininess(sh),shininessStrenght(ss){
}

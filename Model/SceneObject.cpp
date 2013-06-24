#include "SceneObject.h"



SceneObject::SceneObject():name("none"){}
SceneObject::SceneObject(QString n) :name(n){}

QString SceneObject::getName() const {
    return this->name;
}



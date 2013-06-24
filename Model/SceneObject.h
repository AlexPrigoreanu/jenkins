#ifndef SCENENODE_H
#define SCENENODE_H

#include <assimp/cimport.h>
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>
#include <QString>
#include "Vector3D.h"


enum ObjectType {mesh=0,
                light=1,
                camera=2};



class SceneObject{
private:
    QString name;
public:
    SceneObject();
    SceneObject(QString);
    virtual void translate(Vector3D)=0;
    virtual void rotate(double,Vector3D)=0;
    virtual void remove()=0;
    virtual ObjectType getObjectType() const =0;
    QString getName() const;
};

#endif // SCENENODE_H

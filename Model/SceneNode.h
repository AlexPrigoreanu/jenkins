#ifndef SCENENODE_H
#define SCENENODE_H

#include <assimp/cimport.h>
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>
#include <QString>
#include "Vector3D.h"

class SceneNode{
private:
    QString id;
    aiMatrix4x4t<double> transformation;
public:
    SceneNode();
    virtual void Translate(Vector3D)=0;
    virtual void Rotate(Vector3D)=0;
    virtual void Scale(Vector3D)=0;
    aiMatrix4x4t<double> GetTransformation();
};

#endif // SCENENODE_H

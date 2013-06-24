#ifndef MESH_H
#define MESH_H

#include <assimp/mesh.h>
#include <string>
#include "Colour.h"
#include "Material.h"
#include "Vector3D.h"
#include "Face.h"
#include "SceneObject.h"
#include "Matrix4x4.h"


class Mesh : public SceneObject{
private:

    QList<Colour> colors;
    QList<Face> faces;
    Material mat;
    QList<Vector3D> bitangents;
    QList<Vector3D> normals;
    QList<Vector3D> tangents;
    QList<Vector3D*> textureCoords;
    QList<Vector3D> vertices;
    Matrix4x4 transformations;


public:

    //Constructors
    Mesh();
    Mesh(QString, QList<Colour>, QList<Face>, Material, QList<Vector3D>, QList<Vector3D>, QList<Vector3D>, QList<Vector3D*>, QList<Vector3D>,Matrix4x4);

    //queste sono da scrivere
    virtual void translate(Vector3D);
    virtual void rotate(double,Vector3D);
    virtual void remove();
    virtual ObjectType getObjectType() const;

    //Getter
    QList<Face> getFaces() const;
    Material getMat() const;
    QList<Vector3D> getBitangents() const;
    QList<Vector3D> getNormals() const;
    QList<Vector3D> getTangents() const;
    QList<Vector3D*> getTextureCoords() const;
    QList<Vector3D> getVertices() const;
    QList<Colour> getVertColours() const{return colors;}

};

#endif // MESH_H

#include "Mesh.h"

//default constructor
Mesh::Mesh()
    :SceneObject("empty"),bitangents(QList<Vector3D>()),  colors(QList<Colour>()), faces(QList<Face>()), mat(Material()),
      normals(QList<Vector3D>()), tangents(QList<Vector3D>()),
      textureCoords(QList<Vector3D*>()), vertices(QList<Vector3D>()), transformations(Matrix4x4()){
}

//constructor with parameters
Mesh::Mesh(QString name,QList<Colour> col, QList<Face> fcs, Material mtl, QList<Vector3D> bit, QList<Vector3D> nrml, QList<Vector3D> tng, QList<Vector3D*> txtcrd, QList<Vector3D> vrtc, Matrix4x4 trasf)
    : SceneObject(name), bitangents(bit), colors(col), faces(fcs), mat(mtl),
      normals(nrml), tangents(tng), textureCoords(txtcrd), vertices(vrtc), transformations(trasf){}



//Getter
QList<Vector3D> Mesh::getBitangents() const{
    return this->bitangents;
}

QList<Face> Mesh::getFaces() const{
    return faces;
}

Material Mesh::getMat() const {
    return this->mat;
}

QList<Vector3D> Mesh::getNormals() const {
    return this->normals;
}

QList<Vector3D> Mesh::getTangents() const{
    return this->tangents;
}

QList<Vector3D> Mesh::getVertices() const{
    return this->vertices;
}




void Mesh::translate(Vector3D){}
void Mesh::rotate(double,Vector3D){}
void Mesh::remove(){}
ObjectType Mesh::getObjectType() const {
    return static_cast<ObjectType>(0);
}

#ifndef FACE_H
#define FACE_H

#include "Vector3D.h"
#include<QList>

class Face{
public:
	Face();
    Face(QList<int> vi,QList<Vector3D> va);
	bool operator==(const Face& other) const;
	bool operator!=(const Face& other) const;
    Face& operator=(const Face& other);
    Face(const Face& other);
    void setVerticesArray(QList<Vector3D> va);
    QList<Vector3D> getVerticesArray();
    QList<int> getVerticesIndex();



    Vector3D arrayVertici[3];
    int numVertici;


private:
    QList<int> verticesIndex;
    QList<Vector3D> verticesArray;

};

#endif // FACE_H

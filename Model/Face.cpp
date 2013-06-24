#include "Face.h"
#include<QList>

Face::Face(){}

Face::Face(QList<int> vi,QList<Vector3D> va) : verticesArray(va), verticesIndex(vi){
}

bool Face::operator==(const Face& other) const{
	return false;
}

bool Face::operator!=(const Face& other) const{
	return false;
}
void Face::setVerticesArray(QList<Vector3D> va){
}

Face::Face(const Face& other){
    this->verticesArray=other.verticesArray;
    this->verticesIndex=other.verticesIndex;

    for(int a=0;a<other.verticesArray.count();a++){
        this->arrayVertici[a].pos[0]=other.arrayVertici[a].pos[0];
        this->arrayVertici[a].pos[1]=other.arrayVertici[a].pos[1];
        this->arrayVertici[a].pos[2]=other.arrayVertici[a].pos[2];
    }
    this->numVertici=other.numVertici;
}

Face& Face::operator=(const Face& other){
    this->verticesArray=other.verticesArray;
    this->verticesIndex=other.verticesIndex;

//    for(int a=0;a<other.numVertici;a++){
//        this->arrayVertici[a].pos[0]=other.arrayVertici[a].pos[0];
//        this->arrayVertici[a].pos[1]=other.arrayVertici[a].pos[1];
//        this->arrayVertici[a].pos[2]=other.arrayVertici[a].pos[2];
//    }
    this->numVertici=other.numVertici;
    return *this;
}

QList<Vector3D> Face::getVerticesArray(){
    return verticesArray;
}
QList<int> Face::getVerticesIndex(){
    return verticesIndex;

}

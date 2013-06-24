#include "AssimpAdapter.h"
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/camera.h>
#include <string.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <QVector>
#include <assimp/color4.h>
#include <iostream>
#include <assimp/postprocess.h>
#include "SceneImporter.h"
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include "Scene.h"
#include <string>
#include <QList>
#include "Colour.h"
#include "Light.h"
#include <assimp/light.h>
#include <assimp/mesh.h>
#include <assimp/camera.h>
#include <assimp/anim.h>
#include <assimp/color4.h>

//------------------ADAPTING UTILITY FUNCIONS------------------------------//
//This method converts an aiVector3D (assimp library) to a Vector3D object
//Static
Vector3D AssimpAdapter::convertAiVector3D(const aiVector3D aiv){
    return Vector3D(aiv.x,aiv.y, aiv.z);
}

//this method converts an aiColor3D (assimp library) to a Colour object
//Static
Colour AssimpAdapter::convertAiColor3D(const aiColor3D aic){
    return Colour(aic.r,aic.g,aic.b,1);
}

//This method converts an aiColor4D (assimp library) to a Colour object
//Static
Colour AssimpAdapter::convertAiColor4D(const aiColor4D aic){
    return Colour(aic.r,aic.g,aic.b,aic.a);
}

//This method converts an aiString (assimp library) to a std::string variable
//Static
std::string AssimpAdapter::convertAiString(const aiString s){
    char* data =const_cast<char *>(s.data);
    return (string) data;
}








//Constructor
AssimpAdapter::AssimpAdapter() :sc(0), imp(0)
{}





//Redifinition of virtual method in SceneImporter to load a scene given the file path
Scene* AssimpAdapter::importFile(const std::string filePath){

    //importer initialization
    this->imp=new Assimp::Importer();
    //initialization of scene with aiscene pointer returned by ReadFile
    this->sc=const_cast<aiScene*>(imp->ReadFile(filePath,aiProcessPreset_TargetRealtime_MaxQuality));

    //declaration of new scene
    Scene* s = new Scene();
    //adesso bisogna inizializzare tutti i campi della scena con la roba presente nell'aiscene
    s->insertObjects(this->adaptLights());
    s->insertObjects(this->adaptCameras());
    s->insertObjects(this->adaptMeshes());

    return s;
}

//this method, given the array aiCamera** of aiScene struct, initializes a Vector<Camera*>
//needed for Scene initialization
QHash<QString, SceneObject*> AssimpAdapter::adaptCameras() const{
    QHash<QString,SceneObject*> hashcam;
    aiCamera** vCamera=this->GetScene()->mCameras;
    int nCam = this->GetScene()->mNumCameras;
    for (int i=0;i<(int)nCam;i++){
        QString name = QString("Camera").append(QString::number(i));
        SceneObject* element = new Camera(name,
                                          (vCamera)[i]->mAspect,
                                          (vCamera)[i]->mClipPlaneFar,
                                          (vCamera)[i]->mClipPlaneNear,
                                          (vCamera)[i]->mHorizontalFOV,
                                          AssimpAdapter::convertAiVector3D((vCamera)[i]->mLookAt),
                                          AssimpAdapter::convertAiVector3D((vCamera)[i]->mPosition),
                                          AssimpAdapter::convertAiVector3D((vCamera)[i]->mUp));
        hashcam.insert(name,element);

    }
    return hashcam;
}

//this method, given the array aiLight** of aiScene struct, initializes a Vector<Light*>
//needed for Scene initialization
QHash<QString,SceneObject*> AssimpAdapter::adaptLights() const{
    QHash<QString,SceneObject*> hashlight;
    aiLight** vLight=this->GetScene()->mLights;
    int nLight = this->GetScene()->mNumLights;
    for (int i=0;i<(int)nLight;i++){
        QString name = QString("Light").append(QString::number(i));
        //initialize a class Attenuation to construct the Light object
        Attenuation att ((vLight)[i]->mAttenuationConstant,
                         (vLight)[i]->mAttenuationLinear,
                         (vLight)[i]->mAttenuationQuadratic);
        //Creo l'enum che descrive il tipo di luce
        LightType type;
        switch((vLight)[i]->mType){
        case 0x0:
            type=Default;
            break;
        case 0x1:
            type=Directional;
            break;
        case 0x2:
            type=Point;
            break;
        case 0x3:
            type=Spot;
            break;
        default:
            type=Default;
            break;
        }
        SceneObject* element = new Light(name,
                                         (vLight)[i]->mAngleInnerCone,
                                         (vLight)[i]->mAngleOuterCone,
                                         att,
                                         AssimpAdapter::convertAiColor3D((vLight)[i]->mColorAmbient),
                                         AssimpAdapter::convertAiColor3D((vLight)[i]->mColorDiffuse),
                                         AssimpAdapter::convertAiColor3D((vLight)[i]->mColorSpecular),
                                         AssimpAdapter::convertAiVector3D((vLight)[i]->mPosition),
                                         type);

        hashlight.insert(name,element);
    }
    return hashlight;
}

//this method, given the array aiMeshes** of aiScene struct, initializes a Vector<Mesh*>
//needed for Scene initialization
QHash<QString,SceneObject*> AssimpAdapter::adaptMeshes() const{
    QHash<QString,SceneObject*> m;
    aiMesh** vMesh=this->GetScene()->mMeshes;
    int nMesh = this->GetScene()->mNumMeshes;
    for (int i=0;i<(int)nMesh;i++){ //cyclying on meshes
        QList<Vector3D> ourBitangents;
        QList<Vector3D> ourNormals;
        QList<Vector3D> ourTangs;
        QList<Vector3D> ourVertices;
        QList<Vector3D*> ourTexCoords;
        QList<Colour> ourVertColour;
        const struct aiMesh* mesh= vMesh[i];
        //std::cout << &mesh->mColors[0] <<"\n";
        //std::cout << &((vMesh)[i]->mColors[0]) << "\n";
        if (((vMesh)[i]->mColors[0])!=NULL){
            std::cout << (vMesh)[i]->mColors[0][0].a << "\n";
            for (int k=0;k<(int)(vMesh)[i]->mNumVertices;k++){
                if ((vMesh)[i]->mColors[0][k]!=NULL) ourVertColour.insert(k,AssimpAdapter::convertAiColor4D((vMesh)[i]->mColors[0][k]));
            }
        }
        for (int k=0;k<(int)(vMesh)[i]->mNumVertices;k++){ //ciclo sui vertici
            Vector3D textureVertex[8]={Vector3D(),Vector3D(),Vector3D(),Vector3D(),Vector3D(),Vector3D(),Vector3D(),Vector3D()};
            ourTexCoords.insert(k,textureVertex);
            if ((vMesh)[i]->mBitangents!=NULL) ourBitangents.insert(k,AssimpAdapter::convertAiVector3D((vMesh)[i]->mBitangents[k]));
            if ((vMesh)[i]->mNormals!=NULL) ourNormals.insert(k,AssimpAdapter::convertAiVector3D((vMesh)[i]->mNormals[k]));
            if ((vMesh)[i]->mTangents!=NULL) ourTangs.insert(k,AssimpAdapter::convertAiVector3D((vMesh)[i]->mTangents[k]));
            if ((vMesh)[i]->mVertices!=NULL) ourVertices.insert(k,AssimpAdapter::convertAiVector3D((vMesh)[i]->mVertices[k]));
        }



        //this code adapts the aiFaces to an array of Faces
        aiFace* aiMeshFaces=(vMesh)[i]->mFaces;
        aiVector3D* aiMeshVerticesArray = (vMesh)[i]->mVertices;
        QList<Face> ourFaces;
        if ((vMesh)[i]->mNumFaces!=0){
            for(int k=0;k<(int)(vMesh)[i]->mNumFaces;k++){//cyclying of the faces
                QList<Vector3D> vertarr;
                QList<int> vertindx;
                vertindx.clear();
                for(int j=0; j<(int)(aiMeshFaces[k].mNumIndices); j++){//cyclying on the aivector3D per face
                    vertarr.append(AssimpAdapter::convertAiVector3D(aiMeshVerticesArray[(aiMeshFaces[k].mIndices)[j]]));

                    vertindx.append(aiMeshFaces[k].mIndices[j]);
                }
                Face fac=Face(vertindx,vertarr);
                fac.numVertici=aiMeshFaces[k].mNumIndices;
                for(int cc=0; cc<vertarr.count(); cc++){
                    fac.arrayVertici[cc]=vertarr.value(cc);
                    //std::cout << fac.arrayVertici[cc].x << "\t";
                }
                ourFaces.append(fac);
            }
        }

        //now the array of the mesh faces is contained in ourFaces

        //this code adapts the aiMaterials to a Material object
        aiMaterial** aiMats=(sc->mMaterials);
        int aiMatIndex = (vMesh)[i]->mMaterialIndex;
        aiColor3D aiAmb, aiDiff, aiSpec, aiEmiss, aiTransp;
        float aiOp, aiSh, aiShs;
        aiString nam;
        (aiMats[aiMatIndex])->Get(AI_MATKEY_NAME,nam);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_COLOR_AMBIENT,aiAmb);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_COLOR_DIFFUSE,aiDiff);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_COLOR_SPECULAR,aiSpec);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_COLOR_EMISSIVE,aiEmiss);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_COLOR_TRANSPARENT,aiTransp);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_OPACITY,aiOp);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_SHININESS,aiSh);
        (aiMats[aiMatIndex])->Get(AI_MATKEY_SHININESS_STRENGTH,aiShs);
        //initializing a material with adapted values
        Material ourMat = Material(AssimpAdapter::convertAiString(nam),
                                   AssimpAdapter::convertAiColor3D(aiDiff),
                                   AssimpAdapter::convertAiColor3D(aiSpec),
                                   AssimpAdapter::convertAiColor3D(aiAmb),
                                   AssimpAdapter::convertAiColor3D(aiEmiss),
                                   AssimpAdapter::convertAiColor3D(aiTransp),
                                   aiOp,
                                   aiSh,
                                   aiShs);
        //now the material of this mesh is contained in ourMat
        //(QList<Colour*> col, QList<Face> fcs, Material mtl, std::string s, QList<Vector3D> bit, QList<Vector3D> nrml,
        //QList<Vector3D> tng, QList<Vector3D*> txtcrd, QList<Vector3D> vrtc)

        //ora devo prendere la trasformazione di questo nodo

        QString name = QString("Mesh").append(QString::number(i));
        Mesh* element = new Mesh(name,
                                 ourVertColour,
                                 ourFaces,
                                 ourMat,
                                 ourBitangents,
                                 ourNormals,
                                 ourTangs,
                                 ourTexCoords,
                                 ourVertices,
                                 Matrix4x4());
        m.insert(name,element);
    }//chiude ciclo sulle mesh

    return m;
}


aiScene* AssimpAdapter::GetScene() const{
    return sc;
}

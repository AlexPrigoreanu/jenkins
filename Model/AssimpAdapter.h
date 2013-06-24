#ifndef ASSIMPADAPTER_H
#define ASSIMPADAPTER_H

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

//This class Adapts the scene of the Open Asset
//Import Library
class AssimpAdapter : public SceneImporter{

private:
   aiScene* sc;
   Assimp::Importer* imp;

public:
   AssimpAdapter();
   virtual Scene* importFile(const std::string);

   //Getters
   aiScene* GetScene() const ;

   //Static Conversions
   static Vector3D convertAiVector3D(const aiVector3D);
   static Colour convertAiColor3D(const aiColor3D);
   static Colour convertAiColor4D(const aiColor4D);
   static std::string convertAiString(const aiString);

   //methods for Scene import

   //Light initialization
   QHash<QString,SceneObject*> adaptLights() const;
   //Camera initialization
   QHash<QString,SceneObject*> adaptCameras() const;
   //Mesh initialization
   QHash<QString,SceneObject*> adaptMeshes() const;


};

#endif // ASSIMPADAPTER_H

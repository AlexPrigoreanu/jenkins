#ifndef SCENEIMPORTER_H
#define SCENEIMPORTER_H

#include <string>
#include "Scene.h"
using namespace std;

class SceneImporter{
private:

public:
    virtual Scene* importFile(const std::string)=0;
};

#endif // SCENEIMPORTER_H

#ifndef JSONIMPORTER_H
#define JSONIMPORTER_H

#include "SceneImporter.h"

class JSONImporter : public SceneImporter
{
public:
    JSONImporter();
    virtual Scene* importFile(const std::string);
};

#endif // JSONIMPORTER_H

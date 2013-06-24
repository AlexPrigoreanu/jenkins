#ifndef XMLIMPORTER_H
#define XMLIMPORTER_H

#include "SceneImporter.h"

class XMLImporter : public SceneImporter {
public:
    XMLImporter();

    virtual Scene* importFile(const std::string);
};

#endif // XMLIMPORTER_H

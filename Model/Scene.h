#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <QHash>
#include <QString>
#include <QSet>
#include <QPair>
#include "SceneObject.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"



class Exception{};

class DuplicatedKey: public Exception{};
class NodeNotFound: public Exception{};
class Scene{

private:

    //Lista nodi selezionati
    QSet<QPair<QString,ObjectType> > selectedNodes;

    QHash<QString,SceneObject*> objects;
public:
    //Costruttore
    Scene();
    void clearObjects();
    void insertObjects(QHash<QString,SceneObject*>) ;
    void clearSelection();
    void addToSelection(QString);
    SceneObject* getObjectByName(QString) const;
    QHash<QString, SceneObject*>& getObj() {return objects;}

};

#endif // SCENE_H

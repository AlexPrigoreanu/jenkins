#include "Scene.h"

//! costruttore di default
Scene::Scene()
{
}

//! metodo per pulire l'hash di sceneobject di scena, chiamando il metodo remove su ognuno
void Scene::clearObjects(){
    for(QHash<QString,SceneObject*>::Iterator i=objects.begin();i!=objects.end();i++){
        (i.value())->remove();
    }
    this->objects.clear();
}

//! metodo per aggiungere all'hash un altro hash di sceneobject, lancia duplicatedKey e non inserisce se ci sono chiavi raddoppiate
void Scene::insertObjects(QHash<QString,SceneObject*> h){
    for(QHash<QString, SceneObject*>::Iterator i=h.begin();i!=h.end();i++){
        if(objects.contains(i.key()))
            throw DuplicatedKey();
    }
    this->objects.unite(h);
}

//! metodo per pulire la lista di oggetti selezionati
void Scene::clearSelection(){
    this->selectedNodes.clear();
}

//! metodo per restituire il puntatore ad un oggetto della scena dato il suo identificativo nella lista
SceneObject* Scene::getObjectByName(QString k) const {
    QHash<QString,SceneObject*>::ConstIterator i;
    i=this->objects.find(k);
    if (i==objects.end()) return 0;
    return i.value();
}


//! metodo per aggiungere un nodo alla selezione corrente
void Scene::addToSelection(QString name) throw(NodeNotFound){
    SceneObject * p;
    p=this->getObjectByName(name);
    if(p){
       QPair<QString, ObjectType> nuovo=qMakePair(p->getName(),p->getObjectType());
       this->selectedNodes.insert(nuovo);
    }
    else
        throw NodeNotFound();
}

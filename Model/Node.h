#ifndef NODE_H
#define NODE_H

#include <QList>
#include "SceneNode.h"


class Node : public SceneNode{
private:
   QList<SceneNode*> childrenNodes;
public:
   Node();
   QList<SceneNode*> GetChildren() const;

};

#endif // NODE_H

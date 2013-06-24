#include "Node.h"

Node::Node()
{
}

QList<SceneNode*> Node::GetChildren() const{
    return this->childrenNodes;
}

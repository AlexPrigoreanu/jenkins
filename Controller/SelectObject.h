#include "CommandScene.h"

class SelectObject : public CommandScene
{

public:
    void execute();

private:
    SceneObject* selectedNode;
public slots:

};

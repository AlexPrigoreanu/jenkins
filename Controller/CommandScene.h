#include <QtWidgets/QUndoStack>
#include "../Model/Scene.h"

using namespace std;
class CommandScene : public QUndoCommand
{

public:
    virtual void execute()=0;
//da verificare se private o protected (con protected funziona)
private:
    Scene* sceneRef;

public slots:

};

#include <QtWidgets/QUndoStack>
#include "../Model/Scene.h"
//#include "../View/Facade.h"
#include "../Model/SceneImporter.h"
#include "../Model/Setting.h"
class Controller
{

public:
    Controller();
    void openFile(const string);


private:
    QUndoStack* commandStack;
	Scene* sceneRef;
    SceneImporter* sceneImp;
    //Facade* facadeRef;
    Setting* settings;
	
public slots:

};

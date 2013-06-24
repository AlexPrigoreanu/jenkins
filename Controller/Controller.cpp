#include "Controller.h"
#include <string.h>
#include "../Model/AssimpAdapter.h"
#include "../Model/JSONImporter.h"
#include "../Model/XMLImporter.h"
//default constructor
using namespace std;
Controller::Controller() {
}
//metodo che ricevuto il segnale della view con la stringa inizializza
//un adapter a seconda del formato indicato dalla stringa
void Controller::openFile(string path) {
    string estensione = path.substr(path.find_first_of('.') + 1);
    //se l'estensione è 3ds chiama il parser 3ds
    if (estensione == "3ds") {
        sceneImp = new AssimpAdapter();
    }
    //altrimenti se l'estensione è json chiama il parser json
    else if (estensione == "json") {
        SceneImporter* a = new JSONImporter();
        }
        //altrimenti se l'estensione è xml chiama il parser xml
        else if (estensione == "xml") {
        sceneImp = new XMLImporter();
            }
            //altrimenti estensione non riconosciuta
            else {
                //stampa tipo non riconosciuto
            }
    sceneRef = sceneImp->importFile(path);
}
//nuovo importer e chiama importfile

#include "Mount.h"

Mount::Mount() {
}

void Mount::MontarParticion(Mount *montar){
    if(montar->path == ""){
        cout << "ERROR: No se ha ingresado la ruta del disco" << endl;
        return;
    }

    if(montar->name == ""){
        cout << "ERROR: No se ha ingresado el nombre de la particion" << endl;
        return;
    }

    
}
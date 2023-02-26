#include "Unmount.h"

Unmount::Unmount() {
}

void Unmount::DesmontarParticion(Unmount *desmontar){
    if(desmontar->id == ""){
        cout << "ERROR: No se ha ingresado el id de la particion" << endl;
        return;
    }
}
#include "Unmount.h"

Unmount::Unmount() {
}

void Unmount::DesmontarParticion(Unmount *desmontar){
    if(desmontar->id == ""){
        cout << "ERROR: No se ha ingresado el id de la particion" << endl;
        return;
    }
    if(!lista_particiones_montadas.ExisteID(desmontar->id)){
        cout << "ERROR: No se ha encontrado la particion" << endl;
        return;
    }

    lista_particiones_montadas.Eliminar(desmontar->id);

    cout << "La particion se ha desmontado correctamente" << endl;

    lista_particiones_montadas.Mostrar();
}
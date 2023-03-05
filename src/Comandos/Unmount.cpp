#include "Unmount.h"

Unmount::Unmount() {
}

void Unmount::DesmontarParticion(Unmount *desmontar){
    if(desmontar->id == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado el id de la particion \e[m\n" << endl;
        return;
    }
    if(!lista_particiones_montadas.ExisteID(desmontar->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion \e[m\n" << endl;
        return;
    }

    lista_particiones_montadas.Eliminar(desmontar->id);

    cout << "\e[1;32m [SUCCESS]: \e[1;37m La particion se ha desmontado correctamente \e[m\n" << endl;

    lista_particiones_montadas.Mostrar();
}
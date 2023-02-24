#include "Execute.h"

Execute::Execute() {
}

void Execute::AnalizarArchivo(Execute *archivo){
    if(archivo->path == ""){
        cout << "No se ha ingresado una ruta" << endl;
        return;
    }
    Driver driver;
    driver.parseFile(archivo->path);
}
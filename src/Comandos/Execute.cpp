#include "Execute.h"

Execute::Execute() {
}

void Execute::AnalizarArchivo(Execute *archivo){
    Driver driver;
    driver.parseFile(archivo->path);
}
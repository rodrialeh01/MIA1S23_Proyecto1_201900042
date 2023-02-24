#include "Rmdisk.h"

Rmdisk::Rmdisk() {
}

vector<string> Rmdisk::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

void Rmdisk::EliminarDisco(Rmdisk *disco){
    //VALIDACION DEL PATH
    if (disco->path == ""){
        cout << "No se ha ingresado la ruta para eliminar el disco" << endl;
        return;
    }

    //VALIDA SI EXISTE EL DISCO
    vector<string> carpetas = split(disco->path,'/');
    FILE *archivo;
    if(!(archivo = fopen(disco->path.c_str(),"rb"))){
        cout << "ERROR: El disco no se encoentró en el sistema" << endl;
        fclose(archivo);
        return;
    }

    //ELIMINA EL DISCO
    string comando_linux = "rm " + disco->path;
    cout << "Eliminando el disco en " << disco->path<< " ..." << endl;
    sleep(1);
    system(comando_linux.c_str());
    cout << "El Disco ha sido eliminado exitosamente" << endl;
}
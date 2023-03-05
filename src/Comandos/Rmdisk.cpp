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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado la ruta para eliminar el disco \e[m\n" << endl;
        return;
    }

    //VALIDA SI EXISTE EL DISCO
    vector<string> carpetas = split(disco->path,'/');
    FILE *archivo;
    string ruta_validar = disco->path;
    if(ruta_validar[0] == '\"'){
        ruta_validar= ruta_validar.substr(1,disco->path.length()-2);
    }
    if(!(archivo = fopen(ruta_validar.c_str(),"rb"))){
        cout << "\e[1;31m[ERROR]:\e[1;37m El disco no se encontró en el sistema \e[m\n" << endl;
        return;
    }

    //ELIMINA EL DISCO
    string comando_linux = "rm " + disco->path;
    cout << "\n Eliminando el disco en " << disco->path<< " ..." << endl;
    sleep(1);
    system(comando_linux.c_str());
    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Disco ha sido eliminado exitosamente \e[m\n" << endl;
}
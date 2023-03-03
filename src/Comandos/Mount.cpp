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

    //LEE EL ARCHIVO
    FILE *archivo;
    archivo = fopen(montar->path.c_str(), "rb+");
    if(archivo == NULL){
        cout << "ERROR: No se ha encontrado el disco" << endl;
        return;
    }

    //PROCEDE A LEER EL MBR
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    if(mbr.mbr_tamano == 0){
        cout << "ERROR: El disco no tiene particiones" << endl;
        return;
    }
    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'P'){
            if(montar->name == particiones[i].part_name){
                if(!lista_particiones_montadas.ParticionMontada(particiones[i].part_name,montar->path)){
                    cout << "La particion que desea montar ya esta montada" << endl;
                    return;
                }
                string id = "42" + to_string(lista_particiones_montadas.CrearNoParticion(montar->path))+ nombre_disco(montar->path);
                lista_particiones_montadas.Insertar(montar->path,particiones[i].part_name,id,particiones[i].part_type);
                break;
            }
        }else if(particiones[i].part_type == 'E'){
            if(montar->name == particiones[i].part_name){
                if(!lista_particiones_montadas.ParticionMontada(particiones[i].part_name,montar->path)){
                    cout << "La particion que desea montar ya esta montada" << endl;
                    return;
                }
                string id = "42" + to_string(lista_particiones_montadas.CrearNoParticion(montar->path))+ nombre_disco(montar->path);
                lista_particiones_montadas.Insertar(montar->path,particiones[i].part_name,id,particiones[i].part_type);
                break;
            }else{
                vector<EBR> ebrs = ListadoEBR(particiones[i], montar->path);
                for(int j = 0; j < ebrs.size(); j++){
                    if(montar->name == ebrs[j].part_name){
                        if(!lista_particiones_montadas.ParticionMontada(ebrs[j].part_name,montar->path)){
                            cout << "La particion que desea montar ya esta montada" << endl;
                            return;
                        }
                        string id = "42" + to_string(lista_particiones_montadas.CrearNoParticion(montar->path))+ nombre_disco(montar->path);
                        lista_particiones_montadas.Insertar(montar->path,ebrs[j].part_name,id,ebrs[j].part_status);
                        break;
                    }
                }
            }
        }
    }
    fclose(archivo);
    cout << "La particion se ha montado correctamente" << endl;

    lista_particiones_montadas.Mostrar();
}

vector<string> Mount::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Mount::nombre_disco(string path){
    string nombre = "";
    if(path[0] == '"'){
        path = path.substr(1,path.length()-2);
    }
    vector<string> partes_path = split(path,'/');
    nombre = partes_path[partes_path.size()-1];
    nombre = nombre.substr(0,nombre.length()-4);
    return nombre;
}

vector<EBR> Mount::ListadoEBR(Particion extendida, string path){
    vector<EBR> ebrs;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int temp = extendida.part_start;
    while(temp != -1){
        cout << "temp: " << temp << endl;
        fseek(archivo,temp,SEEK_SET);
        EBR ebr;
        fread(&ebr,sizeof(EBR),1,archivo);
        if(!cadenaVacia(ebr.part_name)){
            ebrs.push_back(ebr);
        }else if(cadenaVacia(ebr.part_name) && ebr.part_s != 0){
            ebrs.push_back(ebr);
        }else{
            break;
        }
        temp = ebr.part_next;
    }
    fclose(archivo);
    return ebrs;
}

bool Mount::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}
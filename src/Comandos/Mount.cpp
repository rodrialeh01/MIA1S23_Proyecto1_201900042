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
        if(particiones[i].part_status == '1'){
            cout << "La particion que desea montar ya esta montada" << endl;
            return;
        }
        if(particiones[i].part_type == 'P'){
            if(montar->name == particiones[i].part_name){
                particiones[i].part_status = '1';
                string id = "42" + to_string(lista_particiones_montadas.CrearNoParticion(montar->path))+ nombre_disco(montar->path);
                lista_particiones_montadas.Insertar(montar->path,particiones[i].part_name,id,particiones[i].part_type);
                break;
            }
        }else if(particiones[i].part_type == 'E'){
            if(montar->name == particiones[i].part_name){
                particiones[i].part_status = '1';
                string id = "42" + to_string(lista_particiones_montadas.CrearNoParticion(montar->path))+ nombre_disco(montar->path);
                lista_particiones_montadas.Insertar(montar->path,particiones[i].part_name,id,particiones[i].part_type);
                break;
            }else{
                EBR ebr;
                int temp = particiones[i].part_start;
                while(temp != -1){
                    fseek(archivo, temp, SEEK_SET);
                    fread(&ebr, sizeof(EBR), 1, archivo);
                    if(montar->name == ebr.part_name){
                        if(ebr.part_status == '1'){
                            cout << "La particion que desea montar ya esta montada" << endl;
                            return;
                        }
                        ebr.part_status = '1';
                        string id = "42" + to_string(lista_particiones_montadas.CrearNoParticion(montar->path))+ nombre_disco(montar->path);
                        lista_particiones_montadas.Insertar(montar->path,ebr.part_name,id,'L');
                        fseek(archivo, temp, SEEK_SET);
                        fwrite(&ebr, sizeof(EBR), 1, archivo);
                        break;
                    }
                    temp = ebr.part_next;
                }
            }
        }
    }

    mbr.mbr_particion_1 = particiones[0];
    mbr.mbr_particion_2 = particiones[1];
    mbr.mbr_particion_3 = particiones[2];
    mbr.mbr_particion_4 = particiones[3];

    //ESCRIBE EL MBR
    fseek(archivo, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, archivo);
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
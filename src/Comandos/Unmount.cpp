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

    string path = lista_particiones_montadas.getPath(desmontar->id);
    string name = lista_particiones_montadas.getName(desmontar->id);

    //LEE EL ARCHIVO
    FILE *archivo;
    archivo = fopen(path.c_str(), "rb+");
    if(archivo == NULL){
        cout << "ERROR: No se ha encontrado el disco" << endl;
        return;
    }
    
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
            if(particiones[i].part_type == 'P'){
                if(name == particiones[i].part_name){
                    particiones[i].part_status = '0';
                    lista_particiones_montadas.Eliminar(desmontar->id);
                    break;
                }
            }else if(particiones[i].part_type == 'E'){
                if(name == particiones[i].part_name){
                    particiones[i].part_status = '0';
                    lista_particiones_montadas.Eliminar(desmontar->id);
                    break;
                }else{
                    EBR ebr;
                    int temp = particiones[i].part_start;
                    while(temp != -1){
                        fseek(archivo, temp, SEEK_SET);
                        fread(&ebr, sizeof(EBR), 1, archivo);
                        if(name == ebr.part_name){
                            if(ebr.part_status == '1'){
                                ebr.part_status = '0';
                                lista_particiones_montadas.Eliminar(desmontar->id);
                                fseek(archivo, temp, SEEK_SET);
                                fwrite(&ebr, sizeof(EBR), 1, archivo);
                                break;
                            }else{
                                cout << "ERROR: La particion no esta montada" << endl;
                                return;
                            }
                        }
                        temp = ebr.part_next;
                    }
                }
            }
        }else{
            cout << "ERROR: La particion no esta montada" << endl;
            return;
        }
    }

    mbr.mbr_particion_1 = particiones[0];
    mbr.mbr_particion_2 = particiones[1];
    mbr.mbr_particion_3 = particiones[2];
    mbr.mbr_particion_4 = particiones[3];

    fseek(archivo, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, archivo);
    fclose(archivo);

    cout << "La particion se ha desmontado correctamente" << endl;

    lista_particiones_montadas.Mostrar();
}
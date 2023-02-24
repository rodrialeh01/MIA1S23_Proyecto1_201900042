#include "Fdisk.h"

Fdisk::Fdisk() {
}

vector<string> Fdisk::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Fdisk::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

string Fdisk::toUpperCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += toupper(palabra[i]);
        i++;
    }
    return retorno;
}

bool Fdisk::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

void Fdisk::SistemaDeParticiones(Fdisk *particion){
    //VALIDAR ATRIBUTOS GENERALES OBLIGATORIOS
    //PATH
    if(particion->path == ""){
        cout << "ERROR: No se ha ingresado la ruta para crear la particion" << endl;
        return;
    }

    FILE *archivo;
    if(!(archivo = fopen(particion->path.c_str(),"rb"))){
        cout << "El disco no se encuentro en el sistema" << endl;
        fclose(archivo);
        return;
    }
    fclose(archivo);

    //NAME
    if(particion->name == ""){
        cout << "ERROR: No se ha ingresado el nombre para la particion" << endl;
        return;
    }

    //VALIDAR ATRIBUTOS GENERALES OPCIONALES
    //UNIT
    if(particion->unit == ""){
        particion->unit = "K";
    }

    if(toUpperCase(particion->unit) != "K" && toUpperCase(particion->unit) != "M" && toUpperCase(particion->unit) != "B"){
        cout << "ERROR: No se ha ingresado una unidad válida para la particion" << endl;
        return;
    }

    particion->unit = toUpperCase(particion->unit);

    //TYPE
    if(particion->type == ""){
        particion->type = "P";
    }

    if(toUpperCase(particion->type) != "P" && toUpperCase(particion->type) != "E" && toUpperCase(particion->type) != "L"){
        cout << "ERROR: No se ha ingresado un tipo válido para la particion" << endl;
        return;
    }

    particion->type = toUpperCase(particion->type);

    //FIT
    if(particion->fit == ""){
        particion->fit = "WF";
    }

    if(toUpperCase(particion->fit) != "FF" && toUpperCase(particion->fit) != "BF" && toUpperCase(particion->fit) != "WF"){
        cout << "ERROR: No se ha ingresado un ajuste válido para la particion" << endl;
        return;
    }

    particion->fit = toUpperCase(particion->fit);

    //DELETE
    if(toUpperCase(particion->dsk_delete) == "FULL"){
        particion->dsk_delete = "FULL";
    }

    //VALIDACIONES PARA VER QUE ACCIONES QUIERE REALIZAR
    //CREAR PARTICION
    if(particion->size > 0){
        AgregarParticion(particion);
    }else if(particion->dsk_delete == "FULL"){
        EliminarParticion(particion);
    }else if(particion->add != 0){
        Cambiar_Tamanio_Particion(particion);
    }

}

void Fdisk::AgregarParticion(Fdisk *particion){
   //VALIDACION DEL SIZE
    if(particion->size <= 0){
       cout << "ERROR: No se ha ingresado un tamaño válido para la particion" << endl;
       return;
    }

    //VALIDACION DEL UNIT
    if(particion->unit == "K"){
        particion->size = particion->size * 1024;
    }else if(particion->unit == "M"){
        particion->size = particion->size * 1024 * 1024;
    }

    //VALIDACION DE QUE HAYAN 4 PARTICIONES PRIMARIAS O 3 PRIMARIAS Y 1 EXTENDIDA
    int cantidad_primarias = 0;
    int cantidad_extendidas = 0;
    vector<Particion> particiones;

    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    MBR mbr;
    fseek(archivo,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,archivo);
    fclose(archivo);

    //MUESTRO TEMPORALMENTE EL MBR
    cout << "================MBR==================" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
    cout << "Firma: " << mbr.mbr_dsk_signature << endl;
    cout << "\t- Particion 1: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_1.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
    cout << "\t- Particion 2: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_2.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
    cout << "\t- Particion 3: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_3.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
    cout << "\t- Particion 4: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_4.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
    cout << "=====================================" << endl;

    particiones.push_back(mbr.mbr_particion_1);
    particiones.push_back(mbr.mbr_particion_2);
    particiones.push_back(mbr.mbr_particion_3);
    particiones.push_back(mbr.mbr_particion_4);

    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'P'){
            cantidad_primarias++;
        }else if(particiones[i].part_type == 'E'){
            cantidad_extendidas++;
        }
    }

    if(particion->type == "P"){
        if(cantidad_primarias == 4){
            cout << "ERROR: Ya existen 4 particiones primarias" << endl;
            return;
        }
    }else if(particion->type == "E"){
        if(cantidad_primarias == 4){
            cout << "ERROR: Ya existen 4 particiones primarias" << endl;
            return;
        }else if(cantidad_extendidas == 1){
            cout << "ERROR: Ya existe una particion extendida" << endl;
            return;
        }
    }else if(particion->type == "L"){
        if(cantidad_extendidas == 0){
            cout << "ERROR: No existe una particion extendida para poder agregar su partición Lógica" << endl;
            return;
        }
    }

    //VALIDACION DE QUE NO EXISTA UNA PARTICION CON EL MISMO NOMBRE
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion->name){
            cout << "ERROR: Ya existe una particion con el mismo nombre" << endl;
            return;
        }
    }

    //VALIDACION QUE LA PARTICION A CREAR NO SEA DE MAYOR TAMAÑO QUE EL DISCO
    if(particion->size > mbr.mbr_tamano){
        cout << "ERROR: El tamaño de la particion es mayor al tamaño del disco" << endl;
        return;
    }

    //UNICAMENTE ESTOS METODOS APLICAN PARA PARTICIONES PRIMARIAS Y EXTENDIDAS

    if(particion->type == "P" || particion->type == "E"){
        //PARA PODER CREAR LA PARTICION SE MANDARA A SUS RESPECTIVOS AJUSTES
        if(mbr.disk_fit == 'F'){
            FirstFit(particiones,mbr, particion);
        }else if(mbr.disk_fit == 'B'){
            BestFit(particiones,mbr, particion);
        }else if(mbr.disk_fit == 'W'){
            WorstFit(particiones,mbr, particion);
        }
    }else if(particion->type == "L"){
        //AgregarParticionLogica(particion, mbr);
    }


}

//METODO PARA PODER APLICAR EL PRIMER AJUSTE
void Fdisk::FirstFit(vector<Particion> particiones, MBR mbr,Fdisk *particion){
    //VERIFICA CUANDO COMIENZA A NO TENER 4 PARTICIONES EL DISCO QUE FUERON CREADAS ANTES
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_start == -1){
            if(i == 0){
                particiones[i].part_start = sizeof(MBR);
                particiones[i].part_s = particion->size;
                particiones[i].part_type = particion->type[0];
                particiones[i].part_fit = particion->fit[0];
                strcpy(particiones[i].part_name , particion->name.c_str());
                ActualizarDisco(particiones, mbr, particion->path);
                return;
            }else{
                int tamanio_disponible = mbr.mbr_tamano - particiones[i-1].part_start - particiones[i-1].part_s;
                if(tamanio_disponible >= particion->size){
                    particiones[i].part_start = particiones[i-1].part_start + particiones[i-1].part_s;
                    particiones[i].part_s = particion->size;
                    particiones[i].part_type = particion->type[0];
                    particiones[i].part_fit = particion->fit[0];
                    strcpy(particiones[i].part_name , particion->name.c_str());
                    ActualizarDisco(particiones, mbr, particion->path);
                    return;
                }else{
                    cout << "ERROR: No hay espacio suficiente para crear la particion" << endl;
                    return;
                }
            }
        }
    }

    bool error = true;
    //VERIFICA EN LAS PARTICIONES QUE ANTERIORMENTE FUERON ELIMINADAS
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_start != -1){
            if(cadenaVacia(particiones[i].part_name)){
                if(i != 3){
                    int espacio_disponible = particiones[i+1].part_start - particiones[i].part_start;
                    if(espacio_disponible >= particion->size){
                        particiones[i].part_s = particion->size;
                        particiones[i].part_type = particion->type[0];
                        particiones[i].part_fit = particion->fit[0];
                        strcpy(particiones[i].part_name , particion->name.c_str());
                        error = false;
                        ActualizarDisco(particiones, mbr, particion->path);
                        break;
                    }
                }else if(i == 3){
                    int espacio_disponible = mbr.mbr_tamano - particiones[i].part_start;
                    if(espacio_disponible >= particion->size){
                        particiones[i].part_s = particion->size;
                        particiones[i].part_type = particion->type[0];
                        particiones[i].part_fit = particion->fit[0];
                        strcpy(particiones[i].part_name , particion->name.c_str());
                        error = false;
                        ActualizarDisco(particiones, mbr, particion->path);
                        break;
                    }
                }
            }

        }
    }

    if(error){
        cout << "ERROR: No se pudo crear la partición" << endl;
    }
}

void Fdisk::BestFit(vector<Particion> particiones, MBR mbr,Fdisk *particion){
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_start == -1){
            if(i == 0){
                particiones[i].part_start = sizeof(MBR);
                particiones[i].part_s = particion->size;
                particiones[i].part_type = particion->type[0];
                particiones[i].part_fit = particion->fit[0];
                strcpy(particiones[i].part_name , particion->name.c_str());
                ActualizarDisco(particiones, mbr, particion->path);
                return;
            }else{
                int tamanio_disponible = mbr.mbr_tamano - particiones[i-1].part_start - particiones[i-1].part_s;
                if(tamanio_disponible >= particion->size){
                    particiones[i].part_start = particiones[i-1].part_start + particiones[i-1].part_s;
                    particiones[i].part_s = particion->size;
                    particiones[i].part_type = particion->type[0];
                    particiones[i].part_fit = particion->fit[0];
                    strcpy(particiones[i].part_name , particion->name.c_str());
                    ActualizarDisco(particiones, mbr, particion->path);
                    return;
                }else{
                    cout << "ERROR: No hay espacio suficiente para crear la particion" << endl;
                    return;
                }
            }
        }
    }

    int espacio_pequeño = 1*1024*1024*1024;
    int no_particion = 0;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_start != -1){
            if(cadenaVacia(particiones[i].part_name)){
                if(particiones[i].part_s < espacio_pequeño){
                    espacio_pequeño = particiones[i].part_s;
                    no_particion = i;
                }
            }
        }
    }

    if(espacio_pequeño == 1*1024*1024*1024){
        cout << "ERROR: No se pudo crear la partición ya que no hay espacio" << endl;
        return;
    }else{
        particiones[no_particion].part_s = particion->size;
        particiones[no_particion].part_type = particion->type[0];
        particiones[no_particion].part_fit = particion->fit[0];
        strcpy(particiones[no_particion].part_name , particion->name.c_str());
        ActualizarDisco(particiones, mbr, particion->path);
    }

}

void Fdisk::WorstFit(vector<Particion> particiones, MBR mbr,Fdisk *particion){
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_start == -1){
            if(i == 0){
                particiones[i].part_start = sizeof(MBR);
                particiones[i].part_s = particion->size;
                particiones[i].part_type = particion->type[0];
                particiones[i].part_fit = particion->fit[0];
                strcpy(particiones[i].part_name , particion->name.c_str());
                ActualizarDisco(particiones, mbr, particion->path);
                return;
            }else{
                int tamanio_disponible = mbr.mbr_tamano - particiones[i-1].part_start - particiones[i-1].part_s;
                if(tamanio_disponible >= particion->size){
                    particiones[i].part_start = particiones[i-1].part_start + particiones[i-1].part_s;
                    particiones[i].part_s = particion->size;
                    particiones[i].part_type = particion->type[0];
                    particiones[i].part_fit = particion->fit[0];
                    strcpy(particiones[i].part_name , particion->name.c_str());
                    ActualizarDisco(particiones, mbr, particion->path);
                    return;
                }else{
                    cout << "ERROR: No hay espacio suficiente para crear la particion" << endl;
                    return;
                }
            }
        }
    }

    int espacio_grande = 0;
    int no_particion = 0;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_start != -1){
            if(cadenaVacia(particiones[i].part_name)){
                if(particiones[i].part_s > espacio_grande){
                    espacio_grande = particiones[i].part_s;
                    no_particion = i;
                }
            }
        }
    }

    if(espacio_grande == 0){
        cout << "ERROR: No se pudo crear la partición ya que no hay espacio" << endl;
        return;
    }else{
        particiones[no_particion].part_s = particion->size;
        particiones[no_particion].part_type = particion->type[0];
        particiones[no_particion].part_fit = particion->fit[0];
        strcpy(particiones[no_particion].part_name , particion->name.c_str());
        ActualizarDisco(particiones, mbr, particion->path);
    }

}

void Fdisk::ActualizarDisco(vector<Particion> particiones,MBR mbr, string path){
    mbr.mbr_particion_1 = particiones[0];
    mbr.mbr_particion_2 = particiones[1];
    mbr.mbr_particion_3 = particiones[2];
    mbr.mbr_particion_4 = particiones[3];    
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    fseek(archivo,0,SEEK_SET);
    fwrite(&mbr,sizeof(MBR),1,archivo);
    fclose(archivo);

    //MUESTRO TEMPORALMENTE EL MBR
    cout << "================MBR==================" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
    cout << "Firma: " << mbr.mbr_dsk_signature << endl;
    cout << "\t- Particion 1: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_1.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
    cout << "\t- Particion 2: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_2.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
    cout << "\t- Particion 3: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_3.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
    cout << "\t- Particion 4: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_4.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
    cout << "=====================================" << endl;

    cout << "La Particion fue creada exitosamente" << endl;
    return;
}

void Fdisk::AgregarParticionLogica(Fdisk *particion, MBR mbr_dsk){

}


void Fdisk::EliminarParticion(Fdisk *particion){
    vector<Particion> particiones;
    //OBTIENE LA INFORMACION DEL MBR
    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    MBR mbr;
    fseek(archivo,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,archivo);
    fclose(archivo);

    //MUESTRO TEMPORALMENTE EL MBR
    cout << "================MBR==================" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
    cout << "Firma: " << mbr.mbr_dsk_signature << endl;
    cout << "\t- Particion 1: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_1.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
    cout << "\t- Particion 2: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_2.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
    cout << "\t- Particion 3: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_3.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
    cout << "\t- Particion 4: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_4.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
    cout << "=====================================" << endl;

    particiones.push_back(mbr.mbr_particion_1);
    particiones.push_back(mbr.mbr_particion_2);
    particiones.push_back(mbr.mbr_particion_3);
    particiones.push_back(mbr.mbr_particion_4);

    //VALIDA SI EXISTE LA PARTICION
    bool existe = false;
    int part_eliminada_inicio = 0;
    int part_eliminada_fin = 0;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion->name){
            particiones[i].part_status = '0';
            for(int j = 0; j < 16; j++){
                particiones[i].part_name[j] = '\0';
            }
            particiones[i].part_type = '\0';
            particiones[i].part_fit = '\0';
            part_eliminada_inicio = particiones[i].part_start;
            part_eliminada_fin = particiones[i].part_start + particiones[i].part_s;
            existe = true;
        }
    }
    if(!existe){
        cout << "ERROR: El nombre ingresado no coincide con las particiones que se encuentran dentro del disco" << endl;
        return;
    }else{
        //ACTUALIZA EL MBR EN EL ARCHIVO Y ELIMINA LA PARTICION Y LA LLENA DE CEROS
        mbr.mbr_particion_1 = particiones[0];
        mbr.mbr_particion_2 = particiones[1];
        mbr.mbr_particion_3 = particiones[2];
        mbr.mbr_particion_4 = particiones[3];    
        FILE *archivo;
        archivo = fopen(path.c_str(),"rb+");
        fseek(archivo,0,SEEK_SET);
        fwrite(&mbr,sizeof(MBR),1,archivo);
        fseek(archivo,part_eliminada_inicio,SEEK_SET);
        for(int i = part_eliminada_inicio; i < part_eliminada_fin; i++){
            char cero = '\0';
            fwrite(&cero,1,1,archivo);
        }
        fclose(archivo);

        //MUESTRO TEMPORALMENTE EL MBR
        cout << "================MBR==================" << endl;
        cout << "Tamaño: " << mbr.mbr_tamano << endl;
        cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
        cout << "Firma: " << mbr.mbr_dsk_signature << endl;
        cout << "\t- Particion 1: "  << endl;
        cout << "\t\t-Name: " << mbr.mbr_particion_1.part_name << endl;
        cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
        cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
        cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
        cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
        cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
        cout << "\t- Particion 2: "  << endl;
        cout << "\t\t-Name: " << mbr.mbr_particion_2.part_name << endl;
        cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
        cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
        cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
        cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
        cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
        cout << "\t- Particion 3: "  << endl;
        cout << "\t\t-Name: " << mbr.mbr_particion_3.part_name << endl;
        cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
        cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
        cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
        cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
        cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
        cout << "\t- Particion 4: "  << endl;
        cout << "\t\t-Name: " << mbr.mbr_particion_4.part_name << endl;
        cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
        cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
        cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
        cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
        cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
        cout << "=====================================" << endl;

        cout << "La Particion fue eliminada correctamente" << endl;
    }
}

void Fdisk::Cambiar_Tamanio_Particion(Fdisk *particion){
    vector<Particion> particiones;
    //OBTIENE LA INFORMACION DEL MBR
    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    MBR mbr;
    fseek(archivo,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,archivo);
    fclose(archivo);

    //MUESTRO TEMPORALMENTE EL MBR
    cout << "================MBR==================" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
    cout << "Firma: " << mbr.mbr_dsk_signature << endl;
    cout << "\t- Particion 1: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_1.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
    cout << "\t- Particion 2: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_2.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
    cout << "\t- Particion 3: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_3.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
    cout << "\t- Particion 4: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_4.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
    cout << "=====================================" << endl;

    particiones.push_back(mbr.mbr_particion_1);
    particiones.push_back(mbr.mbr_particion_2);
    particiones.push_back(mbr.mbr_particion_3);
    particiones.push_back(mbr.mbr_particion_4);

    int extra = particion->add;
    if(particion->unit == "K"){
        extra = extra * 1024;
    }else if(particion->unit == "M"){
        extra = extra * 1024 * 1024;
    }

    //BUSCO LA PARTICION A LA CUAL VOY A AGREGAR O QUITAR EL ESPACIO
    bool error = true;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion->name){
            //SI LA PARTICION ES PRIMARIA 
            if(particiones[i].part_type == 'P'){
                if(i != 3){
                    if(particiones[i+1].part_start != -1){
                        int nuevo_tamanio = particiones[i].part_s + extra;
                        if(nuevo_tamanio > 0 && nuevo_tamanio < particiones[i+1].part_start){
                            particiones[i].part_s = nuevo_tamanio;
                            error = false;
                            break;
                        }else{
                            cout << "No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso" << endl;
                            return;
                        }
                    }else{
                        int nuevo_tamanio = particiones[i].part_s + extra;
                        if(nuevo_tamanio > 0 && nuevo_tamanio < mbr.mbr_tamano){
                            particiones[i].part_s = nuevo_tamanio;
                            error = false;
                            break;
                        }else{
                            cout << "No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso" << endl;
                            return;
                        }
                    }
                }else{
                    int nuevo_tamanio = particiones[i].part_s + extra;
                    if(nuevo_tamanio > 0 && nuevo_tamanio < mbr.mbr_tamano){
                        particiones[i].part_s = nuevo_tamanio;
                        error = false;
                        break;
                    }else{
                        cout << "No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso" << endl;
                        return;
                    }
                }
            }
        }
    }

    if(error){
        cout << "No se encontro la particion con el nombre: " << particion->name << endl;
        return;
    }

    //ACTUALIZO EL DISCO
    mbr.mbr_particion_1 = particiones[0];
    mbr.mbr_particion_2 = particiones[1];
    mbr.mbr_particion_3 = particiones[2];
    mbr.mbr_particion_4 = particiones[3];    
    FILE *archivo1;
    archivo1 = fopen(path.c_str(),"rb+");
    fseek(archivo1,0,SEEK_SET);
    fwrite(&mbr,sizeof(MBR),1,archivo1);
    fclose(archivo);

    //MUESTRO TEMPORALMENTE EL MBR
    cout << "================MBR==================" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
    cout << "Firma: " << mbr.mbr_dsk_signature << endl;
    cout << "\t- Particion 1: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_1.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
    cout << "\t- Particion 2: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_2.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
    cout << "\t- Particion 3: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_3.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
    cout << "\t- Particion 4: "  << endl;
    cout << "\t\t-Name: " << mbr.mbr_particion_4.part_name << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
    cout << "=====================================" << endl;

    cout << "La Particion fue modificada exitosamente" << endl;
    
}

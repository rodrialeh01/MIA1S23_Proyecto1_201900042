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
        }else if(particiones[i].part_type == 'E'){
            //SI EXISTE UNA PARTICION EXTENDIDA SE DEBE DE BUSCAR EN SU EBR
            int temp = particiones[i].part_start;
            while(temp != -1){
                EBR ebr;
                fseek(archivo, temp, SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, archivo);
                if(ebr.part_name == particion->name){
                    cout << "ERROR: Ya existe una particion con el mismo nombre" << endl;
                    return;
                }
                temp = ebr.part_next;
            }
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
        AgregarParticionLogica(particiones,mbr, particion);
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

    //VALIDO SI EXISTE EL NOMBRE DE LA PARTICION
    bool encontrado = false;
    bool logica = false;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion->name){
            encontrado = true;
            break;
        }else if(particiones[i].part_type == 'E'){
            //OBTIENE LA INFORMACION DEL EBR
            FILE *archivo;
            archivo = fopen(particion->path.c_str(),"rb+");
            EBR ebr;
            int temp = particiones[i].part_start;
            while(temp != -1){
                fseek(archivo,temp,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,archivo);
                if(ebr.part_name == particion->name){
                    encontrado = true;
                    logica = true;
                    break;
                }
                temp = ebr.part_next;
            }
            
            fclose(archivo);
        }
    }

    //VALIDA EL TIPO DE PARTICION A ELIMINAR
    if(encontrado){
        if(logica){
            EliminarParticionLogica(particiones, mbr, particion);
        }else{
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
    }else{
        cout << "ERROR: La particion no existe" << endl;
        return;
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

    //VALIDO SI EXISTE EL NOMBRE DE LA PARTICION
    bool encontrado = false;
    bool logica = false;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion->name){
            encontrado = true;
            break;
        }else if(particiones[i].part_type == 'E'){
            //OBTIENE LA INFORMACION DEL EBR
            FILE *archivo;
            archivo = fopen(particion->path.c_str(),"rb+");
            EBR ebr;
            int temp = particiones[i].part_start;
            while(temp != -1){
                fseek(archivo,temp,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,archivo);
                if(ebr.part_name == particion->name){
                    encontrado = true;
                    logica = true;
                    break;
                }
                temp = ebr.part_next;
            }
            
            fclose(archivo);
        }
    }

    int extra = particion->add;
    if(particion->unit == "K"){
        extra = extra * 1024;
    }else if(particion->unit == "M"){
        extra = extra * 1024 * 1024;
    }

    if(!encontrado){
        cout << "ERROR: No se encontro la particion con el nombre: " << particion->name << endl;
        return;
    }

    if(!logica){
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
    }else{
        //BUSCO LA PARTICION A LA CUAL VOY A AGREGAR O QUITAR EL ESPACIO
        bool error = true;
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_type == 'E'){
                //OBTIENE LA INFORMACION DEL EBR
                FILE *archivo;
                archivo = fopen(particion->path.c_str(),"rb+");
                EBR ebr;
                int temp = particiones[i].part_start;
                while(temp != -1){
                    fseek(archivo,temp,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,archivo);
                    if(ebr.part_name == particion->name){
                        if(ebr.part_next != -1){
                            int nuevo_tamanio = ebr.part_s + extra;
                            if(nuevo_tamanio > 0 && nuevo_tamanio < ebr.part_next){
                                ebr.part_s = nuevo_tamanio;
                                fseek(archivo,temp,SEEK_SET);
                                fwrite(&ebr,sizeof(EBR),1,archivo);
                                error = false;
                                break;
                            }else{
                                cout << "No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso" << endl;
                                return;
                            }
                        }else{
                            int nuevo_tamanio = ebr.part_s + extra;
                            if(nuevo_tamanio > 0 && nuevo_tamanio < particiones[i].part_s){
                                ebr.part_s = nuevo_tamanio;
                                fseek(archivo,temp,SEEK_SET);
                                fwrite(&ebr,sizeof(EBR),1,archivo);
                                error = false;
                                break;
                            }else{
                                cout << "No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso" << endl;
                                return;
                            }
                        }
                        
                    }
                    temp = ebr.part_next;
                }
                
                fclose(archivo);
            }
        }

        if(error){
            cout << "No se encontro la particion con el nombre: " << particion->name << endl;
            return;
        }
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


void Fdisk::AgregarParticionLogica(vector<Particion> particiones, MBR mbr,Fdisk *particion){
    //BUSCO SI EXISTE LA PARTICION EXTENDIDA
    bool error = true;
    int particion_id = 0;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'E'){
            error = false;
            particion_id = i;
        }
    }

    if(error){
        cout << "ERROR: No se encontro la particion extendida en el disco" << endl;
        return;
    }

    //POSICION INICIAL DE LA PARTICION EXTENDIDA
    int inicio = particiones[particion_id].part_start;
    //POSICION FINAL DE LA PARTICION EXTENDIDA
    int final = particiones[particion_id].part_start + particiones[particion_id].part_s;
    //TAMAÑO DE LA PARTICION EXTENDIDA
    int tamanio = particiones[particion_id].part_s;
    
    //VERIFICACIONES PARA CREAR LA PARTICION LOGICA
    //TAMANIO
    if(particion->size > tamanio){
        cout << "ERROR: No se puede crear la particion logica, el tamaño de la particion a crear es mayor al tamaño de la particion extendida" << endl;
        return;
    }

    //ABRE EL ARCHIVO PARA VER SI HAY UN EBR
    vector<EBR> logicas = ListadoEBR(particiones[particion_id],particion->path);

    if(logicas.size()  == 0){
        //CREO EL PRIMER EBR
        EBR ebr;
        ebr.part_status = '0';
        ebr.part_fit = particion->fit[0];
        ebr.part_start = inicio;
        ebr.part_s = particion->size;
        ebr.part_next = -1;
        strcpy(ebr.part_name,particion->name.c_str());
        cout << "SIUUUUUUUUUU" << endl;
        cout << "================= EBR =================" << endl;
        cout << "\t- Status: " << ebr.part_status << endl;
        cout << "\t- Fit: " << ebr.part_fit << endl;
        cout << "\t- Start: " << ebr.part_start << endl;
        cout << "\t- Size: " << ebr.part_s << endl;
        cout << "\t- Next: " << ebr.part_next << endl;
        cout << "\t- Name: " << ebr.part_name << endl;
        cout << "======================================" << endl;
        AgregarEBR(ebr,particion->path);
    }else{
        //OBTENGO EL ULTIMO EBR
        EBR ultimo = retornarUlitmoEBR(logicas);
        //VERIFICO SI HAY ESPACIO PARA CREAR LA PARTICION LOGICA
        int espacio = final - (ultimo.part_start + ultimo.part_s);
        if(espacio < particion->size){
            cout << "ERROR: No se puede crear la particion logica, no hay espacio suficiente en la particion extendida" << endl;
            return;
        }
        //CREO EL NUEVO EBR
        EBR ebr;
        ebr.part_status = '0';
        ebr.part_fit = particion->fit[0];
        if(particion->fit[0] == 'f' || particion->fit[0] == 'F'){
            ebr.part_fit = 'F';
            if(FirstFit_Logicas(logicas,particion->size,final) != -1){
                ebr.part_start = FirstFit_Logicas(logicas,particion->size, final);
            }else{
                cout << "ERROR: No se puede crear la particion logica, no hay espacio suficiente " << endl;
                return;
            }
        }else if(particion->fit[0] == 'b' || particion->fit[0] == 'B'){
            ebr.part_fit = 'B';
            if(BestFit_Logicas(logicas,particion->size, final) != -1){
                ebr.part_start = BestFit_Logicas(logicas,particion->size, final);
            }else{
                cout << "ERROR: No se puede crear la particion logica, no hay espacio suficiente " << endl;
                return;
            }
        }else if(particion->fit[0] == 'w' || particion->fit[0] == 'W'){
            ebr.part_fit = 'W';
            if(WorstFit_Logicas(logicas,particion->size, final) != -1){
                ebr.part_start = WorstFit_Logicas(logicas,particion->size, final);
            }else{
                cout << "ERROR: No se puede crear la particion logica, no hay espacio suficiente " << endl;
                return;
            }
        }
        ebr.part_s = particion->size;
        ebr.part_next = -1;
        strcpy(ebr.part_name,particion->name.c_str());
        cout << "================= EBR =================" << endl;
        cout << "\t- Status: " << ebr.part_status << endl;
        cout << "\t- Fit: " << ebr.part_fit << endl;
        cout << "\t- Start: " << ebr.part_start << endl;
        cout << "\t- Size: " << ebr.part_s << endl;
        cout << "\t- Next: " << ebr.part_next << endl;
        cout << "\t- Name: " << ebr.part_name << endl;
        cout << "======================================" << endl;
        AgregarEBR(ebr,particion->path);
        //ACTUALIZO EL ULTIMO EBR
        ultimo.part_next = ebr.part_start;
        cout << "================= EBR =================" << endl;
        cout << "\t- Status: " << ultimo.part_status << endl;
        cout << "\t- Fit: " << ultimo.part_fit << endl;
        cout << "\t- Start: " << ultimo.part_start << endl;
        cout << "\t- Size: " << ultimo.part_s << endl;
        cout << "\t- Next: " << ultimo.part_next << endl;
        cout << "\t- Name: " << ultimo.part_name << endl;
        cout << "======================================" << endl;
        ActualizarEBR(ultimo,particion->path);

    }
}

vector<EBR> Fdisk::ListadoEBR(Particion extendida, string path){
    vector<EBR> ebrs;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int temp = extendida.part_start;
    while(temp != -1){
        fseek(archivo,temp,SEEK_SET);
        EBR ebr;
        fread(&ebr,sizeof(EBR),1,archivo);
        if(!cadenaVacia(ebr.part_name)){
            ebrs.push_back(ebr);
        }else{
            break;
        }
        temp = ebr.part_next;
    }
    fclose(archivo);
    return ebrs;
}

EBR Fdisk::retornarUlitmoEBR(vector<EBR> ebrs){
    EBR ebr;
    for(int i = 0; i < ebrs.size(); i++){
        if(ebrs[i].part_next == -1){
            ebr = ebrs[i];
        }
    }
    return ebr;
}

void Fdisk::ActualizarEBR(EBR ebr, string path){
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    if(archivo == NULL){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fseek(archivo,ebr.part_start,SEEK_SET);
    fwrite(&ebr,sizeof(EBR),1,archivo);
    fclose(archivo);
}

void Fdisk::AgregarEBR(EBR ebr, string path){
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    if(archivo == NULL){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fseek(archivo,ebr.part_start,SEEK_SET);
    fwrite(&ebr,sizeof(EBR),1,archivo);
    fclose(archivo);
}

void Fdisk::EliminarParticionLogica(vector<Particion> particiones, MBR mbr,Fdisk *particion){
    //BUSCO SI EXISTE LA PARTICION EXTENDIDA
    bool error = true;
    int particion_id = 0;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'E'){
            error = false;
            particion_id = i;
        }
    }

    if(error){
        cout << "ERROR: No se encontro la particion extendida en el disco" << endl;
        return;
    }

    //POSICION INICIAL DE LA PARTICION EXTENDIDA
    int inicio = particiones[particion_id].part_start;
    //POSICION FINAL DE LA PARTICION EXTENDIDA
    int final = particiones[particion_id].part_start + particiones[particion_id].part_s;
    //TAMAÑO DE LA PARTICION EXTENDIDA
    int tamanio = particiones[particion_id].part_s;

    //ABRE EL ARCHIVO PARA VER SI HAY UN EBR
    vector<EBR> logicas = ListadoEBR(particiones[particion_id],particion->path);

    if(logicas.size() == 0){
        cout << "ERROR: No se encontro ninguna particion logica en la particion extendida" << endl;
        return;
    }

    //BUSCO LA PARTICION LOGICA A ELIMINAR
    bool error2 = true;
    int particion_id2 = 0;
    for(int i = 0; i < logicas.size(); i++){
        if(logicas[i].part_name == particion->name){
            error2 = false;
            particion_id2 = i;
        }
    }

    if(error2){
        cout << "ERROR: No se encontro la particion logica que se quiere eliminar" << endl;
        return;
    }

    //ELIMINO LA PARTICION LOGICA
    EBR ebr;
    ebr.part_status = '0';
    ebr.part_fit = '\0';
    for(int i = 0; i < 16; i++){
        ebr.part_name[i] = '\0';
    }

    ActualizarEBR(ebr,particion->path);

    //LLENO DE CEROS LA PARTICION LOGICA
    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    if(archivo == NULL){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fseek(archivo,logicas[particion_id2].part_start+ sizeof(EBR),SEEK_SET);
    for(int i = 0; i < logicas[particion_id2].part_s; i++){
        char cero = '\0';
        fwrite(&cero,1,1,archivo);
    }
    fclose(archivo);

    cout << "PARTICION LOGICA ELIMINADA" << endl;

}

int Fdisk:: FirstFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe){
    int inicio = -1;
    for(int i = 0; i < ebrs.size(); i++){
        if(i != ebrs.size()-1){
            if(cadenaVacia(ebrs[i].part_name)){
                if((ebrs[i].part_s-ebrs[i].part_start) >= tamanio){
                    return inicio;
                }
            }
        }else{
            if(cadenaVacia(ebrs[i].part_name)){
                if((final_pe-ebrs[i].part_start) >= tamanio){
                    return inicio;
                }
            }
        }
        inicio = ebrs[i].part_next;
    }
    return inicio;
}

int Fdisk:: BestFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe){
    int mejor_ajuste = 999999999;
    int mejor_inicio = -1;
    for(int i = 0; i < ebrs.size(); i++){
        if(i != ebrs.size()-1){
            if(cadenaVacia(ebrs[i].part_name)){
                if((ebrs[i].part_s-ebrs[i].part_start) >= tamanio){
                    if((ebrs[i].part_s-ebrs[i].part_start) < mejor_ajuste){
                        mejor_ajuste = ebrs[i].part_s-ebrs[i].part_start;
                        mejor_inicio = ebrs[i].part_start;
                    }
                }
            }
        }else{
            if(cadenaVacia(ebrs[i].part_name)){
                if((final_pe-ebrs[i].part_start) >= tamanio){
                    if((final_pe-ebrs[i].part_start) < mejor_ajuste){
                        mejor_ajuste = final_pe-ebrs[i].part_start;
                        mejor_inicio = ebrs[i].part_start;
                    }
                }
            }
        }
    }
    return mejor_inicio;
}

int Fdisk:: WorstFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe){
    int peor_ajuste = 0;
    int peor_inicio = -1;
    for(int i = 0; i < ebrs.size(); i++){
        if(i != ebrs.size()-1){
            if(cadenaVacia(ebrs[i].part_name)){
                if((ebrs[i].part_s-ebrs[i].part_start) >= tamanio){
                    if((ebrs[i].part_s-ebrs[i].part_start) > peor_ajuste){
                        peor_ajuste = ebrs[i].part_s-ebrs[i].part_start;
                        peor_inicio = ebrs[i].part_start;
                    }
                }
            }
        }else{
            if(cadenaVacia(ebrs[i].part_name)){
                if((final_pe-ebrs[i].part_start) >= tamanio){
                    if((final_pe-ebrs[i].part_start) > peor_ajuste){
                        peor_ajuste = final_pe-ebrs[i].part_start;
                        peor_inicio = ebrs[i].part_start;
                    }
                }
            }
        }
    }
    return peor_inicio;
}
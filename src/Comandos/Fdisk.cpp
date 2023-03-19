#include "Fdisk.h"

Fdisk::Fdisk() {
}

//FUNCION PARA APLICAR EL SPLIT A UNA CADENA DE TEXTO
vector<string> Fdisk::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

//FUNCION PARA CONVERTIR UNA CADENA DE TEXTO A MINUSCULAS
string Fdisk::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

//FUNCION PARA CONVERTIR UNA CADENA DE TEXTO A MAYUSCULAS
string Fdisk::toUpperCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += toupper(palabra[i]);
        i++;
    }
    return retorno;
}

//FUNCION PARA VALIDAR SI UNA CADENA[16] DE TEXTO ESTA VACIA
bool Fdisk::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

//METODO PARA VER LAS ACCIONES A REALIZAR EN EL SISTEMA DE PARTICIONES
void Fdisk::SistemaDeParticiones(Fdisk *particion){
    //VALIDAR ATRIBUTOS GENERALES OBLIGATORIOS
    //PATH
    if(particion->path == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado la ruta para crear la particion\e[m\n" << endl;
        return;
    }

    FILE *archivo;
    if(particion->path[0] == '\"'){
        particion->path= particion->path.substr(1,particion->path.length()-2);
    }
    if(!(archivo = fopen(particion->path.c_str(),"rb"))){
        cout << "\e[1;31m[ERROR]:\e[1;37m El disco no se encuentro en el sistema\e[m\n" << endl;
        return;
    }
    fclose(archivo);

    //NAME
    if(particion->name == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado el nombre para la particion\e[m\n" << endl;
        return;
    }

    //VALIDAR ATRIBUTOS GENERALES OPCIONALES
    //UNIT
    if(particion->unit == ""){
        particion->unit = "K";
    }

    if(toUpperCase(particion->unit) != "K" && toUpperCase(particion->unit) != "M" && toUpperCase(particion->unit) != "B"){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado una unidad válida para la particion\e[m\n" << endl;
        return;
    }

    particion->unit = toUpperCase(particion->unit);

    //TYPE
    if(particion->type == ""){
        particion->type = "P";
    }

    if(toUpperCase(particion->type) != "P" && toUpperCase(particion->type) != "E" && toUpperCase(particion->type) != "L"){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado un tipo válido para la particion\e[m\n" << endl;
        return;
    }

    particion->type = toUpperCase(particion->type);

    //FIT
    if(particion->fit == ""){
        particion->fit = "WF";
    }

    if(toUpperCase(particion->fit) != "FF" && toUpperCase(particion->fit) != "BF" && toUpperCase(particion->fit) != "WF"){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado un ajuste válido para la particion\e[m\n" << endl;
        return;
    }

    particion->fit = toUpperCase(particion->fit);

    //DELETE
    if(toUpperCase(particion->dsk_delete) == "FULL"){
        particion->dsk_delete = "FULL";
    }

    if(particion->name[0] == '\"'){
        particion->name = particion->name.substr(1,particion->name.length()-2);
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

//METODO PARA CREAR UNA PARTICION
void Fdisk::AgregarParticion(Fdisk *particion){
   //VALIDACION DEL SIZE
    if(particion->size <= 0){
       cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado un tamaño válido para la particion\e[m\n" << endl;
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
            cout << "\e[1;31m[ERROR]:\e[1;37m Ya existen 4 particiones primarias\e[m\n" << endl;
            return;
        }
    }else if(particion->type == "E"){
        if(cantidad_primarias == 4){
            cout << "\e[1;31m[ERROR]:\e[1;37m Ya existen 4 particiones primarias\e[m\n" << endl;
            return;
        }else if(cantidad_extendidas == 1){
            cout << "\e[1;31m[ERROR]:\e[1;37m Ya existe una particion extendida\e[m\n" << endl;
            return;
        }
    }else if(particion->type == "L"){
        if(cantidad_extendidas == 0){
            cout << "\e[1;31m[ERROR]:\e[1;37m No existe una particion extendida para poder agregar su partición Lógica\e[m\n" << endl;
            return;
        }
    }

    //VALIDACION DE QUE NO EXISTA UNA PARTICION CON EL MISMO NOMBRE
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion->name){
            cout << "\e[1;31m[ERROR]:\e[1;37m Ya existe una particion con el mismo nombre\e[m\n" << endl;
            return;
        }else if(particiones[i].part_type == 'E'){
            //SI EXISTE UNA PARTICION EXTENDIDA SE DEBE DE BUSCAR EN SU EBR
            int temp = particiones[i].part_start;
            vector<EBR> ebrs = ListadoEBR(particiones[i],particion->path);
            if(ebrs.size() > 0){
                for(int j = 0; j < ebrs.size(); j++){
                    if(ebrs[j].part_name == particion->name){
                        cout << "\e[1;31m[ERROR]:\e[1;37m Ya existe una particion con el mismo nombre\e[m\n" << endl;
                        return;
                    }
                }
            }
        }
    }

    //VALIDACION QUE LA PARTICION A CREAR NO SEA DE MAYOR TAMAÑO QUE EL DISCO
    if(particion->size > mbr.mbr_tamano){
        cout << "\e[1;31m[ERROR]:\e[1;37m El tamaño de la particion es mayor al tamaño del disco\e[m\n" << endl;
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

//METODO PARA PODER APLICAR EL PRIMER AJUSTE DE PRIMARIAS Y EXTENDIDAS
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
                    cout << "\e[1;31m[ERROR]:\e[1;37m No hay espacio suficiente para crear la particion\e[m\n" << endl;
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se pudo crear la partición\e[m\n" << endl;
    }
}

//METODO PARA PODER APLICAR EL MEJOR AJUSTE DE PRIMARIAS Y EXTENDIDAS
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
                    cout << "\e[1;31m[ERROR]:\e[1;37m No hay espacio suficiente para crear la particion\e[m\n" << endl;
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se pudo crear la partición ya que no hay espacio" << endl;
        return;
    }else{
        particiones[no_particion].part_s = particion->size;
        particiones[no_particion].part_type = particion->type[0];
        particiones[no_particion].part_fit = particion->fit[0];
        strcpy(particiones[no_particion].part_name , particion->name.c_str());
        ActualizarDisco(particiones, mbr, particion->path);
    }

}

//METODO PARA PODER APLICAR EL PEOR AJUSTE DE PRIMARIAS Y EXTENDIDAS
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
                    cout << "\e[1;31m[ERROR]:\e[1;37m No hay espacio suficiente para crear la particion\e[m\n" << endl;
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se pudo crear la partición ya que no hay espacio" << endl;
        return;
    }else{
        particiones[no_particion].part_s = particion->size;
        particiones[no_particion].part_type = particion->type[0];
        particiones[no_particion].part_fit = particion->fit[0];
        strcpy(particiones[no_particion].part_name , particion->name.c_str());
        ActualizarDisco(particiones, mbr, particion->path);
    }

}

//METODO PARA REGISTRAR LOS CAMBIOS HECHOS EN LAS PARTICIONES EN EL DISCO
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
    cout << "\e[1;32m [SUCCESS]: \e[1;37m La Particion fue creada exitosamente\e[m\n" << endl;
    return;
}

//METODO PARA ELIMINAR UNA PARTICION
void Fdisk::EliminarParticion(Fdisk *particion){
    string respuesta = "";
    do{
        cout << "¿Quiere eliminar la particion? [S/N]" << endl;
        cin >> respuesta;
        if(respuesta == "N" || respuesta == "n"){
            cout << "\e[1;33m[WARNING]:\e[1;37m No se elimino la particion\e[m\n" << endl;
            return;
        }else if(respuesta == "S" || respuesta == "s"){
            break;
        }else{
            cout << "\e[1;31m[ERROR]:\e[1;37m Opcion no valida\e[m\n" << endl;
        }
    }while(respuesta != "S" && respuesta != "s" && respuesta != "N" && respuesta != "n");

    vector<Particion> particiones;
    //OBTIENE LA INFORMACION DEL MBR
    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    MBR mbr;
    fseek(archivo,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,archivo);
    fclose(archivo);

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
                cout << "\e[1;31m[ERROR]:\e[1;37m El nombre ingresado no coincide con las particiones que se encuentran dentro del disco\e[m\n" << endl;
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

                cout << "\e[1;32m [SUCCESS]: \e[1;37m La Particion fue eliminada correctamente \e[m\n" << endl;
            }
        }
    }else{
        cout << "\e[1;31m[ERROR]:\e[1;37m La particion no existe\e[m\n" << endl;
        return;
    }
}

//METODO PARA CAMBIAR EL TAMAÑO DE LAS PARTICIONES
void Fdisk::Cambiar_Tamanio_Particion(Fdisk *particion){
    vector<Particion> particiones;
    //OBTIENE LA INFORMACION DEL MBR
    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    MBR mbr;
    fseek(archivo,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,archivo);
    fclose(archivo);

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
            vector<EBR> ebrs = ListadoEBR(particiones[i],particion->path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion->name){
                    encontrado = true;
                    logica = true;
                    break;
                }
            }

        }
    }

    int extra = particion->add;
    if(particion->unit == "K"){
        extra = extra * 1024;
    }else if(particion->unit == "M"){
        extra = extra * 1024 * 1024;
    }

    if(!encontrado){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro la particion con el nombre: " << particion->name << "\e[m\n" << endl;
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
                            if(nuevo_tamanio > 0 && (nuevo_tamanio+particiones[i].part_start) < particiones[i+1].part_start && particiones[i+1].part_start != -1){
                                particiones[i].part_s = nuevo_tamanio;
                                error = false;
                                break;
                            }else if(nuevo_tamanio > 0 && particiones[i+1].part_start == -1 && (particiones[i].part_start + nuevo_tamanio) < mbr.mbr_tamano){
                                particiones[i].part_s = nuevo_tamanio;
                                error = false;
                                break;
                            }else{
                                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso \e[m\n" << endl;
                                return;
                            }
                        }else{
                            int nuevo_tamanio = particiones[i].part_s + extra;
                            if(nuevo_tamanio > 0 && (particiones[i].part_start + nuevo_tamanio) < mbr.mbr_tamano){
                                particiones[i].part_s = nuevo_tamanio;
                                error = false;
                                break;
                            }else{
                                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso \e[m\n" << endl;
                                return;
                            }
                        }
                    }else{
                        int nuevo_tamanio = particiones[i].part_s + extra;
                        if(nuevo_tamanio > 0 && (particiones[i].part_start + nuevo_tamanio) < mbr.mbr_tamano){
                            particiones[i].part_s = nuevo_tamanio;
                            error = false;
                            break;
                        }else{
                            cout << "\e[1;31m[ERROR]:\e[1;37m No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso \e[m\n" << endl;
                            return;
                        }
                    }
                }
            }
        }

        if(error){
            cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro la particion con el nombre: " << particion->name << "\e[m\n" << endl;
            return;
        }
    }else{
        //BUSCO LA PARTICION A LA CUAL VOY A AGREGAR O QUITAR EL ESPACIO
        bool error = true;
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_type == 'E'){
                //OBTIENE LA INFORMACION DEL EBR
                vector<EBR> ebrs = ListadoEBR(particiones[i],particion->path);
                for(int j = 0; j < ebrs.size(); j++){
                    if(ebrs[j].part_name == particion->name){
                        if(j != ebrs.size()){
                            int nuevo_tamanio = ebrs[j].part_s + extra;
                            if(nuevo_tamanio > 0 && (nuevo_tamanio+ebrs[j].part_start) < ebrs[j].part_next){
                                ebrs[j].part_s = nuevo_tamanio;
                                error = false;
                                break;
                            }else{
                                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso \e[m\n" << endl;
                                return;
                            }
                        }else{
                            int nuevo_tamanio = ebrs[j].part_s + extra;
                            if(nuevo_tamanio > 0 && (ebrs[j].part_start + nuevo_tamanio) < particiones[i].part_s){
                                ebrs[j].part_s = nuevo_tamanio;
                                error = false;
                                break;
                            }else{
                                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede realizar la operacion ADD, el tamaño de la particion no es la adecuada para realizar este proceso \e[m\n" << endl;
                                return;
                            }
                        }
                    }
                }
            }
        }

        if(error){
            cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro la particion con el nombre: " << particion->name << " \e[m\n" << endl;
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

    cout << "\e[1;32m [SUCCESS]: \e[1;37m La Particion fue modificada exitosamente \e[m\n" << endl;
    
}

//METODO PARA AGREGAR UNA PARTICION LOGICA
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro la particion extendida en el disco \e[m\n" << endl;
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se puede crear la particion logica, el tamaño de la particion a crear es mayor al tamaño de la particion extendida \e[m\n" << endl;
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
        AgregarEBR(ebr,particion->path);
    }else{
        //CREO EL NUEVO EBR
        EBR ebr;
        ebr.part_status = '0';
        ebr.part_fit = particion->fit[0];
        if(particiones[particion_id].part_fit == 'f' || particiones[particion_id].part_fit == 'F'){
            ebr.part_fit = 'F';
            if(FirstFit_Logicas(logicas,particion->size,final) != -1){
                ebr.part_start = FirstFit_Logicas(logicas,particion->size, final);
            }else{
                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede crear la particion logica, no hay espacio suficiente \e[m\n" << endl;
                return;
            }
        }else if(particiones[particion_id].part_fit == 'b' || particiones[particion_id].part_fit == 'B'){
            ebr.part_fit = 'B';
            if(BestFit_Logicas(logicas,particion->size, final) != -1){
                ebr.part_start = BestFit_Logicas(logicas,particion->size, final);
            }else{
                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede crear la particion logica, no hay espacio suficiente \e[m\n" << endl;
                return;
            }
        }else if(particiones[particion_id].part_fit == 'w' || particiones[particion_id].part_fit == 'W'){
            ebr.part_fit = 'W';
            if(WorstFit_Logicas(logicas,particion->size, final) != -1){
                ebr.part_start = WorstFit_Logicas(logicas,particion->size, final);
            }else{
                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede crear la particion logica, no hay espacio suficiente \e[m\n" << endl;
                return;
            }
        }
        ebr.part_s = particion->size;
        for(int i = 0; i < logicas.size(); i++){
            if(logicas[i].part_next == -1){
                ebr.part_next = -1;
                logicas[i].part_next = ebr.part_start;
                ActualizarEBR(logicas[i],particion->path);
                break;
            }else if(logicas[i].part_next != -1){
                if(logicas[i].part_start == ebr.part_start){
                    ebr.part_next = logicas[i].part_next;
                    logicas[i].part_next = ebr.part_start;
                    break;
                }
            }
        }

        strcpy(ebr.part_name,particion->name.c_str());
        AgregarEBR(ebr,particion->path);

    }
}

//FUNCION PARA ENLISTAR LOS EBRS DE UNA PARTICION EXTENDIDA
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

//FUNCION PARA RETORNAR EL ULTIMO EBR DE LA LISTA
EBR Fdisk::retornarUlitmoEBR(vector<EBR> ebrs){
    EBR ebr;
    for(int i = 0; i < ebrs.size(); i++){
        if(ebrs[i].part_next == -1){
            ebr = ebrs[i];
        }
    }
    return ebr;
}

//METODO PARA ACTUALIZAR LOS CAMBIOS HECHOS EN EL EBR
void Fdisk::ActualizarEBR(EBR ebr, string path){
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    if(archivo == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se pudo abrir el archivo \e[m\n" << endl;
        return;
    }
    fseek(archivo,ebr.part_start,SEEK_SET);
    fwrite(&ebr,sizeof(EBR),1,archivo);
    fclose(archivo);
}

//METODO PARA AGREGAR UN NUEVO EBR
void Fdisk::AgregarEBR(EBR ebr, string path){
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    if(archivo == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se pudo abrir el archivo \e[m\n" << endl;
        return;
    }
    fseek(archivo,ebr.part_start,SEEK_SET);
    fwrite(&ebr,sizeof(EBR),1,archivo);
    fclose(archivo);
    cout << "\e[1;32m [SUCCESS]: \e[1;37m Se creo la particion logica correctamente \e[m\n" << endl;
}

//METODO PARA ELIMINAR UNA PARTICION LOGICA
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro la particion extendida en el disco\e[m\n" << endl;
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
        cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro ninguna particion logica en la particion extendida \e[m\n" << endl;
        return;
    }

    //BUSCO LA PARTICION LOGICA A ELIMINAR
    bool error2 = true;
    int particion_id2 = 0;
    for(int i = 0; i < logicas.size(); i++){
        if(logicas[i].part_name == particion->name){
            error2 = false;
            particion_id2 = i;
            break;
        }
    }

    if(error2){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro la particion logica que se quiere eliminar \e[m\n" << endl;
        return;
    }

    //ELIMINO LA PARTICION LOGICA
    logicas[particion_id2].part_status = '0';
    logicas[particion_id2].part_fit = '\0';
    for(int i = 0; i < 16; i++){
        logicas[particion_id2].part_name[i] = '\0';
    }


    ActualizarEBR(logicas[particion_id2],particion->path);

    //LLENO DE CEROS LA PARTICION LOGICA
    FILE *archivo;
    archivo = fopen(particion->path.c_str(),"rb+");
    if(archivo == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se pudo abrir el archivo \e[m\n" << endl;
        return;
    }
    fseek(archivo,logicas[particion_id2].part_start+ sizeof(EBR),SEEK_SET);
    for(int i = 0; i < (logicas[particion_id2].part_s-sizeof(EBR)); i++){
        char cero = '\0';
        fwrite(&cero,1,1,archivo);
    }
    fclose(archivo);

    cout << "\e[1;32m [SUCCESS]: \e[1;37m La particion Lógica ha sido eliminada correctamente \e[m\n" << endl;

}

//FUNCION PARA RETORNAR LA POSICION DE LA PARTICION EN UN FIT DE PRIMER AJUSTE
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
            }else if(ebrs[i].part_next == -1){
                if((final_pe-(ebrs[i].part_start+ebrs[i].part_s)) >= tamanio){
                    inicio = ebrs[i].part_start+ebrs[i].part_s;
                    return inicio;
                }
            }
        }
        inicio = ebrs[i].part_next;
    }
    return inicio;
}

//FUNCION PARA RETORNAR LA POSICION DE LA PARTICION EN UN FIT DE MEJOR AJUSTE
int Fdisk:: BestFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe){
    int mejor_ajuste = 999999999;
    int mejor_inicio = -1;
    for(int i = 0; i < ebrs.size(); i++){
        if(i != ebrs.size()-1){
            if(cadenaVacia(ebrs[i].part_name)){
                if(ebrs[i].part_s >= tamanio){
                    if(ebrs[i].part_s < mejor_ajuste){
                        mejor_ajuste = ebrs[i].part_s;
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
            }else if(ebrs[i].part_next == -1){
                if((final_pe-(ebrs[i].part_start + ebrs[i].part_s)) < mejor_ajuste){
                    mejor_ajuste = final_pe-(ebrs[i].part_start + ebrs[i].part_s);
                    mejor_inicio = ebrs[i].part_start + ebrs[i].part_s;
                }
            }
        }
    }
    return mejor_inicio;
}

//FUNCION PARA RETORNAR LA POSICION DE LA PARTICION EN UN FIT DE PEOR AJUSTE
int Fdisk:: WorstFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe){
    int peor_ajuste = 0;
    int peor_inicio = -1;
    for(int i = 0; i < ebrs.size(); i++){
        cout << ebrs[i].part_s << endl;
        cout << ebrs[i].part_start << endl;
        cout << i << endl;
        cout << ebrs.size() << endl;
        if(i != ebrs.size()-1){
            cout << "entro0" << endl;
            if(cadenaVacia(ebrs[i].part_name)){
                cout << "entro1" << endl;
                if(ebrs[i].part_s >= tamanio){
                    cout << "entro2" << endl;
                    if((ebrs[i].part_s) > peor_ajuste){
                        cout << "entro3" << endl;
                        peor_ajuste = ebrs[i].part_s;
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
                        break;
                    }
                }
            }else if(ebrs[i].part_next == -1){
                if((final_pe - (ebrs[i].part_start + ebrs[i].part_s)) > peor_ajuste){
                    peor_ajuste = final_pe - (ebrs[i].part_start + ebrs[i].part_s);
                    peor_inicio = ebrs[i].part_start + ebrs[i].part_s;
                    break;
                }
            }
        }
    }
    cout << "peor_inicio: " << peor_inicio << endl;
    return peor_inicio;
}
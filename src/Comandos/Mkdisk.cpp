#include "Mkdisk.h"

Mkdisk::Mkdisk() {
}

vector<string> Mkdisk::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Mkdisk::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

void Mkdisk::CrearDisco(Mkdisk *disco_nuevo){

    bool ruta_complex = false;
    //VALIDACION DEL SIZE
    if (disco_nuevo->size <= 0){
        cout << "No se ha ingresado un tamaño válido para el disco" << endl;
        return;
    }

    //VALIDACION DEL PATH
    if (disco_nuevo->path == ""){
        cout << "No se ha ingresado la ruta para crear el disco" << endl;
        return;
    }

    //MIRA SI INGRESA EL TIPO DE FIT EN EL DISCO
    if (disco_nuevo->fit == ""){
        disco_nuevo->fit = "ff";
    }

    //VALIDACION DEL FIT
    if(toLowerCase(disco_nuevo->fit) != "bf" && toLowerCase(disco_nuevo->fit) != "ff" && toLowerCase(disco_nuevo->fit) != "wf"){
        cout << "No se ha ingresado un fit válido para el disco" << endl;
        return;
    }

    //MIRA SI INGRESA EL TIPO DE UNIT EN EL DISCO
    if(disco_nuevo->unit == ""){
        disco_nuevo->unit = "m";
    }

    //VALIDACION DE LA UNIDAD
    if(toLowerCase(disco_nuevo->unit) != "m" && toLowerCase(disco_nuevo->unit) != "k"){
        cout << "No se ha ingresado una unidad válida para el disco" << endl;
        return;
    }

    //DEFINICION DEL TAMAÑO
    if(toLowerCase(disco_nuevo->unit) == "k"){
        disco_nuevo->size = disco_nuevo->size * 1024;
    }else{
        disco_nuevo->size = disco_nuevo->size * 1024 * 1024;
    }

    //CREACION DEL DISCO
    //VALIDACION Y CREACION DE CARPETAS 
    if(disco_nuevo->path[0] == '"' && disco_nuevo->path[disco_nuevo->path.length()-1] == '"'){
        ruta_complex = true;
        disco_nuevo->path = disco_nuevo->path.substr(1,disco_nuevo->path.length()-2);
    }


    string path_temp =  disco_nuevo->path;
    vector<string> carpetas = split(disco_nuevo->path,'/');
    //VERIFICA SI EXISTE EL ARCHIVO
    FILE *archivo;
    if((archivo = fopen(disco_nuevo->path.c_str(),"rb"))){
        cout << "El disco con el nombre " << carpetas[carpetas.size()-1] << " ya existe" << endl;
        fclose(archivo);
        return;
    }
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas.size()-1; ++i){
        if(carpetas[i]!= ""){
            ruta += carpetas[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());
    cout << "Creando el disco en " << ruta<< " ..." << endl;
    sleep(1);
    
    //CREACION DEL ARCHIVO
    FILE *disco;
    disco = fopen(disco_nuevo->path.c_str(),"wb");

    //CREACION DEL MBR
    MBR mbr;
    mbr.mbr_tamano = disco_nuevo->size;
    time_t fecha_hoy;
    mbr.mbr_fecha_creacion = time(&fecha_hoy);
    mbr.mbr_dsk_signature = rand();
    mbr.disk_fit = toupper(disco_nuevo->fit[0]);
    //INICIALIZO LAS PARTICIONES
    mbr.mbr_particion_1.part_status = '0';
    mbr.mbr_particion_1.part_start = -1;
    mbr.mbr_particion_1.part_s = 0;
    for(int i = 0; i < 16; ++i){
        mbr.mbr_particion_1.part_name[i] = '\0';
    }
    mbr.mbr_particion_1.part_type = '\0';
    mbr.mbr_particion_1.part_fit = '\0';   
    mbr.mbr_particion_2.part_status = '0';
    mbr.mbr_particion_2.part_start = -1;
    mbr.mbr_particion_2.part_s = 0;
    for(int i = 0; i < 16; ++i){
        mbr.mbr_particion_2.part_name[i] = '\0';
    }
    mbr.mbr_particion_2.part_type = '\0';
    mbr.mbr_particion_2.part_fit = '\0';
    mbr.mbr_particion_3.part_status = '0';
    mbr.mbr_particion_3.part_start = -1;
    mbr.mbr_particion_3.part_s = 0;
    for(int i = 0; i < 16; ++i){
        mbr.mbr_particion_3.part_name[i] = '\0';
    }
    mbr.mbr_particion_3.part_type = '\0';
    mbr.mbr_particion_3.part_fit = '\0';
    mbr.mbr_particion_4.part_status = '0';
    mbr.mbr_particion_4.part_start = -1;
    mbr.mbr_particion_4.part_s = 0;
    for(int i = 0; i < 16; ++i){
        mbr.mbr_particion_4.part_name[i] = '\0';
    }
    mbr.mbr_particion_4.part_type = '\0';
    mbr.mbr_particion_4.part_fit = '\0';
    fwrite(&mbr,sizeof(MBR),1,disco);
    for(int i = 0; i < disco_nuevo->size - sizeof(MBR); ++i){
        char cero = '\0';
        fwrite(&cero,1,1,disco);
    }
    fclose(disco);

    //MUESTRO TEMPORALMENTE EL MBR
    cout << "================MBR==================" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha: " << mbr.mbr_fecha_creacion << endl;
    cout << "Firma: " << mbr.mbr_dsk_signature << endl;
    cout << "\t- Particion 1: "  << endl;
    string name = "";
    cout << "\t\t-Name: " << name.assign(mbr.mbr_particion_1.part_name,16) << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_1.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_1.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_1.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_1.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_1.part_fit << endl;
    cout << "\t- Particion 2: "  << endl;
    name = "";
    cout << "\t\t-Name: " << name.assign(mbr.mbr_particion_2.part_name,16) << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_2.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_2.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_2.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_2.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_2.part_fit << endl;
    cout << "\t- Particion 3: "  << endl;
    name = "";
    cout << "\t\t-Name: " << name.assign(mbr.mbr_particion_3.part_name,16) << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_3.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_3.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_3.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_3.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_3.part_fit << endl;
    cout << "\t- Particion 4: "  << endl;
    name = "";
    cout << "\t\t-Name: " << name.assign(mbr.mbr_particion_4.part_name,16) << endl;
    cout << "\t\t-Status: " << mbr.mbr_particion_4.part_status << endl;
    cout << "\t\t-Type: " << mbr.mbr_particion_4.part_type << endl;
    cout << "\t\t-Start: " << mbr.mbr_particion_4.part_start << endl;
    cout << "\t\t-Size: " << mbr.mbr_particion_4.part_s << endl;
    cout << "\t\t-Fit: " << mbr.mbr_particion_4.part_fit << endl;
    cout << "=====================================" << endl;

    cout << "El disco con el nombre " << carpetas[carpetas.size()-1] << " ha sido creado exitosamente" << endl;
}
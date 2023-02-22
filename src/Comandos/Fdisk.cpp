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

void Fdisk::SistemaDeParticiones(Fdisk *particion){
    //VALIDAR ATRIBUTOS GENERALES OBLIGATORIOS

    if(particion->path == ""){
        cout << "No se ha ingresado la ruta para crear la partición" << endl;
        return;
    }

    if(particion->name == ""){
        cout << "No se ha ingresado el nombre para la partición" << endl;
        return;
    }

    if(particion->unit == ""){
        particion->unit = "k";
    }

    if(toLowerCase(particion->unit) != "m" && toLowerCase(particion->unit) != "k" && toLowerCase(particion->unit) != "b"){
        cout << "No se ha ingresado una unidad válida para la partición" << endl;
        return;
    }

    if(particion->type == ""){
        particion->type = "p";
    }

    if(toLowerCase(particion->type) != "p" && toLowerCase(particion->type) != "e" && toLowerCase(particion->type) != "l"){
        cout << "No se ha ingresado un tipo válido para la partición" << endl;
        return;
    }

    if(particion->fit == ""){
        particion->fit = "wf";
    }

    if(toLowerCase(particion->fit) != "bf" && toLowerCase(particion->fit) != "ff" && toLowerCase(particion->fit) != "wf"){
        cout << "No se ha ingresado un fit válido para la partición" << endl;
        return;
    }

    if(particion->dsk_delete != "" && toLowerCase(particion->dsk_delete) != "full"){
        cout << "No se ha ingresado un delete válido para la partición" << endl;
        return;
    }

    //TERMINANDO DE VALIDAR SE MANDA A LAS FUNCIONES
    if(particion->size != 0){
        AgregarParticion(particion);
    }else if(particion->dsk_delete != "" && particion->add == 0){
        EliminarParticion(particion);
    }else if(particion->add > 0 && particion->dsk_delete == ""){
        AumentarParticion(particion);
    }else if(particion->add < 0 && particion->dsk_delete == ""){
        ReducirParticion(particion);
    }else{
        cout << "No se ha ingresado un comando válido para la partición" << endl;
        return;
    }
       
}

void Fdisk::AgregarParticion(Fdisk *particion){
    //VALIDA EL SIZE
    if(particion->size <= 0){
        cout << "No se ha ingresado un tamaño válido para crear la partición" << endl;
        return;
    }

    //VALIDA SI EXISTE EL DISCO
    vector<string> carpetas = split(particion->path,'/');
    FILE *archivo;
    if(!(archivo = fopen(particion->path.c_str(),"rb"))){
        cout << "El disco no se encuentro en el sistema" << endl;
        fclose(archivo);
        return;
    }

    //ABRE EL ARCHIVO Y OBTIENE EL MBR
    FILE *disco;
    MBR *mbr = new MBR();
    disco = fopen(particion->path.c_str(),"rb+");
    if(disco == NULL){
        cout << "No se pudo abrir el disco" << endl;
        return;
    }
    fseek(disco,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,disco);
    fclose(disco);

    //VALIDA SI EXISTE UNA PARTICION CON EL MISMO NOMBRE
    if(mbr->mbr_particion_1.part_name == particion->name || mbr->mbr_particion_2.part_name == particion->name || mbr->mbr_particion_3.part_name == particion->name || mbr->mbr_particion_4.part_name == particion->name){
        cout << "Ya existe una partición con el mismo nombre" << endl;
        return;
    }

    //VALIDA SI EL TAMAÑO DE LA PARTICION ES MAYOR AL DEL DISCO
    if(particion->size > mbr->mbr_tamano){
        cout << "El tamaño de la partición es mayor al del disco" << endl;
        return;
    }

    //VALIDA SI EL DISCO TIENE ESPACIO DISPONIBLE
    int espacioDisponible = mbr->mbr_tamano - sizeof(MBR);
    espacioDisponible -= mbr->mbr_particion_1.part_s - mbr->mbr_particion_2.part_s - mbr->mbr_particion_3.part_s - mbr->mbr_particion_4.part_s;

    if(espacioDisponible < particion->size){
        cout << "No hay espacio disponible en el disco para crear la partición" << endl;
        return;
    }

    //VALIDAR LA CANTIDAD DE PARTICIONES SI CUMPLE QUE SEAN 4 PRIMARIAS O 3 PRIMARIAS Y 1 EXTENDIDA
    int cantidadPrimarias = 0;
    int cantidadExtendidas = 0;

    if(mbr->mbr_particion_1.part_type == 'p'){
        cantidadPrimarias++;
    }else if(mbr->mbr_particion_1.part_type == 'e'){
        cantidadExtendidas++;
    }

    if(mbr->mbr_particion_2.part_type == 'p'){
        cantidadPrimarias++;
    }else if(mbr->mbr_particion_2.part_type == 'e'){
        cantidadExtendidas++;
    }

    if(mbr->mbr_particion_3.part_type == 'p'){
        cantidadPrimarias++;
    }else if(mbr->mbr_particion_3.part_type == 'e'){
        cantidadExtendidas++;
    }

    if(mbr->mbr_particion_4.part_type == 'p'){
        cantidadPrimarias++;
    }else if(mbr->mbr_particion_4.part_type == 'e'){
        cantidadExtendidas++;
    }

    if(particion->type == "p"){
        if(cantidadPrimarias == 4){
            cout << "Ya no se pueden agregar mas particiones primarias" << endl;
            return;
        }
    }else if(particion->type == "e"){
        if(cantidadExtendidas == 1){
            cout << "Ya no se pueden agregar mas particiones extendidas" << endl;
            return;
        }
    }

    //VALIDA SI AL INGRESAR UNA NUEVA PARTICION LOGICA EXISTA UNA PARTICION EXTENDIDA
    if(particion->type == "l"){
        if(cantidadExtendidas == 0){
            cout << "No se puede crear una partición lógica ya que el disco no cuenta con una partición extendida" << endl;
            return;
        }
    }

    //VALIDA SI LA PARTICION LOGICA NO EXCEDE EL TAMAÑO DE LA EXTENDIDA
    if(particion->type == "l"){
        int espacioExtendida = 0;
        if(mbr->mbr_particion_1.part_type == 'e'){
            espacioExtendida = mbr->mbr_particion_1.part_s;
        }else if(mbr->mbr_particion_2.part_type == 'e'){
            espacioExtendida = mbr->mbr_particion_2.part_s;
        }else if(mbr->mbr_particion_3.part_type == 'e'){
            espacioExtendida = mbr->mbr_particion_3.part_s;
        }else if(mbr->mbr_particion_4.part_type == 'e'){
            espacioExtendida = mbr->mbr_particion_4.part_s;
        }

        if(particion->size > espacioExtendida){
            cout << "El tamaño de la partición lógica es mayor al de la partición extendida" << endl;
            return;
        }
    }

    //VALIDA SI LA PARTICION LOGICA NO EXCEDE EL TAMAÑO DE LA EXTENDIDA Y SI EXISTE UNA PARTICION LOGICA ANTERIOR
     /*PENDIENTE*/

    //CREA LA PARTICION
    if(particion->type == "p"){
        AgregarParticionPrimaria(particion, mbr);
    }else if(particion->type == "e"){
        AgregarParticionExtendida(particion, mbr);
    }else if(particion->type == "l"){
        AgregarParticionLogica(particion, mbr);
    }

}

void Fdisk::AgregarParticionPrimaria(Fdisk *particion, MBR *mbr_dsk){
    //VALIDA SI EXISTE UNA PARTICION EN EL MBR Y CREA LA PARTICION PRIMARIA
    if(mbr_dsk->mbr_particion_1.part_status == '0'){
        mbr_dsk->mbr_particion_1.part_status = '1';
        mbr_dsk->mbr_particion_1.part_type = 'p';
        mbr_dsk->mbr_particion_1.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_1.part_start = sizeof(MBR);
        mbr_dsk->mbr_particion_1.part_s = particion->size;
        mbr_dsk->mbr_particion_1.part_name,particion->name.c_str();
    }else if(mbr_dsk->mbr_particion_2.part_status == '0'){
        mbr_dsk->mbr_particion_2.part_status = '1';
        mbr_dsk->mbr_particion_2.part_type = 'p';
        mbr_dsk->mbr_particion_2.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_2.part_start = mbr_dsk->mbr_particion_1.part_start + mbr_dsk->mbr_particion_1.part_s;
        mbr_dsk->mbr_particion_2.part_s = particion->size;
        mbr_dsk->mbr_particion_2.part_name,particion->name.c_str();
    }else if(mbr_dsk->mbr_particion_3.part_status == '0'){
        mbr_dsk->mbr_particion_3.part_status = '1';
        mbr_dsk->mbr_particion_3.part_type = 'p';
        mbr_dsk->mbr_particion_3.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_3.part_start = mbr_dsk->mbr_particion_2.part_start + mbr_dsk->mbr_particion_2.part_s;
        mbr_dsk->mbr_particion_3.part_s = particion->size;
        mbr_dsk->mbr_particion_3.part_name,particion->name.c_str();
    }else if(mbr_dsk->mbr_particion_4.part_status == '0'){
        mbr_dsk->mbr_particion_4.part_status = '1';
        mbr_dsk->mbr_particion_4.part_type = 'p';
        mbr_dsk->mbr_particion_4.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_4.part_start = mbr_dsk->mbr_particion_3.part_start + mbr_dsk->mbr_particion_3.part_s;
        mbr_dsk->mbr_particion_4.part_s = particion->size;
        mbr_dsk->mbr_particion_4.part_name,particion->name.c_str();
    }else{
        cout << "No se pudo crear la partición primaria, ya que no hay espacio disponible" << endl;
        return;
    }

    //ESCRIBE EL MBR EN EL DISCO
    FILE *disco;
    disco = fopen(particion->path.c_str(),"rb+");
    if(disco == NULL){
        cout << "No se pudo abrir el disco" << endl;
        return;
    }
    fseek(disco,0,SEEK_SET);
    fwrite(mbr_dsk,sizeof(MBR),1,disco);
    for(int i = 0; i < mbr_dsk->mbr_tamano - sizeof(MBR); ++i){
        char cero = '\0';
        fwrite(&cero,1,1,disco);
    }
    fclose(disco);

    cout << "Se creo la partición primaria exitosamente" << endl;
}

void Fdisk::AgregarParticionExtendida(Fdisk *particion, MBR *mbr_dsk){
    //VALIDA SI EXISTE UNA PARTICION EN EL MBR Y CREA LA PARTICION EXTENDIDA
    if(mbr_dsk->mbr_particion_1.part_status == '0'){
        mbr_dsk->mbr_particion_1.part_status = '1';
        mbr_dsk->mbr_particion_1.part_type = 'e';
        mbr_dsk->mbr_particion_1.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_1.part_start = sizeof(MBR);
        mbr_dsk->mbr_particion_1.part_s = particion->size;
        mbr_dsk->mbr_particion_1.part_name,particion->name.c_str();
    }else if(mbr_dsk->mbr_particion_2.part_status == '0'){
        mbr_dsk->mbr_particion_2.part_status = '1';
        mbr_dsk->mbr_particion_2.part_type = 'e';
        mbr_dsk->mbr_particion_2.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_2.part_start = mbr_dsk->mbr_particion_1.part_start + mbr_dsk->mbr_particion_1.part_s;
        mbr_dsk->mbr_particion_2.part_s = particion->size;
        mbr_dsk->mbr_particion_2.part_name,particion->name.c_str();
    }else if(mbr_dsk->mbr_particion_3.part_status == '0'){
        mbr_dsk->mbr_particion_3.part_status = '1';
        mbr_dsk->mbr_particion_3.part_type = 'e';
        mbr_dsk->mbr_particion_3.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_3.part_start = mbr_dsk->mbr_particion_2.part_start + mbr_dsk->mbr_particion_2.part_s;
        mbr_dsk->mbr_particion_3.part_s = particion->size;
        mbr_dsk->mbr_particion_3.part_name,particion->name.c_str();
    }else if(mbr_dsk->mbr_particion_4.part_status == '0'){
        mbr_dsk->mbr_particion_4.part_status = '1';
        mbr_dsk->mbr_particion_4.part_type = 'e';
        mbr_dsk->mbr_particion_4.part_fit = particion->fit[0];
        mbr_dsk->mbr_particion_4.part_start = mbr_dsk->mbr_particion_3.part_start + mbr_dsk->mbr_particion_3.part_s;
        mbr_dsk->mbr_particion_4.part_s = particion->size;
        mbr_dsk->mbr_particion_4.part_name,particion->name.c_str();
    }else{
        cout << "No se pudo crear la partición extendida, ya que no hay espacio disponible" << endl;
        return;
    }
    
    //ESCRIBE EL MBR EN EL DISCO
    FILE *disco;
    disco = fopen(particion->path.c_str(),"rb+");
    if(disco == NULL){
        cout << "No se pudo abrir el disco" << endl;
        return;
    }
    fseek(disco,0,SEEK_SET);
    fwrite(mbr_dsk,sizeof(MBR),1,disco);
    for(int i = 0; i < mbr_dsk->mbr_tamano - sizeof(MBR); ++i){
        char cero = '\0';
        fwrite(&cero,1,1,disco);
    }
    fclose(disco);
}

void Fdisk::AgregarParticionLogica(Fdisk *particion, MBR *mbr_dsk){

}


void Fdisk::EliminarParticion(Fdisk *particion){
    //VALIDA SI EXISTE EL DISCO
    vector<string> carpetas = split(particion->path,'/');
    FILE *archivo;
    if(!(archivo = fopen(particion->path.c_str(),"rb"))){
        cout << "El disco no se encuentro en el sistema" << endl;
        fclose(archivo);
        return;
    }

    //ABRE EL ARCHIVO Y OBTIENE EL MBR
    FILE *disco;
    MBR *mbr = new MBR();
    disco = fopen(particion->path.c_str(),"rb+");
    if(disco == NULL){
        cout << "No se pudo abrir el disco" << endl;
        return;
    }
    fseek(disco,0,SEEK_SET);
    fread(&mbr,sizeof(MBR),1,disco);
    fclose(disco);

    //VALIDA SI EXISTE UNA PARTICION CON EL MISMO NOMBRE

    if(mbr->mbr_particion_1.part_name == particion->name){
        mbr->mbr_particion_1.part_status = '0';
        mbr->mbr_particion_1.part_type = '0';
        mbr->mbr_particion_1.part_fit = '0';
        mbr->mbr_particion_1.part_start = -1;
        mbr->mbr_particion_1.part_s = 0;
        for(int i = 0; i < 16; i++){
            mbr->mbr_particion_1.part_name[i] = '\0';
        }
    }else if(mbr->mbr_particion_2.part_name == particion->name){
        mbr->mbr_particion_2.part_status = '0';
        mbr->mbr_particion_2.part_type = '0';
        mbr->mbr_particion_2.part_fit = '0';
        mbr->mbr_particion_2.part_start = -1;
        mbr->mbr_particion_2.part_s = 0;
        for(int i = 0; i < 16; i++){
            mbr->mbr_particion_2.part_name[i] = '\0';
        }
    }else if(mbr->mbr_particion_3.part_name == particion->name){
        mbr->mbr_particion_3.part_status = '0';
        mbr->mbr_particion_3.part_type = '0';
        mbr->mbr_particion_3.part_fit = '0';
        mbr->mbr_particion_3.part_start = -1;
        mbr->mbr_particion_3.part_s = 0;
        for(int i = 0; i < 16; i++){
            mbr->mbr_particion_3.part_name[i] = '\0';
        }
    }else if(mbr->mbr_particion_4.part_name == particion->name){
        mbr->mbr_particion_4.part_status = '0';
        mbr->mbr_particion_4.part_type = '0';
        mbr->mbr_particion_4.part_fit = '0';
        mbr->mbr_particion_4.part_start = -1;
        mbr->mbr_particion_4.part_s = 0;
        for(int i = 0; i < 16; i++){
            mbr->mbr_particion_4.part_name[i] = '\0';
        }
    }else{
        cout << "No se encontro la particion" << endl;
        return;
    }
}

void Fdisk::AumentarParticion(Fdisk *particion){
    
}

void Fdisk::ReducirParticion(Fdisk *disco){
    
}

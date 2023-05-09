#include "Rmgrp.h"

Rmgrp::Rmgrp(){
}

void Rmgrp::EliminarGrupo(Rmgrp *rmgrp){
    string name = rmgrp->name;
    if(name == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No ha agregado el nombre del grupo \e[m\n" << endl;
        return;
    }

    if(!logueado){
        cout << "\e[1;31m[ERROR]:\e[1;37m No ha iniciado sesion \e[m\n" << endl;
        return;
    }

    if(userlogueado != "root"){
        cout << "\e[1;31m[ERROR]:\e[1;37m NO se cuenta con los permisos necesarios para poder eliminar grupos \e[m\n" << endl;
        return;
    }

    if(name[0]== '\"' && name[name.size()-1] == '\"'){
        name = name.substr(1, name.size()-2);
    }

    if(name.size() > 10){
        cout << "\e[1;31m[ERROR]:\e[1;37m El nombre del grupo es muy largo \e[m\n" << endl;
        return;
    }

    if(!ExisteGrupo(name)){
        cout << "\e[1;31m[ERROR]:\e[1;37m El nombre del grupo no existe \e[m\n" << endl;
        return;
    }

    DeleteGrupo(name);

}

vector<EBR> Rmgrp::ListadoEBRS(Particion extendida, string path){
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

bool Rmgrp::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

vector<string> Rmgrp::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Rmgrp::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

void Rmgrp::DeleteGrupo(string name){
    //OBTIENE LA PARTICION
    if(lista_particiones_montadas.ExisteParticion(idlogueado) == false){
        cout << "\e[1;31m[ERROR]:\e[1;37m No existe la particion con el id: " << idlogueado << "\e[m\n" << endl;
        return;
    }
    Nodo particion = lista_particiones_montadas.obtenerNodoParticion(idlogueado);

    //OBTIENE EL MBR
    FILE *archivo;
    archivo = fopen(particion.path.c_str(), "rb+");
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};


    //VERIFICA SI LA PARTICION A FORMATEAR ES EXTENDIDA Y SI ES LA QUE SE QUIERE FORMATEAR O SINO QUE VERIFIQUE SI ES UNA PARTICION LOGICA
    vector<EBR> ebrs;
    EBR particion_logica;
    bool logica_existe = false;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'e' || particiones[i].part_type == 'E'){
            if(particiones[i].part_name == particion.name){
                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede formatear una particion extendida \e[m\n" << endl;
                return;
            }else{
                ebrs = ListadoEBRS(particiones[i], particion.path);
                for(int j = 0; j < ebrs.size(); j++){
                    if(ebrs[j].part_name == particion.name){
                        particion_logica = ebrs[j];
                        logica_existe = true;
                        break;
                    }
                }
            }
        }
    }

    int pos_inicio;
    int pos_fin;
    if(logica_existe){
        pos_inicio = particion_logica.part_start + sizeof(EBR);
        pos_fin = particion_logica.part_start + particion_logica.part_s;
    }else{
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_name == particion.name){
                pos_inicio = particiones[i].part_start;
                pos_fin = particiones[i].part_start + particiones[i].part_s;
                break;
            }
        }
    }

    //OBTIENE EL SUPERBLOQUE
    SuperBloque super_bloque;
    fseek(archivo, pos_inicio, SEEK_SET);
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo);

    //OBTIENE LA POSICION DEL INODO
    int pos_inodo = super_bloque.s_inode_start + sizeof(Inodo);
    Inodo inodo;
    fseek(archivo, pos_inodo, SEEK_SET);
    fread(&inodo, sizeof(Inodo), 1, archivo);

    //OBTIENE LA POSICION DEL BLOQUE
    string usuariostxt = "";
    //APUNTADORES DIRECTOS
    for(int i = 0; i < 12; i++){
        int no_bloque = inodo.i_block[i];
        if(no_bloque == -1){
            break;
        }
        BloqueArchivo bloque;
        fseek(archivo, no_bloque, SEEK_SET);
        fread(&bloque, sizeof(BloqueArchivo), 1, archivo);
        usuariostxt += bloque.b_content;
    }
    
    
    
    //OBTIENE TODOS LOS GRUPOS
    string nuevo_txt = "";
    bool encontrado = false;
    vector<string> usuarios_grupos;
    usuarios_grupos = split(usuariostxt, '\n');
    for(int i = 0; i < usuarios_grupos.size(); i++){
        vector<string> datos;
        datos = split(usuarios_grupos[i], ',');
        if(datos[1] == "G"){
            if(datos[2] == name){
                nuevo_txt += "0," + datos[1] + "," + datos[2] + "\n";
                encontrado = true;
            }else{
                nuevo_txt += datos[0] + "," + datos[1] + "," + datos[2] + "\n";
            }
        }else if(datos[1] == "U"){
            nuevo_txt += datos[0] + "," + datos[1] + "," +datos[2] + "," + datos[3] + "," + datos[4] + "\n";
        }
    }
    if(encontrado == false){
        cout << "\e[1;31m[ERROR]:\e[1;37m No existe el grupo: " << name << "\e[m\n" << endl;
        return;
    }
    string insercion = nuevo_txt;
    for(int i = 0; i < 12; i++){
        int no_bloque = inodo.i_block[i];
        if(no_bloque == -1){
            break;
        }
        if(insercion.size() > 63){
            BloqueArchivo bloque;
            string aux = insercion.substr(0, 63);
            strcpy(bloque.b_content, aux.c_str());
            fseek(archivo, no_bloque, SEEK_SET);
            fwrite(&bloque, sizeof(BloqueArchivo), 1, archivo);
            cout << insercion << endl;
            insercion = insercion.substr(63, insercion.size());
        }else if(insercion.size() <= 63 && insercion.size() > 0){
            BloqueArchivo bloque;
            cout << insercion << endl;
            strcpy(bloque.b_content, insercion.c_str());
            fseek(archivo, no_bloque, SEEK_SET);
            fwrite(&bloque, sizeof(BloqueArchivo), 1, archivo);
        }
    }

    fclose(archivo);

    cout << "\e[1;32m [SUCCESS]: \e[1;37m Se ha eliminado el grupo exitosamente \e[m\n" << endl;

}

bool Rmgrp::ExisteGrupo(string name){
    //OBTIENE LA PARTICION
    Nodo particion = lista_particiones_montadas.obtenerNodoParticion(idlogueado);

    //OBTIENE EL MBR
    FILE *archivo;
    archivo = fopen(particion.path.c_str(), "rb+");
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};


    //VERIFICA SI LA PARTICION A FORMATEAR ES EXTENDIDA Y SI ES LA QUE SE QUIERE FORMATEAR O SINO QUE VERIFIQUE SI ES UNA PARTICION LOGICA
    vector<EBR> ebrs;
    EBR particion_logica;
    bool logica_existe = false;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'e' || particiones[i].part_type == 'E'){
            if(!(particiones[i].part_name == particion.name)){
                ebrs = ListadoEBRS(particiones[i], particion.path);
                for(int j = 0; j < ebrs.size(); j++){
                    if(ebrs[j].part_name == particion.name){
                        particion_logica = ebrs[j];
                        logica_existe = true;
                        break;
                    }
                }
            }
        }
    }

    int pos_inicio;
    int pos_fin;
    if(logica_existe){
        pos_inicio = particion_logica.part_start + sizeof(EBR);
        pos_fin = particion_logica.part_start + particion_logica.part_s;
    }else{
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_name == particion.name){
                pos_inicio = particiones[i].part_start;
                pos_fin = particiones[i].part_start + particiones[i].part_s;
                break;
            }
        }
    }

    //OBTIENE EL SUPERBLOQUE
    SuperBloque super_bloque;
    fseek(archivo, pos_inicio, SEEK_SET);
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo);

    //OBTIENE LA POSICION DEL INODO
    int pos_inodo = super_bloque.s_inode_start + sizeof(Inodo);
    Inodo inodo;
    fseek(archivo, pos_inodo, SEEK_SET);
    fread(&inodo, sizeof(Inodo), 1, archivo);

    //OBTIENE LA POSICION DEL BLOQUE
    string usuariostxt = "";
    //APUNTADORES DIRECTOS
    for(int i = 0; i < 12; i++){
        int no_bloque = inodo.i_block[i];
        if(no_bloque == -1){
            break;
        }
        BloqueArchivo bloque;
        fseek(archivo, no_bloque, SEEK_SET);
        fread(&bloque, sizeof(BloqueArchivo), 1, archivo);
        usuariostxt += bloque.b_content;
    }
    
    fclose(archivo);
    
    //OBTIENE TODOS LOS USUARIOS
    vector<string> usuarios_grupos;
    usuarios_grupos = split(usuariostxt, '\n');
    for(int i = 0; i < usuarios_grupos.size(); i++){
        vector<string> datos;
        datos = split(usuarios_grupos[i], ',');
        if(datos[1] == "G" && datos[2] == name){
            return true;
        }else if(datos[0] == "0" && datos[1] == "G" && datos[2] == name){
            return false;
        }
    }
    return false;
}

int Rmgrp::NumeroGrupo(){
    //OBTIENE LA PARTICION
    Nodo particion = lista_particiones_montadas.obtenerNodoParticion(idlogueado);

    //OBTIENE EL MBR
    FILE *archivo;
    archivo = fopen(particion.path.c_str(), "rb+");
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};


    //VERIFICA SI LA PARTICION A FORMATEAR ES EXTENDIDA Y SI ES LA QUE SE QUIERE FORMATEAR O SINO QUE VERIFIQUE SI ES UNA PARTICION LOGICA
    vector<EBR> ebrs;
    EBR particion_logica;
    bool logica_existe = false;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'e' || particiones[i].part_type == 'E'){
            if(!(particiones[i].part_name == particion.name)){
                ebrs = ListadoEBRS(particiones[i], particion.path);
                for(int j = 0; j < ebrs.size(); j++){
                    if(ebrs[j].part_name == particion.name){
                        particion_logica = ebrs[j];
                        logica_existe = true;
                        break;
                    }
                }
            }
        }
    }

    int pos_inicio;
    int pos_fin;
    if(logica_existe){
        pos_inicio = particion_logica.part_start + sizeof(EBR);
        pos_fin = particion_logica.part_start + particion_logica.part_s;
    }else{
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_name == particion.name){
                pos_inicio = particiones[i].part_start;
                pos_fin = particiones[i].part_start + particiones[i].part_s;
                break;
            }
        }
    }

    //OBTIENE EL SUPERBLOQUE
    SuperBloque super_bloque;
    fseek(archivo, pos_inicio, SEEK_SET);
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo);

    //OBTIENE LA POSICION DEL INODO
    int pos_inodo = super_bloque.s_inode_start + sizeof(Inodo);
    Inodo inodo;
    fseek(archivo, pos_inodo, SEEK_SET);
    fread(&inodo, sizeof(Inodo), 1, archivo);

    //OBTIENE LA POSICION DEL BLOQUE
    string usuariostxt = "";
    //APUNTADORES DIRECTOS
    for(int i = 0; i < 12; i++){
        int no_bloque = inodo.i_block[i];
        if(no_bloque == -1){
            break;
        }
        BloqueArchivo bloque;
        fseek(archivo, no_bloque, SEEK_SET);
        fread(&bloque, sizeof(BloqueArchivo), 1, archivo);
        usuariostxt += bloque.b_content;
    }
    
    fclose(archivo);
    
    //OBTIENE TODOS LOS USUARIOS
    vector<string> usuarios_grupos;
    usuarios_grupos = split(usuariostxt, '\n');
    int contador = 0;
    for(int i = 0; i < usuarios_grupos.size(); i++){
        vector<string> datos;
        datos = split(usuarios_grupos[i], ',');
        if(datos[1] == "G"){
            contador++;
        }
    }
    contador++;
    return contador;
}

int Rmgrp::tamanio_disponible(BloqueArchivo contenido){
    int contador = 0;
    for(int i = 0; i < 63; i++){
        if(contenido.b_content[i] == '\0'){
            contador++;
        }
    }
    return contador;
}
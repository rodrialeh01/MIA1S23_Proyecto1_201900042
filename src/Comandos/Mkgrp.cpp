#include "Mkgrp.h"

Mkgrp::Mkgrp(){
}

void Mkgrp::CrearGrupo(Mkgrp *mkgrp){
    string name = mkgrp->name;
    if(name == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No ha agregado el nombre del grupo \e[m\n" << endl;
        return;
    }

    if(!logueado){
        cout << "\e[1;31m[ERROR]:\e[1;37m No ha iniciado sesion \e[m\n" << endl;
        return;
    }

    if(userlogueado != "root"){
        cout << "\e[1;31m[ERROR]:\e[1;37m NO se cuenta con los permisos necesarios para poder crear grupos \e[m\n" << endl;
        return;
    }

    if(name[0]== '\"' && name[name.size()-1] == '\"'){
        name = name.substr(1, name.size()-2);
    }

    if(name.size() > 10){
        cout << "\e[1;31m[ERROR]:\e[1;37m El nombre del grupo es muy largo \e[m\n" << endl;
        return;
    }

    if(ExisteGrupo(name)){
        cout << "\e[1;31m[ERROR]:\e[1;37m El nombre del grupo ya existe \e[m\n" << endl;
        return;
    }

    CreateGrupo(name);

}

vector<EBR> Mkgrp::ListadoEBRS(Particion extendida, string path){
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

bool Mkgrp::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

vector<string> Mkgrp::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Mkgrp::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

void Mkgrp::CreateGrupo(string name){
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

    //APUNTADORES DIRECTOS
    string linea_grupo = to_string(NumeroGrupo()) + ",G," + name + "\n";
    for(int i = 0; i < 12; i++){
        if(i != 12){
            int no_bloque = inodo.i_block[i];
            if(no_bloque != -1){
                if(inodo.i_block[i+1] == -1){
                    BloqueArchivo bloque;
                    fseek(archivo, no_bloque, SEEK_SET);
                    fread(&bloque, sizeof(BloqueArchivo), 1, archivo);
                    string contenido = string(bloque.b_content);
                    int espacio = tamanio_disponible(bloque)- linea_grupo.size();
                    if(espacio >= 0){
                        if(tamanio_disponible(bloque) == 0){
                            //CREA UN NUEVO BLOQUE
                            BloqueArchivo nuevo;
                            strcpy(nuevo.b_content, linea_grupo.c_str());
                            fseek(archivo, super_bloque.s_first_blo, SEEK_SET);
                            fwrite(&nuevo, sizeof(BloqueArchivo), 1, archivo);
                            //ACTUALIZA EL INODO
                            inodo.i_block[i+1] = super_bloque.s_first_blo;
                            fseek(archivo, pos_inodo, SEEK_SET);
                            fwrite(&inodo, sizeof(Inodo), 1, archivo);
                            //ACTUALIZA EL SUPERBLOQUE
                            super_bloque.s_first_blo += sizeof(BloqueArchivo);
                            super_bloque.s_free_blocks_count--;
                            fseek(archivo, pos_inicio, SEEK_SET);
                            fwrite(&super_bloque, sizeof(SuperBloque), 1, archivo);
                            break;
                        }else{
                            contenido += linea_grupo;
                            strcpy(bloque.b_content, contenido.c_str());
                            fseek(archivo, no_bloque, SEEK_SET);
                            fwrite(&bloque, sizeof(BloqueArchivo), 1, archivo);
                            break;
                        }
                    }else if(espacio < 0){
                        if(tamanio_disponible(bloque) !=0){
                            string parte1 = linea_grupo.substr(0, tamanio_disponible(bloque));
                            string parte2 = linea_grupo.substr(tamanio_disponible(bloque), linea_grupo.length());
                            contenido += parte1;
                            //SETEA EL BLOQUE QUE SE ESTA USANDO
                            strcpy(bloque.b_content, contenido.c_str());
                            fseek(archivo, no_bloque, SEEK_SET);
                            fwrite(&bloque, sizeof(BloqueArchivo), 1, archivo);
                            //CREA UN NUEVO BLOQUE
                            BloqueArchivo nuevo;
                            strcpy(nuevo.b_content, parte2.c_str());
                            fseek(archivo, super_bloque.s_first_blo, SEEK_SET);
                            fwrite(&nuevo, sizeof(BloqueArchivo), 1, archivo);
                            //ACTUALIZA EL INODO
                            inodo.i_block[i+1] = super_bloque.s_first_blo;
                            fseek(archivo, pos_inodo, SEEK_SET);
                            fwrite(&inodo, sizeof(Inodo), 1, archivo);
                            //ACTUALIZA EL SUPERBLOQUE
                            super_bloque.s_first_blo += sizeof(BloqueArchivo);
                            super_bloque.s_free_blocks_count--;
                            fseek(archivo, pos_inicio, SEEK_SET);
                            fwrite(&super_bloque, sizeof(SuperBloque), 1, archivo);
                            break;
                        }
                    }
                }
            }
        }else{
            int no_bloque = inodo.i_block[i];
            BloqueArchivo bloque;
            fseek(archivo, no_bloque, SEEK_SET);
            fread(&bloque, sizeof(BloqueArchivo), 1, archivo);
            string contenido = string(bloque.b_content);
            int espacio = tamanio_disponible(bloque)- linea_grupo.length();
            if(espacio >= 0){
                contenido += linea_grupo;
                strcpy(bloque.b_content, contenido.c_str());
                fseek(archivo, no_bloque, SEEK_SET);
                fwrite(&bloque, sizeof(BloqueArchivo), 1, archivo);
                break;
            }
        }        
    }


    fclose(archivo);

    cout << "\e[1;32m [SUCCESS]: \e[1;37m Se ha creado el grupo: " << name << " exitosamente \e[m\n" << endl;

}

bool Mkgrp::ExisteGrupo(string name){
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
        }
    }
    return false;
}

int Mkgrp::NumeroGrupo(){
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

int Mkgrp::tamanio_disponible(BloqueArchivo contenido){
    int contador = 0;
    for(int i = 0; i < 63; i++){
        if(contenido.b_content[i] == '\0'){
            contador++;
        }
    }
    return contador;
}
#include "Mkfs.h"

Mkfs::Mkfs() {
}

bool Mkfs::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

void Mkfs::SistemaDeArchivos(Mkfs *mkfs){
    //VALIDACIONES DE PARAMETROS
    if(mkfs->id == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado el id de la particion \e[m\n" << endl;
        return;
    }
    if(mkfs->type == ""){
        mkfs->type = "full";
    }
    if(mkfs->fs == ""){
        mkfs->fs = "2fs";
    }

    //VALIDACION SI EXISTE EL ID
    if(!lista_particiones_montadas.ExisteID(mkfs->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion \e[m\n" << endl;
        return;
    }

    if(mkfs->type == "full"){
        if(mkfs->fs == "2fs"){
            FormatearExt2(mkfs->id);
        }else if(mkfs->fs == "3fs"){
            FormatearExt3(mkfs->id);
        }else{
            cout << "\e[1;31m[ERROR]:\e[1;37m El sistema de archivos a formatear no existe \e[m\n" << endl;
            return;
        }
    }else{
        cout << "\e[1;31m[ERROR]:\e[1;37m El tipo de formateo no existe \e[m\n" << endl;
        return;
    }

}

void Mkfs::FormatearExt2(string id){
    //OBTIENE LA PARTICION
    Nodo particion = lista_particiones_montadas.obtenerNodoParticion(id);

    //OBTIENE EL MBR
    FILE *archivo;
    archivo = fopen(particion.path.c_str(), "rb+");
    if(archivo == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }
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

    //PROCEDE A BORRAR TODO EL CONTENIDO DENTRO DE LA PARTICION
    fseek(archivo, pos_inicio, SEEK_SET);
    char vacio = '\0';
    for(int i = pos_inicio; i < pos_fin; i++){
        fwrite(&vacio, sizeof(char), 1, archivo);
    }
    

    //CALCULO DE N
    //FORMULA: n = (tamanio_particion - sizeof(superbloque))/(4+sizeof(inodos) + 3*sizeof(block))
    int tamanio_particion = pos_fin - pos_inicio;

    float n = (tamanio_particion - sizeof(SuperBloque))/(4 + sizeof(Inodo) + 3*sizeof(BloqueArchivo));
    n = floor(n);

    int tamanio_bitmap_inodos = int(n);
    int tamanio_bitmap_bloques = int(n*3);
    int tamanio_inodos = int(n*sizeof(Inodo));
    int tamanio_bloques = int(n*3*sizeof(BloqueArchivo));

    //CALCULO DE INICIO DE CADA SECCION
    int inicio_bitmap_inodos = pos_inicio + sizeof(SuperBloque);
    int inicio_bitmap_bloques = inicio_bitmap_inodos + tamanio_bitmap_inodos;
    int inicio_inodos = inicio_bitmap_bloques + tamanio_bitmap_bloques;
    int inicio_bloques = inicio_inodos + tamanio_inodos;

    //CREACION DEL SUPERBLOQUE
    SuperBloque superbloque;
    superbloque.s_filesystem_type = 2;
    superbloque.s_inodes_count = tamanio_bitmap_inodos;
    superbloque.s_blocks_count = tamanio_bitmap_bloques;
    superbloque.s_free_blocks_count = tamanio_bitmap_bloques;
    superbloque.s_free_inodes_count = tamanio_bitmap_inodos;
    superbloque.s_mtime = particion.fecha_mount;
    superbloque.s_umtime = time(0);
    superbloque.s_mnt_count = 1;
    superbloque.s_magic = 0xEF53;
    superbloque.s_inode_s = sizeof(Inodo);
    superbloque.s_block_s = sizeof(BloqueArchivo);
    superbloque.s_first_ino = inicio_inodos;
    superbloque.s_first_blo = inicio_bloques;
    superbloque.s_bm_inode_start = inicio_bitmap_inodos;
    superbloque.s_bm_block_start = inicio_bitmap_bloques;
    superbloque.s_inode_start = inicio_inodos;
    superbloque.s_block_start = inicio_bloques;

    //ESCRITURA DEL SUPERBLOQUE
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL BITMAP DE INODOS
    int ibn = inicio_bitmap_inodos;
    char bitmap_inodos[tamanio_bitmap_inodos];
    for(int i = 0; i < tamanio_bitmap_inodos; i++){
        char caracter = '0';
        fseek(archivo, ibn, SEEK_SET);
        fwrite(&caracter, sizeof(caracter), 1, archivo);
        ibn++;
    }
    

    //ESCRITURA DEL BITMAP DE BLOQUES
    int ibb = inicio_bitmap_bloques;
    
    char bitmap_bloques[tamanio_bitmap_bloques];
    for(int i = 0; i < tamanio_bitmap_bloques; i++){
        char caracter = '0';
        fseek(archivo, ibb, SEEK_SET);
        fwrite(&caracter, sizeof(caracter), 1, archivo);
        ibb++;
    }

    


    //========================================CREACION DEL /USERS.TXT====================================

    //ESCRITURA DEL INNODO DE LA CARPETA RAIZ
    Inodo inodo_raiz;
    inodo_raiz.i_uid = 1;
    inodo_raiz.i_gid = 1;
    inodo_raiz.i_s = 0;
    time_t ahora;
    inodo_raiz.i_atime = time(&ahora);
    inodo_raiz.i_ctime = time(&ahora);
    inodo_raiz.i_mtime = time(&ahora);
    for(int i = 0; i < 15; i++){
        inodo_raiz.i_block[i] = -1;
    }
    inodo_raiz.i_block[0] = superbloque.s_block_start;
    inodo_raiz.i_type = '0';
    inodo_raiz.i_perm = 664;

    fseek(archivo, inicio_inodos, SEEK_SET);
    fwrite(&inodo_raiz, sizeof(Inodo), 1, archivo);

    //ESCRITURA AL BITMAP DE INNODOS
    fseek(archivo, inicio_bitmap_inodos, SEEK_SET);
    char actualizacion = '1';
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_inodes_count = superbloque.s_free_inodes_count - 1;
    superbloque.s_first_ino = superbloque.s_first_ino + sizeof(Inodo);
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL BLOQUE DE LA CARPETA RAIZ
    BloqueCarpeta carpeta_raiz;
    //SIGNIFICA EL .
    strcpy(carpeta_raiz.b_content[0].b_name, "/");
    carpeta_raiz.b_content[0].b_inodo = superbloque.s_inode_start;
    //SIGNIFICA EL ..
    strcpy(carpeta_raiz.b_content[1].b_name, "/");
    carpeta_raiz.b_content[1].b_inodo = superbloque.s_inode_start;
    //APUNTA AL INODO DEL USERS.TXT
    strcpy(carpeta_raiz.b_content[2].b_name, "users.txt");
    carpeta_raiz.b_content[2].b_inodo = superbloque.s_inode_start + sizeof(Inodo);
    for(int i=0;i<12;i++){
        carpeta_raiz.b_content[3].b_name[i] = '\0';
    }
    //MANTIENE EL OTRO APUNTADOR EN -1
    carpeta_raiz.b_content[3].b_inodo = -1;


    fseek(archivo, inicio_bloques, SEEK_SET);
    fwrite(&carpeta_raiz, sizeof(BloqueCarpeta), 1, archivo);

    //ESCRITURA AL BITMAP DE BLOQUES
    fseek(archivo, inicio_bitmap_bloques, SEEK_SET);
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_blocks_count = superbloque.s_free_blocks_count - 1;
    superbloque.s_first_blo = superbloque.s_first_blo + sizeof(BloqueCarpeta);
    fseek(archivo, pos_inicio, SEEK_SET);

    //ESCRITURA DEL INODO DEL ARCHIVO USERS.TXT
    Inodo inodo_users;
    inodo_users.i_uid = 1;
    inodo_users.i_gid = 1;
    inodo_users.i_s = 27;
    inodo_users.i_atime = time(&ahora);
    inodo_users.i_ctime = time(&ahora);
    inodo_users.i_mtime = time(&ahora);
    for(int i = 0; i < 15; i++){
        inodo_users.i_block[i] = -1;
    }
    inodo_users.i_block[0] = superbloque.s_block_start + sizeof(BloqueCarpeta);
    inodo_users.i_type = '1';
    inodo_users.i_perm = 664;

    fseek(archivo, inicio_inodos + sizeof(Inodo), SEEK_SET);
    fwrite(&inodo_users, sizeof(Inodo), 1, archivo);

    //ESCRITURA AL BITMAP DE INODOS
    fseek(archivo, inicio_bitmap_inodos + sizeof(actualizacion), SEEK_SET);
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_inodes_count = superbloque.s_free_inodes_count - 1;
    superbloque.s_first_ino = superbloque.s_first_ino + sizeof(Inodo);
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL BLOQUE DE CONTENIDO DEL ARCHIVO USERS.TXT

    BloqueArchivo bloque_userstxt;
    strcpy(bloque_userstxt.b_content,"1,G,root\n1,U,root,root,123\n");

    fseek(archivo, superbloque.s_block_start + sizeof(BloqueArchivo), SEEK_SET);
    fwrite(&bloque_userstxt, sizeof(BloqueArchivo), 1, archivo);

    //ESCRITURA AL BITMAP DE BLOQUES
    fseek(archivo, inicio_bitmap_bloques + sizeof(actualizacion), SEEK_SET);
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_blocks_count = superbloque.s_free_blocks_count - 1;
    superbloque.s_first_blo = superbloque.s_first_blo + sizeof(BloqueArchivo);
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    fclose(archivo);

    cout << "\e[1;32m [SUCCESS]: \e[1;37m Se acaba de formatear la partición y se creó el sistema de archivos EXT2 \e[m\n" << endl;

}

void Mkfs::FormatearExt3(string id){
    //OBTIENE LA PARTICION
    Nodo particion = lista_particiones_montadas.obtenerNodoParticion(id);

    //OBTIENE EL MBR
    FILE *archivo;
    archivo = fopen(particion.path.c_str(), "rb+");
    if(archivo == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }
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

    //PROCEDE A BORRAR TODO EL CONTENIDO DENTRO DE LA PARTICION
    fseek(archivo, pos_inicio, SEEK_SET);
    char vacio = '\0';
    for(int i = pos_inicio; i < pos_fin; i++){
        fwrite(&vacio, sizeof(char), 1, archivo);
    }
    

    //CALCULO DE N
    //FORMULA: n = (tamanio_particion - sizeof(superbloque))/(4+sizeof(inodos) + 3*sizeof(block))
    int tamanio_particion = pos_fin - pos_inicio;

    float n = (tamanio_particion - sizeof(SuperBloque))/(4 + sizeof(Journaling) + sizeof(Inodo) + 3*sizeof(BloqueArchivo));
    n = floor(n);

    int tamanio_journaling = int(n*sizeof(Journaling));
    int tamanio_bitmap_inodos = int(n);
    int tamanio_bitmap_bloques = int(n*3);
    int tamanio_inodos = int(n*sizeof(Inodo));
    int tamanio_bloques = int(n*3*sizeof(BloqueArchivo));

    //CALCULO DE INICIO DE CADA SECCION
    int inicio_journaling = pos_inicio + sizeof(SuperBloque);
    int inicio_bitmap_inodos = inicio_journaling + tamanio_journaling;
    int inicio_bitmap_bloques = inicio_bitmap_inodos + tamanio_bitmap_inodos;
    int inicio_inodos = inicio_bitmap_bloques + tamanio_bitmap_bloques;
    int inicio_bloques = inicio_inodos + tamanio_inodos;

    //CREACION DEL SUPERBLOQUE
    SuperBloque superbloque;
    superbloque.s_filesystem_type = 3;
    superbloque.s_inodes_count = tamanio_bitmap_inodos;
    superbloque.s_blocks_count = tamanio_bitmap_bloques;
    superbloque.s_free_blocks_count = tamanio_bitmap_bloques;
    superbloque.s_free_inodes_count = tamanio_bitmap_inodos;
    superbloque.s_mtime = particion.fecha_mount;
    superbloque.s_umtime = time(0);
    superbloque.s_mnt_count = 1;
    superbloque.s_magic = 0xEF53;
    superbloque.s_inode_s = sizeof(Inodo);
    superbloque.s_block_s = sizeof(BloqueArchivo);
    superbloque.s_first_ino = inicio_inodos;
    superbloque.s_first_blo = inicio_bloques;
    superbloque.s_bm_inode_start = inicio_bitmap_inodos;
    superbloque.s_bm_block_start = inicio_bitmap_bloques;
    superbloque.s_inode_start = inicio_inodos;
    superbloque.s_block_start = inicio_bloques;

    //ESCRITURA DEL SUPERBLOQUE
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL BITMAP DE INODOS
    int ibn = inicio_bitmap_inodos;
    char bitmap_inodos[tamanio_bitmap_inodos];
    for(int i = 0; i < tamanio_bitmap_inodos; i++){
        char caracter = '0';
        fseek(archivo, ibn, SEEK_SET);
        fwrite(&caracter, sizeof(caracter), 1, archivo);
        ibn++;
    }
    

    //ESCRITURA DEL BITMAP DE BLOQUES
    int ibb = inicio_bitmap_bloques;
    
    char bitmap_bloques[tamanio_bitmap_bloques];
    for(int i = 0; i < tamanio_bitmap_bloques; i++){
        char caracter = '0';
        fseek(archivo, ibb, SEEK_SET);
        fwrite(&caracter, sizeof(caracter), 1, archivo);
        ibb++;
    }

    


    //========================================CREACION DEL /USERS.TXT====================================

    //ESCRITURA DEL INNODO DE LA CARPETA RAIZ
    Inodo inodo_raiz;
    inodo_raiz.i_uid = 1;
    inodo_raiz.i_gid = 1;
    inodo_raiz.i_s = 0;
    time_t ahora;
    inodo_raiz.i_atime = time(&ahora);
    inodo_raiz.i_ctime = time(&ahora);
    inodo_raiz.i_mtime = time(&ahora);
    for(int i = 0; i < 15; i++){
        inodo_raiz.i_block[i] = -1;
    }
    inodo_raiz.i_block[0] = superbloque.s_block_start;
    inodo_raiz.i_type = '0';
    inodo_raiz.i_perm = 664;

    fseek(archivo, inicio_inodos, SEEK_SET);
    fwrite(&inodo_raiz, sizeof(Inodo), 1, archivo);

    //ESCRITURA AL BITMAP DE INNODOS
    fseek(archivo, inicio_bitmap_inodos, SEEK_SET);
    char actualizacion = '1';
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ESCRITURA DEL JOURNALING
    Journaling journaling_raiz;
    strcpy(journaling_raiz.accion,"Crear");
    strcpy(journaling_raiz.tipo,"Carpeta");
    strcpy(journaling_raiz.nombre,"/");
    for(int i = 0; i < 64; i++){
        journaling_raiz.contenido[i] = '\0';
    }
    for(int i = 0; i < 64; i++){
        journaling_raiz.destino[i] = '\0';
    }
    time_t hoy;
    journaling_raiz.fecha = time(&hoy);

    fseek(archivo, inicio_journaling, SEEK_SET);
    fwrite(&journaling_raiz, sizeof(Journaling), 1, archivo);


    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_inodes_count = superbloque.s_free_inodes_count - 1;
    superbloque.s_first_ino = superbloque.s_first_ino + sizeof(Inodo);
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL BLOQUE DE LA CARPETA RAIZ
    BloqueCarpeta carpeta_raiz;
    //SIGNIFICA EL .
    strcpy(carpeta_raiz.b_content[0].b_name, "/");
    carpeta_raiz.b_content[0].b_inodo = superbloque.s_inode_start;
    //SIGNIFICA EL ..
    strcpy(carpeta_raiz.b_content[1].b_name, "/");
    carpeta_raiz.b_content[1].b_inodo = superbloque.s_inode_start;
    //APUNTA AL INODO DEL USERS.TXT
    strcpy(carpeta_raiz.b_content[2].b_name, "users.txt");
    carpeta_raiz.b_content[2].b_inodo = superbloque.s_inode_start + sizeof(Inodo);
    for(int i=0;i<12;i++){
        carpeta_raiz.b_content[3].b_name[i] = '\0';
    }
    //MANTIENE EL OTRO APUNTADOR EN -1
    carpeta_raiz.b_content[3].b_inodo = -1;


    fseek(archivo, inicio_bloques, SEEK_SET);
    fwrite(&carpeta_raiz, sizeof(BloqueCarpeta), 1, archivo);

    //ESCRITURA AL BITMAP DE BLOQUES
    fseek(archivo, inicio_bitmap_bloques, SEEK_SET);
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_blocks_count = superbloque.s_free_blocks_count - 1;
    superbloque.s_first_blo = superbloque.s_first_blo + sizeof(BloqueCarpeta);
    fseek(archivo, pos_inicio, SEEK_SET);

    //ESCRITURA DEL INODO DEL ARCHIVO USERS.TXT
    Inodo inodo_users;
    inodo_users.i_uid = 1;
    inodo_users.i_gid = 1;
    inodo_users.i_s = 27;
    inodo_users.i_atime = time(&ahora);
    inodo_users.i_ctime = time(&ahora);
    inodo_users.i_mtime = time(&ahora);
    for(int i = 0; i < 15; i++){
        inodo_users.i_block[i] = -1;
    }
    inodo_users.i_block[0] = superbloque.s_block_start + sizeof(BloqueCarpeta);
    inodo_users.i_type = '1';
    inodo_users.i_perm = 664;

    fseek(archivo, inicio_inodos + sizeof(Inodo), SEEK_SET);
    fwrite(&inodo_users, sizeof(Inodo), 1, archivo);

    //ESCRITURA AL BITMAP DE INODOS
    fseek(archivo, inicio_bitmap_inodos + sizeof(actualizacion), SEEK_SET);
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_inodes_count = superbloque.s_free_inodes_count - 1;
    superbloque.s_first_ino = superbloque.s_first_ino + sizeof(Inodo);
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL JOURNALING
    Journaling journaling_users;
    strcpy(journaling_users.accion,"Crear");
    strcpy(journaling_users.tipo,"Archivo");
    strcpy(journaling_users.nombre,"users.txt");
    for(int i = 0; i < 64; i++){
        journaling_users.contenido[i] = '\0';
    }
    for(int i = 0; i < 64; i++){
        journaling_users.destino[i] = '\0';
    }
    journaling_users.fecha = time(&hoy);

    fseek(archivo, inicio_journaling + sizeof(Journaling), SEEK_SET);
    fwrite(&journaling_users, sizeof(Journaling), 1, archivo);


    //ESCRITURA DEL BLOQUE DE CONTENIDO DEL ARCHIVO USERS.TXT

    BloqueArchivo bloque_userstxt;
    strcpy(bloque_userstxt.b_content,"1,G,root\n1,U,root,root,123\n");

    fseek(archivo, superbloque.s_block_start + sizeof(BloqueArchivo), SEEK_SET);
    fwrite(&bloque_userstxt, sizeof(BloqueArchivo), 1, archivo);

    //ESCRITURA AL BITMAP DE BLOQUES
    fseek(archivo, inicio_bitmap_bloques + sizeof(actualizacion), SEEK_SET);
    fwrite(&actualizacion, sizeof(actualizacion), 1, archivo);

    //ACTUALIZACION DEL SUPERBLOQUE
    superbloque.s_free_blocks_count = superbloque.s_free_blocks_count - 1;
    superbloque.s_first_blo = superbloque.s_first_blo + sizeof(BloqueArchivo);
    fseek(archivo, pos_inicio, SEEK_SET);
    fwrite(&superbloque, sizeof(SuperBloque), 1, archivo);

    //ESCRITURA DEL JOURNALING GRUPO
    Journaling journaling_bloque;
    strcpy(journaling_bloque.accion,"Crear");
    strcpy(journaling_bloque.tipo,"Grupo");
    strcpy(journaling_bloque.nombre,"root");
    strcpy(journaling_bloque.destino,"users.txt");
    strcpy(journaling_bloque.contenido,"1,G,root");
    journaling_bloque.fecha = time(&hoy);

    fseek(archivo, inicio_journaling + 2*sizeof(Journaling), SEEK_SET);
    fwrite(&journaling_bloque, sizeof(Journaling), 1, archivo);

    //ESCRITURA DEL JOURNALING USUARIO
    Journaling journaling_bloque2;
    strcpy(journaling_bloque2.accion,"Crear");
    strcpy(journaling_bloque2.tipo,"Usuario");
    strcpy(journaling_bloque2.nombre,"root");
    strcpy(journaling_bloque2.destino,"users.txt");
    strcpy(journaling_bloque2.contenido,"1,U,root,root,123");
    journaling_bloque2.fecha = time(&hoy);

    fseek(archivo, inicio_journaling + 3*sizeof(Journaling), SEEK_SET);
    fwrite(&journaling_bloque2, sizeof(Journaling), 1, archivo);


    fclose(archivo);

    cout << "\e[1;32m [SUCCESS]: \e[1;37m Se acaba de formatear la partición y se creó el sistema de archivos EXT3 \e[m\n" << endl;
}

vector<EBR> Mkfs::ListadoEBRS(Particion extendida, string path){
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
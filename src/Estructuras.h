#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <ctime>
#include <string>

using namespace std;

//Struct de la particion
typedef struct {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_s;
    char part_name[16];
}Particion;

//Struct del MBR

typedef struct {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_dsk_signature;
    char disk_fit;
    Particion mbr_particion_1;
    Particion mbr_particion_2;
    Particion mbr_particion_3;
    Particion mbr_particion_4;
}MBR;

typedef struct {
    char part_status;
    char part_fit;
    int part_start;
    int part_s;
    int part_next;
    char part_name[16];
}EBR;

typedef struct {
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_s;
    int s_block_s;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
}SuperBloque;

typedef struct {
    int i_uid;
    int i_gid;
    int i_s;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block[15];
    char i_type;
    int i_perm;
}Inodo;

typedef struct {
    char b_name[12];
    int b_inodo;
}Content;

typedef struct {
    Content b_content[4];
}BloqueCarpeta;

typedef struct {
    char b_content[64];
}BloqueArchivo;

typedef struct {
    char b_content[64];
}BloqueApuntador;

class Estructuras{
    public:
        Estructuras();
};

#endif
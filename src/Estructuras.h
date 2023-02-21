#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <ctime>
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

#endif
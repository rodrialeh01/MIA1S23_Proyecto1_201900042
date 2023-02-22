
#ifndef FDISK_H
#define FDISK_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

class Fdisk {
    public:
        Fdisk();
        int size = 0;
        string path = "";
        string name = "";
        string unit = "";
        string fit = "";
        string type = "";
        string dsk_delete = "";
        int add = 0;
        vector<string> split(string texto, char  parametro);
        string toLowerCase(string palabra);
        void SistemaDeParticiones(Fdisk *particion);
        void AgregarParticion(Fdisk *particion);
        void AgregarParticionPrimaria(Fdisk *particion, MBR *mbr_dsk);
        void AgregarParticionExtendida(Fdisk *particion, MBR *mbr_dsk);
        void AgregarParticionLogica(Fdisk *particion, MBR *mbr_dsk);
        void EliminarParticion(Fdisk *particion);
        void AumentarParticion(Fdisk *particion);
        void ReducirParticion(Fdisk *particion);
};

#endif
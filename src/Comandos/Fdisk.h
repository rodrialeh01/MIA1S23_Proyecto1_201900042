
#ifndef FDISK_H
#define FDISK_H

#include "vector"
#include <cstring>
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
        string toUpperCase(string palabra);
        bool cadenaVacia(char cadena[]);
        void SistemaDeParticiones(Fdisk *particion);
        void AgregarParticion(Fdisk *particion);
        void AgregarParticion(Fdisk *particion, MBR mbr_dsk);
        EBR retornarUlitmoEBR(vector<EBR> ebrs);
        void ActualizarEBR(EBR ebr, string path);
        vector<EBR> ListadoEBR(Particion extendida, string path);
        void AgregarEBR(EBR ebr, string path);
        void AgregarParticionLogica(vector<Particion> particiones, MBR mbr,Fdisk *particion);
        void ActualizarDisco(vector<Particion>,MBR mbr, string path);
        void FirstFit(vector<Particion> particiones, MBR mbr,Fdisk *particion);
        void BestFit(vector<Particion> particiones, MBR mbr,Fdisk *particion);
        void WorstFit(vector<Particion> particiones, MBR mbr,Fdisk *particion);
        void EliminarParticion(Fdisk *particion);
        void Cambiar_Tamanio_Particion(Fdisk *particion);
        void EliminarParticionLogica(vector<Particion> particiones, MBR mbr,Fdisk *particion);
        int FirstFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe);
        int BestFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe);
        int WorstFit_Logicas(vector<EBR> ebrs, int tamanio, int final_pe);
};

#endif
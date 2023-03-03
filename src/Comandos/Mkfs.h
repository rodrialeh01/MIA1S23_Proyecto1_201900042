#ifndef MKFS_H
#define MKFS_H

#include "vector"
#include <string.h>
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <cmath>

#include "../Estructuras.h"
#include "../RAM/ListaDoble.h"

using namespace std;

extern ListaDoble lista_particiones_montadas;

class Mkfs {
    public:
        Mkfs();
        string id = "";
        string type = "";
        string fs = "";
        void SistemaDeArchivos(Mkfs *mkfs);
        void FormatearExt2(string id);
        void FormatearExt3(string id);
        vector<EBR> ListadoEBRS(Particion extendida, string path);
        bool cadenaVacia(char cadena[]);
};

#endif
#ifndef MKGRP_H
#define MKGRP_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <cmath>
#include <iomanip>
#include "time.h"
#include <typeinfo>
#include <string.h>

#include "../Estructuras.h"
#include "../RAM/ListaDoble.h"

using namespace std;

extern ListaDoble lista_particiones_montadas;
extern bool logueado;
extern string userlogueado;
extern string idlogueado;

class Mkgrp {
    public:
        Mkgrp();
        string name = "";
        void CrearGrupo(Mkgrp *mkgrp);
        vector<EBR> ListadoEBRS(Particion extendida, string path);
        bool cadenaVacia(char cadena[]);
        vector<string> split(string texto, char  parametro);
        string toLowerCase(string palabra);
        int NumeroGrupo();
        bool ExisteGrupo(string name);
        void CreateGrupo(string name);
        int tamanio_disponible(BloqueArchivo contenido);
};

#endif
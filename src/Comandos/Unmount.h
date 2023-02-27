#ifndef UNMOUNT_H
#define UNMOUNT_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"
#include "../RAM/ListaDoble.h"

using namespace std;

extern ListaDoble lista_particiones_montadas;

class Unmount {
    public:
        Unmount();
        string id = "";
        void DesmontarParticion(Unmount *desmontar);
};

#endif
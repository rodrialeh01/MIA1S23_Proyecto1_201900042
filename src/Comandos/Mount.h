#ifndef MOUNT_H
#define MOUNT_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

class Mount {
    public:
        Mount();
        string path = "";
        string name = "";
        void MontarParticion(Mount *montar);
        string nombre_disco(string path);
        vector<string> split(string texto, char  parametro);
};

#endif
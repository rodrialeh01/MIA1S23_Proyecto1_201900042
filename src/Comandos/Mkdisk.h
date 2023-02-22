
#ifndef MKDISK_H
#define MKDISK_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

class Mkdisk {
    public:
        Mkdisk();
        int size = 0;
        string path = "";
        string unit = "";
        string fit = "";
        vector<string> split(string texto, char  parametro);
        string toLowerCase(string palabra);
        void CrearDisco(Mkdisk *disco_nuevo);
};

#endif
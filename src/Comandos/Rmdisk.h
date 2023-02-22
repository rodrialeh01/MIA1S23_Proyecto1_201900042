
#ifndef RMDISK_H
#define RMDISK_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

class Rmdisk {
    public:
        Rmdisk();
        int size = 0;
        string path = "";
        vector<string> split(string texto, char  parametro);
        void EliminarDisco(Rmdisk *disco);
};

#endif
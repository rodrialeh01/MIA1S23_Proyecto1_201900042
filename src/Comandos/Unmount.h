#ifndef UNMOUNT_H
#define UNMOUNT_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

class Unmount {
    public:
        Unmount();
        string id = "";
        void DesmontarParticion(Unmount *desmontar);
};

#endif
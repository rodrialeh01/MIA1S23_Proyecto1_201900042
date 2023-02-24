
#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdio.h>
#include "../analizador/driver.h"

using namespace std;

class Execute {
    public:
        Execute();
        string path = "";
        void AnalizarArchivo(Execute *archivo);
};

#endif
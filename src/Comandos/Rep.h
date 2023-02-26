#ifndef REP_H
#define REP_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

class Rep {
    public:
        Rep();
        string id = "";
        string path = "";
        string name = "";
        string ruta = "";
        void controlReportes(Rep *reporte);
        void ReporteMBR(Rep *reporte);
        void ReporteDisk(Rep *reporte);
};

#endif
#ifndef REP_H
#define REP_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <cmath>
#include <iomanip>
#include "time.h"

#include "../Estructuras.h"
#include "../RAM/ListaDoble.h"

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
        string toLowerCase(string palabra);
        vector<EBR> ListadoEBR(Particion extendida, string path);
        bool cadenaVacia(char cadena[]);
        vector<string> split(string texto, char parametro);
        string getFecha(time_t fecha);
};

#endif
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
#include <typeinfo>

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
        void ReporteInodo(Rep *reporte);
        void ReporteBloque(Rep *reporte);
        void ReporteBMInodo(Rep *reporte);
        void ReporteBMBloque(Rep *reporte);
        void ReporteSuperBloque(Rep *reporte);
        void ReporteJournaling(Rep *reporte);
        void ReporteTree(Rep *reporte);
        void ReporteFile(Rep *reporte);
        string toLowerCase(string palabra);
        vector<EBR> ListadoEBR(Particion extendida, string path);
        vector <Inodo> ListadoInodos(int inicio, int final, string path);
        vector <BloqueArchivo> ListadoBA(int inicio, int final, string path);
        vector <BloqueCarpeta> ListadoBC(int inicio, int final, string path);
        vector <BloqueApuntador> ListadoBAp(int inicio, int final, string path);
        vector <Journaling> ListadoJournaling(int inicio, int final, string path);
        bool cadenaVacia(char cadena[]);
        vector<string> split(string texto, char parametro);
        string getFecha(time_t fecha);
        string getOnlyFecha(time_t fecha);
        string dottree(int posicion, string dot, string path);
};

#endif
#include "Rep.h"

Rep::Rep() {
}

void Rep::controlReportes(Rep *reporte){
    if(reporte->id == ""){
        cout << "ERROR: No se ha ingresado el id del disco" << endl;
        return;
    }

    if(reporte->path == ""){
        cout << "ERROR: No se ha ingresado la ruta del reporte" << endl;
        return;
    }

    if (reporte->name == "mbr"){
        ReporteMBR(reporte);
    }else if (reporte->name == "disk"){
        ReporteDisk(reporte);
    }else{
        cout << "ERROR: El reporte no existe" << endl;
    }
}

void Rep::ReporteMBR(Rep *reporte){

}

void Rep::ReporteDisk(Rep *reporte){

}
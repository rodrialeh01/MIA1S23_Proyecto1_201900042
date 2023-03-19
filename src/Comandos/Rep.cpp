#include "Rep.h"

Rep::Rep() {
}

extern ListaDoble lista_particiones_montadas;

string Rep::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

void Rep::controlReportes(Rep *reporte){
    if(reporte->id == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado el id del disco \e[m\n" << endl;
        return;
    }

    if(reporte->path == ""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha ingresado la ruta del reporte \e[m\n" << endl;
        return;
    }

    if (toLowerCase(reporte->name) == "mbr"){
        ReporteMBR(reporte);
    }else if (toLowerCase(reporte->name) == "disk"){
        ReporteDisk(reporte);
    }else if (toLowerCase(reporte->name) == "inode"){
        ReporteInodo(reporte);
    }else if (toLowerCase(reporte->name) == "block"){
        ReporteBloque(reporte);
    }else if (toLowerCase(reporte->name) == "bm_inode"){
        ReporteBMInodo(reporte);
    }else if (toLowerCase(reporte->name) == "bm_block"){
        ReporteBMBloque(reporte);
    }else if (toLowerCase(reporte->name) == "sb"){
        ReporteSuperBloque(reporte);
    }else if (toLowerCase(reporte->name) == "tree"){
        ReporteTree(reporte);
    }else if (toLowerCase(reporte->name) == "journaling"){
        ReporteJournaling(reporte);
    }else{
        cout << "\e[1;31m[ERROR]:\e[1;37m El tipo de reporte no existe \e[m\n" << endl;
    }
}

void Rep::ReporteMBR(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: \e[m\n" << reporte->id << endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);

    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);
    fclose(archivo2);

    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    
    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            break;
        }
    }

    string reporte_mbr = "digraph G {\n";
    reporte_mbr += "node [shape=plaintext]\n";
    reporte_mbr += "tablambr[label=<\n";
    reporte_mbr += "<table fontname=\"Century Gothic\" border=\"0\" cellspacing=\"0\">\n";
    //REPORTE DE MBR
    reporte_mbr += "<tr><td bgcolor=\"\#8523d6\" ><FONT COLOR=\"white\">REPORTE DE MBR</FONT></td>\n";
    reporte_mbr += "<td bgcolor=\"\#8523d6\" ><FONT COLOR=\"\#8523d6\">a</FONT></td>\n";
    reporte_mbr += "</tr>\n";
    reporte_mbr += "<tr><td border=\"1\">mbr_tamano</td>\n";
    reporte_mbr += "<td border=\"1\">" + to_string(mbr.mbr_tamano) + "</td>\n";
    reporte_mbr += "</tr>\n";
    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">mbr_fecha_creacion</td>\n";
    reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + getFecha(mbr.mbr_fecha_creacion) + "</td>\n";
    reporte_mbr += "</tr>\n";
    reporte_mbr += "<tr><td border=\"1\">mbr_dsk_signature</td>\n";
    reporte_mbr += "<td border=\"1\">" + to_string(mbr.mbr_dsk_signature) + "</td>\n";
    reporte_mbr += "</tr>\n";
    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">dsk_fit</td>\n";
    reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + string(1,mbr.disk_fit) + "</td>\n";
    reporte_mbr += "</tr>\n";
    //REPORTE DE LA PARTICION1
    if(mbr.mbr_particion_1.part_s> 0 && (!cadenaVacia(mbr.mbr_particion_1.part_name))){
        reporte_mbr += "<tr><td bgcolor=\"\#8523d6\" ><FONT COLOR=\"white\">PARTICION 1</FONT></td>\n";
        reporte_mbr += "<td bgcolor=\"\#8523d6\" ><FONT COLOR=\"\#8523d6\">a</FONT></td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
        if(lista_particiones_montadas.ParticionMontada(mbr.mbr_particion_1.part_name, particion_reporte.path)){
            reporte_mbr += "<td border=\"1\">1</td>\n";
        }else{
            reporte_mbr += "<td border=\"1\">0</td>\n";
        }
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_type</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + string(1,mbr.mbr_particion_1.part_type) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_fit</td>\n";
        reporte_mbr += "<td border=\"1\">" + string(1,mbr.mbr_particion_1.part_fit) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_start</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + to_string(mbr.mbr_particion_1.part_start) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_size</td>\n";
        reporte_mbr += "<td border=\"1\">" + to_string(mbr.mbr_particion_1.part_s) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_name</td>\n";
        string name_1(mbr.mbr_particion_1.part_name);
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + name_1 + "</td>\n";
        reporte_mbr += "</tr>\n";
    }
    //SI LA PARTICION 1 ES EXTENDIDA
    if(mbr.mbr_particion_1.part_type == 'e' || mbr.mbr_particion_1.part_type == 'E'){
        if(mbr.mbr_particion_1.part_s> 0 && (!cadenaVacia(mbr.mbr_particion_1.part_name))){
            for(int i = 0; i < ebrs.size(); i++){
                if(!cadenaVacia(ebrs[i].part_name)){
                    reporte_mbr += "<tr><td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"white\">PARTICION LÓGICA</FONT></td>\n";
                    reporte_mbr += "<td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"\#ff9f23\">a</FONT></td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
                    if(lista_particiones_montadas.ParticionMontada(ebrs[i].part_name, particion_reporte.path)){
                        reporte_mbr += "<td border=\"1\">1</td>\n";
                    }else{
                        reporte_mbr += "<td border=\"1\">0</td>\n";
                    }
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_fit</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + string(1,ebrs[i].part_fit) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_start</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_start) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_size</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + to_string(ebrs[i].part_s) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_next</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_next) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_name</td>\n";
                    string name_1(ebrs[i].part_name);
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + name_1 + "</td>\n";
                    reporte_mbr += "</tr>\n";
                }
            }
        }
    }

    //REPORTE DE LA PARTICION2
    if(mbr.mbr_particion_2.part_s>0 && (!cadenaVacia(mbr.mbr_particion_2.part_name))){
        reporte_mbr += "<tr><td bgcolor=\"\#8523d6\" ><FONT COLOR=\"white\">PARTICION 2</FONT></td>\n";
        reporte_mbr += "<td bgcolor=\"\#8523d6\" ><FONT COLOR=\"\#8523d6\">a</FONT></td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
        if(lista_particiones_montadas.ParticionMontada(mbr.mbr_particion_2.part_name, particion_reporte.path)){
            reporte_mbr += "<td border=\"1\">1</td>\n";
        }else{
            reporte_mbr += "<td border=\"1\">0</td>\n";
        }
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_type</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + string(1,mbr.mbr_particion_2.part_type) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_fit</td>\n";
        reporte_mbr += "<td border=\"1\">" + string(1,mbr.mbr_particion_2.part_fit) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_start</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + to_string(mbr.mbr_particion_2.part_start) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_size</td>\n";
        reporte_mbr += "<td border=\"1\">" + to_string(mbr.mbr_particion_2.part_s) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_name</td>\n";
        string name_2(mbr.mbr_particion_2.part_name);
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + name_2 + "</td>\n";
        reporte_mbr += "</tr>\n";
    }
    //SI LA PARTICION 2 ES EXTENDIDA
    if(mbr.mbr_particion_2.part_type == 'e' || mbr.mbr_particion_2.part_type == 'E'){
        if(mbr.mbr_particion_2.part_s> 0 && (!cadenaVacia(mbr.mbr_particion_2.part_name))){
            for(int i = 0; i < ebrs.size(); i++){
                if(!cadenaVacia(ebrs[i].part_name)){
                    reporte_mbr += "<tr><td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"white\">PARTICION LÓGICA</FONT></td>\n";
                    reporte_mbr += "<td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"\#ff9f23\">a</FONT></td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
                    if(lista_particiones_montadas.ParticionMontada(ebrs[i].part_name, particion_reporte.path)){
                        reporte_mbr += "<td border=\"1\">1</td>\n";
                    }else{
                        reporte_mbr += "<td border=\"1\">0</td>\n";
                    }
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_fit</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + string(1,ebrs[i].part_fit) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_start</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_start) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_size</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + to_string(ebrs[i].part_s) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_next</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_next) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_name</td>\n";
                    string name_1(ebrs[i].part_name);
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + name_1 + "</td>\n";
                    reporte_mbr += "</tr>\n";
                }
            }
        }
    }

    //REPORTE DE LA PARTICION3
    if(mbr.mbr_particion_3.part_s>0 && (!cadenaVacia(mbr.mbr_particion_3.part_name))){
        reporte_mbr += "<tr><td bgcolor=\"\#8523d6\" ><FONT COLOR=\"white\">PARTICION 3</FONT></td>\n";
        reporte_mbr += "<td bgcolor=\"\#8523d6\" ><FONT COLOR=\"\#8523d6\">a</FONT></td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
        if(lista_particiones_montadas.ParticionMontada(mbr.mbr_particion_3.part_name, particion_reporte.path)){
            reporte_mbr += "<td border=\"1\">1</td>\n";
        }else{
            reporte_mbr += "<td border=\"1\">0</td>\n";
        }
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_type</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + string(1,mbr.mbr_particion_3.part_type) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_fit</td>\n";
        reporte_mbr += "<td border=\"1\" >" + string(1,mbr.mbr_particion_3.part_fit) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_start</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + to_string(mbr.mbr_particion_3.part_start) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_size</td>\n";
        reporte_mbr += "<td border=\"1\">" + to_string(mbr.mbr_particion_3.part_s) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_name</td>\n";
        string name_3(mbr.mbr_particion_3.part_name);
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + name_3 + "</td>\n";
        reporte_mbr += "</tr>\n";
    }
    //SI LA PARTICION 3 ES EXTENDIDA
    if(mbr.mbr_particion_3.part_type == 'e' || mbr.mbr_particion_3.part_type == 'E'){
        if(mbr.mbr_particion_3.part_s> 0 && (!cadenaVacia(mbr.mbr_particion_3.part_name))){
            for(int i = 0; i < ebrs.size(); i++){
                if(!cadenaVacia(ebrs[i].part_name)){
                    reporte_mbr += "<tr><td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"white\">PARTICION LÓGICA</FONT></td>\n";
                    reporte_mbr += "<td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"\#ff9f23\">a</FONT></td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
                    if(lista_particiones_montadas.ParticionMontada(ebrs[i].part_name, particion_reporte.path)){
                        reporte_mbr += "<td border=\"1\">1</td>\n";
                    }else{
                        reporte_mbr += "<td border=\"1\">0</td>\n";
                    }
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_fit</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + string(1,ebrs[i].part_fit) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_start</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_start) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_size</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + to_string(ebrs[i].part_s) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_next</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_next) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_name</td>\n";
                    string name_1(ebrs[i].part_name);
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + name_1 + "</td>\n";
                    reporte_mbr += "</tr>\n";
                }
            }
        }
    }

    //REPORTE DE LA PARTICION4
    if(mbr.mbr_particion_4.part_s>0 && (!cadenaVacia(mbr.mbr_particion_4.part_name))){
        reporte_mbr += "<tr><td bgcolor=\"\#8523d6\" ><FONT COLOR=\"white\">PARTICION 4</FONT></td>\n";
        reporte_mbr += "<td bgcolor=\"\#8523d6\" ><FONT COLOR=\"\#8523d6\">a</FONT></td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
        if(lista_particiones_montadas.ParticionMontada(mbr.mbr_particion_4.part_name, particion_reporte.path)){
            reporte_mbr += "<td border=\"1\">1</td>\n";
        }else{
            reporte_mbr += "<td border=\"1\">0</td>\n";
        }
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_type</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + string(1,mbr.mbr_particion_4.part_type) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_fit</td>\n";
        reporte_mbr += "<td border=\"1\">" + string(1,mbr.mbr_particion_4.part_fit) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_start</td>\n";
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + to_string(mbr.mbr_particion_4.part_start) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\">part_size</td>\n";
        reporte_mbr += "<td border=\"1\">" + to_string(mbr.mbr_particion_4.part_s) + "</td>\n";
        reporte_mbr += "</tr>\n";
        reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#ddcdea\">part_name</td>\n";
        string name_4(mbr.mbr_particion_4.part_name);
        reporte_mbr += "<td border=\"1\" bgcolor=\"\#ddcdea\">" + name_4 + "</td>\n";
        reporte_mbr += "</tr>\n";
    }
    //SI LA PARTICION 4 ES EXTENDIDA
    if(mbr.mbr_particion_4.part_type == 'e' || mbr.mbr_particion_4.part_type == 'E'){
        if(mbr.mbr_particion_4.part_s> 0 && (!cadenaVacia(mbr.mbr_particion_4.part_name))){
            for(int i = 0; i < ebrs.size(); i++){
                if(!cadenaVacia(ebrs[i].part_name)){
                    reporte_mbr += "<tr><td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"white\">PARTICION LÓGICA</FONT></td>\n";
                    reporte_mbr += "<td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"\#ff9f23\">a</FONT></td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
                    if(lista_particiones_montadas.ParticionMontada(ebrs[i].part_name,particion_reporte.path)){
                        reporte_mbr += "<td border=\"1\">1</td>\n";
                    }else{
                        reporte_mbr += "<td border=\"1\">0</td>\n";
                    }
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_fit</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + string(1,ebrs[i].part_fit) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_start</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_start) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_size</td>\n";
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + to_string(ebrs[i].part_s) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\">part_next</td>\n";
                    reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_next) + "</td>\n";
                    reporte_mbr += "</tr>\n";
                    reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_name</td>\n";
                    string name_1(ebrs[i].part_name);
                    reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + name_1 + "</td>\n";
                    reporte_mbr += "</tr>\n";
                }
            }
        }
    }
    reporte_mbr += "</table>>];\n";

    //REPORTE EBR
    if(ebrs.size()>0){
        reporte_mbr += "tablaEBR[label=<\n";
        reporte_mbr += "<table fontname=\"Century Gothic\" border=\"0\" cellspacing=\"0\">\n";
        reporte_mbr += "<tr><td bgcolor=\"\#8523d6\" ><FONT COLOR=\"white\">REPORTE DE EBR</FONT></td>\n";
        reporte_mbr += "<td bgcolor=\"\#8523d6\" ><FONT COLOR=\"\#8523d6\">a</FONT></td>\n";
        reporte_mbr += "</tr>\n";
        for(int i = 0; i < ebrs.size(); i++){
            if(!cadenaVacia(ebrs[i].part_name)){
                reporte_mbr += "<tr><td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"white\">PARTICION "+to_string(i+1)+"</FONT></td>\n";
                reporte_mbr += "<td bgcolor=\"\#ff9f23\" ><FONT COLOR=\"\#ff9f23\">a</FONT></td>\n";
                reporte_mbr += "</tr>\n";
                reporte_mbr += "<tr><td border=\"1\">part_status</td>\n";
                reporte_mbr += "<td border=\"1\">" + string(1,ebrs[i].part_status) + "</td>\n";
                reporte_mbr += "</tr>\n";
                reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_fit</td>\n";
                reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + string(1,ebrs[i].part_fit) + "</td>\n";
                reporte_mbr += "</tr>\n";
                reporte_mbr += "<tr><td border=\"1\">part_start</td>\n";
                reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_start) + "</td>\n";
                reporte_mbr += "</tr>\n";
                reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_size</td>\n";
                reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + to_string(ebrs[i].part_s) + "</td>\n";
                reporte_mbr += "</tr>\n";
                reporte_mbr += "<tr><td border=\"1\">part_next</td>\n";
                reporte_mbr += "<td border=\"1\">" + to_string(ebrs[i].part_next) + "</td>\n";
                reporte_mbr += "</tr>\n";
                reporte_mbr += "<tr><td border=\"1\" bgcolor=\"\#fad6a8\">part_name</td>\n";
                string name_1(ebrs[i].part_name);
                reporte_mbr += "<td border=\"1\" bgcolor=\"\#fad6a8\">" + name_1 + "</td>\n";
                reporte_mbr += "</tr>\n";
            }
        }
        reporte_mbr += "</table>>];\n";
    }
    reporte_mbr += "}\n";

    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');

    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte_mbr;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string path_rep = ruta + "/" + nombre_rep  + ".dot";
    string path_rep2 = ruta + "/" + nombre_rep;

    archivo_reporte_mbr = fopen(path_rep.c_str(),"wt");
    fputs(reporte_mbr.c_str(),archivo_reporte_mbr);
    fclose(archivo_reporte_mbr);

    if(tipo_rep == ".pdf"){
        string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".png"){
        string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".jpg"){
        string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".svg"){
        string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }

    cout  << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte MBR fue creado con éxito \e[m\n" << endl;

    string comando_open = "xdg-open " + reporte->path;
    system(comando_open.c_str());


}

void Rep::ReporteDisk(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n" << endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);

    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);
    fclose(archivo2);

    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    
    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            break;
        }
    }
    string name_disk_path = particion_reporte.path;
    //OBTENER EL NOMBRE DEL ARCHIVO DEL DISCO
    if(particion_reporte.path[0] == '"' && particion_reporte.path[particion_reporte.path.length()-1] == '"'){
        name_disk_path = particion_reporte.path.substr(1,particion_reporte.path.length()-2);
    }

    vector<string> carpetas = split(name_disk_path,'/');

    string name_disk = carpetas[carpetas.size()-1];

    string reporte_dsk = "digraph G {\n";
    reporte_dsk += "\tlabel=\""+name_disk+"\"; fontsize=25; fontname=\"Tilt Neon\";\n" ;
    reporte_dsk += "\tnode [shape=plaintext];\n";
    reporte_dsk += "\tdisco[fontname=\"Tilt Neon\" label=<<TABLE>";
    reporte_dsk += "\t\t<TR>\n\t\t<TD rowspan=\"2\" bgcolor=\"\#ffe74c\">MBR</TD>\n";
    if(mbr.mbr_particion_1.part_s>0){
        if(mbr.mbr_particion_1.part_type == 'p' || mbr.mbr_particion_1.part_type == 'P'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#f3a144\">Primaria<BR/>\n";
        }else if(mbr.mbr_particion_1.part_type == 'e' || mbr.mbr_particion_1.part_type == 'E'){
            reporte_dsk += "\t\t<TD bgcolor=\"\#18aa3b\">Extendida<BR/>\n";
        }else if(mbr.mbr_particion_1.part_type == '\0'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        }
        double porcentaje = (double(mbr.mbr_particion_1.part_s)/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+ porcentaje_fs +"\% del disco</FONT></TD>\n";
        if(mbr.mbr_particion_2.part_s>0 && (mbr.mbr_particion_1.part_s + mbr.mbr_particion_1.part_start) != mbr.mbr_particion_2.part_start){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
            porcentaje = (double(mbr.mbr_particion_2.part_start - (mbr.mbr_particion_1.part_s + mbr.mbr_particion_1.part_start))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
            porcentaje_s.str("");
            porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
            porcentaje_fs = porcentaje_s.str();
            reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+ porcentaje_fs +"\% del disco</FONT></TD>\n";
        }
    }
    if(mbr.mbr_particion_2.part_s>0){
        if(mbr.mbr_particion_2.part_type == 'p' || mbr.mbr_particion_2.part_type == 'P'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#f3a144\">Primaria<BR/>\n";
        }else if(mbr.mbr_particion_2.part_type == 'e' || mbr.mbr_particion_2.part_type == 'E'){
            reporte_dsk += "\t\t<TD bgcolor=\"\#18aa3b\">Extendida<BR/>\n";
        }else if(mbr.mbr_particion_2.part_type == '\0'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        }
        double porcentaje = (double(mbr.mbr_particion_2.part_s)/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
        if(mbr.mbr_particion_3.part_s>0 && (mbr.mbr_particion_2.part_s + mbr.mbr_particion_2.part_start) != mbr.mbr_particion_3.part_start){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
            porcentaje = (double(mbr.mbr_particion_3.part_start - (mbr.mbr_particion_2.part_s + mbr.mbr_particion_2.part_start))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
            porcentaje_s.str("");
            porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
            porcentaje_fs = porcentaje_s.str();
            reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+ porcentaje_fs +"\% del disco</FONT></TD>\n";
        }
    }
    if(mbr.mbr_particion_3.part_s>0){
        if(mbr.mbr_particion_3.part_type == 'p' || mbr.mbr_particion_3.part_type == 'P'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#f3a144\">Primaria<BR/>\n";
        }else if(mbr.mbr_particion_3.part_type == 'e' || mbr.mbr_particion_3.part_type == 'E'){
            reporte_dsk += "\t\t<TD bgcolor=\"\#18aa3b\">Extendida<BR/>\n";
        }else if(mbr.mbr_particion_3.part_type == '\0'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        }
        double porcentaje = (double(mbr.mbr_particion_3.part_s)/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
        if(mbr.mbr_particion_4.part_s>0 && (mbr.mbr_particion_3.part_s + mbr.mbr_particion_3.part_start) != mbr.mbr_particion_4.part_start){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
            porcentaje = (double(mbr.mbr_particion_4.part_start - (mbr.mbr_particion_3.part_s + mbr.mbr_particion_3.part_start))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
            porcentaje_s.str("");
            porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
            porcentaje_fs = porcentaje_s.str();
            reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+ porcentaje_fs +"\% del disco</FONT></TD>\n";
        }
    }
    if(mbr.mbr_particion_4.part_s>0){
        if(mbr.mbr_particion_4.part_type == 'p' || mbr.mbr_particion_4.part_type == 'P'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#f3a144\">Primaria<BR/>\n";
        }else if(mbr.mbr_particion_4.part_type == 'e' || mbr.mbr_particion_4.part_type == 'E'){
            reporte_dsk += "\t\t<TD bgcolor=\"\#18aa3b\">Extendida<BR/>\n";
        }else if(mbr.mbr_particion_4.part_type == '\0'){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        }
        double porcentaje = (double(mbr.mbr_particion_4.part_s)/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
    }
    if(mbr.mbr_particion_1.part_s ==0){
        reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">100\% del disco</FONT></TD>\n";
    }else if(mbr.mbr_particion_2.part_s ==0){
        reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        double porcentaje = (double(mbr.mbr_tamano-(mbr.mbr_particion_1.part_start + mbr.mbr_particion_1.part_s))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
    }else if(mbr.mbr_particion_3.part_s ==0){
        reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        double porcentaje = (double(mbr.mbr_tamano-(mbr.mbr_particion_2.part_start + mbr.mbr_particion_2.part_s))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
    }else if(mbr.mbr_particion_4.part_s ==0){
        reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        double porcentaje = (double(mbr.mbr_tamano-(mbr.mbr_particion_3.part_start + mbr.mbr_particion_3.part_s))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
    }else{
        if((mbr.mbr_tamano-(mbr.mbr_particion_4.part_start + mbr.mbr_particion_4.part_s)) != 0){
            reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
            double porcentaje = (double(mbr.mbr_tamano-(mbr.mbr_particion_4.part_start + mbr.mbr_particion_4.part_s))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
            stringstream porcentaje_s;
            porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
            string porcentaje_fs = porcentaje_s.str();
            reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
        }
    }
    reporte_dsk += "\t</TR>\n";
    if(ebrs.size() > 0){
        reporte_dsk += "\t<TR>\n<TD>\n<TABLE BORDER=\"0\" ORDER=\"0\" CELLBORDER=\"1\" CELLPADDING=\"4\" CELLSPACING=\"0\">";
        reporte_dsk += "\t\t<TR>\n";
        for(int i = 0; i < ebrs.size(); i++){
            if(!cadenaVacia(ebrs[i].part_name)){
                reporte_dsk += "\t\t\t<TD bgcolor=\"\#2fbad3\">EBR</TD>\n";
                double porcentaje = (double(ebrs[i].part_s)/double(mbr.mbr_tamano-sizeof(MBR)))*100;
                stringstream porcentaje_s;
                porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
                string porcentaje_fs = porcentaje_s.str();
                reporte_dsk += "\t\t\t<TD bgcolor=\"\#b9601e\">Lógica<BR/><FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
            }else{
                reporte_dsk += "\t\t\t<TD bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
                double porcentaje = (double(ebrs[i].part_s)/double(mbr.mbr_tamano-sizeof(MBR)))*100;
                stringstream porcentaje_s;
                porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
                string porcentaje_fs = porcentaje_s.str();
                reporte_dsk += "\t\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
            }
        }
        int size_max_ext = 0;
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_type == 'e' || particiones[i].part_type == 'E'){
                size_max_ext = particiones[i].part_start +particiones[i].part_s;
            }
        }
        if((size_max_ext -(ebrs[ebrs.size()-1].part_start + ebrs[ebrs.size()-1].part_s)) != 0){
            reporte_dsk += "\t\t\t<TD bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
            double porcentaje = (double(size_max_ext-(ebrs[ebrs.size()-1].part_start + ebrs[ebrs.size()-1].part_s))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
            stringstream porcentaje_s;
            porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
            string porcentaje_fs = porcentaje_s.str();
            reporte_dsk += "\t\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
        }
        reporte_dsk += "\t\t</TR>\n</TABLE>\n";
        reporte_dsk += "</TD>\n\t</TR>\n";
    }
    reporte_dsk += "</TABLE>>];\n";
    reporte_dsk += "}";
    
    
    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte_disk;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    
    string path_rep = ruta + "/" + nombre_rep  + ".dot";
    string path_rep2 = ruta + "/" + nombre_rep;

    archivo_reporte_disk = fopen(path_rep.c_str(),"wt");
    fputs(reporte_dsk.c_str(),archivo_reporte_disk);
    fclose(archivo_reporte_disk);

    if(tipo_rep == ".pdf"){
        string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".png"){
        string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".jpg"){
        string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".svg"){
        string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }

        cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte DISK fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + reporte->path;
    system(comando_open.c_str());

}

void Rep::ReporteInodo(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);
    string path_princ = reporte->path;
    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);


    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    int inicio_particion = 0;

    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion_reporte.name){
            inicio_particion = particiones[i].part_start;
        }else if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }
    if(inicio_particion == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);
    
    //LEO TODOS LOS INODOS Y LOS GUARDO EN UN VECTOR PARA SU REPORTE
    vector<Inodo> inodos = ListadoInodos(super_bloque.s_inode_start, super_bloque.s_inode_start + (sizeof(Inodo)*super_bloque.s_inodes_count), particion_reporte.path);

    string reporte_inode = "digraph G {\n";
    reporte_inode += "node [shape=plaintext]\n";
    reporte_inode += "rankdir=LR\n";
    reporte_inode += "label=\"Reporte Inode\";\nfontsize=20;";
    int contador_in = 0;
    for(int i = 0; i < inodos.size(); i++){
        reporte_inode += "tablainodo"+to_string(contador_in)+"[label=<\n";
        reporte_inode += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
        reporte_inode += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Inodo</FONT></td>\n";
        reporte_inode += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\">UID</td>\n";
        reporte_inode += "<td border=\"1\">" + to_string(inodos[i].i_uid) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">GID</td>\n";
        reporte_inode += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + to_string(inodos[i].i_gid) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\">Size</td>\n";
        reporte_inode += "<td border=\"1\">" + to_string(inodos[i].i_s) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">aTime</td>\n";
        reporte_inode += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + getFecha(inodos[i].i_atime) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\">cTime</td>\n";
        reporte_inode += "<td border=\"1\">" + getFecha(inodos[i].i_ctime) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">mTIme</td>\n";
        reporte_inode += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + getFecha(inodos[i].i_mtime) + "</td>\n";
        reporte_inode += "</tr>\n";
        for(int j = 0; j < 15; j++){
            if(j%2== 0){
                reporte_inode += "<tr><td border=\"1\">Block "+to_string(j+1)+"</td>\n";
                reporte_inode += "<td border=\"1\">" + to_string(inodos[i].i_block[j]) + "</td>\n";
                reporte_inode += "</tr>\n";
            }else{
                reporte_inode += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Block "+to_string(j+1)+"</td>\n";
                reporte_inode += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + to_string(inodos[i].i_block[j]) + "</td>\n";
                reporte_inode += "</tr>\n";
            }
        }
        reporte_inode += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Type</td>\n";
        reporte_inode += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + string(1,inodos[i].i_type) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "<tr><td border=\"1\">Perm</td>\n";
        reporte_inode += "<td border=\"1\">" + to_string(inodos[i].i_perm) + "</td>\n";
        reporte_inode += "</tr>\n";
        reporte_inode += "</table>>];\n";
        if(i!=inodos.size()-1){
            reporte_inode += "tablainodo"+to_string(contador_in)+"->tablainodo"+to_string(contador_in+1)+";\n";
        }
        contador_in ++;
    }
    reporte_inode += "}";


    fclose(archivo2);
    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string ruta2 = ruta; 
    if(ruta_complex == true){
        ruta2 = path_princ.substr(1,path_princ.length()-2);
        ruta2 = ruta2.substr(0,ruta2.length()-5);
    }
    
    string path_rep = ruta2 + ".dot";
    string path_rep2 = ruta2;
    cout << path_rep << endl;
    archivo_reporte= fopen(path_rep.c_str(),"w");
    fputs(reporte_inode.c_str(),archivo_reporte);
    fclose(archivo_reporte);


    if(tipo_rep == ".pdf"){
        string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".png"){
        string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".jpg"){
        string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".svg"){
        string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }

    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte Inode fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + path_princ;
    system(comando_open.c_str());
}

void Rep::ReporteBloque(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);
    string path_princ = reporte->path;
    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);


    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    int inicio_particion = 0;

    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion_reporte.name){
            inicio_particion = particiones[i].part_start;
        }else if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }
    if(inicio_particion == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);
    
   
    //OBTENCION DE LOS INODOS
    vector<Inodo> inodos = ListadoInodos(super_bloque.s_inode_start, super_bloque.s_inode_start+(super_bloque.s_inodes_count*sizeof(Inodo)), particion_reporte.path);

    string reporte_block = "digraph G {\n";
    reporte_block += "node [shape=plaintext]\n";
    reporte_block += "rankdir=LR\n";
    reporte_block += "label=\"Reporte Block\";\nfontsize=20;";
    int contador_in = 0;
    //REPORTA TODOS LOS BLOQUES DE CARPETA
    for(int i = 0; i < inodos.size(); i++){
        if(inodos[i].i_type == '0'){
            int contador_apuntadores = 0;
            while(contador_apuntadores != 12){
                int apuntador = inodos[i].i_block[contador_apuntadores];
                if(apuntador != -1){
                    BloqueCarpeta bloquec;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquec, sizeof(BloqueCarpeta), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Name</td>\n";
                    reporte_block += "<td border=\"1\" bgcolor=\"\#9dbaf9\"> Inodo </td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\"> . </td>\n";
                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[0].b_inodo) + "</td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\">..</td>\n";
                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[1].b_inodo) + "</td>\n";
                    reporte_block += "</tr>\n";
                    string name_block2="";
                    if(cadenaVacia(bloquec.b_content[2].b_name)){
                        name_block2 = "";
                    }else{
                        string nb(bloquec.b_content[2].b_name);
                        name_block2 = nb;
                    }
                    reporte_block += "<tr><td border=\"1\">"+name_block2+"</td>\n";
                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[2].b_inodo) + "</td>\n";
                    reporte_block += "</tr>\n";
                    string name_block3="";
                    if(cadenaVacia(bloquec.b_content[3].b_name)){
                        name_block3 = "";
                    }else{
                        string nb(bloquec.b_content[3].b_name);
                        name_block3 = nb;
                    }
                    reporte_block += "<tr><td border=\"1\">"+name_block3+"</td>\n";
                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[3].b_inodo) + "</td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                }
                contador_apuntadores ++;
            }
            if(contador_apuntadores == 12){
                int apuntador = inodos[i].i_block[12];
                if(apuntador != -1){
                    BloqueApuntador bloquea;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquea, sizeof(BloqueApuntador), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                    reporte_block += "</tr>\n";
                    for(int j = 0; j < 16; j++){
                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                        reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                        reporte_block += "</tr>\n";
                    }
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                    for(int j = 0; j < 16; j++){
                        int apuntador2 = bloquea.b_pointers[j];
                        if(apuntador2 != -1){
                            BloqueCarpeta bloquec;
                            fseek(archivo2, apuntador2, SEEK_SET);
                            fread(&bloquec, sizeof(BloqueCarpeta), 1, archivo2);
                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Name</td>\n";
                            reporte_block += "<td border=\"1\" bgcolor=\"\#9dbaf9\"> Inodo </td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\"> . </td>\n";
                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[0].b_inodo) + "</td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\">..</td>\n";
                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[1].b_inodo) + "</td>\n";
                            reporte_block += "</tr>\n";
                            string name_block2="";
                            if(cadenaVacia(bloquec.b_content[2].b_name)){
                                name_block2 = "";
                            }else{
                                string nb(bloquec.b_content[2].b_name);
                                name_block2 = nb;
                            }
                            reporte_block += "<tr><td border=\"1\">"+name_block2+"</td>\n";
                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[2].b_inodo) + "</td>\n";
                            reporte_block += "</tr>\n";
                            string name_block3="";
                            if(cadenaVacia(bloquec.b_content[3].b_name)){
                                name_block3 = "";
                            }else{
                                string nb(bloquec.b_content[3].b_name);
                                name_block3 = nb;
                            }
                            reporte_block += "<tr><td border=\"1\">"+name_block3+"</td>\n";
                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[3].b_inodo) + "</td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "</table>>];\n";
                            contador_in ++;
                        }
                    }
                }
                contador_apuntadores ++;
            }else if(contador_apuntadores == 13){
                int apuntador = inodos[i].i_block[13];
                if(apuntador != -1){
                    BloqueApuntador bloquea;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquea, sizeof(BloqueApuntador), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                    reporte_block += "</tr>\n";
                    for(int j = 0; j < 16; j++){
                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                        reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                        reporte_block += "</tr>\n";
                    }
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                    for(int j = 0; j < 16; j++){
                        int apuntador2 = bloquea.b_pointers[j];
                        if(apuntador2 != -1){
                            BloqueApuntador bloquea2;
                            fseek(archivo2, apuntador2, SEEK_SET);
                            fread(&bloquea2, sizeof(BloqueApuntador), 1, archivo2);
                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                            reporte_block += "</tr>\n";
                            for(int k = 0; k < 16; k++){
                                reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                                reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                                reporte_block += "</tr>\n";
                            }
                            reporte_block += "</table>>];\n";
                            contador_in ++;
                            for(int k = 0; k < 16; k++){
                                int apuntador2 = bloquea.b_pointers[k];
                                if(apuntador2 != -1){
                                    BloqueCarpeta bloquec;
                                    fseek(archivo2, apuntador2, SEEK_SET);
                                    fread(&bloquec, sizeof(BloqueCarpeta), 1, archivo2);
                                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Name</td>\n";
                                    reporte_block += "<td border=\"1\" bgcolor=\"\#9dbaf9\"> Inodo </td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "<tr><td border=\"1\"> . </td>\n";
                                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[0].b_inodo) + "</td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "<tr><td border=\"1\">..</td>\n";
                                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[1].b_inodo) + "</td>\n";
                                    reporte_block += "</tr>\n";
                                    string name_block2="";
                                    if(cadenaVacia(bloquec.b_content[2].b_name)){
                                        name_block2 = "";
                                    }else{
                                        string nb(bloquec.b_content[2].b_name);
                                        name_block2 = nb;
                                    }
                                    reporte_block += "<tr><td border=\"1\">"+name_block2+"</td>\n";
                                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[2].b_inodo) + "</td>\n";
                                    reporte_block += "</tr>\n";
                                    string name_block3="";
                                    if(cadenaVacia(bloquec.b_content[3].b_name)){
                                        name_block3 = "";
                                    }else{
                                        string nb(bloquec.b_content[3].b_name);
                                        name_block3 = nb;
                                    }
                                    reporte_block += "<tr><td border=\"1\">"+name_block3+"</td>\n";
                                    reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[3].b_inodo) + "</td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "</table>>];\n";
                                    contador_in ++;
                                }
                            }
                        }
                    }
                }
                contador_apuntadores++;
            }else if(contador_apuntadores == 14){
                int apuntador = inodos[i].i_block[14];
                if(apuntador != -1){
                    BloqueApuntador bloquea;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquea, sizeof(BloqueApuntador), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                    reporte_block += "</tr>\n";
                    for(int j = 0; j < 16; j++){
                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                        reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                        reporte_block += "</tr>\n";
                    }
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                    for(int j = 0; j < 16; j++){
                        int apuntador2 = bloquea.b_pointers[j];
                        if(apuntador2 != -1){
                            BloqueApuntador bloquea2;
                            fseek(archivo2, apuntador2, SEEK_SET);
                            fread(&bloquea2, sizeof(BloqueApuntador), 1, archivo2);
                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                            reporte_block += "</tr>\n";
                            for(int k = 0; k < 16; k++){
                                reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(k+1)+"</td>\n";
                                reporte_block += "<td border=\"1\">" + to_string(bloquea2.b_pointers[k])+"</td>\n";
                                reporte_block += "</tr>\n";
                            }
                            reporte_block += "</table>>];\n";
                            contador_in ++;
                            for(int k = 0; k < 16; k++){
                                int apuntador3 = bloquea2.b_pointers[k];
                                if(apuntador3 != -1){
                                    BloqueApuntador bloquea3;
                                    fseek(archivo2, apuntador3, SEEK_SET);
                                    fread(&bloquea3, sizeof(BloqueApuntador), 1, archivo2);
                                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                                    reporte_block += "</tr>\n";
                                    for(int l = 0; l < 16; l++){
                                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(l+1)+"</td>\n";
                                        reporte_block += "<td border=\"1\">" + to_string(bloquea3.b_pointers[l])+"</td>\n";
                                        reporte_block += "</tr>\n";
                                    }
                                    reporte_block += "</table>>];\n";
                                    contador_in ++;
                                    for(int l = 0; i <16; l++){
                                        int apuntador4 = bloquea3.b_pointers[l];
                                        if(apuntador4 != -1){
                                            BloqueCarpeta bloquec;
                                            fseek(archivo2, apuntador4, SEEK_SET);
                                            fread(&bloquec, sizeof(BloqueCarpeta), 1, archivo2);
                                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                                            reporte_block += "</tr>\n";
                                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Name</td>\n";
                                            reporte_block += "<td border=\"1\" bgcolor=\"\#9dbaf9\"> Inodo </td>\n";
                                            reporte_block += "</tr>\n";
                                            reporte_block += "<tr><td border=\"1\"> . </td>\n";
                                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[0].b_inodo) + "</td>\n";
                                            reporte_block += "</tr>\n";
                                            reporte_block += "<tr><td border=\"1\">..</td>\n";
                                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[1].b_inodo) + "</td>\n";
                                            reporte_block += "</tr>\n";
                                            string name_block2="";
                                            if(cadenaVacia(bloquec.b_content[2].b_name)){
                                                name_block2 = "";
                                            }else{
                                                string nb(bloquec.b_content[2].b_name);
                                                name_block2 = nb;
                                            }
                                            reporte_block += "<tr><td border=\"1\">"+name_block2+"</td>\n";
                                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[2].b_inodo) + "</td>\n";
                                            reporte_block += "</tr>\n";
                                            string name_block3="";
                                            if(cadenaVacia(bloquec.b_content[3].b_name)){
                                                name_block3 = "";
                                            }else{
                                                string nb(bloquec.b_content[3].b_name);
                                                name_block3 = nb;
                                            }
                                            reporte_block += "<tr><td border=\"1\">"+name_block3+"</td>\n";
                                            reporte_block += "<td border=\"1\">" + to_string(bloquec.b_content[3].b_inodo) + "</td>\n";
                                            reporte_block += "</tr>\n";
                                            reporte_block += "</table>>];\n";
                                            contador_in ++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                contador_apuntadores++;
            }
        }else if(inodos[i].i_type == '1'){
            int contador_apuntadores = 0;
            while(contador_apuntadores != 12){
                int apuntador = inodos[i].i_block[contador_apuntadores];
                if(apuntador != -1){
                    BloqueArchivo bloquear;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquear, sizeof(BloqueArchivo), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Archivo</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Contenido</td>\n";
                    string contenido(bloquear.b_content);
                    reporte_block += "<td border=\"1\">"+contenido+"</td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                }
                contador_apuntadores ++;
            }
            if(contador_apuntadores == 12){
                int apuntador = inodos[i].i_block[12];
                if(apuntador != -1){
                    BloqueApuntador bloquea;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquea, sizeof(BloqueApuntador), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                    reporte_block += "</tr>\n";
                    for(int j = 0; j < 16; j++){
                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                        reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                        reporte_block += "</tr>\n";
                    }
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                    for(int j = 0; j < 16; j++){
                        int apuntador2 = bloquea.b_pointers[j];
                        if(apuntador2 != -1){
                            BloqueArchivo bloquear;
                            fseek(archivo2, apuntador, SEEK_SET);
                            fread(&bloquear, sizeof(BloqueArchivo), 1, archivo2);
                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Archivo</FONT></td>\n";
                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Contenido</td>\n";
                            string contenido(bloquear.b_content);
                            reporte_block += "<td border=\"1\">"+contenido+"</td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "</table>>];\n";
                            contador_in ++;
                        }
                    }
                }
                contador_apuntadores ++;
            }else if(contador_apuntadores == 13){
                int apuntador = inodos[i].i_block[13];
                if(apuntador != -1){
                    BloqueApuntador bloquea;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquea, sizeof(BloqueApuntador), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                    reporte_block += "</tr>\n";
                    for(int j = 0; j < 16; j++){
                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                        reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                        reporte_block += "</tr>\n";
                    }
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                    for(int j = 0; j < 16; j++){
                        int apuntador2 = bloquea.b_pointers[j];
                        if(apuntador2 != -1){
                            BloqueApuntador bloquea2;
                            fseek(archivo2, apuntador2, SEEK_SET);
                            fread(&bloquea2, sizeof(BloqueApuntador), 1, archivo2);
                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                            reporte_block += "</tr>\n";
                            for(int k = 0; k < 16; k++){
                                reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                                reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                                reporte_block += "</tr>\n";
                            }
                            reporte_block += "</table>>];\n";
                            contador_in ++;
                            for(int k = 0; k < 16; k++){
                                int apuntador2 = bloquea.b_pointers[k];
                                if(apuntador2 != -1){
                                    BloqueArchivo bloquear;
                                    fseek(archivo2, apuntador, SEEK_SET);
                                    fread(&bloquear, sizeof(BloqueArchivo), 1, archivo2);
                                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Archivo</FONT></td>\n";
                                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Contenido</td>\n";
                                    string contenido(bloquear.b_content);
                                    reporte_block += "<td border=\"1\">"+contenido+"</td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "</table>>];\n";
                                    contador_in ++;
                                }
                            }
                        }
                    }
                }
                contador_apuntadores++;
            }else if(contador_apuntadores == 14){
                int apuntador = inodos[i].i_block[14];
                if(apuntador != -1){
                    BloqueApuntador bloquea;
                    fseek(archivo2, apuntador, SEEK_SET);
                    fread(&bloquea, sizeof(BloqueApuntador), 1, archivo2);
                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                    reporte_block += "</tr>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                    reporte_block += "</tr>\n";
                    for(int j = 0; j < 16; j++){
                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(j+1)+"</td>\n";
                        reporte_block += "<td border=\"1\">" + to_string(bloquea.b_pointers[j])+"</td>\n";
                        reporte_block += "</tr>\n";
                    }
                    reporte_block += "</table>>];\n";
                    contador_in ++;
                    for(int j = 0; j < 16; j++){
                        int apuntador2 = bloquea.b_pointers[j];
                        if(apuntador2 != -1){
                            BloqueApuntador bloquea2;
                            fseek(archivo2, apuntador2, SEEK_SET);
                            fread(&bloquea2, sizeof(BloqueApuntador), 1, archivo2);
                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                            reporte_block += "</tr>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                            reporte_block += "</tr>\n";
                            for(int k = 0; k < 16; k++){
                                reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(k+1)+"</td>\n";
                                reporte_block += "<td border=\"1\">" + to_string(bloquea2.b_pointers[k])+"</td>\n";
                                reporte_block += "</tr>\n";
                            }
                            reporte_block += "</table>>];\n";
                            contador_in ++;
                            for(int k = 0; k < 16; k++){
                                int apuntador3 = bloquea2.b_pointers[k];
                                if(apuntador3 != -1){
                                    BloqueApuntador bloquea3;
                                    fseek(archivo2, apuntador3, SEEK_SET);
                                    fread(&bloquea3, sizeof(BloqueApuntador), 1, archivo2);
                                    reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                                    reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                                    reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Carpeta</FONT></td>\n";
                                    reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                                    reporte_block += "</tr>\n";
                                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Apuntador</td>\n";
                                    reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Bloque/Inodo</td>\n";
                                    reporte_block += "</tr>\n";
                                    for(int l = 0; l < 16; l++){
                                        reporte_block += "<tr><td border=\"1\">Apuntador"+to_string(l+1)+"</td>\n";
                                        reporte_block += "<td border=\"1\">" + to_string(bloquea3.b_pointers[l])+"</td>\n";
                                        reporte_block += "</tr>\n";
                                    }
                                    reporte_block += "</table>>];\n";
                                    contador_in ++;
                                    for(int l = 0; i <16; l++){
                                        int apuntador4 = bloquea3.b_pointers[l];
                                        if(apuntador4 != -1){
                                            BloqueArchivo bloquear;
                                            fseek(archivo2, apuntador, SEEK_SET);
                                            fread(&bloquear, sizeof(BloqueArchivo), 1, archivo2);
                                            reporte_block += "tablabloque"+to_string(contador_in)+"[label=<\n";
                                            reporte_block += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
                                            reporte_block += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Bloque Archivo</FONT></td>\n";
                                            reporte_block += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">"+to_string(contador_in)+"</FONT></td>\n";
                                            reporte_block += "</tr>\n";
                                            reporte_block += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Contenido</td>\n";
                                            string contenido(bloquear.b_content);
                                            reporte_block += "<td border=\"1\">"+contenido+"</td>\n";
                                            reporte_block += "</tr>\n";
                                            reporte_block += "</table>>];\n";
                                            contador_in ++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                contador_apuntadores++;
            }
        }     
    }
    for(int i = 0; i < contador_in; i++){
        if(i != contador_in-1){
            reporte_block += "tablabloque"+to_string(i)+"->tablabloque"+to_string(i+1)+";\n";
        }
    }
    reporte_block += "}";

    fclose(archivo2);
    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string ruta2 = ruta; 
    if(ruta_complex == true){
        ruta2 = path_princ.substr(1,path_princ.length()-2);
        ruta2 = ruta2.substr(0,ruta2.length()-5);
    }
    
    string path_rep = ruta2 + ".dot";
    string path_rep2 = ruta2;
    cout << path_rep << endl;
    archivo_reporte= fopen(path_rep.c_str(),"w");
    fputs(reporte_block.c_str(),archivo_reporte);
    fclose(archivo_reporte);


    if(tipo_rep == ".pdf"){
        string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".png"){
        string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".jpg"){
        string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".svg"){
        string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }

    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte Block fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + path_princ;
    system(comando_open.c_str());
}

void Rep::ReporteBMInodo(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);
    string path_princ = reporte->path;
    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }
    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);


    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    int inicio_particion = 0;

    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion_reporte.name){
            inicio_particion = particiones[i].part_start;
        }else if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }
    if(inicio_particion == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }
    
    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);
    string reporte_txt = "";
    string reporte_bm_inodo = "digraph G{\n";
    reporte_bm_inodo += "node [shape=plaintext]\n";
    reporte_bm_inodo += "rankdir=LR\n";
    reporte_bm_inodo += "label = \"Bitmap Inodo\"\n";
    reporte_bm_inodo += "bminodo [shape=none, margin=0, label=<\n";
    reporte_bm_inodo += "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    reporte_bm_inodo += "<TR>\n";
    reporte_bm_inodo += "<TD COLSPAN=\"50\" BGCOLOR=\"\#000000\"><FONT COLOR=\"white\"><B>BITMAP INNODOS</B></FONT></TD>\n";
    reporte_bm_inodo += "</TR>\n";
    int contador = 0;
    int contador2 = super_bloque.s_bm_inode_start;
    int cfinal = super_bloque.s_bm_inode_start + (super_bloque.s_inodes_count*sizeof(char));
    while(contador < cfinal){
        int contador3 = 0;
        reporte_bm_inodo += "<TR>\n";
        while(contador3 < 20){
            cout << "CONTADOR: " << contador << endl;
            cout << "CONTADOR2: " << contador2 << endl;
            cout << "CONTADOR3: " << contador3 << endl;
            char caracter;
            fseek(archivo2, contador2, SEEK_SET);
            fread(&caracter, sizeof(char), 1, archivo2);
            cout << "CARACTER: " << caracter << endl;
            if(caracter == '1'){
                reporte_txt += "1";
                reporte_bm_inodo += "<TD>1</TD>\n";
            }else if(caracter == '0'){
                reporte_txt += "0";
                reporte_bm_inodo += "<TD>0</TD>\n";
            }
            cout << "CARACTER: " << caracter << endl;
            contador++;
            contador2 += sizeof(char);
            contador3++;
            cout << "CONTADOR: " << contador << endl;
            cout << "CONTADOR2: " << contador2 << endl;
            cout << "CONTADOR3: " << contador3 << endl;
            reporte_txt +=" ";
        }
        reporte_txt += "\n";
        reporte_bm_inodo += "</TR>\n";
    }
    reporte_bm_inodo += "</TABLE>\n";
    reporte_bm_inodo += ">];\n";
    reporte_bm_inodo += "}";
    cout << reporte_bm_inodo << endl;
    fclose(archivo2);
    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string ruta2 = ruta; 
    if(ruta_complex == true){
        ruta2 = path_princ.substr(1,path_princ.length()-2);
        ruta2 = ruta2.substr(0,ruta2.length()-5);
    }
    if(tipo_rep == ".txt"){
        string path_rep = ruta2 + ".txt";
        string path_rep2 = ruta2;
        cout << path_rep << endl;
        archivo_reporte= fopen(path_rep.c_str(),"w");
        fputs(reporte_txt.c_str(),archivo_reporte);
        fclose(archivo_reporte);
    }else{
        string path_rep = ruta2 + ".dot";
        string path_rep2 = ruta2;
        cout << path_rep << endl;
        archivo_reporte= fopen(path_rep.c_str(),"w");
        fputs(reporte_bm_inodo.c_str(),archivo_reporte);
        fclose(archivo_reporte);

        if(tipo_rep == ".pdf"){
            string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }else if(tipo_rep == ".png"){
            string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }else if(tipo_rep == ".jpg"){
            string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }else if(tipo_rep == ".svg"){
            string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }
    }
    
    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte de BitMap de Innodos fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + path_princ;
    system(comando_open.c_str());
}

void Rep::ReporteBMBloque(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);
    string path_princ = reporte->path;
    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);


    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    int inicio_particion = 0;

    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion_reporte.name){
            inicio_particion = particiones[i].part_start;
        }else if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }
    if(inicio_particion == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);
    string reporte_txt = "";
    string reporte_bm_bloque = "digraph G{\n";
    reporte_bm_bloque += "node [shape=plaintext]\n";
    reporte_bm_bloque += "rankdir=LR\n";
    reporte_bm_bloque += "label = \"Bitmap Inodo\"\n";
    reporte_bm_bloque += "bminodo [shape=none, margin=0, label=<\n";
    reporte_bm_bloque += "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    reporte_bm_bloque += "<TR>\n";
    reporte_bm_bloque += "<TD COLSPAN=\"50\" BGCOLOR=\"\#000000\"><FONT COLOR=\"white\"><B>BITMAP BLOQUES</B></FONT></TD>\n";
    reporte_bm_bloque += "</TR>\n";

    int contador = 0;
    int contador2 = super_bloque.s_bm_block_start;
    int cfinal = super_bloque.s_bm_block_start+ super_bloque.s_blocks_count;
    while(contador < cfinal){
        int contador3 = 0;
        reporte_bm_bloque += "<TR>\n";
        while(contador3 < 20){
            char caracter;
            fseek(archivo2, contador2, SEEK_SET);
            fread(&caracter, sizeof(char), 1, archivo2);
            if(caracter == '1'){
                reporte_txt += "1";
                reporte_bm_bloque += "<TD>1</TD>\n";
            }else{
                reporte_txt += "0";
                reporte_bm_bloque += "<TD>1</TD>\n";
            }
            contador++;
            contador2+= sizeof(char);
            contador3++;
            reporte_txt +=" ";
        }
        reporte_txt += "\n";
        reporte_bm_bloque += "</TR>\n";
    }
    reporte_bm_bloque += "</TABLE>\n";
    reporte_bm_bloque += ">];\n";
    reporte_bm_bloque += "}";

    fclose(archivo2);
    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string ruta2 = ruta; 
    if(ruta_complex == true){
        ruta2 = path_princ.substr(1,path_princ.length()-2);
        ruta2 = ruta2.substr(0,ruta2.length()-5);
    }
    if(tipo_rep == ".txt"){
        string path_rep = ruta2 + ".txt";
        string path_rep2 = ruta2;
        cout << path_rep << endl;
        archivo_reporte= fopen(path_rep.c_str(),"w");
        fputs(reporte_txt.c_str(),archivo_reporte);
        fclose(archivo_reporte);
    }else{
        string path_rep = ruta2 + ".dot";
        string path_rep2 = ruta2;
        cout << path_rep << endl;
        archivo_reporte= fopen(path_rep.c_str(),"w");
        fputs(reporte_bm_bloque.c_str(),archivo_reporte);
        fclose(archivo_reporte);


        if(tipo_rep == ".pdf"){
            string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }else if(tipo_rep == ".png"){
            string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }else if(tipo_rep == ".jpg"){
            string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }else if(tipo_rep == ".svg"){
            string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
            system(comando_dot.c_str());
        }
    }

    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte de BitMap de Bloques fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + path_princ;
    system(comando_open.c_str());
}

void Rep::ReporteSuperBloque(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);
    string path_princ = reporte->path;
    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);


    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    int inicio_particion = 0;

    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion_reporte.name){
            inicio_particion = particiones[i].part_start;
        }else if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }
    if(inicio_particion == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);
    fclose(archivo2);

    string reporte_sb = "digraph G {\n";
    reporte_sb += "node [shape=plaintext]\n";
    reporte_sb += "label=\"Reporte de SuperBloque\";\n";
    reporte_sb += "tablambr[label=<\n";
    reporte_sb += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
    reporte_sb += "<tr><td bgcolor=\"\#0d7236\" ><FONT COLOR=\"white\">REPORTE DE SUPERBLOQUE</FONT></td>\n";
    reporte_sb += "<td bgcolor=\"\#0d7236\" ><FONT COLOR=\"\#0d7236\">a</FONT></td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_filesystem_type</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_filesystem_type) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_inodes_count</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_inodes_count) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_blocks_count</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_blocks_count) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_free_blocks_count</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_free_blocks_count) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_free_inodes_count</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_free_inodes_count) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_mtime</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + getFecha(super_bloque.s_mtime) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_umtime</td>\n";
    reporte_sb += "<td border=\"1\">" + getFecha(super_bloque.s_umtime) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_mnt_count</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_mnt_count) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_magic</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_magic) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_inode_s</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_inode_s) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_block_s</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_block_s) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_firts_ino</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_first_ino) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_first_blo</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_first_blo) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_bm_inode_start</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_bm_inode_start) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_bm_block_start</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_bm_block_start) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\" bgcolor=\"\#94ffc0\">s_inode_start</td>\n";
    reporte_sb += "<td border=\"1\" bgcolor=\"\#94ffc0\">" + to_string(super_bloque.s_inode_start) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "<tr><td border=\"1\">s_block_start</td>\n";
    reporte_sb += "<td border=\"1\">" + to_string(super_bloque.s_block_start) + "</td>\n";
    reporte_sb += "</tr>\n";
    reporte_sb += "</table>>];\n";
    reporte_sb += "}";

    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string ruta2 = ruta; 
    if(ruta_complex == true){
        ruta2 = path_princ.substr(1,path_princ.length()-2);
        ruta2 = ruta2.substr(0,ruta2.length()-5);
    }
    
    string path_rep = ruta2 + ".dot";
    string path_rep2 = ruta2;
    cout << path_rep << endl;
    archivo_reporte= fopen(path_rep.c_str(),"w");
    fputs(reporte_sb.c_str(),archivo_reporte);
    fclose(archivo_reporte);


    if(tipo_rep == ".pdf"){
        string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".png"){
        string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".jpg"){
        string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".svg"){
        string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }

    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte de SuperBloque fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + path_princ;
    system(comando_open.c_str());
}

void Rep::ReporteTree(Rep* reporte){

}

void Rep::ReporteJournaling(Rep* reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);
    string path_princ = reporte->path;
    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el disco \e[m\n" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);


    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    int inicio_particion = 0;

    vector<EBR> ebrs;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_name == particion_reporte.name){
            inicio_particion = particiones[i].part_start;
        }else if(particiones[i].part_type == 'e'|| particiones[i].part_type == 'E'){
            ebrs = ListadoEBR(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }
    if(inicio_particion == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado la particion con el id: " << reporte->id << "\e[m\n"<< endl;
        return;
    }

    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);

    if(super_bloque.s_filesystem_type != 3){
        cout << "\e[1;31m[ERROR]:\e[1;37m El sistema de archivos que contiene esta partición no es de tipo EXT3 \e[m\n" << endl;
        return;
    }

    int inicio_journaling = inicio_particion + sizeof(SuperBloque);
    int fin_journaling = inicio_journaling + (super_bloque.s_inodes_count * sizeof(Journaling));

    vector<Journaling> journalings = ListadoJournaling(inicio_journaling,fin_journaling, particion_reporte.path);
    string reporte_journaling = "digraph G{\n";
    reporte_journaling += "node [shape=plaintext]\n";
    reporte_journaling += "rankdir=LR\n";
    reporte_journaling += "label = \"Reporte Journaling\"\n";
    reporte_journaling += "journaling [shape=none, margin=0, label=<\n";
    reporte_journaling += "<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";
    reporte_journaling += "<TR><TD COLSPAN=\"50\" BGCOLOR=\"\#02c5f9\"><FONT COLOR=\"white\"><B>JOURNALING</B></FONT></TD></TR>\n";
    reporte_journaling += "<TR>\n";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">ID</TD>";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">Acción</TD>";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">Tipo</TD>";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">Nombre</TD>";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">Archivo Destino</TD>";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">Contenido</TD>";
    reporte_journaling += "<TD BGCOLOR=\"\#b2efff\">Fecha</TD>";
    reporte_journaling += "</TR>\n";
    for(int i = 0; i < journalings.size(); i++){
        reporte_journaling += "<TR>\n";
        reporte_journaling += "<TD>" + to_string(i+1) + "</TD>";
        string accion(journalings[i].accion);
        reporte_journaling += "<TD>" + accion + "</TD>";
        string tipo(journalings[i].tipo);
        reporte_journaling += "<TD>" + tipo + "</TD>";
        string nombre(journalings[i].nombre);
        reporte_journaling += "<TD>" + nombre + "</TD>";
        string destino="";
        if(cadenaVacia(journalings[i].destino)){
            destino = "";
        }else{
            string de(journalings[i].destino);
            destino = de;
        }
        reporte_journaling += "<TD>" + destino + "</TD>";
        string contenido="";
        if(cadenaVacia(journalings[i].contenido)){
            contenido = "";
        }else{
            string co(journalings[i].contenido);
            contenido = co;
        }
        reporte_journaling += "<TD>" + contenido + "</TD>";
        reporte_journaling += "<TD>" + getOnlyFecha(journalings[i].fecha) + "</TD>";
        reporte_journaling += "</TR>\n";
    }
    reporte_journaling += "</table>\n";
    reporte_journaling += ">];\n";
    reporte_journaling += "}";

    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    string ruta = "";
    if(path_temp[0] == '/' && ruta_complex == false){
        ruta = "/";
    }else if(path_temp[0] == '/' && ruta_complex == true){
        ruta = "\"/";
    }
    
    for(int i = 0; i < carpetas_rep.size()-1; ++i){
        if(carpetas_rep[i]!= ""){
            ruta += carpetas_rep[i] + "/";
        }
    }
    if(ruta_complex == true){
        ruta += "\"";
    }
    string comando_linux = "mkdir -p " + ruta;
    system(comando_linux.c_str());

    //CREACION DEL ARCHIVO
    FILE *archivo_reporte;
    string nombre_rep = carpetas_rep[carpetas_rep.size()-1].substr(0,carpetas_rep[carpetas_rep.size()-1].length()-4);

    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());

    string ruta2 = ruta; 
    if(ruta_complex == true){
        ruta2 = path_princ.substr(1,path_princ.length()-2);
        ruta2 = ruta2.substr(0,ruta2.length()-5);
    }
    
    string path_rep = ruta2 + ".dot";
    string path_rep2 = ruta2;
    cout << path_rep << endl;
    archivo_reporte= fopen(path_rep.c_str(),"w");
    fputs(reporte_journaling.c_str(),archivo_reporte);
    fclose(archivo_reporte);


    if(tipo_rep == ".pdf"){
        string comando_dot = "dot -Tpdf " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".png"){
        string comando_dot = "dot -Tpng " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".jpg"){
        string comando_dot = "dot -Tjpg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }else if(tipo_rep == ".svg"){
        string comando_dot = "dot -Tsvg " + path_rep + " -o " + reporte->path;
        system(comando_dot.c_str());
    }

    cout << "\e[1;32m [SUCCESS]: \e[1;37m El Reporte de Journaling fue generado con exito \e[m\n" << endl;

    string comando_open = "xdg-open " + path_princ;
    system(comando_open.c_str());
}

vector<EBR> Rep::ListadoEBR(Particion extendida, string path){
    vector<EBR> ebrs;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int temp = extendida.part_start;
    while(temp != -1){
        cout << "temp: " << temp << endl;
        fseek(archivo,temp,SEEK_SET);
        EBR ebr;
        fread(&ebr,sizeof(EBR),1,archivo);
        if(!cadenaVacia(ebr.part_name)){
            ebrs.push_back(ebr);
        }else if(cadenaVacia(ebr.part_name) && ebr.part_s != 0){
            ebrs.push_back(ebr);
        }else{
            break;
        }
        temp = ebr.part_next;
    }
    fclose(archivo);
    return ebrs;
}

vector <Inodo> Rep:: ListadoInodos(int inicio, int final, string path){
    vector <Inodo> inodos;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int pos = inicio;
    while(pos < final){
        fseek(archivo,pos,SEEK_SET);
        Inodo inodo;
        fread(&inodo,sizeof(Inodo),1,archivo);
        if(inodo.i_uid != -1 && inodo.i_gid != -1 && inodo.i_type != '\0'){
            inodos.push_back(inodo);
        }
        pos += sizeof(Inodo);
    }
    fclose(archivo);
    return inodos;
}

vector <BloqueArchivo> Rep::ListadoBA(int inicio, int final, string path){
    vector <BloqueArchivo> bas;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int pos = inicio;
    while(pos < final){
        fseek(archivo,pos,SEEK_SET);
        BloqueArchivo ba;
        fread(&ba,sizeof(BloqueArchivo),1,archivo);
        if(typeid(ba) == typeid(BloqueArchivo) && !cadenaVacia(ba.b_content)){
            bas.push_back(ba);
        }
        pos += sizeof(BloqueArchivo);
    }
    fclose(archivo);
    return bas;
}

vector <BloqueCarpeta> Rep::ListadoBC(int inicio,int final, string path){
    vector <BloqueCarpeta> bcs;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int pos = inicio;
    while(pos < final){
        fseek(archivo,pos,SEEK_SET);
        BloqueCarpeta bc;
        fread(&bc,sizeof(BloqueCarpeta),1,archivo);
        if(typeid(bc) == typeid(BloqueCarpeta) && bc.b_content[0].b_inodo != 0 && !cadenaVacia(bc.b_content[0].b_name) && bc.b_content[1].b_inodo != 0 && !cadenaVacia(bc.b_content[1].b_name)){
            bcs.push_back(bc);
        }
        pos += sizeof(BloqueCarpeta);
    }
    fclose(archivo);
    return bcs;
}

vector<BloqueApuntador> Rep::ListadoBAp(int inicio, int final, string path){
    vector <BloqueApuntador> baps;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int pos = inicio;
    while(pos < final){
        fseek(archivo,pos,SEEK_SET);
        BloqueApuntador ba;
        fread(&ba,sizeof(BloqueApuntador),1,archivo);
        if(typeid(ba) == typeid(BloqueApuntador) && ba.b_pointers[0] != 0){
            baps.push_back(ba);
        }
        pos += sizeof(BloqueApuntador);
    }
    fclose(archivo);
    return baps;
}

bool Rep::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

vector<string> Rep::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Rep::getFecha(time_t fecha){
    time_t date = fecha;
    char time_string[100];
    strftime(time_string, sizeof(time_string), "%d/%m/%Y %H:%M:%S", localtime(&date));
    string final_date(time_string);
    return final_date;
}

vector<Journaling> Rep::ListadoJournaling(int inicio, int final, string path){
    vector <Journaling> journalings;
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    int pos = inicio;
    while(pos < final){
        fseek(archivo,pos,SEEK_SET);
        Journaling journaling;
        fread(&journaling,sizeof(Journaling),1,archivo);
        if(!cadenaVacia(journaling.accion)){
            journalings.push_back(journaling);
        }
        pos += sizeof(Journaling);
    }
    fclose(archivo);
    return journalings;
}

string Rep::getOnlyFecha(time_t fecha){
    time_t date = fecha;
    char time_string[100];
    strftime(time_string, sizeof(time_string), "%d/%m/%Y", localtime(&date));
    string final_date(time_string);
    return final_date;
}

string Rep::dottree(int posicion, string dot, string path){
    FILE *archivo;
    archivo = fopen(path.c_str(),"rb+");
    fseek(archivo,posicion,SEEK_SET);
    Inodo inode;
    fread(&inode,sizeof(Inodo),1,archivo);
    dot += "nodo" + to_string(posicion) + " [label=<";
    dot += "<table fontname=\"Quicksand\" border=\"0\" cellspacing=\"0\">\n";
    dot += "<tr><td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"white\">Inodo</FONT></td>\n";
    dot += "<td bgcolor=\"\#0f3fa5\" ><FONT COLOR=\"\#0f3fa5\">a</FONT></td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\">UID</td>\n";
    dot += "<td border=\"1\">" + to_string(inode.i_uid) + "</td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">GID</td>\n";
    dot += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + to_string(inode.i_gid) + "</td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\">Size</td>\n";
    dot += "<td border=\"1\">" + to_string(inode.i_s) + "</td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">aTime</td>\n";
    dot += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + getFecha(inode.i_atime) + "</td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\">cTime</td>\n";
    dot += "<td border=\"1\">" + getFecha(inode.i_ctime) + "</td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">mTIme</td>\n";
    dot += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + getFecha(inode.i_mtime) + "</td>\n";
    dot += "</tr>\n";
    for(int j = 0; j < 15; j++){
        if(j%2== 0){
            dot += "<tr><td border=\"1\">Block "+to_string(j+1)+"</td>\n";
            dot += "<td border=\"1\">" + to_string(inode.i_block[j]) + "</td>\n";
            dot += "</tr>\n";
        }else{
            dot += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Block "+to_string(j+1)+"</td>\n";
            dot += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + to_string(inode.i_block[j]) + "</td>\n";
            dot += "</tr>\n";
        }
    }
    dot += "<tr><td border=\"1\" bgcolor=\"\#9dbaf9\">Type</td>\n";
    dot += "<td border=\"1\" bgcolor=\"\#9dbaf9\">" + string(1,inode.i_type) + "</td>\n";
    dot += "</tr>\n";
    dot += "<tr><td border=\"1\">Perm</td>\n";
    dot += "<td border=\"1\">" + to_string(inode.i_perm) + "</td>\n";
    dot += "</tr>\n";
    dot += "</table>>];\n";
    for(int i = 0; i <15;i++){
        if(inode.i_block[i] != -1){
            if(i < 12){
                if(inode.i_type == '0'){
                    dot += "";
                }
            }
        }
    }
}
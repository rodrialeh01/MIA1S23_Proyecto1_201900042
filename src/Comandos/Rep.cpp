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
    
}

void Rep::ReporteBMInodo(Rep *reporte){
    
}

void Rep::ReporteBMBloque(Rep *reporte){
    
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
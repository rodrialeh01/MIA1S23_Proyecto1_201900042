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
        cout << "ERROR: No se ha ingresado el id del disco" << endl;
        return;
    }

    if(reporte->path == ""){
        cout << "ERROR: No se ha ingresado la ruta del reporte" << endl;
        return;
    }

    if (toLowerCase(reporte->name) == "mbr"){
        ReporteMBR(reporte);
    }else if (toLowerCase(reporte->name) == "disk"){
        ReporteDisk(reporte);
    }else{
        cout << "ERROR: El reporte no existe" << endl;
    }
}

void Rep::ReporteMBR(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "ERROR: No se ha encontrado la particion con el id: " << reporte->id << endl;
        return;
    }





}

void Rep::ReporteDisk(Rep *reporte){
    if(!lista_particiones_montadas.ExisteParticion(reporte->id)){
        cout << "ERROR: No se ha encontrado la particion con el id: " << reporte->id << endl;
        return;
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(reporte->id);

    cout << "Path: " << particion_reporte.path << endl;

    FILE *archivo2;
    archivo2 = fopen(particion_reporte.path.c_str(), "rb+");
    if(archivo2 == NULL){
        cout << "ERROR: No se ha encontrado el disco" << endl;
        return;
    }

    MBR mbr;
    fseek(archivo2, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo2);
    fclose(archivo2);

    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};
    for(int i = 0; i < particiones.size(); i++){
        cout << "Particion " << i+1 << endl;
    }
    
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

    cout << "Name_disk_path: " << name_disk_path << endl;
    cout << "Name_disk: " << name_disk << endl;

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
        cout << "Porcentaje2: " << porcentaje << endl;
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
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
        cout << "Porcentaje3: " << porcentaje << endl;
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
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
        cout << "Porcentaje4: " << porcentaje << endl;
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
    }
    if(mbr.mbr_particion_1.part_s ==0){
        reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">100\% del disco<FONT/></TD>\n";
    }else if(mbr.mbr_particion_2.part_s ==0){
        reporte_dsk += "\t\t<TD rowspan=\"2\" bgcolor=\"\#a2a2a2\">Libre<BR/>\n";
        double porcentaje = (double(mbr.mbr_tamano-(mbr.mbr_particion_1.part_start + mbr.mbr_particion_1.part_s))/double(mbr.mbr_tamano-sizeof(MBR)))*100;
        stringstream porcentaje_s;
        porcentaje_s << std::fixed << std::setprecision(2) << porcentaje;
        string porcentaje_fs = porcentaje_s.str();
        reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco<FONT/></TD>\n";
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
            cout << "PorcentajeLibre: " << porcentaje << endl;
            reporte_dsk += "\t\t<FONT POINT-SIZE=\"10\">"+porcentaje_fs+"\% del disco</FONT></TD>\n";
        }
    }
    reporte_dsk += "\t</TR>\n";
    if(ebrs.size() > 0){
        reporte_dsk += "\t<TR>\n<TD>\n<TABLE BORDER=\"0\" ORDER=\"0\" CELLBORDER=\"1\" CELLPADDING=\"4\" >";
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
    cout << reporte_dsk << endl;
    
    
    //GENERANDO EL ARCHIVO DE REPORTE
    //VALIDACION Y CREACION DE CARPETAS 
    bool ruta_complex = false;
    if(reporte->path[0] == '"' && reporte->path[reporte->path.length()-1] == '"'){
        ruta_complex = true;
        reporte->path = reporte->path.substr(1,reporte->path.length()-2);
    }


    string path_temp =  reporte->path;
    vector<string> carpetas_rep = split(reporte->path,'/');
    //VERIFICA SI EXISTE EL ARCHIVO
    FILE *archivo;
    if((archivo = fopen(reporte->path.c_str(),"rb"))){
        cout << "El disco con el nombre " << carpetas_rep[carpetas_rep.size()-1] << " ya existe" << endl;
        fclose(archivo);
        return;
    }
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
    cout << "Nombre del archivo: " << nombre_rep << endl;
    string tipo_rep = carpetas_rep[carpetas_rep.size()-1].substr(carpetas_rep[carpetas_rep.size()-1].length()-4,carpetas_rep[carpetas_rep.size()-1].length());
    cout << "Con extensión: " << tipo_rep << endl;
    
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

    string comando_open = "xdg-open " + reporte->path;
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
#include "Cat.h"

Cat::Cat(){
}

void Cat::LeerArchivo(Cat*cat){
    string file = cat->file;
    if(file==""){
        cout << "\e[1;31m[ERROR]:\e[1;37m No ha agregado el nombre del archivo \e[m\n" << endl;
        return;
    }
    if(file[0] == '\"'){
        file = file.substr(1,file.length()-2);
    }

    Nodo particion_reporte = lista_particiones_montadas.obtenerNodoParticion(idlogueado);
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
            ebrs = ListadoEBRS(particiones[i], particion_reporte.path);
            for(int j = 0; j < ebrs.size(); j++){
                if(ebrs[j].part_name == particion_reporte.name){
                    inicio_particion = ebrs[j].part_start;
                    break;
                }
            }
            break;
        }
    }

    vector<string> carpetas_rep_file = split(file,'/');
    string name_file = carpetas_rep_file[carpetas_rep_file.size()-1];
    fseek(archivo2, inicio_particion, SEEK_SET);
    SuperBloque super_bloque;
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo2);
    
    //LEO TODOS LOS INODOS Y LOS GUARDO EN UN VECTOR PARA SU REPORTE
    vector<Inodo> inodos = ListadoInodos(super_bloque.s_inode_start, super_bloque.s_inode_start + (sizeof(Inodo)*super_bloque.s_inodes_count), particion_reporte.path);

    //RECORRO TODOS LOS INODOS PARA ENCONTRAR EL QUE CONTIENE LA RUTA
    bool encontrado = false;
    int pos_inodo = 0;
    for(int i = 0; i < inodos.size(); i++){
        if(inodos[i].i_type == '0'){
            BloqueCarpeta bloque_carpeta;
            fseek(archivo2, inodos[i].i_block[0], SEEK_SET);
            fread(&bloque_carpeta, sizeof(BloqueCarpeta), 1, archivo2);
            for(int j = 2; j < 4; j++){
                if(bloque_carpeta.b_content[j].b_name == name_file){
                    encontrado = true;
                    pos_inodo = bloque_carpeta.b_content[j].b_inodo;
                    break;
                }
            }
        }
    }
    if(encontrado == false && pos_inodo == 0){
        cout << "\e[1;31m[ERROR]:\e[1;37m No se ha encontrado el archivo con la ruta: " << file << "\e[m\n"<< endl;
        return;
    }

    fseek(archivo2, pos_inodo, SEEK_SET);
    Inodo inodo;
    fread(&inodo, sizeof(Inodo), 1, archivo2);
    string contenido = "";
    for(int i = 0; i < 12; i++){
        if(inodo.i_block[i] != -1){
            BloqueArchivo bloque_archivo;
            fseek(archivo2, inodo.i_block[i], SEEK_SET);
            fread(&bloque_archivo, sizeof(BloqueArchivo), 1, archivo2);
            contenido += bloque_archivo.b_content;
        }
    }

    fclose(archivo2);

    cout << "\e[1;34m[CONTENIDO]:\e[1;37m \n" << contenido << "\e[m\n"<< endl;
}

vector<EBR> Cat::ListadoEBRS(Particion extendida, string path){
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

bool Cat::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

vector<string> Cat::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Cat::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}

vector <Inodo> Cat:: ListadoInodos(int inicio, int final, string path){
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
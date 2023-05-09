#include "Login.h"

Login::Login(){
}

void Login::IniciarSesion(Login *login){
    string user = login->user;
    string password = login->password;
    string id = login->id;
    if(user[0]== '\"' && user[user.size()-1] == '\"'){
        user = user.substr(1, user.size()-2);
    }
    if(password[0]== '\"' && password[password.size()-1] == '\"'){
        password = password.substr(1, password.size()-2);
    }
    if(id[0]== '\"' && id[id.size()-1] == '\"'){
        id = id.substr(1, id.size()-2);
    }

    //OBTIENE LA PARTICION
    if(lista_particiones_montadas.ExisteParticion(id) == false){
        cout << "\e[1;31m[ERROR]:\e[1;37m No existe la particion con el id: " << id << "\e[m\n" << endl;
        return;
    }
    Nodo particion = lista_particiones_montadas.obtenerNodoParticion(id);

    //OBTIENE EL MBR
    FILE *archivo;
    archivo = fopen(particion.path.c_str(), "rb+");
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    vector<Particion> particiones = {mbr.mbr_particion_1, mbr.mbr_particion_2, mbr.mbr_particion_3, mbr.mbr_particion_4};


    //VERIFICA SI LA PARTICION A FORMATEAR ES EXTENDIDA Y SI ES LA QUE SE QUIERE FORMATEAR O SINO QUE VERIFIQUE SI ES UNA PARTICION LOGICA
    vector<EBR> ebrs;
    EBR particion_logica;
    bool logica_existe = false;
    for(int i = 0; i < particiones.size(); i++){
        if(particiones[i].part_type == 'e' || particiones[i].part_type == 'E'){
            if(particiones[i].part_name == particion.name){
                cout << "\e[1;31m[ERROR]:\e[1;37m No se puede formatear una particion extendida \e[m\n" << endl;
                return;
            }else{
                ebrs = ListadoEBRS(particiones[i], particion.path);
                for(int j = 0; j < ebrs.size(); j++){
                    if(ebrs[j].part_name == particion.name){
                        particion_logica = ebrs[j];
                        logica_existe = true;
                        break;
                    }
                }
            }
        }
    }

    int pos_inicio;
    int pos_fin;
    if(logica_existe){
        pos_inicio = particion_logica.part_start + sizeof(EBR);
        pos_fin = particion_logica.part_start + particion_logica.part_s;
    }else{
        for(int i = 0; i < particiones.size(); i++){
            if(particiones[i].part_name == particion.name){
                pos_inicio = particiones[i].part_start;
                pos_fin = particiones[i].part_start + particiones[i].part_s;
                break;
            }
        }
    }

    //OBTIENE EL SUPERBLOQUE
    SuperBloque super_bloque;
    fseek(archivo, pos_inicio, SEEK_SET);
    fread(&super_bloque, sizeof(SuperBloque), 1, archivo);

    //OBTIENE LA POSICION DEL INODO
    int pos_inodo = super_bloque.s_inode_start + sizeof(Inodo);
    Inodo inodo;
    fseek(archivo, pos_inodo, SEEK_SET);
    fread(&inodo, sizeof(Inodo), 1, archivo);

    //OBTIENE LA POSICION DEL BLOQUE
    string usuariostxt = "";
    //APUNTADORES DIRECTOS
    for(int i = 0; i < 12; i++){
        int no_bloque = inodo.i_block[i];
        if(no_bloque == -1){
            break;
        }
        BloqueArchivo bloque;
        fseek(archivo, no_bloque, SEEK_SET);
        fread(&bloque, sizeof(BloqueArchivo), 1, archivo);
        usuariostxt += bloque.b_content;
    }
    
    fclose(archivo);
    
    //OBTIENE TODOS LOS USUARIOS
    vector<string> usuarios_grupos;
    usuarios_grupos = split(usuariostxt, '\n');
    for(int i = 0; i < usuarios_grupos.size(); i++){
        vector<string> datos;
        datos = split(usuarios_grupos[i], ',');
        if(datos[1] == "U"){
            if(datos[3] == user){
                if(datos[4] == password){
                    if(logueado == false){
                        logueado = true;
                        userlogueado = datos[3];
                        idlogueado = id;
                        cout << "\e[1;32m [SUCCESS]: \e[1;37m Se ha iniciado sesion con el usuario: " << datos[3] << "\e[m\n" << endl;
                        return;
                    }else{
                        cout << "\e[1;31m[ERROR]:\e[1;37m Ya hay una sesion iniciada \e[m\n" << endl;
                        return;
                    }
                }else{
                    cout << "\e[1;31m[ERROR]:\e[1;37m Autenticación fallida \e[m\n" << endl;
                    return;
                }
            }
        }
    }
    cout << "\e[1;31m[ERROR]:\e[1;37m No se encontro el usuario \e[m\n" << endl;

}

vector<EBR> Login::ListadoEBRS(Particion extendida, string path){
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

bool Login::cadenaVacia(char cadena[]){
    for(int i = 0; i < 16; i++) {
        if(cadena[i] != '\0') {
            return false; 
        }
    }
   return true;
}

vector<string> Login::split(string texto, char parametro) {
    stringstream text_to_split(texto);
    string text2;
    vector<string> resultado;
    while(getline(text_to_split,text2,parametro)){
        resultado.push_back(text2);
    }
    return resultado;
}

string Login::toLowerCase(string palabra){
    int i = 0;
    string retorno = "";
    while(i<palabra.length()){
        retorno += tolower(palabra[i]);
        i++;
    }
    return retorno;
}
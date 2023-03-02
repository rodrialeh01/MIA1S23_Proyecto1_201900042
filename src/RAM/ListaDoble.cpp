#include "ListaDoble.h"

ListaDoble lista_particiones_montadas; 

ListaDoble::ListaDoble(){
    primero = NULL;
    ultimo = NULL;
    longitud = 0;
}

void ListaDoble::Insertar(string path, string name, string id, char type){
    Nodo* nuevo = new Nodo();
    nuevo->path = path;
    nuevo->name = name;
    nuevo->id = id;
    nuevo->type = type;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    if(primero == NULL){
        primero = nuevo;
        ultimo = nuevo;
    }else{
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
    longitud++;
}

void ListaDoble::Mostrar(){
    cout << "========== LAS PARTICIONES QUE SE ENCUENTRAN MONTADAS SON ==========" << endl;
    Nodo* aux = primero;
    while(aux != NULL){
        cout << "Id: " << aux->id << endl;
        cout << "---------------------------------------------------------------" << endl;
        aux = aux->siguiente;
    }
}

void ListaDoble::Eliminar(string id){
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->id == id){
            if(aux == primero){
                primero = primero->siguiente;
                primero->anterior = NULL;
            }else if(aux == ultimo){
                ultimo = ultimo->anterior;
                ultimo->siguiente = NULL;
            }else{
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
            }
            delete aux;
            longitud--;
            break;
        }
        aux = aux->siguiente;
    }
}

Nodo ListaDoble::obtenerNodoParticion(string id){
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->id == id){
            return *aux;
        }
        aux = aux->siguiente;
    }
    return *aux;
}


int ListaDoble::CrearNoParticion(string path){
    int numero = 1;
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->path == path){
            numero++;
        }
        aux = aux->siguiente;
    }
    return numero;
}

bool ListaDoble::ExisteID(string id){
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->id == id){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

string ListaDoble::getPath(string id){
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->id == id){
            return aux->path;
        }
        aux = aux->siguiente;
    }
    return "";
}

string ListaDoble::getName(string id){
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->id == id){
            return aux->name;
        }
        aux = aux->siguiente;
    }
    return "";
}

bool ListaDoble::ExisteParticion(string id){
    Nodo* aux = primero;
    while(aux != NULL){
        if(aux->id == id){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}
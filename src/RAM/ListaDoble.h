#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

using namespace std;

struct Nodo{
    string path = "";
    string name = "";
    string id = "";
    char type = '\0';
    Nodo* siguiente;
    Nodo* anterior;
};

class ListaDoble {
    private:
        Nodo* primero;
        Nodo* ultimo;
        int longitud;

    public:
        ListaDoble();

        void Insertar(string path, string name, string id, char type);
        void Mostrar();
        void Eliminar(string id);
        Nodo obtenerNodoParticion(string id);
        int CrearNoParticion(string path);
        bool ExisteID(string id);
        string getPath(string id);
        string getName(string id);
        bool ExisteParticion(string id);
};

#endif
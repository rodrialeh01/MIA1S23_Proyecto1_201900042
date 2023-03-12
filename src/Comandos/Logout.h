
#ifndef LOGOUT_H
#define LOGOUT_H

#include "vector"
#include "string"
#include "sstream"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include "../Estructuras.h"

using namespace std;

extern bool logueado;
extern string userlogueado;

class Logout {
    public:
        Logout();
        void CerrarSesion(Logout *logout);
};

#endif
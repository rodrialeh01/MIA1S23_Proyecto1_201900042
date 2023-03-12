#include "Logout.h"

Logout::Logout(){
}

void Logout::CerrarSesion(Logout *logout){
    
    if(logueado == true){
        logueado = false;
        userlogueado = "";
        cout << "\e[1;32m [SUCCESS]: \e[1;37m Se ha cerrado sesión correctamente" << "\e[m\n" << endl;
    }else{
        cout << "\e[1;31m[ERROR]:\e[1;37m No hay ningun usuario logueado \e[m\n" << endl;
    }

}
#include <stdio.h>
#include <string>
#include "./analizador/driver.h"
using namespace std;

int main() {
    string comando = "";
    cout << "\e[1;36m===============================================================\e[m"<<endl;
    cout << "\e[1;36m= UNIVERSIDAD DE SAN CARLOS DE GUATEMALA                      =\e[m"<<endl;
    cout << "\e[1;36m= MANEJO E IMPLEMENTACIÓN DE ARCHIVOS                         =\e[m"<<endl;
    cout << "\e[1;36m= SECCIÓN B                                                   =\e[m"<<endl;
    cout << "\e[1;36m=                          PROYECTO 1                         =\e[m"<<endl;
    cout << "\e[1;36m= NOMBRE: RODRIGO ALEJANDRO HERNÁNDEZ DE LEÓN                 =\e[m"<<endl;
    cout << "\e[1;36m= CARNET: 201900042                                           =\e[m"<<endl;
    cout << "\e[1;36m===============================================================\e[m"<<endl;
    do{
        Driver driver;
        cout << "_______________________________________________________________"<<endl;
        cout << "Ingresa un comando: \n- ";
        getline(cin, comando);
        cout << endl;
        if(comando!= "exit") {
            driver.parse(comando);
        }else{
            break;
        }
    }while(comando!="exit");
	return 0;
}
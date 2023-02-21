#include <stdio.h>
#include <string>
#include "./analizador/driver.h"
using namespace std;

int main() {
    string comando = "";
    cout << "==============================================================="<<endl;
    cout << "= MANEJO E IMPLEMENTACIÓN DE ARCHIVOS                         ="<<endl;
    cout << "= SECCIÓN B                                                   ="<<endl;
    cout << "=                          PROYECTO 1                         ="<<endl;
    cout << "= NOMBRE: RODRIGO ALEJANDRO HERNÁNDEZ DE LEÓN                 ="<<endl;
    cout << "= CARNET: 201900042                                           ="<<endl;
    do{
        Driver driver;
        cout << "_______________________________________________________________"<<endl;
        cout << "Ingresa un comando: \n- ";
        getline(cin, comando);
        if(comando!= "exit") {
            driver.parse(comando);
        }else{
            break;
        }
    }while(comando!="exit");
	return 0;
}
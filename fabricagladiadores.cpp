#include "fabricagladiadores.h"
#include "gladiador.h"
#include <iostream>

using namespace std;

FabricaGladiadores::FabricaGladiadores(int cant) {
    for (int i=0; i<cant; i++){
        Gladiador* gladiador = new Gladiador;
        gladiador->setProba_sup_nextgen(1);
        cout<< "Se ha creado el gladiador: "<< i+1 <<endl;
    }
}

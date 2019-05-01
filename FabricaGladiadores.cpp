//
// Created by jose on 30/04/19.
//

#include "FabricaGladiadores.h"
#include "Gladiador.h"

FabricaGladiadores::FabricaGladiadores(int cant) {
    for (int i; i>0; i++){
        Gladiador* gladiador = new Gladiador;
        gladiador->setProba_sup_nextgen(1);
    }
}

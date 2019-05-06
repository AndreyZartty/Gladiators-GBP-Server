#include <iostream>
#include "Juego.h"


/**
 * Main del programa
 * @since 30/04/19
 */
int main() {

    cout << "Testing\n" << endl;

    Juego* juego = new Juego();

    juego->getCuadricula()->printTorres();

    juego->getCuadricula()->calculateHeuristic();

    juego->getCuadricula()->print();

    juego->doAStar();

    //juego->getCuadricula()->print();





    return 0;
}
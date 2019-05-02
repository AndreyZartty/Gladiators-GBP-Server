
#ifndef GLADIATORS_GBP_JUEGO_H
#define GLADIATORS_GBP_JUEGO_H


#include "Gladiador.h"
#include "Cuadricula.h"
#include "AStar.h"

class Juego {
private:
    Cuadricula cuadricula;
    Gladiador gladiador1;
    Gladiador gladiador2;

    vector<int> towerIdList;
    AStar* aStarAlgorithm;

public:
    Juego();

};


#endif //GLADIATORS_GBP_JUEGO_H

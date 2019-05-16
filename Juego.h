
#ifndef GLADIATORS_GBP_JUEGO_H
#define GLADIATORS_GBP_JUEGO_H


#include "Gladiador.h"
#include "poblacion.h"
#include "Cuadricula.h"
#include "AStar.h"
#include "Backtracking.h"

class Juego {
private:

    Cuadricula* cuadricula;
    AStar* aStarAlgorithm;
    Backtracking* backtrackingAlgorithm;
    Node* nodoInicio;
    Node* nodoFinal;

    Poblacion *poblacion1;
    Poblacion *poblacion2;

    Gladiador* gladiador1;
    Gladiador* gladiador2;


public:

    ///Constructor
    Juego();

    ///Metodos
    void doAStar();
    void doBacktracking();
    void generateTowers();

    ///Getters & Setters
    Cuadricula* getCuadricula();
    void setCuadricula(Cuadricula* _cuadricula);
    AStar* getAStarAlgorithm();
    void setAStarAlgorithm(AStar* _aStarAlgorithm);
    Backtracking* getBacktrackingAlgorithm();
    void setBacktrackingAlgorithm(Backtracking* _backtrackingAlgorithm);
    Gladiador* getGladiador1();
    Gladiador* getGladiador2();
    void setGladiador1(Gladiador* _gladiador1);
    void setGladiador2(Gladiador* _gladiador2);

    Poblacion* getPoblacion1();
    Poblacion* getPoblacion2();

};


#endif //GLADIATORS_GBP_JUEGO_H
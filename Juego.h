
#ifndef GLADIATORS_GBP_JUEGO_H
#define GLADIATORS_GBP_JUEGO_H


#include "Gladiador.h"
#include "Cuadricula.h"
#include "AStar.h"
#include "Backtracking.h"

class Juego {
private:
    Cuadricula* cuadricula;
    AStar* aStarAlgorithm;
    Backtracking* backtrackingAlgorithm;


    Gladiador* gladiador1;
    Gladiador* gladiador2;

    Node* nodoInicio;
    Node* nodoFinal;




public:
    ///Constructor
    Juego();

    ///Metodos
    void doAStar();
    void doBacktracking();

    ///Getters & Setters
    Cuadricula* getCuadricula();
    void setCuadricula(Cuadricula* _cuadricula);
    AStar* getAStarAlgorithm();
    void setAStarAlgorithm(AStar* _aStarAlgorithm);
    Backtracking* getBacktrackingAlgorithm();
    void setBacktrackingAlgorithm(Backtracking* _backtrackingAlgorithm);
    void reasignarTorres();


};


#endif //GLADIATORS_GBP_JUEGO_H
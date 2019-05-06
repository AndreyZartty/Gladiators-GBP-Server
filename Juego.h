
#ifndef GLADIATORS_GBP_JUEGO_H
#define GLADIATORS_GBP_JUEGO_H


#include "Gladiador.h"
#include "Cuadricula.h"
#include "AStar.h"

class Juego {
private:
    Cuadricula* cuadricula;
    AStar* aStarAlgorithm;

    Gladiador* gladiador1;
    Gladiador* gladiador2;

    Node* nodoInicio;
    Node* nodoFinal;




public:
    ///Constructor
    Juego();

    ///Metodos
    void doAStar();


    ///Getters & Setters
    Cuadricula* getCuadricula();
    void setCuadricula(Cuadricula* _cuadricula);
    AStar* getAStarAlgorithm();
    void setAStarAlgorithm(AStar* _aStarAlgorithm);



};


#endif //GLADIATORS_GBP_JUEGO_H
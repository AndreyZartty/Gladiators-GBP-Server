
#include "Juego.h"

/**
 * Representa el Juego
 *
 * @since 30/04/19
 */


/**
 * Constructor de Juego
 */
Juego::Juego() {

    cuadricula = new Cuadricula();

    nodoInicio = cuadricula->getNode(0,0);
    nodoFinal = cuadricula->getNode(cuadricula->getSize() - 1, cuadricula->getSize() - 1);

    aStarAlgorithm = new AStar(cuadricula);


}


///Metodos



void Juego::doAStar() {
    cuadricula->calculateHeuristic();
    aStarAlgorithm->n_findPath(nodoInicio, nodoFinal);
}


///Getters & Setters


/**
 * Getter de Cuadricula de Juego.
 * @return Cuadricula
 */
Cuadricula* Juego::getCuadricula() {
    return cuadricula;
}

/**
 * Setter de Cuadricula de Juego.
 * @param _cuadricula
 */
void Juego::setCuadricula(Cuadricula* _cuadricula) {
    cuadricula = _cuadricula;
}

/**
 * Getter de aStarAlgorithm de Juego.
 * @return A*
 */
AStar* Juego::getAStarAlgorithm(){
    return aStarAlgorithm;
}

/**
 * Setter de aStarAlgorithm de Juego.
 * @param _aStarAlgorithm
 */
void Juego::setAStarAlgorithm(AStar* _aStarAlgorithm) {
    aStarAlgorithm = _aStarAlgorithm;
}


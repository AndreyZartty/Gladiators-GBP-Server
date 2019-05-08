
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

    backtrackingAlgorithm = new Backtracking(cuadricula);


}


///Metodos


/**
 * Inicia el algoritmo A*
 */
void Juego::doAStar() {
    aStarAlgorithm->n_findPath(nodoInicio, nodoFinal);
}

void Juego::doBacktracking() {
    backtrackingAlgorithm->findPath(nodoInicio,nodoFinal);
    //backtrackingAlgorithm->printVector("pathToGoal");
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

/**
 * Getter del backtrackingAlgorithm de Juego.
 * @return _backtrackingAlgorithm
 */
Backtracking* Juego::getBacktrackingAlgorithm() {
    return backtrackingAlgorithm;
}

/**
 * Setter del backtrackingAlgorithm de Juego.
 * @param _backtrackingAlgorithm
 */
void Juego::setBacktrackingAlgorithm(Backtracking* _backtrackingAlgorithm) {
    backtrackingAlgorithm = _backtrackingAlgorithm;
}



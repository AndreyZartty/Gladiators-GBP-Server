
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
    nodoInicio = cuadricula->getNodoInicial();
    nodoFinal = cuadricula->getNodoFinal();
    aStarAlgorithm = new AStar(cuadricula);
    backtrackingAlgorithm = new Backtracking(cuadricula);

}


///Metodos


/**
 * Inicia el algoritmo A*
 */
void Juego::doAStar() {
    aStarAlgorithm->findPath(nodoInicio, nodoFinal);
}

/**
 * Inicia el algoritmo Backtracking
 */
void Juego::doBacktracking() {
    backtrackingAlgorithm->findPath(nodoInicio,nodoFinal);
}

/**
 * Inicia ambos algoritmos y previamente establece todas sus condiciones de inicio
 */
void Juego::doAlgorithms() {

    cout << "Doing Algorithms\n" << endl;

    ///Genera las Torres
    cuadricula->generateTowers();
    ///Calcula el Heuristico para el A*
    //cuadricula->calculateHeuristic();

    ///Imprime solo las torres
    cuadricula->printTorres();

    ///Repone los booleans del A*
    aStarAlgorithm->setInitializedStartGoal(false);
    aStarAlgorithm->setFoundGoal(false);

    ///Repone los booleans del Backtracking
    backtrackingAlgorithm->setInitializedStartGoal(false);
    backtrackingAlgorithm->setFoundGoal(false);

    ///Hace el algortimo A*
    doAStar();

    ///Hace el algoritmo Backtracking
    doBacktracking();

    ///Verificacion de si el algortimo A* ha sido completado
    if ( aStarAlgorithm->isFoundGoal() ) {
        cout << "A* Completed" << endl;
    } else {
        cout << "A* Failed" << endl;
    }

    ///Verificacion de si el algortimo Backtracking ha sido completado
    if (backtrackingAlgorithm->isFoundGoal()) {
        cout << "Backtracking Completed" << endl;
    } else {
        cout << "Backtracking Failed" << endl;
    }

    ///Imprime los caminos
    cuadricula->printTorres();

    return;

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


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
    cuadricula->addPosibleTowerIdList();
    nodoInicio = cuadricula->getNodoInicial();
    nodoFinal = cuadricula->getNodoFinal();
    aStarAlgorithm = new AStar(cuadricula);
    backtrackingAlgorithm = new Backtracking(cuadricula);

    ///Poblaciones
    //poblacion1 = new Poblacion("Lannister");
    //poblacion2 = new Poblacion("Stark");

    //cuadricula->generateFirstTowers();

}


///Metodos


/**
 * Inicia el algoritmo A*
 */
void Juego::doAStar() {
    //aStarAlgorithm->setInitializedStartGoal(false);
    //aStarAlgorithm->setFoundGoal(false);
    aStarAlgorithm->findPath(nodoInicio, nodoFinal);
}

/**
 * Inicia el algoritmo Backtracking
 */
void Juego::doBacktracking() {
    //backtrackingAlgorithm->setInitializedStartGoal(false);
    //backtrackingAlgorithm->setFoundGoal(false);
    backtrackingAlgorithm->findPath(nodoInicio,nodoFinal);

}

/**
 * Inicia ambos algoritmos y previamente establece todas sus condiciones de inicio
 */
void Juego::doAlgorithms() {

    cout << "Doing Algorithms\n" << endl;

    ///Se crea un contador
    int c = 0;

    ///Cantidad de Torres
    int ct = 50;

    while (c < ct) {

        //aStarAlgorithm = new AStar(cuadricula);
        //backtrackingAlgorithm = new Backtracking(cuadricula);

        ///Genera las Torres
        int evaluatingTower = cuadricula->newTower();

        ///Se evalua si hay mas posibilidades para colocar torres
        if (evaluatingTower == -1) {
            cout << "No se pueden asignar mas torres" << endl;
            c=ct;
        }
        else {

            ///Imprime solo las torres
            cuadricula->printTorres();

            for (int i = 0 ; i < cuadricula->getSize() ; i++) {
                for (int j = 0 ; j < cuadricula->getSize() ; j++) {

                    int id = ((i) * (cuadricula->getSize()) + (j));

                    cuadricula->getNode(id)->setInAStarPath(false);
                    cuadricula->getNode(id)->setInBacktrackingPath(false);

                }

            }

            ///Repone los booleans del A*
            aStarAlgorithm->setInitializedStartGoal(false);
            aStarAlgorithm->setFoundGoal(false);

            ///Repone los booleans del Backtracking
            //backtrackingAlgorithm->setInitializedStartGoal(false);
            //backtrackingAlgorithm->setFoundGoal(false);

            ///Hace el algortimo A*
            doAStar();
            aStarAlgorithm->showPath();

            ///Hace el algoritmo Backtracking
            doBacktracking();
            //backtrackingAlgorithm->showPath();

            ///Verificacion de si el algortimo A* ha sido completado
            if (aStarAlgorithm->isFoundGoal()) {
                if (backtrackingAlgorithm->isFoundGoal()) {
                    cout << "Backtracking Completed" << endl;
                    c++;
                } else {

                    ///Rechaza la torre evaluada
                    cout << "Backtracking Failed" << endl;
                    cout << "La torre de id "<< evaluatingTower << " bloquea el camino" << endl;
                    cuadricula->addToVerifiedNot(evaluatingTower);
                    cuadricula->deleteTower(evaluatingTower);

                }
                cout << "A* Completed" << endl;
            } else {
                ///Rechaza la torre evaluada
                cout << "A* Failed" << endl;
                cout << "La torre de id "<< evaluatingTower << " bloquea el camino" << endl;
                cuadricula->addToVerifiedNot(evaluatingTower);
                cuadricula->deleteTower(evaluatingTower);
            }

            ///Repone los booleans del A*
            //aStarAlgorithm->setInitializedStartGoal(false);
            //aStarAlgorithm->setFoundGoal(false);

            ///Repone los booleans del Backtracking
            //backtrackingAlgorithm->setInitializedStartGoal(false);
            //backtrackingAlgorithm->setFoundGoal(false);

            ///Verificacion de si el algortimo Backtracking ha sido completado




        }

    }

    cuadricula->resetVerifiedNot();

    ///Imprime los caminos
    cuadricula->printTorres();

    ///IMPRIMIR VECTOR DE TORRES
    cout << "Tower Id's: ";
    for (int i = 0; i < cuadricula->getTowerIdList().size(); i++) {

        if (i == 0) {
            cout << "[" << cuadricula->getTowerIdList()[i] << ", ";
        } else if (i == cuadricula->getTowerIdList().size() - 1) {
            cout << cuadricula->getTowerIdList()[i] << "]\n" << endl;
        } else {
            cout << cuadricula->getTowerIdList()[i] << ", ";
        }

    }

    ///IMPRIMIR VECTOR DE POSIBLES TORRES

    cout << "PosibleTower Id's: ";
    for (int i = 0; i < cuadricula->getPosibleTowerIdList().size(); i++) {

        if (i == 0) {
            cout << "[" << cuadricula->getPosibleTowerIdList()[i] << ", ";
        } else if (i == cuadricula->getPosibleTowerIdList().size() - 1) {
            cout << cuadricula->getPosibleTowerIdList()[i] << "]\n" << endl;
        } else {
            cout << cuadricula->getPosibleTowerIdList()[i] << ", ";
        }

    }

    if (ct == cuadricula->getTowerIdList().size()) {

        cout << "Completed every tower";

    } else {

    }


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

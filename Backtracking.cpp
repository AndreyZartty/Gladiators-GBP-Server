
#include "Backtracking.h"


/**
 * Representación de Backtracking
 *
 * @since 06/05/19
 */


///Constructor


/**
 * Constructor de Backtracking.
 * @param _cuadricula
 */
Backtracking::Backtracking(Cuadricula*_cuadricula) {

    cuadricula = _cuadricula;
    towerIdList = cuadricula->getTowerIdList();
    initializedStartGoal = false;
    foundGoal = false;

}


///Métodos


/**
 * Buscará el camino entre dos Nodes por medio del algoritmo Backtracking.
 * @param currentPosition
 * @param targetPosition
 */
void Backtracking::findPath(Node* currentPosition, Node* targetPosition) {

    ///En la primera iteracion
    if (!initializedStartGoal) {

        cout << " [Starting Backtracking]";

        ///Limpia pathToGoal
        pathToGoal.clear();

        ///Limpia fullPath
        fullPath.clear();

        ///Ingresa cero como estado inicial a las variables de TODOS los Nodes
        for (int i = 0 ; i < cuadricula->getSize() ; i++) {
            for (int j = 0 ; j < cuadricula->getSize() ; j++) {

                int id = ((i) * (cuadricula->getSize()) + (j));

                cuadricula->getNode(id)->setInBacktrackingPath(false);

            }

        }

        ///Instancia el nodo start y el goal
        startNode = currentPosition;
        goalNode = targetPosition;

        ///Agregar el primer nodo al Path
        pathToGoal.push_back(currentPosition->getId());

        ///Hace el boolean true para saber que ya comenzó
        setInitializedStartGoal(true);

    }

    ///Para continuar el algoritmo
    if (initializedStartGoal)  {
        if ( continuePath(currentPosition) ) {
            return;
        }

    }

}

/**
 * Continua el paso del algoritmo
 * @param currentPosition
 * @return
 */
bool Backtracking::continuePath(Node* currentPosition) {

    fullPath.push_back(currentPosition->getId());

    ///Cuando llega al deseado
    if (currentPosition->getId() == goalNode->getId()) {

        pathToGoal.push_back(currentPosition->getId());
        currentPosition->setInBacktrackingPath(true);

        setFoundGoal(true);
        return true;

    }

    ///Si se encuentra dentro de la cuadricula
    if ( currentPosition->getId() < ( (cuadricula->getSize())*(cuadricula->getSize()) + (cuadricula->getSize()) )
        && currentPosition->getTorre() == nullptr) {

        if (currentPosition->getFila() + 1 < cuadricula->getSize()) {

            Node* nextNodeFila = cuadricula->getNode(currentPosition->getFila() + 1, currentPosition->getColumna());

            if ( continuePath(nextNodeFila) ) {

                pathToGoal.push_back(currentPosition->getId());
                currentPosition->setInBacktrackingPath(true);

                setFoundGoal(true);
                return true;

            }

        }

        if (currentPosition->getColumna() + 1 < 10) {

            Node* nextNodeColumna = cuadricula->getNode(currentPosition->getFila(), currentPosition->getColumna() + 1 );

            if ( continuePath(nextNodeColumna) ) {

                pathToGoal.push_back(currentPosition->getId());
                currentPosition->setInBacktrackingPath(true);

                setFoundGoal(true);
                return true;

            }

            fullPath.push_back(currentPosition->getId());

        }

    }

    ///Si no esta dentro de la cuadricula
    setFoundGoal(false);
    return false;

}


/**
 * Imprime el vector deseado
 * @param list
 */
void Backtracking::printVector(string list) {

    cout << "\n" << list << endl;

    if (list == "pathToGoal") {
        for (int i = 0; i < pathToGoal.size(); i++) {

            cout << pathToGoal[i] << endl;

        }
    }

    if (list == "fullPath") {
        for (int i = 0; i < fullPath.size(); i++) {

            cout << fullPath[i] << " ";

        }
    }

    cout << "\n" << endl;

}


/**
 * Muestra y retorna el path de Backtracking.
 * @return path
 */
vector<int> Backtracking::showPath() {
    printVector("pathToGoal");
    return pathToGoal;
}


///Getters & Setters


/**
 * Setter de initializedStartGoal de Backtracking.
 * @param _initializedStartGoal
 */
void Backtracking::setInitializedStartGoal(bool _initializedStartGoal) {
    initializedStartGoal = _initializedStartGoal;
}

/**
 * Getter de pathToGoal de Backtracking.
 * @return pathToGoal
 */
vector<int> Backtracking::getPathToGoal() {
    return pathToGoal;
}

/**
 * Getter del fullPath de Backtracking.
 * @return
 */
vector<int> Backtracking::getFullPath() {
    return fullPath;
}

/**
 * Getter de foundGoal de Backtracking.
 * @return bool
 */
bool Backtracking::isFoundGoal() {
    return foundGoal;
}

/**
 * Setter de foundGoal de Backtracking.
 * @param _foundGoal
 */
void Backtracking::setFoundGoal(bool _foundGoal) {
    foundGoal = _foundGoal;
}

/**
 * Setter de la cuadricula de Backtracking.
 * @param _cuadricula
 */
void Backtracking::setCuadricula(Cuadricula *_cuadricula) {
    cuadricula = _cuadricula;
}

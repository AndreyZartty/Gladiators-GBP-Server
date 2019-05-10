
#include "Backtracking.h"


/**
 * Representación de Backtracking
 *
 * @since 06/05/19
 */


///Métodos


Backtracking::Backtracking(Cuadricula*_cuadricula) {

    cuadricula = _cuadricula;
    towerIdList = cuadricula->getTowerIdList();
    initializedStartGoal = false;
    foundGoal = false;

}




void Backtracking::findPath(Node* currentPosition, Node* targetPosition) {

    string current = "[" + to_string( currentPosition->getFila() ) + "," + to_string( currentPosition->getColumna() ) + "]";
    string target = "[" + to_string( targetPosition->getFila() ) + "," + to_string( targetPosition->getColumna() ) + "]";

    cout << "\nA path will be found between: " + current + " & " + target;



    ///En la primera iteracion
    if (!initializedStartGoal) {

        ///Limpia pathToGoal
        pathToGoal.clear();


        ///Instancia el nodo start y el goal
        startNode = currentPosition;
        goalNode = targetPosition;


        ///Agregar el primer nodo al Path
        //pathToGoal.push_back(currentPosition->getId());


        setInitializedStartGoal(true);

    }

    if (initializedStartGoal)  {
        if (continuePath(currentPosition) == true) {
            printVector("pathToGoal");
            printVector("fullPath");
            return;
        }

    }

}



bool Backtracking::continuePath(Node* currentPosition) {

    cout << "\ncontinuePath: " << currentPosition->getId() << endl;

    fullPath.push_back(currentPosition->getId());

    if (currentPosition->getId() == goalNode->getId()) {

        pathToGoal.push_back(currentPosition->getId());
        currentPosition->setInBacktrakingPath(true);

        setFoundGoal(true);
        return true;

    }

    ///Si se encuentra dentro de la cuadricula
    if ( currentPosition->getId() < ( (cuadricula->getSize())*(cuadricula->getSize()) + (cuadricula->getSize()) )
        && currentPosition->getTorre() == nullptr) {

        cout << "In zone" << endl;

        if (currentPosition->getFila() + 1 < cuadricula->getSize()) {

            Node* nextNodeFila = cuadricula->getNode(currentPosition->getFila() + 1, currentPosition->getColumna());

            if (continuePath(nextNodeFila) == true) {
                pathToGoal.push_back(currentPosition->getId());
                currentPosition->setInBacktrakingPath(true);

                setFoundGoal(true);
                return true;
            }

        }

        if (currentPosition->getColumna() + 1 < 10) {

            Node* nextNodeColumna = cuadricula->getNode(currentPosition->getFila(), currentPosition->getColumna() + 1 );

            if (continuePath(nextNodeColumna) == true) {
                pathToGoal.push_back(currentPosition->getId());
                currentPosition->setInBacktrakingPath(true);

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



void Backtracking::printVector(string list) {

    cout << "\n" << list << endl;

    if (list == "pathToGoal") {
        for (int i = 0; i < pathToGoal.size(); i++) {

            cout << pathToGoal[i] << endl;

        }
    }

    if (list == "fullPath") {
        for (int i = 0; i < fullPath.size(); i++) {

            cout << fullPath[i] << endl;

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
 *
 * @return
 */
vector<int> Backtracking::getFullPath() {
    return fullPath;
}

/**
 *
 * @return
 */
bool Backtracking::isFoundGoal() {
    return foundGoal;
}

/**
 *
 * @param _foundGoal
 */
void Backtracking::setFoundGoal(bool _foundGoal) {
    foundGoal = _foundGoal;
}

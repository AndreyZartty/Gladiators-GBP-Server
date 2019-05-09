
#include "AStar.h"


/**
 * Representa el Algoritmo de Pathfinding AStar (A*)
 *
 * @since 01/05/19
 */


///Constructor


/**
 * Constructor de AStar.
 * @param _cuadricula
 */
AStar::AStar(Cuadricula* _cuadricula) {

    cuadricula = _cuadricula;
    towerIdList = cuadricula->getTowerIdList();

    initializedStartGoal = false;
    foundGoal = false;

}


///Métodos


/**
 * Empezará o continuará el camino por medio de su posición actual y su target.
 * @param currentPosition
 * @param targetPosition
 */
void AStar::n_findPath(Node* currentPosition, Node* targetPosition) {

    string current = "[" + to_string( currentPosition->getFila() ) + "," + to_string( currentPosition->getColumna() ) + "]";
    string target = "[" + to_string( targetPosition->getFila() ) + "," + to_string( targetPosition->getColumna() ) + "]";

    cout << "\nA path will be found between: " + current + " & " + target << endl;


    ///En la primera iteracion
    if (!initializedStartGoal) {


        ///Limpia openList
        n_openList.clear();

        ///Limpia visitedList
        closedList.clear();

        ///Limpia pathToGoal
        n_pathToGoal.clear();

        ///Calcula el Heuristicos de la zona
        cuadricula->calculateHeuristic();


        n_setStartAndGoal(currentPosition, targetPosition);
        setInitializedStartGoal(true);

    }

    if (initializedStartGoal)  {
        n_continuePath(currentPosition);
    }

}


/**
 * Configura el inicio y el target del algoritmo.
 * @param start
 * @param goal
 */
void AStar::n_setStartAndGoal(Node* start, Node* goal) {

    cout << "\nsetStartAndGoal" << endl;

    ///Instancia el nodo start y el goal
    startNode = start;
    goalNode = goal;

    ///Calcula la Distancia Manhattan del nodo de inicio, configura su G y su padre
    startNode->setGCost(0);
    //startNode->setParent(nullptr);

    ///Ingresa el startNode al openList
    n_openList.push_back(startNode->getId());

}


/**
 * Comienza a calcular los costos de los caminos al rededor del actual
 * @param currentNode
 */
void AStar::n_continuePath(Node* currentNode){

    cout << "\ncontinuePath" << endl;

    if (startNode->getParent() == nullptr) {
        cout << "NULL PARENT" << endl;
    }

    if (n_openList.empty()) {
        return;
    }

    ///Si llega al goal comienza a llenar lista del Path
    if (currentNode->getId() == goalNode->getId()) {

        cuadricula->print();

        goalNode->setParent( currentNode->getParent() );

        Node* getPath;

        cout << "\nCOMPLETE" << endl;

        for (getPath = goalNode; getPath != nullptr; getPath = getPath->getParent()) {

            n_pathToGoal.push_back( getPath->getId() );

            getPath->setInAStarPath(true);

        }

        setFoundGoal(true);

        showPath();

        cout << "COMPLETEx2\n" << endl;

        cuadricula->printTorres();

        return;

    }

    else {

        ///Si el camino debe continuar, se recalcularán los costos de este

        ///RightNode
        n_pathOpened(currentNode->getFila() + 1, currentNode->getColumna(), currentNode->getGCost() + 10, currentNode);
        ///LeftNode
        n_pathOpened(currentNode->getFila() - 1, currentNode->getColumna(), currentNode->getGCost() + 10, currentNode);
        ///TopNode
        n_pathOpened(currentNode->getFila(), currentNode->getColumna() + 1, currentNode->getGCost() + 10, currentNode);
        ///BottomNode
        n_pathOpened(currentNode->getFila(), currentNode->getColumna() - 1, currentNode->getGCost() + 10, currentNode);
        ///TopLeftNode (Diagonal)
        n_pathOpened(currentNode->getFila() - 1, currentNode->getColumna() + 1, currentNode->getGCost() + 14,
                     currentNode);
        ///TopRightNode (Diagonal)
        n_pathOpened(currentNode->getFila() + 1, currentNode->getColumna() + 1, currentNode->getGCost() + 14,
                     currentNode);
        ///BottomRightNode (Diagonal)
        n_pathOpened(currentNode->getFila() - 1, currentNode->getColumna() - 1, currentNode->getGCost() + 14,
                     currentNode);
        ///BottomRightNode (Diagonal)
        n_pathOpened(currentNode->getFila() + 1, currentNode->getColumna() - 1, currentNode->getGCost() + 14,
                     currentNode);


        ///Saca del open list al revisado, si se encuentra ahi
        for (int i = 0; i < n_openList.size(); i++) {

            if (currentNode->getId() == n_openList[i]) {

                n_openList.erase(n_openList.begin() + i);
                closedList.push_back(currentNode->getId());

            }
        }

        Node* nextNode = n_getNextNode();

        cuadricula->print();

        n_findPath(nextNode,goalNode);

    }

}


/**
 * Verificará si las coordenadas pertenecen a uno ya revisado o a una torre
 * Si no es así, comparará su valor F y si este es mejor que el nuevo, se actualizan sus parámetros.
 * @param fila
 * @param columna
 * @param newGCost
 * @param parent
 */
void AStar::n_pathOpened(int fila, int columna, float newGCost, Node* parent){

    cout << "\npathOpened" << endl;

    if (startNode->getParent() == nullptr) {
        cout << "NULL PARENT" << endl;
    }

    ///Si se sale de la cuadricula
    if (fila < 0 || columna < 0 || fila > ZONE_SIZE - 1 || columna > ZONE_SIZE - 1) {
        return;
    }

    ///Genera el id para ser comparado
    int id = fila * ZONE_SIZE + columna;

    ///Revisa en visitedList si estas x y y pertenecen a uno de los ya visitados por medio de su id
    for (int i = 0; i < closedList.size(); i++) {

        if ( id == closedList[i] ) {
            return;
        }
    }

    ///Revisa en towerIdList si estas x y y pertenecen a una de las torres por medio de su id
    for (int i = 0; i < towerIdList.size(); i++) {

        if ( id == towerIdList[i] ) {
            return;
        }
    }


    Node* child = cuadricula->getNode(fila, columna);


    ///Si no está en el open list
    if (child->getGCost() == 0) {

        child->setGCost(newGCost);
        child->setParent(parent);
        child->obtainF();
        ///Se agrega al openList
        n_openList.push_back(child->getId());

        printVector("openList");
        printVector("closedList");

    }
    ///Si el G es mayor que el nuevo, su padre cambiara
    else if (child->getGCost() > newGCost) {
        child->setParent(parent);
    }

    else {
        return;
    }

}


/**
 * Busca cual será el siguiente Node.
 * @return nextNode
 */
Node* AStar::n_getNextNode() {

    cout << "getNextNode" << endl;

    if (startNode->getParent() == nullptr) {
        cout << "NULL PARENT" << endl;
    }

    Node* next;

    int lowest = 99999999;

    ///Se recorre openList para encontrar el Node con el F mas pequeño
    for (int i = 0; i < n_openList.size(); i++) {


        Node* temp = cuadricula->getNode(n_openList[i]);

        ///Modifica el F mas pequeño para ser comparado
        if ( temp->getFCost() < lowest) {
            lowest = temp->getFCost();
            next = temp;
        }
    }

    return next;

}


/**
 * Imprime el vector deseado.
 * @param list
 */
void AStar::printVector(string list) {

    cout << list << endl;

    if (list == "openList") {
        for (int i = 0; i < n_openList.size(); i++) {

            cout << n_openList[i] << endl;

        }
    }
    else if (list == "closedList") {
        for (int i = 0; i < closedList.size(); i++) {

            cout << closedList[i] << endl;

        }
    }
    else if (list == "pathToGoal") {
        for (int i = 0; i < n_pathToGoal.size(); i++) {

            cout << n_pathToGoal[i] << endl;

        }
    }

    cout << "\n" << endl;

}


/**
 * Muestra el path de AStar.
 */
void AStar::showPath() {
    printVector("pathToGoal");
}


///Getters y Setters


/**
 * Getter de Cuadricula de .
 * @return Cuadricula
 */
Cuadricula* AStar::getCuadricula() {
    return cuadricula;
}

/**
 * Setter de Cuadricula de .
 * @param _cuadricula
 */
void AStar::setCuadricula(Cuadricula* _cuadricula) {
    cuadricula = _cuadricula;
}


/**
 * Getter de initializedStartGoal de AStar.
 * @return initializedStartGoal
 */
bool AStar::isInitializedStartGoal() {
    return initializedStartGoal;
}

/**
 * Setter de initializedStartGoal de AStar.
 * @param _initializedStartGoal
 */
void AStar::setInitializedStartGoal(bool _initializedStartGoal) {
    initializedStartGoal = _initializedStartGoal;
}

/**
 * Getter de foundGoal de AStar.
 * @return foundGoal
 */
bool AStar::isFoundGoal() {
    return foundGoal;
}

/**
 * Setter de foundGoal de AStar.
 * @param _foundGoal
 */
void AStar::setFoundGoal(bool _foundGoal) {
    foundGoal = _foundGoal;
}

/**
 * Getter del startNode de AStar.
 * @return startNode
 */
Node* AStar::getStartNode() {
    return startNode;
}

/**
 * Setter del startNode de AStar.
 * @param _startNode
 */
void AStar::setStartNode(Node* _startNode) {
    startNode = _startNode;
}

/**
 * Getter del goalNode de AStar.
 * @return goalNode
 */
Node* AStar::getGoalNode() {
    return goalNode;
}

/**
 * Setter del goalNode de AStar.
 * @param _goalNode
 */
void AStar::setGoalNode(Node* _goalNode) {
    goalNode = _goalNode;
}

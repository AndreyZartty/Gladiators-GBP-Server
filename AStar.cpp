
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
    initializedStartGoal = false;
    foundGoal = false;

}


///Métodos


/**
 * Empezará o continuará el camino por medio de su posición actual y su target.
 * @param currentPosition
 * @param targetPosition
 */
void AStar::findPath(Node *currentPosition, Node *targetPosition) {

    ///En la primera iteracion
    if (!initializedStartGoal) {

        cout << " [Starting A*]";

        ///Limpia openList
        openList.clear();

        ///Limpia visitedList
        closedList.clear();

        ///Limpia pathToGoal
        pathToGoal.clear();


        ///Ingresa cero como estado inicial a las variables de TODOS los Nodes
        for (int i = 0 ; i < cuadricula->getSize() ; i++) {
            for (int j = 0 ; j < cuadricula->getSize() ; j++) {

                int id = ((i) * (cuadricula->getSize()) + (j));

                cuadricula->getNode(id)->setInAStarPath(false);
                cuadricula->getNode(id)->setGCost(0);
                cuadricula->getNode(id)->setFCost(0);
                cuadricula->getNode(id)->setHCost(0);

            }

        }

        ///Calcula el Heuristicos de la zona
        cuadricula->calculateHeuristic();

        ///Modifica los nodos inicial y final
        setStartAndGoal(currentPosition, targetPosition);
        setInitializedStartGoal(true);
    }


/*
    cout << "   Openlist size: " << openList.size();
    cout << "   PathToGoal size: " << pathToGoal.size();
    cout << "   InPath: " << currentPosition->isInAStarPath();
    cout << "   TEST: " << currentPosition->test << "\n" << endl;*/


    ///Continua el algoritmo si no es la primera vez
    if (initializedStartGoal)  {;
        continuePath(currentPosition);
    }

}


/**
 * Configura el inicio y el target del algoritmo.
 * @param start
 * @param goal
 */
void AStar::setStartAndGoal(Node *start, Node *goal) {

    ///Instancia el nodo start y el goal
    startNode = start;
    goalNode = goal;

    ///Calcula la Distancia Manhattan del nodo de inicio, configura su G y su padre
    startNode->setGCost(0);

    ///Ingresa el startNode al openList
    openList.push_back(startNode->getId());

}


/**
 * Comienza a calcular los costos de los caminos al rededor del actual
 * @param currentNode
 */
void AStar::continuePath(Node *currentNode){

    if (openList.empty()) {
        cout << "OpenList empty" << endl;
        return;
    }

    ///Si llega al goal comienza a llenar lista del Path
    if (currentNode->getId() == goalNode->getId()) {

        cuadricula->print();

        goalNode->setParent( currentNode->getParent() );

        Node* getPath;

        for (getPath = goalNode; getPath != nullptr; getPath = getPath->getParent()) {

            pathToGoal.push_back( getPath->getId() );

            getPath->setInAStarPath(true);

        }

        setInitializedStartGoal(false);

        setFoundGoal(true);

        return;

    }

    else {

        ///Si el camino debe continuar, se recalcularán los costos de este

        ///RightNode
        pathOpened(currentNode->getFila() + 1, currentNode->getColumna(), currentNode->getGCost() + 10, currentNode);
        ///LeftNode
        pathOpened(currentNode->getFila() - 1, currentNode->getColumna(), currentNode->getGCost() + 10, currentNode);
        ///TopNode
        pathOpened(currentNode->getFila(), currentNode->getColumna() + 1, currentNode->getGCost() + 10, currentNode);
        ///BottomNode
        pathOpened(currentNode->getFila(), currentNode->getColumna() - 1, currentNode->getGCost() + 10, currentNode);
        ///TopLeftNode (Diagonal)
        pathOpened(currentNode->getFila() - 1, currentNode->getColumna() + 1, currentNode->getGCost() + 14, currentNode);
        ///TopRightNode (Diagonal)
        pathOpened(currentNode->getFila() + 1, currentNode->getColumna() + 1, currentNode->getGCost() + 14, currentNode);
        ///BottomRightNode (Diagonal)
        pathOpened(currentNode->getFila() - 1, currentNode->getColumna() - 1, currentNode->getGCost() + 14, currentNode);
        ///BottomRightNode (Diagonal)
        pathOpened(currentNode->getFila() + 1, currentNode->getColumna() - 1, currentNode->getGCost() + 14, currentNode);


        ///Saca del open list al revisado, si se encuentra ahi
        for (int i = 0; i < openList.size(); i++) {

            if (currentNode->getId() == openList[i]) {

                openList.erase(openList.begin() + i);
                closedList.push_back(currentNode->getId());

            }
        }

        Node* nextNode = getNextNode();

        findPath(nextNode, goalNode);

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
void AStar::pathOpened(int fila, int columna, float newGCost, Node *parent){

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
    for (int i = 0; i < cuadricula->getTowerIdList().size(); i++) {

        if ( id == cuadricula->getTowerIdList()[i] ) {
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
        openList.push_back(child->getId());

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
Node* AStar::getNextNode() {

    Node* next;

    int lowest = 99999999;

    ///Se recorre openList para encontrar el Node con el F mas pequeño
    for (int i = 0; i < openList.size(); i++) {

        Node* temp = cuadricula->getNode(openList[i]);

        ///Modifica el F mas pequeño para ser comparado
        if ( temp->getFCost() < lowest) {

            lowest = temp->getFCost();
            next = temp;
        }
    }

    next->setInAStarPath(false);

    return next;

}


/**
 * Imprime el vector deseado.
 * @param list
 */
void AStar::printVector(string list) {

    cout << list << endl;

    if (list == "openList") {
        for (int i = 0; i < openList.size(); i++) {

            cout << openList[i] << endl;

        }
    }
    else if (list == "closedList") {
        for (int i = 0; i < closedList.size(); i++) {

            cout << closedList[i] << endl;

        }
    }
    else if (list == "pathToGoal") {
        for (int i = 0; i < pathToGoal.size(); i++) {

            cout << pathToGoal[i] << endl;

        }
    }

    cout << "\n" << endl;

}


/**
 * Muestra y retorna el path de AStar.
 * @return path
 */
vector<int> AStar::showPath() {
    printVector("pathToGoal");
    return pathToGoal;
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

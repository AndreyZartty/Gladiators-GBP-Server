
#include "AStar.h"


/**
 * Representa el Algoritmo de Pathfinding AStar (A*)
 *
 * @since 01/05/19
 */


///Constructor


AStar::AStar(vector<int> _towerIdList) {
    initializedStartGoal = false;
    foundGoal = false;

    towerIdList = _towerIdList;
}

AStar::~AStar() {

}


///Métodos


/**
 * Empezará o continuará el camino por medio de su posición actual y su target.
 * @param currentPosition - Vector
 * @param targetPosition - Vector
 */
void AStar::findPath(Vector2* currentPosition, Vector2* targetPosition) {

    if (!initializedStartGoal) {

        ///Limpia openList
        for (int i = 0; i < openList.size(); i++) {
            delete openList[i];
        }
        openList.clear();

        ///Limpia visitedList
        for (int i = 0; i < visitedList.size(); i++) {
            delete visitedList[i];
        }
        visitedList.clear();

        ///Limpia pathToGoal
        for (int i = 0; i < pathToGoal.size(); i++) {
            delete pathToGoal[i];
        }
        pathToGoal.clear();

        ///Inicializa el startpoint del recorrido
        Node* start;
        start->setXCoord( currentPosition->getX() );
        start->setYCoord( currentPosition->getY() );

        ///Initialize el goal del recorrido
        Node* goal;
        goal->setXCoord( targetPosition->getX() );
        goal->setYCoord( targetPosition->getY() );

        setStartAndGoal(start, goal);
        setInitializedStartGoal(true);

    }

    if (initializedStartGoal)  {
        continuePath();
    }

}

/**
 * Configura el inicio y el target del algoritmo.
 * @param start - Node
 * @param goal - Node
 */
void AStar::setStartAndGoal(Node* start, Node* goal) {

    ///Instancia el nodo start y el goal
    startNode = new Node(start->getXCoord(), start->getYCoord(), nullptr);
    goalNode = new Node(goal->getXCoord(), goal->getYCoord(), goal);

    ///Calcula la Distancia Manhattan del nodo de inicio, configura su G y su padre
    startNode->setGCost(0);
    startNode->setHCost( startNode->ManhattanDistance(goalNode) );
    startNode->setParent(nullptr);

    ///Ingresa el startNode al openList
    openList.push_back(startNode);

}

/**
 * Busca cual será el siguiente Node.
 * @return nextNode
 */
Node* AStar::getNextNode(){

    ///Numero muy grande para su primera comparacion
    float bestF = 999999.0f;
    ///Index para saber donde sera guardado en el vector
    int nodeIndex = -1;
    Node* nextNode = nullptr;

    ///Calculo del F
    for (int i = 0; i < openList.size(); i++) {

        if (openList[i]->obtainF() < bestF) {

            bestF = openList[i]->getFCost();
            nodeIndex = i;

        }
    }


    if (nodeIndex >= 0) {

        nextNode = openList[nodeIndex];
        visitedList.push_back(nextNode);
        openList.erase(openList.begin() + nodeIndex);

    }

    return nextNode;

}

/**
 * Verificará si las coordenadas pertenecen a uno ya revisado o a una torre
 * Si no es así, comparará su valor F y si este es mejor que el nuevo, se actualizan sus parámetros.
 * @param x - coord
 * @param y - coord
 * @param newGCost - nuevo gCost
 * @param parent - Node
 */
void AStar::pathOpened(int x, int y, float newGCost, Node* parent){

    ///Genera el id para ser comparado
    int id = y * ZONE_SIZE + x;

    ///Revisa en visitedList si estas x y y pertenecen a uno de los ya visitados por medio de su id
    for (int i = 0; i < visitedList.size(); i++) {

        if ( id == visitedList[i]->getId() ) {
            return;
        }
    }

    ///Revisa en towerIdList si estas x y y pertenecen a una de las torres por medio de su id
    for (int i = 0; i < towerIdList.size(); i++) {

        if ( id == towerIdList[i] ) {
            return;
        }
    }

    Node* newChild = new Node(x, y, parent);
    newChild->setGCost( newGCost );
    newChild->setHCost( parent->ManhattanDistance(getGoalNode()) );

    ///Se compara el valor de F
    for (int i = 0; i < openList.size(); i++) {

        if (id == openList[i]->getId()) {

            float newF = newChild->getGCost() + newGCost + openList[i]->getHCost();

            if (openList[i]->obtainF() > newF) {

                openList[i]->setGCost( newChild->getGCost() + newGCost );
                openList[i]->setParent(newChild);

            }
            else { ///Si el F no es mejor

                delete newChild;
                return;

            }
        }
    }

    ///Se agrega al openList
    openList.push_back(newChild);

}

void AStar::continuePath(){

}

Vector2* AStar::nextPathPosition() {

}

void AStar::clearOpenList() {

}

void AStar::clearVisitedList() {

}

void AStar::clearPathToGoal() {

}


///Getters y Setters


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
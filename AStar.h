
#ifndef GLADIATORS_GBP_ASTAR_H
#define GLADIATORS_GBP_ASTAR_H


#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Node.h"
#include "Cuadricula.h"

using namespace std;


/**
 * Representa al Algortimo Pathfinding A*
 */


class AStar {

private:
    Cuadricula* cuadricula;
    bool initializedStartGoal;
    bool foundGoal;
    vector<int> n_openList;
    vector<int> closedList;
    vector<int> n_pathToGoal;
    Node* startNode;
    Node* goalNode;
    vector<int> towerIdList;

public:

    ///Constructor

    AStar(Cuadricula* _cuadricula);

    ///Métodos

    void n_findPath(Node* currentPosition, Node* targetPosition);
    void n_setStartAndGoal(Node* start, Node* goal);
    void n_continuePath(Node* currentNode);
    void n_pathOpened(int fila, int columna, float newGCost, Node* parent);
    Node* n_getNextNode();
    void printVector(string list);
    vector<int> showPath();


    ///Getters & Setters

    Cuadricula* getCuadricula();
    void setCuadricula(Cuadricula* _cuadricula);
    bool isInitializedStartGoal();
    void setInitializedStartGoal(bool _initializedStartGoal);
    bool isFoundGoal();
    void setFoundGoal(bool _foundGoal);
    Node* getStartNode();
    void setStartNode(Node* _startNode);
    Node* getGoalNode();
    void setGoalNode(Node* _goalNode);

};


#endif //GLADIATORS_GBP_ASTAR_H

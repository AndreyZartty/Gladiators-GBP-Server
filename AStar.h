
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
 *
 * @since 01/05/19
 */


class AStar {

private:

    Cuadricula* cuadricula;
    bool initializedStartGoal;
    bool foundGoal;
    vector<int> openList;
    vector<int> closedList;
    vector<int> pathToGoal;
    Node* startNode;
    Node* goalNode;

public:

    ///Constructor
    AStar(Cuadricula* _cuadricula);

    ///Métodos
    void findPath(Node *currentPosition, Node *targetPosition);
    void setStartAndGoal(Node *start, Node *goal);
    void continuePath(Node *currentNode);
    void pathOpened(int fila, int columna, float newGCost, Node *parent);
    Node* getNextNode();
    void printVector(string list);
    vector<int> showPath();
    void rotatePath();

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
    vector<int> getPathToGoal();

};


#endif //GLADIATORS_GBP_ASTAR_H

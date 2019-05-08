
#ifndef GLADIATORS_GBP_BACKTRACKING_H
#define GLADIATORS_GBP_BACKTRACKING_H


#include "Cuadricula.h"


/**
 * Header de Backtracking
 *
 * @since 06/05/19
 */


class Backtracking {

private:
    Cuadricula* cuadricula;

    bool initializedStartGoal;

    vector<int> towerIdList;
    vector<int> pathToGoal;
    vector<int> fullPath;

    Node* startNode;
    Node* goalNode;

public:

    ///Constructor
    explicit Backtracking(Cuadricula* _cuadricula);

    ///Métodos
    void findPath(Node* currentPosition, Node* targetPosition);
    void setStartAndGoal(Node* start, Node* goal);
    bool continuePath(Node* currentPosition);

    void printVector(string list);

    ///Getters & Setters

    void setInitializedStartGoal(bool _initializedStartGoal);

    vector<int> getPathToGoal();

    vector<int> getFullPath();


};


#endif //GLADIATORS_GBP_BACKTRACKING_H

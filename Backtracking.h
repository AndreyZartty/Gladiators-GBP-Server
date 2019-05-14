
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
    bool foundGoal;
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
    bool continuePath(Node* currentPosition);
    void printVector(string list);
    vector<int> showPath();
    void rotatePath();


    ///Getters & Setters
    void setCuadricula(Cuadricula* _cuadricula);
    void setInitializedStartGoal(bool _initializedStartGoal);
    bool isFoundGoal();
    void setFoundGoal(bool _foundGoal);
    vector<int> getPathToGoal();
    vector<int> getFullPath();

};


#endif //GLADIATORS_GBP_BACKTRACKING_H

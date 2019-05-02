
#ifndef GLADIATORS_GBP_ASTAR_H
#define GLADIATORS_GBP_ASTAR_H


#include <vector>
#include "Vector2.h"
#include "Node.h"

using namespace std;


/**
 * Representa al Algortimo Pathfinding A*
 */


class AStar {

private:
    bool initializedStartGoal;
    bool foundGoal;
    Node* startNode;
    Node* goalNode;
    vector<Node*> openList;
    vector<Node*> visitedList;
    vector<Vector2*> pathToGoal;

    vector<int> towerIdList;

public:

    ///Constructor

    AStar(vector<int> _towerIdList);
    ~AStar();


    ///Métodos

    void findPath(Vector2* currentPosition, Vector2* targetPosition);
    void setStartAndGoal(Node* start, Node* goal);
    Node* getNextNode();
    void pathOpened(int x, int y, float newCost, Node* parent);
    void continuePath();

    Vector2* nextPathPosition();
    void clearOpenList();
    void clearVisitedList();
    void clearPathToGoal();


    ///Getters & Setters

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

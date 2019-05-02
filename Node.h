
#ifndef GLADIATORS_GBP_NODE_H
#define GLADIATORS_GBP_NODE_H

#define ZONE_SIZE 10

#include "Gladiador.h"
#include "Torre.h"


/**
 * Header de Node
 *
 * @since 01/05/19
 */


class Node {

private:
    Torre* torre;
    Gladiador* gladiador1;
    Gladiador* gladiador2;
    bool libre;

    int xCoord;
    int yCoord;
    int id;
    Node* parent;
    float gCost;
    float hCost;
    float fCost;


public:
    ///Constructores
    Node();
    Node(int _xCoord, int _yCoord, Node* _parent);

    ///Métodos
    float ManhattanDistance(Node* endNode);
    float obtainF();

    ///Getters & Setters

    //torre
    //glad1
    //glad2
    //libre

    int getXCoord();
    void setXCoord(int _xCoord);
    int getYCoord();
    void setYCoord(int _yCoord);
    int getId();
    void setId(int _id);
    Node* getParent();
    void setParent(Node* _parent);
    float getGCost();
    void setGCost(float _gCost);
    float getHCost();
    void setHCost(float _hCost);
    float getFCost();
    void setFCost(float _fCost);


};


#endif //GLADIATORS_GBP_NODE_H

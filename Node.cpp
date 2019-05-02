
#include <math.h>
#include "Node.h"


/**
 * Representa un Node
 *
 * @since 01/05/19
 */





///Constructores


/**
 * Constructor sin parametros de Node.
 */
Node::Node(){
    parent = nullptr;
}

/**
 * Constructor con paramentros de Node.
 * @param _xCoord
 * @param _yCoord
 * @param _parent
 */
Node::Node(int _xCoord, int _yCoord, Node* _parent = nullptr) {
    xCoord = _xCoord;
    yCoord = _yCoord;
    parent = _parent;
    id = yCoord * ZONE_SIZE + yCoord;
    gCost = 0;
    hCost = 0;
    fCost = 0;
}


///Métodos


/**
 * Genera el fCost por medio de la suma del gCost y el hCost
 * @return fCost
 */
float Node::obtainF() {
    setFCost( gCost + hCost );
    return getFCost();
}

/**
 * Calcula la distancia Manhattan hacia el endNode
 * @param endNode
 * @return distancia
 */
float Node::ManhattanDistance(Node* endNode) {
    float x = (float) ( fabs ( xCoord - endNode->getXCoord() ) );
    float y = (float) ( fabs ( yCoord - endNode->getYCoord() ) );

    return x + y;
}


///Getters y Setters


/**
 * Getter de la coordenada x del Node.
 * @return x
 */
int Node::getXCoord() {
    return xCoord;
}

/**
 * Setter de la coordenada x del Node.
 * @param _xCoord
 */
void Node::setXCoord(int _xCoord) {
    xCoord = _xCoord;
}

/**
 * Getter de la coordenada y del Node.
 * @return y
 */
int Node::getYCoord() {
    return yCoord;
}

/**
 * Setter de la coordenada y del Node.
 * @param _yCoord
 */
void Node::setYCoord(int _yCoord) {
    yCoord = _yCoord;
}

/**
 * Getter del id del Node.
 * @return id - identificador
 */
int Node::getId() {
    return id;
}

/**
 * Setter del id del Node
 * @param _id
 */
void Node::setId(int _id) {
    id = _id;
}

/**
 *  Getter del parent del Node.
 * @return parent - Node
 */
Node* Node::getParent() {
    return parent;
}

/**
 * Setter del parent del Node.
 * @param _parent
 */
void Node::setParent(Node* _parent) {
    parent =_parent;
}

/**
 * Getter del gCost del Node.
 * @return gCost
 */
float Node::getGCost() {
    return gCost;
}

/**
 * Setter del gCost del Node.
 * @param _gCost
 */
void Node::setGCost(float _gCost) {
    gCost = _gCost;
}

/**
 * Getter del hCost del Node.
 * @return hCost
 */
float Node::getHCost() {
    return hCost;
}

/**
 * Setter del hCost del Node.
 * @param _hCost
 */
void Node::setHCost(float _hCost) {
    hCost = _hCost;
}

/**
 * Getter del fCost del Node.
 * @return fCost
 */
float Node::getFCost() {
    return fCost;
}

/**
 * Setter del fCost del Node.
 * @param _fCost
 */
void Node::setFCost(float _fCost) {
    fCost = _fCost;
}
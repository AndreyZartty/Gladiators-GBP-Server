
#include <math.h>
#include <iostream>
#include "Node.h"

using namespace std;


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

    torre = nullptr;
    zoneSize = -1;
    fila = -1;
    columna = -1;
    parent = nullptr;
    id = -1;
    gCost = -1;
    hCost = -1;
    fCost = -1;
    xCoord = 0;
    yCoord = 0;

}

/**
 * Constructor con paramentros de Node.
 * @param _fila
 * @param _yCoord
 * @param _zoneSize
 */
Node::Node(int _fila, int _columna, int _zoneSize) {
    torre = nullptr;
    zoneSize = _zoneSize;
    fila = _fila;
    columna = _columna;
    parent = nullptr;
    id = fila * zoneSize + columna;
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
    float i = ( fabs ( (float) fila - endNode->getFila() ) );
    float j = ( fabs ( (float) columna - endNode->getColumna() ) );
    int h = i + j;
    setHCost(h);
    return h;
}


///Getters y Setters


/**
 * Getter de Torre del Node.
 * @return Torre
 */
Torre* Node::getTorre(){
    return torre;
}

/**
 * Setter de Torre del Node.
 * @param _torre
 */
void Node::setTorre(Torre* _torre){
    torre = _torre;
}

/**
 * Getter de la fila del Node.
 * @return int de la fila
 */
int Node::getFila() {
    return fila;
}

/**
 * Setter de la fila del Node.
 * @param _fila
 */
void Node::setFila(int _fila) {
    fila = _fila;
}

/**
 * Getter de la columna del Node.
 * @return int de la columna
 */
int Node::getColumna() {
    return columna;
}

/**
 * Setter de la columna del Node.
 * @param _columna
 */
void Node::setColumna(int _columna) {
    columna = _columna;
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
    parent = _parent;
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

/**
 * Getter de inAStarPath de Node.
 * @return bool
 */
bool Node::isInAStarPath() {
    return inAStarPath;
}

/**
 * Setter de inAStarPath de Node.
 * @param _inAStarPath
 */
void Node::setInAStarPath(bool _inAStarPath) {
    inAStarPath = _inAStarPath;
}

/**
 * Getter de inBacktrackingPath de Node.
 * @return bool
 */
bool Node::isInBacktrackingPath() {
    return inBacktrackingPath;
}

/**
 * Setter de inBacktrackingPath de Node.
 * @param _inBacktrackingPath
 */
void Node::setInBacktrackingPath(bool _inBacktrackingPath) {
    inBacktrackingPath = _inBacktrackingPath;
}

/**
 * Getter de zoneSize de Node.
 * @return zoneSize
 */
int Node::getZoneSize(){
    return zoneSize;
}

/**
 * Setter de zoneSize de Node.
 * @param _zoneSize
 */
void Node::setZoneSize(int _zoneSize) {
    zoneSize = _zoneSize;
}

/**
 * Getter de xCoord de Node.
 * @return xCoord
 */
int Node::getXCoord() {
    return xCoord;
}

/**
 * Setter de xCoord.
 * @param _xCoord
 */
void Node::setXCoord(int _xCoord) {
    xCoord = _xCoord;
}

/**
 * Getter de yCoord.
 * @return yCoord
 */
int Node::getYCoord() {
    return yCoord;
}

/**
 * Setter de yCoord de Node.
 * @param _yCoord
 */
void Node::setYCoord(int _yCoord) {
    yCoord =_yCoord;
}

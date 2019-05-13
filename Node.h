
#ifndef GLADIATORS_GBP_NODE_H
#define GLADIATORS_GBP_NODE_H

#include "Gladiador.h"
#include "Torre.h"


/**
 * Header de Node
 *
 * @since 01/05/19
 */


class Node {

private:

    int fila;
    int columna;
    int id;
    Node* parent;
    float gCost;
    float hCost;
    float fCost;
    Torre* torre;
    bool inAStarPath;
    bool inBacktrackingPath;
    int zoneSize;
    int xCoord;
    int yCoord;
    Gladiador* gladiador1;
    Gladiador* gladiador2;


public:

    ///Constructores
    Node();
    Node(int _fila, int _columna, int _zoneSize);

    ///Métodos
    float ManhattanDistance(Node* endNode);
    float obtainF();

    ///Getters & Setters
    Torre* getTorre();
    void setTorre(Torre* _torre);
    int getFila();
    void setFila(int _fila);
    int getColumna();
    void setColumna(int _columna);
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
    bool isInAStarPath();
    void setInAStarPath(bool _inAStarPath);
    bool isInBacktrackingPath();
    void setInBacktrackingPath(bool _inBacktrackingPath);
    int getZoneSize();
    void setZoneSize(int _zoneSize);
    int getXCoord();
    void setXCoord(int _xCoord);
    int getYCoord();
    void setYCoord(int _yCoord);

    int test = 69;

};


#endif //GLADIATORS_GBP_NODE_H

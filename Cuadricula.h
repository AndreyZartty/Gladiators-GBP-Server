
#ifndef GLADIATORS_GBP_CUADRICULA_H
#define GLADIATORS_GBP_CUADRICULA_H

#include "Node.h"
#include <iostream>
#include <vector>

#define ZONE_SIZE 10

using namespace std;


/**
 * Header de Cuadricula
 *
 * @since 30/04/19
 */


class Cuadricula {

private:
    int size = ZONE_SIZE;
    Node* matriz [ZONE_SIZE][ZONE_SIZE];

    Node* nodoInicio;
    Node* nodoFinal;

    vector<int> towerIdList;
    vector<int> clientTowerIdList;

    int cantTorres;
    bool recorrible;

public:
    ///Constructor
    Cuadricula();

    ///Metodos
    void buildZone(int n);
    void generateTowers();
    void calculateHeuristic();
    Node* getNode(int i, int j);
    Node* getNode(int id);

    void print();
    void printTorres();


    ///Getters & Setters
    int getSize();

    vector<int> getTowerIdList();
    vector<int> getClientTowerIdList();

};


#endif //GLADIATORS_GBP_CUADRICULA_H

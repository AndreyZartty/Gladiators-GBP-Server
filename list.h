//
// Created by jose on 13/05/19.
//

#ifndef GLADIATORS_GBP_LIST_H
#define GLADIATORS_GBP_LIST_H

#include <iostream>
#include "nodeG.h"
#include "Gladiador.h"

class List{

public:

    NodeG* getPointerHead();
    void setPointerHead(NodeG* head);
    void insertFirst(Gladiador *gladiador);
    int getSize();
    NodeG* getLast();
    void insertLast(Gladiador *gladiador);
    Gladiador* recorrer(int indice);
    Gladiador* sacar(int indice);
    void swap(Gladiador *xp, Gladiador *yp);
    void bubbleSort();
    void vaciar();
private:

    NodeG* pointerHead= nullptr;

};


#endif //GLADIATORS_GBP_LIST_H

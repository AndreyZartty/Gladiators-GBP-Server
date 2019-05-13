//
// Created by jose on 13/05/19.
//

#ifndef GLADIATORS_GBP_NODEG_H
#define GLADIATORS_GBP_NODEG_H

#include "Gladiador.h"

class NodeG {
public:
    NodeG();
    NodeG(NodeG* _nxtPtr, Gladiador* _data);
    void set_data(Gladiador* _data);
    void set_nxtNd(NodeG* node);
    Gladiador* get_data();
    NodeG* get_nxtPtr();
private:
    Gladiador* data;
    NodeG* nxtPtr;
};


#endif //GLADIATORS_GBP_NODEG_H

//
// Created by jose on 13/05/19.
//

#include "nodeG.h"

NodeG :: NodeG(NodeG* _nxtPtr, Gladiador* _data) {
    nxtPtr = _nxtPtr;
    data = _data;
}
void NodeG::set_data(Gladiador* _data) {
    data = _data;
}
void NodeG::set_nxtNd(NodeG* _nxtNd) {
    nxtPtr = _nxtNd;
    //std::cout<<&_nxtNd<<std::endl;
}
Gladiador* NodeG::get_data() {
    //std::cout<<data<<std::endl;
    return data;
}
NodeG* NodeG::get_nxtPtr() {
    //std::cout<<nxtPtr<<std::endl;
    return nxtPtr;
}


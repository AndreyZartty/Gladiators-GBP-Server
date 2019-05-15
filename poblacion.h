//
// Created by jose on 13/05/19.
//

#ifndef GLADIATORS_GBP_POBLACION_H
#define GLADIATORS_GBP_POBLACION_H

#include "Gladiador.h"
#include "list.h"
#include <vector>


class Poblacion
{
public:
    Poblacion(string _nombrePoblacion);
    int getGeneracion();
    void setGeneracion(int Generacion);
    void insertarGladiador(Gladiador* gladiador);
    void insertarCopia(Gladiador* gladiador);
    List getGladiadores();
    List getCopia();
    List getPadres();
    void setPadres();
    void setMejor();
    Gladiador* getMejor();
    string getNombrePoblacion();
    void nuevageneracion();
    vector <List*> getGeneraciones();



private:
    string nombrePoblacion;
    List gladiadores;
    List copia;
    List padres;
    int generacion=1;
    Gladiador* mejor;
    vector <List*> generaciones;
};


#endif //GLADIATORS_GBP_POBLACION_H

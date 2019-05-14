//
// Created by jose on 13/05/19.
//

#ifndef GLADIATORS_GBP_POBLACION_H
#define GLADIATORS_GBP_POBLACION_H

#include "Gladiador.h"
#include "list.h"

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


private:
    string nombrePoblacion;
    List gladiadores;
    List copia;
    List padres;
    int generacion=1;
    Gladiador* mejor;
};


#endif //GLADIATORS_GBP_POBLACION_H

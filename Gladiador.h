
#ifndef GLADIATORS_GBP_GLADIADOR_H
#define GLADIATORS_GBP_GLADIADOR_H

#include <iostream>
#include "Vector2.h"

using namespace std;

class Gladiador {

private:

    Vector2* current;
    Vector2* target;

    int fila;
    int columna;

    string nombre;
    int edad;
    int probabilidadSupervivencia;
    int expectativaVida;
    int inteligencia;
    int condicionFisica;
    int fuerzaSuperior;
    int fuerzaInferior;
    int resistencia;
    bool muerto=false;

    int SendJson();

public:
    Gladiador();
    Gladiador(int generacion);
    Gladiador(int generacion, Gladiador *padre1, Gladiador *parte2);
    void setNombre(string Nombre);
    void setEdad(int Edad);
    void setProbabilidadSupervivencia(int PS);
    void setExpectativaVida(int EV);
    void setInteligencia(int Inteligencia);
    void setCondicionFisica(int CF);
    void setFuerzaSuperior(int FS);
    void setFuerzaInferior(int FI);
    void setResistencia();
    void morir();
    int getEdad();
    int getProbabilidadSupervivencia();
    int getExpectativaVida();
    int getInteligencia();
    int getCondicionFisica();
    int getFuerzaSuperior();
    int getFuerzaInferior();
    int getResistencia();
    string getNombre();
    bool getMuerto();
    void mutacion(string *gen);


};


#endif //GLADIATORS_GBP_GLADIADOR_H

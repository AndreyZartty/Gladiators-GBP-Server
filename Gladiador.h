
#ifndef GLADIATORS_GBP_GLADIADOR_H
#define GLADIATORS_GBP_GLADIADOR_H

#include <iostream>
#include <vector>
#include "Cuadricula.h"

#define ZONE_SIZE 10

using namespace std;

class Gladiador {

private:

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
    vector<int> pathToGoal;
    Cuadricula* cuadricula;
    int hits[ZONE_SIZE*ZONE_SIZE][24];

    string nombrePadre1;
    string nombrePadre2;

    int generacion;


public:

    ///Constructores
    Gladiador(int generacion);
    Gladiador(int generacion, Gladiador *padre1, Gladiador *parte2);

    ///Metodos
    void morir();
    void mutacion(string *gen);
    void generateHits();


    ///Getters & Setters
    void setNombre(string Nombre);
    void setEdad(int Edad);
    void setProbabilidadSupervivencia(int PS);
    void setExpectativaVida(int EV);
    void setInteligencia(int Inteligencia);
    void setCondicionFisica(int CF);
    void setFuerzaSuperior(int FS);
    void setFuerzaInferior(int FI);
    void setResistencia();
    void setResistencia(int id);
    void setPathToGoal(vector<int> _pathToGoal);
    void setNombrePadre1(string _nombre);
    void setNombrePadre2(string _nombre);
    void setGeneracion(int _generacion);
    void setCuadricula(Cuadricula* _cuadricula);

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
    vector<int> getPathToGoal();
    Cuadricula* getCuadricula();
    bool isHit(int pathIndex, int arrowIndex);
    string getNombrePadre1();
    string getNombrePadre2();
    int getGeneracion();


};


#endif //GLADIATORS_GBP_GLADIADOR_H

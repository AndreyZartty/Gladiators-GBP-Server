
#include "Gladiador.h"

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>
#include "list.h"

#define PORT 3550
#define MAXDATASIZE 1000

using namespace std;


/**
 * Representa un Gladiador
 *
 * @since 30/04/19
 */

/**
 * Constructor vacio de Gladiador.
 */
Gladiador::Gladiador() {}

/**
 * Constructor de Gladiador.
 * @param generacion
 */
Gladiador::Gladiador(int generacion)
{
    if (generacion == 1){

        //srand (time(NULL));
        int random = 15 + rand() % (61 - 15);
        setEdad(random);
        random = 1 + rand() % (5 - 1);

        setInteligencia(random);
        random = 1 + rand() % (5 - 1);

        setCondicionFisica(random);
        random = 1 + rand() % (5 - 1);

        setFuerzaSuperior(random);
        random = 1 + rand() % (5 - 1);

        setFuerzaInferior(random);
        setResistencia();
        setExpectativaVida(getResistencia()/10);
        setProbabilidadSupervivencia(getResistencia()-4);
    }
    else {
        cout << "Introduzca los padres si no es la primera generacion" << endl;
    }
}


///Conversiones

/**
 * Convierte un numero de decimal a binario.
 * @param n
 * @return resultado
 */
string decToBinary(int n)
{
    // Size of an integer is assumed to be 32 bits
    string res;
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            res+="1";
        else
            res+= "0";
    }
    return res;
}

/**
 * Convierte un numero de binario a decimal.
 * @param binario
 * @return resultado
 */
int binToDec(int binario)
{
    int exp,digito;
    int decimal;

    exp=0;
    decimal=0;
    while(((int)(binario/10))!=0)
    {

        digito = (int)binario % 10;
        decimal = decimal + digito * pow(2,exp);
        exp++;
        binario=(int)(binario/10);
    }
    decimal=decimal + binario * pow(2,exp);
    //cout << endl << "Decimal: " << decimal << endl;
    return decimal;
}

/**
 * Constructor de Gladiador.
 * @param generacion
 * @param padre1
 * @param padre2
 */
Gladiador::Gladiador(int generacion, Gladiador *padre1, Gladiador *padre2)
{
    int random1 = 1 + rand() % (100-1);
    if (generacion == 1){
        cout << "No introduzca padres, ya que no es de la primera generacion" << endl;
    }
    else {
        string cromosomaInte1 = decToBinary(padre1->getInteligencia()).substr(0,2);
        string cromosomaInte2 = decToBinary(padre2->getInteligencia()).substr(2,4);
        string cromosomaCond1 = decToBinary(padre1->getCondicionFisica()).substr(0,2);
        string cromosomaCond2 = decToBinary(padre2->getCondicionFisica()).substr(2,4);
        string cromosomaFuerzaSup1 = decToBinary(padre1->getFuerzaSuperior()).substr(0,2);
        string cromosomaFuerzaSup2 = decToBinary(padre2->getFuerzaSuperior()).substr(2,4);
        string cromosomaFuerzaInf1 = decToBinary(padre1->getFuerzaInferior()).substr(0,2);
        string cromosomaFuerzaInf2 = decToBinary(padre2->getFuerzaInferior()).substr(2,4);
        string *arr[]={&cromosomaInte1,&cromosomaInte2,&cromosomaCond1,&cromosomaCond2,&cromosomaFuerzaSup1,&cromosomaFuerzaSup2,&cromosomaFuerzaInf1,&cromosomaFuerzaInf2};
        //cout<<padre1->getInteligencia()<<endl;
        //cout<<cromosomaInte1<<endl;
        if (random1<=5){
            int random2 = 0 + rand() % (7-0);
            mutacion(arr[random2]);
        }
        setInteligencia(binToDec(atoi((cromosomaInte1+cromosomaInte2).c_str())));
        setCondicionFisica(binToDec(atoi((cromosomaCond1+cromosomaCond2).c_str())));
        setFuerzaSuperior(binToDec(atoi((cromosomaFuerzaSup1+cromosomaFuerzaSup2).c_str())));
        setFuerzaInferior(binToDec(atoi((cromosomaFuerzaInf1+cromosomaFuerzaInf2).c_str())));
        setEdad(20);
        setResistencia();
        setExpectativaVida(getResistencia()/10);
        setProbabilidadSupervivencia(getResistencia()-4);
    }
    setNombrePadre1(padre1->getNombre());
    setNombrePadre2(padre2->getNombre());
}


///Metodos


/**
 * Genera una mutación en el algortimo genético.
 * @param gen
 */
void Gladiador::mutacion(string *gen){
    cout<<"mutacion de gen: "<<*gen;
    int random = rand() % 2;
    if (random==1){
        if(gen->substr(0,1)=="1"){
            *gen="0"+gen->substr(1,2);
        }else {
            *gen="1"+gen->substr(1,2);
        }
    }else {
        if(gen->substr(1,2)=="1"){
            *gen=gen->substr(0,1)+"0";
        }else {
            *gen=gen->substr(0,1)+"1";
        }
    }
    cout<<" a: "<<*gen<<endl;
}


/**
 * Empieza a llenar la matriz "hits" con los valores de la de las torres que lo lastiman por el camino.
 * y sus respectivas flechas.
 */
void Gladiador::generateHits() {

    //cout << "Hits->Start\n" << endl;

    int zoneSize = cuadricula->getSize();

    for(int i = 0; i < pathToGoal.size(); i++) {

        ///Id de la poscion actual del path
        int currentId = pathToGoal[i];

        ///Cantidad de torres
        int towerCount = 1;

        ///Se ingresa la poscion del path a la matriz
        hits[i][0] = currentId;

        ///Atributos de la posicion para utilizarlos para obtener las torres
        int idToCheck;
        int filaToCheck = cuadricula->getNode(currentId)->getFila();
        int columnaToCheck = cuadricula->getNode(currentId)->getColumna();

        for (int fila = -2; fila <= 2; fila++) {

            for (int columna = -2; columna <= 2; columna++) {

                ///Verificara cada Nodo al rededor de la posicion si esta en la cuadricula y si tiene torre

                if (cuadricula->getNode(filaToCheck + fila, columnaToCheck + columna) != nullptr) {

                    if (cuadricula->getNode(filaToCheck + fila, columnaToCheck + columna)->getTorre() != nullptr) {

                        hits[i][towerCount] = cuadricula->getNode(filaToCheck + fila, columnaToCheck + columna)->getId();

                        towerCount++;

                    }
                    else {
                      //  cout << "No existe" << endl;
                    }
                } else {
                   // cout << "Out of bounds" << endl;
                }

            }

        }

    }

    /*for (int i = 0 ; i < pathToGoal.size() ; i++) {
        for (int j = 0 ; j < 24 ; j++) {

            int printee = hits[i][j];

            cout << " ["<< printee << "] " ;

        }
        cout << "\n" << endl;
    }*/

    //cout << "Hits->End\n\n" << endl;

}

/**
 * Retorna si este gladiador ha sido golpeado.
 * @param pathIndex
 * @param arrowIndex
 * @return bool
 */
bool Gladiador::isHit(int pathIndex, int arrowIndex) {

    if (hits[pathIndex][arrowIndex] != 0) {
        return true;
    }
    else {
        return false;
    }

}

/**
 * Verifica si alguna Torre ha golpeado a este gladiador.
 * @param pathIndex
 * @param arrowIndex
 * @return id
 */
int Gladiador::getHitTower(int pathIndex, int arrowIndex) {

    int towerId = hits[pathIndex][arrowIndex];

    if (towerId != 0) {
        return towerId;
    }
    else {
        return -1;
    }

}

/**
 * Establece la resistencia luego de verificar cuanto ha sido golpeado el gladiador.
 * @param pathIndex
 */
void Gladiador::restarResistencia(int pathIndex) {

    for (int i = 1; i < 24; i++) {

        int gladiatorId = hits[pathIndex][0];

        int towerId = hits[pathIndex][i];

        int resultantX = cuadricula->getNode(gladiatorId)->getXCoord() - cuadricula->getNode(towerId)->getXCoord();
        int resultantY = cuadricula->getNode(gladiatorId)->getYCoord() - cuadricula->getNode(towerId)->getYCoord();

        if (towerId != 0 && pathIndex != 0) {

            if (cuadricula->getNode(towerId) != nullptr) {

                int towerType = cuadricula->getNode(towerId)->getTorre()->getTipo();

                cout << "TowerType @ restarResistencia: " << towerType << endl;

                if ( towerType == 1 && abs(resultantX) == 1 && abs(resultantY) == 1 ) {

                    resistencia -= 1;

                } else if (towerType == 2) {

                    resistencia -= 2;

                } else if (towerType == 3) {

                    resistencia -= 4;

                } else {

                   cout << "restarResistencia: failed" << endl;

                }

                if (resistencia < 0) {
                    resistencia = 0;
                    return;
                }

            }

        } else {

            //cout << "restarResistencia: Id not correct " << endl;

        }

    }

}

/**
 * Obtiene la direccion de la flecha de donde es disparada.
 * @param pathIndex
 * @param towerIndex
 * @return int con direccion
 */
int Gladiador::getArrowDirection(int pathIndex, int towerIndex) {
    int gladiatorId = hits[pathIndex][0];
    int towerId = hits[pathIndex][towerIndex];

    int resultantX = cuadricula->getNode(gladiatorId)->getXCoord() - cuadricula->getNode(towerId)->getXCoord();

    int resultantY = cuadricula->getNode(gladiatorId)->getYCoord() - cuadricula->getNode(towerId)->getYCoord();

    ///Diagonal izquierda arriba
    if ( (resultantX == -2 && resultantY == -2) || (resultantX == -1 && resultantY == -2) ||
         (resultantX == -2 && resultantY == -1) || (resultantX == -1 && resultantY == -1) ) {
        return 0;
    }

    ///Arriba
    else if ( (resultantX == 0 && resultantY == -2) || (resultantX == 0 && resultantY == 2) ) {
        return 1;
    }

    ///Diagonal derecha arriba
    else if ( (resultantX == 1 && resultantY == -2 ) || (resultantX == 2 && resultantY == -2) ||
              (resultantX == 1 && resultantY == -1 ) || (resultantX == 2 && resultantY == -1) ) {
        return 2;
    }

    ///Izquierda
    else if ( (resultantX == -2 && resultantY == 0 ) || (resultantX == -1 && resultantY == 0 ) ) {
        return 3;
    }

    ///Derecha
    else if ( (resultantX == 1 && resultantY == 0 ) || (resultantX == 2 && resultantY == 0 ) ) {
        return 4;
    }

    ///Diagonal izquierda abajo
    else if ( (resultantX == -2 && resultantY == 1 ) || (resultantX == -1 && resultantY == 1 ) ||
              (resultantX == -2 && resultantY == 2 ) || (resultantX == -1 && resultantY == 2 ) ) {
        return 5;
    }

    ///Abajo
    else if ( (resultantX == 0 && resultantY == 1 ) || (resultantX == 0 && resultantY == 2 ) ) {
        return 6;
    }

    ///Diagonal derecha abajo
    else if ( (resultantX == 1 && resultantY == 1 ) || (resultantX == 2 && resultantY == 1 ) ||
              (resultantX == 1 && resultantY == 2 ) || (resultantX == 2 && resultantY == 2 ) ) {
        return 7;
    }
    else {
        return 8;
    }

}


///Getters & Setters


void Gladiador::setNombre(string Nombre)
{
    nombre = Nombre;
}

void Gladiador::setEdad(int Edad)
{
    edad = Edad;
}

void Gladiador::setProbabilidadSupervivencia(int PS)
{
    probabilidadSupervivencia = PS;
}

void Gladiador::setExpectativaVida(int EV)
{
    expectativaVida = EV;
}

void Gladiador::setInteligencia(int Inteligencia)
{
    inteligencia = Inteligencia;
}

void Gladiador::setCondicionFisica(int CF)
{
    condicionFisica = CF;
}

void Gladiador::setFuerzaSuperior(int FS)
{
    fuerzaSuperior = FS;
}

void Gladiador::setFuerzaInferior(int FI)
{
    fuerzaInferior = FI;
}

void Gladiador::setResistencia()
{
    int resist=0;
    if(70<=edad){
        muerto=true;
    }

    else {
        if(25 <= edad && edad <= 45){
            resist += 20;
        }
        else if (25 > edad){
            resist += 15;
        }
        else if (45 < edad){
            resist += 10;
        }
        resist += 2*inteligencia;
        resist += 2*condicionFisica;
        resist += 2*fuerzaInferior;
        resist += 2*fuerzaSuperior;
    }

    resistencia = resist;

}

void Gladiador::morir(){
    muerto=true;
}

bool Gladiador::getMuerto(){
    return muerto;
}

string Gladiador::getNombre()
{
    return nombre;
}

int Gladiador::getEdad()
{
    return edad;
}

int Gladiador::getProbabilidadSupervivencia()
{
    return probabilidadSupervivencia;
}

int Gladiador::getExpectativaVida()
{
    return expectativaVida;
}

int Gladiador::getInteligencia()
{
    return inteligencia;
}

int Gladiador::getCondicionFisica()
{
    return condicionFisica;
}

int Gladiador::getFuerzaSuperior()
{
    return fuerzaSuperior;
}

int Gladiador::getFuerzaInferior()
{
    return fuerzaInferior;
}

int Gladiador::getResistencia()
{
    return resistencia;
}

void Gladiador::setResistencia(int id)
{
    resistencia-=id;
}

vector<int> Gladiador::getPathToGoal() {
    return pathToGoal;
}

void Gladiador::setPathToGoal(vector<int> _pathToGoal) {
    pathToGoal = _pathToGoal;
}

void Gladiador::setNombrePadre1(string _nombre) {
    nombrePadre1 = _nombre;
}

void Gladiador::setNombrePadre2(string _nombre) {
    nombrePadre2 = _nombre;
}

string Gladiador::getNombrePadre1() {
    return nombrePadre1;
}

string Gladiador::getNombrePadre2() {
    return nombrePadre2;
}

void Gladiador::setGeneracion(int _generacion) {
    generacion = _generacion;
}

int Gladiador::getGeneracion() {
    return generacion;
}
Cuadricula* Gladiador::getCuadricula() {
    return cuadricula;
}

void Gladiador::setCuadricula(Cuadricula* _cuadricula) {
    cuadricula = _cuadricula;
}
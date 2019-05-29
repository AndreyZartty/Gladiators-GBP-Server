
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <json-c/json.h>
#include <iostream>
#include <thread>

#include "Gladiador.h"
#include "poblacion.h"
#include "list.h"
#include "Juego.h"


#include <gtest/gtest.h>

#define PORT 3550
#define BACKLOG 4
#define MAXDATASIZE 1000



using namespace std;


/**
 * Main del programa
 *
 * @since 30/04/19
 */


///Instancia estatica del juego
static Juego* juego;
static int pathIndexG1 = 0;
static int pathIndexG2 = 0;

static int indiceGen = 0;
static int indiceGlad = 0;
static int indicePob = 0;

/**
 * Retorna al cliente el tamaño de la Zona de Intimidación.
 * @return JSON
 */
string sendZoneSize() {

    int zoneSize = juego->getCuadricula()->getSize();

    json_object *jobjZoneSize = json_object_new_object();

    json_object *jstringZoneSize = json_object_new_string(to_string(zoneSize).c_str());

    json_object_object_add(jobjZoneSize,"ZONESIZE", jstringZoneSize);

    return json_object_to_json_string(jobjZoneSize);

}

/**
 * Envia un JSON con la coordenada del Nodo deseado.
 * @param coord
 * @param id
 * @return JSON
 */
string sendCoord(string coord, string id) {

    int coordToSend;

    if (coord == "x") {

        coordToSend = juego->getCuadricula()->getNode( stoi(id) )->getXCoord();

        json_object *jobjXCoord = json_object_new_object();

        json_object *jstringXCoord = json_object_new_string(to_string(coordToSend).c_str());

        json_object_object_add(jobjXCoord,"XCOORD", jstringXCoord);

        return json_object_to_json_string(jobjXCoord);

    }
    else if (coord == "y") {

        coordToSend = juego->getCuadricula()->getNode( stoi(id) )->getYCoord();

        json_object *jobjYCoord = json_object_new_object();

        json_object *jstringYCoord = json_object_new_string(to_string(coordToSend).c_str());

        json_object_object_add(jobjYCoord,"YCOORD", jstringYCoord);

        return json_object_to_json_string(jobjYCoord);

    } else {
        cout << "Error en sendCoord" << endl;
        coordToSend = -1;
    }

}

/**
 * Retorna la coordenada de la Torre deseada.
 * @param coord
 * @param i
 * @return JSON
 */
string sendCoordTorre(string coord, string i) {

    int index = stoi(i);

    int vectorSize = (int) juego->getCuadricula()->getTowerIdList().size();

    int coordToSendTorre;

    if (index < vectorSize) {

        int id = juego->getCuadricula()->getTowerIdList()[index];

        if ( coord == "x") {

            Node* nodeToGetCoord = juego->getCuadricula()->getNode( id );

            if (nodeToGetCoord != nullptr) {
                coordToSendTorre = nodeToGetCoord->getXCoord();
            }
            else {
                coordToSendTorre = -1;
            }

            json_object *jobjXCoordTorre = json_object_new_object();

            json_object *jstringXCoordTorre = json_object_new_string(to_string(coordToSendTorre).c_str());

            json_object_object_add(jobjXCoordTorre,"XCOORDTORRE", jstringXCoordTorre);

            return json_object_to_json_string(jobjXCoordTorre);

        }
        else if (coord == "y") {

            Node* nodeToGetCoord = juego->getCuadricula()->getNode( id );

            if (nodeToGetCoord != nullptr) {
                coordToSendTorre = nodeToGetCoord->getYCoord();
            }
            else {
                coordToSendTorre = -1;
            }

            json_object *jobjYCoordTorre = json_object_new_object();

            json_object *jstringYCoordTorre = json_object_new_string(to_string(coordToSendTorre).c_str());

            json_object_object_add(jobjYCoordTorre,"YCOORDTORRE", jstringYCoordTorre);

            return json_object_to_json_string(jobjYCoordTorre);

        }
        else {

            coordToSendTorre = -1;

        }

    }

    if ( coord == "x") {

        coordToSendTorre = -1;

        json_object *jobjXCoordTorre = json_object_new_object();

        json_object *jstringXCoordTorre = json_object_new_string(to_string(coordToSendTorre).c_str());

        json_object_object_add(jobjXCoordTorre,"XCOORDTORRE", jstringXCoordTorre);

        return json_object_to_json_string(jobjXCoordTorre);

    }
    else if (coord == "y") {


        coordToSendTorre = -1;

        json_object *jobjYCoordTorre = json_object_new_object();

        json_object *jstringYCoordTorre = json_object_new_string(to_string(coordToSendTorre).c_str());

        json_object_object_add(jobjYCoordTorre,"YCOORDTORRE", jstringYCoordTorre);

        return json_object_to_json_string(jobjYCoordTorre);

    }

}

/**
 * Retorna la coordenada para el Gladiador deseado.
 * @param poblacion
 * @param coord
 * @param i
 * @return JSON
 */
string sendCoordGladiador(string poblacion, string coord, string i) {

    int index = stoi(i);

    int vectorSize;

    int coordToSendGladiator;

    ///Guarda el tamaño del vector dependiendo de su poblacion
    if (poblacion == "1") {
        vectorSize = (int) juego->getAStarAlgorithm()->showPath().size();
    }
    else if (poblacion == "2") {
        vectorSize = (int) juego->getBacktrackingAlgorithm()->showPath().size();
    }

    ///Cuando continua dentro del vector
    if (index < vectorSize) {

        if (poblacion == "1") {

            int id = juego->getAStarAlgorithm()->showPath()[index];

            if ( coord == "x") {

                coordToSendGladiator = juego->getCuadricula()->getNode( id )->getXCoord();

                json_object *jobjXCoordGladiador = json_object_new_object();

                json_object *jstringXCoordGladiador = json_object_new_string(to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGladiador,"XCOORDGP1", jstringXCoordGladiador);

                return json_object_to_json_string(jobjXCoordGladiador);

            }
            else if (coord == "y") {

                coordToSendGladiator = juego->getCuadricula()->getNode( id )->getYCoord();

                json_object *jobjYCoordGladiador = json_object_new_object();

                json_object *jstringYCoordGladiador = json_object_new_string(to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjYCoordGladiador,"YCOORDGP1", jstringYCoordGladiador);

                return json_object_to_json_string(jobjYCoordGladiador);

            }

            else {

                coordToSendGladiator = -1;

            }

        } else if (poblacion == "2") {

            int id = juego->getBacktrackingAlgorithm()->showPath()[index];

            if ( coord == "x") {

                coordToSendGladiator = juego->getCuadricula()->getNode( id )->getXCoord();

                json_object *jobjXCoordGladiador = json_object_new_object();

                json_object *jstringXCoordGladiador = json_object_new_string(to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGladiador,"XCOORDGP2", jstringXCoordGladiador);

                return json_object_to_json_string(jobjXCoordGladiador);

            }

            else if (coord == "y") {

                coordToSendGladiator = juego->getCuadricula()->getNode( id )->getYCoord();

                json_object *jobjYCoordGladiador = json_object_new_object();

                json_object *jstringYCoordGladiador = json_object_new_string(to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjYCoordGladiador,"YCOORDGP2", jstringYCoordGladiador);

                return json_object_to_json_string(jobjYCoordGladiador);

            }
            else {

                coordToSendGladiator = -1;

            }

        } else {

            cout << "No existe esta poblacion." << endl;

        }

    }

    ///Cuando ya ha terminado el vector
    else {


        if (poblacion == "1") {


            if (coord == "x") {

                coordToSendGladiator = -1;

                json_object *jobjXCoordGP1 = json_object_new_object();

                json_object *jstringXCoordGladiadorGP1 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGP1, "XCOORDGP1", jstringXCoordGladiadorGP1);

                return json_object_to_json_string(jobjXCoordGP1);

            } else if (coord == "y") {

                coordToSendGladiator = -1;

                json_object *jobjYCoordGP1 = json_object_new_object();

                json_object *jstringYCoordGladiadorGP1 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjYCoordGP1, "YCOORDGP1", jstringYCoordGladiadorGP1);

                return json_object_to_json_string(jobjYCoordGP1);

            }

        } else if (poblacion == "2") {


            if (coord == "x") {

                coordToSendGladiator = -1;

                json_object *jobjXCoordGP2 = json_object_new_object();

                json_object *jstringXCoordGladiadorGP2 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGP2, "XCOORDGP2", jstringXCoordGladiadorGP2);

                return json_object_to_json_string(jobjXCoordGP2);

            } else if (coord == "y") {

                coordToSendGladiator = -1;

                json_object *jobjYCoordGP2 = json_object_new_object();

                json_object *jstringYCoordGladiadorGP2 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjYCoordGP2, "YCOORDGP2", jstringYCoordGladiadorGP2);

                return json_object_to_json_string(jobjYCoordGP2);

            }

        }

    }

}

/**
 * Retorna un bool al cliente si este va a ser golpeado por una torre o no
 * @param gladiador
 * @param arrowIndex
 * @return JSON
 */
string sendHit(string gladiador, string arrowIndex) {

    Gladiador* gladInstance;
    int hit;

    if ( gladiador == "1" ) {

        gladInstance = juego->getGladiador1();

        hit = gladInstance->isHit(pathIndexG1, stoi(arrowIndex) );

        json_object *jobjHit = json_object_new_object();

        json_object *jstringHit = json_object_new_string( to_string(hit).c_str());

        json_object_object_add(jobjHit, "HITG1", jstringHit);

        return json_object_to_json_string(jobjHit);



    } else if (gladiador == "2") {

        gladInstance = juego->getGladiador2();

        hit = gladInstance->isHit(pathIndexG2, stoi(arrowIndex) );

        json_object *jobjHit = json_object_new_object();

        json_object *jstringHit = json_object_new_string( to_string(hit).c_str());

        json_object_object_add(jobjHit, "HITG2", jstringHit);

        return json_object_to_json_string(jobjHit);

    }
    else {
        cout << "sendHit failed" << endl;
    }

}




string sendCoordFlecha(string gladiador, string coord, string arrowIndex) {

    int indexFlecha = stoi(arrowIndex);

    if (gladiador == "1") {

        Gladiador* gladInstance1 = juego->getGladiador1();

        if ( coord == "x") {

            int coordToSend = gladInstance1->getHitTower(pathIndexG1,indexFlecha);

            int xCoord = juego->getCuadricula()->getNode(coordToSend)->getXCoord();

        }
        else if (coord == "y") {

            int coordToSend = gladInstance1->getHitTower(pathIndexG1,indexFlecha);

            int yCoord = juego->getCuadricula()->getNode(coordToSend)->getYCoord();

        }

        else {



        }

    } else if (gladiador == "2") {

        Gladiador* gladInstance2 = juego->getGladiador2();

        if ( coord == "x") {



        }

        else if (coord == "y") {



        }
        else {



        }

    } else {

        cout << "sendCoordFlecha: gladiador failed" << endl;

    }

}

/**
 * Envia un JSON con el tipo de flecha y su dirección para ser graficado.
 * @param gladiador
 * @param arrowIndex
 * @return
 */
string sendAType(string gladiador, string arrowIndex) {

    int indexFlecha = stoi(arrowIndex);

    if (gladiador == "1") {

        Gladiador* gladInstance1 = juego->getGladiador1();

        int towerId = gladInstance1->getHitTower(pathIndexG1,indexFlecha);

        Node* towerNode = juego->getCuadricula()->getNode(towerId);

        int aTypeToSend1 = -1;

        if (towerNode != nullptr) {
            cout << "sendAType: " << towerNode->getTorre()->getTipo() << endl;
            aTypeToSend1 = towerNode->getTorre()->getTipo() * 10;
            aTypeToSend1 += juego->getGladiador1()->getArrowDirection(pathIndexG1,indexFlecha);
        } else {
            aTypeToSend1 = -1;
        }

        json_object *jobjATypeToSend1 = json_object_new_object();

        json_object *jstringATypeToSend1 = json_object_new_string( to_string(aTypeToSend1).c_str());

        json_object_object_add(jobjATypeToSend1, "ATYPEG1", jstringATypeToSend1);

        return json_object_to_json_string(jobjATypeToSend1);


    } else if (gladiador == "2") {

        Gladiador* gladInstance2 = juego->getGladiador2();

        int towerId = gladInstance2->getHitTower(pathIndexG2,indexFlecha);

        Node* towerNode = juego->getCuadricula()->getNode(towerId);

        int aTypeToSend2 = 10;

        if (towerNode != nullptr) {
            cout << "sendAType: " << towerNode->getTorre()->getTipo() << endl;
            aTypeToSend2 = towerNode->getTorre()->getTipo() * 10;
            aTypeToSend2 += juego->getGladiador2()->getArrowDirection(pathIndexG2,indexFlecha);
        } else {
            aTypeToSend2 = -1;
        }

        json_object *jobjATypeToSend2 = json_object_new_object();

        json_object *jstringATypeToSend2 = json_object_new_string( to_string(aTypeToSend2).c_str());

        json_object_object_add(jobjATypeToSend2, "ATYPEG2", jstringATypeToSend2);

        return json_object_to_json_string(jobjATypeToSend2);


    } else {

        cout << "sendAType: failed" << endl;

    }

}

/**
 * Envia un JSON con todos los atributos del Gladiador para ser graficado en la historia genética de la población.
 * @return JSON
 */
string sendGladiador() {

    ///Gladiador temporal
    Gladiador *gtmp;

    ///Atributos temporales por mandar
    string nombretmp;
    string edadtmp;
    string probsuptmp;
    string expecttmp;
    string inteltmp;
    string condfistmp;
    string frzsuptmp;
    string frzinftmp;
    string resisttmp;
    string muertotmp;
    string gentmp;
    string pad1tmp;
    string pad2tmp;

    json_object *jobjGlad = json_object_new_object();

    if (indiceGlad>=juego->getPoblacion1()->getGeneracion()){
        if(indicePob==1) {
            json_object *jstring1 = json_object_new_string("X");
            json_object *jstring2 = json_object_new_string("X");
            json_object *jstring3 = json_object_new_string("X");
            json_object *jstring4 = json_object_new_string("X");
            json_object *jstring5 = json_object_new_string("X");
            json_object *jstring6 = json_object_new_string("X");
            json_object *jstring7 = json_object_new_string("X");
            json_object *jstring8 = json_object_new_string("X");
            json_object *jstring9 = json_object_new_string("X");
            json_object *jstring10 = json_object_new_string("X");
            json_object *jstring11 = json_object_new_string("X");
            json_object *jstring12 = json_object_new_string("X");
            json_object *jstring13 = json_object_new_string("X");

            json_object_object_add(jobjGlad,"NOMBRE",jstring1);
            json_object_object_add(jobjGlad,"EDAD",jstring2);
            json_object_object_add(jobjGlad,"PROBSUP",jstring3);
            json_object_object_add(jobjGlad,"EXPECT",jstring4);
            json_object_object_add(jobjGlad,"INTEL",jstring5);
            json_object_object_add(jobjGlad,"CONDFIS",jstring6);
            json_object_object_add(jobjGlad,"FRZSUP",jstring7);
            json_object_object_add(jobjGlad,"FRZINF",jstring8);
            json_object_object_add(jobjGlad,"RESIST",jstring9);
            json_object_object_add(jobjGlad,"MUERTO",jstring10);
            json_object_object_add(jobjGlad,"GEN",jstring11);
            json_object_object_add(jobjGlad,"PAD1",jstring12);
            json_object_object_add(jobjGlad,"PAD2",jstring13);
        }else{
            json_object *jstring1 = json_object_new_string("Y");
            json_object *jstring2 = json_object_new_string("Y");
            json_object *jstring3 = json_object_new_string("Y");
            json_object *jstring4 = json_object_new_string("Y");
            json_object *jstring5 = json_object_new_string("Y");
            json_object *jstring6 = json_object_new_string("Y");
            json_object *jstring7 = json_object_new_string("Y");
            json_object *jstring8 = json_object_new_string("Y");
            json_object *jstring9 = json_object_new_string("Y");
            json_object *jstring10 = json_object_new_string("Y");
            json_object *jstring11 = json_object_new_string("Y");
            json_object *jstring12 = json_object_new_string("Y");
            json_object *jstring13 = json_object_new_string("Y");

            json_object_object_add(jobjGlad,"NOMBRE",jstring1);
            json_object_object_add(jobjGlad,"EDAD",jstring2);
            json_object_object_add(jobjGlad,"PROBSUP",jstring3);
            json_object_object_add(jobjGlad,"EXPECT",jstring4);
            json_object_object_add(jobjGlad,"INTEL",jstring5);
            json_object_object_add(jobjGlad,"CONDFIS",jstring6);
            json_object_object_add(jobjGlad,"FRZSUP",jstring7);
            json_object_object_add(jobjGlad,"FRZINF",jstring8);
            json_object_object_add(jobjGlad,"RESIST",jstring9);
            json_object_object_add(jobjGlad,"MUERTO",jstring10);
            json_object_object_add(jobjGlad,"GEN",jstring11);
            json_object_object_add(jobjGlad,"PAD1",jstring12);
            json_object_object_add(jobjGlad,"PAD2",jstring13);
        }

        indiceGen=0;
        indiceGlad=0;
        indicePob+=1;

    }
    else {

        if (indicePob == 1) {
            gtmp = juego->getPoblacion1()->getGeneraciones()[indiceGen]->recorrer(indiceGlad);
            if (gtmp == nullptr) {
                indiceGen += 1;
                indiceGlad = 0;
                return sendGladiador();
            }

        } else {
            gtmp = juego->getPoblacion2()->getGeneraciones()[indiceGen]->recorrer(indiceGlad);
            if (gtmp == nullptr) {
                indiceGen += 1;
                indiceGlad = 0;
                return sendGladiador();
            }
        }

        nombretmp = gtmp->getNombre();
        edadtmp = to_string(gtmp->getEdad());
        probsuptmp = to_string(gtmp->getProbabilidadSupervivencia());
        expecttmp = to_string(gtmp->getExpectativaVida());
        inteltmp = to_string(gtmp->getInteligencia());
        condfistmp = to_string(gtmp->getCondicionFisica());
        frzsuptmp = to_string(gtmp->getFuerzaSuperior());
        frzinftmp = to_string(gtmp->getFuerzaInferior());
        resisttmp = to_string(gtmp->getResistencia());
        muertotmp = to_string(gtmp->getMuerto());
        gentmp = to_string(gtmp->getGeneracion());
        pad1tmp = gtmp->getNombrePadre1();
        pad2tmp = gtmp->getNombrePadre2();

        json_object *jstring1 = json_object_new_string(nombretmp.c_str());
        json_object *jstring2 = json_object_new_string(edadtmp.c_str());
        json_object *jstring3 = json_object_new_string(probsuptmp.c_str());
        json_object *jstring4 = json_object_new_string(expecttmp.c_str());
        json_object *jstring5 = json_object_new_string(inteltmp.c_str());
        json_object *jstring6 = json_object_new_string(condfistmp.c_str());
        json_object *jstring7 = json_object_new_string(frzsuptmp.c_str());
        json_object *jstring8 = json_object_new_string(frzinftmp.c_str());
        json_object *jstring9 = json_object_new_string(resisttmp.c_str());
        json_object *jstring10 = json_object_new_string(muertotmp.c_str());
        json_object *jstring11 = json_object_new_string(gentmp.c_str());
        json_object *jstring12 = json_object_new_string(pad1tmp.c_str());
        json_object *jstring13 = json_object_new_string(pad2tmp.c_str());

        json_object_object_add(jobjGlad,"NOMBRE",jstring1);
        json_object_object_add(jobjGlad,"EDAD",jstring2);
        json_object_object_add(jobjGlad,"PROBSUP",jstring3);
        json_object_object_add(jobjGlad,"EXPECT",jstring4);
        json_object_object_add(jobjGlad,"INTEL",jstring5);
        json_object_object_add(jobjGlad,"CONDFIS",jstring6);
        json_object_object_add(jobjGlad,"FRZSUP",jstring7);
        json_object_object_add(jobjGlad,"FRZINF",jstring8);
        json_object_object_add(jobjGlad,"RESIST",jstring9);
        json_object_object_add(jobjGlad,"MUERTO",jstring10);
        json_object_object_add(jobjGlad,"GEN",jstring11);
        json_object_object_add(jobjGlad,"PAD1",jstring12);
        json_object_object_add(jobjGlad,"PAD2",jstring13);



        indiceGlad += 1;
    }

    return json_object_to_json_string(jobjGlad);
}

/**
 * Envia un JSON para confirmar la modificación del pathIndex para conocer por que posicion del path se encuentra el gladiador deseado
 * @param gladiador
 * @param modificacion
 * @return JSON
 */
string changePathIndex(string gladiador, string modificacion) {

    int mod = stoi(modificacion);

    if (gladiador == "1") {

        pathIndexG1++;

        if (mod == 1) {
            pathIndexG1 = 0;
        }

    } else if (gladiador == "2") {

        pathIndexG2++;

        if (mod == 1) {
            pathIndexG2 = 0;
        }

    } else {
        cout << " changePathIndex: failed " << endl;
    }

}

/**
 * Envia un JSON con la resistencia que le queda al gladiador respectivo
 * @param gladiador
 * @return JSON
 */
string sendResistencia(string gladiador) {

    if (gladiador == "1") {

        Gladiador* gladInstance1 = juego->getGladiador1();

        gladInstance1->restarResistencia(pathIndexG1);

        int resistencia1 = gladInstance1->getResistencia();

        json_object *jobjResistencia1 = json_object_new_object();

        json_object *jstringResistencia1 = json_object_new_string( to_string(resistencia1).c_str());

        json_object_object_add(jobjResistencia1, "RESISTENCIAG1", jstringResistencia1);

        return json_object_to_json_string(jobjResistencia1);

    }
    else if (gladiador == "2") {

        Gladiador* gladInstance2 = juego->getGladiador2();

        gladInstance2->restarResistencia(pathIndexG2);

        int resistencia2 = gladInstance2->getResistencia();

        json_object *jobjResistencia2 = json_object_new_object();

        json_object *jstringResistencia2 = json_object_new_string( to_string(resistencia2).c_str());

        json_object_object_add(jobjResistencia2, "RESISTENCIAG2", jstringResistencia2);

        return json_object_to_json_string(jobjResistencia2);

    }
    else {
        cout << "sendResistencia: failed" << endl;
    }

}

/**
 * Genera los atributos y clases necesarias para el inicio y seguimiento del juego.
 * @param tipo
 */
void iniciar(string tipo) {

    if (tipo == "0") {

        ///Genera las torres por primera vez
        juego->generateTowers(3);

        ///Genera el camino para ambos gladiadores por medio de su algoritmo
        juego->doBacktracking();
        juego->doAStar();

    } else if (tipo == "1") {

        ///Nuevas generaciones de las poblaciones
        juego->getPoblacion1()->nuevageneracion();
        juego->getPoblacion2()->nuevageneracion();

        ///Mejores gladiadores de cada poblacion
        juego->setGladiador1(juego->getPoblacion1()->getMejor());
        juego->setGladiador2(juego->getPoblacion2()->getMejor());

        ///Añade a los gladiadores la cuadricula
        juego->getGladiador1()->setCuadricula(juego->getCuadricula());
        juego->getGladiador2()->setCuadricula(juego->getCuadricula());

        ///Agrega tres torres a la Zona de Intimidación
        juego->generateTowers(3);

        ///Genera el camino para ambos gladiadores por medio de su algoritmo
        juego->doBacktracking();
        juego->doAStar();


    } else if (tipo == "2") {

            ///Para actualizarlo en la tercera iteración por cada movimiento del gladiador.

            int cantTorres = juego->getCuadricula()->getTowerIdList().size();

            juego->getCuadricula()->getTowerIdList().clear();

        for(int i=0; i<juego->getCuadricula()->getSize()*juego->getCuadricula()->getSize(); i++){

            juego->getCuadricula()->getNode(i)->setTorre(nullptr);

        }

        juego->generateTowers(cantTorres);

        ///Genera el camino para ambos gladiadores por medio de su algoritmo
        juego->doBacktracking();
        juego->doAStar();

        

    }

}

/**
 * Envia un JSON con los labels necesarios para que aparezcan en tiempo real.
 * @return JSON
 */
string sendLiveLabels() {

    json_object *jobjLivelabels = json_object_new_object();

    ///Gladiador 1

    string nombreG1 = juego->getGladiador1()->getNombre();
    string edadG1 = to_string(juego->getGladiador1()->getEdad());
    string resistenciaG1 = to_string(juego->getGladiador1()->getResistencia());
    string inteligenciaG1 = to_string(juego->getGladiador1()->getInteligencia());
    string tSuperiorG1 = to_string(juego->getGladiador1()->getFuerzaSuperior());
    string tInferiorG1 = to_string(juego->getGladiador1()->getFuerzaInferior());
    string probabilidadG1 = to_string(juego->getGladiador1()->getProbabilidadSupervivencia());
    string expectativaG1 = to_string(juego->getGladiador1()->getExpectativaVida());

    json_object *jstringNombreG1 = json_object_new_string(nombreG1.c_str());
    json_object *jstringEdadG1 = json_object_new_string(edadG1.c_str());
    json_object *jstringResistenciaG1 = json_object_new_string(resistenciaG1.c_str());
    json_object *jstringInteligenciaG1 = json_object_new_string(inteligenciaG1.c_str());
    json_object *jstringTSuperiorG1 = json_object_new_string(tSuperiorG1.c_str());
    json_object *jstringTInferiorG1 = json_object_new_string(tInferiorG1.c_str());
    json_object *jstringProbabilidadG1 = json_object_new_string(probabilidadG1.c_str());
    json_object *jstringExpectativaG1 = json_object_new_string(expectativaG1.c_str());

    json_object_object_add(jobjLivelabels, "NOMBREG1", jstringNombreG1);
    json_object_object_add(jobjLivelabels, "EDADG1", jstringEdadG1);
    json_object_object_add(jobjLivelabels, "RESISTENCIAG1", jstringResistenciaG1);
    json_object_object_add(jobjLivelabels, "INTELIGENCIAG1", jstringInteligenciaG1);
    json_object_object_add(jobjLivelabels, "TSUPERIORG1", jstringTSuperiorG1);
    json_object_object_add(jobjLivelabels, "TINFERIORG1", jstringTInferiorG1);
    json_object_object_add(jobjLivelabels, "PROBABILIDADG1", jstringProbabilidadG1);
    json_object_object_add(jobjLivelabels, "EXPECTATIVAG1", jstringExpectativaG1);


    ///Gladiador 2

    string nombreG2 = juego->getGladiador2()->getNombre();
    string edadG2 = to_string(juego->getGladiador2()->getEdad());
    string resistenciaG2 = to_string(juego->getGladiador2()->getResistencia());
    string inteligenciaG2 = to_string(juego->getGladiador2()->getInteligencia());
    string tSuperiorG2 = to_string(juego->getGladiador2()->getFuerzaSuperior());
    string tInferiorG2 = to_string(juego->getGladiador2()->getFuerzaInferior());
    string probabilidadG2 = to_string(juego->getGladiador2()->getProbabilidadSupervivencia());
    string expectativaG2 = to_string(juego->getGladiador2()->getExpectativaVida());

    json_object *jstringNombreG2 = json_object_new_string(nombreG2.c_str());
    json_object *jstringEdadG2 = json_object_new_string(edadG1.c_str());
    json_object *jstringResistenciaG2 = json_object_new_string(resistenciaG1.c_str());
    json_object *jstringInteligenciaG2 = json_object_new_string(inteligenciaG2.c_str());
    json_object *jstringTSuperiorG2 = json_object_new_string(tSuperiorG1.c_str());
    json_object *jstringTInferiorG2 = json_object_new_string(tInferiorG1.c_str());
    json_object *jstringProbabilidadG2 = json_object_new_string(probabilidadG2.c_str());
    json_object *jstringExpectativaG2 = json_object_new_string(expectativaG2.c_str());

    json_object_object_add(jobjLivelabels, "NOMBREG2", jstringNombreG2);
    json_object_object_add(jobjLivelabels, "EDADG2", jstringEdadG2);
    json_object_object_add(jobjLivelabels, "RESISTENCIAG2", jstringResistenciaG2);
    json_object_object_add(jobjLivelabels, "INTELIGENCIAG2", jstringInteligenciaG2);
    json_object_object_add(jobjLivelabels, "TSUPERIORG2", jstringTSuperiorG2);
    json_object_object_add(jobjLivelabels, "TINFERIORG2", jstringTInferiorG2);
    json_object_object_add(jobjLivelabels, "PROBABILIDADG2", jstringProbabilidadG2);
    json_object_object_add(jobjLivelabels, "EXPECTATIVAG2", jstringExpectativaG2);

    return json_object_to_json_string(jobjLivelabels);

}

/**
 * Corre el servidor
 * @return int
 */
int runServer() {

    int fd, fd2;

    struct sockaddr_in server;

    struct sockaddr_in client;


    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("error en socket()\n");
        exit(-1);
    }

    server.sin_family = AF_INET;

    server.sin_port = htons(PORT);

    server.sin_addr.s_addr = INADDR_ANY;

    bzero(&(server.sin_zero), 8);

    if (bind(fd, (struct sockaddr *) &server,
             sizeof(struct sockaddr)) == -1) {
        printf("error en bind() \n");
        exit(-1);
    }

    if (listen(fd, BACKLOG) == -1) {
        printf("error en listen()\n");
        exit(-1);
    }

    printf("\nServidor 'Gladiators - GBP' abierto.\n");

    while (true) {

        unsigned int address_size = sizeof(client);

        if ((fd2 = accept(fd, (struct sockaddr *) &client,
                          &address_size)) == -1) {
            printf("error en accept()\n");
            exit(-1);
        }

        printf("\nSe obtuvo una conexión de un cliente.\n");

        ssize_t r;

        char buff[MAXDATASIZE];

        for (;;) {
            r = read(fd2, buff, MAXDATASIZE);

            if (r == -1) {
                perror("read");
                return EXIT_FAILURE;
            }
            if (r == 0)
                break;
            printf("\nREAD: %s\n", buff);



            ///JSON Reads



            ///KEY: COMENZAR
            ///Obtiene el flag para comenzar el juego
            struct json_object *tempComenzar;
            //cout<<"COMENZAR"<<endl;
            json_object *parsed_jsonComenzar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonComenzar, "COMENZAR", &tempComenzar);
            //printf("Por comenzar: %s\n", json_object_get_string(tempComenzar));

            ///KEY: XCOORD
            ///Obtiene la coordenada x del nodo deseado
            struct json_object *tempXCoord;
            //cout<<"XCoord"<<endl;
            json_object *parsed_jsonXCoord = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoord, "XCOORD", &tempXCoord);
            //printf("XCoord: %s\n", json_object_get_string(tempXCoord));

            ///KEY: YCOORD
            ///Obtiene la coordenada y del nodo deseado
            struct json_object *tempYCoord;
            //cout<<"YCoord"<<endl;
            json_object *parsed_jsonYCoord = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoord, "YCOORD", &tempYCoord);
            //printf("YCoord: %s\n", json_object_get_string(tempYCoord));

            ///KEY: XCOORDTORRE
            ///Obtiene la coordenada x de la torre deseada
            struct json_object *tempXCoordTorre;
            //cout<<"XCoordTorre"<<endl;
            json_object *parsed_jsonXCoordTorre = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordTorre, "XCOORDTORRE", &tempXCoordTorre);
            //printf("XCoordTorre: %s\n", json_object_get_string(tempXCoordTorre));

            ///KEY: YCOORDTORRE
            ///Obtiene la coordenada y de la torre deseada
            struct json_object *tempYCoordTorre;
            //cout<<"YCoordTorre"<<endl;
            json_object *parsed_jsonYCoordTorre = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordTorre, "YCOORDTORRE", &tempYCoordTorre);
            //printf("YCoordTorre: %s\n", json_object_get_string(tempYCoordTorre));

            ///KEY: XCOORDGP1
            ///Obtiene la coordenada x del gladiador de la poblacion 1
            struct json_object *tempXCoordGP1;
            //cout<<"XCoordGP1"<<endl;
            json_object *parsed_jsonXCoordGP1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordGP1, "XCOORDGP1", &tempXCoordGP1);

            ///KEY: YCOORDGP1
            ///Obtiene la coordenada y del gladiador de la poblacion 1
            struct json_object *tempYCoordGP1;
            //cout<<"YCoordGP1"<<endl;
            json_object *parsed_jsonYCoordGP1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordGP1, "YCOORDGP1", &tempYCoordGP1);

            ///KEY: XCOORDGP2
            ///Obtiene la coordenada x del gladiador de la poblacion 2
            struct json_object *tempXCoordGP2;
            //cout<<"XCoordGP2"<<endl;
            json_object *parsed_jsonXCoordGP2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordGP2, "XCOORDGP2", &tempXCoordGP2);

            ///KEY: YCOORDGP2
            ///Obtiene la coordenada y del gladiador de la poblacion 2
            struct json_object *tempYCoordGP2;
            //cout<<"YCoordGP2"<<endl;
            json_object *parsed_jsonYCoordGP2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordGP2, "YCOORDGP2", &tempYCoordGP2);

            ///KEY: HITG1
            ///Obtiene un request para verificar si el Gladiador 1 será golpeado por una flecha
            struct json_object *tempHitG1;
            //cout<<"HitG1"<<endl;
            json_object *parsed_jsonHitG1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonHitG1, "HITG1", &tempHitG1);

            ///KEY: HITG2
            ///Obtiene un request para verificar si el Gladiador 2 será golpeado por una flecha
            struct json_object *tempHitG2;
            //cout<<"HitG2"<<endl;
            json_object *parsed_jsonHitG2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonHitG2, "HITG2", &tempHitG2);

            ///KEY: ATYPEG1
            ///Obtiene un request para verificar el tipo de flecha con la que ha sido golpeado el gladiador 1
            struct json_object *tempATypeG1;
            //cout<<"ATypeG1"<<endl;
            json_object *parsed_jsonATypeG1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonATypeG1, "ATYPEG1", &tempATypeG1);

            ///KEY: ATYPEG2
            ///Obtiene un request para verificar el tipo de flecha con la que ha sido golpeado el gladiador 2
            struct json_object *tempATypeG2;
            //cout<<"ATypeG2"<<endl;
            json_object *parsed_jsonATypeG2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonATypeG2, "ATYPEG2", &tempATypeG2);

            ///KEY: XCOORDFLECHAG1
            ///Obtiene un request para obtener las coordenadas x de la flecha con la que ha sido golpeado el gladiador 1
            struct json_object *tempXCoordFlechaG1;
            //cout<<"XCoordFlechaG1"<<endl;
            json_object *parsed_jsonXCoordFlechaG1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordFlechaG1, "XCOORDFLECHAG1", &tempXCoordFlechaG1);

            ///KEY: YCOORDFLECHAG1
            ///Obtiene un request para obtener las coordenadas y de la flecha con la que ha sido golpeado el gladiador 2
            struct json_object *tempYCoordFlechaG1;
            //cout<<"YCoordFlechaG1"<<endl;
            json_object *parsed_jsonYCoordFlechaG1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordFlechaG1, "YCOORDFLECHAG1", &tempYCoordFlechaG1);

            ///KEY: XCOORDFLECHAG2
            ///Obtiene un request para obtener las coordenadas x de la flecha con la que ha sido golpeado el gladiador 1
            struct json_object *tempXCoordFlechaG2;
            //cout<<"XCoordFlechaG2"<<endl;
            json_object *parsed_jsonXCoordFlechaG2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordFlechaG2, "XCOORDFLECHAG2", &tempXCoordFlechaG2);

            ///KEY: YCOORDFLECHAG2
            ///Obtiene un request para obtener las coordenadas y de la flecha con la que ha sido golpeado el gladiador 2
            struct json_object *tempYCoordFlechaG2;
            //cout<<"YCoordFlechaG2"<<endl;
            json_object *parsed_jsonYCoordFlechaG2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordFlechaG2, "YCOORDFLECHAG2", &tempYCoordFlechaG2);

            ///KEY: RESISTENCIAG1
            ///Obtiene un request para obtener la resistencia del gladiador 1
            struct json_object *tempResistenciaG1;
            //cout<<"ResistenciaG1"<<endl;
            json_object *parsed_jsonResistenciaG1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonResistenciaG1, "RESISTENCIAG1", &tempResistenciaG1);

            ///KEY: RESISTENCIAG2
            ///Obtiene un request para obtener la resistencia del gladiador 2
            struct json_object *tempResistenciaG2;
            //cout<<"ResistenciaG2"<<endl;
            json_object *parsed_jsonResistenciaG2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonResistenciaG2, "RESISTENCIAG2", &tempResistenciaG2);

            ///KEY: GMUERTO
            ///Obtiene un request para obtener la resistencia del gladiador 2
            struct json_object *tempGMUERTO;
            //cout<<"GMUERTO"<<endl;
            json_object *parsed_jsonGMUERTO = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonGMUERTO, "GMUERTO", &tempGMUERTO);
            ///KEY: STORICLABELS
            ///Obtiene un request para
            struct json_object *tempPobla1;
            cout<<"STORIC LABELS"<<endl;
            json_object *parsed_jsonPobla1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPobla1, "STORICLABELS", &tempPobla1);

            /*
            ///KEY: POBLA2
            ///Obtiene un request para
            struct json_object *tempPobla2;
            cout<<"Pobla2"<<endl;
            json_object *parsed_jsonPobla2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPobla2, "POBLA2", &tempPobla2);
*/

            /*///KEY: ASTAR
            ///Genera la ejecucion del algoritmo AStar (A*)
            struct json_object *tempAStar;
            cout<<"AStar"<<endl;
            json_object *parsed_jsonAStar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonAStar, "ASTAR", &tempAStar);*/

            ///KEY: NEXTPOSITIONG1
            ///Obtiene un request para obtener el cambio de posicion del gladiador 1
            struct json_object *tempNextPositionG1;
            //cout<<"NextPositionG1"<<endl;
            json_object *parsed_jsonPositionG1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPositionG1, "NEXTPOSITIONG1", &tempNextPositionG1);

            ///KEY: NEXTPOSITIONG2
            ///Obtiene un request para obtener el cambio de posicion del gladiador 2
            struct json_object *tempNextPositionG2;
            //cout<<"NextPositionG2"<<endl;
            json_object *parsed_jsonPositionG2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPositionG2, "NEXTPOSITIONG2", &tempNextPositionG2);

            ///KEY: INICIAR
            ///Obtiene un request para continuar el algoritmo genetico y volver a pasar la zona
            struct json_object *tempReiniciar;
            //cout<<"Iniciar"<<endl;
            json_object *parsed_jsonReiniciar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonReiniciar, "INICIAR", &tempReiniciar);

            ///KEYS LIVE LABELS

            ///KEY: LIVELABELS
            ///Obtiene un request para obtener el nombre del gladiador 1
            struct json_object *tempLiveLabels;
            json_object *parsed_jsonLiveLabels = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonLiveLabels, "LIVELABELS", &tempLiveLabels);



            ///KEYS HISTORIC LABELS



            /*
            ///KEY: TEMPLATE
            ///Obtiene un request para
            struct json_object *tempZZ;
            cout<<"ZZ"<<endl;
            json_object *parsed_jsonZZ = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonZZ, "ZZ", &tempZZ);
             */



            ///JSON Writes



            ///Obtendra un request para comenzar el juego
            ///Verifica que reciba los KEYS: COMIENZO
            if (json_object_get_string(tempComenzar) != nullptr) {
                ///JSON saliente del servidor
                string zoneSize = sendZoneSize();
                ///Envio al cliente
                send(fd2, zoneSize.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", zoneSize.c_str());
            }

            ///Obtendra un request para obtener la coordenada x del nodo deseado.
            ///Verifica que reciba los KEYS: XCOORD
            if (json_object_get_string(tempXCoord) != nullptr ) {
                ///JSON saliente del servidor
                string xCoord = sendCoord("x",json_object_get_string(tempXCoord));
                ///Envio al cliente
                send(fd2, xCoord.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", xCoord.c_str());
            }

            ///Obtendra un request para obtener la coordenada y del nodo deseado.
            ///Verifica que reciba los KEYS: YCOORD
            if (json_object_get_string(tempYCoord) != nullptr ) {
                ///JSON saliente del servidor
                string yCoord = sendCoord("y",json_object_get_string(tempYCoord));
                ///Envio al cliente
                send(fd2, yCoord.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", yCoord.c_str());
            }

            ///Obtendra un request para obtener la coordenada x de la torre deseada
            ///Verifica que reciba los KEYS: XCOORDTORRE
            if (json_object_get_string(tempXCoordTorre) != nullptr ) {
                ///JSON saliente del servidor
                string xCoordTorre = sendCoordTorre("x",json_object_get_string(tempXCoordTorre));
                ///Envio al cliente
                send(fd2, xCoordTorre.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", xCoordTorre.c_str());
            }

            ///Obtendra un request para obtener la coordenada y de la torre deseada
            ///Verifica que reciba los KEYS: YCOORDTORRE
            if (json_object_get_string(tempYCoordTorre) != nullptr ) {
                ///JSON saliente del servidor
                string yCoordTorre = sendCoordTorre("y",json_object_get_string(tempYCoordTorre));
                ///Envio al cliente
                send(fd2, yCoordTorre.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", yCoordTorre.c_str());
            }

            ///Obtendra un request para obtener la coordenada x del gladiador 1
            ///Verifica que reciba los KEYS: XCOORDGP1
            if (json_object_get_string(tempXCoordGP1) != nullptr ) {
                ///JSON saliente del servidor
                string xCoordGP1 = sendCoordGladiador("1","x",json_object_get_string(tempXCoordGP1));
                ///Envio al cliente
                send(fd2, xCoordGP1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", xCoordGP1.c_str());
            }

            ///Obtendra un request para obtener la coordenada y del gladiador 1
            ///Verifica que reciba los KEYS: YCOORDGP1
            if (json_object_get_string(tempYCoordGP1) != nullptr ) {
                ///JSON saliente del servidor
                string yCoordGP1 = sendCoordGladiador("1","y",json_object_get_string(tempYCoordGP1));
                ///Envio al cliente
                send(fd2, yCoordGP1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", yCoordGP1.c_str());
            }

            ///Obtendra un request para obtener la coordenada x del gladiador 2
            ///Verifica que reciba los KEYS: XCOORDGP2
            if (json_object_get_string(tempXCoordGP2) != nullptr ) {
                ///JSON saliente del servidor
                string xCoordGP2 = sendCoordGladiador("2","x",json_object_get_string(tempXCoordGP2));
                ///Envio al cliente
                send(fd2, xCoordGP2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", xCoordGP2.c_str());
            }

            ///Obtendra un request para obtener la coordenada y del gladiador 2
            ///Verifica que reciba los KEYS: YCOORDGP2
            if (json_object_get_string(tempYCoordGP2) != nullptr ) {
                ///JSON saliente del servidor
                string yCoordGP2 = sendCoordGladiador("2","y",json_object_get_string(tempYCoordGP2));
                ///Envio al cliente
                send(fd2, yCoordGP2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", yCoordGP2.c_str());
            }

            ///Obtendra un request para obtener si el gladiador 1 le han pegado
            ///Verifica que reciba los KEYS: HITG1
            if (json_object_get_string(tempHitG1) != nullptr ) {
                ///JSON saliente del servidor
                string hitG1 = sendHit("1",json_object_get_string(tempHitG1));
                ///Envio al cliente
                send(fd2, hitG1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", hitG1.c_str());
            }

            ///Obtendra un request para obtener si el gladiador 2 le han pegado
            ///Verifica que reciba los KEYS: HITG2
            if (json_object_get_string(tempHitG2) != nullptr ) {
                ///JSON saliente del servidor
                string hitG2 = sendHit("2",json_object_get_string(tempHitG2));
                ///Envio al cliente
                send(fd2, hitG2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", hitG2.c_str());
            }

            ///Obtendra un request para obtener el tipo de flecha que ha impactado al gladiador 1
            ///Verifica que reciba los KEYS: ATYPEG1
            if (json_object_get_string(tempATypeG1) != nullptr ) {
                ///JSON saliente del servidor
                string aTypeG1 = sendAType("1",json_object_get_string(tempATypeG1));
                ///Envio al cliente
                send(fd2, aTypeG1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", aTypeG1.c_str());

            }

            ///Obtendra un request para obtener el tipo de flecha que ha impactado al gladiador 2
            ///Verifica que reciba los KEYS: ATYPEG2
            if (json_object_get_string(tempATypeG2) != nullptr ) {
                ///JSON saliente del servidor
                string aTypeG2 = sendAType("2",json_object_get_string(tempATypeG2));
                ///Envio al cliente
                send(fd2, aTypeG2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", aTypeG2.c_str());
            }

            ///Obtendra un request para obtener la coordenada x de la flecha que ha impactado al gladiador 1
            ///Verifica que reciba los KEYS: XCOORDFLECHAG1
            if (json_object_get_string(tempXCoordFlechaG1) != nullptr ) {
                ///JSON saliente del servidor
                string xCoordFlechaG1 = sendCoordFlecha("1", "x",json_object_get_string(tempXCoordFlechaG1));
                ///Envio al cliente
                send(fd2, xCoordFlechaG1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", xCoordFlechaG1.c_str());
            }

            ///Obtendra un request para obtener la coordenada y de la flecha que ha impactado al gladiador 1
            ///Verifica que reciba los KEYS: YCOORDFLECHAG1
            if (json_object_get_string(tempYCoordFlechaG1) != nullptr ) {
                ///JSON saliente del servidor
                string yCoordFlechaG1 = sendCoordFlecha("1", "y",json_object_get_string(tempYCoordFlechaG1));
                ///Envio al cliente
                send(fd2, yCoordFlechaG1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", yCoordFlechaG1.c_str());
            }

            ///Obtendra un request para obtener la coordenada x de la flecha que ha impactado al gladiador 2
            ///Verifica que reciba los KEYS: XCOORDFLECHAG2
            if (json_object_get_string(tempXCoordFlechaG2) != nullptr ) {
                ///JSON saliente del servidor
                string xCoordFlechaG2 = sendCoordFlecha("2", "x",json_object_get_string(tempXCoordFlechaG2));
                ///Envio al cliente
                send(fd2, xCoordFlechaG2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", xCoordFlechaG2.c_str());
            }

            ///Obtendra un request para obtener la coordenada y de la flecha que ha impactado al gladiador 2
            ///Verifica que reciba los KEYS: YCOORDFLECHAG2
            if (json_object_get_string(tempYCoordFlechaG2) != nullptr ) {
                ///JSON saliente del servidor
                string yCoordFlechaG2 = sendCoordFlecha("2", "y",json_object_get_string(tempYCoordFlechaG2));
                ///Envio al cliente
                send(fd2, yCoordFlechaG2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", yCoordFlechaG2.c_str());
            }

            ///Obtendra un request para obtener la resistencia del gladiador 1
            ///Verifica que reciba los KEYS: RESISTENCIAG1
            if (json_object_get_string(tempResistenciaG1) != nullptr ) {
                ///JSON saliente del servidor
                string resistenciaG1 = sendResistencia("1");
                ///Envio al cliente
                send(fd2, resistenciaG1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", resistenciaG1.c_str());
            }

            ///Obtendra un request para obtener la resistencia del gladiador 2
            ///Verifica que reciba los KEYS: RESISTENCIA G2
            if (json_object_get_string(tempResistenciaG2) != nullptr ) {
                ///JSON saliente del servidor
                string resistenciaG2 = sendResistencia("2");
                ///Envio al cliente
                send(fd2, resistenciaG2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", resistenciaG2.c_str());
            }

            ///Obtendra un request para obtener la proxima posicion en el path del gladiador 1
            ///Verifica que reciba los KEYS: NEXTPOSITIONG1
            if (json_object_get_string(tempNextPositionG1) != nullptr ) {
                ///JSON saliente del servidor
                string nextPositionG1 = changePathIndex("1",json_object_get_string(tempNextPositionG1));
                ///Envio al cliente
                send(fd2, nextPositionG1.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", nextPositionG1.c_str());
            }

            ///Obtendra un request para obtener la proxima posicion en el path del gladiador 2
            ///Verifica que reciba los KEYS: NEXTPOSITIONG2
            if (json_object_get_string(tempNextPositionG2) != nullptr ) {
                ///JSON saliente del servidor
                string nextPositionG2 = changePathIndex("2",json_object_get_string(tempNextPositionG2));
                ///Envio al cliente
                send(fd2, nextPositionG2.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", nextPositionG2.c_str());
            }

            ///Obtendra un request para obtener para iniciar, reiniciar y recalcular los algoritmos del programa
            ///Verifica que reciba los KEYS: INICIAR
            if (json_object_get_string(tempReiniciar) != nullptr ) {
                ///JSON saliente del servidor
                iniciar(json_object_get_string(tempReiniciar));
                ///Envio al cliente
                send(fd2, "Inicio", MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: LIVELABELS
            if (json_object_get_string(tempLiveLabels) != nullptr ) {
                ///JSON saliente del servidor
                string liveLabels = sendLiveLabels();
                ///Envio al cliente
                send(fd2, liveLabels.c_str(), MAXDATASIZE, 0);
            }


            /*
            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: TEMPLATE
            if (json_object_get_string(tempZZ) != nullptr ) {
                ///JSON saliente del servidor
                string aTypeZZ = sendAType("ZZ",json_object_get_string(tempZZ));
                ///Envio al cliente
                send(fd2, aTypeZZ.c_str(), MAXDATASIZE, 0);
            }
             */

        }

        ///Reestablece el buffer
        memset(buff, 0, MAXDATASIZE);

        cout <<
             "\n\n--------------------------------------------------------------------------------"
             "END--------------------------------------------------------------------------------\n"
             << endl;

    }

    close(fd2);

}


/**
 * Main del programa
 */
int main(int argc, char** argv) {

    ///Inicializa las pruebas unitarias
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    ///Para obtener un random real a base del tiempo
    srand(time(NULL));

    ///Instanciación del juego
    juego = new Juego();

    ///Corre el servidor
    runServer();

}

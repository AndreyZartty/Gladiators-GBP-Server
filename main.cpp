
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <json-c/json.h>

#define PORT 3550
#define BACKLOG 4
#define MAXDATASIZE 1000

#include <iostream>
#include "Juego.h"


/**
 * Main del programa
 * @since 30/04/19
 */


///Instancia estatica del juego
static Juego* juego = new Juego();


/**
 * Retorna al cliente el tamaño de la Zona de Intimidación.
 * @return JSON
 */
string sendZoneSize() {

    int zoneSize = juego->getCuadricula()->getSize();

    cout<<"\nZoneSize: " << zoneSize << endl;

    json_object *jobjZoneSize = json_object_new_object();

    json_object *jstringZoneSize = json_object_new_string(to_string(zoneSize).c_str());

    json_object_object_add(jobjZoneSize,"ZONESIZE", jstringZoneSize);

    return json_object_to_json_string(jobjZoneSize);

}

/**
 * Retora la coordenada del Nodo deseada.
 * @param coord
 * @param id
 * @return JSON
 */
string sendCoord(string coord, string id) {

    int coordToSend;

    if (coord == "x") {

        coordToSend = juego->getCuadricula()->getNode( stoi(id) )->getXCoord();

        cout<<"\nxCoord: " << coordToSend << endl;

        json_object *jobjXCoord = json_object_new_object();

        json_object *jstringXCoord = json_object_new_string(to_string(coordToSend).c_str());

        json_object_object_add(jobjXCoord,"XCOORD", jstringXCoord);

        return json_object_to_json_string(jobjXCoord);

    }
    else if (coord == "y") {

        coordToSend = juego->getCuadricula()->getNode( stoi(id) )->getYCoord();

        cout<<"\nyCoord: " << coordToSend << endl;

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

    int vectorSize = (int) juego->getCuadricula()->getPosibleTowerIdList().size();

    int coordToSendTorre;

    if (index < vectorSize) {

        int id = juego->getCuadricula()->getTowerIdList()[index];

        if ( coord == "x") {

            coordToSendTorre = juego->getCuadricula()->getNode( id )->getXCoord();

            cout<<"\nxCoordTorre: " << coordToSendTorre << endl;

            json_object *jobjXCoordTorre = json_object_new_object();

            json_object *jstringXCoordTorre = json_object_new_string(to_string(coordToSendTorre).c_str());

            json_object_object_add(jobjXCoordTorre,"XCOORDTORRE", jstringXCoordTorre);

            return json_object_to_json_string(jobjXCoordTorre);

        }
        else if (coord == "y") {

            coordToSendTorre = juego->getCuadricula()->getNode( id )->getYCoord();

            cout<<"\nyCoordTorre: " << coordToSendTorre << endl;

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

        cout<<"\nCoordTorre: " << coordToSendTorre << endl;

        json_object *jobjXCoordTorre = json_object_new_object();

        json_object *jstringXCoordTorre = json_object_new_string(to_string(coordToSendTorre).c_str());

        json_object_object_add(jobjXCoordTorre,"XCOORDTORRE", jstringXCoordTorre);

        return json_object_to_json_string(jobjXCoordTorre);

    }
    else if (coord == "y") {


        coordToSendTorre = -1;

        cout<<"\nCoordTorre: " << coordToSendTorre << endl;

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

                cout<<"\nxCoordGladiador: " << coordToSendGladiator << endl;

                json_object *jobjXCoordGladiador = json_object_new_object();

                json_object *jstringXCoordGladiador = json_object_new_string(to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGladiador,"XCOORDGP1", jstringXCoordGladiador);

                return json_object_to_json_string(jobjXCoordGladiador);

            }
            else if (coord == "y") {

                coordToSendGladiator = juego->getCuadricula()->getNode( id )->getYCoord();

                cout<<"\nyCoordGladiador: " << coordToSendGladiator << endl;

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

                cout<<"\nxCoordGladiador: " << coordToSendGladiator << endl;

                json_object *jobjXCoordGladiador = json_object_new_object();

                json_object *jstringXCoordGladiador = json_object_new_string(to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGladiador,"XCOORDGP2", jstringXCoordGladiador);

                return json_object_to_json_string(jobjXCoordGladiador);

            }

            else if (coord == "y") {

                coordToSendGladiator = juego->getCuadricula()->getNode( id )->getYCoord();

                cout<<"\nyCoordGladiador: " << coordToSendGladiator << endl;

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

                cout << "\nxCoordGladiador: " << coordToSendGladiator << endl;

                json_object *jobjXCoordGP1 = json_object_new_object();

                json_object *jstringXCoordGladiadorGP1 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGP1, "XCOORDGP1", jstringXCoordGladiadorGP1);

                return json_object_to_json_string(jobjXCoordGP1);

            } else if (coord == "y") {

                coordToSendGladiator = -1;

                cout << "\nyCoordGladiador: " << coordToSendGladiator << endl;

                json_object *jobjYCoordGP1 = json_object_new_object();

                json_object *jstringYCoordGladiadorGP1 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjYCoordGP1, "YCOORDGP1", jstringYCoordGladiadorGP1);

                return json_object_to_json_string(jobjYCoordGP1);

            }

        } else if (poblacion == "2") {


            if (coord == "x") {

                coordToSendGladiator = -1;

                cout << "\nxCoordGladiador: " << coordToSendGladiator << endl;

                json_object *jobjXCoordGP2 = json_object_new_object();

                json_object *jstringXCoordGladiadorGP2 = json_object_new_string(
                        to_string(coordToSendGladiator).c_str());

                json_object_object_add(jobjXCoordGP2, "XCOORDGP2", jstringXCoordGladiadorGP2);

                return json_object_to_json_string(jobjXCoordGP2);

            } else if (coord == "y") {

                coordToSendGladiator = -1;

                cout << "\nyCoordGladiador: " << coordToSendGladiator << endl;

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
            cout<<"COMENZAR"<<endl;
            json_object *parsed_jsonComenzar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonComenzar, "COMENZAR", &tempComenzar);
            printf("Por comenzar: %s\n", json_object_get_string(tempComenzar));

            ///KEY: XCOORD
            ///Obtiene la coordenada x del nodo deseado
            struct json_object *tempXCoord;
            cout<<"XCoord"<<endl;
            json_object *parsed_jsonXCoord = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoord, "XCOORD", &tempXCoord);
            printf("XCoord: %s\n", json_object_get_string(tempXCoord));

            ///KEY: YCOORD
            ///Obtiene la coordenada y del nodo deseado
            struct json_object *tempYCoord;
            cout<<"YCoord"<<endl;
            json_object *parsed_jsonYCoord = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoord, "YCOORD", &tempYCoord);
            printf("YCoord: %s\n", json_object_get_string(tempYCoord));

            ///KEY: XCOORDTORRE
            ///Obtiene la coordenada x de la torre deseada
            struct json_object *tempXCoordTorre;
            cout<<"XCoordTorre"<<endl;
            json_object *parsed_jsonXCoordTorre = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordTorre, "XCOORDTORRE", &tempXCoordTorre);
            printf("XCoordTorre: %s\n", json_object_get_string(tempXCoordTorre));

            ///KEY: YCOORDTORRE
            ///Obtiene la coordenada y de la torre deseada
            struct json_object *tempYCoordTorre;
            cout<<"YCoordTorre"<<endl;
            json_object *parsed_jsonYCoordTorre = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordTorre, "YCOORDTORRE", &tempYCoordTorre);
            printf("YCoordTorre: %s\n", json_object_get_string(tempYCoordTorre));

            ///KEY: XCOORDGP1
            ///Obtiene la coordenada x del gladiador de la poblacion 1
            struct json_object *tempXCoordGP1;
            cout<<"XCoordGP1"<<endl;
            json_object *parsed_jsonXCoordGP1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordGP1, "XCOORDGP1", &tempXCoordGP1);

            ///KEY: YCOORDGP1
            ///Obtiene la coordenada y del gladiador de la poblacion 1
            struct json_object *tempYCoordGP1;
            cout<<"YCoordGP1"<<endl;
            json_object *parsed_jsonYCoordGP1 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordGP1, "YCOORDGP1", &tempYCoordGP1);

            ///KEY: XCOORDGP2
            ///Obtiene la coordenada x del gladiador de la poblacion 2
            struct json_object *tempXCoordGP2;
            cout<<"XCoordGP2"<<endl;
            json_object *parsed_jsonXCoordGP2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonXCoordGP2, "XCOORDGP2", &tempXCoordGP2);

            ///KEY: YCOORDGP2
            ///Obtiene la coordenada y del gladiador de la poblacion 2
            struct json_object *tempYCoordGP2;
            cout<<"YCoordGP2"<<endl;
            json_object *parsed_jsonYCoordGP2 = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonYCoordGP2, "YCOORDGP2", &tempYCoordGP2);

            ///KEY: ASTAR
            ///Genera la ejecucion del algoritmo AStar (A*)
            struct json_object *tempAStar;
            cout<<"AStar"<<endl;
            json_object *parsed_jsonAStar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonAStar, "ASTAR", &tempAStar);

            ///KEY: BACKTRACKING
            ///Genera la ejecucion del algoritmo Backtracking
            struct json_object *tempBacktracking;
            cout<<"Backtracking"<<endl;
            json_object *parsed_jsonBacktracking = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonBacktracking, "BACKTRACKING", &tempBacktracking);



            ///JSON Writes



            ///Obtendra un request para comenzar el juego
            ///Verifica que reciba los KEYS: COMIENZO
            if (json_object_get_string(tempComenzar) != 0 ) {
                ///JSON saliente del servidor
                string zoneSize = sendZoneSize();
                ///Envio al cliente
                send(fd2, zoneSize.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener la coordenada x del nodo deseado.
            ///Verifica que reciba los KEYS: XCOORD
            if (json_object_get_string(tempXCoord) != 0 ) {
                ///JSON saliente del servidor
                string xCoord = sendCoord("x",json_object_get_string(tempXCoord));
                ///Envio al cliente
                send(fd2, xCoord.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener la coordenada y del nodo deseado.
            ///Verifica que reciba los KEYS: YCOORD
            if (json_object_get_string(tempYCoord) != 0 ) {
                ///JSON saliente del servidor
                string yCoord = sendCoord("y",json_object_get_string(tempYCoord));
                ///Envio al cliente
                send(fd2, yCoord.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener la coordenada x de la torre deseada
            ///Verifica que reciba los KEYS: XCOORDTORRE
            if (json_object_get_string(tempXCoordTorre) != 0 ) {
                ///JSON saliente del servidor
                string xCoordTorre = sendCoordTorre("x",json_object_get_string(tempXCoordTorre));
                ///Envio al cliente
                send(fd2, xCoordTorre.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener la coordenada y de la torre deseada
            ///Verifica que reciba los KEYS: YCOORDTORRE
            if (json_object_get_string(tempYCoordTorre) != 0 ) {
                ///JSON saliente del servidor
                string yCoordTorre = sendCoordTorre("y",json_object_get_string(tempYCoordTorre));
                ///Envio al cliente
                send(fd2, yCoordTorre.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: XCOORDGP1
            if (json_object_get_string(tempXCoordGP1) != 0 ) {
                ///JSON saliente del servidor
                string xCoordGP1 = sendCoordGladiador("1","x",json_object_get_string(tempXCoordGP1));
                ///Envio al cliente
                send(fd2, xCoordGP1.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: YCOORDGP1
            if (json_object_get_string(tempYCoordGP1) != 0 ) {
                ///JSON saliente del servidor
                string yCoordGP1 = sendCoordGladiador("1","y",json_object_get_string(tempYCoordGP1));
                ///Envio al cliente
                send(fd2, yCoordGP1.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: XCOORDGP2
            if (json_object_get_string(tempXCoordGP2) != 0 ) {
                ///JSON saliente del servidor
                string xCoordGP2 = sendCoordGladiador("2","x",json_object_get_string(tempXCoordGP2));
                ///Envio al cliente
                send(fd2, xCoordGP2.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: YCOORDGP2
            if (json_object_get_string(tempYCoordGP2) != 0 ) {
                ///JSON saliente del servidor
                string yCoordGP2 = sendCoordGladiador("2","y",json_object_get_string(tempYCoordGP2));
                ///Envio al cliente
                send(fd2, yCoordGP2.c_str(), MAXDATASIZE, 0);
            }


            /*
            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: ASTAR
            if (json_object_get_string(tempAStar) != 0 ) {
                ///JSON saliente del servidor
                string aStar = sendAStar("",json_object_get_string(tempAStar));
                ///Envio al cliente
                send(fd2, aStar.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: BACKTRACKING
            if (json_object_get_string(tempBacktracking) != 0 ) {
                ///JSON saliente del servidor
                string backtracking = sendBacktracking("",json_object_get_string(tempBacktracking));
                ///Envio al cliente
                send(fd2, backtracking.c_str(), MAXDATASIZE, 0);
            }*/


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
int main() {

    ///Realiza el primer A* y el primer Backtracking
    //juego->doBacktracking();
    //juego->doAStar();

    ///Corre los algoritmos
    juego->doAlgorithms();

    cout << "No va a correr gay" << endl;

    juego->getAStarAlgorithm()->showPath();
    

    juego->getBacktrackingAlgorithm()->showPath();



    ///Corre el servidor
    //runServer();

}

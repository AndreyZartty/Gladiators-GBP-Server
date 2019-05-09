
#include "Cuadricula.h"

/**
 * Representa la cuadricula
 *
 * @since 30/04/19
 */


/**
 * Constructor de Cuadricula
 */
Cuadricula::Cuadricula() {
    buildZone(ZONE_SIZE);

    nodoInicio = matriz[0][0];
    nodoFinal = matriz[ZONE_SIZE - 1][ZONE_SIZE - 1];

    generateTowers();



}


///Metodos


/**
 * Construye la matriz nxn con Nodes preestablecidos
 */
void Cuadricula::buildZone(int n) {

    ///Posiciones graficas
    int x = 380;
    int y = 100;

    ///Espacio entre cada nodo graficamente
    int dxy = 450/ZONE_SIZE;

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {

            ///Instancia el nuevo nodo
            Node* nNode = new Node(i, j, ZONE_SIZE);
            ///Es añadido en la cuadricula
            matriz[i][j] = nNode;

            ///Ingresa las posiciones graficas de los nodos
            matriz[i][j]->setXCoord( x + dxy * j );
            matriz[i][j]->setYCoord( y + dxy * i );

            //cout << "["<< i << "," << j <<"]" ;
        }
        //cout << "" << endl;
    }
    cout << "\nMatriz de cuadricula lista" << endl;
}


void Cuadricula::generateTowers() {

    ///Genera un valor diferente cada vez que se llame a la funcion dependiendo de la hora y fecha.
    srand (time(NULL));

    for (int n = 0; n < 19; n++) {

        ///Obtiene un int aleatorio
        int i = rand() % (ZONE_SIZE ) ;
        int j = rand() % (ZONE_SIZE ) ;

        ///Si no posee ya una torre
        if (matriz[i][j]->getTorre() == nullptr && matriz[i][j]->getId() != 0 && matriz[i][j]->getId() != ( (ZONE_SIZE-1)*(ZONE_SIZE) + (ZONE_SIZE-1) ) ) {
            matriz[i][j]->setTorre( new Torre() );
            towerIdList.push_back( matriz[i][j]->getId() );
            clientTowerIdList.push_back( matriz[i][j]->getId() );
        } else {
            n--;
        }

    }

    ///IMPRIMIR VECTOR
    for (int i = 0; i < towerIdList.size(); i++) {

        if (i == 0) {
            cout << "[" << towerIdList[i] << ", ";
        }
        else if (i == towerIdList.size() - 1) {
            cout << towerIdList[i] << "]" << endl;
        }
        else {
            cout << towerIdList[i] << ", ";
        }

    }

}


/**
 * Calcular el valor de Heuristico
 */
void Cuadricula::calculateHeuristic() {

    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {

            if (matriz[i][j]->getTorre() != nullptr) {
                matriz[i][j]->setHCost(-1);
            }
            else {
                matriz[i][j]->ManhattanDistance(matriz[size - 1][size - 1]);
            }

        }
    }

}


Node* Cuadricula::getNode(int i, int j) {
    return matriz[i][j];
}

Node* Cuadricula::getNode(int id) {


    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {

            if (matriz[i][j]->getId() == id) {

                return matriz[i][j];

            }

        }
    }

    return nullptr;

}


void Cuadricula::print() {
    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {

            Node* printee = matriz[i][j];

            int hayTorre = 0;
            int hCost = printee->getHCost();
            int id = printee->getId();
            int parent = -1;

            if (printee->getParent() != nullptr) {
                parent = printee->getParent()->getId();
            }


            if (printee->getTorre() != nullptr) {
                hayTorre = 1;
            }

            int x = printee->getXCoord();
            int y = printee->getYCoord();

            cout << " ["<< i << "," << j << "," << id << "," << hayTorre << ","
                 << hCost << "," << parent << "," << x << "," << y << "] " ;

        }
        cout << "\n" << endl;
    }
    cout << "\nMatriz de cuadricula lista" << endl;
}


void Cuadricula::printTorres() {
    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {

            string place = " ";

            if (matriz[i][j]->getTorre() != nullptr) {
                place = "|";
            }

            if (matriz[i][j]->isInAStarPath()) {
                place = "0";
            }

            if (matriz[i][j]->isInBacktrakingPath()) {
                place = "X";
            }

            if (matriz[i][j]->isInAStarPath() && matriz[i][j]->isInBacktrakingPath()) {
                place = "#";
            }

            cout << "["<< place <<"]" ;

        }
        cout << "" << endl;
    }
    cout << "\nMatriz de cuadricula lista" << endl;
}






///Getters & Setters


/**
 * Getter del size de Cuadricula;
 * @return size
 */
int Cuadricula::getSize() {
    return size;
}


/**
 * Getter de towerIdList de Cuadricula.
 * @return lista de Towers
 */
vector<int> Cuadricula::getTowerIdList() {
    return towerIdList;
}


/**
 * Getter de clientTowerIdList de Cuadricula.
 * @return lista de Towers
 */
vector<int> Cuadricula::getClientTowerIdList() {
    return towerIdList;
}
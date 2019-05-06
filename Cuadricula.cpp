
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

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            Node* nNode = new Node(i, j, ZONE_SIZE);
            matriz[i][j] = nNode;
            cout << "["<< i << "," << j <<"]" ;
        }
        cout << "" << endl;
    }
    cout << "\nMatriz de cuadricula lista" << endl;
}


void Cuadricula::generateTowers() {

    ///Genera un valor diferente cada vez que se llame a la funcion dependiendo de la hora y fecha.
    srand (time(NULL));

    for (int n = 0; n < 29; n++) {

        ///Obtiene un int aleatorio
        int i = rand() % (ZONE_SIZE - 1) + 1;
        int j = rand() % (ZONE_SIZE - 1) + 1;

        ///Si no posee ya una torre
        if (matriz[i][j]->getTorre() == nullptr && matriz[i][j]->getId() != 0 && matriz[i][j]->getId() != 99 ) {
            matriz[i][j]->setTorre( new Torre() );
            towerIdList.push_back( matriz[i][j]->getId() );
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

            cout << " ["<< i << "," << j << "," << id << "," << hayTorre << "," << hCost << "," << parent << "] " ;

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

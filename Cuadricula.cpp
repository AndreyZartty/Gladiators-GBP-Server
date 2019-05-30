
#include "Cuadricula.h"
#include <iostream>

using namespace std;


/**
 * Representa la cuadricula
 *
 * @since 30/04/19
 */


/**
 * Constructor de Cuadricula.
 */
Cuadricula::Cuadricula() {

    ///Se genera la matriz
    buildZone(ZONE_SIZE);

    ///Nodos inicial y final
    nodoInicial = matriz[0][0];
    nodoFinal = matriz[ZONE_SIZE - 1][ZONE_SIZE - 1];
}


///Metodos


/**
 * Construye la matriz nxn con Nodes preestablecidos.
 */
void Cuadricula::buildZone(int n) {

    ///Posiciones graficas
    int x = 380;
    int y = 150;

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

        }

    }

}

/**
 * Crea una nueva Torre e imprime sus vectores.
 * @return int
 */
int Cuadricula::newTower() {

    int randomTowerType ;
    if (posibleTowerIdList.size() == 0){
        return -1;
    }
    else {

        randomTowerType = 1 + rand() % 3;

        ///Obtiene un int aleatorio
        int i = rand() % (posibleTowerIdList.size());

        for (int n = 0; n < 1; n++) {

            ///Si no posee ya una torre
            if (getNode(posibleTowerIdList[i])->getTorre() == nullptr && posibleTowerIdList[i] != 0 &&
                    posibleTowerIdList[i] != ((ZONE_SIZE - 1) * (ZONE_SIZE) + (ZONE_SIZE - 1))) {

                getNode(posibleTowerIdList[i])->setTorre(new Torre(randomTowerType));

                int send = posibleTowerIdList[i];
                towerIdList.push_back(posibleTowerIdList[i]);
                std::vector<int>::iterator buscador = find(posibleTowerIdList.begin(), posibleTowerIdList.end(), posibleTowerIdList[i]);
                int posTorre = std::distance(posibleTowerIdList.begin(), buscador);
                posibleTowerIdList.erase(posibleTowerIdList.begin() + posTorre);
                return send;

            } else {
                n--;
            }

        }

        ///IMPRIMIR VECTOR DE TORRES
        cout << "Tower Id's: ";
        for (int i = 0; i < towerIdList.size(); i++) {

            if (i == 0) {
                cout << "[" << towerIdList[i] << ", ";
            } else if (i == towerIdList.size() - 1) {
                cout << towerIdList[i] << "]\n" << endl;
            } else {
                cout << towerIdList[i] << ", ";
            }

        }

        ///IMPRIMIR VECTOR DE POSIBLES TORRES

        cout << "PosibleTower Id's: ";
        for (int i = 0; i < posibleTowerIdList.size(); i++) {

            if (i == 0) {
                cout << "[" << posibleTowerIdList[i] << ", ";
            } else if (i == posibleTowerIdList.size() - 1) {
                cout << posibleTowerIdList[i] << "]\n" << endl;
            } else {
                cout << posibleTowerIdList[i] << ", ";
            }

        }
    }
}

/**
 * Calcula el valor de Heuristico para el algoritmo A*
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

/**
 * Obtiene un nodo por medio de su fila y su columna.
 * @param i - fila
 * @param j - columna
 * @return Node
 */
Node* Cuadricula::getNode(int i, int j) {
    if (i >= 0 && j >= 0 && i < size && j < size ) {
        return matriz[i][j];
    }
    return nullptr;
}

/**
 * Obtiene un nodo por medio de su id.
 * @param id - id
 * @return Node
 */
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

/**
 * Imprime toda la matriz con las caracteristicas de cada nodo.
 */
void Cuadricula::print() {
    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {

            Node* printee = matriz[i][j];

            string hayTorre = "0";
            int towerType = 0;
            int id = printee->getId();

            if (printee->getTorre() != nullptr) {
                hayTorre = "T";
                towerType = printee->getTorre()->getTipo();
            }

            int x = printee->getXCoord();
            int y = printee->getYCoord();

            cout << " ["<< i << "," << j << "," << id << "," << hayTorre << ","
                 << towerType << "," << x << "," << y << "] " ;

        }
        cout << "\n" << endl;
    }
    cout << "Matriz de cuadricula lista\n\n" << endl;
}

/**
 * Imprime la matriz con las torres, y los caminos de ambos algoritmos.
 */
void Cuadricula::printTorres() {
    cout << "" << endl;
    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {

            string place = " ";

            if (matriz[i][j]->getTorre() != nullptr) {
                place = "|";
            }

            if (matriz[i][j]->isInAStarPath()) {
                place = "0";
            }

            if (matriz[i][j]->isInBacktrackingPath()) {
                place = "X";
            }

            if (matriz[i][j]->isInAStarPath() && matriz[i][j]->isInBacktrackingPath()) {
                place = "#";
            }

            if (matriz[i][j]->getTorre() != nullptr && matriz[i][j]->isInBacktrackingPath()) {
                place = "1";
            }

            if (matriz[i][j]->getTorre() != nullptr && matriz[i][j]->isInAStarPath()) {
                place = "2";
            }

            cout << "["<< place <<"]" ;

        }
        cout << "" << endl;
    }
    cout << "\n" << endl;
}

/**
 * Añade una posible torre.
 */
void Cuadricula::addPosibleTowerIdList() {
    for(int i=0; i<ZONE_SIZE; i++){
        for (int j=0; j<ZONE_SIZE; j++){
            if (matriz[i][j]->getTorre() == nullptr && matriz[i][j]->getId() != 0 && matriz[i][j]->getId() != ( (ZONE_SIZE-1)*(ZONE_SIZE) + (ZONE_SIZE-1) ) ){
                posibleTowerIdList.push_back( matriz[i][j]->getId() );
            }
        }
    }
}

/**
 * Añade una torre a la liste toVerifiedNot
 * @param evaluatingTower
 */
void Cuadricula::addToVerifiedNot(int evaluatingTower) {
    verfifiedNotTowersIdList.push_back(evaluatingTower);

}

/**
 * Elimina una torre cuando esta no funciona en la zona.
 * @param evaluatingTower
 */
void Cuadricula::deleteTower(int evaluatingTower) {
    std::vector<int>::iterator buscador = find(towerIdList.begin(), towerIdList.end(), evaluatingTower);
    int posTorre = std::distance(towerIdList.begin(), buscador);
    towerIdList.erase(towerIdList.begin() + posTorre);
    getNode(evaluatingTower)->setTorre(nullptr);
}

/**
 * Reestablece verifiedNot.
 */
void Cuadricula::resetVerifiedNot() {
    while(verfifiedNotTowersIdList.size() != 0){

        ///Imprime las opciones descartadas
        //cout << "VerifiedNot Id's: ";
        for (int i = 0; i < verfifiedNotTowersIdList.size(); i++) {

            if (i == 0) {
                //cout << "[" << verfifiedNotTowersIdList[i] << ", ";
            } else if (i == verfifiedNotTowersIdList.size() - 1) {
                //cout << verfifiedNotTowersIdList[i] << "]\n" << endl;
            } else {
                //cout << verfifiedNotTowersIdList[i] << ", ";
            }

        }
        posibleTowerIdList.push_back(verfifiedNotTowersIdList[verfifiedNotTowersIdList.size()-1]);
        verfifiedNotTowersIdList.pop_back();

    }
}


///Getters & Setters


/**
 * Getter del size de Cuadricula.
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
vector<int> Cuadricula::getPosibleTowerIdList() {
    return posibleTowerIdList;
}

/**
 * Getter del NodoInicial de Cuadricula.
 * @return Node
 */
Node *Cuadricula::getNodoInicial() {
    return nodoInicial;
}

/**
 * Getter del NodoFinal de Cuadricula.
 * @return Node
 */
Node* Cuadricula::getNodoFinal() {
    return nodoFinal;
}

/**
 * Getter del verifiedNotTowersIdList de Cuadricula.
 * @return vector
 */
vector<int> Cuadricula::getVerfifiedNotTowersIdList() {
    return verfifiedNotTowersIdList;
}

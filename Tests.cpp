#include <iostream>
#include <gtest/gtest.h>
#include "Juego.h"

using namespace std;


/**
 * GTests
 *
 * @since 27/05/19
 */


////////////////////////////////ASTAR////////////////////////////////*


/**
 * Text Fixture de una instancia de AStar obtenido de una instancia
 * de Juego.
 */
struct AStarTest : public testing::Test {
    Juego* jt;
    AStar* as;
    void SetUp() { jt = new Juego(); as = jt->getAStarAlgorithm(); }
    void TearDown() { delete jt; delete as; }
};


/**
 * Test de la creación correcta de una instancia de AStar
 */
TEST_F(AStarTest, Test_Constructor) {

    ///Assert
    EXPECT_NE(as,nullptr);

}

/**
 * Test de la creación correcta de los atributos de AStar
 */
TEST_F(AStarTest, Test_Constructor_Atributos) {

    ///Assert
    EXPECT_NE(as->getCuadricula(),nullptr);
    EXPECT_EQ(as->isInitializedStartGoal(),false);
    EXPECT_EQ(as->isFoundGoal(),false);

}

/**
 * Test del borrado correcto de las listas que utiliza el algoritmo AStar
 */
TEST_F(AStarTest, Test_FindPath_Wipe_Lists) {

    ///Arrange:
    //ClosedList
    as->getClosedList().push_back(1);
    as->getClosedList().push_back(10);
    as->getClosedList().push_back(20);
    //OpenList
    as->getOpenList().push_back(5);
    as->getOpenList().push_back(2);
    as->getOpenList().push_back(3);
    as->getOpenList().push_back(4);
    //PathToGoal
    as->getPathToGoal().push_back(0);
    as->getPathToGoal().push_back(11);
    as->getPathToGoal().push_back(22);
    as->getPathToGoal().push_back(33);
    as->getPathToGoal().push_back(44);

    ///Act
    //Limpia openList
    as->getOpenList().clear();
    //Limpia visitedList
    as->getClosedList().clear();
    //Limpia pathToGoal
    as->getPathToGoal().clear();

    ///Assert
    ASSERT_EQ(as->getOpenList().size(),0);
    ASSERT_EQ(as->getClosedList().size(),0);
    ASSERT_EQ(as->getPathToGoal().size(),0);
    
}

/**
 * Test de la reiniciación de los costos de los nodos utilizados
 * en el algoritmo AStar
 */
TEST_F(AStarTest, Test_FindPath_Wipe_Costs) {

    ///Arrange:
    //Calcula el Heuristico
    as->getCuadricula()->calculateHeuristic();

    ///Act
    //Ingresa cero como estado inicial a las variables de TODOS los Nodes
    for (int i = 0 ; i < as->getCuadricula()->getSize() ; i++) {
        for (int j = 0 ; j < as->getCuadricula()->getSize() ; j++) {

            int id = ((i) * (as->getCuadricula()->getSize()) + (j));

            as->getCuadricula()->getNode(id)->setInAStarPath(false);
            as->getCuadricula()->getNode(id)->setGCost(0);
            as->getCuadricula()->getNode(id)->setFCost(0);
            as->getCuadricula()->getNode(id)->setHCost(0);

        }
    }

    ///Assert
    for (int i = 0 ; i < as->getCuadricula()->getSize() ; i++) {
        for (int j = 0 ; j < as->getCuadricula()->getSize() ; j++) {

            int id = ((i) * (as->getCuadricula()->getSize()) + (j));
            //cout << as->getCuadricula()->getNode(id)->getId() << endl;

            EXPECT_EQ(as->getCuadricula()->getNode(id)->isInAStarPath(),false);
            EXPECT_EQ(as->getCuadricula()->getNode(id)->getGCost(),0);
            EXPECT_EQ(as->getCuadricula()->getNode(id)->getFCost(),0);
            EXPECT_EQ(as->getCuadricula()->getNode(id)->getHCost(),0);

        }
    }

}

/**
 * Test de la asignación debida a los nodos start y goal del AStar
 */
TEST_F(AStarTest, Test_SetStartAndGoal) {

    ///Act
    as->setStartAndGoal(jt->getNodoInicio(), jt->getNodoFinal());

    ///Assert
    EXPECT_NE(as->getStartNode(),nullptr);
    ASSERT_EQ(as->getStartNode(),jt->getNodoInicio());
    EXPECT_NE(as->getGoalNode(),nullptr);
    ASSERT_EQ(as->getGoalNode(),jt->getNodoFinal());

}

/*
TEST_F(AStarTest, TestName_1) {

    ///Arrange:
    //Arrange everything to run the Test


    ///Act
    //Run the Test

    ///Assert
    //Verify the Output

}
*/

////////////////////////////////ASTAR////////////////////////////////





/////////////////////////////BACKTRACKING/////////////////////////////*


/**
 * Text Fixture de una instancia de Backtracking obtenido de una instancia
 * de Juego.
 */
struct BacktrackingTest : public testing::Test {
    Juego* jt;
    Backtracking* bt;
    void SetUp() { jt = new Juego(); bt = jt->getBacktrackingAlgorithm(); }
    void TearDown() { delete jt; delete bt; }
};


/**
 * Test de la creación correcta de una instancia de Backtracking
 */
TEST_F(BacktrackingTest, Test_Constructor) {

    ///Assert
    EXPECT_NE(bt,nullptr);

}

/**
 * Test de la creación correcta de los atributos de Backtracking
 */
TEST_F(BacktrackingTest, Test_Constructor_Atributos) {

    ///Assert
    EXPECT_NE(bt->getCuadricula(),nullptr);
    EXPECT_EQ(bt->isInitializedStartGoal(),false);
    EXPECT_EQ(bt->isFoundGoal(),false);

}


/////////////////////////////BACKTRACKING/////////////////////////////





//////////////////////////////CUADRICULA//////////////////////////////*


/**
 * Text Fixture de una instancia de la Cuadrícula obtenida de una instancia
 * de Juego.
 */
struct CuadriculaTest : public testing::Test {
    Juego* jt;
    Cuadricula* cd;
    void SetUp() { jt = new Juego(); cd = jt->getCuadricula(); }
    void TearDown() { delete jt; delete cd; }
};


/**
 * Test de la creación correcta de una instancia de Cuadricula
 */
TEST_F(CuadriculaTest, Test_Constructor) {

    ///Assert
    EXPECT_NE(cd,nullptr);

}

/**
 * Test de la creación correcta de los atributos de Cuadricula
 */
TEST_F(CuadriculaTest, Test_Constructor_Atributos) {

    ///Assert
    EXPECT_NE(cd->getNodoInicial(),nullptr);
    ASSERT_EQ(cd->getNodoInicial()->getId(),0);
    EXPECT_NE(cd->getNodoFinal(),nullptr);
    ASSERT_EQ(cd->getNodoFinal()->getId(),((ZONE_SIZE - 1) * (ZONE_SIZE) + (ZONE_SIZE - 1)));

}


//////////////////////////////CUADRICULA//////////////////////////////





//////////////////////////////GLADIADOR//////////////////////////////*



//////////////////////////////GLADIADOR//////////////////////////////





////////////////////////////////JUEGO////////////////////////////////*


/**
 * Text Fixture de una instancia de Juego
 */
struct JuegoTest : public testing::Test {
    Juego* jt;
    void SetUp() { jt = new Juego(); }
    void TearDown() { delete jt; }
};


/**
 * Test de la creación correcta de una instancia de Juego
 */
TEST_F(JuegoTest, Test_Constructor) {

    ///Assert
    EXPECT_NE(jt,nullptr);

}

/**
 * Test de la creación correcta de los atributos de Juego
 */
TEST_F(JuegoTest, Test_Constructor_Atributos) {

    ///Assert
    EXPECT_NE(jt->getCuadricula(),nullptr);
    EXPECT_NE(jt->getNodoInicio(),nullptr);
    EXPECT_NE(jt->getNodoFinal(),nullptr);
    EXPECT_NE(jt->getAStarAlgorithm(),nullptr);
    EXPECT_NE(jt->getBacktrackingAlgorithm(),nullptr);
    EXPECT_NE(jt->getPoblacion1(),nullptr);
    EXPECT_NE(jt->getPoblacion2(),nullptr);
    EXPECT_NE(jt->getGladiador1(),nullptr);
    EXPECT_NE(jt->getGladiador2(),nullptr);

}


////////////////////////////////JUEGO////////////////////////////////





/////////////////////////////////LIST/////////////////////////////////*



/////////////////////////////////LIST/////////////////////////////////





/////////////////////////////////NODE/////////////////////////////////*



/////////////////////////////////NODE/////////////////////////////////





//////////////////////////////POBLACION//////////////////////////////*



//////////////////////////////POBLACION//////////////////////////////





/////////////////////////////___/////////////////////////////


/*
//Fixture

struct FixtureName : public testing::Test {
    Class* cl;
    void SetUp() { cl = new Class(); }
    void TearDown() { delete cl; }
};

*/


/*
//TEST_F

TEST_F(FixtureName, TestName_1) {

    ///Arrange
    //Arrange everything to run the Test


    ///Act
    //Run the Test

    ///Assert
    //Verify the Output

}

 */

/////////////////////////////___/////////////////////////////

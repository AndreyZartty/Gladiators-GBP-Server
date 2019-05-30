#include <iostream>
#include <gtest/gtest.h>
#include "Juego.h"

#include <gmock/gmock.h>

#include "Gladiador.h"
#include "poblacion.h"

using testing::Eq;

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

/**
 * Test para verificar el largo del path, siendo así
 * un path completo de start a goal
 */
TEST_F(AStarTest, Test_FindPath_PathToGo) {

    ///Act
    as->setInitializedStartGoal(false);
    as->setFoundGoal(false);
    as->findPath(jt->getNodoInicio(),jt->getNodoFinal());

    ///Assert
    ASSERT_GE(as->getPathToGoal().size(),10);

}


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


/**
 * Test del borrado correcto de las listas que utiliza el algoritmo Backtracking
 */
TEST_F(BacktrackingTest, Test_FindPath_Wipe_Lists) {

    ///Arrange:
    //PathToGoal
    bt->getPathToGoal().push_back(0);
    bt->getPathToGoal().push_back(11);
    bt->getPathToGoal().push_back(22);
    bt->getPathToGoal().push_back(33);
    //FullPath
    bt->getFullPath().push_back(0);
    bt->getFullPath().push_back(10);
    bt->getFullPath().push_back(11);
    bt->getFullPath().push_back(22);
    bt->getFullPath().push_back(23);
    bt->getFullPath().push_back(33);

    ///Act
    //Limpia pathToGoal
    bt->getPathToGoal().clear();
    ///Limpia fullPath
    bt->getFullPath().clear();

    ///Assert
    ASSERT_EQ(bt->getPathToGoal().size(),0);
    ASSERT_EQ(bt->getPathToGoal().size(),0);

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

/**
 * Test de la creacion de torres en Cuadricula
 */
TEST_F(CuadriculaTest, Test_Creacion_Torres) {

    ///Act
    cd->newTower();
    cd->newTower();
    cd->newTower();

    ///Assert
    ASSERT_EQ(cd->getTowerIdList().size(),3);

}

/**
 * Test del borrado de torres en Cuadricula
 */
TEST_F(CuadriculaTest, Test_Borrado_Torres) {

    ///Act
    cd->newTower();
    cd->newTower();
    cd->deleteTower(cd->getTowerIdList()[0]);


    ///Assert
    ASSERT_EQ(cd->getTowerIdList().size(),1);

}

/**
 * Test del restaurado de la lista de Torres no Verificadas en Cuadricula
 */
TEST_F(CuadriculaTest, Test_ResetVerifiedNot) {

    ///Act
    cd->newTower();
    int towerId = cd->getTowerIdList()[0];
    cd->addToVerifiedNot(towerId);
    cd->resetVerifiedNot();

    ///Assert
    ASSERT_EQ(cd->getVerfifiedNotTowersIdList().size(),0);

}



//////////////////////////////CUADRICULA//////////////////////////////





//////////////////////////////GLADIADOR//////////////////////////////*


/**
 * Text Fixture de una instancia de Gladiador obtenida de una instancia
 * de Juego.
 */
struct GladiadorTest : public testing::Test {
    Juego* jt;
    Gladiador* gl;
    void SetUp() { jt = new Juego(); gl = jt->getGladiador1(); }
    void TearDown() { delete jt; delete gl; }
};



TEST_F(GladiadorTest, testResistencia){

    ///Se establecen todos los atributos necesarios para realizar el algoritmo que calcula la resistencia

    gl->setEdad(16);///Se establece una edad pequena para confirmar que la resistencia cambia segun la edad

    gl->setInteligencia(1);
    gl->setCondicionFisica(1);
    gl->setFuerzaSuperior(1);
    gl->setFuerzaInferior(1);
    gl->setResistencia();
    ASSERT_EQ(23, gl->getResistencia());

    gl->setEdad(30);///Se establece una edad media para confirmar si resistencia aumenta como deberia
    gl->setResistencia();
    ASSERT_EQ(28, gl->getResistencia());

    gl->setEdad(50);///Se establece una edad avanzada para confirmar si resistencia disminuye como deberia
    gl->setResistencia();
    ASSERT_EQ(18, gl->getResistencia());

    gl->setEdad(80);///Se establece una edad muy alta para confirmar si el gladiador muere y su resistencia llega a 0
    gl->setResistencia();
    ASSERT_EQ(0, gl->getResistencia());
}


TEST_F(GladiadorTest, testPadres){

    Gladiador *padre1 = new Gladiador(1);
    Gladiador *padre2 = new Gladiador(1);

    padre1->setNombre("Padre");
    padre2->setNombre("Madre");

    Gladiador *gladiador = new Gladiador(2,padre1,padre2);

    Gladiador* glad = gladiador;

    ASSERT_EQ("Padre", glad->getNombrePadre1());
    ASSERT_EQ("Madre", glad->getNombrePadre2());

}

TEST_F(GladiadorTest, testMuerte){

    gl->setEdad(80);
    gl->setInteligencia(1);
    gl->setCondicionFisica(1);
    gl->setFuerzaSuperior(1);
    gl->setFuerzaInferior(1);
    gl->setResistencia();

    ASSERT_EQ(1, gl->getMuerto());
}


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
    ASSERT_NE(jt,nullptr);

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

/**
 * Test de la creación torres para la Cuadricula dentro de Juego
 */
TEST_F(JuegoTest, Test_Creacion_Torres) {

    ///Act
    jt->generateTowers(8);

    ///Assert
    EXPECT_EQ(jt->getCuadricula()->getTowerIdList().size(),8);

}

////////////////////////////////JUEGO////////////////////////////////





//////////////////////////////POBLACION//////////////////////////////*


/**
 * Text Fixture de una instancia de Poblacion obtenida de una instancia
 * de Juego.
 */
struct TestPoblacion : public testing::Test {
    Juego* jt;
    Poblacion* p1;
    void SetUp() { jt = new Juego(); p1 = jt->getPoblacion1(); }
    void TearDown() { delete jt; delete p1; }
};


TEST_F(TestPoblacion, testCantidadInicial){

    ASSERT_EQ(10, p1->getGladiadores().getSize());
}

TEST_F(TestPoblacion, testAgregarUnGladiador){

    Gladiador *gladiador;

    p1->insertarGladiador(gladiador);

    ASSERT_EQ(11, p1->getGladiadores().getSize());
}

TEST_F(TestPoblacion, testAgregarGeneracion){

    p1->nuevageneracion();


    ASSERT_EQ(18, p1->getGladiadores().getSize());
}


//////////////////////////////POBLACION//////////////////////////////


#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gladiador.h"
#include "poblacion.h"

using testing::Eq;

namespace {
    class TestGladiadores : public testing::Test {
    public:
        Gladiador obj;
        TestGladiadores(){
            obj;
        }
    };
}

TEST_F(TestGladiadores, testResistencia){

    ///Se establecen todos los atributos necesarios para realizar el algoritmo que calcula la resistencia

    obj.setEdad(16);///Se establece una edad pequena para confirmar que la resistencia cambia segun la edad

    obj.setInteligencia(1);
    obj.setCondicionFisica(1);
    obj.setFuerzaSuperior(1);
    obj.setFuerzaInferior(1);
    obj.setResistencia();
    ASSERT_EQ(23, obj.getResistencia());

    obj.setEdad(30);///Se establece una edad media para confirmar si resistencia aumenta como deberia
    obj.setResistencia();
    ASSERT_EQ(28, obj.getResistencia());

    obj.setEdad(50);///Se establece una edad avanzada para confirmar si resistencia disminuye como deberia
    obj.setResistencia();
    ASSERT_EQ(18, obj.getResistencia());

    obj.setEdad(80);///Se establece una edad muy alta para confirmar si el gladiador muere y su resistencia llega a 0
    obj.setResistencia();
    ASSERT_EQ(0, obj.getResistencia());
}


TEST_F(TestGladiadores, testPadres){

    Gladiador *padre1 = new Gladiador(1);
    Gladiador *padre2 = new Gladiador(1);

    padre1->setNombre("Padre");
    padre2->setNombre("Madre");

    Gladiador *gladiador = new Gladiador(2,padre1,padre2);

    obj = *gladiador;

    ASSERT_EQ("Padre", obj.getNombrePadre1());
    ASSERT_EQ("Madre", obj.getNombrePadre2());
}

TEST_F(TestGladiadores, testMuerte){

    obj.setEdad(80);
    obj.setInteligencia(1);
    obj.setCondicionFisica(1);
    obj.setFuerzaSuperior(1);
    obj.setFuerzaInferior(1);
    obj.setResistencia();

    ASSERT_EQ(1, obj.getMuerto());
}

namespace {
    class TestPoblacion : public testing::Test {
    public:
        Poblacion obj2;
        TestPoblacion(){
            obj2;
        }
    };
}


TEST_F(TestPoblacion, testCantidadInicial){

    Poblacion *p1 = new Poblacion("PoblacionPrueba");

    obj2 = *p1;

    ASSERT_EQ(10, obj2.getGladiadores().getSize());
}

TEST_F(TestPoblacion, testAgregarUnGladiador){

    Poblacion *p1 = new Poblacion("PoblacionPrueba");
    Gladiador *gladiador;

    p1->insertarGladiador(gladiador);

    obj2 = *p1;

    ASSERT_EQ(11, obj2.getGladiadores().getSize());
}

TEST_F(TestPoblacion, testAgregarGeneracion){

    Poblacion *p1 = new Poblacion("PoblacionPrueba");
    p1->nuevageneracion();

    obj2 = *p1;

    ASSERT_EQ(18, obj2.getGladiadores().getSize());
}


/*
TEST( TestName, SubTest_1) {

    //Arange
    int value = 100;
    int increment = 5;

    //Act
    value = value + increment;

    //Assert
    ASSERT_EQ(value, 105);

}
 */
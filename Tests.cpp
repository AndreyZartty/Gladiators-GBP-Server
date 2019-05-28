#include <iostream>
#include <gtest/gtest.h>

#include "Juego.h"

using namespace std;


/**
 * GTests
 *
 * @since 27/05/19
 */


TEST( TestName, SubTest_1) {

    //Arange
    int value = 100;
    int increment = 5;

    //Act
    value = value + increment;

    //Assert
    ASSERT_EQ(value, 105);

}
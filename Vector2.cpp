
#include "Vector2.h"


/**
 * Representa un Vector
 *
 * @since 01/05/19
 */


/**
 * Constructor de Vector
 * @param _x
 * @param _y
 */
Vector2::Vector2(int _x, int _y) {
    x = _x;
    y = _y;
}


///Getters y Setters

/**
 * Getter de x del Vector.
 * @return x
 */
int Vector2::getX() {
    return x;
}

/**
 * Setter de x del Vector.
 * @param _x
 */
void Vector2::setX(int _x) {
    x = _x;
}

/**
 * Getter de y del Vector.
 * @return y
 */
int Vector2::getY() {
    return y;
}

/**
 * Setter de y del Vector.
 * @param _y
 */
void Vector2::setY(int _y) {
    y = _y;
}

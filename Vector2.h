
#ifndef GLADIATORS_GBP_VECTOR2_H
#define GLADIATORS_GBP_VECTOR2_H


/**
 * Header de Vector2
 *
 * @since 01/05/19
 */


class Vector2 {

private:
    int x;
    int y;

public:
    ///Constructor
    Vector2(int _x, int _y);

    ///Getters & Setters
    int getX();
    void setX(int _x);
    int getY();
    void setY(int _y);

};


#endif //GLADIATORS_GBP_VECTOR2_H

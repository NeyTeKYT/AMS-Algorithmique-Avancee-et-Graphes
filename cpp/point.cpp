#include <iostream>
#include "../h/point.h"
using namespace std;

point::point(double x, double y) {
    (*this).x = x;
    (*this).y = y;
}

void point::afficher() {
    cout << "(" << x << ", " << y << ")";
}

double point::getX() {
    return x;
}

double point::getY() {
    return y;
}
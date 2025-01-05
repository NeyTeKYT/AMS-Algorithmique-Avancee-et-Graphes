#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class point {

    private:
        double x;
        double y;

    public:
        point(double x, double y);
        void afficher();
        double getX();
        double getY();

};

#endif
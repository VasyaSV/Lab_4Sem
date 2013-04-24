#ifndef PROJECTION2D_H
#define PROJECTION2D_H
#include <QList>
#include "point.h"
#include "Constants.h"

class point2d{
public:
    int x;
    int y;
    point2d(){ x = y = 0;}
    point2d(int x, int y)
    {
        this->x=x;
        this->y=y;
    }
};

class projection2d{
public:
    QList <point2d> l2d;
    projection2d(const QList <point> l3d, char fO); // fO - 1 is Oxy, 2 is Oyz, 3 is Oxz projection
    int d_sign(int p1, int p2);
    int vect_sign(point2d p1, point2d p2, point2d p);
    bool is_convex();
};

#endif // PROJECTION2D_H

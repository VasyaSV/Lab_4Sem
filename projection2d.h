#ifndef PROJECTION2D_H
#define PROJECTION2D_H
#include <QList>
#include <qmath.h>
#include "point.h"
#include "figure.h"
#include "Constants.h"
#include "point2d.h"

class projection2d{
    QList <point2d> l2d;
    point d_vect;
   // point
    point b1, b2; // bazis 1 - условно x, 2 - условно y, 3
    int d_sign(int p1, int p2);
    int sign(int);

    // -1 p is lefter vector (p1, p2)
    // 1 p is righter vector (p1, p2)
    // 0 on line (p1, p2)
    int vect_sign(point2d p1, point2d p2, point2d p);
    // угол между векторами
    // тупой = -1
    // острый = 1
    // прямой = 0
    int ungl_sign(point p1, point p2);
public:
    projection2d(const QList <point> l3d, char fO); // fO - 1 is Oxy, 2 is Oyz, 3 is Oxz projection
    projection2d();
    //projection2d(char fO, figure* fgr);
    //projection2d();
    point bazis(int n); // return bazis number n
    bool is_convex();
    int get_num_points();
    point get_dvect();
    point get_real_pos(point2d);
    point2d get_point(int n);
    point2d get_proj_point(point, int fO);
    void set_new(QList<point> l3d, char fO);
    float S(point l1, point l2, point p); // растояние от прямой l до точки p
};

#endif // PROJECTION2D_H

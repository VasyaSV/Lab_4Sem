#ifndef FIGURE_H
#define FIGURE_H

#include <QString>
#include <QList>
#include "point.h"
#include "Constants.h"

class figure{
public:
    QList <point> points_base;   // in one plane //set or part colculate
    point point_hight_A;         // AB vertical plane point_base //set or colculate
    QList <double> sites;         // colculate only
    QString figure_type;         // piramid || prisme //set or colculate
    QString base_type;           // equilateral convex || unequilateral convex || unequilateral unconvex //set or colculate
    int hight;                   // >0 //set or colculate
    figure();
};

#endif // FIGURE_H

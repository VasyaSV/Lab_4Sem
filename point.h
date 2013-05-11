#ifndef POINT_H
#define POINT_H

#include "Constants.h"
class point{
public:
    float k[demention];
    point();
    point(const point& p);
    point(const int x, const int y, const int z);
    friend bool operator ==(point&, point&);
};


#endif // POINT_H

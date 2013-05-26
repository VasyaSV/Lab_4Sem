#ifndef POINT_H
#define POINT_H

#include "Constants.h"
class point{
public:
    float k[demention];
    point();
    point(const point& p);
    point(const float x, const float y, const float z);
    friend bool operator ==(point&, point&);
    point operator -(point);
};

#endif // POINT_H

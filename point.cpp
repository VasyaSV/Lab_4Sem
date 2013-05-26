#include "point.h"

point::point(){
    for (int i=0; i<demention; i++)
        k[i]=0;
}
point::point(const point& p){
    for (int i=0; i<demention; i++)
        k[i]=p.k[i];
}
point::point(const float x, const float y, const float z){
    k[0]=x;
    k[1]=y;
    k[2]=z;
}
bool operator ==(point &p1, point &p2){
    for (int i=0; i<demention; i++)
        if (p1.k[i] != p2.k[i])
            return 0;
    return 1;
}

point point::operator -(point p){
    return point(this->k[0]-(float)p.k[0], this->k[1]-(float)p.k[1], this->k[2]-(float)p.k[2]);
}

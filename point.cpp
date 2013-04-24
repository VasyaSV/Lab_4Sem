#include "point.h"

point::point(){
    for (int i=0; i<demention; i++)
        k[i]=0;
}
point::point(const point& p){
    for (int i=0; i<demention; i++)
        k[i]=p.k[i];
}
point::point(const int x, const int y, const int z){
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

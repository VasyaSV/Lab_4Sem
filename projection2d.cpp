#include "projection2d.h"

projection2d::projection2d(const QList <point> l3d, char fO){ // fO - 1 is Oxy, 2 is Oyz, 3 is Oxz projection
    QList <point>::const_iterator i;
    for (i=l3d.begin(); i!=l3d.end(); ++i)
        if (fO==1)
            l2d.push_back(point2d((*i).k[0],(*i).k[1]));
        else if (fO==2)
            l2d.push_back(point2d((*i).k[1],(*i).k[2]));
        else if (fO==3)
            l2d.push_back(point2d((*i).k[0],(*i).k[2]));
}
int projection2d::d_sign(int p1, int p2){
    if (p1==p2)
        return 0;
    if (p1>p2)
        return 1;
    return -1;
}
int projection2d::vect_sign(point2d p1, point2d p2, point2d p){
// -1 p is lefter vector (p1, p2)
// 1 p is righter vector (p1, p2)
// 0 on line (p1, p2)
    if (p1.x==p2.x)
    {
        int d;
             d   = d_sign(p.x, p1.x)*(-1 * d_sign(p1.y, p2.y));
        return d; // (-1 * d_sign(p1.y, p2.y)) change signed if p1.y<p2.y
    }
    double k=abs((p2.y-p1.y)/(p2.x-p1.x)); // tg alfa
    double c = p1.y - k*p1.x;

    int d;
         d = d_sign(k*p.x+c, p.y)*(-1*d_sign(p1.x, p2.x));
    return d;
}
bool projection2d::is_convex(){
    if (l2d.size()<4)
        return 1;
    QList <point2d>::iterator i, j;
    point2d last = *(l2d.end()-1);
    char now_sign = 0;
    for (i=l2d.begin(); i!=l2d.end(); last=*i, i++)
        for (j=l2d.begin(); j!=l2d.end(); j++)
            if (i != j)
                if (now_sign == 0)
                    now_sign = vect_sign(last, *i, *j);
                else
                    if (now_sign != vect_sign(last, *i, *j) && now_sign && vect_sign(last, *i, *j))
                        return 0;
    return 1;
}

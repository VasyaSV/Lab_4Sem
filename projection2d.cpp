#include "projection2d.h"

projection2d::projection2d(){
}

float projection2d::S(point l1, point l2, point p){
    point point_on_l = l1;// точка на прямой
    point direct_vect_l = l2-l1;// направляющий вектор прямой
    point d_point = point_on_l - p;
    float len_direct_vect = sqrt(direct_vect_l.k[0]*direct_vect_l.k[0]
            + direct_vect_l.k[1]*direct_vect_l.k[1]
            + direct_vect_l.k[2]*direct_vect_l.k[2]);
    float i, j, k; // вычисляем через детерминат i j k
    i = d_point.k[1]*direct_vect_l.k[2] - direct_vect_l.k[1]*d_point.k[2];
    j = d_point.k[2]*direct_vect_l.k[0] - direct_vect_l.k[2]*d_point.k[0];
    k = d_point.k[0]*direct_vect_l.k[1] - direct_vect_l.k[0]*d_point.k[1];
    float len_det_ijk = sqrt(i*i + j*j + k*k);
    if (!len_direct_vect)
         return 0;
    float tenp = len_det_ijk / len_direct_vect;
    return len_det_ijk / len_direct_vect;
}

point projection2d::bazis(int n){
    if (n)
        return b2;
    return b1;
}

point projection2d::get_dvect(){
    return d_vect;
}

point projection2d::get_real_pos(point2d in_bazis){
    float x = in_bazis.x*b1.k[0] + in_bazis.y*b2.k[0] + d_vect.k[0]
         ,y = in_bazis.x*b1.k[1] + in_bazis.y*b2.k[1] + d_vect.k[1]
         ,z = in_bazis.x*b1.k[2] + in_bazis.y*b2.k[2] + d_vect.k[2]
            ;
    return point(x, y, z);
}

void projection2d::set_new(QList <point> l3d, char fO){
    QList <point>::iterator i;
    l2d.clear();
    if (!l3d.size())
        return;
//    if (l3d.size() == 1)
        d_vect = l3d.at(0); // векстор смещения
    //else
       // d_vect = l3d.at(1);
    if (fO==0 && l3d.size() >= 3) // отображение на плоскость только прин аличии прлоскости
    {
        float A, B, C; // добавить проверку на не колониарность трех точек
        float x1, y1, z1, x2, y2, z2, x3, y3, z3;
        point p1=l3d.at(0);
        point p2=l3d.at(1);
        point p3=l3d.at(2);
        x1=p1.k[0];
        y1=p1.k[1];
        z1=p1.k[2];
        x2=p2.k[0];
        y2=p2.k[1];
        z2=p2.k[2];
        x3=p3.k[0];
        y3=p3.k[1];
        z3=p3.k[2];
        A=(y2-y1)*(z3-z1) - (y3-y1)*(z2-z1);
        B=(z2-z1)*(x3-x1) - (z3-z1)*(x2-x1);
        C=(x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);

        x1=p1.k[0];
        y1=p1.k[1];
        z1=p1.k[2];
        x2=p2.k[0];
        y2=p2.k[1];
        z2=p2.k[2];
        x3=p1.k[0]+A;
        y3=p1.k[1]+B;
        z3=p1.k[2]+C;
        A=(y2-y1)*(z3-z1) - (y3-y1)*(z2-z1);
        B=(z2-z1)*(x3-x1) - (z3-z1)*(x2-x1);
        C=(x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);

        // базис в плоскости основания
        b1.k[0]=p2.k[0]-p1.k[0];//-d_vect.k[0];
        b1.k[1]=p2.k[1]-p1.k[1];//-d_vect.k[1];
        b1.k[2]=p2.k[2]-p1.k[2];//-d_vect.k[2];
        b2.k[0]=A;
        b2.k[1]=B;
        b2.k[2]=C;

        // нормируем его
        float len1= sqrt(b1.k[0]*b1.k[0] + b1.k[1]*b1.k[1] + b1.k[2]*b1.k[2]),
              len2= sqrt(b2.k[0]*b2.k[0] + b2.k[1]*b2.k[1] + b2.k[2]*b2.k[2]);
       // float qrt_len1 = len1*len1,
        //      qrt_len2 = len2*len2;
        if (!len1 || !len2)
            return;
        b1.k[0]/=len1;
        b1.k[1]/=len1;
        b1.k[2]/=len1;
        b2.k[0]/=len2;
        b2.k[1]/=len2;
        b2.k[2]/=len2;
    }

    for (i=l3d.begin(); i!=l3d.end(); ++i)
        if (fO==0)
            l2d.push_back(point2d(ungl_sign(b1, *i - d_vect)*S(point(0,0,0), b2, *i - d_vect),
                                  ungl_sign(b2, *i - d_vect)*S(point(0,0,0), b1, *i - d_vect)));
        else if (fO==1)
            l2d.push_back(point2d((*i).k[0] - d_vect.k[0],(*i).k[1] - d_vect.k[1]));
        else if (fO==2)
            l2d.push_back(point2d((*i).k[1] - d_vect.k[1],(*i).k[2] - d_vect.k[2]));
        else if (fO==3)
            l2d.push_back(point2d((*i).k[0] - d_vect.k[0],(*i).k[2] - d_vect.k[2] ));
}

int projection2d::sign(int c){
    if (c>0)
        return 1;
    if (c<0) return -1;
    return 0;
}

projection2d::projection2d(const QList <point> l3d, char fO){ // fO - 1 is Oxy, 2 is Oyz, 3 is Oxz projection
    set_new(l3d, fO);
}

int projection2d::ungl_sign(point p1, point p2){
    point vp = p2-p1;
    float temp = p1.k[0]*p2.k[0] + p1.k[1]*p2.k[1] + p1.k[2]*p2.k[2];
    if (!temp)
        temp = 1;
    return sign(temp);
}

point2d projection2d::get_proj_point(point p, int fO){
    if (fO==0)
        return point2d(ungl_sign(b1, p - d_vect)*S(point(0,0,0), b2, p - d_vect),
                       ungl_sign(b2, p - d_vect)*S(point(0,0,0), b1, p - d_vect));
    else if (fO==1)
        return point2d(p.k[0] - d_vect.k[0], p.k[1] - d_vect.k[1]);
    else if (fO==2)
        return point2d(p.k[1] - d_vect.k[1], p.k[2] - d_vect.k[2]);
    else if (fO==3)
        return point2d(p.k[0] - d_vect.k[0], p.k[2] - d_vect.k[2]);
}

int projection2d::get_num_points(){
    return l2d.size();
}

//projection2d::projection2d(figure *fgr, char fO){ // fO - 1 is Oxy, 2 is Oyz, 3 is Oxz projection

//    QList <point>::const_iterator i;
//    for (i=0; i < fgr->get_base_size(); ++i)
//        if (fO==1)
//            l2d.push_back(point2d(fgr->get_point_base(i).k[0],fgr->get_point_base(i).k[1]));
//        else if (fO==2)
//            l2d.push_back(point2d(fgr->get_point_base(i).k[1],fgr->get_point_base(i).k[2]));
//        else if (fO==3)
//            l2d.push_back(point2d(fgr->get_point_base(i).k[0],fgr->get_point_base(i).k[2]));
//}

point2d projection2d::get_point(int n){
    return l2d.at(n);
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


#include "figure.h"

figure::figure()
{
    points_base.push_back(point());
    hight=
    point_hight_A.k[0]=point_hight_A.k[1]=point_hight_A.k[2]=0;
    figure_type=
    base_type=defoult;
    calc_base_type();
    calc_sites();
}

figure::figure(QString figure_type, int hight, QString point_hight, QString base_point){
    set_figure_type(figure_type);
    set_hight(hight);
    set_point_hight(point_hight);
    set_point_base(base_point);
    calc_base_type();
    calc_sites();
}

bool figure::point_in_one_plane(){ // Function work in 3D only, for more need giperkomplane
    if (this->points_base.size()<=3)
        return 1;
    QList <point>::const_iterator i;
    i = this->points_base.begin();
    int x1, x2, x3, y1, y2, y3, z1, z2, z3;
    x1 = (*i).k[0];
    y1 = (*i).k[1];
    z1 = (*i).k[2];
    ++i;
    x2 = (*i).k[0];
    y2 = (*i).k[1];
    z2 = (*i).k[2];
    ++i;
    x3 = (*i).k[0];
    y3 = (*i).k[1];
    z3 = (*i).k[2];
    ++i;
    for (; i!=this->points_base.end(); ++i)
    {
        int x= (*i).k[0],
            y= (*i).k[1],
            z= (*i).k[2];
        // not one plane // plane detarminate
        if ((x-x1)*(y2-y1)*(z3-z1)+(y-y1)*(z2-z1)*(x3-x1)+(z-z1)*(x2-x1)*(y3-y1)
                - (x3-x1)*(y2-y1)*(z-z1) - (y3-y1)*(z2-z1)*(x-x1) - (z3-z1)*(x2-x1)*(y-y1))
            return 0;
    }
    return 1;
}
bool figure::figure_is_equilateral(){
    if (this->sites.size() < 3)
        return 1;
    QList <double>::const_iterator i;
    for (i = this->sites.begin()+1; i!=this->sites.end() ; ++i)
        if ((*i) != *(i-1))
            return 0;
    return 1;
}
bool figure::figure_is_convex(){
    if (this->sites.size()<3)
        return 1;
    projection2d *d2p;
    bool z_change=0;
    QList <point>::const_iterator i;
    for (i=this->points_base.begin()+1; i!=this->points_base.end(); ++i)
        if ((*i).k[2]!=(*(i-1)).k[2])
            z_change = 1;
    if (!z_change)
        d2p=new projection2d(this->points_base, 1);
    else
        d2p=new projection2d(this->points_base, 2);
    return d2p->is_convex();
}

QList <point> figure::string_to_points(const QString str) const{
    QList <point> lst;
    int i=0, j;
    QString qstmp;
    while (i<str.length())
    { // format (9,9,9)(9,9,9)(9,9,9)(9,9,9)(9,9,9)(9,9,9)...(9,9,9)
        point p;
        i++; // (
        char tmp[100];
        for (int k=0; k<demention; k++){
            for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='-') ; i++, j++)
                tmp[j]= str[i].unicode();
            tmp[j]=0;
            qstmp = tmp;
            p.k[k] = qstmp.toInt();
            i++; // , || )
        }
        lst.push_back(p);
    }
    return lst;
}
QList <double> figure::string_to_list_double(const QString str) const{
    QList <double> lst;
    int i=0, j;
    QString qstmp;
    while (i<str.length())
    { //format 9.9_9.9_9.9...9.9
        char tmp[100];
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='.') ; i++, j++)
            tmp[j]=str[i].unicode();
        tmp[j]=0;
        qstmp = tmp;
        lst.push_back(qstmp.toInt());
        i++; // _ || /0
    }
    return lst;
}

QString figure::get_hight_point_to_QStr() const{
    point p = this->point_hight_A;
    QString str("(");
    for (int k=0; k<demention; k++){
        QString tmp;
        tmp.setNum(p.k[k]);
        str += tmp + ",";
    }
    str[str.length()-1]=')';
    return str;
}
QString figure::get_sites_list_to_QStr() const{
    QString str="";
    QList <double>::const_iterator i;
    for (i = this->sites.begin(); i!=this->sites.end(); ++i)
        if (i == this->sites.begin())
            str+=QString("%1").arg(*i);
        else
            str+=QString("_%1").arg(*i);
    if (!str.length())
        return defoult;
    return str;
}
QString figure::get_points_base_to_QStr() const
{
    QString str("");
    QList <point>::const_iterator i;
    for (i = this->points_base.begin(); i!=this->points_base.end(); ++i)
    {
        QString pstr("(");
        for (int k=0; k<demention; k++){
            QString tmp;
            tmp.setNum((*i).k[k]);
            pstr += tmp + ",";
        }
        pstr[pstr.length()-1]=')';
        str.push_back(pstr);
    }
    if (!str.length())
        return defoult;
    return str;
}

void figure::calc_sites()
{
    QList <point>::iterator i; // calculate length site
    this->sites.clear();
    for (i=this->points_base.begin(); i != this->points_base.end(); ++i)
    {
        point p1, p2;
        p1 = *i;
        if (i == this->points_base.end()-1)
            p2 = this->points_base.at(0);
        else
            p2 = *(i+1);

        double sum_sqr_de_komponent(0); // summ squear delta komponent
        for (int k=0; k<demention; k++)
            sum_sqr_de_komponent += (p1.k[k] - p2.k[k])*(p1.k[k] - p2.k[k]);
        double long_site = sqrt(sum_sqr_de_komponent);
        this->sites.push_back(long_site);
    }
}
void figure::calc_base_type()
{
    //   convex equilateral
    //   convex
    //   unconvex
   QString type("");
   if (!point_in_one_plane() || this->points_base.size()<1)
   {
       this->base_type = "incorect";
       return;
   }
   if (!figure_is_convex())
   {
       this->base_type = "unconvex";
       return;
   }
   type = "convex";
   if (figure_is_equilateral())
       switch (this->points_base.size())
       {
       case 1:
           this->base_type = "point";
           return;
       case 2:
           this->base_type = "line";
           return;
       case 3:
           this->base_type = "right_triangle";
           return;
       case 4:
           this->base_type = "squear";
           return;
       default:
           type += "_equilateral";
       }
   this->base_type = type;
}

int figure::get_hight_to_int() const{
    return hight;
}

void figure::set_hight(const int h){
    hight=h;
}
void figure::set_hight(const QString h){
    hight = h.toInt();
}
void figure::set_point_base(const QString l_points){
    points_base = string_to_points(l_points);
    calc_base_type();
    calc_sites();
}
void figure::set_point_hight(const QString point){
    point_hight_A = string_to_points(point)[0];
}
void figure::set_figure_type(const QString f_t){
    figure_type = f_t;
}
void figure::set_point_hight(const point p){
    point_hight_A = p;
}
void figure::set_point_base(const point p){
    points_base.clear();
    points_base.append(p);
    calc_base_type();
    calc_sites();
}
void figure::add_point_base(const point p){
    points_base.append(p);
    calc_base_type();
    calc_sites();
}

// QString constructors
QString figure::get_figure_type_to_QStr() const{
    return figure_type;
}
QString figure::get_base_type_to_QStr() const{
    return base_type;
}
QString figure::get_hight_to_QStr() const{
    return QString().setNum(hight);
}

point figure::get_point_base(int i) const{
    return points_base.at(i);
}
point figure::get_point_hight() const{
    return point_hight_A;
}
int figure::get_base_size() const{
    return points_base.size();
}

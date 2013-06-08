#ifndef FIGURE_H
#define FIGURE_H

#include <QString>
#include <QList>
#include "point.h"
#include "Constants.h"
#include "projection2d.h"

class figure{
    point point_hight_A;         // AB vertical plane point_base //set or colculate
    QList <double> sites;         // colculate only
    QString figure_type;         // piramid || prisme //set or colculate
    QString base_type;           // equilateral convex || unequilateral convex || unequilateral unconvex //set or colculate
    int hight;                   // >0 //set or colculate

    // QList constructors
    QList <point> string_to_points(const QString) const;
    QList <double> string_to_list_double(const QString str) const;

    void calc_sites();
    void calc_base_type();

    //bool point_in_one_plane(point p1, point p2, point p3, point p);
    bool point_in_one_plane();
    bool figure_is_convex();
    bool figure_is_equilateral();

public:
    QList <point> points_base;   // in one plane //set or part colculate
    // seek old_p (or first point in epsilon radius) and change on new_p
    void change_point_base(point old_p, point new_p, float epsilon = 0);
    //void change_point_base(point old_p, point new_p, float epsilon = 0);
    void set_hight(const int);
    void set_hight(const QString);

    void set_point_base(const QString);
    void set_point_hight(const QString);
    void set_figure_type(const QString);
    void set_point_hight(const point);
    void set_point_base(const point);
    void add_point_base(const point);

    // QString constructors
    QString get_figure_type_to_QStr() const;
    QString get_base_type_to_QStr() const;
    QString get_points_base_to_QStr() const;
    QString get_sites_list_to_QStr() const;
    QString get_hight_point_to_QStr() const;
    QString get_hight_to_QStr() const;
    int get_hight_to_int() const;
    point get_point_base(int) const;
    point get_point_hight() const;
    int get_base_size() const;

    float S(point, point);
    int get_n_point(point , float ep);
    figure();
    figure(QString figure_type, int hight, QString point_hight, QString base_point);
};

#endif // FIGURE_H

#ifndef MODEL_FIGURE_H
#define MODEL_FIGURE_H
/// «¿ ŒÃ»“»“‹!!!
#include <QObject>
#include <QString>
#include <iostream>
#include <vector>
#include <QtSql>

using namespace std;

struct point{
    int x;
    int y;
    int z;
};

struct seek_struct{
    int id;
    bool _id;

    int hight;
    bool _hight;

    QString base_type;
    bool _base_type;

    QString figure_type;
    bool _figure_type;

    vector <point> points;
    bool _points;

    vector <int> sites;
    bool _sites;
};

// Model cur (cultivated) figure
class model_figure : public QObject
{
    Q_OBJECT
    // input figure: <number points> <point [1]> <point [2]> ... <point [number points]>
    // point: x y z
    // figure types: pyramid || prism
    // base type: equilateral convex || unequilateral convex || unequilateral unconvex

    int id; // individual number cur figure in base, change whith:

    vector <point> points; // set
    vector <int> sites; // calculated
    int hight; // calculated
    QString base_type; // calculated
    QString figure_type; // calculated

    QSqlDatabase data;
    QSqlQuery query;

    seek_struct seek;

public:
    model_figure();

    int get_hight(); // For getters: if returning value not calculated it calculating
    QString get_base_type();
    QString get_figure_type();

    void set_figures_from_file(string name);
    void set_figure_on_point(vector <point> points);

    void add_point(point);
    void add_point(int x, int y, int z);

    void set_point(point, point); // move p1 on p2

    void write_in_seek(seek_struct);
    void set_figure(); // seek in table figure for seek_struct seek
    void set_next(); // set next found figure

    void refreash(); // save cur figure in data
                    // add in data hight, long side
};

#endif // MODEL_FIGURE_H

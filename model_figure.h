#ifndef MODEL_FIGURE_H
#define MODEL_FIGURE_H

#include <QObject>
#include <QString>
#include <QtSql>
#include <QAbstractTableModel>
#include <QVector>
#include <QList>

using namespace std;

class point{
public:
    qint32 x;
    qint32 y;
    qint32 z;
    point::point()
    {
        x=y=z=0;
    }
};

class figure{
public:
    QList <point> points_base; // in one plane //set or part colculate
    point point_hight_A;         // AB vertical plane point_base //set or colculate
    point point_hight_B;         // ... //set or colculate
    // QVector <int> sites;      // colculate only
    QString figure_type;         // piramid || prisme //set or colculate
    QString base_type;           // equilateral convex || unequilateral convex || unequilateral unconvex //set or colculate
    int hight;                   // >0 //set or colculate

    //  true if set field
    bool f_pb;
    bool f_A;
    bool f_B;
    bool f_ft;
    bool f_bt;
    bool f_h;

    figure(){
       f_h = f_bt = f_ft = f_B = f_A = f_pb = false;
    }
};

class QATableFigure : public QAbstractTableModel{
Q_OBJECT

public:
QList <figure*> list;
QStringList header_data;

QATableFigure(QObject *parent);
QATableFigure();


bool setData(const QModelIndex &index, const QVariant &value, int role);

QVariant data(const QModelIndex &index, int role) const;

int rowCount(const QModelIndex &parent=QModelIndex()) const;
int columnCount(const QModelIndex &parent) const;

QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
Qt::ItemFlags flags(const QModelIndex &index) const;

// String constructors
QString vect_to_string(point p1, point p2);
QVariant string_list_points(QList <point>);
QList <point> string_to_points(QString);

};


















//struct seek_struct{
//    int id;
//    bool _id;

//    int hight;
//    bool _hight;

//    QString base_type;
//    bool _base_type;

//    QString figure_type;
//    bool _figure_type;

//    vector <point> points;
//    bool _points;

//    vector <int> sites;
//    bool _sites;
//};

//// Model cur (cultivated) figure
//class model_figure : public QObject
//{
//    Q_OBJECT
//    // input figure: <number points> <point [1]> <point [2]> ... <point [number points]>
//    // point: x y z
//    // figure types: pyramid || prism
//    // base type: equilateral convex || unequilateral convex || unequilateral unconvex

//    int id; // individual number cur figure in base, change whith:

//    vector <point> points; // set
//    vector <int> sites; // calculated
//    int hight; // calculated
//    QString base_type; // calculated
//    QString figure_type; // calculated

//    QSqlDatabase data;
//    QSqlQuery query;

//    seek_struct seek;

//public:
//    model_figure();

//    int get_hight(); // For getters: if returning value not calculated it calculating
//    QString get_base_type();
//    QString get_figure_type();

//    void set_figures_from_file(string name);
//    void set_figure_on_point(vector <point> points);

//    void add_point(point);
//    void add_point(int x, int y, int z);

//    void set_point(point, point); // move p1 on p2

//    void write_in_seek(seek_struct);
//    void set_figure(); // seek in table figure for seek_struct seek
//    void set_next(); // set next found figure

//    void refreash(); // save cur figure in data
//                    // add in data hight, long side
//};

#endif // MODEL_FIGURE_H

#ifndef MODEL_FIGURE_H
#define MODEL_FIGURE_H

#include <QObject>
#include <QString>
#include <QAbstractTableModel>
#include <QVector>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QTableWidgetItem>
#include "projection2d.h"
const int start_size_table = 1;

using namespace std;

class figure{
public:
    QList <point> points_base;   // in one plane //set or part colculate
    point point_hight_A;         // AB vertical plane point_base //set or colculate
    QList <double> sites;         // colculate only
    QString figure_type;         // piramid || prisme //set or colculate
    QString base_type;           // equilateral convex || unequilateral convex || unequilateral unconvex //set or colculate
    int hight;                   // >0 //set or colculate
    figure(){
        points_base.push_back(point());
        hight=
        point_hight_A.k[0]=point_hight_A.k[1]=point_hight_A.k[2]=0;
        figure_type=
        base_type="";
    }
};

class QATableFigure : public QAbstractTableModel{
Q_OBJECT

public:
QList <figure*> list;
QStringList header_data;

QATableFigure();
//QATableFigure(QObject *parent);

bool setData(const QModelIndex &index, const QVariant &value, int role);

QVariant data(const QModelIndex &index, int role) const;

int rowCount(const QModelIndex &parent=QModelIndex()) const;
int columnCount(const QModelIndex &parent) const;

QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
Qt::ItemFlags flags(const QModelIndex &index) const;

// QList constructors
QList <point> string_to_points(const QString) const;
QList <double> string_to_list_double(const QString str) const;

//   convex equilateral
//   convex
//   unconvex
void calc_sites(const QModelIndex&);
void calc_base_type(const QModelIndex&);

bool point_in_one_plane(point p1, point p2, point p3, point p);
bool point_in_one_plane(const QList <point>);
bool figure_is_convex(const QList <point>);
bool figure_is_equilateral(const QList <double>);

// QString constructors
QString sites_list_to_QStr(const QModelIndex&) const;
QString points_base_to_QStr(const QModelIndex&) const;
QString hight_to_QStr(const QModelIndex&) const;
QString sites_list_to_QStr(figure*) const;
QString points_base_to_QStr(figure*) const;
QString hight_to_QStr(figure*) const;

public slots:
void read_base_from_file(QString);
void write_base_in_file(QString);
void clear_cell(int row, int column);
void removeRow(int row, int num);
};

#endif // MODEL_FIGURE_H

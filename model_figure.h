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
#include <QVariant>
#include <QtSql/QtSql>
#include "projection2d.h"
#include "figure.h"
#include "Constants.h"

using namespace std;

class QATableFigure : public QAbstractTableModel{
Q_OBJECT

public:
bool f_sql;// sinhronize with sqlite base
QSqlDatabase data_base;
QSqlQuery a_query;
QString sql_name;

QList <figure*> list;
QStringList header_data;

QATableFigure();
//QATableFigure(QObject *parent);
// +=проверку на звезду
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
void sql(bool);
void set_sql_name(QString);
void insertRow(int row);
void removeRow(int row, int num);
void read_base_from_file(QString);
void write_base_in_file(QString);
void clear_cell(int row, int column);
};

#endif // MODEL_FIGURE_H

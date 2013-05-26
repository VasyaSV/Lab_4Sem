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
#include "Constants.h"
#include "projection2d.h"
#include "figure.h"
#include "sql_sync.h"
#include "name_dialog.h"

using namespace std;

class QATableFigure : public QAbstractTableModel{
Q_OBJECT

public:
QList <figure*> list;
QStringList header_data;

Sql_sync sql;

QATableFigure();
bool setData(const QModelIndex &index, const QVariant &value, int role);
QVariant data(const QModelIndex &index, int role) const;
int rowCount(const QModelIndex &parent=QModelIndex()) const;
int columnCount(const QModelIndex &parent) const;

QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;
Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
void read_from_sql(QString name_file, QString base_name = "figure");
void write_in_sql(QString name_file, QString base_name = "figure");

void insertRow(int row);
void removeRow(int row, int num);
void read_base_from_file(QString);
void write_base_in_file(QString);
void clear_cell(int row, int column);
};

#endif // MODEL_FIGURE_H

#ifndef SQL_SYNC_H
#define SQL_SYNC_H

#include <QVariant>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlRecord>
#include "figure.h"
//const QString def_sql_name = "temp.sqlite";

class Sql_sync{
public:
QSqlDatabase db;
QSqlQuery *query;
QString file_name;
QString base_name;
figure *tmp;
//QSqlRecord rec;
public:
    Sql_sync();
    void change(figure *old_f, figure *new_f);
    void add_figure(figure*);
    void delete_figure(figure*);
    void open_base(QString file_name, QString base_name);
    figure* get_cur_figure();
    figure* next();
    figure* first();
    void clear_base();
    void close();

    // for debug
    void print();
};



#endif // SQL_SYNC_H

#include "sql_sync.h"


Sql_sync::Sql_sync(){
    query = NULL;
    tmp = new figure();
    open_base("temp", "figure");
}

void Sql_sync::close(){
    if (db.isOpen())
       db.close();
}

void Sql_sync::open_base(QString file_name, QString base_name){
    this->file_name = file_name;
    this->base_name = base_name;
    if (query)
        delete query;
    if (db.isOpen())
        db.close();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(file_name);
    if (!db.open())
       qDebug("Error: bd not open");
    query = new QSqlQuery(db);
    //rec = query->record();
    QString   str  = "CREATE TABLE " + base_name +
                         " ( "
                         "figure_type   VARCHAR(30), "
                         "hight         INTEGER,     "
                         "hight_point   VARCHAR(30), "
                         "points_base   VARCHAR(150) "
                     ");";
    if (!query->exec(str)) {
        qDebug() << "Unable to create a table";
    }
    if (!query->exec("SELECT * FROM "+ base_name +";")) {
        qDebug() << "Unable to execute query - exiting";
        return ;
    }
}

void Sql_sync::add_figure(figure* f){
    if (!db.isOpen() || !query)
        return;
    QString insetrt_exec_F =
             "INSERT INTO " + base_name +
            " (figure_type, hight, hight_point, points_base) "
            "VALUES('%1', %2, '%3', '%4');";
    QString insert_exec =
            insetrt_exec_F.arg(f->get_figure_type_to_QStr())
                 .arg(f->get_hight_to_QStr())
                 .arg(f->get_hight_point_to_QStr())
                 .arg(f->get_points_base_to_QStr());
       if (!query->exec(insert_exec)) {
           qDebug() << "Unable to do insert opeation";
       }
}

void Sql_sync::delete_figure(figure *f){
    if (!db.isOpen() || !query)
        return;
    QString delete_exec = " DELETE FROM " + base_name +
            " WHERE figure_type='" + f->get_figure_type_to_QStr() + "'"
            " AND hight=" + f->get_hight_to_QStr() +
            " AND hight_point='" + f->get_hight_point_to_QStr() + "'"
            " AND points_base='" + f->get_points_base_to_QStr() + "'"
            ;
    if (!query->exec(delete_exec)) {
        qDebug() << "Unable to execute query - exiting";
        return ;
    }
}

void Sql_sync::change(figure* old_figure, figure* new_figure){
    if (!db.isOpen() || !query)
        return;
    delete_figure(old_figure);
    add_figure(new_figure);
}
void Sql_sync::print(){
    if (!db.isOpen() || !query)
        return;
    if (!query->exec("SELECT * FROM "+ base_name +";")) {
        qDebug() << "Unable to execute query - exiting";
        return ;
    }
    QString    figure_type;
    int        hight = 0;
    QString    hight_point;
    QString    points_base;
    query->first();
    do{
        figure_type  = query->value(0).toString();
        hight  = query->value(1).toInt();
        hight_point = query->value(2).toString();
        points_base = query->value(3).toString();
        qDebug() << figure_type << " " << hight << ";\t"
                 << hight_point << ";\t" << points_base;
    }while (query->next());
}

void Sql_sync::clear_base(){
    if ((!db.isOpen()) || !query)
        return;
    this->query->exec("DELETE FROM " + base_name + ";");
}

figure* Sql_sync::get_cur_figure(){
    if (!db.isOpen() || !query)
        return NULL;
    return tmp;
}

figure* Sql_sync::next(){
    if (!query->next() || !db.isOpen())
        return NULL;
    tmp=new figure;
    tmp->set_figure_type(query->value(0).toString());
    tmp->set_hight(query->value(1).toInt());
    tmp->set_point_hight(query->value(2).toString());
    tmp->set_point_base(query->value(3).toString());
    return tmp;
}

figure* Sql_sync::first(){
    if (!query->exec("SELECT * FROM "+ base_name +";")) {
        qDebug() << "Unable to execute query - exiting";
        return NULL;
    }
    if (!query->first() || !db.isOpen())
            return NULL;
    tmp=new figure;
    tmp->set_figure_type(query->value(0).toString());
    tmp->set_hight(query->value(1).toInt());
    tmp->set_point_hight(query->value(2).toString());
    tmp->set_point_base(query->value(3).toString());
    return tmp;
}

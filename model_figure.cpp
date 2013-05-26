#include "model_figure.h"

QATableFigure::QATableFigure()
{
    header_data << QString("Figure type") << QString("Base type")
                << QString("Hight") << QString("Hight posicion")
                << QString("Base points") << QString("Long base sites");
    for(int i = 0; i < start_size_table; i++)
        list.append(new figure);
    sql.clear_base();
}

QVariant QATableFigure::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= list.size())
        return QVariant();
    // for everyone column return value
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0)
            return list.at(index.row())->get_figure_type_to_QStr();
        if (index.column() == 1)
            return list.at(index.row())->get_base_type_to_QStr();
        if (index.column() == 2)
            return list.at(index.row())->get_hight_to_int();
        if (index.column() == 3)
            return list.at(index.row())->get_hight_point_to_QStr();
        if (index.column() == 4 )
            return list.at(index.row())->get_points_base_to_QStr();
        if (index.column() == 5 )
            return list.at(index.row())->get_sites_list_to_QStr();
    }
    return QVariant();
}
bool QATableFigure::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole){
        if (index.row() == list.size()-1){
            beginInsertRows(QModelIndex(), list.size(), list.size());
            list.append(new figure);
            endInsertRows();
        }
        figure old = *(list.at(index.row()));
        // read value to everyone column
        if (index.column() == 0)
            list.at(index.row())->set_figure_type(value.toString());
        if (index.column() == 2)
            list.at(index.row())->set_hight(value.toUInt());
        if (index.column() == 3)
            list.at(index.row())->set_point_hight(value.toString());
        if (index.column() == 4)
            list.at(index.row())->set_point_base(value.toString());
        sql.change(&old, list.at(index.row()));
        return true;
    }
    return false;
}
int QATableFigure::rowCount(const QModelIndex &parent) const
{
    return list.size(); // list.size() = namber strings
}
int QATableFigure::columnCount(const QModelIndex &parent) const
{
    return 6; // 6 column
}
QVariant QATableFigure::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(role != Qt::DisplayRole)
           return QVariant();
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
       return header_data.at(section); // header column
   }else{
       return QString("%1").arg(section + 1); // return namber strings
   }
}
Qt::ItemFlags QATableFigure::flags(const QModelIndex &index) const
{
   if (!index.isValid())
        return Qt::ItemIsEnabled;
   return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void QATableFigure::read_from_sql(QString name_file, QString name_base){

    qDebug("=)");
    sql.open_base(name_file, name_base);
    figure *f;
    //sql.print();
    if (!(f = sql.first()))
        return;
    do{
        beginInsertRows(QModelIndex(), list.size(), list.size());
        list.append(f);
        endInsertRows();
    }
    while (f = sql.next());
}

void QATableFigure::write_in_sql(QString name_file, QString name_base){
    QList <figure*>::iterator i;
    sql.open_base(name_file, name_base);
    sql.clear_base();
    for (i = list.begin(); i!=list.end(); ++i)
        sql.add_figure(*i);
}

void QATableFigure::read_base_from_file(QString name){
    QFile file(name);
    char str[500];
    figure *tmp;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    //sql.clear_base();
    while(!in.atEnd())
    {
        tmp=new figure();
        str[0]=0;
        in >> str;
        if (QString(str) == QString("SQLite"))
        {
            Name_dialog *d_name = new Name_dialog(QString("It's sql base, please enter name base"),
                                                  QString("File name"), QString("Base name"),
                                                  name);
            QObject::connect(d_name, SIGNAL(name(QString,QString)), this, SLOT(read_from_sql(QString,QString)));
            break;
        }
        //sql.open_base("temp", "figure");
        if (in.atEnd()) break;
        str[strlen(str)-1]=0;
        tmp->set_figure_type(str);

        in >> str;
        str[strlen(str)-1]=0;
        if (in.atEnd()) break;
        tmp->set_hight(str);

        in >> str;
        if (in.atEnd()) break;
        str[strlen(str)-1]=0;
        tmp->set_point_hight(str);

        in >> str;
        if (in.atEnd()) break;
        str[strlen(str)-1]=0;
        tmp->set_point_base(str);

        beginInsertRows(QModelIndex(), list.size(), list.size());
        list.append(tmp);
        endInsertRows();

        //sql.add_figure(tmp);
    }

    delete tmp;
    file.close();
}
void QATableFigure::write_base_in_file(QString name){
    if (name.lastIndexOf(QString(".SQLite")) != -1)
    {
        Name_dialog *d_name = new Name_dialog(QString("Please enter name base for save"),
                                              QString("File name"), QString("Base name"),
                                              name);
        QObject::connect(d_name, SIGNAL(name(QString,QString)), this, SLOT(write_in_sql(QString,QString)));
        return;
    }
    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QList <figure*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i)
    {
        out << (*i)->get_figure_type_to_QStr() << "_ ";
        out << (*i)->get_hight_to_QStr() << "_ ";
        out << (*i)->get_hight_point_to_QStr() << "_ ";
        out << (*i)->get_sites_list_to_QStr() << "_ ";
    }
    file.close();
}

void QATableFigure::removeRow(int row, int num){
    if (list.size() < 1 || num < 1)
        return ;
    for (int i=0; i<num; i++)
    {
        sql.delete_figure(list.at(row));
        beginRemoveRows(QModelIndex(), row, row+num-1);
        list.removeAt(row);
        endRemoveRows();
    }

}
void QATableFigure::insertRow(int row){
    beginInsertRows(QModelIndex(), row, row);
    list.insert(row, new figure);
    endInsertRows();
}

void QATableFigure::clear_cell(int row, int column){
    figure old = *(list.at(row));
    switch (column)
    {
    case 2:
        this->list.at(row)->set_hight(0);
        break;
    case 3:
        this->list.at(row)->set_point_hight(point());
        break;
    case 4:
        this->list.at(row)->set_point_base(point());
        break;
    }
    sql.change(&old, list.at(row));
}

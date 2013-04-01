#include "model_figure.h"

QATableFigure::QATableFigure(QObject *parent) :
    QAbstractTableModel(parent)
{
    header_data << QString::fromUtf8("Тип фигуры") << QString::fromUtf8("Тип основания")
                << QString::fromUtf8("Высота") << QString::fromUtf8("координаты высоты")
                << QString::fromUtf8("Точки основания");
    for(int i = 0; i < 20; i++){
        figure* it = new figure;
        list.append(it);
    }
}

QATableFigure::QATableFigure()
{

}

//QString
QString vect_to_string(point p1, point p2){
    return QString("(%1,%2,%3), (%4,%5,%6);")
            .arg(p1.x, p1.y,
                 p1.z, p2.x,
                 p2.y, p2.z);
}

QVariant points_to_string(QList <point> lst){
    QString str;
    QList <point>::iterator i;
    for (i = lst.begin(); i!=lst.end(); ++i)
        str+=QString("(%1,%2,%3);").arg((*i).x,(*i).y,(*i).z);
    return str;
}

QList <point> string_to_points(QString str){
    QList <point> lst;
    int i=0;
    while (i<str.length())
    { // format (9,9,9)
        point p;
        i++; // (
        QString tmp;
        tmp.sprintf("%d",&str[i]);
        p.x = tmp.toInt();
        i+= tmp.length();
        i++; // ,
        tmp.sprintf("%d",&str[i]);
        p.y = tmp.toInt();
        i+= tmp.length();
        i++; // ,
        tmp.sprintf("%d",&str[i]);
        p.z = tmp.toInt();
        i+= tmp.length();
        i++; // )
        lst.push_back(p);
    }
    return lst;
}




QVariant QATableFigure::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= list.size())
        return QVariant();
    QString tmp;
    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0)
            return list.at(index.row())->figure_type;
        if (index.column() == 1)
            return list.at(index.row())->base_type;
        if (index.column() == 2)
            return tmp.setNum(list.at(index.row())->hight);
        if (index.column() == 3)
        {
            point p1, p2;
            p1 = list.at(index.row())->point_hight_A;
            p2 = list.at(index.row())->point_hight_B;

            tmp = (vect_to_string(p1, p2));
            return tmp;
        }
        if (index.column() == 4 )
            return points_to_string(list.at(index.row())->points_base);
    }
    return QVariant();
}

bool QATableFigure::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        // записываем данные из каждого столбца
        if (index.column() == 0)
            list.at(index.row())->figure_type = value.toString();
        if (index.column() == 1)
            list.at(index.row())->base_type = value.toString();
        if (index.column() == 2)
            list.at(index.row())->hight = value.toUInt();
        if (index.column() == 3)
        {
            list.at(index.row())->point_hight_A = (string_to_points(value.toString()))[0];
            list.at(index.row())->point_hight_B = (string_to_points(value.toString()))[1];
        }
        if (index.column() == 4)
            list.at(index.row())->points_base = string_to_points(value.toString());
        return true;
    }
    return false;
}

int QATableFigure::rowCount(const QModelIndex &parent) const
{
    return list.size(); // размер списка - это количество строк
}

int QATableFigure::columnCount(const QModelIndex &parent) const
{
    return 5; // 5
}

QVariant QATableFigure::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(role != Qt::DisplayRole)
           return QVariant();
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
       return header_data.at(section); // заголовки столбцов
   }else{
       return QString("%1").arg(section + 1); // возвращаем номера строк
   }
}

Qt::ItemFlags QATableFigure::flags(const QModelIndex &index) const
{
   if (!index.isValid())
        return Qt::ItemIsEnabled;
   return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


























//model_figure::model_figure()
//{
//    this->base_type = "";
//    this->figure_type = "";
//    this->hight = 0;
//    data = QSqlDatabase::addDatabase("QSQLITE");
//    data.setDatabaseName("figures.sqlite");
//    if (!data.open())
//        qDebug() << data.lastError().text();
//    seek._base_type=seek._figure_type=seek._hight
//            =seek._id=seek._points=seek._sites=false;
//}

//void model_figure::refreash(){


//}

#include "model_figure.h"
#include <fstream>

using namespace std;

QATableFigure::QATableFigure()
{
    header_data << QString("Type figure") << QString("Base type")
                << QString("Hight") << QString("Hight posicion")
                << QString("Base points") << QString("Long base sites");
    for(int i = 0; i < 20; i++){
        figure* it = new figure;
        list.append(it);
    }
}
//QString
QString QATableFigure::vect_to_string(const point p1, const point p2){
    QString a1, a2, a3, a4, a5, a6;
    a1.setNum(p1.x);
    a2.setNum(p1.y);
    a3.setNum(p1.z);
    a4.setNum(p2.x);
    a5.setNum(p2.y);
    a6.setNum(p2.z);
    return QString("(%1,%2,%3), (%4,%5,%6);")
            .arg(a1, a2, a3, a4, a5, a6);
}
QString QATableFigure::points_to_string(QList <point> lst){
    QString str;
    QList <point>::iterator i;
    for (i = lst.begin(); i!=lst.end(); ++i)
        str+=QString("(%1,%2,%3);").arg((*i).x,(*i).y,(*i).z);
    return str;
}
QString QATableFigure::list_int_to_string(QList <int> lst){
    QString str="";
    QList <int>::iterator i;
    for (i = lst.begin(); i!=lst.end(); ++i)
        if (i == lst.begin())
            str+=QString("%1").arg(*i);
        else
            str+=QString("-%1").arg(*i);
    return str;
}
QList <point> QATableFigure::string_to_points(const QString str){
    QList <point> lst;
    int i=0;
    while (i<str.length())
    { // format (9,9,9)(9,9,9)(9,9,9)(9,9,9)(9,9,9)(9,9,9)...(9,9,9)
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
QList <int> QATableFigure::string_to_list_int(const QString str){
    QList <int> lst;
    int i=0;
    while (i<str.length())
    { //format 9-9-9-9-9-9-9-9-9-9-9-9-9-9...9
        int p;
        QString tmp;
        tmp.sprintf("%d",&str[i]);
        p = tmp.toInt();
        i+= tmp.length();
        lst.push_back(p);
        i++; // -
    }
    return lst;
}

QVariant QATableFigure::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QString tmp;
    if (index.row() >= list.size())
        return QVariant();
    // for everyone column return value
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
            QString a1, a2, a3, a4, a5, a6;
            a1.setNum(p1.x);
            a2.setNum(p1.y);
            a3.setNum(p1.z);
            a4.setNum(p2.x);
            a5.setNum(p2.y);
            a6.setNum(p2.z);
            return QString("(%1,%2,%3)(%4,%5,%6) ")
                    .arg(a1, a2, a3, a4, a5, a6);
        }
        if (index.column() == 4 )
        {
            QString str("");
            QList <point>::iterator i;
            for (i = (list.at(index.row())->points_base).begin(); i!=(list.at(index.row())->points_base).end(); ++i)
                str+=QString("(%1,%2,%3)").arg((*i).x,(*i).y,(*i).z);
            str.push_back(" ");
            return str;
        }
        if (index.column() == 5 )
        {
            QString str="";
            QList <qint32>::iterator i;
            for (i = (list.at(index.row())->sites).begin(); i!=(list.at(index.row())->sites).end(); ++i)
                if (i == (list.at(index.row())->sites).begin())
                    str+=QString("%1").arg(*i);
                else
                    str+=QString("-%1").arg(*i);
            str+=" ";
            return str;
        }
    }
    return QVariant();
}
bool QATableFigure::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        // read value to everyone column
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
        if (index.column() == 5)
            list.at(index.row())->sites = string_to_list_int(value.toString());
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
    return 5; // 5 column
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

void QATableFigure::read_base_from_file(QString name){
    ifstream input;
    input.open(name.toStdString());
    this->list.clear();
    QList <figure*>::iterator i;
    for (i=list.begin(); input;)
    {
        figure tmp;
        input >> tmp.figure_type.toStdString();
        input >> tmp.base_type.toStdString();
        input >> tmp.hight;
        QString str;
        input >> str.toStdString();
        tmp.point_hight_A = (string_to_points(str))[0];
        tmp.point_hight_B = (string_to_points(str))[1];
        input >> str.toStdString();
        tmp.points_base = string_to_points(str);
        input >> str.toStdString();
        tmp.sites = string_to_list_int(str);
        list.push_back(&tmp);
    }
}
void QATableFigure::write_base_in_file(QString name){
    ofstream out;
    out.open(name.toStdString());
    QList <figure*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i)
    {
        out << (*i)->base_type.toStdString() << " ";
        out << (*i)->figure_type.toStdString() << " ";
        out << (*i)->hight << " ";
        out << "(" << (*i)->point_hight_A.x << "," << (*i)->point_hight_A.y << ")" <<
               "(" << (*i)->point_hight_B.x << "," << (*i)->point_hight_B.y << ")" << " ";
        point p1, p2;
        p1 = (*i)->point_hight_A;
        p2 = (*i)->point_hight_B;
        QString a1, a2, a3, a4, a5, a6;
        a1.setNum(p1.x);
        a2.setNum(p1.y);
        a3.setNum(p1.z);
        a4.setNum(p2.x);
        a5.setNum(p2.y);
        a6.setNum(p2.z);
        out << QString("(%1,%2,%3)(%4,%5,%6) ")
                .arg(a1, a2, a3, a4, a5, a6).toStdString();
        QString str("");
        QList <point>::iterator j;
        for (j = ((*i)->points_base).begin(); j!=(*i)->points_base.end(); ++j)
            str+=QString("(%1,%2,%3)").arg((*j).x,(*j).y,(*j).z);
        str+=" ";
        out << str.toStdString();
        str="";
        QList <qint32>::iterator k;
        for (k = (*i)->sites.begin(); k!=(*i)->sites.end(); ++k)
            if (k == (*i)->sites.begin())
                str+=QString("%1").arg(*k);
            else
                str+=QString("-%1").arg(*k);
        str+="\n";
        out << str.toStdString();
    }
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

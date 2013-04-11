#include "model_figure.h"
#include <fstream>

using namespace std;

const int start_size_table = 1;

bool operator ==(point &p1, point &p2){
    return p1.x==p2.x && p1.y==p2.y && p1.z==p2.z;
}

QATableFigure::QATableFigure()
{
    header_data << QString("Figure type") << QString("Base type")
                << QString("Hight") << QString("Hight posicion")
                << QString("Base points") << QString("Long base sites");
    for(int i = 0; i < start_size_table; i++)
        list.append(new figure);
}

QList <point> QATableFigure::string_to_points(const QString str){
    QList <point> lst;
    int i=0, j;
    QString qstmp;
    while (i<str.length())
    { // format (9,9,9)(9,9,9)(9,9,9)(9,9,9)(9,9,9)(9,9,9)...(9,9,9)
        point p;
        i++; // (
        char tmp[100];
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='-') ; i++, j++)
            tmp[j]=str[i].toAscii();
        tmp[j]=0;
        qstmp = tmp;
        p.x = qstmp.toInt();
        i++; // ,
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='-') ; i++, j++)
            tmp[j]=str[i].toAscii();
        tmp[j]=0;
        qstmp = tmp;
        p.y = qstmp.toInt();
        i++; // ,
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='-') ; i++, j++)
            tmp[j]=str[i].toAscii();
        tmp[j]=0;
        qstmp = tmp;
        p.z = qstmp.toInt();
        i++; // )
        lst.push_back(p);
    }
    return lst;
}
QList <int> QATableFigure::string_to_list_int(const QString str){
    QList <int> lst;
    int i=0, j;
    QString qstmp;
    while (i<str.length())
    { //format 9,9,9...9
        char tmp[100];
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit()) ; i++, j++)
            tmp[j]=str[i].toAscii();
        tmp[j]=0;
        qstmp = tmp;
        lst.push_back(qstmp.toInt());
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
        {// NEED CALC!!
         //   convex equilateral
         //   convex unequilateral
         //   unconvex
            return list.at(index.row())->base_type;
        }
        if (index.column() == 2)
            return tmp.setNum(list.at(index.row())->hight);
        if (index.column() == 3)
        {// defoult set first point base
            point p1;
            p1 = list.at(index.row())->point_hight_A;
            QString a1, a2, a3;
            a1.setNum(p1.x);
            a2.setNum(p1.y);
            a3.setNum(p1.z);
            return QString("(%1,%2,%3)")
                    .arg(a1, a2, a3);
        }
        if (index.column() == 4 )
        {
            QString str("");
            QList <point>::iterator i;
            for (i = (list.at(index.row())->points_base).begin(); i!=(list.at(index.row())->points_base).end(); ++i)
            {
               QString a1, a2, a3;
               a1.setNum((*i).x);
               a2.setNum((*i).y);
               a3.setNum((*i).z);
               str.push_back(QString("(%1,%2,%3)").arg(a1,a2,a3));
            }
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
                    str+=QString(",%1").arg(*i);
            str+=" ";
            return str;
        }
    }
    return QVariant();
}
bool QATableFigure::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        if (index.row() == list.size()-1)
        {
            beginInsertRows(QModelIndex(), list.size(), list.size());
            list.append(new figure);
            endInsertRows();
        }
        // read value to everyone column
        if (index.column() == 0)
            list.at(index.row())->figure_type = value.toString();
        if (index.column() == 1)
            list.at(index.row())->base_type = value.toString();
        if (index.column() == 2)
            list.at(index.row())->hight = value.toUInt();
        if (index.column() == 3)
         // defoult set first point base
            list.at(index.row())->point_hight_A = (string_to_points(value.toString()))[0];
        if (index.column() == 4)
        {
            list.at(index.row())->points_base = string_to_points(value.toString());
            // calculate sites
            QList <point>::iterator i;
            list.at(index.row())->sites.clear();
            for (i=list.at(index.row())->points_base.begin(); i != list.at(index.row())->points_base.end(); ++i)
            {
                point p1, p2;
                p1 = *i;
                if ((*i) == *(list.at(index.row())->points_base.end()-1))
                    p2 = list.at(index.row())->points_base.takeFirst();
                else
                    p2 = *(i+1);
                int long_site = qSqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
                list.at(index.row())->sites.push_back(long_site);
            }
        }
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
        out << "(" << (*i)->point_hight_A.x << "," << (*i)->point_hight_A.y << ")" << " ";
        point p1;
        p1 = (*i)->point_hight_A;
        QString a1, a2, a3;
        a1.setNum(p1.x);
        a2.setNum(p1.y);
        a3.setNum(p1.z);
        out << QString("(%1,%2,%3)")
                .arg(a1, a2, a3).toStdString();
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

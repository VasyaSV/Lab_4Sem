#include "model_figure.h"
#include <fstream>

using namespace std;

bool operator ==(point &p1, point &p2){
    for (int i=0; i<demention; i++)
        if (p1.k[i] != p2.k[i])
            return 0;
    return 1;
}

bool in_one_plane(const QList <point> l){ // Function work in 3D only, for more need giperkomplane
    if (l.size()<=3)
        return 1;
    QList <point>::const_iterator i;
    i=l.begin();
    int x1, x2, x3, y1, y2, y3, z1, z2, z3;
    x1 = (*i).k[0];
    y1 = (*i).k[1];
    z1 = (*i).k[2];
    ++i;
    x2 = (*i).k[0];
    y2 = (*i).k[1];
    z2 = (*i).k[2];
    ++i;
    x3 = (*i).k[0];
    y3 = (*i).k[1];
    z3 = (*i).k[2];
    ++i;
    for (; i!=l.end(); ++i)
    {
        int x= (*i).k[0],
            y= (*i).k[1],
            z= (*i).k[2];
        // not one plane // plane detarminate
        if ((x-x1)*(y2-y1)*(z3-z1)+(y-y1)*(z2-z1)*(x3-x1)+(z-z1)*(x2-x1)*(y3-y1)
                - (x3-x1)*(y2-y1)*(z-z1) - (y3-y1)*(z2-z1)*(x-x1) - (z3-z1)*(x2-x1)*(y-y1))
            return 0;
    }
    return 1;
}

bool figure_is_equilateral(const QList <double> l){
    if (l.size() < 3)
        return 1;
    for (QList <double>::const_iterator i = l.begin()+1; i!=l.end() ; ++i)
        if ((*i) != *(i-1))
            return 0;
    return 1;
}

class proection2d{
public:
    class point2d{
    public:
        int x;
        int y;
        point2d(){ x = y = 0;}
        point2d(int x, int y)
        {
            this->x=x;
            this->y=y;
        }
    };
    QList <point2d> l2d;
    proection2d(const QList <point> l3d, char fO){ // fO - 1 is Oxy, 2 is Oyz, 3 is Oxz projection
        QList <point>::const_iterator i;
        for (i=l3d.begin(); i!=l3d.end(); ++i)
            if (fO==1)
                l2d.push_back(point2d((*i).k[0],(*i).k[1]));
            else if (fO==2)
                l2d.push_back(point2d((*i).k[1],(*i).k[2]));
            else if (fO==3)
                l2d.push_back(point2d((*i).k[0],(*i).k[2]));
    }

    int d_sign(int p1, int p2){
        if (p1==p2)
            return 0;
        if (p1>p2)
            return 1;
        return -1;
    }

    int vect_sign(point2d p1, point2d p2, point2d p){
    // -1 p is lefter vector (p1, p2)
    // 1 p is righter vector (p1, p2)
    // 0 on line (p1, p2)
        if (p1.x==p2.x)
        {
            int d;
                 d   = d_sign(p.x, p1.x)*(-1 * d_sign(p1.y, p2.y));
            return d; // (-1 * d_sign(p1.y, p2.y)) change signed if p1.y<p2.y
        }
        double k=abs((p2.y-p1.y)/(p2.x-p1.x)); // tg alfa
        double c = p1.y - k*p1.x;

        int d;
             d = d_sign(k*p.x+c, p.y)*(-1*d_sign(p1.x, p2.x));
        return d;
    }
    bool is_convex(){
        if (l2d.size()<4)
            return 1;
        QList <point2d>::iterator i, j;
        point2d last = *(l2d.end()-1);
        char now_sign = 0;
        for (i=l2d.begin(); i!=l2d.end(); last=*i, i++)
            for (j=l2d.begin(); j!=l2d.end(); j++)
                if (i != j)
                    if (now_sign == 0)
                        now_sign = vect_sign(last, *i, *j);
                    else
                        if (now_sign != vect_sign(last, *i, *j) && now_sign && vect_sign(last, *i, *j))
                            return 0;
        return 1;
    }
};




bool figure_is_convex(const QList <point> l){
    if (l.size()<3)
        return 1;
    proection2d *d2p;
    bool z_change=0;
    for (QList <point>::const_iterator i=l.begin()+1; i!=l.end(); ++i)
        if ((*i).k[2]!=(*(i-1)).k[2])
            z_change = 1;
    if (!z_change)
        d2p=new proection2d(l, 1);
    else
        d2p=new proection2d(l, 2);
    return d2p->is_convex();
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
        for (int k=0; k<demention; k++){
            for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='-') ; i++, j++)
                tmp[j]=str[i].toAscii();
            tmp[j]=0;
            qstmp = tmp;
            p.k[k] = qstmp.toInt();
            i++; // , || )
        }
        lst.push_back(p);
    }
    return lst;
}
QList <double> QATableFigure::string_to_list_double(const QString str){
    QList <double> lst;
    int i=0, j;
    QString qstmp;
    while (i<str.length())
    { //format 9.9_9.9_9.9...9.9
        char tmp[100];
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='.') ; i++, j++)
            tmp[j]=str[i].toAscii();
        tmp[j]=0;
        qstmp = tmp;
        lst.push_back(qstmp.toInt());
        i++; // _ || /0
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
            point p = list.at(index.row())->point_hight_A;
            QString str("(");
            for (int k=0; k<demention; k++){
                QString tmp;
                tmp.setNum(p.k[k]);
                str += tmp + ",";
            }
            str[str.length()-1]=')';
            return str;
        }
        if (index.column() == 4 )
        {
            QString str("");
            QList <point>::iterator i;
            for (i = (list.at(index.row())->points_base).begin(); i!=(list.at(index.row())->points_base).end(); ++i)
            {
                QString pstr("(");
                for (int k=0; k<demention; k++){
                    QString tmp;
                    tmp.setNum((*i).k[k]);
                    pstr += tmp + ",";
                }
                pstr[pstr.length()-1]=')';
                str.push_back(pstr);
            }
            return str;
        }
        if (index.column() == 5 )
        {
            QString str="";
            QList <double>::iterator i;
            for (i = (list.at(index.row())->sites).begin(); i!=(list.at(index.row())->sites).end(); ++i)
                if (i == (list.at(index.row())->sites).begin())
                    str+=QString("%1").arg(*i);
                else
                    str+=QString("_%1").arg(*i);
            str+=" ";
            return str;
        }
    }
    return QVariant();
}
bool QATableFigure::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
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
        {
         // defoult set first point base
            point p;
            p = list.at(index.row())->point_hight_A;

            if (list.at(index.row())->points_base.size()>2){
            QList <point>::iterator i;
            i=list.at(index.row())->points_base.begin();
            int x1, x2, x3, y1, y2, y3, z1, z2, z3;
            x1 = (*i).k[0];
            y1 = (*i).k[1];
            z1 = (*i).k[2];
            ++i;
            x2 = (*i).k[0];
            y2 = (*i).k[1];
            z2 = (*i).k[2];
            ++i;
            x3 = (*i).k[0];
            y3 = (*i).k[1];
            z3 = (*i).k[2];
            int x= p.k[0],
                y= p.k[1],
                z= p.k[2];
                // not one plane // plane detarminate
            if ((x-x1)*(y2-y1)*(z3-z1)+(y-y1)*(z2-z1)*(x3-x1)+(z-z1)*(x2-x1)*(y3-y1)
                    - (x3-x1)*(y2-y1)*(z-z1) - (y3-y1)*(z2-z1)*(x-x1) - (z3-z1)*(x2-x1)*(y-y1))
                list.at(index.row())->point_hight_A = list.at(index.row())->points_base.at(0);
                return true;
            }
            list.at(index.row())->point_hight_A = (string_to_points(value.toString()))[0];

        }
        if (index.column() == 4)
        {
            list.at(index.row())->points_base = string_to_points(value.toString());
            // calculate sites
            QList <point>::iterator i; // calculate length site
            list.at(index.row())->sites.clear();
            for (i=list.at(index.row())->points_base.begin(); i != list.at(index.row())->points_base.end(); ++i)
            {
                point p1, p2;
                p1 = *i;
                if ((*i) == *(list.at(index.row())->points_base.end()-1))
                    p2 = list.at(index.row())->points_base.at(0);
                else
                    p2 = *(i+1);

                double sum_sqr_de_komponent(0); // summ squear delta komponent
                for (int k=0; k<demention; k++)
                    sum_sqr_de_komponent += (p1.k[k] - p2.k[k])*(p1.k[k] - p2.k[k]);
                double long_site = qSqrt(sum_sqr_de_komponent);
                list.at(index.row())->sites.push_back(long_site);
            }
             //   convex equilateral
             //   convex
             //   unconvex
            QString type("");
            if (!in_one_plane(list.at(index.row())->points_base) || list.at(index.row())->points_base.size()<1)
            {
                list.at(index.row())->base_type = "incorect";
                return true;
            }
            if (!figure_is_convex(list.at(index.row())->points_base))
            {
                list.at(index.row())->base_type = "unconvex";
                return true;
            }
                type = "convex";
                if (figure_is_equilateral(list.at(index.row())->sites))
                    switch (list.at(index.row())->points_base.size())
                    {
                    case 1:
                        list.at(index.row())->base_type = "point";
                        return true;
                    case 2:
                        list.at(index.row())->base_type = "line";
                        return true;
                    case 3:
                        list.at(index.row())->base_type = "right triangle";
                        return true;
                    case 4:
                        list.at(index.row())->base_type = "squear";
                        return true;
                    default:
                        type += " equilateral";
                    }
                list.at(index.row())->base_type = type;
                return true;
            }
        if (index.column() == 5)
            list.at(index.row())->sites = string_to_list_double(value.toString());
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

//void QATableFigure::read_base_from_file(QString name){
//    ifstream input;
//    input.open(name.toStdString());
//    this->list.clear();
//    QList <figure*>::iterator i;
//    for (i=list.begin(); input;)
//    {
//        figure tmp;
//        input >> tmp.figure_type.toStdString();
//        input >> tmp.base_type.toStdString();
//        input >> tmp.hight;
//        QString str;
//        input >> str.toStdString();
//        tmp.point_hight_A = (string_to_points(str))[0];
//        input >> str.toStdString();
//        tmp.points_base = string_to_points(str);
//        input >> str.toStdString();
//        tmp.sites = string_to_list_double(str);
//        list.push_back(&tmp);
//    }
//}
//void QATableFigure::write_base_in_file(QString name){
//    ofstream out;
//    out.open(name.toStdString());
//    QList <figure*>::iterator i;
//    for (i = list.begin(); i != list.end(); ++i)
//    {
//        out << (*i)->base_type.toStdString() << " ";
//        out << (*i)->figure_type.toStdString() << " ";
//        out << (*i)->hight << " ";
//        out << "(" << (*i)->point_hight_A.x << "," << (*i)->point_hight_A.y << ")" << " ";
//        point p1;
//        p1 = (*i)->point_hight_A;
//        QString a1, a2, a3;
//        a1.setNum(p1.x);
//        a2.setNum(p1.y);
//        a3.setNum(p1.z);
//        out << QString("(%1,%2,%3)")
//                .arg(a1, a2, a3).toStdString();
//        QString str("");
//        QList <point>::iterator j;
//        for (j = ((*i)->points_base).begin(); j!=(*i)->points_base.end(); ++j)
//            str+=QString("(%1,%2,%3)").arg((*j).x,(*j).y,(*j).z);
//        str+=" ";
//        out << str.toStdString();
//        str="";
//        QList <double>::iterator k;
//        for (k = (*i)->sites.begin(); k!=(*i)->sites.end(); ++k)
//            if (k == (*i)->sites.begin())
//                str+=QString("%1").arg(*k);
//            else
//                str+=QString("-%1").arg(*k);
//        str+="\n";
//        out << str.toStdString();
//    }
//}



























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

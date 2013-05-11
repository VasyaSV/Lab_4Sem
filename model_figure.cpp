#include "model_figure.h"

using namespace std;

void  QATableFigure::set_sql_name(QString name){
    sql_name = name;
}

void QATableFigure::sql(bool f){
    f_sql = f;
    if (!f)
        return;
    data_base.setDatabaseName(sql_name);
    if (!data_base.open()) {
            qDebug() << "Not open SQlite";
            return;
        }
    if (!a_query.exec("CREATE TABLE figures ("
                      "figure_type VARCHAR(255), "
                      "base_type VARCHAR(255), "
                      "hight integer,"
                      "hight_point VARCHAR(255), "
                      "base_points VARCHAR(255)"
                      ");")) {
        qDebug() << "Not exec table";
    }

}

void QATableFigure::refreash(){
    QList <figure *>::iterator i;
    for (i=list.begin(); i!=list.end() ;i++)
    {
        calc_base_type(*i);
        point p;
        p = (*i)->point_hight_A;
        if ((*i)->points_base.size()>2){
            QList <point>::iterator j;
            j=(*i)->points_base.begin();
            if (!point_in_one_plane(*(j), *(j+1), *(j+2), p)) // defoult set first point base
                p  = *j;
        }
        (*i)->point_hight_A = p;
        calc_sites(*i);
    }
}
QATableFigure::QATableFigure()
{
    data_base = QSqlDatabase::addDatabase("QSQLITE");
    sql_name = DEFOULT_SQL_OUT;
    header_data << QString("Figure type") << QString("Base type")
                << QString("Hight") << QString("Hight posicion")
                << QString("Base points") << QString("Long base sites");
    for(int i = 0; i < start_size_table; i++)
        list.append(new figure);
}

bool QATableFigure::point_in_one_plane(const QList <point> l){ // Function work in 3D only, for more need giperkomplane
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
bool QATableFigure::figure_is_equilateral(const QList <double> l){
    if (l.size() < 3)
        return 1;
    for (QList <double>::const_iterator i = l.begin()+1; i!=l.end() ; ++i)
        if ((*i) != *(i-1))
            return 0;
    return 1;
}
bool QATableFigure::figure_is_convex(const QList <point> l){
    if (l.size()<3)
        return 1;
    projection2d *d2p;
    bool z_change=0;
    for (QList <point>::const_iterator i=l.begin()+1; i!=l.end(); ++i)
        if ((*i).k[2]!=(*(i-1)).k[2])
            z_change = 1;
    if (!z_change)
        d2p=new projection2d(l, 1);
    else
        d2p=new projection2d(l, 2);
    return d2p->is_convex();
}

QList <point> QATableFigure::string_to_points(const QString str) const{
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
                tmp[j]= str[i].unicode();
            tmp[j]=0;
            qstmp = tmp;
            p.k[k] = qstmp.toInt();
            i++; // , || )
        }
        lst.push_back(p);
    }
    return lst;
}
QList <double> QATableFigure::string_to_list_double(const QString str) const{
    QList <double> lst;
    int i=0, j;
    QString qstmp;
    while (i<str.length())
    { //format 9.9_9.9_9.9...9.9
        char tmp[100];
        for (j = 0; i<str.length() && i<100 && (str[i].isDigit() || str[i]=='.') ; i++, j++)
            tmp[j]=str[i].unicode();
        tmp[j]=0;
        qstmp = tmp;
        lst.push_back(qstmp.toInt());
        i++; // _ || /0
    }
    return lst;
}

QString QATableFigure::hight_to_QStr(const QModelIndex &index) const{
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
QString QATableFigure::sites_list_to_QStr(const QModelIndex &index) const{
    QString str="";
    QList <double>::iterator i;
    for (i = (list.at(index.row())->sites).begin(); i!=(list.at(index.row())->sites).end(); ++i)
        if (i == (list.at(index.row())->sites).begin())
            str+=QString("%1").arg(*i);
        else
            str+=QString("_%1").arg(*i);
    if (!str.length())
        return defoult;
    return str;
}
QString QATableFigure::points_base_to_QStr(const QModelIndex &index) const
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
    if (!str.length())
        return defoult;
    return str;
}
QString QATableFigure::hight_to_QStr(figure *f) const{
    point p = f->point_hight_A;
    QString str("(");
    for (int k=0; k<demention; k++){
        QString tmp;
        tmp.setNum(p.k[k]);
        str += tmp + ",";
    }
    str[str.length()-1]=')';
    return str;
}
QString QATableFigure::sites_list_to_QStr(figure *f) const{
    QString str="";
    QList <double>::iterator i;
    for (i = (f->sites).begin(); i!=(f->sites).end(); ++i)
        if (i == (f->sites).begin())
            str+=QString("%1").arg(*i);
        else
            str+=QString("_%1").arg(*i);
    if (!str.length())
        return defoult;
    return str;
}
QString QATableFigure::points_base_to_QStr(figure *f) const
{
    QString str("");
    QList <point>::iterator i;
    for (i = (f->points_base).begin(); i!=(f->points_base).end(); ++i)
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
    if (!str.length())
        return defoult;
    return str;
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
            return hight_to_QStr(index);
        if (index.column() == 4 )
            return points_base_to_QStr(index);
        if (index.column() == 5 )
            return sites_list_to_QStr(index);
    }
    return QVariant();
}
void QATableFigure::calc_sites(const QModelIndex &index)
{
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
        double long_site = sqrt(sum_sqr_de_komponent);
        list.at(index.row())->sites.push_back(long_site);
    }
}
void QATableFigure::calc_base_type(const QModelIndex &index)
{
    //   convex equilateral
    //   convex
    //   unconvex
   QString type("");
   if (!point_in_one_plane(list.at(index.row())->points_base) || list.at(index.row())->points_base.size()<1)
   {
       list.at(index.row())->base_type = "incorect";
       return;
   }
   if (!figure_is_convex(list.at(index.row())->points_base))
   {
       list.at(index.row())->base_type = "unconvex";
       return;
   }
   type = "convex";
   if (figure_is_equilateral(list.at(index.row())->sites))
       switch (list.at(index.row())->points_base.size())
       {
       case 1:
           list.at(index.row())->base_type = "point";
           return;
       case 2:
           list.at(index.row())->base_type = "line";
           return;
       case 3:
           list.at(index.row())->base_type = "right_triangle";
           return;
       case 4:
           list.at(index.row())->base_type = "squear";
           return;
       default:
           type += "_equilateral";
       }
   list.at(index.row())->base_type = type;
}


void QATableFigure::calc_sites(figure* f)
{
    QList <point>::iterator i; // calculate length site
    f->sites.clear();
    for (i=f->points_base.begin(); i != f->points_base.end(); ++i)
    {
        point p1, p2;
        p1 = *i;
        if ((*i) == *(f->points_base.end()-1))
            p2 = f->points_base.at(0);
        else
            p2 = *(i+1);

        double sum_sqr_de_komponent(0); // summ squear delta komponent
        for (int k=0; k<demention; k++)
            sum_sqr_de_komponent += (p1.k[k] - p2.k[k])*(p1.k[k] - p2.k[k]);
        double long_site = sqrt(sum_sqr_de_komponent);
        f->sites.push_back(long_site);
    }
}
void QATableFigure::calc_base_type(figure* f)
{
    //   convex equilateral
    //   convex
    //   unconvex
   QString type("");
   if (!point_in_one_plane(f->points_base) || f->points_base.size()<1)
   {
       f->base_type = "incorect";
       return;
   }
   if (!figure_is_convex(f->points_base))
   {
       f->base_type = "unconvex";
       return;
   }
   type = "convex";
   if (figure_is_equilateral(f->sites))
       switch (f->points_base.size())
       {
       case 1:
           f->base_type = "point";
           return;
       case 2:
           f->base_type = "line";
           return;
       case 3:
           f->base_type = "right_triangle";
           return;
       case 4:
           f->base_type = "squear";
           return;
       default:
           type += "_equilateral";
       }
   f->base_type = type;
}


bool QATableFigure::point_in_one_plane(point p1, point p2, point p3, point p) // p in plane (p1,p2,p3)?
{
    int x1, x2, x3, y1, y2, y3, z1, z2, z3, x, y, z;
    x1 = p1.k[0];
    y1 = p1.k[1];
    z1 = p1.k[2];
    x2 = p2.k[0];
    y2 = p2.k[1];
    z2 = p2.k[2];
    x3 = p3.k[0];
    y3 = p3.k[1];
    z3 = p3.k[2];
    x= p.k[0];
    y= p.k[1];
    z= p.k[2];
        // not one plane // plane detarminate
    if ((x-x1)*(y2-y1)*(z3-z1)+(y-y1)*(z2-z1)*(x3-x1)+(z-z1)*(x2-x1)*(y3-y1)
            - (x3-x1)*(y2-y1)*(z-z1) - (y3-y1)*(z2-z1)*(x-x1) - (z3-z1)*(x2-x1)*(y-y1))
        return 0;
    return 1;
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
            list.at(index.row())->point_hight_A = (string_to_points(value.toString()))[0];
        if (index.column() == 4)
            list.at(index.row())->points_base = string_to_points(value.toString());
        if (index.column() == 5)
            list.at(index.row())->sites = string_to_list_double(value.toString());
        refreash();
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
    qDebug("%s",name.toStdString());
    QFile file(name);
    figure *tmp;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    if (in.atEnd())
        return;
    while(!in.atEnd())
    {
        tmp=new figure();
        char str[500];
        str[0]=0;
        in >> str;
        if (in.atEnd())
            break;
        str[strlen(str)-1]=0;
        if (in.atEnd())
            break;
        tmp->figure_type = str;
//        in >> str;
//        if (in.atEnd())
//            break;
//        str[strlen(str)-1]=0;
//        tmp->base_type = str;
        in >> tmp->hight;
        if (in.atEnd())
            break;
        in >> str; // _
        if (in.atEnd())
            break;
        in >> str;
        if (in.atEnd())
            break;
        str[strlen(str)-1]=0;
        tmp->point_hight_A = (string_to_points(str))[0];
        in >> str;
        str[strlen(str)-1]=0;
        if (in.atEnd())
            break;
        tmp->points_base = string_to_points(str);
//        in >> str;
//        if (in.atEnd())
//            break;
//        str[strlen(str)-1]=0;
//        tmp->sites = string_to_list_double(str);
        beginInsertRows(QModelIndex(), list.size(), list.size());
        list.append(tmp);
        endInsertRows();
    }
    delete tmp;
    file.close();
}
void QATableFigure::write_base_in_file(QString name){
    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QList <figure*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i)
    {
        out << (*i)->figure_type << "_ ";
        //out << (*i)->base_type << "_ ";
        out << (*i)->hight << "_ ";
        out << hight_to_QStr(*i) << "_ ";
        out << points_base_to_QStr(*i) << "_ ";
        //out << sites_list_to_QStr(*i) << "_ \n";
    }
    file.close();
}

void QATableFigure::removeRow(int row, int num){
    if (list.size() < 1 || num < 1)
        return ;
    beginRemoveRows(QModelIndex(), row, row+num-1);
    for (int i=0; i<num; i++)
        list.removeAt(row);
    endRemoveRows();
}
void QATableFigure::insertRow(int row){
    beginInsertRows(QModelIndex(), row, row);
    list.insert(row, new figure);
    endInsertRows();
}

void QATableFigure::clear_cell(int row, int column){
    switch (column)
    {
    case 2:
        this->list.at(row)->hight = 0;
        break;
    case 3:
        this->list.at(row)->point_hight_A = point();
        break;
    case 4:
        this->list.at(row)->points_base = string_to_points("(0,0,0)");
        break;
    }
}


#include "model_figure.h"

model_figure::model_figure()
{
    this->base_type = "";
    this->figure_type = "";
    this->hight = 0;
    data = QSqlDatabase::addDatabase("QSQLITE");
    data.setDatabaseName("figures.sqlite");
    if (!data.open())
        qDebug() << data.lastError().text();
    seek._base_type=seek._figure_type=seek._hight
            =seek._id=seek._points=seek._sites=false;
}

void model_figure::refreash(){


}

#include "main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    table_view = new QTableView;
    model = new QATableFigure;
    table_view->setItemDelegate(new TableDelegate);
    table_view->setModel(model);
    //QHBoxLayout lo;
    //lo.addWidget(table_view);
    doooocckk.layout()->addWidget(table_view);
    this->addDockWidget(Qt::LeftDockWidgetArea, &doooocckk);
}

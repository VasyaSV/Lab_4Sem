#include "main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    table_view = new QTableView;
    model = new QATableFigure;
    table_view->setItemDelegate(new TableDelegate);
    table_view->setModel(model);
    dcw_table_view = new QDockWidget();
    dcw_table_view->layout()->addWidget(table_view);
    this->addDockWidget(Qt::LeftDockWidgetArea, dcw_table_view);
}

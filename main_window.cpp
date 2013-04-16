#include "main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    table_view = new QTableView;
    tdelegate = new TableDelegate;
    model = new QATableFigure;
    table_view->setItemDelegate(tdelegate);
    table_view->setModel(model);
    dcw_table_view = new QDockWidget();
    dcw_table_view->layout()->addWidget(table_view);
    this->addDockWidget(Qt::LeftDockWidgetArea, dcw_table_view);
    QObject::connect(this, SIGNAL(clear_cell(int,int)), model, SLOT(clear_cell(int,int)));
    QObject::connect(this, SIGNAL(removeRow(int,int)), model, SLOT(removeRow(int,int)));
}

void main_window::keyPressEvent(QKeyEvent *ev){
    if (ev->key() == Qt::Key_Delete)
    {
        int n = table_view->selectionModel()->selectedIndexes().count();
        for( int i = 0; i < n; i++)
            emit clear_cell(table_view->selectionModel()->selectedIndexes().at(i).row(),
                            table_view->selectionModel()->selectedIndexes().at(i).column());
        n = table_view->selectionModel()->selectedRows().count();
        if (n)
            emit removeRow(table_view->selectionModel()->selectedRows().at(0).row(), n);
        table_view->clearSelection();
        return;
    }
    return;
}

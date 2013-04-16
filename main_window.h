#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QModelIndexList>
#include "model_figure.h"
#include "control_dialog.h"

using namespace std;

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    QTableView* table_view;
    TableDelegate *tdelegate;
    QATableFigure* model;
    QDockWidget *dcw_table_view; // xz why, but now i havan't fantasy
    explicit main_window(QWidget *parent = 0);
    bool del_cliced(QEvent*);
    void keyPressEvent(QKeyEvent *ev);
signals:
    void clear_cell(int row, int column);
    void removeRow(int row, int num);
    void del_pressed();
};

#endif // MAIN_WINDOW_H

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QModelIndexList>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include "model_figure.h"
#include "control_dialog.h"
#include "view_3d.h"

using namespace std;

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    QTableView* table_view;
    TableDelegate *tdelegate;
    QATableFigure* model;
    QDockWidget *dcw_table_view;
    QDockWidget *dcw_3d_tool;
    QMenuBar *menu_bar;
    QAction *file_new;
    QAction *file_open;
    QAction *file_save;
    QAction *quit;
    QAction *about;
    QAction *table;
    QAction *window_3d;

    Scene3D *scene3d; // создаём виджет класса Scene3D
    //view_3d *v3d;
    //QAction *delete_row;
    //QAction *add_row;
    //QAction *up_row;
    //QAction *down_row;
    //QAction *copy
    //QAction *paste
    //QAction *i_dont_know_what_all_else_matters

    void add_menu_bar(QWidget *parent);
    void add_dock_widgets(QWidget *parent);
    void cultivate_conects();

    main_window(QWidget *parent = 0);
    bool del_cliced(QEvent*);
    void keyPressEvent(QKeyEvent *ev);
signals:
    void clear_cell(int row, int column);
    void removeRow(int row, int num);
    void del_pressed();
    void fileSave(QString);
    void fileOpen(QString);
    void insertRow(int);
public slots:
    void fileSave_clicked();
    void fileOpen_clicked();
    void fileNew_clicked();
    void setVisible_3d(bool);
    void setVisible_table(bool);
};

#endif // MAIN_WINDOW_H

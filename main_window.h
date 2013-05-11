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
#include <QDrag>
#include "model_figure.h"
#include "control_dialog.h"
#include "view_3d.h"
#include "Constants.h"

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
    QFileDialog *file_dialog;
    Scene3D *scene3d; // создаём виджет класса Scene3D

    void add_menu_bar(QWidget *parent);
    void add_dock_widgets(QWidget *parent);
    void cultivate_conects();

    main_window(QWidget *parent = 0);
    bool del_cliced(QEvent*);
    void keyPressEvent(QKeyEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    //void dragMoveEvent(QDragMoveEvent *ev);
    void dropEvent(QDropEvent *ev);
signals:
    void sql(bool);
    void recolculat_model();
    void clear_cell(int row, int column);
    void removeRow(int row, int num);
    void del_pressed();
    void fileSave(QString);
    void fileOpen(QString);
    void insertRow(int);
public slots:
    void tableSelectionChanged();
    void fileSave_clicked();
    void fileOpen_clicked();
    void fileNew_clicked();
    void about_clicked();
    void setVisible_3d(bool);
    void setVisible_table(bool);
    void add_after();
    void add_before();
    void add_end();
};

#endif // MAIN_WINDOW_H

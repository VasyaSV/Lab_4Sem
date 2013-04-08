#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QDockWidget>
#include <QHBoxLayout>
#include "model_figure.h"
#include "control_dialog.h"

using namespace std;

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    QTableView* table_view;
    QATableFigure* model;
    QDockWidget doooocckk; // xz why, but now i havan't fantasy
    explicit main_window(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MAIN_WINDOW_H

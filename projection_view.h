#ifndef PROJECTION_VIEW_H
#define PROJECTION_VIEW_H

#include <QGraphicsItem>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QDockWidget>
#include <QLayout>
#include <QCursor>
#include <QGraphicsLineItem>
#include <QComboBox>
#include <QMouseEvent>
#include <QLabel>
#include <QTimer>
#include "figure.h"
#include "projection2d.h"

class projection_view : public QDockWidget
{
    Q_OBJECT
    qreal sx, sy;
    figure *cur_figure;
    projection2d cur_projection;
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;
    QComboBox *project_on;
   // QPoint ptr_mouse_pos; // координата указателя мыши
    QLabel *pos_x_y_z;
    int proj_type;
    int changing_point;
    point2d h; // hight
    //bool f_change;
    QTimer t;
public:
    projection_view(QWidget *parent=0);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* pe); // нажатие клавиши мыши
    void mouseReleaseEvent(QMouseEvent* pe); // отжатие клавиши мыши
    void mouseMoveEvent(QMouseEvent* pe);
public slots:
    void set_cur_figure(figure*);
private slots:
    void proj_calc(int);
signals:
    void refreash(figure*);
};

#endif // PROJECTION_VIEW_H

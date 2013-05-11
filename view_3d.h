#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QEvent>
#include <math.h>
#include "figure.h"
#include "Constants.h"

class Scene3D : public QGLWidget
{
    Q_OBJECT
    GLfloat VertexArray[60][3]; // декларируем массив вершин
    GLfloat ColorArray[60][3];  // декларируем массив цветов вершин
    GLubyte IndexArray[300][3];  // декларируем массив индексов вершин
      figure *cur_figure;
      point h;
      QColor back_grount_color;

      GLfloat xRot; // переменная хранит угол поворота вокруг оси X
      GLfloat yRot; // переменная хранит угол поворота вокруг оси Y
      GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
      GLfloat zTra; // переменная хранит величину трансляции оси Z
      GLfloat nSca; // переменная отвечает за масштабирование объекта

      QPoint ptrMousePosition; // координата указателя мыши

      void scale_plus();     // приблизить сцену
      void scale_minus();    // удалиться от сцены
      void rotate_up();      // повернуть сцену вверх
      void rotate_down();    // повернуть сцену вниз
      void rotate_left();    // повернуть сцену влево
      void rotate_right();   // повернуть сцену вправо
      void translate_down(); // транслировать сцену вниз
      void translate_up();   // транслировать сцену вверх
      void defaultScene();   // наблюдение сцены по умолчанию

      void drawAxis();       // построить оси координат

      void getVertexArray(); // определить массив вершин
      void getColorArray();  // определить массив цветов вершин
      void getIndexArray();  // определить массив индексов вершин
      void drawFigure();     // построить фигуру

   protected:
      void initializeGL();
      void resizeGL(int nWidth, int nHeight);
      void paintGL();

      void mousePressEvent(QMouseEvent* pe);
      void mouseMoveEvent(QMouseEvent* pe);
      void mouseReleaseEvent(QMouseEvent* pe);
      void wheelEvent(QWheelEvent* pe);
      void keyPressEvent(QKeyEvent* pe);

   public:
      Scene3D(QWidget* parent = 0);
   public slots:
      void set_figure(figure*);
};
#endif

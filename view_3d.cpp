
#include "view_3d.h"

void Scene3D::set_figure(figure* f){
    if (f->get_base_type_to_QStr() != INCORECT
            && f->get_base_type_to_QStr() != UNCONVEX
            && (f->get_figure_type_to_QStr() == PIRAMID || f->get_figure_type_to_QStr() ==PRISME)
            && f->get_hight_to_int() && f->get_base_size() > 2)
    cur_figure = f;
    else
        return;
    qglClearColor(back_grount_color);
    getVertexArray();
    getColorArray();
    getIndexArray();
    updateGL();
}
Scene3D::Scene3D(QWidget* parent) : QGLWidget(parent)
{
   tone = 10;
   this->setParent(parent);
   this->setAcceptDrops(false);
   back_grount_color = Qt :: white;
   xRot=-90; yRot=0; zRot=0;
   zTra=0;
   nSca=1;
   cur_figure = new figure;
   cur_figure->set_figure_type(CONVEX);
   cur_figure->set_figure_type(PIRAMID);
   cur_figure->set_hight(2);
   cur_figure->set_point_hight(point(0,0,0));
   cur_figure->add_point_base(point(-4,0,0));
   cur_figure->add_point_base(point(0,-4,0));
   cur_figure->add_point_base(point(4,0,0));
   cur_figure->add_point_base(point(0,4,0));
}
void Scene3D::initializeGL()
{
   // цвет для очистки буфера изображения - фон окна
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
   glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов

   getVertexArray();
   getColorArray();
   getIndexArray();

   glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
   glEnableClientState(GL_COLOR_ARRAY);  // активизация массива цветов вершин
}
void Scene3D::resizeGL(int nWidth, int nHeight)
{
   glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
   glLoadIdentity();            // присваивает проекционной матрице единичную матрицу

   // отношение высоты окна виджета к его ширине
   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

   // мировое окно
   if (nWidth>=nHeight)
      // параметры видимости ортогональной проекции
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);
   // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
   // поле просмотра
   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}
void Scene3D::paintGL()
{
   // очистка буфера изображения и глубины
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // устанавливаем положение и ориентацию матрице моделирования
   glMatrixMode(GL_MODELVIEW);
  // загружаем единичную матрицу моделирования
   glLoadIdentity();
   glScalef(nSca, nSca, nSca);
   glTranslatef(0.0f, zTra, 0.0f);
   glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
   glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
   glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z

   drawAxis();   // рисование осей координат
   drawFigure(); // нарисовать фигуру
}

void Scene3D::contextMenuEvent(QContextMenuEvent *ev)
{
    //this->setc
}

void Scene3D::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   ptrMousePosition = pe->pos();
}
void Scene3D::mouseReleaseEvent(QMouseEvent* pe) // отжатие клавиши мыши
{
   //при отжатии клавиши мыши..
}

void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
   // вычисление углов поворота
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();
   ptrMousePosition = pe->pos();
   updateGL();
}

void Scene3D::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0)
       scale_plus();
   else if ((pe->delta())<0)
       scale_minus();
   updateGL();
}
void Scene3D::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();
      break;
      case Qt::Key_Equal:
         scale_plus();
      break;
      case Qt::Key_Minus:
         scale_minus();
      break;
      case Qt::Key_Up:
         rotate_up();
      break;
      case Qt::Key_Down:
         rotate_down();
      break;
      case Qt::Key_Left:
        rotate_left();
       break;
      case Qt::Key_Right:
         rotate_right();
      break;
      case Qt::Key_Z:
         translate_down();
      break;
      case Qt::Key_X:
         translate_up();
      break;
      case Qt::Key_Space:
         defaultScene();
      break;
   }
   updateGL();
}

void Scene3D::scale_plus() // приблизить сцену
{
   nSca = nSca*1.1;
}

void Scene3D::scale_minus() // удалиться от сцены
{
   nSca = nSca/1.1;
}

void Scene3D::rotate_up() // повернуть сцену вверх
{
   xRot += 1.0;
}

void Scene3D::rotate_down() // повернуть сцену вниз
{
   xRot -= 1.0;
}

void Scene3D::rotate_left() // повернуть сцену влево
{
   zRot += 1.0;
}

void Scene3D::rotate_right() // повернуть сцену вправо
{
   zRot -= 1.0;
}

void Scene3D::translate_down() // транслировать сцену вниз
{
   zTra -= 0.05;
}

void Scene3D::translate_up() // транслировать сцену вверх
{
   zTra += 0.05;
}

void Scene3D::defaultScene() // наблюдение сцены по умолчанию
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::drawAxis() // построить оси координат
{
   // устанавливаем ширину линии
   glLineWidth(3.0f);
   // устанавливаем цвет последующих примитивов
   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   // ось x красного цвета
   glBegin(GL_LINES); // построение линии
      glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}

void Scene3D::getVertexArray() // определить массив вершин
{// вычисляем точки фигуры
    //вычисляем вектор высоты h
    float A, B, C; // добавить проверку на не колониарность трех точек
    int x1, y1, z1, x2, y2, z2, x3, y3, z3;
    point p1=cur_figure->get_point_base(0);
    point p2=cur_figure->get_point_base(1);
    point p3=cur_figure->get_point_base(2);
    x1=p1.k[0];
    y1=p1.k[1];
    z1=p1.k[2];
    x2=p2.k[0];
    y2=p2.k[1];
    z2=p2.k[2];
    x3=p3.k[0];
    y3=p3.k[1];
    z3=p3.k[2];
    A=(y2-y1)*(z3-z1) - (y3-y1)*(z2-z1);
    B=(z2-z1)*(x3-x1) - (z3-z1)*(x2-x1);
    C=(x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
    A/=qSqrt(A*A+B*B+C*C)+static_cast<int>(qSqrt(A*A+B*B+C*C)==0);
    B/=qSqrt(A*A+B*B+C*C)+static_cast<int>(qSqrt(A*A+B*B+C*C)==0);
    C/=qSqrt(A*A+B*B+C*C)+static_cast<int>(qSqrt(A*A+B*B+C*C)==0);
    h.k[0]=A*static_cast<float>(cur_figure->get_hight_to_int());
    h.k[1]=B*static_cast<float>(cur_figure->get_hight_to_int());
    h.k[2]=C*static_cast<float>(cur_figure->get_hight_to_int());
    // вычисляем точки основания
    int i, n_points = cur_figure->get_base_size();// количество точек в основании
    for (i=0; i<n_points;i++)
    {
        VertexArray[i][0]=cur_figure->get_point_base(i).k[0];   // x
        VertexArray[i][1]=cur_figure->get_point_base(i).k[1];   // y
        VertexArray[i][2]=cur_figure->get_point_base(i).k[2];   // z
        // Для пирамиды сразу вычисляем точки второго основание
        if (cur_figure->get_figure_type_to_QStr()==PRISME)
        {
            VertexArray[i+n_points][0]=cur_figure->get_point_base(i).k[0]+h.k[0];   // x
            VertexArray[i+n_points][1]=cur_figure->get_point_base(i).k[1]+h.k[1];   // y
            VertexArray[i+n_points][2]=cur_figure->get_point_base(i).k[2]+h.k[2];   // z
        }
    }
    if (cur_figure->get_figure_type_to_QStr()==PIRAMID)
    {
        // Вычисляем вторую точку высоты
        VertexArray[i][0]=cur_figure->get_point_hight().k[0]+h.k[0];   // x
        VertexArray[i][1]=cur_figure->get_point_hight().k[1]+h.k[1];   // y
        VertexArray[i][2]=cur_figure->get_point_hight().k[2]+h.k[2];   // z
    }
}

void Scene3D::getColorArray() // определить массив цветов вершин
{
    int n_points;
    if (cur_figure->get_figure_type_to_QStr()==PIRAMID)
        n_points = cur_figure->get_base_size()*6+6;
    else if (cur_figure->get_figure_type_to_QStr()==PRISME)
        n_points = cur_figure->get_base_size()*12;
   for (int i=0; i < n_points; i++)
   {
       ColorArray[i][0]=0.1f*(i%2+qrand()%tone); // R - красная составляющая
       ColorArray[i][1]=0.1f*(i%2+qrand()%tone); // G - зелёная составляющая
       ColorArray[i][2]=0.1f*(i%2+qrand()%tone); // B - синяя составляющая
   }
}

void Scene3D::getIndexArray()   // определить массив индексов
{
    int i, j;
    int n_points = cur_figure->get_base_size();
    // Основание
    for (i=2, j=0; i<n_points; i++, j++)
    {
        IndexArray[j][0]=0; // индекс (номер) 1-ой вершины
        IndexArray[j][1]=i-1; // индекс (номер) 2-ой вершины
        IndexArray[j][2]=i; // индекс (номер) 3-ей вершины
    }
    if (cur_figure->get_figure_type_to_QStr() == PRISME) // для призмы вычисляем второе основание
        for (i=2+n_points; i< 2*n_points; i++, j++)
        {
            IndexArray[j][0]=n_points; // индекс (номер) 1-ой вершины
            IndexArray[j][1]=i-1; // индекс (номер) 2-ой вершины
            IndexArray[j][2]=i; // индекс (номер) 3-ей вершины
        }

    if (cur_figure->get_figure_type_to_QStr() == PIRAMID)
    {// Бока для пирамиды
        for (i=1; i<n_points;i++, j++)
        {
            IndexArray[j][0]=n_points; // индекс (номер) 1-ой вершины
            IndexArray[j][1]=i-1; // индекс (номер) 2-ой вершины
            IndexArray[j][2]=i; // индекс (номер) 3-ей вершины
        }
        // замыкающая грань, последие точки с первыми
        IndexArray[j][0]=n_points; // индекс второй точки высоты
        IndexArray[j][1]=i-1; // индекс (номер) 2-ой вершины
        IndexArray[j][2]=0; // индекс (номер) 3-ей вершины
        j++;
    }
    else if (cur_figure->get_figure_type_to_QStr() == PRISME)
    {
        for (i=1; i<n_points;i++, j++)
        {// бок призмы состоит из двух триугольников
            // парвый триугольник
            IndexArray[j][0]=i-1; // индекс (номер) 1-ой вершины
            IndexArray[j][1]=i+n_points-1; // индекс (номер) 2-ой вершины
            IndexArray[j][2]=i+n_points; // индекс (номер) 3-ей вершины
            j++; // второй
            IndexArray[j][0]=i-1; // индекс (номер) 1-ой вершины
            IndexArray[j][1]=i; // индекс (номер) 2-ой вершины
            IndexArray[j][2]=i+n_points; // индекс (номер) 3-ей вершины
        }
        // замыкающая грань, последие точки с первыми
        // парвый триугольник
        IndexArray[j][0]=0; // индекс (номер) 1-ой вершины
        IndexArray[j][1]=n_points; // индекс (номер) 2-ой вершины
        IndexArray[j][2]=2*n_points-1; // индекс (номер) 3-ей вершины
        j++; // второй
        IndexArray[j][0]=0; // индекс (номер) 1-ой вершины
        IndexArray[j][1]=n_points-1; // индекс (номер) 2-ой вершины
        IndexArray[j][2]=2*n_points-1; // индекс (номер) 3-ей вершины
    }
}

void Scene3D::drawFigure() // построить фигуру
{
   // указываем, откуда нужно извлечь данные о массиве вершин
   glVertexPointer(3, GL_FLOAT, 0, VertexArray);
   // указываем, откуда нужно извлечь данные о массиве цветов вершин
   glColorPointer(3, GL_FLOAT, 0, ColorArray);
   // используя массивы вершин и индексов, строим поверхности
   if (cur_figure->get_figure_type_to_QStr() == PIRAMID)
      glDrawElements(GL_TRIANGLES, (cur_figure->get_base_size()-1)*6, GL_UNSIGNED_BYTE, IndexArray);
   else if(cur_figure->get_figure_type_to_QStr() == PRISME)
       glDrawElements(GL_TRIANGLES, (cur_figure->get_base_size()-1)*12, GL_UNSIGNED_BYTE, IndexArray);
}

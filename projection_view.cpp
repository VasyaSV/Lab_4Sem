#include "projection_view.h"

projection_view::projection_view(QWidget *parent)
{
    this->setParent(parent);
    this->setAcceptDrops(false);
    graphicsView = new QGraphicsView(parent);
    graphicsScene = new QGraphicsScene(parent);
    graphicsView->setMouseTracking(true);
    pos_x_y_z = new QLabel("hello", parent);
    graphicsView->setScene(graphicsScene);
    this->layout()->addWidget(graphicsView);
    sx = sy = 10.7;
    //graphicsScene->setSceneRect(0, 0, 300, 200);
    graphicsView->setGeometry(0,0,300,200);
    graphicsView->scale(sx, sy);

    project_on = new QComboBox(this);
    project_on->addItem(tr("On plane"));
    project_on->addItem(tr("x/y"));
    project_on->addItem(tr("y/z"));
    project_on->addItem(tr("x/z"));

    cur_figure = new figure;
    cur_figure->set_figure_type(CONVEX);
    cur_figure->set_figure_type(PIRAMID);
    cur_figure->set_hight(2);
    cur_figure->set_point_hight(point(0,0,0));
    cur_figure->add_point_base(point(-4,0,0));
    cur_figure->add_point_base(point(0,-4,0));
    cur_figure->add_point_base(point(4,0,0));
    cur_figure->add_point_base(point(0,4,0));
    this->set_cur_figure(cur_figure);

    QHBoxLayout *l = new QHBoxLayout(parent);
    this->setLayout(l);
    l->addWidget(project_on, 1);
    l->addWidget(pos_x_y_z, 2);
    //project_on->hide();
    //pos_x_y_z->move(10,15);
    proj_type = 0;
    QObject::connect(project_on, SIGNAL(currentIndexChanged(int)), this, SLOT(proj_calc(int)));

}

void projection_view::proj_calc(int n){
    proj_type = n;
    cur_projection.set_new(cur_figure->points_base, proj_type);
}

void projection_view::paintEvent(QPaintEvent *event)
{
    if (!cur_projection.get_num_points())
        return;
    graphicsScene->clear();
    //graphicsView->resetCachedContent();
    if (cur_figure->get_base_size() == 1)
    {
        graphicsScene->addLine(QLineF(cur_projection.get_point(0).x, cur_projection.get_point(0).y,
                                      cur_projection.get_point(0).x + 0.01, cur_projection.get_point(0).y + 0.01),
                               QPen(Qt::blue));
        return;
    }
    int i;
    for (i=1; i < cur_figure->get_base_size(); i++)
    {
        graphicsScene->addLine(QLineF(cur_projection.get_point(i-1).x, cur_projection.get_point(i-1).y,
                                      cur_projection.get_point(i).x, cur_projection.get_point(i).y), QPen(Qt::blue));
        graphicsScene->addLine(QLineF(cur_projection.get_point(i).x, cur_projection.get_point(i).y
                                     ,cur_projection.get_point(i).x+0.01, cur_projection.get_point(i).y-0.01), QPen(Qt::black, 0.5));
    }
    graphicsScene->addLine(QLineF(cur_projection.get_point(i-1).x, cur_projection.get_point(i-1).y,
                                  cur_projection.get_point(0).x, cur_projection.get_point(0).y), QPen(Qt::blue));
    graphicsScene->addLine(QLineF(cur_projection.get_point(0).x, cur_projection.get_point(0).y
                                 ,cur_projection.get_point(0).x+0.01, cur_projection.get_point(0).y-0.01), QPen(Qt::black, 0.5));
    point2d h; // hight
    h = cur_projection.get_proj_point(cur_figure->get_point_hight(), proj_type);
    graphicsScene->addLine(QLineF(h.x, h.y, h.x+0.01, h.y-0.01), QPen(Qt::red, 0.5));
}

void projection_view::set_cur_figure(figure* fgr){
    cur_figure = fgr;
    proj_calc(project_on->currentIndex());
    update();
}

void projection_view::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    QPointF pos = graphicsView->mapToScene(graphicsView->mapFromGlobal(QCursor::pos()));
    //float realx = pos.x() * cur_projection.bazis(0);
    //float realy = pos.y() * cur_projection.bazis(1);
    point realpos = cur_projection.get_real_pos(point2d(pos.x(),pos.y()));
    qDebug(("x=" + QString().setNum(realpos.k[0])+" "
           +"y=" + QString().setNum(realpos.k[1])+" "
           +"z=" + QString().setNum(realpos.k[2])+";").toAscii());
}

void projection_view::mouseReleaseEvent(QMouseEvent* pe) // отжатие клавиши мыши
{
   //при отжатии клавиши мыши..

}

void projection_view::mouseMoveEvent(QMouseEvent* pe)
{
   // вычисление x y z позиции и вектора здвига
    //pos_x_y_z->setText("hello i'm hir");

   //ptrMousePosition = pe->pos();
   //update();

}

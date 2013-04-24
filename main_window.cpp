#include "main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    table_view = new QTableView;
    tdelegate = new TableDelegate;
    model = new QATableFigure;
    scene3d = new Scene3D;
    file_dialog = new QFileDialog;
    file_dialog->setNameFilter("Figure file\'s (*.fgr)");
    this->setDockOptions(QMainWindow::VerticalTabs);
    table_view->setItemDelegate(tdelegate);
    table_view->setModel(model);
    add_menu_bar(parent);
    add_dock_widgets(parent);
    cultivate_conects();
}

void main_window::add_menu_bar(QWidget *parent){
    QAction *file_new;
    QAction *file_open;
    QAction *file_save;
    QAction *quit;
    QAction *about;
    QAction *table;
    QAction *window_3d;
    QAction *a_add_after;
    QAction *a_add_before;
    QAction *a_add_down;
    menu_bar = new QMenuBar;
    this->setMenuBar(menu_bar);
    QMenu *tmp = new QMenu;
    tmp->setTitle("File");
    menu_bar->addMenu(tmp);

    file_new = new QAction(parent);
    file_new->setShortcut(tr("Ctrl+N"));
    QObject::connect(file_new, SIGNAL(activated()), this, SLOT(fileNew_clicked()));

    file_open = new QAction(parent);
    file_open->setShortcut(tr("Ctrl+O"));
    QObject::connect(file_open, SIGNAL(activated()), this, SLOT(fileOpen_clicked()));

    file_save = new QAction(parent);
    file_save->setShortcut(tr("Ctrl+S"));
    QObject::connect(file_save, SIGNAL(activated()), this, SLOT(fileSave_clicked()));

    quit = new QAction(parent);
    quit->setShortcut(tr("Ctrl+X"));
    QObject::connect(quit, SIGNAL(activated()), this, SLOT(close()));

    file_new->setText("New");
    file_open->setText("Open");
    file_save->setText("Save");
    quit->setText("Exit");

    tmp->addAction(file_new);
    tmp->addAction(file_open);
    tmp->addAction(file_save);
    tmp->addSeparator();
    tmp->addAction(quit);

    QMenu *tmp3 = new QMenu;
    tmp3->setTitle("Edit");
    menu_bar->addMenu(tmp3);

    a_add_after = new QAction(parent);
    a_add_before = new QAction(parent);
    a_add_down = new QAction(parent);
    a_add_after->setShortcut(tr("Ctrl+A"));
    a_add_before->setShortcut(tr("Shift+A"));
    a_add_down->setShortcut(tr("Shift+D"));
    a_add_after->setText("Add after");
    a_add_before->setText("Add before");
    a_add_down->setText("Add down");
    tmp3->addAction(a_add_after);
    tmp3->addAction(a_add_before);
    tmp3->addAction(a_add_down);
    QObject::connect(a_add_after, SIGNAL(activated()), this, SLOT(add_after()));
    QObject::connect(a_add_before, SIGNAL(activated()), this, SLOT(add_before()));
    QObject::connect(a_add_down, SIGNAL(activated()), this, SLOT(add_end()));

    QMenu *tmp2 = new QMenu;
    tmp2->setTitle("Window");
    menu_bar->addMenu(tmp2);

    table = new QAction(parent);
    table->setShortcut(tr("Shift+T"));
    table->setCheckable(true);
    table->toggle();
    QObject::connect(table, SIGNAL(toggled(bool)), this, SLOT(setVisible_table(bool)));

    window_3d = new QAction(parent);
    window_3d->setShortcut(tr("Shift+D"));
    window_3d->setCheckable(true);
    window_3d->toggle();
    QObject::connect(window_3d, SIGNAL(toggled(bool)), this, SLOT(setVisible_3d(bool)));

    table->setText("Table view");
    window_3d->setText("3D Tool");

    tmp2->addAction(table);
    tmp2->addAction(window_3d);

    about = new QAction(parent);
    about->setText("About");
    menu_bar->addAction(about);
    QObject::connect(about, SIGNAL(activated()), this, SLOT(about_clicked()));
}

void main_window::add_dock_widgets(QWidget *parent){
    dcw_table_view = new QDockWidget(parent);
    dcw_table_view->layout()->addWidget(table_view);
    this->addDockWidget(Qt::LeftDockWidgetArea, dcw_table_view);
    dcw_3d_tool = new QDockWidget(parent);
    this->addDockWidget(Qt::RightDockWidgetArea, dcw_3d_tool);
    dcw_3d_tool->layout()->addWidget(scene3d);
    //scene3d->setWindowTitle("x y z");
    //scene3d->resize(300, 300);  // размеры (nWidth, nHeight) окна
    //scene3d->show(); // изобразить виджет
    scene3d->showFullScreen();
    scene3d->showMaximized();
}

void main_window::cultivate_conects(){
    QObject::connect(this, SIGNAL(clear_cell(int,int)), model, SLOT(clear_cell(int,int)));
    QObject::connect(this, SIGNAL(removeRow(int,int)), model, SLOT(removeRow(int,int)));
    QObject::connect(this, SIGNAL(insertRow(int)), model, SLOT(insertRow(int)));
    QObject::connect(this, SIGNAL(fileSave(QString)), model, SLOT(write_base_in_file(QString)));
    QObject::connect(this, SIGNAL(fileOpen(QString)), model, SLOT(read_base_from_file(QString)));
    QObject::connect(dcw_table_view, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisible_table(bool)));
    QObject::connect(dcw_3d_tool, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisible_3d(bool)));
    QObject::connect(this, SIGNAL(sql(bool)), model, SLOT(sql(bool)));

    QObject::connect(table_view->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                SLOT(tableSelectionChanged()));
}

void main_window::tableSelectionChanged()
{
    if (table_view->selectionModel()->selectedIndexes().count())
        scene3d->set_figure(model->list.at(
                               table_view->selectionModel()->selectedIndexes().at(0).row()));
}

void main_window::about_clicked(){
   // QDebug << ("WHOT ABOUT!???");
}

void main_window::add_after(){
    if (table_view->selectionModel()->selectedIndexes().count())
        model->insertRow(table_view->selectionModel()->selectedIndexes().at(0).row()+1);
}

void main_window::add_before(){
    if (table_view->selectionModel()->selectedIndexes().count())
        model->insertRow(table_view->selectionModel()->selectedIndexes().at(0).row());
}

void main_window::add_end(){
    if (table_view->selectionModel()->selectedIndexes().count())
        model->insertRow(table_view->model()->rowCount());
}

void main_window::fileNew_clicked(){
    int n_rows = table_view->model()->rowCount();
    if (n_rows) // delete all raws
        emit removeRow(table_view->rowAt(0), n_rows);
    emit insertRow(0);
    for (int i=0; i<5 ; i++)
        emit clear_cell(0,i);
}

void main_window::fileSave_clicked(){
    emit fileSave(file_dialog->getSaveFileName());
}
void main_window::fileOpen_clicked(){
    table_view->clearSelection();
    QString name = file_dialog->getOpenFileName();
    if (name.length()==0)
        return;
    int n = table_view->model()->rowCount();
    if (n) // delete all raws
        emit removeRow(table_view->rowAt(0), n);
    emit fileOpen(name);
}

void main_window::setVisible_3d(bool hf){
    dcw_3d_tool->setVisible(hf);
}

void main_window::setVisible_table(bool hf){
    dcw_table_view->setVisible(hf);
}

void main_window::keyPressEvent(QKeyEvent *ev){
    if (ev->key() == Qt::Key_Delete)
    {
        int n_select = table_view->selectionModel()->selectedIndexes().count();
        int first_select;
        if (table_view->selectionModel()->selectedRows().size())
            first_select = table_view->selectionModel()->selectedRows().at(0).row();
        int n_rows = table_view->model()->rowCount();
        for( int i = 0; i < n_select; i++)
            emit clear_cell(table_view->selectionModel()->selectedIndexes().at(i).row(),
                            table_view->selectionModel()->selectedIndexes().at(i).column());

        n_select = table_view->selectionModel()->selectedRows().count();
        if (n_select)
            if (first_select && n_rows != n_select)
                emit removeRow(first_select, n_select);
            else if (n_rows > 1)
                emit removeRow(table_view->selectionModel()->selectedRows().at(1).row(),
                               n_select-1);
        table_view->clearSelection();
        return;
    }
    if(ev->key() == Qt::Key_R)
    {
        qDebug("Key Space");
        //scene3d->set_now_figure(model->list.at(0));
    }
    return;
}

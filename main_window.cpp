#include "main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent)
{
    table_view = new QTableView(parent);
    tdelegate = new TableDelegate;
    model = new QATableFigure;
    scene3d = new Scene3D(parent);
    file_dialog = new QFileDialog(parent);
    this->setDockOptions(QMainWindow::VerticalTabs);
    add_dock_widgets(parent);
    table_view->setItemDelegate(tdelegate);
    table_view->setModel(model);
    add_menu_bar(parent);
    cultivate_conects();
    table_view->setAcceptDrops(false);
    this->setAcceptDrops(true);
    this->resize(950, 444);
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
    QAction *sinchro;
    //QAction *down_row;
    //QAction *copy
    //QAction *paste
    //QAction *i_dont_know_what_all_else_matters

    menu_bar = new QMenuBar;
    this->setMenuBar(menu_bar);
    QMenu *memu_file = new QMenu;
    memu_file->setTitle("File");
    menu_bar->addMenu(memu_file);

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

    memu_file->addAction(file_new);
    memu_file->addAction(file_open);
    memu_file->addAction(file_save);
    memu_file->addSeparator();
    memu_file->addAction(quit);

    QMenu *memu_edit = new QMenu;
    memu_edit->setTitle("Edit");
    menu_bar->addMenu(memu_edit);

    a_add_after = new QAction(parent);
    a_add_after->setShortcut(tr("Ctrl+A"));

    a_add_before = new QAction(parent);
    a_add_before->setShortcut(tr("Shift+A"));

    a_add_down = new QAction(parent);
    a_add_down->setShortcut(tr("Ctrl+D"));

    a_add_after->setText("Add after");
    a_add_before->setText("Add before");
    a_add_down->setText("Add down");

    memu_edit->addAction(a_add_after);
    memu_edit->addAction(a_add_before);
    memu_edit->addAction(a_add_down);
    QObject::connect(a_add_after, SIGNAL(activated()), this, SLOT(add_after()));
    QObject::connect(a_add_before, SIGNAL(activated()), this, SLOT(add_before()));
    QObject::connect(a_add_down, SIGNAL(activated()), this, SLOT(add_end()));

    QMenu *memu_window = new QMenu;
    memu_window->setTitle("Window");
    menu_bar->addMenu(memu_window);

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

    memu_window->addAction(table);
    memu_window->addAction(window_3d);

    about = new QAction(parent);
    about->setText("About");
    menu_bar->addAction(about);
    QObject::connect(about, SIGNAL(activated()), this, SLOT(about_clicked()));
}

void main_window::add_dock_widgets(QWidget *parent){
    this->setCentralWidget(table_view);
    dcw_3d_tool = new QDockWidget(parent);
    this->addDockWidget(Qt::RightDockWidgetArea, dcw_3d_tool);
    dcw_3d_tool->setLayout(new QHBoxLayout(parent));
    dcw_3d_tool->layout()->addWidget(scene3d);
    scene3d->move(5, 22);
    scene3d->setFixedSize(300, 200);
    dcw_3d_tool->setFixedSize(305, 222);

    dcw_2d_tool = new QDockWidget(parent);
    projection = new projection_view(parent);
    dcw_2d_tool->setFixedSize(300,200);
    this->addDockWidget(Qt::RightDockWidgetArea, dcw_2d_tool);
    dcw_2d_tool->setLayout(new QHBoxLayout(parent));
    dcw_2d_tool->layout()->addWidget(projection);
    projection->move(5, 22);
    projection->setFixedSize(300, 200);
    dcw_2d_tool->setFixedSize(305, 222);

   // QLabel *view_3d_name = new QLabel("3d view", parent);
   // dcw_3d_tool->layout()->addWidget(view_3d_name);
   // view_3d_name->move(5, 210);

}

void main_window::cultivate_conects(){
    QObject::connect(this, SIGNAL(clear_cell(int,int)), model, SLOT(clear_cell(int,int)));
    QObject::connect(this, SIGNAL(removeRow(int,int)), model, SLOT(removeRow(int,int)));
    QObject::connect(this, SIGNAL(insertRow(int)), model, SLOT(insertRow(int)));
    QObject::connect(this, SIGNAL(fileSave(QString)), model, SLOT(write_base_in_file(QString)));
    QObject::connect(this, SIGNAL(fileOpen(QString)), model, SLOT(read_base_from_file(QString)));
    QObject::connect(dcw_3d_tool, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisible_3d(bool)));
    QObject::connect(this, SIGNAL(sql(bool)), model, SLOT(sql(bool)));
    QObject::connect(this, SIGNAL(recolculat_model()), model, SLOT(refreash()));
    QObject::connect(table_view->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                SLOT(tableSelectionChanged()));
    QObject::connect(projection, SIGNAL(refreash(figure*)), scene3d, SLOT(set_figure(figure*)));
}

void main_window::tableSelectionChanged(){
    if (table_view->selectionModel()->selectedIndexes().count())
    {
        scene3d->set_figure(model->list.at(
                               table_view->selectionModel()->selectedIndexes().at(0).row()));
        projection->set_cur_figure(model->list.at(
                               table_view->selectionModel()->selectedIndexes().at(0).row()));

    }
}

void main_window::about_clicked(){
    QMessageBox::about(this, "About", "<img src = about.jpg>");
}

void main_window::add_after(){
    if (table_view->selectionModel()->selectedIndexes().count())
        model->insertRow(table_view->selectionModel()->selectedIndexes().at(0).row()+1);
    else
        model->insertRow(0);
}

void main_window::add_before(){
    if (table_view->selectionModel()->selectedIndexes().count())
        model->insertRow(table_view->selectionModel()->selectedIndexes().at(0).row());
    else
        model->insertRow(0);
}

void main_window::add_end(){
    if (table_view->selectionModel()->selectedIndexes().count())
        model->insertRow(table_view->model()->rowCount());
    else
        model->insertRow(0);
}

void main_window::fileNew_clicked(){
    int n_rows = table_view->model()->rowCount();
    if (n_rows) // delete all raws
        emit removeRow(table_view->rowAt(0), n_rows);
    model->sql.close();
    emit insertRow(0);
    for (int i=0; i<5 ; i++)
        emit clear_cell(0,i);
}

void main_window::fileSave_clicked(){
    model->sql.close();
    emit fileSave(file_dialog->getSaveFileName(this, tr("Save files"), QString(),
                                               tr( "Figure file(*.fgr);;"
                                                 "Sql data base(*.SQLite);;"
                                                 "Text file(*.txt);;"
                                                 "All files(*.*)")));
}
void main_window::fileOpen_clicked(){
    table_view->clearSelection();
    QString name = file_dialog->getOpenFileName(this, tr("Open files"), QString(),
                                                 tr( "Figure file(*.fgr);;"
                                                   "Sql data base(*.SQLite);;"
                                                   "Text file(*.txt);;"
                                                   "All files(*.*)"));
    if (name.isEmpty())
        return;
    int n = table_view->model()->rowCount();
    model->sql.close();
    if (n) // delete all raws
        emit removeRow(table_view->rowAt(0), n);
    emit fileOpen(name);
    emit recolculat_model();
}

void main_window::setVisible_3d(bool hf){
    dcw_3d_tool->setVisible(hf);
}

void main_window::setVisible_table(bool hf){
    table_view->setVisible(hf);
}

void main_window::keyPressEvent(QKeyEvent *ev){
    if (ev->key() == Qt::Key_Delete)
    {
        int n_select = table_view->selectionModel()->selectedIndexes().count();
        int first_select;
        if (!table_view->selectionModel()->selectedRows().isEmpty())
            first_select = table_view->selectionModel()->selectedRows().at(0).row();
        int n_rows = table_view->model()->rowCount();
        int count_select = table_view->selectionModel()->selectedRows().count();
        if (!count_select)
            for( int i = 0; i < n_select; i++)
                emit clear_cell(table_view->selectionModel()->selectedIndexes().at(i).row(),
                        table_view->selectionModel()->selectedIndexes().at(i).column());
        else
            if (first_select || n_rows > count_select)
                emit removeRow(first_select, count_select);
            else if (n_rows > 1)
                if (count_select > 1)
                   emit removeRow(table_view->selectionModel()->selectedRows().at(1).row(),
                        count_select-1);
                else
                    emit removeRow(table_view->selectionModel()->selectedRows().at(0).row(),
                                1);

        table_view->clearSelection();
        return;
    }
    return;
}

void main_window::dropEvent(QDropEvent *ev){
    if (ev->mimeData()->urls().empty())
        return;
    QString fileName = ev->mimeData()->urls().first().toLocalFile();
    if (fileName.isEmpty())
        return;
    table_view->clearSelection();
    int n = table_view->model()->rowCount();
    if (n) // delete all raws
        emit removeRow(table_view->rowAt(0), n);
    emit fileOpen(fileName);
}

void main_window::dragEnterEvent(QDragEnterEvent *ev){
   if (ev->mimeData()->hasFormat("text/uri-list"))
       ev->acceptProposedAction();
}




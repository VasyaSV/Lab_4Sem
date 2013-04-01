#include <Windows.h>
#include <QApplication>
#include "control_dialog.h"
#include "main_window.h"
#include "model_figure.h"
#include "visual_draw_vertex_map.h"
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton mwin_temp;
    mwin_temp.show();

    QATableFigure mdl;
    mdl;
    return app.exec();
}

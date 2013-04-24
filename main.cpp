#include <Windows.h>
#include <QApplication>
#include <QtOpenGL>
#include <QTimer>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    main_window w;
    w.show();
    return app.exec();
}

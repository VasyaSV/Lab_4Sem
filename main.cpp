#include <Windows.h>
#include <QApplication>
#include <QtOpenGL>
#include <QTimer>
#include "view_3d.h"
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    Scene3D scene1; // создаём виджет класса Scene3D
//    scene1.setWindowTitle("x y z");
//    scene1.resize(250, 250);  // размеры (nWidth, nHeight) окна
//    scene1.show(); // изобразить виджет
//    scene1.showFullScreen();
//    scene1.showMaximized();
    main_window w;
    w.show();
    return app.exec();
}

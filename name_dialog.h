#ifndef NAME_DIALOG_H
#define NAME_DIALOG_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

class Name_dialog : public QDialog
{
    Q_OBJECT
    QGridLayout *l;
    QLineEdit *edit1, *edit2;
    QPushButton *btn_ok, *btn_cancel;
    QString first_name;
    QString second_name;
public:
    Name_dialog(QString question = "Wat's your name",
                QString l_first_name = "first name", QString l_second_name = "second name",
                QString first_name = "temp", QString second_name = "figure");
public slots:
    void ok_pressed();
signals:
    void name(QString first_name, QString second_name);
};


#endif // NAME_DIALOG_H

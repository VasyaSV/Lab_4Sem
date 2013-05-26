#include "name_dialog.h"

Name_dialog::Name_dialog(QString question, QString l_first_name, QString l_second_name,
                         QString first_name, QString second_name)
{    
    this->first_name = first_name;
    this->second_name = second_name;
    l = new QGridLayout;
    this->setLayout(l);
    QLabel *quest = new QLabel(question);
    l->addWidget(quest, 0, 0, 1, 2);

    edit1 = new QLineEdit(first_name, this);
    QLabel *l_first = new QLabel(l_first_name, this);
    l->addWidget(l_first, 1, 0, 1, 1);
    l->addWidget(edit1, 1, 1, 1, 1);
    edit2 = new QLineEdit(second_name, this);
    QLabel *l_second = new QLabel(l_second_name, this);
    l->addWidget(l_second, 2, 0, 1, 1);
    l->addWidget(edit2, 2, 1, 1, 1);
    btn_ok = new QPushButton("Ok", this);
    btn_cancel = new QPushButton("Cancel", this);
    l->addWidget(btn_ok, 3, 5, 1, 1);
    l->addWidget(btn_cancel, 3, 6, 1, 1);
    QObject::connect(btn_ok, SIGNAL(clicked()), this, SLOT(ok_pressed()));
    QObject::connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    this->show();
}

void Name_dialog::ok_pressed(){
    first_name = edit1->text();
    second_name = edit2->text();
    emit name(first_name, second_name);
    this->close();
}

#ifndef CONTROL_DIALOG_H
#define CONTROL_DIALOG_H

#include <QObject>
#include <QItemDelegate>
#include <QDateTimeEdit>
#include <QTimeEdit>
#include <QLineEdit>

using namespace std;

class TableDelegate : public QItemDelegate
{
public:
    TableDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};



class control_dialog : public QObject
{
    Q_OBJECT
public:
    explicit control_dialog(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CONTROL_DIALOG_H

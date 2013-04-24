#ifndef CONTROL_DIALOG_H
#define CONTROL_DIALOG_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QItemDelegate>
#include <QDateTimeEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include "Constants.h"

using namespace std;

class TableDelegate : public QItemDelegate
{
public:
    TableDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // CONTROL_DIALOG_H

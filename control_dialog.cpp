#include "control_dialog.h"

control_dialog::control_dialog(QObject *parent) :
    QObject(parent)
{
}

TableDelegate::TableDelegate(){}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
    editor->setText(currentText);
    return editor;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
    if (textEditor) {
        textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
    }
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
    if (textEditor) {
        model->setData(index, textEditor->text());
    }
}


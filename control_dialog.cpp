#include "control_dialog.h"
const QString max_number_sites = "20";

TableDelegate::TableDelegate(){}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0) // figure type
    {
        QComboBox *combo_editor;
        combo_editor = new QComboBox(parent);
        combo_editor->addItem(tr("Piramid"));
        combo_editor->addItem(tr("Prisme"));
        return combo_editor;
    }
    else if (index.column() == 1 || index.column() == 5) // base type
    {
        QLabel *l_base = new QLabel(parent);
        return l_base;
    }
    else if (index.column() == 2) // hight
    {
        QRegExp rx;
        rx.setPattern("[0-9]{1,6}");
        QRegExpValidator *validator = new QRegExpValidator(rx);
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(validator);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    else if (index.column() == 3) // hight possicion
    {
        QRegExp rx;
        rx.setPattern("(\\([0-9\\-][0-9]{0,6},[0-9\\-][0-9]{0,6},[0-9\\-][0-9]{0,6}\\)){1,1}");
        QRegExpValidator *validator = new QRegExpValidator(rx);
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(validator);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    else //if (index.column() == 4) // base points
    {
        QRegExp rx;
        rx.setPattern("(\\([0-9\\-][0-9]{0,6},[0-9\\-][0-9]{0,6},[0-9\\-][0-9]{0,6}\\)){0," + max_number_sites + "}");
        QRegExpValidator *validator = new QRegExpValidator(rx);
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(validator);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!editor)
        return;
   if (index.column()==0)
   {
        QComboBox *combo_editor = qobject_cast<QComboBox *>(editor);
        combo_editor->setEditText(index.model()->data(index, Qt::EditRole).toString());
        return;
   }
   if (index.column()==1 || index.column()==5)
   {
        QLabel *lable_editor = qobject_cast<QLabel *>(editor);
        lable_editor->setText(index.model()->data(index, Qt::EditRole).toString());
        return;
   }
    QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
    if (textEditor)
        textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!editor || index.column()==1 || index.column()==5)
        return;
    if (index.column()==0)
    {
        QComboBox *combo_editor = qobject_cast<QComboBox *>(editor);
        model->setData(index, combo_editor->currentText());
        return;
    }

    QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
    if (textEditor) {
        model->setData(index, textEditor->text());
    }
}


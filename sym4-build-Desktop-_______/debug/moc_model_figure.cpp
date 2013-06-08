/****************************************************************************
** Meta object code from reading C++ file 'model_figure.h'
**
** Created: Sat 8. Jun 14:14:15 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../model_figure.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model_figure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QATableFigure[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   15,   14,   14, 0x0a,
      76,   66,   14,   14, 0x2a,
      99,   15,   14,   14, 0x0a,
     129,   66,   14,   14, 0x2a,
     155,  151,   14,   14, 0x0a,
     178,  170,   14,   14, 0x0a,
     197,   14,   14,   14, 0x0a,
     226,   14,   14,   14, 0x0a,
     265,  254,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QATableFigure[] = {
    "QATableFigure\0\0name_file,base_name\0"
    "read_from_sql(QString,QString)\0name_file\0"
    "read_from_sql(QString)\0"
    "write_in_sql(QString,QString)\0"
    "write_in_sql(QString)\0row\0insertRow(int)\0"
    "row,num\0removeRow(int,int)\0"
    "read_base_from_file(QString)\0"
    "write_base_in_file(QString)\0row,column\0"
    "clear_cell(int,int)\0"
};

void QATableFigure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QATableFigure *_t = static_cast<QATableFigure *>(_o);
        switch (_id) {
        case 0: _t->read_from_sql((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->read_from_sql((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->write_in_sql((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->write_in_sql((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->insertRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->removeRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->read_base_from_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->write_base_in_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->clear_cell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QATableFigure::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QATableFigure::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_QATableFigure,
      qt_meta_data_QATableFigure, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QATableFigure::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QATableFigure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QATableFigure::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QATableFigure))
        return static_cast<void*>(const_cast< QATableFigure*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int QATableFigure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

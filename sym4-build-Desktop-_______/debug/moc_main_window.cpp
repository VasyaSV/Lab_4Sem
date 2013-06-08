/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created: Sat 8. Jun 14:21:08 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_main_window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      25,   12,   12,   12, 0x05,
      55,   44,   12,   12, 0x05,
      83,   75,   12,   12, 0x05,
     102,   12,   12,   12, 0x05,
     116,   12,   12,   12, 0x05,
     134,   12,   12,   12, 0x05,
     152,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     167,   12,   12,   12, 0x0a,
     191,   12,   12,   12, 0x0a,
     210,   12,   12,   12, 0x0a,
     229,   12,   12,   12, 0x0a,
     247,   12,   12,   12, 0x0a,
     263,   12,   12,   12, 0x0a,
     283,   12,   12,   12, 0x0a,
     306,   12,   12,   12, 0x0a,
     318,   12,   12,   12, 0x0a,
     331,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_main_window[] = {
    "main_window\0\0sql_close()\0recolculat_model()\0"
    "row,column\0clear_cell(int,int)\0row,num\0"
    "removeRow(int,int)\0del_pressed()\0"
    "fileSave(QString)\0fileOpen(QString)\0"
    "insertRow(int)\0tableSelectionChanged()\0"
    "fileSave_clicked()\0fileOpen_clicked()\0"
    "fileNew_clicked()\0about_clicked()\0"
    "setVisible_3d(bool)\0setVisible_table(bool)\0"
    "add_after()\0add_before()\0add_end()\0"
};

void main_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        main_window *_t = static_cast<main_window *>(_o);
        switch (_id) {
        case 0: _t->sql_close(); break;
        case 1: _t->recolculat_model(); break;
        case 2: _t->clear_cell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->removeRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->del_pressed(); break;
        case 5: _t->fileSave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->fileOpen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->insertRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->tableSelectionChanged(); break;
        case 9: _t->fileSave_clicked(); break;
        case 10: _t->fileOpen_clicked(); break;
        case 11: _t->fileNew_clicked(); break;
        case 12: _t->about_clicked(); break;
        case 13: _t->setVisible_3d((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setVisible_table((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->add_after(); break;
        case 16: _t->add_before(); break;
        case 17: _t->add_end(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData main_window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject main_window::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_main_window,
      qt_meta_data_main_window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &main_window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *main_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *main_window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_main_window))
        return static_cast<void*>(const_cast< main_window*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int main_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void main_window::sql_close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void main_window::recolculat_model()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void main_window::clear_cell(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void main_window::removeRow(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void main_window::del_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void main_window::fileSave(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void main_window::fileOpen(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void main_window::insertRow(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE

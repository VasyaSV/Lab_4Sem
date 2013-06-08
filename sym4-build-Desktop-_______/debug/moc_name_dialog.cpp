/****************************************************************************
** Meta object code from reading C++ file 'name_dialog.h'
**
** Created: Sat 8. Jun 12:26:07 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../name_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'name_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Name_dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Name_dialog[] = {
    "Name_dialog\0\0first_name,second_name\0"
    "name(QString,QString)\0ok_pressed()\0"
};

void Name_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Name_dialog *_t = static_cast<Name_dialog *>(_o);
        switch (_id) {
        case 0: _t->name((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->ok_pressed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Name_dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Name_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Name_dialog,
      qt_meta_data_Name_dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Name_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Name_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Name_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Name_dialog))
        return static_cast<void*>(const_cast< Name_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Name_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Name_dialog::name(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

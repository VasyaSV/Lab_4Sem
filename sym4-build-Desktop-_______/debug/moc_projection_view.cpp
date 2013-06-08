/****************************************************************************
** Meta object code from reading C++ file 'projection_view.h'
**
** Created: Sat 8. Jun 14:21:06 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projection_view.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projection_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_projection_view[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   16,   16,   16, 0x0a,
      59,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_projection_view[] = {
    "projection_view\0\0refreash(figure*)\0"
    "set_cur_figure(figure*)\0proj_calc(int)\0"
};

void projection_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        projection_view *_t = static_cast<projection_view *>(_o);
        switch (_id) {
        case 0: _t->refreash((*reinterpret_cast< figure*(*)>(_a[1]))); break;
        case 1: _t->set_cur_figure((*reinterpret_cast< figure*(*)>(_a[1]))); break;
        case 2: _t->proj_calc((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData projection_view::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject projection_view::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_projection_view,
      qt_meta_data_projection_view, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &projection_view::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *projection_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *projection_view::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_projection_view))
        return static_cast<void*>(const_cast< projection_view*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int projection_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void projection_view::refreash(figure * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

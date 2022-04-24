/****************************************************************************
** Meta object code from reading C++ file 'modifysystimeui.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modifysystimeui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modifysystimeui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_modifySysTimeUi[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      42,   39,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_modifySysTimeUi[] = {
    "modifySysTimeUi\0\0updateSysTimeHandle()\0"
    "ev\0keyPressEvent(QKeyEvent*)\0"
};

void modifySysTimeUi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        modifySysTimeUi *_t = static_cast<modifySysTimeUi *>(_o);
        switch (_id) {
        case 0: _t->updateSysTimeHandle(); break;
        case 1: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData modifySysTimeUi::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject modifySysTimeUi::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_modifySysTimeUi,
      qt_meta_data_modifySysTimeUi, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &modifySysTimeUi::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *modifySysTimeUi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *modifySysTimeUi::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_modifySysTimeUi))
        return static_cast<void*>(const_cast< modifySysTimeUi*>(this));
    return QDialog::qt_metacast(_clname);
}

int modifySysTimeUi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE

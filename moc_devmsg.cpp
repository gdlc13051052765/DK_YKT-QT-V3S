/****************************************************************************
** Meta object code from reading C++ file 'devmsg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "devmsg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devmsg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_devMsg[] = {

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
      11,    8,    7,    7, 0x08,
      37,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_devMsg[] = {
    "devMsg\0\0ev\0keyPressEvent(QKeyEvent*)\0"
    "save_devMsg_to_config_db()\0"
};

void devMsg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        devMsg *_t = static_cast<devMsg *>(_o);
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->save_devMsg_to_config_db(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData devMsg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject devMsg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_devMsg,
      qt_meta_data_devMsg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &devMsg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *devMsg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *devMsg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_devMsg))
        return static_cast<void*>(const_cast< devMsg*>(this));
    return QDialog::qt_metacast(_clname);
}

int devMsg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

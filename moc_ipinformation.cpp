/****************************************************************************
** Meta object code from reading C++ file 'ipinformation.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ipinformation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipinformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ipInformation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   15,   14,   14, 0x08,
      63,   49,   44,   14, 0x08,
      93,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ipInformation[] = {
    "ipInformation\0\0ev\0keyPressEvent(QKeyEvent*)\0"
    "bool\0watched,event\0eventFilter(QObject*,QEvent*)\0"
    "save_ipInformation_to_config_db()\0"
};

void ipInformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ipInformation *_t = static_cast<ipInformation *>(_o);
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->save_ipInformation_to_config_db(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ipInformation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ipInformation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ipInformation,
      qt_meta_data_ipInformation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ipInformation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ipInformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ipInformation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ipInformation))
        return static_cast<void*>(const_cast< ipInformation*>(this));
    return QDialog::qt_metacast(_clname);
}

int ipInformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainconsumeinterface.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainconsumeinterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainconsumeinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainConsumeInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      44,   21,   21,   21, 0x08,
      72,   69,   21,   21, 0x08,
      98,   21,   21,   21, 0x08,
     129,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainConsumeInterface[] = {
    "mainConsumeInterface\0\0updateSysTimeHandle()\0"
    "twinkleTimerTimeHandle()\0ev\0"
    "keyPressEvent(QKeyEvent*)\0"
    "Communicate_Msg_QT_Go_Handle()\0"
    "getConsumeModeHandle(QString)\0"
};

void mainConsumeInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainConsumeInterface *_t = static_cast<mainConsumeInterface *>(_o);
        switch (_id) {
        case 0: _t->updateSysTimeHandle(); break;
        case 1: _t->twinkleTimerTimeHandle(); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->Communicate_Msg_QT_Go_Handle(); break;
        case 4: _t->getConsumeModeHandle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mainConsumeInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainConsumeInterface::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mainConsumeInterface,
      qt_meta_data_mainConsumeInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainConsumeInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainConsumeInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainConsumeInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainConsumeInterface))
        return static_cast<void*>(const_cast< mainConsumeInterface*>(this));
    return QDialog::qt_metacast(_clname);
}

int mainConsumeInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

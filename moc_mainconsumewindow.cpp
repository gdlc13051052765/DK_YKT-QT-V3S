/****************************************************************************
** Meta object code from reading C++ file 'mainconsumewindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainconsumewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainconsumewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainConsumeWindow[] = {

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
      19,   18,   18,   18, 0x08,
      43,   18,   18,   18, 0x08,
      64,   18,   18,   18, 0x08,
      84,   81,   18,   18, 0x08,
     110,   18,   18,   18, 0x08,
     149,  141,   18,   18, 0x08,
     177,   18,   18,   18, 0x08,
     199,   18,   18,   18, 0x08,
     224,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainConsumeWindow[] = {
    "MainConsumeWindow\0\0on_OpenDialog_clicked()\0"
    "on_emitBtn_clicked()\0setStr(QString&)\0"
    "ev\0keyPressEvent(QKeyEvent*)\0"
    "Communicate_Msg_QT_Go_Handle()\0Snd_msg\0"
    "Msg_QT_Send_Handle(mesgStu)\0"
    "updateSysTimeHandle()\0twinkleTimerTimeHandle()\0"
    "getConsumeModeHandle(QString)\0"
};

void MainConsumeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainConsumeWindow *_t = static_cast<MainConsumeWindow *>(_o);
        switch (_id) {
        case 0: _t->on_OpenDialog_clicked(); break;
        case 1: _t->on_emitBtn_clicked(); break;
        case 2: _t->setStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->Communicate_Msg_QT_Go_Handle(); break;
        case 5: _t->Msg_QT_Send_Handle((*reinterpret_cast< mesgStu(*)>(_a[1]))); break;
        case 6: _t->updateSysTimeHandle(); break;
        case 7: _t->twinkleTimerTimeHandle(); break;
        case 8: _t->getConsumeModeHandle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainConsumeWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainConsumeWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainConsumeWindow,
      qt_meta_data_MainConsumeWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainConsumeWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainConsumeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainConsumeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainConsumeWindow))
        return static_cast<void*>(const_cast< MainConsumeWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainConsumeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
     101,   98,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     166,  158,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,
     215,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x0a,
     274,  270,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0mainWidgetStr(QString&)\0"
    "on_OpenDialog_clicked()\0on_emitBtn_clicked()\0"
    "setStr(QString&)\0ev\0keyPressEvent(QKeyEvent*)\0"
    "Communicate_Msg_QT_Go_Handle()\0Snd_msg\0"
    "Msg_QT_Send_Handle(mymesg)\0"
    "updateSysTimeHandle()\0twinkleTimerTimeHandle()\0"
    "getConsumeModeHandle(QString)\0str\0"
    "Handle_Rfal_Value_Event(QString)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->mainWidgetStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_OpenDialog_clicked(); break;
        case 2: _t->on_emitBtn_clicked(); break;
        case 3: _t->setStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 5: _t->Communicate_Msg_QT_Go_Handle(); break;
        case 6: _t->Msg_QT_Send_Handle((*reinterpret_cast< mymesg(*)>(_a[1]))); break;
        case 7: _t->updateSysTimeHandle(); break;
        case 8: _t->twinkleTimerTimeHandle(); break;
        case 9: _t->getConsumeModeHandle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->Handle_Rfal_Value_Event((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::mainWidgetStr(QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

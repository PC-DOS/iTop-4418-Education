/****************************************************************************
** Meta object code from reading C++ file 'networktcp.h'
**
** Created: Fri Sep 2 23:31:55 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "networktcp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networktcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkTcp[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      30,   11,   11,   11, 0x08,
      50,   11,   11,   11, 0x08,
      65,   11,   11,   11, 0x08,
      82,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NetworkTcp[] = {
    "NetworkTcp\0\0slotStartServer()\0"
    "slotConnectServer()\0slotSendMesg()\0"
    "slotNewConnect()\0slotReadMesg()\0"
};

const QMetaObject NetworkTcp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_NetworkTcp,
      qt_meta_data_NetworkTcp, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetworkTcp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetworkTcp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetworkTcp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkTcp))
        return static_cast<void*>(const_cast< NetworkTcp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int NetworkTcp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotStartServer(); break;
        case 1: slotConnectServer(); break;
        case 2: slotSendMesg(); break;
        case 3: slotNewConnect(); break;
        case 4: slotReadMesg(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

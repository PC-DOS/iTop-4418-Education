/****************************************************************************
** Meta object code from reading C++ file 'uarttest.h'
**
** Created: Thu Mar 9 22:34:58 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "uarttest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uarttest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_uarttest[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      36,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_uarttest[] = {
    "uarttest\0\0on_m_sendButton_clicked()\0"
    "remoteDataIncoming()\0"
};

const QMetaObject uarttest::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_uarttest,
      qt_meta_data_uarttest, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uarttest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uarttest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uarttest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uarttest))
        return static_cast<void*>(const_cast< uarttest*>(this));
    return QDialog::qt_metacast(_clname);
}

int uarttest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_m_sendButton_clicked(); break;
        case 1: remoteDataIncoming(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

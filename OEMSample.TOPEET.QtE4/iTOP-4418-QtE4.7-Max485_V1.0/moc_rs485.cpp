/****************************************************************************
** Meta object code from reading C++ file 'rs485.h'
**
** Created: Wed Nov 1 23:21:35 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rs485.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs485.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rs485[] = {

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
       7,    6,    6,    6, 0x08,
      33,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_rs485[] = {
    "rs485\0\0on_m_sendButton_clicked()\0"
    "remoteDataIncoming()\0"
};

const QMetaObject rs485::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_rs485,
      qt_meta_data_rs485, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rs485::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rs485::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rs485::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rs485))
        return static_cast<void*>(const_cast< rs485*>(this));
    return QDialog::qt_metacast(_clname);
}

int rs485::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

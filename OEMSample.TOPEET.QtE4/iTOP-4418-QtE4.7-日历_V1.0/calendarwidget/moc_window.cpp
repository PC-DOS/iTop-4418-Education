/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created: Sat Oct 8 02:33:24 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Window[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x08,
      33,    8,    7,    7, 0x08,
      54,    8,    7,    7, 0x08,
      80,    8,    7,    7, 0x08,
     109,    8,    7,    7, 0x08,
     136,    7,    7,    7, 0x08,
     163,  158,    7,    7, 0x08,
     189,  158,    7,    7, 0x08,
     215,    7,    7,    7, 0x08,
     238,    7,    7,    7, 0x08,
     261,    7,    7,    7, 0x08,
     279,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Window[] = {
    "Window\0\0index\0localeChanged(int)\0"
    "firstDayChanged(int)\0selectionModeChanged(int)\0"
    "horizontalHeaderChanged(int)\0"
    "verticalHeaderChanged(int)\0"
    "selectedDateChanged()\0date\0"
    "minimumDateChanged(QDate)\0"
    "maximumDateChanged(QDate)\0"
    "weekdayFormatChanged()\0weekendFormatChanged()\0"
    "reformatHeaders()\0reformatCalendarPage()\0"
};

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window,
      qt_meta_data_Window, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: localeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: firstDayChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: selectionModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: horizontalHeaderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: verticalHeaderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: selectedDateChanged(); break;
        case 6: minimumDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 7: maximumDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 8: weekdayFormatChanged(); break;
        case 9: weekendFormatChanged(); break;
        case 10: reformatHeaders(); break;
        case 11: reformatCalendarPage(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'uartdialog.h'
**
** Created: Fri Dec 7 17:17:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "uartdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uartdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UartDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UartDialog[] = {
    "UartDialog\0\0UartShowLogin()\0"
    "on_uartreturnbutton_clicked()\0"
    "on_uartlogbutton_clicked()\0"
};

void UartDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UartDialog *_t = static_cast<UartDialog *>(_o);
        switch (_id) {
        case 0: _t->UartShowLogin(); break;
        case 1: _t->on_uartreturnbutton_clicked(); break;
        case 2: _t->on_uartlogbutton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData UartDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UartDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UartDialog,
      qt_meta_data_UartDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UartDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UartDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UartDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UartDialog))
        return static_cast<void*>(const_cast< UartDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UartDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void UartDialog::UartShowLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

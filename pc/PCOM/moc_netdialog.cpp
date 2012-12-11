/****************************************************************************
** Meta object code from reading C++ file 'netdialog.h'
**
** Created: Fri Dec 7 17:17:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "netdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetDialog[] = {

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
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   10,   10,   10, 0x08,
      53,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NetDialog[] = {
    "NetDialog\0\0NetShowLogin()\0"
    "on_netexitbutton_clicked()\0"
    "on_netlogbutton_clicked()\0"
};

void NetDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetDialog *_t = static_cast<NetDialog *>(_o);
        switch (_id) {
        case 0: _t->NetShowLogin(); break;
        case 1: _t->on_netexitbutton_clicked(); break;
        case 2: _t->on_netlogbutton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NetDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NetDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetDialog,
      qt_meta_data_NetDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetDialog))
        return static_cast<void*>(const_cast< NetDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void NetDialog::NetShowLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

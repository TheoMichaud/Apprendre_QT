/****************************************************************************
** Meta object code from reading C++ file 'ihmsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../13_1_ClientTCP/ihmsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ihmsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientDialogueWindows_t {
    QByteArrayData data[12];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientDialogueWindows_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientDialogueWindows_t qt_meta_stringdata_ClientDialogueWindows = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ClientDialogueWindows"
QT_MOC_LITERAL(1, 22, 29), // "on_lineEditAdresse_textEdited"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 4), // "arg1"
QT_MOC_LITERAL(4, 58, 32), // "on_lineEditNumeroPort_textEdited"
QT_MOC_LITERAL(5, 91, 39), // "on_pushButtonConnexionAuServe..."
QT_MOC_LITERAL(6, 131, 23), // "on_pushButtonF5_clicked"
QT_MOC_LITERAL(7, 155, 23), // "on_pushButtonF1_clicked"
QT_MOC_LITERAL(8, 179, 23), // "on_pushButtonF6_clicked"
QT_MOC_LITERAL(9, 203, 23), // "on_pushButtonF3_clicked"
QT_MOC_LITERAL(10, 227, 9), // "OnReponse"
QT_MOC_LITERAL(11, 237, 7) // "reponse"

    },
    "ClientDialogueWindows\0"
    "on_lineEditAdresse_textEdited\0\0arg1\0"
    "on_lineEditNumeroPort_textEdited\0"
    "on_pushButtonConnexionAuServeur_clicked\0"
    "on_pushButtonF5_clicked\0on_pushButtonF1_clicked\0"
    "on_pushButtonF6_clicked\0on_pushButtonF3_clicked\0"
    "OnReponse\0reponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientDialogueWindows[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    0,   60,    2, 0x08 /* Private */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    0,   62,    2, 0x08 /* Private */,
       8,    0,   63,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void ClientDialogueWindows::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientDialogueWindows *_t = static_cast<ClientDialogueWindows *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_lineEditAdresse_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_lineEditNumeroPort_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_pushButtonConnexionAuServeur_clicked(); break;
        case 3: _t->on_pushButtonF5_clicked(); break;
        case 4: _t->on_pushButtonF1_clicked(); break;
        case 5: _t->on_pushButtonF6_clicked(); break;
        case 6: _t->on_pushButtonF3_clicked(); break;
        case 7: _t->OnReponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ClientDialogueWindows::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ClientDialogueWindows.data,
      qt_meta_data_ClientDialogueWindows,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientDialogueWindows::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientDialogueWindows::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientDialogueWindows.stringdata0))
        return static_cast<void*>(const_cast< ClientDialogueWindows*>(this));
    return QWidget::qt_metacast(_clname);
}

int ClientDialogueWindows::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

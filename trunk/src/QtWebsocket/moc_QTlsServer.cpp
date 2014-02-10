/****************************************************************************
** Meta object code from reading C++ file 'QTlsServer.h'
**
** Created: Thu Jan 9 20:35:38 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QTlsServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTlsServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtWebsocket__QTlsServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   68,   24,   24, 0x0a,
     110,   24,   24,   24, 0x0a,
     131,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtWebsocket__QTlsServer[] = {
    "QtWebsocket::QTlsServer\0\0serverSocket\0"
    "newTlsConnection(QSslSocket*)\0errors\0"
    "displayTlsErrors(QList<QSslError>)\0"
    "tlsSocketEncrypted()\0test()\0"
};

void QtWebsocket::QTlsServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QTlsServer *_t = static_cast<QTlsServer *>(_o);
        switch (_id) {
        case 0: _t->newTlsConnection((*reinterpret_cast< QSslSocket*(*)>(_a[1]))); break;
        case 1: _t->displayTlsErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 2: _t->tlsSocketEncrypted(); break;
        case 3: _t->test(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtWebsocket::QTlsServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtWebsocket::QTlsServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_QtWebsocket__QTlsServer,
      qt_meta_data_QtWebsocket__QTlsServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtWebsocket::QTlsServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtWebsocket::QTlsServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtWebsocket::QTlsServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtWebsocket__QTlsServer))
        return static_cast<void*>(const_cast< QTlsServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int QtWebsocket::QTlsServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QtWebsocket::QTlsServer::newTlsConnection(QSslSocket * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

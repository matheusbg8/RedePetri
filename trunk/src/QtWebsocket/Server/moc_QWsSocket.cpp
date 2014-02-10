/****************************************************************************
** Meta object code from reading C++ file 'QWsSocket.h'
**
** Created: Mon Jan 13 09:30:45 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtWebsocket/QWsSocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QWsSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtWebsocket__QWsSocket[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   24,   23,   23, 0x05,
      53,   24,   23,   23, 0x05,
      91,   79,   23,   23, 0x05,
     105,   23,   23,   23, 0x05,
     124,  117,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
     171,  152,   23,   23, 0x0a,
     225,  211,   23,   23, 0x2a,
     265,  256,   23,   23, 0x2a,
     306,  288,   23,   23, 0x0a,
     364,  351,   23,   23, 0x2a,
     408,  400,   23,   23, 0x2a,
     436,   23,   23,   23, 0x0a,
     464,  457,   23,   23, 0x0a,
     479,   23,   23,   23, 0x2a,
     487,   23,   23,   23, 0x0a,
     517,  494,   23,   23, 0x09,
     564,  548,   23,   23, 0x29,
     587,   23,   23,   23, 0x29,
     595,   23,   23,   23, 0x09,
     611,   23,   23,   23, 0x09,
     627,   23,   23,   23, 0x09,
     658,  646,   23,   23, 0x09,
     715,  711,   23,   23, 0x09,
     761,   23,   23,   23, 0x09,
     778,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtWebsocket__QWsSocket[] = {
    "QtWebsocket::QWsSocket\0\0frame\0"
    "frameReceived(QString)\0frameReceived(QByteArray)\0"
    "elapsedTime\0pong(quint64)\0encrypted()\0"
    "errors\0sslErrors(QList<QSslError>)\0"
    "hostName,port,mode\0"
    "connectToHost(QString,quint16,OpenMode)\0"
    "hostName,port\0connectToHost(QString,quint16)\0"
    "hostName\0connectToHost(QString)\0"
    "address,port,mode\0"
    "connectToHost(QHostAddress,quint16,OpenMode)\0"
    "address,port\0connectToHost(QHostAddress,quint16)\0"
    "address\0connectToHost(QHostAddress)\0"
    "disconnectFromHost()\0reason\0abort(QString)\0"
    "abort()\0ping()\0closeStatusCode,reason\0"
    "close(CloseStatusCode,QString)\0"
    "closeStatusCode\0close(CloseStatusCode)\0"
    "close()\0processDataV0()\0processDataV4()\0"
    "processHandshake()\0socketState\0"
    "processTcpStateChanged(QAbstractSocket::SocketState)\0"
    "err\0processTcpError(QAbstractSocket::SocketError)\0"
    "startHandshake()\0onEncrypted()\0"
};

void QtWebsocket::QWsSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QWsSocket *_t = static_cast<QWsSocket *>(_o);
        switch (_id) {
        case 0: _t->frameReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->frameReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->pong((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 3: _t->encrypted(); break;
        case 4: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 5: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< OpenMode(*)>(_a[3]))); break;
        case 6: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 7: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->connectToHost((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< OpenMode(*)>(_a[3]))); break;
        case 9: _t->connectToHost((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 10: _t->connectToHost((*reinterpret_cast< const QHostAddress(*)>(_a[1]))); break;
        case 11: _t->disconnectFromHost(); break;
        case 12: _t->abort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->abort(); break;
        case 14: _t->ping(); break;
        case 15: _t->close((*reinterpret_cast< CloseStatusCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->close((*reinterpret_cast< CloseStatusCode(*)>(_a[1]))); break;
        case 17: _t->close(); break;
        case 18: _t->processDataV0(); break;
        case 19: _t->processDataV4(); break;
        case 20: _t->processHandshake(); break;
        case 21: _t->processTcpStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 22: _t->processTcpError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 23: _t->startHandshake(); break;
        case 24: _t->onEncrypted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtWebsocket::QWsSocket::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtWebsocket::QWsSocket::staticMetaObject = {
    { &QAbstractSocket::staticMetaObject, qt_meta_stringdata_QtWebsocket__QWsSocket,
      qt_meta_data_QtWebsocket__QWsSocket, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtWebsocket::QWsSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtWebsocket::QWsSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtWebsocket::QWsSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtWebsocket__QWsSocket))
        return static_cast<void*>(const_cast< QWsSocket*>(this));
    return QAbstractSocket::qt_metacast(_clname);
}

int QtWebsocket::QWsSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void QtWebsocket::QWsSocket::frameReceived(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtWebsocket::QWsSocket::frameReceived(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtWebsocket::QWsSocket::pong(quint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtWebsocket::QWsSocket::encrypted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QtWebsocket::QWsSocket::sslErrors(const QList<QSslError> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

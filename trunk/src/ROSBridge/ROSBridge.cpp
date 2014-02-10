#include "ROSBridge.h"
#include <iostream>
#include <QCoreApplication>
#include <QThread>
#include "ROSBridgeJSON.h"
using namespace std;


RosBridge::RosBridge(QObject *QObjPai):
    QObject(QObjPai),
    m_bufferServico(20)
{
    m_webSocket = new QtWebsocket::QWsSocket(this, NULL, QtWebsocket::WS_V13);

    QObject::connect(m_webSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(trocaEstado(QAbstractSocket::SocketState)));
    QObject::connect(m_webSocket, SIGNAL(frameReceived(QString)), this, SLOT(recebidoMensagem(QString)));
    QObject::connect(m_webSocket, SIGNAL(connected()), this, SLOT(conectado()));
    QObject::connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(desconectado()));
    QObject::connect(m_webSocket, SIGNAL(sslErrors(const QList<QSslError>&)), this, SLOT(erro(const QList<QSslError>&)));
}

void RosBridge::conecta(string ip, unsigned short porta)
{
    m_webSocket->connectToHost(ip.c_str() , porta);
    qApp->processEvents(QEventLoop::WaitForMoreEvents);
}

void RosBridge::criaTopico(string nomeTopico, string tipoMsg)
{
    m_webSocket->write(QByteArray(ROSBridgeJSON::advertise(nomeTopico,tipoMsg).c_str()));
}

void RosBridge::publica(string nomeTopico, string msg)
{
    m_publicando = nomeTopico;
    m_webSocket->write(QByteArray(ROSBridgeJSON::publish(nomeTopico,msg).c_str()));
}

void RosBridge::escutaTopico(string nomeTopico)
{
    m_webSocket->write(QByteArray(ROSBridgeJSON::subscribe(nomeTopico).c_str()));
}

bool RosBridge::listaTopicos(list<string> &listaTopicos)
{
    string resp = consultaServico("/rosapi/topics");

    if(ROSBridgeJSON::JSONextraiCampoLista(resp,string("topics"),listaTopicos))
        return true;
    return false;
}

bool RosBridge::listaSevicos(list<string> &listaServicos)
{
    string resp = consultaServico("/rosapi/services");

    if(ROSBridgeJSON::JSONextraiCampoLista(resp,string("services"),listaServicos))
        return true;
    return false;
}

bool RosBridge::listaNodos(list<string> &listaNodos)
{
    string resp = consultaServico("/rosapi/nodes");

    if(ROSBridgeJSON::JSONextraiCampoLista(resp,string("nodes"),listaNodos))
        return true;
    return false;
}

bool RosBridge::listaParametros(list<string> &listaParametros)
{
    string resp = consultaServico("/rosapi/get_param_names");

    if(ROSBridgeJSON::JSONextraiCampoLista(resp,string("names"),listaParametros))
        return true;
    return false;
}

string RosBridge::msgTopico(string nomeTopico)
{
    string resp = consultaServico("/rosapi/topic_type" );
/*
    if(ROSBridgeJSON::JSONextraiCampoLista(resp,string("names"),listaParametros))
        return true;
    return false;
*/
}

string RosBridge::detalheMsg(string msg)
{
}

/**
 * @brief
 *  Consulta um servico e retorna o JSON resposta
 * @param servico - Nome do servico
 * @param ok - true se obteve resposta, false caso contrario
 * @return string - JSON resposta do servico
 */
string RosBridge::consultaServico(string servico, string argumentos, bool *ok)
{
    // Faz a requisicao
    m_webSocket->write(QByteArray(ROSBridgeJSON::callService(servico.c_str()).c_str()));

    // Pega a resposta
    MensagemROS msg;
    int tentativa;

    for(tentativa = 0 ; tentativa < 10 ; tentativa++)
    {
        qApp->processEvents(QEventLoop::WaitForMoreEvents);

        msg = m_bufferServico.top();
        if(msg.tipoMsg() == SERVICE_RESPONSE && msg.origem() == servico)
        {
            m_bufferServico.pop();
            if(ok != 0x0)
                *ok = true;

            return msg.msg();
        }
    }
    if(ok != 0x0)
        *ok = false;

    return string();
}

void RosBridge::adicionaEscuta(EscutaRosBridge *escuta)
{
    m_escutas.push_back(escuta);
}

void RosBridge::removeEscuta(EscutaRosBridge *escuta)
{
    m_escutas.remove(escuta);
}

void RosBridge::trocaEstado(QAbstractSocket::SocketState estado)
{
    switch (estado)
    {
        case QAbstractSocket::UnconnectedState:
            cout << "Estado trocado " << "Unconnected" << endl;
            break;
        case QAbstractSocket::HostLookupState:
            cout << "Estado trocado " << "HostLookup" << endl;
            break;
        case QAbstractSocket::ConnectingState:
            cout << "Estado trocado " << "Connecting" << endl;
            break;
        case QAbstractSocket::ConnectedState:
            cout << "Estado trocado " << "Connected" << endl;
            break;
        case QAbstractSocket::BoundState:
            cout << "Estado trocado " << "Bound" << endl;
            break;
        case QAbstractSocket::ClosingState:
            cout << "Estado trocado " << "Closing" << endl;
            break;
        case QAbstractSocket::ListeningState:
            cout << "Estado trocado " << "Listening" << endl;
            break;
        default:
            cout << "Estado trocado " << "Unknown" << endl;
            break;
    }
}

void RosBridge::recebidoMensagem(QString msg)
{
    MensagemROS ROSmsg(msg.toStdString());

    if(ROSmsg.tipoMsg() == SERVICE_RESPONSE)
        m_bufferServico.push(ROSmsg);
    else if(ROSmsg.tipoMsg() == PUBLISHER)
    {
        // Elimina msgs publisher enviada por mim (evita loop inifinito de publish)
        if(ROSmsg.origem().find(m_publicando) == 1 || ROSmsg.origem() == m_publicando)
        {
            m_publicando = "";
            return;
        }

        m_bufferTopico.push(ROSmsg);

        list<EscutaRosBridge*>::iterator i;
        for( i = m_escutas.begin() ; i != m_escutas.end() ; i++)
        {
            (*i)->recebidoMsg(ROSmsg);
        }
    }

    cout << "de: " << ROSmsg.origem() << " msg " << ROSmsg.msg() << endl;
}

void RosBridge::conectado()
{
    cout << "Conectado" << endl;

    list<EscutaRosBridge*>::iterator i;
    for( i = m_escutas.begin() ; i != m_escutas.end() ; i++)
    {
        (*i)->conectado();
    }
}

void RosBridge::desconectado()
{
    cout << "Desconectado" << endl;
    list<EscutaRosBridge*>::iterator i;
    for( i = m_escutas.begin() ; i != m_escutas.end() ; i++)
    {
        (*i)->desconectado();
    }
}

void RosBridge::erro(const QList<QSslError> &erros)
{
    cout << "Erro" << endl;
}


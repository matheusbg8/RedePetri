#ifndef ROSBRIDGE_H
#define ROSBRIDGE_H

#include <QObject>
#include "QtWebsocket/QTlsServer.h"
#include <string>
#include <list>
#include "EscutaRosBridge.h"
#include "ROSBridge/MensagemROS.h"
#include "FilaCircular.h"

using namespace std;

class RosBridge: public QObject
{

    Q_OBJECT

protected:

    QtWebsocket::QWsSocket* m_webSocket;
    list<EscutaRosBridge*> m_escutas;

    FilaCircular <MensagemROS> m_bufferServico;
    FilaCircular <MensagemROS> m_bufferTopico;

    string m_publicando;
public:
    RosBridge(QObject *QObjPai = 0x0);

    void conecta(string ip, unsigned short porta);

    void criaTopico(string nomeTopico, string tipoMsg);
    void publica(string nomeTopico, string msg);
    void escutaTopico(string nomeTopico);

    bool listaTopicos(list<string> &listaTopicos);
    bool listaSevicos(list<string> &listaServicos);
    bool listaNodos(list<string> &listaNodos);
    bool listaParametros(list<string> &listaParametros);
    string msgTopico(string nomeTopico);
    string detalheMsg(string msg);

    string consultaServico(string servico, string argumentos = "", bool *ok = 0x0);

    void adicionaEscuta(EscutaRosBridge * escuta);
    void removeEscuta(EscutaRosBridge *escuta);

protected slots:
    void trocaEstado(QAbstractSocket::SocketState estado);
    void recebidoMensagem(QString msg);
    void conectado();
    void desconectado();
    void erro(const QList<QSslError>& erros);
};

#endif // ROSBRIDGE_H


/*
#include <QtGui/QApplication>
#include "ROSBridge/ROSBridge.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RosBridge r;
    r.conecta("ws://localhost",9090);
    a.processEvents();

    r.criaTopico("/matheus", "std_msgs/String");
    r.escutaTopico("/matheus");

    for(int i = 0 ; i < 20 ; i++)
    {
        r.publica("/matheus", QString("{\"data\":\"msg %1\"}").arg(i).toStdString());
        r.listaTopicos();
        a.processEvents();
        sleep(1);
    }
    a.processEvents();
}
*/

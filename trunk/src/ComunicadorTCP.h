#ifndef COMUNICADORTCP_H
#define COMUNICADORTCP_H

#include <QTcpSocket>
#include <sstream>
#include <QMutex>
#include <list>

#include "EscutaComunicadorTCP.h"

using namespace std;

class ComunicadorTCP:
        public QObject
{
    Q_OBJECT
protected:
    QTcpSocket m_socket;
    QByteArray m_dadosRecebidos;
    std::stringstream m_bufferReceber;
    std::stringstream m_bufferEnviar;
    QMutex m_mutex;
    list<EscutaComunicadorTCP*> m_escutas;

public:
    ComunicadorTCP();

    bool conecta( const char *host , unsigned porta);

    istream &recebe();
    ostream &envia();

    void enviaPacote();

    bool esperaReceber();

    bool conectado();

    void adcionaEscuta(EscutaComunicadorTCP * escuta);
    void removeEscuta(EscutaComunicadorTCP *escuta);
public slots:
    void trataRecepcaoDados();
    void conexaoPerdida();

};

#endif // COMUNICADORTCP_H





//// Teste do comunicador TCP

//#include "ComunicadorTCP.h"

//int main()
//{
//    ComunicadorTCP c;

//    c.conecta("localhost", 12345);

//    while(c.esperaReceber())
//    {
//        string msg;

//        c.recebe() >> msg;
//        cout << "Mensagem recebida:" << msg << endl;

//        if(msg == "soma")
//        {
//            float a, b;
//            c.recebe() >> a >> b;
//            cout << "Calculando " << a << " + " << b << endl;
//            c.envia() << "Resposta " << a + b;
//        }else
//        if(msg == "subtrai")
//        {
//            float a, b;
//            c.recebe() >> a >> b;
//            c.envia() << "Resposta " << a - b;
//        }else
//        if(msg == "divide")
//        {
//            float a, b;
//            c.recebe() >> a >> b;
//            c.envia() << "Resposta " << a / b;
//        }else
//        if(msg == "multiplica")
//        {
//            float a, b;
//            c.recebe() >> a >> b;
//            c.envia() << "Resposta " << a * b;
//        }
//        c.enviaPacote();
//    }
//}

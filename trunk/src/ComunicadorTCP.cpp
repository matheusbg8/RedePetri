#include "ComunicadorTCP.h"

#include <iostream>

using namespace std;

ComunicadorTCP::ComunicadorTCP()
{
    connect(&m_socket, SIGNAL(readyRead()), SLOT(trataRecepcaoDados()));
    connect(&m_socket, SIGNAL(connected()), SLOT(conexaoPerdida()));
}

bool ComunicadorTCP::conecta(const char * host, unsigned porta)
{

    m_socket.connectToHost(host , porta);


    if(m_socket.waitForConnected())
    {
//        m_socket.write(QByteArray("Olaa!"));
    }
}

istream &ComunicadorTCP::recebe()
{
    // Verifica se precisa reseta o buffer
    if(m_bufferReceber.eof())
    {
        m_bufferReceber.str( std::string() );
        m_bufferReceber.clear();
    }

    // Atualiza o buffer com os dados recebidos
    m_mutex.lock();
    m_bufferReceber << m_dadosRecebidos.constData();
    m_dadosRecebidos.clear();
    m_mutex.unlock();

    // Retorna o buffer de dados
    return m_bufferReceber;
}

ostream &ComunicadorTCP::envia()
{
    return m_bufferEnviar;
}

void ComunicadorTCP::enviaPacote()
{
    string enviar = m_bufferEnviar.str();
    m_bufferEnviar.str( std::string() );
    m_bufferEnviar.clear();

    if(! conectado() ) return;
    m_socket.write(enviar.c_str(), enviar.size());
}

bool ComunicadorTCP::esperaReceber()
{
    return m_socket.waitForReadyRead();
}

bool ComunicadorTCP::conectado()
{
    return m_socket.state() == QAbstractSocket::ConnectedState;
}

void ComunicadorTCP::adcionaEscuta(EscutaComunicadorTCP *escuta)
{
    m_escutas.push_back(escuta);
}

void ComunicadorTCP::removeEscuta(EscutaComunicadorTCP *escuta)
{
    m_escutas.remove(escuta);
}

void ComunicadorTCP::trataRecepcaoDados()
{
    /// @todo - Usar direito os mutex, de uma forma que eles sejam uteis!
    m_mutex.lock();
    m_dadosRecebidos = m_socket.readAll();
    cout << "Recebido " << m_dadosRecebidos.constData() << endl;
    m_mutex.unlock();

    // Avisa escutas
    list<EscutaComunicadorTCP*>::iterator i;
    for( i = m_escutas.begin() ; i != m_escutas.end() ; i++)
    {
        (*i)->novaMensagem(recebe());
    }
}

void ComunicadorTCP::conexaoPerdida()
{
    // Avisa escutas
    list<EscutaComunicadorTCP*>::iterator i;
    for( i = m_escutas.begin() ; i != m_escutas.end() ; i++)
    {
        (*i)->conexaoPerdida();
    }
}

#include "WebSocket.h"
#include <iostream>

using namespace std;

WebSocket::WebSocket()
{
    m_comunicadorTCP.adcionaEscuta(this);
    m_comunicadorTCP.conecta("localhost", 12344);
}

void WebSocket::handshake()
{
    m_comunicadorTCP.envia() <<
    "GET / HTTP/1.1\nHost: localhost:12344\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:25.0) Gecko/20100101 Firefox/25.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\nAccept-Language: en-us,en;q=0.8,pt-br;q=0.5,pt;q=0.3\nAccept-Encoding: gzip, deflate\nDNT: 1\nSec-WebSocket-Version: 13\nOrigin: null\nSec-WebSocket-Key: 9x0sFStTxYDSqhGPhVCkJA==\nConnection: keep-alive, Upgrade\nPragma: no-cache\nCache-Control: no-cache\nUpgrade: websocket\n";
    m_comunicadorTCP.enviaPacote();
}

void WebSocket::novaMensagem(istream &msg)
{
    string s, strmsg;

    while(!msg.eof())
    {
        msg >> s;
        strmsg+= s;
    }
    cout << endl << endl<< strmsg << endl << endl;
}

void WebSocket::conexaoPerdida()
{
}

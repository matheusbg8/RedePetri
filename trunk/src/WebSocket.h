#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include "ComunicadorTCP.h"

class WebSocket: public EscutaComunicadorTCP
{
    ComunicadorTCP m_comunicadorTCP;

public:
    WebSocket();

    void handshake();

    void novaMensagem(istream &msg);
    void conexaoPerdida();
};

#endif // WEBSOCKET_H

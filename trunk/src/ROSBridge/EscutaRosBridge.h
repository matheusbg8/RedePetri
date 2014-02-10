#ifndef ESCUTAROSBRIDGE_H
#define ESCUTAROSBRIDGE_H

#include "MensagemROS.h"
class EscutaRosBridge
{
public:

    virtual void conectado() = 0;
    virtual void desconectado() = 0;
    virtual void recebidoMsg(const MensagemROS & msg) = 0;
};

#endif // ESCUTAROSBRIDGE_H

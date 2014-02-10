#ifndef MENSAGEMROS_H
#define MENSAGEMROS_H

#include <string>
using namespace std;

enum TipoMsgROS
{
    PUBLISHER,
    SERVICE_RESPONSE,
    INDEEFINIDO
};

class MensagemROS
{
protected:
    TipoMsgROS m_tipoMsg;
    string m_msg;
    string m_origem;
    void inicia();

public:
    MensagemROS();
    MensagemROS(const string &msgJSON);

    TipoMsgROS tipoMsg() const;
    const string msg() const;
    const string &origem() const;


};

#endif // MENSAGEMROS_H

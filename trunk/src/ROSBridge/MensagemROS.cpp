#include "MensagemROS.h"
#include "ROSBridgeJSON.h"
#include <iostream>

void MensagemROS::inicia()
{
    m_tipoMsg = INDEEFINIDO;
    m_msg = "";
    m_origem = "";
}

MensagemROS::MensagemROS()
{
    inicia();
}

MensagemROS::MensagemROS(const string &msg)
{
    inicia();

    bool ok;
    string strOP = ROSBridgeJSON::JSONextraiCampoSTR(msg,string("op"),&ok);

    if(!ok)
    {
        cout << "Erro ao intepretar msgROS , op nao encontrado" << endl;
        return;
    }

    if(strOP == "publish")
    {
        m_tipoMsg = PUBLISHER;
        m_origem = ROSBridgeJSON::JSONextraiCampoSTR(msg,string("topic"));
        m_msg = ROSBridgeJSON::JSONextraiCampoJSON(msg,string("msg"));
    }else if( strOP == "service_response")
    {
        m_tipoMsg = SERVICE_RESPONSE;
        m_origem = ROSBridgeJSON::JSONextraiCampoSTR(msg,string("service"));
        m_msg = ROSBridgeJSON::JSONextraiCampoJSON(msg,string("values"));
    }else
    {
        cout << "Erro interpretar msg com op " << strOP << endl;
    }

}

TipoMsgROS MensagemROS::tipoMsg() const
{
    return m_tipoMsg;
}

const string MensagemROS::msg() const
{
    return m_msg;
}

const string& MensagemROS::origem() const
{
    return m_origem;
}

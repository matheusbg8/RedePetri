#include "ROSBridgeJSON.h"

#include <cstdio>

int ROSBridgeJSON::encontraFimBloco(int posIni, char abreBloco, char fechaBloco, const string &str)
{
    int numBlocos = 0, i;
    char c;

    for(i = posIni ; i < str.size() ; ++i)
    {
        c = str.at(i);
        if(c == abreBloco) break;
    }

    for( ; i < str.size() ; i++)
    {
        c = str.at(i);
        if(c == abreBloco)
            numBlocos ++;
        else if(c == fechaBloco)
            numBlocos --;

        if(numBlocos == 0)
            return i;
    }
    return i;
}

string ROSBridgeJSON::advertise(string nomeTopico, string tipo, string id)
{
/*
{ "op": "advertise",
  (optional) "id": <string>,
  "topic": <string>,
  "type": <string>
}
*/
    char r[1024];
    if(id != "")
        sprintf(r , "{\"op\":\"advertise\",\"id\":\"%s\",\"topic\":\"%s\",\"type\":\"%s\"}", id.c_str() , nomeTopico.c_str() , tipo.c_str() );
    else
        sprintf(r , "{\"op\":\"advertise\",\"topic\":\"%s\",\"type\":\"%s\"}", nomeTopico.c_str(), tipo.c_str());
    return string(r);
}

string ROSBridgeJSON::unadvertise(string nomeTopico, string id)
{
/*
{ "op": "unadvertise",
  (optional) "id": <string>,
  "topic": <string>
}
*/
    char r[1024];
    if(id != "")
        sprintf(r , "{\"op\":\"unadvertise\",\"id\":\"%s\",\"topic\":\"%s\"}", id.c_str() , nomeTopico.c_str());
    else
        sprintf(r , "{\"op\":\"unadvertise\",\"topic\":\"%s\"}", nomeTopico.c_str());
    return string(r);
}

string ROSBridgeJSON::publish(string nomeTopico, string msg, string id)
{
/*
{ "op": "publish",
  (optional) "id": <string>,
  "topic": <string>,
  "msg": <json>
}
*/
    char r[1024];
    if(id != "")
        sprintf(r , "{\"op\":\"publish\",\"id\":\"%s\",\"topic\":\"%s\",\"msg\":%s}", id.c_str() , nomeTopico.c_str(), msg.c_str());
    else
        sprintf(r , "{\"op\":\"publish\",\"topic\":\"%s\",\"msg\":%s}",nomeTopico.c_str(), msg.c_str());
    return string(r);
}

string ROSBridgeJSON::subscribe(string nomeTopico, string id)
{
/*
{ "op": "subscribe",
  (optional) "id": <string>,
  "topic": <string>,
  (optional) "type": <string>,
  (optional) "throttle_rate": <int>,
  (optional) "queue_length": <int>,
  (optional) "fragment_size": <int>,
  (optional) "compression": <string>
}
*/

    char r[1024];
    if(id != "")
        sprintf(r , "{\"op\":\"subscribe\",\"id\":\"%s\",\"topic\":\"%s\"}", id.c_str() , nomeTopico.c_str());
    else
        sprintf(r , "{\"op\":\"subscribe\",\"topic\":\"%s\"}",nomeTopico.c_str());
    return string(r);
}

string ROSBridgeJSON::unsubscribe(string nomeTopico, string id)
{
/*
{ "op": "unsubscribe",
  (optional) "id": <string>,
  "topic": <string>
}
*/
    char r[1024];
    if(id != "")
        sprintf(r , "{\"op\":\"unsubscribe\",\"id\":\"%s\",\"topic\":\"%s\"}", id.c_str() , nomeTopico.c_str());
    else
        sprintf(r , "{\"op\":\"unsubscribe\",\"topic\":\"%s\"}", nomeTopico.c_str());
    return string(r);
}

string ROSBridgeJSON::callService(string nomeServico, string argumentos,string id)
{
/*
{ "op": "call_service",
  (optional) "id": <string>,
  "service": <string>,
  (optional) "args": <list<json>>,
  (optional) "fragment_size": <int>,
  (optional) "compression": <string>
}
*/
    char r[1024];
    if(argumentos != "")
        sprintf(r , "{\"op\":\"call_service\",\"id\":\"%s\",\"service\":\"%s\",\"args\":\"%s\"}", id.c_str() , nomeServico.c_str(), argumentos.c_str());
    else
        sprintf(r , "{\"op\":\"call_service\",\"service\":\"%s\"}", nomeServico.c_str());
    return string(r);
}

string ROSBridgeJSON::JSONextraiCampoSTR(const string &json, const string &campo, bool *ok)
{
    int op = json.find("\"" + campo + "\"");
    string resp;

    if(op < 0)
    {
        if(ok != 0x0)
            *ok = false;
    }else
    {
        int ini = json.find('\"', op + campo.size() + 2)+1,
            fim = json.find('\"', ini);
        resp = json.substr(ini,fim-ini);

        if(ok != 0x0)
            *ok = true;
    }

    return resp;
}

string ROSBridgeJSON::JSONextraiCampoJSON(const string &json, const string &campo, bool *ok)
{
    int op = json.find("\"" + campo + "\"");
    string resp;

    if(op < 0)
    {
        if(ok != 0x0)
            *ok = false;
    }else
    {
        int ini = json.find('{', op + campo.size() + 2),
            fim = encontraFimBloco(ini , '{', '}',json);
        ini++; // tira o {
        resp = json.substr(ini,fim-ini);

        if(ok != 0x0)
            *ok = true;
    }
    return resp;
}

bool ROSBridgeJSON::JSONextraiCampoLista(const string &json, const string &campo, list<string> &lista)
{
    int op = json.find("\"" + campo + "\"");
    string resp;

    if(op < 0)
        return false;

    int ini = json.find('[', op + campo.size() + 2),
        fim = encontraFimBloco(ini,'[', ']',json), k;

    ini = json.find('\"', ini)+1;
    while( ( k = json.find('\"', ini) ) > 0 && k < fim )
    {
        lista.push_back(json.substr(ini, k - ini));
        ini = json.find('\"', k +1)+1;
    }
    return true;
}

string ROSBridgeJSON::JSONextraiCampoBool(const string &json, const string &campo, bool *ok)
{
    int op = json.find("\"" + campo + "\"");
    string resp;

    if(op < 0)
    {
        if(ok != 0x0)
            *ok = false;
    }else
    {
        int ini = json.find(":",op + campo.size() + 2)+1,
            fim1 = json.find("{",ini),
            fim2 = json.find(",",ini);

        if(fim2 != -1 && fim2 < fim1)
            fim1 = fim2;

        resp = json.substr(ini,fim1-ini);

        if(ok != 0x0)
            *ok = true;
    }
    return resp;
}

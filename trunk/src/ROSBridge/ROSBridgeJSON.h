#ifndef ROSBRIDGEJASON_H
#define ROSBRIDGEJASON_H

#include <string>
#include <list>
using namespace std;


class ROSBridgeJSON
{
private:
    ROSBridgeJSON(){};

    static int encontraFimBloco(int posIni, char abreBloco, char fechaBloco, const string &str);

public:

    static string advertise(string nomeTopico,  string tipo, string id = "");
    static string unadvertise(string nomeTopico, string id);
    static string publish(string nomeTopico, string msg, string id = "");
    static string subscribe(string nomeTopico, string id = "");
    static string unsubscribe(string nomeTopico, string id = "");
    static string callService(string nomeServico, string argumentos = "",string id= "");

    static string JSONextraiCampoSTR(const string& json, const string& campo, bool *ok = 0x0);
    static string JSONextraiCampoJSON(const string& json, const string& campo, bool *ok = 0x0);
    static bool JSONextraiCampoLista(const string& json, const string& campo, list<string> &lista);
    static string JSONextraiCampoBool(const string& json, const string& campo, bool *ok = 0x0);

/* Ideia mini biblioteca para gravar jason
     ObjetoJSON
     ob << JSON << PARAM("papapa") << LISTA <<

     LISTA << LISTA = LISTA
     LISTA << OP = LISTA
     JSON << PARAM = JSON
     JSON << LISTA = JSON
     JSON << OP = INVALIDO
     PARAN << OP
*/
};

#endif // ROSBRIDGEJASON_H

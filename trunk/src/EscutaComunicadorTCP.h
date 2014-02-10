#ifndef ESCUTACOMUNICADORTCP_H
#define ESCUTACOMUNICADORTCP_H

#include <istream>
using namespace std;

class EscutaComunicadorTCP
{
public:

    virtual void novaMensagem(std::istream &msg) = 0;
    virtual void conexaoPerdida() = 0;
};

#endif // ESCUTACOMUNICADORTCP_H

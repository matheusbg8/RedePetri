#ifndef LUGAR_H
#define LUGAR_H

#include <string>
#include <vector>

using namespace std;

#include "ComponentePetri.h"
class RedePetri;

class Lugar : public ComponentePetri
{
private:
    short int grau;
    int lID; /**< ID local do Lugar */
    string nome;
    vector<string> fichas;  /**< Informação de cada ficha */

    // Implementação da interface ComponentePetri
    TipoComponentePetri meuTipoComponentePetri();

public:

    Lugar(const Lugar &P);
    Lugar(int IDGlobal = -1, int IDLocal= -1);

    int getIDLocal() const;

    friend class RedePetri;
};



#endif // LUGAR_H

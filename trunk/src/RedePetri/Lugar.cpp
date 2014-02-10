#include "RedePetri.h"
#include "Lugar.h"


TipoComponentePetri Lugar::meuTipoComponentePetri()
{
    return LUGAR;
}

Lugar::Lugar(const Lugar &P)
{
    lID = P.lID;
    grau = P.grau;
}

Lugar::Lugar(int IDGlobal, int IDLocal):
    ComponentePetri(IDGlobal)
{
    lID = IDLocal;
    grau = 0;
}

int Lugar::getIDLocal() const
{
    return lID;
}

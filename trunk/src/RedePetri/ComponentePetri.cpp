#include "ComponentePetri.h"

ComponentePetri::ComponentePetri(int IDGlobal)
{
    gID = IDGlobal;
}

ComponentePetri::~ComponentePetri()
{
    //Destrutor virtual necessario para chama de destrutores derivados
}

int ComponentePetri::getIDGlobal() const
{
    return gID;
}

TipoComponentePetri ComponentePetri::tipo()
{
    return meuTipoComponentePetri();
}

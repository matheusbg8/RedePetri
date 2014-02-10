#include "Transicao.h"

TipoComponentePetri Transicao::meuTipoComponentePetri()
{
    return TRANSICAO;
}

Transicao::Transicao(const Transicao &T)
{
    Sensibilizado = T.Sensibilizado;
    Ciclo_Sensibilizado = T.Ciclo_Sensibilizado;

    Desenhado = T.Desenhado;
    grau = T.grau;

    lID = T.lID;

    CondVal = T.CondVal;
    CondVar = T.CondVar;

    AcaoVal = T.AcaoVal;
    AcaoVar = T.AcaoVar;
}

Transicao::Transicao(int IDGlobal, int IDLocal):
    ComponentePetri(IDGlobal)
{
    Sensibilizado = false;
    Ciclo_Sensibilizado = -1;
    Desenhado = false;
    grau = 0;
    lID = IDLocal;
}

int Transicao::getIDLocal() const
{
    return lID;
}

string Transicao::getNome()
{
    return nome;
}

void Transicao::setNome(string nome)
{
    this->nome = nome;
}

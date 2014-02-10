#include "ComunicadorRedePetri.h"

ComunicadorRedePetri::ComunicadorRedePetri(const char *ip, int porta)
{
    m_comunicador.conecta(ip, porta);
}

ComunicadorRedePetri::ComunicadorRedePetri()
{
    m_comunicador.conecta("localhost", 12345);
}

void ComunicadorRedePetri::dNovoLugar(unsigned id)
{
    m_comunicador.envia() << "NovoLugar " << id;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dNovaTransicao(unsigned id)
{
    m_comunicador.envia() << "NovoTransicao " << id;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso)
{
    m_comunicador.envia() << "NovoArcoPT " << id << ' ' << de << ' ' << para << ' ' << peso;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso)
{
    m_comunicador.envia() << "NovoArcoTP " << id << ' ' << de << ' ' << para << ' ' << peso;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dDeletaTransicao(unsigned id)
{
    m_comunicador.envia() << "DeletaTransicao " << id;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dDeletaLugar(unsigned id)
{
    m_comunicador.envia() << "DeletaLugar " << id;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dDeletaArco(unsigned id)
{
    m_comunicador.envia() << "DeletaArco " << id;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dSetPesoArco(unsigned id, unsigned peso)
{
    m_comunicador.envia() << "SetPesoArco " << id << ' ' << peso;
    m_comunicador.enviaPacote();
}

void ComunicadorRedePetri::dSetFichas(unsigned id, unsigned numFichas)
{
    m_comunicador.envia() << "SetFichas " << id << ' ' << numFichas;
    m_comunicador.enviaPacote();
}

unsigned ComunicadorRedePetri::dPesoArco(unsigned id)
{
    return 0;
}

unsigned ComunicadorRedePetri::dFichas(unsigned id)
{
    return 0;
}

void ComunicadorRedePetri::dExecutaTransicao(unsigned id)
{
    m_comunicador.envia() << "ExecutaTransicao " << id ;
    m_comunicador.enviaPacote();
}

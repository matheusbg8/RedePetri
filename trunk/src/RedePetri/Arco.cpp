#include "RedePetri.h"

#include "Arco.h"

Arco::Arco(RedePetri *rede, TipoArco tipoArco, unsigned de, unsigned para, unsigned peso)
{
    m_rede = rede;
    m_para = para;
    m_de = de;
    m_peso = peso;
    m_tipo = tipoArco;
}

void Arco::setPeso(unsigned peso)
{
    m_peso = peso;
}

bool Arco::setRede(RedePetri *rede)
{
    m_rede = rede;
}

bool Arco::setID(unsigned id)
{
    m_id = id;
}

void Arco::setArco(TipoArco tipo, unsigned de, unsigned para, unsigned peso)
{
    m_tipo = tipo;
    m_de = de;
    m_para = para;
}

unsigned Arco::id() const
{
    return m_id;
}

unsigned Arco::de() const
{
    return m_de;
}

unsigned Arco::para() const
{
    return m_para;
}

unsigned Arco::peso() const
{
    return m_peso;
}

TipoArco Arco::tipo() const
{
    return m_tipo;
}

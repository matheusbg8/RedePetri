#include "sinal.h"

Sinal::Sinal(TipoSinal tipo , Desenho *origem)
{
    m_tipo = tipo;
    m_origem = origem;
}

TipoSinal Sinal::tipo() const
{
    return m_tipo;
}

Desenho *Sinal::origem() const
{
    return m_origem;
}

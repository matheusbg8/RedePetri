#include "Evento.h"
#include "Desenho.h"

Evento::Evento(Desenho *desenhoOrigem, const TipoEvento &tipoEvento)
{
    m_desenhoOrigem = desenhoOrigem;
    m_tipoEvento = tipoEvento;
}

TipoEvento Evento::tipoEvento() const
{
    return m_tipoEvento;
}

Desenho *Evento::desenhoOrigem() const
{
    return m_desenhoOrigem;
}

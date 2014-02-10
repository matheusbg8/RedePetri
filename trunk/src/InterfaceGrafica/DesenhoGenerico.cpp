#include "DesenhoGenerico.h"

DesenhoGenerico::DesenhoGenerico(Desenho *desenho, int idTipoDesenho)
{
    m_desenho = desenho;
    m_tipoDesenho = idTipoDesenho;
}


int DesenhoGenerico::faixaIndexacao() const
{
    return m_faixaIndexacao;
}

void DesenhoGenerico::setFaixaIndexacao(int faixaIndexacao)
{
    m_faixaIndexacao = faixaIndexacao;
}

int DesenhoGenerico::tipoDesenho() const
{
    return m_tipoDesenho;
}

void DesenhoGenerico::setTipoDesenho(int idTipoDesenho)
{
    m_tipoDesenho = idTipoDesenho;
}

Desenho *DesenhoGenerico::novaInstancia() const
{
    if(m_desenho != 0x0)
        return m_desenho->novaInstancia();
    return 0x0;
}

Desenho *DesenhoGenerico::desenho()
{
    return m_desenho;
}

const Desenho *DesenhoGenerico::desenho() const
{
    return m_desenho;
}

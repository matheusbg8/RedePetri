#ifndef EVENTO_H
#define EVENTO_H

class Desenho;

enum TipoEvento
{
    EVENTO_INVALIDO,
    EVENTO_ALTERACAO_POSICAO,
    EVENTO_ALTERACAO_LARGRA,
    EVENTO_ALTERACAO_ALTURA,
    EVENTO_DELETANDO,
    EVENTO_ALTERACAO_SELECAO
};

class Evento
{
private:
    Desenho *m_desenhoOrigem;
    TipoEvento m_tipoEvento;

public:
    Evento(Desenho *desenhoOrigem,const TipoEvento &tipoEvento);

    TipoEvento tipoEvento() const;
    Desenho * desenhoOrigem() const;
};

#endif // EVENTO_H

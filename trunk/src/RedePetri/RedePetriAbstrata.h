#ifndef REDEPETRIABSTRATA_H
#define REDEPETRIABSTRATA_H


/**
 * @brief
 *  Esta classe é a interface de todas
 * as redes de petri, e todas as suas visualizacoes
 */
class RedePetriAbstrata
{
public:
    virtual unsigned novoArcoPT(unsigned de , unsigned para, unsigned peso) = 0;
    virtual unsigned novoArcoTP(unsigned de , unsigned para, unsigned peso) = 0;
    virtual unsigned novaTransicao() = 0;
    virtual unsigned novoLugar() = 0;
    virtual unsigned setFichas(unsigned idLugar) = 0;

    virtual bool removeArco(unsigned id) = 0;
    virtual bool removeArcoPT(unsigned de, unsigned para) = 0;
    virtual bool removeArcoTP(unsigned de, unsigned para) = 0;
};

#endif // REDEPETRIABSTRATA_H

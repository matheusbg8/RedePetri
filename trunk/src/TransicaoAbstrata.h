#ifndef TRANSICAOABSTRATA_H
#define TRANSICAOABSTRATA_H

class TransicaoAbstrata
{
public:
    TransicaoAbstrata();

    virtual bool avaliaCondicao() = 0;
    virtual bool executaAcao() = 0;

};

#endif // TRANSICAOABSTRATA_H

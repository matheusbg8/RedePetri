#ifndef DESENHODELIGACAO_H
#define DESENHODELIGACAO_H


#include "Desenho.h"

/**
 * @brief
 *  Interface de todos desenhos que permitem
 * estabelecer uma ligacao entre dois desenhos
 */
class DesenhoDeLigacao
{
public:

    virtual bool setLigacaoIni(Desenho *desenho) = 0;
    virtual bool setLigacaoFim(Desenho *desenho) = 0;

    virtual const Desenho* getLigacaoIni() const = 0;
    virtual const Desenho* getLigacaoFim() const = 0;

};

#endif // DESENHODELIGACAO_H

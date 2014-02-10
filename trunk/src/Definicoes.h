#ifndef DEFINICOES_H
#define DEFINICOES_H

#include "Ponto.h"
typedef Ponto<float> rPonto;

enum AcaoNovoDesenho
{
    ACEITA_NOVOS_DESENHOS,              // Aceita o novos desenhos
    NAO_ACEITA_NOVOS_DESENHOS,          // Não aceita novos desenhos (o desenho é desalocado e uma msg no terminal é gerada)
    PASSA_NOVO_DESENHO_PARA_DESENHO_PAI // Repassa o novo desenho para seu pai, se não existir pai, ocorre o mesmo que na acao de cima
};

enum Orientacao
{
    LESTE,
    SULDESTE,
    SUL,
    SULDOESTE,
    OESTE,
    NOROESTE,
    NORTE,
    NORDESTE
};

#endif // DEFINICOES_H

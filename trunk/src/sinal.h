#ifndef SINAL_H
#define SINAL_H


class Desenho;
class Sinal;

enum TipoSinal {
    SINAL_INVALIDO,                /**< Sinal nulo, sem valor, indefinido */
    SINAL_ALTERACAO_POSICAO,       /**< Sinal que avisa quando a posicao foi alterada */
    SINAL_ALTERACAO_LARGURA,       /**< Sinal que avisa quando ocorre uma alteração de largura */
    SINAL_ALTERACAO_ALTURA,        /**< Sinal que avisa qunado ocorre uma alteração de posição */
    SINAL_ALTERACAO_SELECAO,        /**< Sinal que avisa qunado ocorre uma alteração de seleção */
    SINAL_DELETANDO                /**< Sinal que avisa quando o desenho esta sendo deletado */
};

#include "Desenho.h"

class Sinal
{
private:
    TipoSinal m_tipo;
    Desenho *m_origem;
public:

    Sinal(TipoSinal m_tipo = SINAL_INVALIDO, Desenho *m_origem = 0x0);

    TipoSinal tipo() const;
    Desenho * origem() const;
};

#endif // SINAL_H

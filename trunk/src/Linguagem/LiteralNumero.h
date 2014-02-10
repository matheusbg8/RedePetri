#ifndef LITERALNUMERO_H
#define LITERALNUMERO_H

#include "Literal.h"
#include "Automato.h"


/**
 * @brief
 *  Os literais númericos
 * são numeros de ponto flutuante
 * com sinal.
 *  Assim como todos os literais,
 * a contrução é realizada atraves
 * do livro de literais, onde possui
 * uma fábrica de cada literal do livro.
 *  O metodo para construi o literal
 * é novoLiteraL().

    @todo - Concertar problema com o sinal de subtração.
 */
class LiteralNumero : public Literal
{
private:
    LiteralNumero();

    static Automato *m_automato;
    static LiteralNumero* m_fabrica;

protected:
    float m_valor;

public:
    static LiteralNumero * fabrica();

    // Interface Literal
    TipoLiteral tipoLiteral() const;
    Literal * novoLiteral(istream &expressao) const;
    Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const;
    void imprime(ostream &os) const;

    Literal * novoLiteral(float valor);
    float valor() const;

};

#endif // LITERALNUMERO_H

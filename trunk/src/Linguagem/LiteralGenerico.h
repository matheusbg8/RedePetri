#ifndef LITERALGENERICO_H
#define LITERALGENERICO_H

#include "Literal.h"

#include "Automato.h"


enum TipoLiteralGenerico
{
    LITERAL_GENERICO_ABRE_PARENSES,
    LITERAL_GENERICO_FECHA_PARENSES
};

/**
 * @brief
 *  Os literais genericos, são literais
 * simples utilizados para delimitar
 * informações, como o abre e fecha
 * parenteses.
 *  Assim como todos os literais,
 * a contrução é realizada atraves
 * do livro de literais, onde possui
 * uma fábrica de cada literal do livro.
 *  O metodo para construi o literal
 * é novoLiteraL().
 */
class LiteralGenerico : public Literal
{
protected:
    TipoLiteralGenerico m_tipoGenerico;

    static Automato *m_automato;

    LiteralGenerico(TipoLiteralGenerico tipo = LITERAL_GENERICO_ABRE_PARENSES);
    static LiteralGenerico* m_fabrica;
public:
    static LiteralGenerico* fabrica();

    TipoLiteralGenerico tipoLiteralGenerico() const;

    // Interface Literal
    TipoLiteral tipoLiteral() const;
    Literal* novoLiteral(istream &expressao) const;
    Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const;
    void imprime(ostream &os) const;

};

#endif // LITERALGENERICO_H

#ifndef LITERALBOOLEANO_H
#define LITERALBOOLEANO_H

#include "Literal.h"
#include "Automato.h"

/**
 * @brief
 *  LiteralBooleano armazena um valor
 * booleano true ou false.
 *  Assim como todos os literais,
 * a contrução é realizada atraves
 * do livro de literais, onde possui
 * uma fábrica de cada literal do livro.
 *  O metodo para construi o literal
 * é novoLiteraL().
 */
class LiteralBooleano : public Literal
{
protected:
    bool m_valor;

    static Automato *m_automato;
    static LiteralBooleano* m_fabrica;
    LiteralBooleano(bool valor = false);
public:
    static LiteralBooleano *fabrica();

    LiteralBooleano* novoLiteral(bool valor = false);

    // Interface Literal
    TipoLiteral tipoLiteral() const;
    Literal * novoLiteral(istream &expressao) const;
    Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const;
    void imprime(ostream &os) const;

    bool valor();
};

#endif // LITERALBOOLEANO_H

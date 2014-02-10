#ifndef LITERALSTRING_H
#define LITERALSTRING_H

#include "Literal.h"
#include <string>
#include "Automato.h"

/**
 * @brief
 *  Os literais strings são
 * string definidas de forma
 * constante em uma expressão
 * entre aspas duplas.
 *  Assim como todos os literais,
 * a contrução é realizada atraves
 * do livro de literais, onde possui
 * uma fábrica de cada literal do livro.
 *  O metodo para construi o literal
 * é novoLiteraL().
 */
class LiteralString : public Literal
{
private:
    LiteralString();
    static Automato* m_automato;
    static LiteralString *m_fabrica;

protected:
    string m_valor;

public:
    static LiteralString* fabrica();

    const string& valor() const;

    // Interface Literal
    TipoLiteral tipoLiteral() const;
    Literal* novoLiteral(istream &expressao) const;
    Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const;
    void imprime(ostream &os) const;

    Literal* novoLiteral(string valor);
};

#endif // LITERALSTRING_H

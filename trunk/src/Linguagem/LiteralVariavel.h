#ifndef LITERALVARIAVEL_H
#define LITERALVARIAVEL_H

#include "Literal.h"
#include "Automato.h"

/**
 * @brief
 *  Os literais variaveis
 * são os nomes de veriaveis
 * utilizados em uma expressão.
 *  Assim como todos os literais,
 * a contrução é realizada atraves
 * do livro de literais, onde possui
 * uma fábrica de cada literal do livro.
 *  O metodo para construi o literal
 * é novoLiteraL().
 */
class LiteralVariavel : public Literal
{
private:
    LiteralVariavel();
    LiteralVariavel(string nome);
    static Automato* m_automato;
    static LiteralVariavel* m_fabrica;

protected:
    string m_nome;
public:
    static LiteralVariavel* fabrica();

    const string &nome() const;

    // Interface Literal
    TipoLiteral tipoLiteral() const;
    Literal* novoLiteral(istream &expressao) const;
    Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const;
    void imprime(ostream &os) const;

};

#endif // LITERALVARIAVEL_H

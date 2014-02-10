#ifndef LITERALOPERADOR_H
#define LITERALOPERADOR_H

#include <vector>
#include "Literal.h"
#include "Automato.h"
#include "Ambiente.h"

using namespace std;

enum TipoLiteralOperador
{
    OP_IGUAL,
    OP_DIFERENTE,
    OP_MAIOR,
    OP_MENOR,
    OP_MAIOR_IGUAL,
    OP_MENOR_IGUAL,
    OP_AND,
    OP_OR,
    OP_NEGADO,
    OP_SOMA,
    OP_SUBTRACAO,
    OP_MULTIPLICACAO,
    OP_DIVISAO,
    OP_ATRIBUICAO
};


/**
 * @brief
 *  Os litarais operadores represetam
 * todos tipos de operadores.
 *  Atualmente esta represemtando
 * apenas operadores de comparação
 *  Assim como todos os literais,
 * a contrução é realizada atraves
 * do livro de literais, onde possui
 * uma fábrica de cada literal do livro.
 *  O metodo para construi o literal
 * é novoLiteraL().
 */
class LiteralOperador : public Literal
{
private:
    LiteralOperador();
    static Automato* m_automato;
    static LiteralOperador* m_fabrica;

protected:
    TipoLiteralOperador m_operador;
    unsigned m_numArgumentos;

    // Resolucao de variave
    Literal *resolve(Literal* A);
    void desalocaLiteraisResolvidos();

public:
    static LiteralOperador* fabrica();

    TipoLiteralOperador operador() const;
    unsigned precedencia() const;
    unsigned numArgumentos();

    // Interface Literal
    TipoLiteral tipoLiteral() const;
    Literal* novoLiteral(istream &expressao) const;
    Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const;
    void imprime(ostream &os) const;

};

#endif // LITERALOPERADOR_H

#ifndef LITERAL_H
#define LITERAL_H

#include <sstream>
using namespace std;

enum TipoLiteral
{
    LITERAL,
    LITERAL_VARIAVEL,
    LITERAL_NUMERO,
    LITERAL_OPERADOR,
    LITERAL_STRING,
    LITERAL_GENERICO,
    LITERAL_BOOLEANO
};

// Alguns literais básicos
class LiteralGenerico;
class LiteralNumero;
class LiteralOperador;
class LiteralString;
class LiteralVariavel;
class LiteralBooleano;

/**
 * @brief
 *  Literais são utilizados para representar
 * os caracteres de uma expressão.
 *  Os literais estão divididos em:
 * Literais Genericos - Caracteres utilizados
 * apenas para marcação, são caracteres genericos
 * o abre parenteses e o fecha parenteses.
 * Literais Numericos - São caracteres que representão
 * um número.
 * Literais Operadores - São caracetres que representão
 * um operador, são operadores: == , != , >= , <=
 * > , < , && , || .
 * Literais String - São literais que representão uma
 * sequencia de caracteres constante em uma expressão,
 * as strings são representadas entre aspas duplas.
 * Literais Variaveis - São literais que representão
 * o nome de uma variavel.
 */
class Literal
{
public:
    Literal();

    // Interface
    virtual TipoLiteral tipoLiteral() const = 0;
    virtual Literal * novoLiteral(istream &expressao) const = 0;
    virtual Literal * novoLiteral(const char *expressao, unsigned *numCaractersLidos) const = 0;
    virtual void imprime(ostream &os) const = 0;

    // Reflections
    LiteralGenerico* getGenerico() const;
    LiteralNumero* getNumero() const;
    LiteralOperador* getOperador() const;
    LiteralString* getString() const;
    LiteralVariavel* getVariavel() const ;
    LiteralBooleano *getBooleano() const;

    void processa( string s);

};

ostream & operator << (ostream & os , const Literal *literal);



#endif // LITERAL_H

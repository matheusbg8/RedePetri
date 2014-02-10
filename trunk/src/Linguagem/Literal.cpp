#include "Literal.h"
#include <string>
#include <iostream>

Literal::Literal()
{
}

LiteralGenerico *Literal::getGenerico() const
{
    if(tipoLiteral() == LITERAL_GENERICO)
    {
        return (LiteralGenerico*) this;
    }
    return 0x0;
}

LiteralNumero *Literal::getNumero() const
{
    if(tipoLiteral() == LITERAL_NUMERO)
    {
        return (LiteralNumero*) this;
    }
    return 0x0;
}

LiteralOperador *Literal::getOperador() const
{
    if(tipoLiteral() == LITERAL_OPERADOR)
    {
        return (LiteralOperador*) this;
    }
    return 0x0;
}

LiteralString *Literal::getString() const
{
    if(tipoLiteral() == LITERAL_STRING)
    {
        return (LiteralString*) this;
    }
    return 0x0;
}

LiteralVariavel *Literal::getVariavel() const
{
    if(tipoLiteral() == LITERAL_VARIAVEL)
    {
        return (LiteralVariavel*) this;
    }
    return 0x0;
}

LiteralBooleano *Literal::getBooleano() const
{
    if(tipoLiteral() == LITERAL_BOOLEANO)
    {
        return (LiteralBooleano*) this;
    }
    return 0x0;
}

void Literal::processa(string s)
{
    stringstream is;
    is << s;

    string temp;
    float num;
    char c;

    while(!is.eof())
    {
        c = is.peek();
        // Se for uma string
        if(c == '\"')
        {
            // Tira aspas inicial
            is.get();
            is >> temp;
            // Tira aspas final
            temp.erase(temp.size()-1);

            cout << "String " << temp << endl;

         // Se for um numero
        }else if( c == '-' || (c >= '0' && c <= '9') )
        {
            is >> num;
            cout << "Num " << num << endl;

        // Se for um operador
        }else if( c == '=' || c == '>' || c == '<' || c == '|' || c == '&')
        {
            is >> temp;
            cout << "Operador " << temp << endl;
        // Se for uma variavel
        }else if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            is >> temp;
            cout << "Variavel " << temp << endl;
        }

        is.get();
    }
}


ostream & operator << (ostream & os , const Literal *literal)
{
    if(literal != 0x0)
        literal->imprime(os);
    else
        os << "Literal Invalido(0x0)";

    return os;
}

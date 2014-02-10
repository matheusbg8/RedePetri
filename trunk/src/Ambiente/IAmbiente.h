#ifndef IAMBIENTE_H
#define IAMBIENTE_H

#include "Literal.h"

class IAmbiente
{
public:
    IAmbiente();

    // Criacao do ambiente
    virtual unsigned variavel(const string &nome, const string &valor) = 0;
    virtual unsigned pergunta(const string &nome, const string &expressao) = 0;
    virtual unsigned acao(const string& nome, const string &instrucoes) = 0;

    virtual bool removeNodo(const string& nome) = 0;
    virtual bool removeNodo(unsigned id) = 0;

    // Execucao do ambiente
    virtual bool executaAcao(const string &nome) = 0;
    virtual bool executaAcao(unsigned id) = 0;

    // Avalia
    virtual bool avaliaPergunta(const string &nome) = 0;
    virtual bool avaliaPergunta(unsigned id) = 0;

    virtual Literal* avaliaVariavel(const string &nome) = 0;
    virtual Literal* avaliaVariavel(unsigned id) = 0;
};

#endif // IAMBIENTE_H

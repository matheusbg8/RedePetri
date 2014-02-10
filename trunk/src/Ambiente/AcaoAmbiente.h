#ifndef ACAOAMBIENTE_H
#define ACAOAMBIENTE_H

#include "NodoAmbiente.h"
#include "Linguagem/Expressao.h"

/**
 * @brief
 *  Uma ação no ambiente é um
 * evento que altera o ambiente,
 * realizando modificações nas
 * variaveis do ambiente ou
 * gerando um evento externo
 * gerando uma mudança no ambiente real.
 */
class AcaoAmbiente : public NodoAmbiente
{
protected:
    list<Expressao*> m_expressoes;
    string m_acao;
public:
    AcaoAmbiente(string nome, string acao);

    bool executaAcao(CAmbiente *ambiente);

    bool addExpressao(string expressao);

    TipoNodoAmbiente tipoNodo() const;

    const string& acao() const;
    const string& nome() const;

};

#endif // ACAOAMBIENTE_H

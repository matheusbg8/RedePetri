#ifndef PERGUTAAMBIENTE_H
#define PERGUTAAMBIENTE_H

#include "NodoAmbiente.h"
#include "Linguagem/Expressao.h"

class Ambiente;

#include<string>
using namespace std;


/**
 * @brief
 *  Uma pergunta do ambiente é uma ou mais expressões
 * lógicas sobre as variaveis do ambiente, que retornam
 * verdadeiro ou falso.
 */
class PerguntaAmbiente: public NodoAmbiente
{
protected:
    Expressao m_pergunta;
    string m_strPergunta; /// @todo - Tentar encontrar uma solucao melhor para expressao e pergunta (o mesmo em acaoAmbiente)

public:
    PerguntaAmbiente(string nome, string pergunta);
    bool verdade(CAmbiente *ambiente);

    bool setPergunta(string pergunta);

    TipoNodoAmbiente tipoNodo() const;

    const string& nome() const;
    const string& pergunta() const;
};

#endif // PERGUTAAMBIENTE_H

#include "PerguntaAmbiente.h"
#include "Ambiente.h"

PerguntaAmbiente::PerguntaAmbiente(string nome,string pergunta):
    NodoAmbiente(nome)
{
    m_pergunta.setExpressao(pergunta);
    m_strPergunta = pergunta;
}

/**
 * @brief
 *  Retorna true se a pergunta for verdade, false caso contrario
 * @return bool
 */
bool PerguntaAmbiente::verdade(CAmbiente* ambiente)
{
    // Se estou relacionado com um ambiente
    if(!possuiAmbiente())
        return false;

    return m_pergunta.avaliaExpressao(ambiente);
}

bool PerguntaAmbiente::setPergunta(string pergunta)
{
    if(m_pergunta.setExpressao(pergunta))
    {
        m_strPergunta = pergunta;
        return true;
    }
    return false;
}

TipoNodoAmbiente PerguntaAmbiente::tipoNodo() const
{
    return NODO_PERGUNTA;
}

const string &PerguntaAmbiente::nome() const
{
    return NodoAmbiente::nome();
}

const string &PerguntaAmbiente::pergunta() const
{
    return m_strPergunta;
}


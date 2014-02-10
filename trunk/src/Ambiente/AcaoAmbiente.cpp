#include "AcaoAmbiente.h"

AcaoAmbiente::AcaoAmbiente(string nome, string acao):
    NodoAmbiente(nome)
{
    m_acao = acao;
    addExpressao(acao);
}

bool AcaoAmbiente::executaAcao(CAmbiente *ambiente)
{
    bool executouTudo = true;
   list<Expressao*>::iterator ie;
   for(ie = m_expressoes.begin() ; ie != m_expressoes.end() ; ie++)
   {
       if(!(*ie)->avaliaExpressao(ambiente))
           executouTudo = false;
   }
    return executouTudo;
}

bool AcaoAmbiente::addExpressao(string expressao)
{
    Expressao *nova = new Expressao;
    if(nova->setExpressao(expressao))
    {
        m_expressoes.push_back(nova);
        return true;
    }
    delete nova;
    return false;
}

TipoNodoAmbiente AcaoAmbiente::tipoNodo() const
{
    return NODO_ACAO;
}

const string &AcaoAmbiente::acao() const
{
    return m_acao;
}

const string &AcaoAmbiente::nome() const
{
    return NodoAmbiente::nome();
}

#include "LiteralString.h"
#include <iostream>
using namespace std;


LiteralString::LiteralString()
{
    if(m_automato == 0x0)
    {
        ArestaAutomato * aresta = 0x0;
        m_automato = new Automato;

        m_automato->criaEstados(4);
        m_automato->setEstadoInicial(0);
        m_automato->addEstadoFinal(3);
        m_automato->addEstadoAceitacao(2);

        // Criando arestas
        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(0);
        aresta->setSimbulosAceitos(Automato::branco().c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(1);
        aresta->setSimbulosAceitos("\"");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(2);
        aresta->setSimbulosAceitos("\"");
        aresta->setNegado(true); // Nega resultado da aceitação
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(3);
        aresta->setSimbulosAceitos("\"");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(2);
        aresta->setPara(2);
        aresta->setSimbulosAceitos("\"");
        aresta->setNegado(true); // Nega resultado da aceitação
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(2);
        aresta->setPara(3);
        aresta->setSimbulosAceitos("\"");
        m_automato->addAresta(aresta);
    }
}

LiteralString * LiteralString::m_fabrica = 0x0;
Automato* LiteralString::m_automato = 0x0;

LiteralString *LiteralString::fabrica()
{
    if(m_fabrica == 0x0)
    {
        m_fabrica = new LiteralString();
    }
    return m_fabrica;
}

const string &LiteralString::valor() const
{
    return m_valor;
}

TipoLiteral LiteralString::tipoLiteral() const
{
    return LITERAL_STRING;
}

Literal *LiteralString::novoLiteral(istream &expressao) const
{
    char c = expressao.peek();
    LiteralString *resp = 0x0;

    if(c == '\"')
    {
        expressao.get(); // consome "

        string nome;

        c = expressao.get();
        while(c != '\"' && !expressao.eof())
        {
            nome += c;
            c = expressao.get();
        }

        // O /" já foi consumido no while

        resp = new LiteralString;
        resp->m_valor = nome;
    }
    return resp;
}

Literal *LiteralString::novoLiteral(const char *expressao, unsigned *numCaractersLidos) const
{
    string palavra;
    unsigned numCarac = 0;

    numCarac = m_automato->avalia(expressao , palavra);

    if(numCaractersLidos != 0x0)
        *numCaractersLidos = numCarac;

    if(numCarac > 0)
    {
        LiteralString *novo = new LiteralString;
        novo->m_valor = palavra;
        return novo;
    }
    return 0x0;
}

void LiteralString::imprime(ostream &os) const
{
    os << "LString \"" << m_valor << '\"';
}

Literal * LiteralString::novoLiteral(string valor)
{
    LiteralString *novo = new LiteralString;
    novo->m_valor = valor;
    return novo;
}


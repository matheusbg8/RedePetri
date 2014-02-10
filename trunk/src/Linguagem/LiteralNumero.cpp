#include "LiteralNumero.h"

LiteralNumero::LiteralNumero()
{
    if(m_automato == 0x0)
    {
        ArestaAutomato *aresta = 0x0;
        m_automato = new Automato;

        m_automato->criaEstados(4);
        m_automato->setEstadoInicial(0);
        m_automato->addEstadoFinal(1);
        m_automato->addEstadoFinal(2);
        m_automato->addEstadoAceitacao(1);
        m_automato->addEstadoAceitacao(2);
        m_automato->addEstadoAceitacao(3);

        // Criando arestas
        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(0);
        aresta->setSimbulosAceitos(Automato::branco().c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(1);
        aresta->setSimbulosAceitos((Automato::numeros()+"-").c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(1);
        aresta->setSimbulosAceitos(Automato::numeros().c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(2);
        aresta->setSimbulosAceitos(".");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(2);
        aresta->setPara(2);
        aresta->setSimbulosAceitos(Automato::numeros().c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(3);
        aresta->setSimbulosAceitos(".");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(3);
        aresta->setPara(2);
        aresta->setSimbulosAceitos(Automato::numeros().c_str());
        m_automato->addAresta(aresta);
    }
}

Automato* LiteralNumero::m_automato = 0x0;
LiteralNumero* LiteralNumero::m_fabrica = 0x0;

LiteralNumero *LiteralNumero::fabrica()
{
    if(m_fabrica == 0x0)
    {
        m_fabrica = new LiteralNumero();
    }
    return m_fabrica;
}

TipoLiteral LiteralNumero::tipoLiteral() const
{
    return LITERAL_NUMERO;
}

Literal *LiteralNumero::novoLiteral(istream &expressao) const
{
    char c = expressao.peek();

    if( c == '-' || (c >= '0' && c <= '9'))
    {

        float num;
        expressao >> num;
        LiteralNumero *resp = new LiteralNumero;
        resp->m_valor = num;
        return resp;
    }
    return 0x0;
}

Literal *LiteralNumero::novoLiteral(const char *expressao, unsigned *numCaractersLidos) const
{
    string palavra;
    unsigned numCarac = 0;

    numCarac = m_automato->avalia(expressao , palavra);

    if(numCaractersLidos != 0x0)
        *numCaractersLidos = numCarac;

    if(numCarac > 0)
    {
        LiteralNumero *novo = new LiteralNumero;
        stringstream ss;
        ss << palavra;
        ss >> novo->m_valor;
        return novo;
    }
    return 0x0;
}

void LiteralNumero::imprime(ostream &os) const
{
    os << "LNumero " << m_valor;
}

Literal *LiteralNumero::novoLiteral(float valor)
{
    LiteralNumero* novo = new LiteralNumero;
    novo->m_valor = valor;
    return novo;
}

float LiteralNumero::valor() const
{
    return m_valor;
}


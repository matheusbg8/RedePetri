#include "LiteralVariavel.h"

LiteralVariavel::LiteralVariavel()
{
    if(m_automato == 0x0)
    {
        ArestaAutomato *aresta = 0x0;

        m_automato = new Automato;
        m_automato->criaEstados(3);
        m_automato->setEstadoInicial(0);
        m_automato->addEstadoFinal(1);
        m_automato->addEstadoAceitacao(1);
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
        aresta->setSimbulosAceitos((Automato::letrasMaiusculas() + Automato::letrasMinusculas()).c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(1);
        aresta->setSimbulosAceitos((Automato::numeros() + Automato::letrasMaiusculas() + Automato::letrasMinusculas() + "_").c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(2);
        aresta->setSimbulosAceitos(".");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(2);
        aresta->setPara(1);
        aresta->setSimbulosAceitos((Automato::letrasMaiusculas() + Automato::letrasMinusculas()).c_str());
        m_automato->addAresta(aresta);
    }
}

LiteralVariavel::LiteralVariavel(string nome)
{
    m_nome = nome;
}

Automato* LiteralVariavel::m_automato = 0x0;
LiteralVariavel* LiteralVariavel::m_fabrica = 0x0;

LiteralVariavel *LiteralVariavel::fabrica()
{
    if(m_fabrica == 0x0)
    {
        m_fabrica = new LiteralVariavel();
    }
    return m_fabrica;
}

const string &LiteralVariavel::nome() const
{
    return m_nome;
}

TipoLiteral LiteralVariavel::tipoLiteral() const
{
    return LITERAL_VARIAVEL;
}

Literal *LiteralVariavel::novoLiteral(istream &expressao) const
{
    char c = expressao.peek();
    LiteralVariavel *resp = 0x0;

    // Se começa com uma letra
    if((c >= 'a' && c <= 'z') ||
      ( c >= 'A' && c <= 'Z'))
    {
        // Consome 1º caracter
        expressao.get();

        string nomeVar;
        while(c != ' ' && !expressao.eof())
        {
            nomeVar += c;
            c = expressao.get();
        }

        resp = new LiteralVariavel(nomeVar);
    }

    return resp;
}

Literal *LiteralVariavel::novoLiteral(const char *expressao, unsigned *numCaractersLidos) const
{
    string palavra;
    unsigned numCarac;

    numCarac = m_automato->avalia(expressao , palavra);

    if(numCaractersLidos != 0x0)
        *numCaractersLidos = numCarac;

    if(numCarac > 0)
    {
        LiteralVariavel *novo = new LiteralVariavel;
        novo->m_nome = palavra;
        return novo;
    }

    return 0x0;
}

void LiteralVariavel::imprime(ostream &os) const
{
    os << "LVariavel " << m_nome;
}


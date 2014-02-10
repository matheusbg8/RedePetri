#include "LiteralBooleano.h"

LiteralBooleano::LiteralBooleano(bool valor)
{
    m_valor = valor;

    // Inicializa o automato, se ele ainda na tiver sido inicializado
    if(m_automato == 0x0)
    {
        ArestaAutomato *aresta =0x0;
        m_automato = new Automato;
        m_automato->criaEstados(9);
        m_automato->setEstadoInicial(0);
        m_automato->addEstadoFinal(8);
        m_automato->addEstadoAceitacao(1);
        m_automato->addEstadoAceitacao(2);
        m_automato->addEstadoAceitacao(3);
        m_automato->addEstadoAceitacao(4);
        m_automato->addEstadoAceitacao(5);
        m_automato->addEstadoAceitacao(6);
        m_automato->addEstadoAceitacao(7);
        m_automato->addEstadoAceitacao(8);

        // Criando arestas
        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(0);
        aresta->setSimbulosAceitos(Automato::branco().c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(1);
        aresta->setSimbulosAceitos("tT");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(2);
        aresta->setSimbulosAceitos("rR");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(2);
        aresta->setPara(3);
        aresta->setSimbulosAceitos("uU");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(3);
        aresta->setPara(8);
        aresta->setSimbulosAceitos("eE");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(4);
        aresta->setSimbulosAceitos("fF");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(4);
        aresta->setPara(5);
        aresta->setSimbulosAceitos("aA");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(5);
        aresta->setPara(6);
        aresta->setSimbulosAceitos("lL");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(6);
        aresta->setPara(7);
        aresta->setSimbulosAceitos("sS");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(7);
        aresta->setPara(8);
        aresta->setSimbulosAceitos("eE");
        m_automato->addAresta(aresta);
    }
}

Automato * LiteralBooleano::m_automato = 0x0;

LiteralBooleano* LiteralBooleano::m_fabrica = 0x0;

LiteralBooleano *LiteralBooleano::fabrica()
{
    if(m_fabrica == 0x0)
    {
        m_fabrica = new LiteralBooleano();
    }
    return m_fabrica;
}

LiteralBooleano *LiteralBooleano::novoLiteral(bool valor)
{
    return new LiteralBooleano(valor);
}

TipoLiteral LiteralBooleano::tipoLiteral() const
{
    return LITERAL_BOOLEANO;
}

Literal *LiteralBooleano::novoLiteral(istream &expressao) const
{
    char verdade[] = "true",
            falso[] = "false";


}

Literal *LiteralBooleano::novoLiteral(const char *expressao, unsigned *numCaractersLidos) const
{
    if(expressao == 0x0) return 0x0;
    unsigned numCarac = 0;
    string palavra;

    numCarac = m_automato->avalia(expressao , palavra);

    if(numCaractersLidos != 0x0)
        *numCaractersLidos = numCarac;

    if(numCarac > 0)
    {
        LiteralBooleano *novo = 0x0;
        if(palavra.at(0) == 't' || palavra.at(0) == 'T')
        {
            novo = new LiteralBooleano(true);
        }else if(palavra.at(0) == 'f' || palavra.at(0) == 'F')
        {
            novo = new LiteralBooleano(false);
        }else
        {
            cout << "Erro literalOperador" << endl;
        }
        return novo;
    }
    return 0x0;
}

void LiteralBooleano::imprime(ostream &os) const
{
    os << "LBooleano ";
    if(m_valor)
    {
        os << "true";
    }else
    {
        os << "false";
    }
}

bool LiteralBooleano::valor()
{
    return m_valor;
}

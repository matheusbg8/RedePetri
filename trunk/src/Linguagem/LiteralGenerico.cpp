#include "LiteralGenerico.h"

LiteralGenerico::LiteralGenerico(TipoLiteralGenerico tipo)
{
    m_tipoGenerico = tipo;

    if(m_automato == 0x0)
    {
        ArestaAutomato *aresta =0x0;

        m_automato = new Automato;

        m_automato->criaEstados(2);
        m_automato->setEstadoInicial(0);
        m_automato->addEstadoFinal(1);
        m_automato->addEstadoAceitacao(1);

        // Criando arestas
        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(1);
        aresta->setSimbulosAceitos(")(");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(0);
        aresta->setSimbulosAceitos(Automato::branco().c_str());
        m_automato->addAresta(aresta);
    }
}

Automato * LiteralGenerico::m_automato = 0x0;

LiteralGenerico* LiteralGenerico::m_fabrica = 0x0;

LiteralGenerico *LiteralGenerico::fabrica()
{
    if(m_fabrica == 0x0)
    {
        m_fabrica = new LiteralGenerico();
    }
    return m_fabrica;
}

TipoLiteralGenerico LiteralGenerico::tipoLiteralGenerico() const
{
    return m_tipoGenerico;
}

TipoLiteral LiteralGenerico::tipoLiteral() const
{
    return LITERAL_GENERICO;
}

Literal *LiteralGenerico::novoLiteral(istream &expressao) const
{
    LiteralGenerico * resp = 0x0;

    // Verifica primeiro caracter
    switch(expressao.peek())
    {
        case '(':
            resp = new LiteralGenerico;
            resp->m_tipoGenerico = LITERAL_GENERICO_ABRE_PARENSES;
            expressao.get(); //Consome caracter
        break;
        case ')':
            resp = new LiteralGenerico;
            resp->m_tipoGenerico = LITERAL_GENERICO_FECHA_PARENSES;
            expressao.get(); // Consome caracter
        break;
    }

    return resp;
}

Literal *LiteralGenerico::novoLiteral(const char *expressao, unsigned *numCaractersLidos) const
{
    string palavra;
    unsigned numCarac = 0;

    numCarac = m_automato->avalia(expressao , palavra);

    if(numCaractersLidos != 0x0)
        *numCaractersLidos = numCarac;

    if(numCarac > 0)
    {
        LiteralGenerico *novo = 0x0;
        if(palavra == ")")
        {
            novo = new LiteralGenerico(LITERAL_GENERICO_FECHA_PARENSES);
        }else if( palavra == "(")
        {
            novo = new LiteralGenerico(LITERAL_GENERICO_ABRE_PARENSES);
        }else
        {
            cout << "Erro LiteralGenerico!" << endl;
        }
        return novo;
    }

    return 0x0;
}

void LiteralGenerico::imprime(ostream &os) const
{
    switch(m_tipoGenerico)
    {
    case LITERAL_GENERICO_ABRE_PARENSES:
        os << "LGenerico (";
        return;
    break;
    case LITERAL_GENERICO_FECHA_PARENSES:
        os << "LGenerico )";
        return;
    break;
    }

    os << "LGenerico Invalido";
}


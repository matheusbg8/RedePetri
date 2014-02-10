#include "LiteralOperador.h"

#include "LiteralBooleano.h"

LiteralOperador::LiteralOperador()
{

    if(m_automato == 0x0)
    {
        ArestaAutomato *aresta;

        m_automato = new Automato;

        m_automato->criaEstados(2);
        m_automato->setEstadoInicial(0);
        m_automato->addEstadoFinal(1);
        m_automato->addEstadoAceitacao(1);

        // Criando arestas
        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(0);
        aresta->setSimbulosAceitos(Automato::branco().c_str());
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(0);
        aresta->setPara(1);
        aresta->setSimbulosAceitos("+-*/=<>&|!");
        m_automato->addAresta(aresta);

        aresta = new ArestaAutomato;
        aresta->setDe(1);
        aresta->setPara(1);
        aresta->setSimbulosAceitos("+-*/=<>&|!");
        m_automato->addAresta(aresta);
    }
}



Automato* LiteralOperador::m_automato = 0x0;
LiteralOperador* LiteralOperador::m_fabrica = 0x0;

LiteralOperador *LiteralOperador::fabrica()
{
    if(m_fabrica == 0x0)
    {
        m_fabrica = new LiteralOperador();
    }
    return m_fabrica;
}

TipoLiteralOperador LiteralOperador::operador() const
{
    return m_operador;
}

unsigned LiteralOperador::precedencia() const
{
    switch(m_operador)
    {
        case OP_ATRIBUICAO: return 0;
        case OP_IGUAL: return 1;
        case OP_DIFERENTE: return 1;
        case OP_MAIOR: return 1;
        case OP_MENOR: return 1;
        case OP_MAIOR_IGUAL: return 1;
        case OP_MENOR_IGUAL: return 1;
        case OP_AND: return 2;
        case OP_OR: return 2;
        case OP_NEGADO: return 3;
        case OP_SOMA: return 3;
        case OP_SUBTRACAO: return 3;
        case OP_MULTIPLICACAO: return 4;
        case OP_DIVISAO: return 4;
    }
    return 0;
}

unsigned LiteralOperador::numArgumentos()
{
    return m_numArgumentos;
}

TipoLiteral LiteralOperador::tipoLiteral() const
{
    return LITERAL_OPERADOR;
}

Literal *LiteralOperador::novoLiteral(istream &expressao) const
{
    /// @todo - Encontrar uma forma de identificar quando operador - e de inversao de sinal ou quando e de subtracao
    char c = expressao.peek();
    LiteralOperador *resp = 0x0;

    switch(c)
    {
        case '=':
            expressao.get(); // Consome o caracter =
            c = expressao.peek();
            if( c == '=')
            {
                expressao.get(); // consome caracter =
                resp = new LiteralOperador;
                resp->m_operador = OP_IGUAL;
                resp->m_numArgumentos = 2;
            }
        break;

        case '>':
            expressao.get();
            resp = new LiteralOperador;

            c = expressao.peek();
            if(c == '=')
            {
                expressao.get(); // consome caracter =
                resp->m_operador = OP_MAIOR_IGUAL;
            }else
            {
                resp->m_operador = OP_MAIOR;
            }
            resp->m_numArgumentos = 2;
        break;

        case '<':
            expressao.get(); // consome o <
            resp = new LiteralOperador;

            c = expressao.peek();
            if( c == '=')
            {
                expressao.get(); // consome o caracter =
                resp->m_operador = OP_MENOR_IGUAL;
            }else
            {
                resp->m_operador = OP_MENOR;
            }
            resp->m_numArgumentos = 2;
        break;
        case '!':
            resp = new LiteralOperador;
            resp->m_operador = OP_NEGADO;
            resp->m_numArgumentos = 1;
        break;
        case '|':
            expressao.get(); // consome o |
            resp = new LiteralOperador;
            resp->m_operador = OP_OR;
            resp->m_numArgumentos = 2;

            c = expressao.peek();
            if( c == '|')
                expressao.get(); // consome o caracter |

        break;
        case '&':
            expressao.get(); // consome o |
            resp = new LiteralOperador;
            resp->m_operador = OP_AND;
            resp->m_numArgumentos = 2;

            c = expressao.peek();
            if( c == '&')
                expressao.get(); // consome o caracter &
        break;
        case '+':
            expressao.get(); // Consome o +

            resp = new LiteralOperador;
            resp->m_operador = OP_SOMA;
            resp->m_numArgumentos = 2;
        break;
        case '*':
            expressao.get(); // Consome o *

            resp = new LiteralOperador;
            resp->m_operador = OP_MULTIPLICACAO;
            resp->m_numArgumentos = 2;
        break;
        case '/':
        case '\\':
            expressao.get(); // Consome o /

            resp = new LiteralOperador;
            resp->m_operador = OP_DIVISAO;
            resp->m_numArgumentos = 2;
        break;
    }
    return resp;
}

Literal *LiteralOperador::novoLiteral(const char *expressao, unsigned *numCaractersLidos) const
{
    string palavra;
    unsigned numCarac = 0;

    numCarac = m_automato->avalia(expressao , palavra);

    if(numCaractersLidos != 0x0)
        *numCaractersLidos = numCarac;

    if(numCarac > 0)
    {
        LiteralOperador *novo = new LiteralOperador;
        novo->m_numArgumentos = 2;

        switch(palavra.at(0))
        {
            case '=':
            switch(palavra.size())
            {
                case 1:
                    novo->m_operador = OP_ATRIBUICAO;
                break;
                case 2:
                    if(palavra.at(1) == '=')
                        novo->m_operador = OP_IGUAL;
                    else
                        cout << "Erro op =" << endl;
                break;
                default:
                    cout << "Erro op = 2" << endl;
                break;
            }
            break;

            case '>':
                switch(palavra.size())
                {
                    case 1:
                        novo->m_operador = OP_MAIOR;
                    break;
                    case 2:
                        if(palavra.at(1) == '=')
                            novo->m_operador = OP_MAIOR_IGUAL;
                        else
                            cout << "Erro op >" << endl;
                    break;
                    default:
                        cout << "Erro op > 2" << endl;
                    break;
                }
            break;

            case '<':
                switch(palavra.size())
                {
                    case 1:
                        novo->m_operador = OP_MENOR;
                    break;
                    case 2:
                        if(palavra.at(1) == '=')
                            novo->m_operador = OP_MENOR_IGUAL;
                        else
                            cout << "Erro op <" << endl;
                    break;
                    default:
                        cout << "Erro op < 2" << endl;
                    break;
                }
            break;
            case '|':
                novo->m_operador = OP_OR;
            break;
            case '&':
                novo->m_operador = OP_AND;
            break;
            case '+':
                novo->m_operador = OP_SOMA;
            break;
            case '-':
                novo->m_operador = OP_SUBTRACAO;
            break;
            case '*':
                novo->m_operador = OP_MULTIPLICACAO;
            break;
            case '/':
                novo->m_operador = OP_DIVISAO;
            break;
            case '!':
                novo->m_operador = OP_NEGADO;
                novo->m_numArgumentos = 1;
            break;
            default:
                cout << "Erro ao interpretar operador literal, operador nao reconhecido" << endl;
            break;
        }

        return novo;
    }

    return 0x0;
}

void LiteralOperador::imprime(ostream &os) const
{
    switch(m_operador)
    {
        case OP_IGUAL:
            os << "LOperador ==";
            return;
        break;
        case OP_ATRIBUICAO:
            os << "LOperador =";
            return;
        break;
        case OP_DIFERENTE:
            os << "LOperador !=";
            return;
        break;
        case OP_MAIOR:
            os << "LOperador >";
            return;
        break;
        case OP_MENOR:
            os << "LOperador <";
            return;
        break;
        case OP_MAIOR_IGUAL:
            os << "LOperador >=";
            return;
        break;
        case OP_MENOR_IGUAL:
            os << "LOperador <=";
            return;
        break;
        case OP_AND:
            os << "LOperador &&";
            return;
        break;
        case OP_OR:
            os << "LOperador ||";
            return;
        break;
        case OP_NEGADO:
            os << "LOperador !";
            return;
        break;
        case OP_SOMA:
            os << "LOperador +";
            return;
        break;
        case OP_SUBTRACAO:
            os << "LOperador -";
            return;
        break;
        case OP_DIVISAO:
            os << "LOperador / ";
            return;
        break;
        case OP_MULTIPLICACAO:
            os << "LOperador *";
            return;
        break;
    }

    os << "LOperador Invalido";
}


#include "Ambiente.h"


/**
 * @brief
 *  Registrar uma variavel siginifica dizer que uma variavel pertence
 * a um ambiente, no registro de uma variavel um vertice é criado
 * representando a novavariavel e um id e a definição do ambiente da
 * variavel é definida. O ambiente passa a conter a nova variavel
 * a morte do ambiente implica na morte de suas variaveis.
 *
 * @param varivavel
 * @return bool
 */
bool Ambiente::registraNodo(NodoAmbiente *nodo)
{
    // Se pertence a um abiente diferente
    if(nodo->m_ambiente != 0x0 && nodo->m_ambiente != this)
    {
        cout << "Erro ao registrar variavel ao ambiente, ela pertence a outro ambiente" << endl;
        return false;
    }

    // Se ja esta no ambiente
    if(nodo->m_ambiente == this && m_grafo.existeVertice(nodo->m_id))
    {
        return true;
    }

    // Se ainda não existe em lugar algum
    int idNovaVariavel = m_grafo.novoVertice();

    // Verifica se conseguiu cria novo vertice
    if( idNovaVariavel < 0)
    {
        cout << "Erro ao registrar nova variavel, problema com o grafo" << endl;
        return false;
    }

    // Configura nova variavel
    nodo->m_id = idNovaVariavel;
    nodo->m_ambiente = this;

    // Verifica se é necessario alocar mais elementos
    if(idNovaVariavel >= m_nodos.size() )
        m_nodos.resize((idNovaVariavel+1)*2);

    // Armazena a variavel
    m_nodos[idNovaVariavel] = nodo;

    // Registrada :) Ok
    return true;
}

Ambiente::Ambiente(string nome):
    NodoAmbiente(nome)
{
    // O ambiente de um ambiente e o proprio ambiente
    m_ambiente = this;
    m_controle = 0x0;
    m_id = m_grafo.novoVertice();
    m_nodos.push_back(this);
}

Ambiente::~Ambiente()
{
    // Forca que as variaveis sejam deletadas
    // primeiro, se nao forcar, elas tentaram
    // se deletarem utilizando o grafo do ambiente
    // que não existira quando o ambiente
    // for destruido, como ambiente herda
    // VariavelAmbiente, o destrutor do ambinte
    // sempre é chamado antes do destrutor das
    // variaveis e um erro acontecera
    executandoDestrutor = true;
    for(unsigned i = 0 ; i < m_nodos.size() ; i++)
    {
        if(m_nodos[i] != this && m_nodos[i] != 0x0)
            delete m_nodos[i];
    }
    m_nodos.clear();
}

void Ambiente::setControle(CAmbiente *controle)
{
    m_controle = controle;
}

CAmbiente *Ambiente::controle()
{
    return m_controle;
}

NodoAmbiente *Ambiente::getNodo(unsigned id)
{
    // Se nao existe o ID
    if(!m_grafo.existeVertice(id))
        return 0x0; // Retorna null

    return m_nodos[id];
}

const NodoAmbiente *Ambiente::getNodo(unsigned id) const
{
    // Se nao existe o ID
    if(!m_grafo.existeVertice(id))
        return 0x0; // Retorna null

    return m_nodos[id];
}

NodoAmbiente *Ambiente::getNodo(const string &nome)
{
    return NodoAmbiente::getNodo(nome);
}

const NodoAmbiente *Ambiente::getNodo(const string &nome) const
{
    return NodoAmbiente::getNodo(nome);
}

int Ambiente::idMaiorNodo() const
{
    return m_grafo.idMaiorVertice();
}

VariavelAmbiente *Ambiente::getVariavel(unsigned id)
{
    NodoAmbiente * nodo = getNodo(id);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_VARIAVEL)
    {
        return (VariavelAmbiente*) nodo;
    }
    return 0x0;
}

PerguntaAmbiente *Ambiente::getPergunta(unsigned id)
{
    NodoAmbiente * nodo = getNodo(id);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_PERGUNTA)
    {
        return (PerguntaAmbiente*) nodo;
    }
    return 0x0;
}

AcaoAmbiente *Ambiente::getAcao(unsigned id)
{
    NodoAmbiente * nodo = getNodo(id);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_ACAO)
    {
        return (AcaoAmbiente*) nodo;
    }
    return 0x0;
}

VariavelAmbiente *Ambiente::getVariavel(string nome)
{
    return NodoAmbiente::getVariavel(nome);
}

/**
 * @brief
 *  Acessa uma pergunta
 * @param nomePergunta - Nome da pergunta que sera acessada
 * @return const PergutaAmbiente - Refrencia contante a pergunta, ou
 * 0x0 se ela não existir
 */
PerguntaAmbiente *Ambiente::getPergunta(string nome)
{
    return NodoAmbiente::getPergunta(nome);
}

AcaoAmbiente *Ambiente::getAcao(string nome)
{
    return NodoAmbiente::getAcao(nome);
}

/**
 * @brief
 *  Faz uma pergunta
 * @param nomePergunta - Nome da pergunta
 * @return bool - true se ela for verdade, false caso contrario ou nao existir.
 */
bool Ambiente::pergunta(string nomePergunta)
{
    PerguntaAmbiente *p = getPergunta(nomePergunta);
    if(p == 0x0)
    {
        cout << "Erro ao fazer pergunta ao ambiente, pergunta nao existe" << endl;
        return false;
    }

    return p->verdade(controle());
}

bool Ambiente::pergunta(unsigned id)
{
    PerguntaAmbiente *p = getPergunta(id);
    if(p == 0x0)
    {
        cout << "Erro ao fazer pergunta ao ambiente, pergunta nao existe" << endl;
        return false;
    }

    return p->verdade(controle());
}


void Ambiente::imprimeAmbiente()
{
    list<ArestaGrafo*>::const_iterator la;
    NodoAmbiente *de , *para;

    for(la = m_grafo.arestaBegin() ; la != m_grafo.arestaEnd() ; la++)
    {
        de = m_nodos[(*la)->de()];
        para = m_nodos[(*la)->para()];

        cout << "( " << de->nome() << " , " << /*de->valor() <<*/ " , " << de->m_id << " ) "
             << " --> "
             << "( " << para->nome() << " , " << /*para->valor() <<*/ " , " << para->m_id << ")"
             << endl;
    }
}

const Grafo *Ambiente::grafo() const
{
    return &m_grafo;
}

TipoNodoAmbiente Ambiente::tipoNodo()
{
    return NODO_AMBIENTE;
}


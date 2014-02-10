#include "CAmbiente.h"

const string CAmbiente::m_nomeNaoEncontrado = "";


void CAmbiente::removeVariavelVisualizacao(unsigned id)
{
    // Atualiza visualizacoes
    list<VisualizacaoAmbiente*>::iterator li;
    for(li = m_visualizacoes.begin() ; li != m_visualizacoes.end() ; li++)
    {
        (*li)->removeVariavel(id);
    }
}

void CAmbiente::removeAcaoVisualizacao(unsigned id)
{
    // Atualiza visualizacoes
    list<VisualizacaoAmbiente*>::iterator li;
    for(li = m_visualizacoes.begin() ; li != m_visualizacoes.end() ; li++)
    {
        (*li)->removeAcao(id);
    }
}

void CAmbiente::removePerguntaVisualizacao(unsigned id)
{
    // Atualiza visualizacoes
    list<VisualizacaoAmbiente*>::iterator li;
    for(li = m_visualizacoes.begin() ; li != m_visualizacoes.end() ; li++)
    {
        (*li)->removePergunta(id);
    }
}


/**
 * @brief
 *  Atualiza a visualização informa o modelo atual
 * @param visualizacao- Visualização que sera atualizada
 */
void CAmbiente::atualizaVisualizacao(VisualizacaoAmbiente *visualizacao)
{
    visualizacao->removeTudo();
    visualizacao->alteracaoNome(m_modelo->nome());

    NodoAmbiente *nodo = 0x0;
    int i;
    for(i = 0 ; i < m_modelo->idMaiorNodo(); i++)
    {
        nodo = m_modelo->getNodo(i);
        if(nodo != 0x0)
        switch(nodo->tipoNodo())
        {
            case NODO_PERGUNTA:
                visualizacao->novaPergunta(i,nodo->nome(), nodo->pergunta()->pergunta());
            break;
            case NODO_VARIAVEL:
                visualizacao->novaVariavel(i,nodo->nome(), nodo->variavel()->valor());
            break;
            case NODO_ACAO:
                visualizacao->novaAcao(i,nodo->nome(), nodo->acao()->acao());
            break;
        }
    }
}

CAmbiente::CAmbiente()
{
    m_modelo = 0x0;
    iniciaControleAmbiente();
}

CAmbiente::~CAmbiente()
{
    if(m_modelo)
        delete m_modelo;
    m_modelo = 0x0;
}

void CAmbiente::iniciaControleAmbiente()
{
    m_modelo = new Ambiente("NovoAmbiente");
    m_modelo->setControle(this);
}

void CAmbiente::addVisualizacao(VisualizacaoAmbiente *visualizacao)
{
    m_visualizacoes.push_back(visualizacao);

    // Se ja possui modelo
    if(m_modelo != 0x0)
        atualizaVisualizacao(visualizacao);
}

void CAmbiente::removeVisualizacao(VisualizacaoAmbiente *visualizacao)
{
    m_visualizacoes.remove(visualizacao);    
}

bool CAmbiente::possuiVisualizacoes()
{
    return !m_visualizacoes.empty();
}

void CAmbiente::setModelo(Ambiente *modelo)
{
    if(modelo == 0x0)
        return;

    m_modelo = modelo;
    modelo->setControle(this);

    // Atualiza todas visualizações
    list<VisualizacaoAmbiente*>::iterator lda;
    for(lda = m_visualizacoes.begin() ; lda != m_visualizacoes.end() ; lda++)
    {
        atualizaVisualizacao(*lda);
    }

}

const Ambiente *CAmbiente::modelo() const
{
    return m_modelo;
}

void CAmbiente::setNomeAmbiente(const string &nome)
{
    m_modelo->setNome(nome);
}


/**
 * @brief
 *  Cria uma nova variavel no ambiente
 * @param nome - Nome da variavel
 * @param valor - Valor inicial da variavel
 */
int CAmbiente::novaVariavel(const string& nome, const string& valor)
{
    /// @todo - Solucao tempoaria
    NodoAmbiente *n = m_modelo->getNodo(nome);
    if(n != 0x0) return n->id();

    VariavelAmbiente *v = m_modelo->addVariavel(nome, valor);

    if( v == 0x0)
        return -1;

    list<VisualizacaoAmbiente*>::iterator i;
    for(i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        (*i)->novaVariavel(v->id(), nome, valor);

    return v->id();
}

int CAmbiente::novaPergunta(const string& nome, const string& valor)
{
    /// @todo - Solucao tempoaria
    NodoAmbiente *n = m_modelo->getNodo(nome);
    if(n != 0x0) return n->id();

    PerguntaAmbiente *p = m_modelo->addPergunta(nome, valor);

    if( p == 0x0)
        return -1;

    list<VisualizacaoAmbiente*>::iterator i;
    for(i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        (*i)->novaPergunta(p->id(), nome, valor);

    return p->id();
}

int CAmbiente::novaAcao(const string&nome, const string& valor)
{
    /// @todo - Solucao tempoaria
    NodoAmbiente *n = m_modelo->getNodo(nome);
    if(n != 0x0) return n->id();

    AcaoAmbiente *a = m_modelo->addAcao(nome, valor);

    if( a == 0x0)
        return -1;

    list<VisualizacaoAmbiente*>::iterator i;
    for(i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        (*i)->novaAcao(a->id(), nome, valor);

    return a->id();
}

bool CAmbiente::setVariavel(int id, const string &valor)
{
    VariavelAmbiente *var =  m_modelo->getVariavel(id);
    if(var == 0x0)
    {
        cout << "Erro ao atribuir valor a variavel, id nao encontrado" << endl;
        return false;
    }

    var->setValor(valor);

    // Atualiza visializacoes
    list<VisualizacaoAmbiente*>::iterator i;
    for(i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        (*i)->alteracaoValor(id,valor);

    return true;
}


/**
 * @brief
 *  Remove variavel do ambiente
 * @param id - ID da variavel que sera removida
 */
void CAmbiente::removeVariavel(unsigned id)
{
    /// @todo - Corrigir problema de remover variavel, dependencia pai->filho
    // Atualiza Modelo
    m_modelo->removeNodo(m_modelo->getNodo(id));

    removeVariavelVisualizacao(id);
}

void CAmbiente::removePergunta(unsigned id)
{
    // Atualiza Modelo
    m_modelo->removeNodo(m_modelo->getNodo(id));

    removePerguntaVisualizacao(id);
}

void CAmbiente::removeAcao(unsigned id)
{
    // Atualiza Modelo
    m_modelo->removeNodo(m_modelo->getNodo(id));

    removeAcaoVisualizacao(id);
}

int CAmbiente::idNodo(const string &nome)
{
    NodoAmbiente *n = m_modelo->getNodo(nome);
    if(n)
        return n->id();
    cout << "Erro ao consultar ID do nodoAmbiente, nodo nao encontrado" << endl;
    return -1;
}

const string &CAmbiente::nomeNodo(unsigned id)
{
    NodoAmbiente *n = m_modelo->getNodo(id);
    if(n)
        return n->nome();
    cout << "Erro ao consultar nome do NodoAmbiente, nodo nao encontrado" << endl;
    return m_nomeNaoEncontrado;
}

const Literal *CAmbiente::getVariavel(unsigned id)
{
    const VariavelAmbiente* v = m_modelo->getVariavel(id);
    if(v)
        return v->literal();
    return 0x0;
}

bool CAmbiente::ehVariavel(int idNodo)
{
    return m_modelo->getVariavel(idNodo);
}

const NodoAmbiente *CAmbiente::getNodo(unsigned id)
{
    const NodoAmbiente *n = m_modelo->getNodo(id);
    return n;
}

bool CAmbiente::avaliaPergunta(int id)
{
    PerguntaAmbiente *p = m_modelo->getPergunta(id);
    if(p)
        return p->verdade(this);

    cout << "Erro ao consultar modelo, pergunta invalida" << endl;

    return false;
}

bool CAmbiente::executaAcao(int id)
{
    AcaoAmbiente *a = m_modelo->getAcao(id);

    if(a)
    {
        a->executaAcao(this);
        return true;
    }

    cout << "Erro ao executar acao do ambiente, id invalido" << endl;
    return false;
}


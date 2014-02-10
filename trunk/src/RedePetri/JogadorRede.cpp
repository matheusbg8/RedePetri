#include "JogadoRrede.h"

void JogadorRede::atualizaEscuta(EscutaJogadorRede *escuta)
{
    escuta->reiniciaJogadorRede();

    for(int i = 0 ; i < m_mapaTransicao.size() ; i++)
    {
        if(m_controladorRede->existeTransicao(i))
        {
            escuta->novaTransicao(i);
        }
    }
}

JogadorRede::JogadorRede()
{
    m_controladorRede = 0x0;
    m_controleAmbiente = 0x0;

    iniciaJogadorRede();
}

JogadorRede::~JogadorRede()
{
    if(m_controladorRede != 0x0)
        m_controladorRede->removeVisualizacao(this);
    // O controlador da rede se auto destroe se nao tiver nenhuma visualizacao
    // ele nao deve ser destruido pq pode ter mais visualizacoes usando o
    // mesmo controlador
    m_controladorRede = 0x0;

}

void JogadorRede::iniciaJogadorRede()
{
    m_execucaoAutomatica = false;
//    m_controleAmbiente = new CAmbiente();
}

void JogadorRede::setControladorRede(ControladorRede *controlador)
{
    if(m_controladorRede)
    {
        m_controladorRede->removeVisualizacao(this);
    }

    /// Revisar a troca de controlador quando ja possui um antes

    m_controladorRede = controlador;
    m_controladorRede->addVisualizacao(this);
}

void JogadorRede::setControladorAmbiente(CAmbiente *ambiente)
{
    if(m_controleAmbiente)
    {
        m_controleAmbiente->removeVisualizacao(this);
    }

    m_controleAmbiente = ambiente;
    m_controleAmbiente->addVisualizacao(this);
}

void JogadorRede::loop()
{
    bool execAuto = execucaoAutomatica();
    setExecucaoAutomatica(false);
    for(unsigned t = 0 ; t < m_controladorRede->numTransicoes(); t++)
    {        
        // Para cada transicao sensibilida
        if(m_controladorRede->sensibilizado(t))
        {
            bool executaTransicao = true;

            // Pega a lista de condicoes da transicao t
            list<unsigned>&conds = m_mapaTransicao[t].first;
            list<unsigned>::iterator il;

            // Verifica cada condicao associada a transica t
            for(il = conds.begin() ; il != conds.end() ; il++)
            {
                if(!m_controleAmbiente->avaliaPergunta(*il))
                {
                    executaTransicao = false;
                    break;
                }
            }

            list<unsigned>&acoes = m_mapaTransicao[t].second;
            // Se todas condicoede t foram satisfeitas,
            // executa todas acoes associadas a t
            if(executaTransicao)
            {
                for(il = acoes.begin(); il != acoes.end() ; il++)
                    m_controleAmbiente->executaAcao(*il);
                m_controladorRede->executaTransicao(t);
                break;
            }
        }        
    }
    setExecucaoAutomatica(execAuto);
}

int JogadorRede::relacionaPergunta(int idTransicao, int idPergunta)
{
    m_mapaTransicao[idTransicao].first.push_front(idPergunta);

    int id = m_indexacaoRelacoes.adicionaElemento(
                make_pair(
                    idTransicao ,
                    make_pair( jrRELACAO_PERGUNTA,
                    m_mapaTransicao[idTransicao].first.begin()
                    ) )
                );

    if(id >= 0)
    {
        list<EscutaJogadorRede*>::iterator i;
        for( i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        {
            (*i)->novaRelacaoPergunta(idTransicao,idPergunta, id);
        }
    }

    return id;
}

int JogadorRede::relacionaAcao(int idTransicao, int idAcao)
{
    m_mapaTransicao[idTransicao].second.push_front(idAcao);
    int id = m_indexacaoRelacoes.adicionaElemento(
                make_pair( idTransicao,
                make_pair( jrRELACAO_ACAO,
                m_mapaTransicao[idTransicao].second.begin()
                           ))
                );

    if(id >= 0)
    {
        list<EscutaJogadorRede*>::iterator i;
        for( i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        {
            (*i)->novaRelacaoAcao(idTransicao,idAcao, id);
        }
    }

    return id;
}

bool JogadorRede::removeRelacao(int idRelacao)
{
    if(m_indexacaoRelacoes.existeElemento(idRelacao))
    {
        pair< unsigned , pair < TipoRelacao , list<unsigned>::iterator >  >
                relacao = m_indexacaoRelacoes[idRelacao];

        if(relacao.second.first == jrRELACAO_ACAO)
        {
            m_mapaTransicao[relacao.first].second.erase(relacao.second.second);
        }else if( relacao.second.first == jrRELACAO_PERGUNTA)
        {
            m_mapaTransicao[relacao.first].first.erase(relacao.second.second);
        }

        m_indexacaoRelacoes.removeElemento(idRelacao);

        list<EscutaJogadorRede*>::iterator i;
        for( i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
        {
            (*i)->removeRelacao(idRelacao);
        }
    }

}

void JogadorRede::adicionaEscuta(EscutaJogadorRede *escuta)
{
    atualizaEscuta(escuta);
    m_visualizacoes.push_back(escuta);
    m_controleAmbiente->addVisualizacao(escuta);
}

void JogadorRede::removeEscuta(EscutaJogadorRede *escuta)
{
    m_visualizacoes.remove(escuta);
    m_controleAmbiente->removeVisualizacao(escuta);
}

const vector<pair<list<unsigned>, list<unsigned> > > &JogadorRede::relacoes() const
{
    return m_mapaTransicao;
}

bool JogadorRede::execucaoAutomatica() const
{
    return m_execucaoAutomatica;
}

void JogadorRede::setExecucaoAutomatica(bool simNao)
{
    m_execucaoAutomatica = simNao;
}


/**
 * @brief
 *  Metodo chamado quando um novo lugar foi criado na rede
 * em que o jogador esta controlando
 * @param id - ID do lugar criado
 */
void JogadorRede::dNovoLugar(unsigned id)
{
    // O Jogador nao reage a criacao de novos lugares
}


/**
 * @brief
 *  Metodo chamado quando uma transicao é criada na rede observada
 * pelo jogador da rede.
 * @param id - ID da transicao criada.
 */
void JogadorRede::dNovaTransicao(unsigned id)
{
    // O jogador cria uma linha no mapa de transicoes
    // para associar perguntas e acoes a nova transicao criada
    if(id >= m_mapaTransicao.size())
        m_mapaTransicao.resize((id+1)*2);

    list<EscutaJogadorRede*>::iterator i;
    for( i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
    {
        (*i)->novaTransicao(id);
    }
}


/**
 * @brief
 *  Metodo chamado quando um arco que leva um lugar a uma transicao
 * é criado na rede que o jogador esta observando.
 * @param id - ID do arco criado
 * @param de - ID do lugar de origem do arco.
 * @param para - ID da transicao de destino do arco.
 * @param peso - Peso do arco.
 */
void JogadorRede::dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso)
{
    // O jogador nao da bola para os arcos
}

/**
 * @brief
 *  Metodo chamado quando um arco que leva uma transicao a um lugar
 * é criado na rede que o jogador esta observando.
 * @param id - ID do arco criado
 * @param de - ID da transicao de origem do arco.
 * @param para - ID do lugar de destino do arco.
 * @param peso - Peso do arco.
 */

void JogadorRede::dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso)
{
    // O jogador nao da bola para os arcos
}


/**
 * @brief
 *  Metodo chamado quando uma transicao é deletada da
 * rede que o jogador esta observando.
 * @param id - ID do arco deletado.
 */
void JogadorRede::dDeletaTransicao(unsigned id)
{
    // Apaga todas acoes e perguntas associadas aquela transicao
    // que foi deletada.
    m_mapaTransicao[id].first.clear();
    m_mapaTransicao[id].second.clear();

    list<EscutaJogadorRede*>::iterator i;
    for( i = m_visualizacoes.begin() ; i != m_visualizacoes.end() ; i++)
    {
        (*i)->removeTransicao(id);
    }
}

void JogadorRede::dDeletaLugar(unsigned id)
{
}

void JogadorRede::dDeletaArco(unsigned id)
{
}

void JogadorRede::dSetPesoArco(unsigned id, unsigned peso)
{
}

void JogadorRede::dSetFichas(unsigned id, unsigned numFichas)
{
}

unsigned JogadorRede::dPesoArco(unsigned id)
{
}

unsigned JogadorRede::dFichas(unsigned id)
{
}

void JogadorRede::dExecutaTransicao(unsigned id)
{
}

/**
 * @brief
 *  Metodo chamado quando uma novavariavel é criado no ambiente
 * @param id - id da variavel criada.
 * @param nome - nome da variavel criada.
 * @param valor - valor da variavel criada.
 */
void JogadorRede::novaVariavel(unsigned idNodo, const string &nome, const string &valor)
{
    cout << "Criado nova variavel " << nome << " valor " << valor << endl;    
    if(m_execucaoAutomatica)
    {
        loop();
    }
}

/**
 * @brief
 *  Metodo chamado quando uma pergunta é criada
 * @param id - ID da pergunta criada.
 * @param nome - Nome da pergunta criada.
 * @param valor Valor da variavel criada.
 */
void JogadorRede::novaPergunta(unsigned idNodo, const string &nome, const string &valor)
{
    if(m_execucaoAutomatica)
    {
        loop();
    }
}

/**
 * @brief
 *  Metodo chamado quando uma nova acao é criada.
 * @param id - ID da acao criada.
 * @param nome - Nome da acao criada.
 * @param acao - Valor da acao criada.
 */
void JogadorRede::novaAcao(unsigned idNodo, const string &nome, const string &valor)
{
    if(m_execucaoAutomatica)
    {
        loop();
    }
}


/**
 * @brief
 *  Metodo chamado quando o modelo observado sofre uma alteracao de nome
 * @param nome - Novo nome do modelo
 */
void JogadorRede::alteracaoNome(const string &nome)
{
}

/**
 * @brief
 *  Metodo chamado quando algum nodo do ambiente é alterado.
 *  O valor é interpretado como uma condição se o nodoAmbiente for
 * uma pergunta, uma instrucao, se o nodoAmbiente for uma Acao e
 * o valor de uma variavel se o nodo for uma Variavel.
 * @param id - ID do nodo.
 * @param valor - Novo valor do nodo.
 * @return bool -
 */
bool JogadorRede::alteracaoValor(unsigned idNodo, const string &valor)
{
    if(m_execucaoAutomatica)
    {
        loop();
    }
}

/**
 * @brief
 *  Método chamado quando uma variavel é removida do ambiente.
 * @param idNodo - ID da variável.
 */
void JogadorRede::removeVariavel(unsigned idNodo)
{
    if(m_execucaoAutomatica)
    {
        loop();
    }
}

/**
 * @brief
 *  Método chamado quando uma pergunta é removida do ambiente.
 * @param idNodo - ID da pergunta.
 */
void JogadorRede::removePergunta(unsigned idNodo)
{
    if(m_execucaoAutomatica)
    {
        loop();
    }
}

/**
 * @brief
 *  Método chamado quando uma ação é removida do ambiente.
 * @param idNodo - ID da açao removida.
 */
void JogadorRede::removeAcao(unsigned idNodo)
{
    if(m_execucaoAutomatica)
    {
        loop();
    }
}

/**
 * @brief
 *  Metodo chamado quando todos nodos do ambiente foram apagados
 */
void JogadorRede::removeTudo()
{
}

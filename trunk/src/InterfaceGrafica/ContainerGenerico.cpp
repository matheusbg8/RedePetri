#include "ContainerGenerico.h"

ContainerGenerico::ContainerGenerico():
    Container(0x0)
{
    m_seta = 0x0;
    m_setaDefinindo = 0x0;
    m_definindoArco = false;
}

ContainerGenerico::~ContainerGenerico()
{
    // Deleta os desenhos da fabrica (inclusive as setas)
    list<Desenho*>::iterator id;
    for( id = m_fabricaDesenhos.begin() ; id != m_fabricaDesenhos.end() ; id++)
    {
        delete *id;
    }
    m_seta = 0x0;

    // Lembrando que todos os desenhos contidos no container sao
    // desalocados automaticamente pelo container
}

bool ContainerGenerico::adicionaDesenhoNaFabrica(Desenho *d, int idTipoDesenho, int faixaIndexacao)
{
    if(d == 0x0 ) return false;

    // Verifica se o id esta disponivel na fabrica
    if(m_fabricaDesenhos.adicionaElemento(d, idTipoDesenho) == idTipoDesenho)
    {
        d->setIdTipoDesenho(idTipoDesenho);
        d->setFaixaIndexacao(faixaIndexacao);
    }
    else
    {
        cout << "Erro ao adicionar desenho generico na fabrica conteiner generico, desenho ja existe" << endl;
        return false;
    }

    // Verifica alocacao de indexacao
    if(d->faixaIndexacao() >= m_indexacao.size())
    {
        // Se nao esta, aloca espaco necessario
        m_indexacao.resize((d->faixaIndexacao()+1)*2);
    }

    return true;
}

bool ContainerGenerico::removeDesenhoFabrica(int idTipoDesenho)
{
    const Desenho *d = getDesenhoGenerico(idTipoDesenho);
    Desenho * t;

    if(d == 0x0) return false;

    for(int i = 0 ; i <= m_indexacao[d->faixaIndexacao()].maiorIndice(); i++)
    {
        if(m_indexacao[d->faixaIndexacao()].existeElemento(i))
        {
            t = m_indexacao[d->faixaIndexacao()][i];
            if(t->idTipoDesenho() == idTipoDesenho)
            {
                m_indexacao[d->faixaIndexacao()].removeElemento(i);
                delete t;
            }
        }
    }

    m_fabricaDesenhos.removeElemento(idTipoDesenho);
    delete d;
    return true;
}

bool ContainerGenerico::defineSeta(Seta *seta, int idTipoDesenho, int faixaIndexacao)
{
    if(m_seta != 0x0)
    {
        removeDesenhoFabrica(m_seta->idTipoDesenho());
        m_seta = 0x0;
    }

    if(adicionaDesenhoNaFabrica(seta,idTipoDesenho,faixaIndexacao))
    {
        m_seta = seta;
    }else
    {
        cout << "ContainerGenerico::Erro ao definir seta, conflito de ID na fabrica de desenho" << endl;
        delete seta;
        return false;
    }
    return true;
}

/**
 * @brief
 *  Retorna um desenho generico da fabrica
 * @param id - id do tipo de desenho.
 * @return DesenhoGenerico
 */
const Desenho *ContainerGenerico::getDesenhoGenerico(int idTipoDesenho) const
{    
    if(m_fabricaDesenhos.existeElemento(idTipoDesenho))
        return m_fabricaDesenhos[idTipoDesenho];
    return 0x0;
}

Desenho *ContainerGenerico::getDesenhoGenerico(int idTipoDesenho)
{
    if(m_fabricaDesenhos.existeElemento(idTipoDesenho))
        return m_fabricaDesenhos[idTipoDesenho];
    return 0x0;
}

/**
 * @brief
 *  Cria um desenho no container
 * @param tipoDesenho - id do tipo do desenho
 * @return int - id do desenho criado, ou -1
 * se nao pode ser criado
 */
int ContainerGenerico::novoDesenho(int idTipoDesenho)
{
    const Desenho *d = getDesenhoGenerico(idTipoDesenho);

    if(d == 0x0)
    {
        cout << "Erro desenho nao esta presente na fabrica do container generico" << endl;
        return -1;
    }

    Desenho *novoDesenho = d->novaInstancia();

    if(novoDesenho == 0x0)
            return -1;

    int id = m_indexacao[d->faixaIndexacao()].adicionaElemento(novoDesenho);
    novoDesenho->setIdDesenho(id);
    novoDesenho->setIdTipoDesenho(idTipoDesenho);
    novoDesenho->setFaixaIndexacao(d->faixaIndexacao());

    Container::novoDesenho(novoDesenho);

    return id;
}


/**
 * @brief
 *  Cria um desenho no container
 * @param tipoDesenho - Tipo do desenho
 * @param idDesenho - ID desejado para o desenho,
 * os IDs sao indexados em um vetor, portanto passe ids pequenos.
 * @return int - ID atribido ao desenho ou -1 se
 * o desenho não pode ser criado.
 */
int ContainerGenerico::novoDesenho(int idTipoDesenho, int id)
{
    const Desenho *d = getDesenhoGenerico(idTipoDesenho);

    if(d == 0x0)
    {
        cout << "Erro desenho nao esta presente na fabrica do container generico" << endl;
        return -1;
    }

    // Verifica se o id esta ocupado
    if(m_indexacao[d->faixaIndexacao()].existeElemento(id))
    {
        // Se esta, nao é possivel criar desenho
        return -1;
    }

    // Cria novo desenho
    Desenho *novoDesenho = d->novaInstancia();
    if(novoDesenho == 0x0)
        return -1;

    // Coloca na indexacao
    if(m_indexacao[d->faixaIndexacao()].adicionaElemento(novoDesenho, id) != id)
    {
        cout << "Erro ao adicionar desenho container generico" << endl;
    }

    // Define o desenho
    novoDesenho->setIdDesenho(id);
    novoDesenho->setIdTipoDesenho(idTipoDesenho);
    novoDesenho->setFaixaIndexacao(d->faixaIndexacao());

    // Adiciona composicao
    Container::novoDesenho(novoDesenho);

    // Retorna id do desenho
    return id;
}


/**
 * @brief
 *  Cria uma seta entre dois desenhos do container
 * @param idDe - ID do desenho de origem.
 * @param idDeTipo - ID do tipo do desenho de origem.
 * @param idPara - ID do desenho de destino.
 * @param idParaTipo - ID do tipo do desenho de destino.
 * @return int - ID da seta criada, ou -1 se não for
 * possivel criar a seta por nao existir os desenhos
 * de origem ou destino, ou porque a seta nao foi definida.
 */
int ContainerGenerico::novaSeta(int idDe, int idDeTipo, int idPara, int idParaTipo)
{
    Desenho *de = desenho(idDeTipo, idDe),
            *para = desenho(idParaTipo, idPara);
    int id = -1;

    if(de == 0x0 || para == 0x0 || m_seta == 0x0)
        return -1;

    id = novoDesenho(m_seta->idTipoDesenho());
    if(id >= 0)
    {
        Seta *s = (Seta*) desenho(m_seta->idTipoDesenho(),id);
        s->setLigacaoIni(de);
        s->setLigacaoFim(para);
    }
    return id;
}


/**
 * @brief
 *  Cria uma seta entre dois desenhos do container
 * @param idDe - ID do desenho de origem.
 * @param idDeTipo - ID do tipo do desenho de origem.
 * @param idPara - ID do desenho de destino.
 * @param idParaTipo - ID do tipo do desenho de destino.
 * @param idSeta - ID que sera definido para seta criada.
 * @return int - ID da seta criada, ou -1 se não for
 * possivel criar a seta por nao existir os desenhos
 * de origem ou destino, ou porque a seta nao foi definida.
 */
int ContainerGenerico::novaSeta(int idDe, int idDeTipo, int idPara, int idParaTipo, int idSeta)
{
    Desenho *de = desenho(idDeTipo, idDe),
            *para = desenho(idParaTipo, idPara);

    if(de == 0x0 || para == 0x0 || m_seta == 0x0)
        return -1;

    if(novoDesenho(m_seta->idTipoDesenho(), idSeta) == idSeta)
    {
        Seta *s = (Seta*) desenho(m_seta->idTipoDesenho(),idSeta);
        s->setLigacaoIni(de);
        s->setLigacaoFim(para);
    }else
    {
        idSeta = -1;
    }
    return idSeta;
}

void ContainerGenerico::deletaDesenho(int idTipoDesenho, int id)
{
    const Desenho *d = getDesenhoGenerico(idTipoDesenho);
    if(d == 0x0) return;

    if(m_indexacao[d->faixaIndexacao()].existeElemento(id))
    {
        delete m_indexacao[d->faixaIndexacao()][id];
        m_indexacao[d->faixaIndexacao()].removeElemento(id);
    }
}


/**
 * @brief
 *  Retorna o um desenho do container
 * @param tipoDesenho - Tipo do desenho procurado.
 * @param id - ID do desenho procurado.
 * @return Desenho - Desenho, ou 0x0 se ele não existir.
 */
Desenho *ContainerGenerico::desenho(int idTipoDesenho, int id)
{
    const Desenho *d = getDesenhoGenerico(idTipoDesenho);

    if(d == 0x0) return 0x0;

    // Verifica se o Desenho com id ID foi criado no container
    if(m_indexacao[d->faixaIndexacao()].existeElemento(id))
    {
        return m_indexacao[d->faixaIndexacao()][id];
    }
    return 0x0;
}

const Desenho *ContainerGenerico::desenho(int idTipoDesenho, int id) const
{
    const Desenho *d = getDesenhoGenerico(idTipoDesenho);

    if(d == 0x0) return 0x0;

    // Verifica se o Desenho com id ID foi criado no container
    if(m_indexacao[d->faixaIndexacao()].existeElemento(id))
    {
        return m_indexacao[d->faixaIndexacao()][id];
    }
    return 0x0;
}

int ContainerGenerico::numDesenhos(int tipoDesenho) const
{
    const Desenho *d = getDesenhoGenerico(tipoDesenho);

    if(d == 0x0) return 0;

    return m_indexacao[d->faixaIndexacao()].tamanho();
}

int ContainerGenerico::maiorIndice(int tipoDesenho) const
{
    const Desenho *d = getDesenhoGenerico(tipoDesenho);

    if(d == 0x0) return 0;

    return m_indexacao[d->faixaIndexacao()].maiorIndice();
}


/**
 * @brief
 *  Este metodo inicia uma sequencia de procedimentos
 * para cria um arco (seta) entre dois desenhos utilizando
 * o mouse.
 */
void ContainerGenerico::novoArco()
{
    if(m_seta == 0x0)
    {
        cout << "Erro ao criar seta em container generico, nao foi definido seta na fabrica" << endl;
        return ;
    }

    Seta *s = (Seta*) m_seta->novaInstancia();
    if(s == 0x0)
    {
        cout << "Erro ao cria seta, seta da fabrica com problemas" << endl;
        return ;
    }

    Container::novoDesenho(s);
//    s->comecaRastriamento();
    s->comecaRastriamentoInicio();

    m_definindoArco = true;
    m_setaDefinindo = s;
}

bool ContainerGenerico::novoMouseEvento(MouseEvento *mouseEvento)
{
    bool eventoPropagado = false; // Booleano que indica se o evento foi propagado para algum desenho ou não

    if(produzLog)
        cout << "Container ( " << getNome().toStdString() << "):: novoMouseEvento( )" << endl;

    // Converte a posição local do evento para o referencial do container
    // para que esse evento possa ser repassado para os desenhos internos do
    // container

    rPonto posicaoLocal = converteMeuReferencial(mouseEvento->posicaoLocal());
    MouseEvento novoEvento(*mouseEvento);
    novoEvento.setPosicaoLocal(posicaoLocal);

    // Se eu tenho desenhos dentro
    if(!filhos.empty())
    {

        // Para cada desenho, comecando pelo fim
        // porque a ordem que os desenhos sao desenhados
        // começa pelo inicio, o ultimo desenho desenhado é
        // que esta mais em cima.
        list<Desenho*>::reverse_iterator i;
        for(i = filhos.rbegin() ; i != filhos.rend() && !eventoPropagado ; ++i)
        {
            // Se o desenho e visivel e esta escutando eventos do mouse
            if((*i)->visivel() && (*i)->escutaMouseEvento(mouseEvento)) // Se o desenho esta escutando tal evento
            {
                if(novoEvento.evento() == MOUSE_MOVENDO)
                {
                    if((*i)->novoMouseEvento(&novoEvento))
                    {
                        eventoPropagado = true;
                        processaMouseEvento(&novoEvento , *i);
                    }
                }
                else if((*i)->contemrPonto(novoEvento.posicaoLocal()) )
                {
                    if((*i)->novoMouseEvento(&novoEvento))
                    {
                        eventoPropagado = true;
                        processaMouseEvento(&novoEvento , *i);
                    }
                }
            }
        }
    }


    if(escutaMouseEvento(mouseEvento))
    {
        if(eventoPropagado == true)
        {
            setEscutaMouseMovendo(true);
            setEscutaMouseSolto(true);
            setEscutaMousePrecionado(true);

            /* Não propaga mais o evento,pois ja foi propagado 1 vez
            Porem as escutas devem ser ativadas para que os eventos
            possam ser transmitidos para os desenhos filhos
            */
            if(produzLog)
                cout << "Evento foi propagado" << endl;

        }else
        {// Caso contrario, sempre propaga para mim mesmo
            if(Desenho::novoMouseEvento(mouseEvento))
            {
                eventoPropagado = true;
                processaMouseEvento(mouseEvento, 0x0);
            }
        }
    }
    return eventoPropagado;

}

void ContainerGenerico::processaMouseEvento(MouseEvento *me, Desenho *d)
{
    int id = -1, idTipoDesenho = -1, idArco = -1;

    if(d != 0x0)
    {
        id = d->idDesenho();
        idTipoDesenho = d->idTipoDesenho();
    }

    switch(me->evento())
    {
    case MOUSE_PRECIONADO:
            mousePrecionado(me, idTipoDesenho,id);
    break;
    case MOUSE_SOLTO:
        if(m_definindoArco && m_setaDefinindo)
        {
            if(m_setaDefinindo->getLigacaoIni() && m_setaDefinindo->getLigacaoFim())
            {
                idArco = ligacao(m_setaDefinindo->getLigacaoIni()->idDesenho(),
                           m_setaDefinindo->getLigacaoIni()->idTipoDesenho(),
                           m_setaDefinindo->getLigacaoFim()->idDesenho(),
                           m_setaDefinindo->getLigacaoFim()->idTipoDesenho());

                if(idArco == -2) // Nao aceita arco
                {
                    delete m_setaDefinindo;
                    m_setaDefinindo = 0x0;
                }else if(idArco == -1) // Aceita arco sem se preocupar com o ID
                {
                    // Adiciona arco na indexacao
                    idArco = m_indexacao[m_seta->faixaIndexacao()].adicionaElemento(m_setaDefinindo);
                }else // Cria o arco com o id definido
                {
                    // Adiciona arco na indexacao com id especidifcado
                    idArco = m_indexacao[m_seta->faixaIndexacao()].adicionaElemento(m_setaDefinindo, idArco);
                    if( idArco < 0)
                    {
                        cout << "Erro ao criar arco em container generico, ja existe arco com id expecificado" << endl;
                    }
                }
                if(m_setaDefinindo)
                {
                    m_setaDefinindo->setIdDesenho(idArco);
                    m_setaDefinindo->setIdTipoDesenho(m_seta->idTipoDesenho());
                    m_setaDefinindo->setFaixaIndexacao(m_seta->faixaIndexacao());
                    m_setaDefinindo = 0x0;
                }
                m_definindoArco = false;
            }else if(m_setaDefinindo->getLigacaoIni() && !m_setaDefinindo->getLigacaoFim())
            {
//                m_setaDefinindo->defineSeta(m_setaDefinindo->posicaoInicial(), converteMeuReferencial(me->posicaoLocal()));
//                m_setaDefinindo->comecaRastriamentoInicio();
                m_setaDefinindo->comecaRastriamentoFim();
            }else
            {
                delete m_setaDefinindo;
                m_setaDefinindo = 0x0;
                m_definindoArco = false;
            }
        }else // Se nao estive criando arco
        {
            mouseSolto(me, idTipoDesenho, id);
        }
        break;
    case MOUSE_MOVENDO:
        break;
    }
}

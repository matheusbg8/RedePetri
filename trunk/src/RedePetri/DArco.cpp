#include "DArco.h"
#include "DLugar.h"
#include "DTransicao.h"

DArco::DArco()
{
    inicializaDArco();
}

DArco::~DArco()
{
    // O tratamento de desalocamento do desenho é feito
    // no destrutor do desenho.    
}

void DArco::setPeso(int custo)
{
    cout << "Definindo novo custo parao arco!" << endl;
    m_peso = custo;

    if(m_cmpOrigem != 0x0 && m_cmpDestino != 0x0)
    {
        if(m_controlador != 0x0)
        {
            m_controlador->setPesoArco(m_IDCP, m_peso);
        }else
        {
            cout << "Erro ao atualizar custo do arco, sem modelo de dados" << endl;
        }
    }else
    {
        cout << "Arco não possui duas ligações" << endl;
    }
}

int DArco::getPeso() const
{
    if(m_controlador != 0x0)
        return m_controlador->pesoArco(m_IDCP);
    return 0;
}

void DArco::dSetPeso(unsigned peso)
{
    m_peso = peso;
}

unsigned DArco::dPeso()
{
    return m_peso;
}


/**
 * @brief
 *  Retorna o ComponentePetri de origem
 * do arco, ou 0x0 se não existir nenhum
 * componente na origem.
 * @return ComponentePetri - ComponentePetri
 * de origem
 */
DComponentePetri *DArco::getOrigem()
{
    return m_cmpOrigem;
}


/**
 * @brief
 *  Retorna o ComponentePetri de destino
 * do arco, ou 0x0 se não existir nenhum
 * componente conectado.
 * @return ComponentePetri - Componente
 * Petri de desetino.
 */
DComponentePetri *DArco::getDestino()
{
    return m_cmpDestino;
}


/**
 * @brief
 *  Desenha o arco
 */
void DArco::desenha()
{
    // Desenha a seta
    Seta::desenha();

    // Depois o peso, se necessario
    if(m_peso != 1)
    {
        rPonto posicaoDesenho ( (fim->posicaoLocal() - inicio->posicaoLocal()) /2.f);
        posicaoDesenho += posicaoDesenho.ortoAntiHorario().uni()*10.f + inicio->posicaoLocal();

        desenhaTexto(QString("%1").arg(m_peso), posicaoDesenho, QFont("Times",12,QFont::Bold));
    }
}

void DArco::setFake(bool simNao)
{
    m_fake = simNao;
}

bool DArco::fake()
{
    return m_fake;
}

bool DArco::setControle(ControladorRede *controlador)
{
    m_controlador = controlador;
}

ControladorRede *DArco::getControlador()
{
    return m_controlador;
}

bool DArco::ehTransicao()
{
    return false;
}

bool DArco::ehLugar()
{
    return false;
}

bool DArco::ehArco()
{
    return true;
}

void DArco::inicializaDArco()
{
    setNome(QString("Arco %1").arg(id()));
    m_tipoDesenho = TD_ARCO;
    m_controlador = 0x0;

    m_cmpOrigem = 0x0;
    m_cmpDestino = 0x0;

    m_peso = 1;

    m_fake = false;

    setNomeVisivel(true);

    criaAcoes();
    criaMenus();
}


/**
 * @brief
 *  Tenta pega a ComponentePetri do desenho, se consegui, retorna a referencia
 * pra componente, se não consegui retorna null (0x0).
 * @param desenho - Desenho que possui a componente petri
 * @return ComponentePetri - Componente Petri do desenho
 */
DComponentePetri *DArco::pegaComponente(Desenho *desenho)
{
    DComponentePetri *resp = 0x0;
    if(desenho != 0x0)
    {
        switch(desenho->tipoDesenho())
        {
        case TD_LUGAR:
            resp = (DLugar*) desenho;
        break;
        case TD_TRANSICAO:
            resp = (DTransicao*) desenho;
        break;
        case TD_ARCO:
            resp = (DArco*) desenho;
        break;
        default:
        break;
        }
    }
    return resp;
}


/**
 * @brief
 * Remove a componente petri de origem do arco
 */
void DArco::removeComponenteIni()
{
    if(produzLog)
        cout << "DArco(" << getNome().toStdString() << ")::removeComponenteIni()\n";

    // Se tem um desenho na origem
    if(m_cmpOrigem != 0x0)
    {
        // Como o arco perde a origem, ele volta a ser um fake, nao faz parte do modelo
        setFake(true);
        if(m_controlador != 0x0 && m_cmpDestino != 0x0)
        {   // E um arco valido no moelo
            if(m_cmpOrigem->ehLugar() && m_cmpDestino->ehTransicao())
            {
                m_controlador->deletaArco(getIDCP());
//                m_controlador->deletaArcoPT(m_cmpOrigem->getIDCP(), m_cmpDestino->getIDCP());
            }else if( m_cmpOrigem->ehTransicao() && m_cmpDestino->ehLugar())
            {
                m_controlador->deletaArco(getIDCP());
//                m_controlador->deletaArcoTP(m_cmpOrigem->getIDCP() , m_cmpDestino->getIDCP());
            }
        }
        m_cmpOrigem = 0x0;
    }
}

void DArco::removeComponenteFim()
{
    if(produzLog)
        cout << "DArco(" << getNome().toStdString() << ")::removeComponenteFim()\n";

    // Se tem um destino definido
    if(m_cmpDestino != 0x0)
    {
        setFake(true); // Como o arco perde a componente de destino, ele volta a ser um fake por nao fazer mais parte do modelo

        // Se esta numa rede e possui uma origem (atualiza modelo da rede)
        if(m_controlador != 0x0 && m_cmpOrigem != 0x0)
        {
            if(m_cmpOrigem->ehLugar() && m_cmpDestino->ehTransicao())
            {
                m_controlador->deletaArco(getIDCP());
//                m_controlador->deletaArcoPT(m_cmpOrigem->getIDCP(), m_cmpDestino->getIDCP());
            }else if( m_cmpOrigem->ehTransicao() && m_cmpDestino->ehLugar())
            {
                m_controlador->deletaArco(getIDCP());
//                m_controlador->deletaArcoTP(m_cmpOrigem->getIDCP() , m_cmpDestino->getIDCP());
            }
        }
        m_cmpDestino = 0x0;
    }
}

bool DArco::mousePrecionado(MouseEvento *novoMouseEvento)
{
    if(novoMouseEvento->botao() == BOTAO_DIREITO)
    {
        mnu->exec(novoMouseEvento->posicaoJanela());
        return true;
    }
    return Seta::mousePrecionado(novoMouseEvento);
}

void DArco::criaAcoes()
{
    actDeleta = new QAction("Deleta Arco",this);
    QObject::connect(actDeleta, SIGNAL(triggered()), this, SLOT(deleta()));
}

void DArco::criaMenus()
{
    mnu = new QMenu(widget());
    mnu->addAction(actDeleta);
}

bool DArco::aceitaLigacaoIni(Desenho *desenho)
{
    /** @todo - Acho que é melhor sobrescreve o metodo setLigacaoIni,
      * e não aceitaLigacaoIni.
     **/

    // Se for para remover o componente
    if(desenho == 0x0)
    {
        removeComponenteIni();
        return true;
    }

    DComponentePetri *novaComponente = pegaComponente(desenho);

    // Se possuei um controlador de rede
    if(m_controlador != 0x0 && novaComponente != 0x0)
    {
        // Se tem componente de destino
        if(m_cmpDestino != 0x0)
        {
            if(novaComponente->ehLugar() && m_cmpDestino->ehTransicao())
            {
                // Se nao e arco fake
                if(!m_fake)
                {
                    m_cmpOrigem = novaComponente;
                    return true; // Aceita a ligação
                }else // Se é fake
                {
                    m_controlador->novoArcoPT(novaComponente->getIDCP(), m_cmpDestino->getIDCP(), m_peso);
                    /// @todo - Melhorar a idéia do arco fake
                    delete this;
                    return false;
                }

            }else if(novaComponente->ehTransicao() && m_cmpDestino->ehLugar())
            {
                // Se nao e arco fake
                if(!m_fake)
                {
                    m_cmpOrigem = novaComponente;
                    return true; // Aceita a ligação
                }else // Se é fake, cria arco no modelo e de destroi
                {
                    m_controlador->novoArcoTP(novaComponente->getIDCP() , m_cmpDestino->getIDCP(), m_peso);
                    delete this; // q lokura :)
                    return false;
                }
            }else
            {
                cout << "Erro ao definir arco, não é permitido ligações de transição com transição ou lugar com lugar" << endl;
                QMessageBox msgErro;
                msgErro.setText("Nao e permitido ligacao de lugar com lugar ou transicao com transicao");                
                msgErro.exec();
            }
        }else // Primero componente que esta sendo ligado
        {
            m_cmpOrigem = novaComponente;
            return true;
        }
    }
    else{
        cout << "Erro ao definir arco, o arco não possui uma rede de petri associada" << endl;
        QMessageBox msgErro;
        msgErro.setText("Erro ao definir arco, o arco não possui uma rede de petri associada");
        msgErro.exec();
    }
    return false; // Não aceita a ligação
}

bool DArco::aceitaLigacaoFim(Desenho *desenho)
{
    //Se for para remover uma ligação
    if(desenho == 0x0)
    {
        removeComponenteFim();
        return true;
    }

    DComponentePetri *novaComponente = pegaComponente(desenho);

    // Se possuei uma rede de petri
    if(m_controlador != 0x0 && novaComponente != 0x0)
    {
        // Se tem componente de origem
        if(m_cmpOrigem != 0x0)
        {
            if(m_cmpOrigem->ehLugar() && novaComponente->ehTransicao())
            {
                if(!m_fake)
                {
                    m_cmpDestino = novaComponente;
                    return true; // Aceita a ligação
                }else // Se é fake, cria arco no modelo e de destroi
                {
                    m_controlador->novoArcoPT(m_cmpOrigem->getIDCP(), novaComponente->getIDCP(), m_peso);
                    delete this;
                    return false;
                }
            }else if(m_cmpOrigem->ehTransicao() && novaComponente->ehLugar())
            {
                if(!m_fake)
                {
                    m_cmpDestino = novaComponente;
                    return true; // Aceita a ligação
                }else // Se é fake, cria arco no modelo e de destroi
                {
                    m_controlador->novoArcoTP(m_cmpOrigem->getIDCP(), novaComponente->getIDCP(), m_peso);
                    delete this;
                    return false;
                }
            }else
            {
                cout << "Erro ao definir arco, não é permitido ligações de transição com transição ou lugar com lugar" << endl;
                QMessageBox msgErro;
                msgErro.setText("Nao e permitido ligacao de lugar com lugar ou transicao com transicao");
                msgErro.exec();
            }
        }else // Primero componente que esta sendo ligado
        {
            m_cmpDestino = novaComponente;
            return true;
        }
    }
    else{
        cout << "Erro ao definir arco, o arco não possui uma rede de petri associada ou o novo componente petri associado ao arco é inválido" << endl;
        QMessageBox msgErro;
        msgErro.setText("Erro ao definir arco, o arco não possui uma rede de petri associada ou o novo componente petri associado ao arco é inválido");
    }
    return false; // Não aceita a ligação
}

/**
 * @brief
 *  Deleta o arco do modelo se ele faz parte do modelo,
 * ou deleta apenas da visualizacao caso ele ainda nao
 * faça parte do modelo.
 *   Um arco só começa a fazer parte do modelo quando
 * ele possui uma origem e um destino definido e válido
 * para o modelo.
 */
void DArco::deleta()
{
    // Se pertence ao modelo e nao e fake
    if(m_cmpOrigem != 0x0 && m_cmpDestino != 0x0 && !m_fake)
    {
        if(m_cmpOrigem->ehLugar() && m_cmpDestino->ehTransicao())
        {
            m_controlador->deletaArcoPT(m_cmpOrigem->getIDCP(), m_cmpDestino->getIDCP());
        }else
        if(m_cmpOrigem->ehTransicao() && m_cmpDestino->ehLugar())
        {
            m_controlador->deletaArcoTP(m_cmpOrigem->getIDCP(), m_cmpDestino->getIDCP());
        }
    }else
    {
        delete this;
    }
}


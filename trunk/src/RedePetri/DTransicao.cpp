#include "DTransicao.h"

#include "DRedePetri.h"

void DTransicao::inicializaDTransicao()
{
    Retangulo::setNome(QString("Transicao %1").arg(id()));
    m_tipoDesenho = TD_TRANSICAO;
    m_controlador = 0x0;

    setCorFundo(Cor::verde);
    setNomeVisivel(true);
    criaAcoes();
    criaMenus();
}

bool DTransicao::mousePrecionado(MouseEvento *novoMouseEvento)
{
    if(novoMouseEvento->botao() == BOTAO_DIREITO)
    {
        mnu->exec(novoMouseEvento->posicaoJanela());
        return true;
    }
    return Retangulo::mousePrecionado(novoMouseEvento);
}

void DTransicao::criaAcoes()
{
    actDeleta = new QAction("Deleta Transicao",this);
    QObject::connect(actDeleta , SIGNAL(triggered()), this, SLOT(deleteta()));
    actExecuta = new QAction("Disparar Transicao",this);
    QObject::connect(actExecuta , SIGNAL(triggered()), this, SLOT(executa()));
    actNovoArco = new QAction("Novo Arco",this);
    QObject::connect(actNovoArco , SIGNAL(triggered()), this, SLOT(novoArco()));
}

void DTransicao::criaMenus()
{
    mnu = new QMenu(widget());
    mnu->addAction(actNovoArco);
    mnu->addAction(actExecuta);
    mnu->addAction(actDeleta);
}


/**
 * @brief
 *  Deleta do modelo
 */
void DTransicao::deleteta()
{
    m_controlador->deletaTransicao(m_IDCP);
}


/**
 * @brief
 *  Dispara uma transicao no modelo
 */
void DTransicao::executa()
{
    m_controlador->executaTransicao(m_IDCP);
}

void DTransicao::novoArco()
{
    // Cria um arco fake para o usuario dizer qual arco ele que inserir na rede
    // o arco decha de ser fake e começa a fazer parte do modelo
    // quando ele possuir uma origem e um destino valido na rede
    DArco *d = new DArco;
    d->setControle(m_controlador);
    d->setLigacaoIni(this);
    d->setFake(true);
    m_pai->novoDesenho(d);
    d->comecaRastriamentoFim();
}

DTransicao::DTransicao():Retangulo(rPonto(10,10), 30 , 10)
{
    inicializaDTransicao();
}

DTransicao::~DTransicao()
{
}

void DTransicao::desenha()
{
    if(m_controlador != 0x0)
    if(m_controlador->sensibilizado(m_IDCP) )
    {
        setCorFundo(Cor::verde);
    }else
    {
        setCorFundo(Cor(0.0f,0.8f,0.0f));
    }
    Retangulo::desenha();
}

void DTransicao::setNome(QString m_nome)
{
//    Retangulo::setNome( QString("t%1 ").arg(m_id) + m_nome);
    Retangulo::setNome(m_nome);
}

bool DTransicao::setControle(ControladorRede *controlador)
{
    m_controlador = controlador;
}

ControladorRede *DTransicao::getControlador()
{
    return m_controlador;
}

bool DTransicao::ehTransicao()
{
    return true;
}

bool DTransicao::ehLugar()
{
    return false;
}

bool DTransicao::ehArco()
{
    return false;
}

string &DTransicao::informacao()
{
    return m_informacao;
}


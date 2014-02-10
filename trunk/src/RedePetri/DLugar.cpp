#include "DLugar.h"
#include "iostream"
#include "RedePetri.h"
#include "DRedePetri.h"
#include "Container.h"

using namespace std;

void DLugar::iniciaDLugar()
{
    m_tipoDesenho = TD_LUGAR;
    m_controlador = 0x0;

    m_numFichas = 0;

    setCorFundo(Cor::amarelo);
    setNomeVisivel(true);
    Circulo::setNome(QString("Lugar %1").arg(id()));
    criaAcoes();
    criaMenus();
}


DLugar::DLugar():Circulo(15, rPonto(20,20), 0x0)
{
    iniciaDLugar();
}

DLugar::~DLugar()
{

}


/**
 * @brief
 *  Define o numero de fichas no modelo
 * @param numFichas - Numero de fichas
 * @return bool
 */
bool DLugar::setFichas(int numFichas)
{
    if(m_controlador != 0x0)
    {
        m_controlador->setFichas(m_IDCP, numFichas);
        return true;
    }
    return false;
}


/**
 * @brief
 *  Define o número de fichas no desenho
 * @param numFichas - Numero de fichas
 */
void DLugar::dSetFichas(unsigned numFichas)
{
    m_numFichas = numFichas;
}


/**
 * @brief
 *  Retorna o numero de fichas do desenho
 * @return unsigned - Numero de fichas
 */
unsigned DLugar::fichas()
{
    return m_numFichas;
}

void DLugar::desenha()
{
    Circulo::desenha();
    desenhaTexto(QString("%1").arg(fichas()), rPonto(10.0f,10.0f), QFont("Times",15, QFont::Bold));

}

void DLugar::setNome(QString nome)
{
 //   Circulo::setNome(QString("p%1 ").arg(m_id) + nome);
    Circulo::setNome(nome);
}

/**
 * @brief
 * Define o controlador da rede
 */
bool DLugar::setControle(ControladorRede *controladorRede)
{
    // Define o controlador
    m_controlador = controladorRede;
}

ControladorRede *DLugar::getControlador()
{
    return m_controlador;
}

bool DLugar::ehTransicao()
{
    return false;
}

bool DLugar::ehLugar()
{
    return true;
}

bool DLugar::ehArco()
{
    return false;
}


/**
 * @brief
 *  Cria um arco com origem neste lugar,
 * habilita o rastriamento do mouse para
 * definir destino com movimento do mouse.
 */
void DLugar::novoArco()
{
    // Cria um arco fake que com a interacao
    // do usuario pode se tornar um arco do modelo
    // quando sua origem e seu destino for definido
    DArco *d = new DArco;
    d->setControle(m_controlador);
    d->setFake(true);
    d->setLigacaoIni(this);
    m_pai->novoDesenho(d);
    d->comecaRastriamentoFim(); // Chame o rastriamento apenas quando ja tiver sido inserido em um container
}


/**
 * @brief
 *  Deleta o lugar do modelo
 */
void DLugar::deleta()
{
    if(m_controlador != 0x0)
        m_controlador->deletaLugar(m_IDCP);
}


/**
 * @brief
 *  Adiciona ficha no modelo
 */
void DLugar::adicionaFicha()
{
    setFichas(fichas() + 1);
}


/**
 * @brief
 *  Remove ficha no modelo
 */
void DLugar::removeFicha()
{
    setFichas(fichas() - 1);
}

/**
 * @brief
 *  Inicializa as ações utilizadas no menu do PopUp Menu,
 * aqui as ações sera inicializadas conectando os sinais em
 * seus devidos slots.
 * Esse metodo só é chamado uma vez durante a construção do objeto.
 */
void DLugar::criaAcoes()
{
    novoArcoAct = new QAction("Novo Arco" ,this);
    QObject::connect(novoArcoAct, SIGNAL(triggered()), this, SLOT(novoArco()));
    deletaAct = new QAction("Deleta" ,this);
    QObject::connect(deletaAct, SIGNAL(triggered()), this, SLOT(deleta()));
    actADDFicha = new QAction("Adiciona Ficha" ,this);
    QObject::connect(actADDFicha, SIGNAL(triggered()), this, SLOT(adicionaFicha()));
    actRMVFicha = new QAction("Remove Ficha" ,this);
    QObject::connect(actRMVFicha, SIGNAL(triggered()), this, SLOT(removeFicha()));
    actNovoArco = new QAction("Novo Arco" ,this);
    QObject::connect(actNovoArco, SIGNAL(triggered()), this, SLOT(novoArco()));
}

/**
 * @brief
 * Inicializa os menus utilizado no POPUP menu dos lugar
 * Esse metodo só é chamado uma vez durante a construção do objeto.
 */
void DLugar::criaMenus()
{
   /**
     @todo - Verificar qual efeito provocado
     se for passado 0x0 como pai do QMenu, pois
     nem sempre o desenho vai ter o desenho mestre
     definido durante a construção do objeto,
     (na verdade nunva vai ter o desenho mestre definido,
     so depois que o pai já foi definido)
      em DTransicao::criaMenus() tbm ocorre o mesmo problema.
   **/
    mnu = new QMenu(widget());
    mnu->addAction(novoArcoAct);
    mnu->addAction(actADDFicha);
    mnu->addAction(actRMVFicha);
    mnu->addAction(deletaAct);
}

bool DLugar::mousePrecionado(MouseEvento *e)
{
    if(e->botao() == BOTAO_DIREITO)
    {
        mnu->exec(e->posicaoJanela());
        return true;
    }
    return Circulo::mousePrecionado(e);
}

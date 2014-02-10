#include "AreaDesenho.h"
#include "Segmento.h"
#include "CirculoBasico.h"
#include "Retangulo.h"
#include "Triangulo.h"
#include "TrianguloModificavel.h"
#include "Seta.h"
#include "DRedePetri.h"
#include "DAmbiente.h"
#include "DNovoAmbiente.h" // Dialog para criar ambientes
#include "DGrafo.h"
#include "CAmbiente.h"
#include "DJogadorRede.h"
#include "TesteContainerGenerico.h"
#include "WebSocket.h"

void AreaDesenho::iniciaAreaDesenho()
{
    static int k;

//    setNome(QString("Area de desenho 1"));
    setNome(QString("Container %1").arg(k++));
    criaAcoes();
    criaMenus();
}

AreaDesenho::AreaDesenho(rPonto posicao ,int largura , int altura, Container *pai):
    Container(posicao,largura, altura, pai)
{
    iniciaAreaDesenho();
}

void AreaDesenho::criaAcoes()
{
    novoSegmentoAct = new QAction("Novo Segmento" ,this);
    QObject::connect(novoSegmentoAct, SIGNAL(triggered()), this, SLOT(novoSegmento()));
    novoCirculoAct = new QAction("Novo Circulo" ,this);
    QObject::connect(novoCirculoAct, SIGNAL(triggered()), this, SLOT(novoCirculo()));
    novoTrianguloAct = new QAction("Novo Triangulo" ,this);
    QObject::connect(novoTrianguloAct, SIGNAL(triggered()), this, SLOT(novoTriangulo()));
    novoTrianguloModificavelAct = new QAction("Novo TrianguloModificavel" ,this);
    QObject::connect(novoTrianguloModificavelAct, SIGNAL(triggered()), this, SLOT(novoTrianguloModificavel()));
    novoRetanguloAct = new QAction("Novo Retangulo" ,this);
    QObject::connect(novoRetanguloAct, SIGNAL(triggered()), this, SLOT(novoRetangulo()));
    novoSetaAct = new QAction("Nova Seta" ,this);
    QObject::connect(novoSetaAct, SIGNAL(triggered()), this, SLOT(novoSeta()));
    novaRedePetriAct = new QAction("Nova Rede Petri", this);
    QObject::connect(novaRedePetriAct, SIGNAL(triggered()), this, SLOT(novaRedePetri()));
    actNovoAmbiente = new QAction("Novo Ambiente", this);
    QObject::connect(actNovoAmbiente , SIGNAL(triggered()), this , SLOT(novoAmbiente()));
    actNovoGrafo = new QAction("Novo Grafo", this);
    QObject::connect(actNovoGrafo , SIGNAL(triggered()), this , SLOT(novoGrafo()));
    actNovoJogador = new QAction("Novo Jogador de Rede de Petri", this);
    QObject::connect(actNovoJogador , SIGNAL(triggered()), this , SLOT(novoJogadorRede()));
    actContainerGenerico = new QAction("Novo Teste Container Generico", this);
    QObject::connect(actContainerGenerico , SIGNAL(triggered()), this , SLOT(novoTesteContainerGenerico()));
}

void AreaDesenho::criaMenus()
{
    mnu = new QMenu(widget());
    mnu->addAction(novaRedePetriAct);
    mnu->addAction(novoSetaAct);
    mnu->addAction(novoRetanguloAct);
    mnu->addAction(novoSegmentoAct);
    mnu->addAction(novoCirculoAct);
    mnu->addAction(novoTrianguloAct);
    mnu->addAction(novoTrianguloModificavelAct);
    mnu->addAction(actNovoAmbiente);
    mnu->addAction(actNovoGrafo);
    mnu->addAction(actNovoJogador);
    mnu->addAction(actContainerGenerico);
}

bool AreaDesenho::mousePrecionado(MouseEvento *e)
{
    if(e->botao() == BOTAO_DIREITO)
    {
        mnu->exec(e->posicaoJanela());
        return true;
    }
    return Container::mousePrecionado(e);
}

void *AreaDesenho::getSuper()
{
    return this;
}

void AreaDesenho::novoSegmento()
{

//    WebSocket *w = new WebSocket;

//    w->handshake();

//    RosBridge *ros = new RosBridge(this);

//    QUrl url("ws://localhost");
//    url.setPort(9090);
//    ros->fazRequisicao(url);

//    ros->enviaRequisicao(QUrl("http://localhost:12344"),QByteArray(RosBridge::advertise("","Machado","string").c_str()));
    Desenho *s = new Segmento();
    s->setCorFundo(Cor::ciano);
    novoDesenho(s);
}

void AreaDesenho::novoCirculo()
{
    Desenho *c = new Circulo();
    c->setCorFundo(Cor::ciano);
    novoDesenho(c);
}

void AreaDesenho::novoTriangulo()
{
    Desenho *t = new Triangulo();
    t->setCorFundo(Cor::ciano);
    novoDesenho(t);
}

void AreaDesenho::novoTrianguloModificavel()
{
    novoDesenho(new TrianguloModificavel(this));
}

void AreaDesenho::novoRetangulo()
{
    Desenho *r = new Retangulo();
    r->setCorFundo(Cor::ciano);
    novoDesenho(r);
}

void AreaDesenho::novoSeta()
{
    Seta *seta = new Seta;
    seta->defineSeta(rPonto(40,40), rPonto(100,100));
    novoDesenho(seta);
}

void AreaDesenho::novaRedePetri()
{
    DRedePetri * rede = new DRedePetri;
    novoDesenho(rede);
}

void AreaDesenho::novoAmbiente()
{
//    Ambiente *novoAmbiente = 0x0;

//    DNovoAmbiente dialogNAmbiente(&novoAmbiente, widget());
//    dialogNAmbiente.exec();

//    if(novoAmbiente != 0x0)
//    {
//        // Cria o controlador do ambiente
//        CAmbiente *controladorAmbiente = new CAmbiente();

//        // Cria a visualização do ambiente
//        DAmbiente *visualizacaoAmbiente = new DAmbiente();

//        // Define o controlador do desenho
//        visualizacaoAmbiente->setControleAmbiente(controladorAmbiente);

//        // Adiciona uma visualização no controlador
//        controladorAmbiente->addVisualizacao(visualizacaoAmbiente);

//        // Adiciona modelo no controlador
//        controladorAmbiente->setModelo(novoAmbiente);

//        novoDesenho(visualizacaoAmbiente);
//    }
}

void AreaDesenho::novoGrafo()
{
    DGrafo *n_grafo = new DGrafo();
    novoDesenho(n_grafo);
}

void AreaDesenho::novoJogadorRede()
{
    DJogadorRede * jogador = new DJogadorRede();
    novoDesenho(jogador);

    jogador->inicia();
}

void AreaDesenho::novoTesteContainerGenerico()
{
    TesteContainerGenerico * t = new TesteContainerGenerico;
    novoDesenho(t);

}

void AreaDesenho::novoDesenho(Desenho *d, bool avisaFilho)
{
    if(d != 0x0)
    {
        if(d->tipoDesenho() != TD_TRANSICAO)
        {
            Container::novoDesenho(d, avisaFilho);
        }else
        {
            QMessageBox msgErro;
            msgErro.setText("Erro, nao e permetido inserir esse desenho fora de uma rede de petri");
            msgErro.exec();
            delete d;
        }
    }
}



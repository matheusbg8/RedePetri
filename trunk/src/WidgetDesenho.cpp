#include "WidgetDesenho.h"
#include <iostream>
#include <QDomNode>
#include <cmath>
#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>
#include "Lugar.h"
#include "Poligono.h"
#include "DRedePetri.h"
#include "DLugar.h"
#include "AreaDesenho.h"
#include "SegmentoAjustavel.h"
#include "ModeloGrafoSimples.h"
#include "Grafo.h"
#include "DGrafo.h"
#include "VisualizadorGrafo.h"
#include "Arco.h"


using namespace std;

void WidgetDesenho::inicializa()
{
    // nada
}

WidgetDesenho::WidgetDesenho(QWidget *parent) :
    QGLWidget(parent)
{
    cout << "Criando GL" << endl;
    inicializa();
    criaAcoes();
    criaMenus();

    // Importante chamar este metodo pq o
    // desenho mestre precisa ser inicializado depois
    // da widget (melhores explicações dentro do metodo)
    inicializaDesenhoMestre();
}

void WidgetDesenho::initializeGL()
{
    cout << "Inicializando GL" << endl;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, width(), 0, height(), -1 ,1);
    glViewport(0, 0, (GLint)width(), (GLint)height());

    // Define o tamanho inicial no DesenhoMestre
    setTamanho(width(), height());

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Cor para apagar a janela


//    glViewport(0,0,(GLsizei) 100,(GLsizei) 100);
//    glOrtho(0.0, 0.0, width(), height(),2,50);
//    glOrtho(0, width(), 0, height(),2,50);
//    glOrtho (0, 256, 0, 256, -1 ,1);     // modo de projecao ortogonal
//    glViewport(0,0, width(),height());

}

void WidgetDesenho::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(GLint) width(), 0,(GLint) height(), -1 ,1);
    glViewport(0, 0, (GLint)width(), (GLint)height());

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_MODELVIEW);

//    cout << "Resizing GL w=" << w << " h=" << h << endl;
//    glViewport(0, 0, (GLint)w, (GLint)h);
}

void WidgetDesenho::paintGL()
{
//    cout << "Painting GL" << endl;
//    glViewport(-100,-100, 1000, 1000);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Pede pro desenhoMestre desenhar todos desenhos
    desenha();
}

void WidgetDesenho::mousePressEvent(QMouseEvent *event)
{
    MouseEvento novoMouseEvento;
    novoMouseEvento.setEvento(MOUSE_PRECIONADO);
    converteQtMouseEvento(&novoMouseEvento , event);

    this->novoMouseEvento(&novoMouseEvento);
    emit atualizaDesenho(selecionado());
}


void WidgetDesenho::mouseReleaseEvent(QMouseEvent *event)
{
    MouseEvento mouseEvento;
    mouseEvento.setEvento(MOUSE_SOLTO);
    converteQtMouseEvento(&mouseEvento, event);

    this->novoMouseEvento(&mouseEvento);
    emit atualizaDesenho(selecionado());
}


void WidgetDesenho::mouseMoveEvent(QMouseEvent *event)
{
    MouseEvento mouseEvento;
    mouseEvento.setEvento(MOUSE_MOVENDO);
    converteQtMouseEvento(&mouseEvento, event);

    this->novoMouseEvento(&mouseEvento);
}


void WidgetDesenho::comando(string cmd)
{

}

int WidgetDesenho::altura()
{
    return height();
}

int WidgetDesenho::largura()
{
    return width();
}

void WidgetDesenho::redesenha()
{
    //    cout << "--------------DESENHANDO TUDO !!! " << endl;
    updateGL();
}

QWidget *WidgetDesenho::getWidget()
{
    return this;
}

/** Desenha texto na tela **/
void WidgetDesenho::desenhaTexto(int x, int y, const QString &str, const QFont &font)
{
    renderText(x,y, str, font);
}

/** Cria um MouseEvento a partir de um QMouseEvent **/
void WidgetDesenho::converteQtMouseEvento(MouseEvento *me ,QMouseEvent *qme)
{
    // Convertendo o sistema de coordenadas do Qt para o do OpenGL
    rPonto p(qme->x() , height() - qme->y());
    BotaoMouse b;

    switch(qme->buttons())
    {
        case Qt::RightButton:
            b = BOTAO_DIREITO;
//            cout << "BotÃ£o direito " << ( (int) BOTAO_DIREITO ) << endl;
        break;
        case Qt::LeftButton:
            b = BOTAO_ESQUERDO;
//            cout << "BotÃ£o esquerdo" << ( (int) BOTAO_ESQUERDO ) << endl;
        break;
        case Qt::MidButton:
            b = BOTAO_MEIO;
 //           cout << "BotÃ£o do meio" << ( (int) BOTAO_MEIO) << endl;
        break;
        case Qt::NoButton:
        // Quando mouse esta movendo, nenhum botÃ£o Ã© retornado pelo Qt
            b = NENHUM_BOTAO;
        break;
    case Qt::XButton1:
//        cout << "XButton1" << endl;
        b = NENHUM_BOTAO;
    break;
    case Qt::XButton2:
//        cout << "XButton2" << endl;
        b = NENHUM_BOTAO;
    break;
        default:
        break;
    }

    me->setBotao(b);
    me->setPosicaoGlobal(p);
    me->setPosicaoLocal(p);
    me->setPosicaoJanela(qme->globalPos());

}

void WidgetDesenho::novaTransicao()
{
    Desenho *d = new DTransicao;
    d->setNomeVisivel(true);
    DesenhoMestre::novoDesenho(d);
    redesenha();
}

void WidgetDesenho::novoLugar()
{
    Desenho *d = new DLugar;
    d->setNomeVisivel(true);
    DesenhoMestre::novoDesenho(d);
    redesenha();
}

void WidgetDesenho::novaRedePetri()
{
    DRedePetri *d = new DRedePetri;
    DRedePetri *d2 = new DRedePetri;

    d2->setControlador(d->controlador());

    DesenhoMestre::novoDesenho(d);
    DesenhoMestre::novoDesenho(d2);
    redesenha();
}

void WidgetDesenho::carregaXMLSimples()
{
    QString nomeArquivo = QFileDialog::getOpenFileName(this, "Abrir xml", QString(), "XML (*.xml)" );

    DRedePetri *rede = new DRedePetri();
    if(rede->carregaXML(nomeArquivo))
    {
        DesenhoMestre::novoDesenhoEmPrincipal(rede);
    }else
    {
            delete rede;
    }
}

void WidgetDesenho::carregaGrafoModeloSimples()
{
//    cout << "Carregando Grafo Modelo Simples" << endl;
//    ModeloGrafoSimples *modeloGrafo = new ModeloGrafoSimples;
//    VisualizadorGrafo *grafo = new VisualizadorGrafo;
//    QString nomeArquivo = QFileDialog::getOpenFileName(this, "Abrir grafo", QString(), "text (*.txt)" );
//    FILE *arq = fopen(nomeArquivo.toStdString().c_str() , "r");

//    DesenhoMestre::novoDesenhoEmPrincipal(grafo);

//    modeloGrafo->carrega(arq);

//    grafo->setModelo(modeloGrafo);

}

void WidgetDesenho::carregaGrafo()
{
    /// @todo - arrumar isso
//    cout << "Carregando Grafo" << endl;
//    Grafo <char> *modeloGrafo = new Grafo<char>;
//    VisualizadorGrafo *grafo = new VisualizadorGrafo;
//    QString nomeArquivo = QFileDialog::getOpenFileName(this, "Abrir grafo", QString(), "text (*.txt)" );
//    FILE *arq = fopen(nomeArquivo.toStdString().c_str() , "r");

//    DesenhoMestre::novoDesenhoEmPrincipal(grafo);

//    modeloGrafo->carrega(arq);

//    grafo->setModelo(modeloGrafo);

}

void WidgetDesenho::alinharDesenhos()
{
    DesenhoMestre::selecionado()->alinhar();
}

void WidgetDesenho::ajustaDesenho(rPonto P)
{
}


void WidgetDesenho::ativarRastriamentoDoMouse(bool simNao)
{
    setMouseTracking(simNao);
}

void WidgetDesenho::criaAcoes()
{
    novaTransicaoAct = new QAction("Nova Transicao" ,this);
    QObject::connect(novaTransicaoAct, SIGNAL(triggered()), this, SLOT(novaTransicao()));
    novoLugarAct = new QAction("Novo Lugar" , this);
    QObject::connect(novoLugarAct, SIGNAL(triggered()), this, SLOT(novoLugar()));
    novoArcoAct = new QAction("Novo Arco" ,this);
    QObject::connect(novoArcoAct, SIGNAL(triggered()), this, SLOT(novoArco()));
    alinharAct = new QAction("Alinhar Desenhos" ,this);
    QObject::connect(alinharAct, SIGNAL(triggered()), this, SLOT(novoArco()));
}

void WidgetDesenho::criaMenus()
{
    mnuFundo = new QMenu(this);
    mnuFundo->addAction(novaTransicaoAct);
    mnuFundo->addAction(novoLugarAct);
    mnuFundo->addAction(novoArcoAct);
    mnuFundo->addAction(alinharAct);
}

/**
 * @brief
 *  Este metodo implementa avisa o resto da interface grafica
 * que um desenho foi selecionado.
 * O Objetivo inicial é mostrar as propriedades desse
 * desenho na twVisuzalizacao (QTreeWidget da interface grafica)
 * @param desenho - Desenho que foi selecionado
 */
void WidgetDesenho::desenhoSelecionado(Desenho *desenho)
{
    emit desenhoEmFoco(desenho);
}

void WidgetDesenho::novoCirculo()
{
/*    SegmentoAjustavel *seg = new SegmentoAjustavel;
    Circulo *circ = new Circulo(10,rPonto(50,50));
    DesenhoMestre::novoDesenho(seg);
    DesenhoMestre::novoDesenho(circ);
    seg->ligaA(circ);
*/
    Circulo *cir = new Circulo();
    cir->setCorFundo(Cor::amarelo);
    DesenhoMestre::novoDesenho(cir);

/*    rPonto p(50, 50);

    teste = new Seta();
    teste->defineSeta(rPonto(10,10), rPonto(90,90));
    desenhos->novoDesenho(teste);
*/
/*
    Circulo *teste = new Circulo();
    teste->defineCirculo(10,rPonto(10,10));
    teste->setCorFundo(Cor::vermelho);
    desenhos->novoDesenho(teste);
*/
//    d->defineSeta(rPonto(10,10), rPonto(200,200));

//    Desenho *d = new Circulo(15, p, this);

//    Desenho *d = new DLugar();
//    DesenhoMestre::novoDesenho(d);
}

void WidgetDesenho::novoRetangulo()
{
//    SegmentoAjustavel *seg = new SegmentoAjustavel;
//    DesenhoMestre::novoDesenho(seg);
//    TesteDesenhoComposto *teste = new TesteDesenhoComposto;
//    DesenhoMestre::novoDesenho(teste);
    Desenho *desenho = new Retangulo();
    DesenhoMestre::novoDesenho(desenho);
}

void WidgetDesenho::novoArco()
{
//    Desenho *d = new DArco;
//    DesenhoMestre::novoDesenho(d);
//    redesenha();
    Desenho *d = new AreaDesenho();
    DesenhoMestre::novoDesenho(d);
    redesenha();
}

void WidgetDesenho::novoDesenho()
{
    rPonto p(50,50);
    cout << "Chamada de novo desenho" << endl;
//    Desenho *d = new Container(p , 100 , 100);
    DRedePetri *d = new DRedePetri();
    DesenhoMestre::novoDesenho(d);

//    Desenho *d = new DRedePetri(this);
//    novoDesenho(d);
}

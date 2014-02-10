#include "JanelaPrincipal.h"
#include "ui_JanelaPrincipal.h"

JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);

    connect(ui->janelaPetri, SIGNAL(atualizaDesenho(Desenho*)), this, SLOT(atulizaDesenho(Desenho*)));
    connect(ui->janelaPetri , SIGNAL(desenhoEmFoco(Desenho*)) , this, SLOT(desenhoEmFoco(Desenho*)));

    criaMenus();
    setWindowTitle("Editor Rede de Petri");
}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
}

void JanelaPrincipal::on_linhaComando_editingFinished()
{

}

void JanelaPrincipal::desenhoEmFoco(Desenho *desenho)
{
//    ui->twVisualizaPropriedade->visualizaDesenho(desenho);
}

void JanelaPrincipal::atulizaDesenho(Desenho *desenho)
{
    ui->twVisualizaPropriedade->visualizaDesenho(desenho);
}

void JanelaPrincipal::on_pbTransicao_clicked()
{
}

void JanelaPrincipal::criaMenus()
{
    mnuArquivo = menuBar()->addMenu("Arquivo");

    actCarregaXMLSimples = new QAction("Carregar XML Simples", this);
    mnuArquivo->addAction(actCarregaXMLSimples);
    connect(actCarregaXMLSimples , SIGNAL(triggered()), ui->janelaPetri, SLOT(carregaXMLSimples()));

    actCarregaGrafoModeloSimples = new QAction("Carregar Grafo Modelo Simples", this);
    mnuArquivo->addAction(actCarregaGrafoModeloSimples);
    connect(actCarregaGrafoModeloSimples , SIGNAL(triggered()), ui->janelaPetri , SLOT(carregaGrafoModeloSimples()));

    actCarregaGrafo = new QAction("Carregar Grafo", this);
    mnuArquivo->addAction(actCarregaGrafo);
    connect(actCarregaGrafo , SIGNAL(triggered()), ui->janelaPetri, SLOT(carregaGrafoModeloSimples()));

    ui->menuBar->setVisible(true);
}

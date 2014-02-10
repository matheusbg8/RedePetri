#include "DVertice.h"
#include "Grafo.h"



void DVertice::criaAcoes()
{
    actDeleta = new QAction("Deleta" , this);
    QObject::connect(actDeleta, SIGNAL(triggered()), this, SLOT(deleta()));

}

void DVertice::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(actDeleta);
}

void DVertice::inicializaDVertice()
{
    m_grafoID = -1;
    m_marcacaoVisivel = false;

    m_tipoDesenho = TD_VERTICE;

    if(m_grafo != 0x0)
    {
        m_grafoID = m_grafo->novoVertice();
    }else
    {
        cout << "DVertice::Construtor - Erro, modelo grafo invalido" << endl;
    }

    criaAcoes();
    criaMenus();
}

void DVertice::deleta()
{
    delete this;
}


bool DVertice::mousePrecionado(MouseEvento *e)
{
    if(e->botao() == BOTAO_DIREITO)
    {
        mnuFundo->exec(e->posicaoJanela());
    }else // Não repassa botoes direito precionado
    {
        Circulo::mousePrecionado(e);
    }
}

DVertice::DVertice(Grafo *grafo)
{
    m_grafo = grafo;

    inicializaDVertice();
}

DVertice::~DVertice()
{
    if(m_grafo != 0x0)
    {
        m_grafo->deletaVertice(m_grafoID);
        m_grafo = 0x0;
    }
}

int DVertice::idGrafo()
{
    return m_grafoID;
}




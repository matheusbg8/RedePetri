#include "DGrafo.h"
#include "GrafoLista.h"

unsigned DGrafo::grafoID = 0;

DGrafo::DGrafo(Grafo *grafo):
    Container(rPonto(10.f,10.f), 200,200)
{
    m_tipoDesenho = TD_REDE_PETRI;
    m_grafoID = grafoID++;

    if(grafo == 0x0)
        m_grafo = new GrafoLista();
    else
        m_grafo = grafo;

    setNome(QString("Grafo %1").arg(m_grafoID));
    criaAcoes();
    criaMenus();
}

DGrafo::~DGrafo()
{
    if(m_grafo == 0x0)
        delete m_grafo;
}

void DGrafo::removeDesenho(Desenho *d)
{
    switch(d->tipoDesenho())
    {
        case TD_VERTICE:
            m_vertices.remove((DVertice*) d);
        break;
        case TD_ARESTA:
            m_arestas.remove((DAresta*) d);
        break;
        default:
         cout << "Grafo Erro: removendo desenho invalido" << endl;
        break;
    }
    Container::removeDesenho(d);
}

void DGrafo::novoDesenho(Desenho *d, bool avisaFilho)
{
    DAresta *nova_aresta;
    DVertice *novo_vertice;

    switch(d->tipoDesenho())
    {
    case TD_ARESTA:
        nova_aresta = (DAresta*) d->getSuper();
        m_arestas.push_back(nova_aresta);
        Container::novoDesenho(d, avisaFilho);
    break;
    case TD_VERTICE:
        novo_vertice = (DVertice*) d->getSuper();
        m_vertices.push_back(novo_vertice);
        Container::novoDesenho(d, avisaFilho);
    break;
    default:
        QMessageBox msg;
        msg.setText("Adicicao de componente invalido no grafo");
        msg.setInformativeText("Voce esta tentando adicionar um componente nao permetido no grafo");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        cout << "Adicionando elemento invalido no grafo" << endl;
        delete d;
    }
}

bool DGrafo::mousePrecionado(MouseEvento *novoMouseEvento)
{
    if(novoMouseEvento->botao() == BOTAO_DIREITO)
    {
        mnuFundo->exec(novoMouseEvento->posicaoJanela());
    }else // Não repassa botao direito
    {
        Container::mousePrecionado(novoMouseEvento);
    }
}

void DGrafo::criaAcoes()
{
    actNovoVertice = new QAction("Novo vertice", this);
    QObject::connect(actNovoVertice , SIGNAL(triggered()), this, SLOT(novoVertice()));

    actNovaAresta = new QAction("Nova Aresta", this);
    QObject::connect(actNovaAresta , SIGNAL(triggered()), this, SLOT(novaAresta()));

    actImprimeDados = new QAction("Imprime Dados", this);
    QObject::connect(actImprimeDados , SIGNAL(triggered()), this, SLOT(imprimeDados()));
}

void DGrafo::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(actNovoVertice);
    mnuFundo->addAction(actNovaAresta);
    mnuFundo->addAction(actImprimeDados);

}

void DGrafo::novaAresta()
{
    DAresta *n_aresta = new DAresta(m_grafo);
    novoDesenho(n_aresta);
}

void DGrafo::novoVertice()
{
    DVertice *n_vertice = new DVertice(m_grafo);
    novoDesenho(n_vertice);
}

void DGrafo::imprimeDados()
{
    imprimeGrafo(m_grafo);
}

void DGrafo::buscaComponentes()
{

}

void DGrafo::buscaProfundidade()
{
}

void DGrafo::buscaLargura()
{
}

#include "VisualizadorGrafo.h"
#include "CirculoBasico.h"
#include "Seta.h"
#include "PosicionadorObjetos2D.h"

Cor VisualizadorGrafo::m_cores[48] =
{
/*    Cor( 30.f, 144.f, 255.f) ,
    Cor(  0.f, 100.f,   0.f) ,
    Cor(124.f, 252.f,   0.f) ,
    Cor(255.f, 215.f,   0.f) ,
    Cor(210.f, 105.f,  30.f) ,
    Cor(250.f, 128.f, 114.f) ,
    Cor(255.f, 140.f,   0.f) ,
    Cor(255.f,  69.f,   0.f) ,
    Cor(255.f,   0.f,   0.f) ,
    Cor(255.f,  20.f, 147.f) ,
    Cor(148.f,   0.f, 211.f) ,
    Cor(139.f,   0.f,   0.f) ,
    Cor(  0.f, 139.f, 139.f) ,
    Cor( 85.f, 107.f,  47.f) ,
    Cor(  0.f,   0.f, 139.f) ,
*/
    Cor(           0.f,           1.f,           0.f) ,
    Cor(           1.f, 128.f / 255.f, 128.f / 255.f) ,
    Cor(           1.f,           1.f, 128.f / 255.f) ,
    Cor( 128.f / 255.f,           1.f, 128.f / 255.f) ,
    Cor(           0.f,           1.f, 128.f / 255.f) ,
    Cor( 128.f / 255.f,           1.f,           1.f) ,
    Cor(           0.f, 128.f / 255.f,           1.f) ,
    Cor(           1.f, 128.f / 255.f, 192.f / 255.f) ,
    Cor(           1.f, 128.f / 255.f,           1.f) ,
    Cor(           1.f,           0.f,           0.f) ,
    Cor(           1.f,           1.f,           0.f) ,
    Cor( 128.f / 255.f,           1.f,           0.f) ,
    Cor(           0.f,           1.f,  64.f / 255.f) ,
    Cor(           0.f,           1.f,           1.f) ,
    Cor(           0.f, 128.f / 255.f, 198.f / 255.f) ,
    Cor( 128.f / 255.f, 128.f / 255.f, 192.f / 255.f) ,
    Cor(           1.f,           0.f,           1.f) ,
    Cor( 128.f / 255.f,  64.f / 255.f,  64.f / 255.f) ,
    Cor(           1.f, 128.f / 255.f,  64.f / 255.f) ,
    Cor(           0.f, 128.f / 255.f, 128.f / 255.f) ,
    Cor(           0.f,  64.f / 255.f, 128.f / 255.f) ,
    Cor( 128.f / 255.f, 128.f / 255.f,           1.f) ,
    Cor( 128.f / 255.f,           0.f,  64.f / 255.f) ,
    Cor(           1.f,           0.f, 128.f / 255.f) ,
    Cor( 128.f / 255.f,           0.f,           0.f) ,
    Cor(           1.f, 128.f / 255.f,           0.f) ,
    Cor(           0.f, 128.f / 255.f,           0.f) ,
    Cor(           0.f, 128.f / 255.f,  64.f / 255.f) ,
    Cor(           0.f,           0.f,           1.f) ,
    Cor(           0.f,           0.f, 160.f / 255.f) ,
    Cor( 128.f / 255.f,           0.f, 128.f / 255.f) ,
    Cor( 128.f / 255.f,           0.f,           1.f) ,
    Cor(  64.f / 255.f,           0.f,           0.f) ,
    Cor( 128.f / 255.f,  64.f / 255.f,           0.f) ,
    Cor(           0.f,  64.f / 255.f,           0.f) ,
    Cor(           0.f,  64.f / 255.f,  64.f / 255.f) ,
    Cor(           0.f,           0.f, 128.f / 255.f) ,
    Cor(           0.f,           0.f,  64.f / 255.f) ,
    Cor(  64.f / 255.f,           0.f,  64.f / 255.f) ,
    Cor(  64.f / 255.f,           0.f, 128.f / 255.f) ,
    Cor(           0.f,           0.f,           0.f) ,
    Cor( 128.f / 255.f, 128.f / 255.f,           0.f) ,
    Cor( 128.f / 255.f, 128.f / 255.f,  64.f / 255.f) ,
    Cor( 128.f / 255.f, 128.f / 255.f, 128.f / 255.f) ,
    Cor(  64.f / 255.f, 128.f / 255.f, 128.f / 255.f) ,
    Cor( 192.f / 255.f, 192.f / 255.f, 192.f / 255.f) ,
    Cor(  64.f / 255.f,           0.f,  64.f / 255.f) ,
    Cor(           1.f,           1.f,           1.f)
};

void VisualizadorGrafo::criaAcoes()
{
    actApagaGrafo = new QAction("Apaga Grafo" , this);
    QObject::connect(actApagaGrafo , SIGNAL(triggered()), this, SLOT(apagaGrafo()) );
}

void VisualizadorGrafo::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(actApagaGrafo);
}

void VisualizadorGrafo::inicilizaCores(Cor a, Cor b, Cor c, unsigned numCores)
{
    if(numCores >= 48)
        numCores = 48;

    float x1 = a.r(), y1 = a.g(), z1 = a.b(),
          x2 = b.r(), y2 = b.g(), z2 = b.g(),
          x3 = c.r(), y3 = c.g(), z3 = c.b(),
          dt = 1.f/numCores, t =0.f, nt;

    /* Curva de Bézier quadratica */
    for(unsigned i=0 ; i < numCores ; i++)
    {
        nt = 1.f - t;
        m_cores[i].set(
            nt*nt*x1 + 2*nt*t*x2 + t*t*x3,
            nt*nt*y1 + 2*nt*t*y2 + t*t*y3,
            nt*nt*z1 + 2*nt*t*z2 + t*t*z3
              );
        t += dt;
    }

}

void VisualizadorGrafo::atualizaVisualizacao()
{
    // Se eu tenho um grafo
    if(m_grafo != 0x0)
    {
        // Deleta todos meus desenhos filhos
        deletaDesenhos();

        unsigned j, u ,v, a, m, n = m_grafo->numVertices();
        list<VerticeGrafo*>::const_iterator i;


        PosicionadorObjetos2D posicionador(rPonto(0.f,0.f), rPonto(m_grafo->numVertices()*30  , m_grafo->numVertices()*30), m_grafo->idMaiorVertice()+1);

        Circulo * circulos[m_grafo->idMaiorVertice()+1];

        setNome(m_grafo->nome().c_str());

        inicilizaCores(Cor::verde, Cor::branco , Cor::azul, n);

        for(i = m_grafo->verticeBegin() ; i != m_grafo->verticeEnd(); i++)
        {
            u = (*i)->id();

            Circulo *c = new Circulo(10,rPonto(20,20));
            circulos[u] = c;
            novoDesenho(c);

            c->setNome(m_grafo->nomeVertice(u).c_str());
            c->setNomeVisivel(true);

//            c->setCorFundo( m_cores[m_grafo->getMarcacao(i)] );
            c->setCorFundo( m_cores[u] );
        }

        for(i = m_grafo->verticeBegin() ; i != m_grafo->verticeEnd(); i++)
        {
            u = (*i)->id();
            m = m_grafo->numSucessor(u);
            for( j = 0 ; j < m; j++)
            {
                v = m_grafo->sucessor(u,j);
                a = m_grafo->idArestaSucessor(u , j);

                Seta *seta = new Seta();

                seta->setNomeSeta(QString(m_grafo->nomeAresta(a).c_str()));
                novoDesenho(seta);

                seta->setLigacaoIni(circulos[u]);
                seta->setLigacaoFim(circulos[v]);
                posicionador.ligaObjeto(u, v);
            }
        }

        posicionador.calculaPosicoes();

        for(j = 0 ; j < n; j++)
        {
            circulos[j]->setPosicao(posicionador.getPosicao(j));
        }
    }
}

bool VisualizadorGrafo::mousePrecionado(MouseEvento *novoMouseEvento)
{
    // Executa o Menu
    if(novoMouseEvento->botao() == BOTAO_DIREITO)
    {
        mnuFundo->exec(novoMouseEvento->posicaoJanela());
        return true;
    }

    //Senão reage como um Container
    return Container::mousePrecionado(novoMouseEvento);
}

VisualizadorGrafo::VisualizadorGrafo(Container *pai):Container(rPonto(10.f,10.f), 100, 100 , pai)
{
    m_grafo = 0x0;
    criaAcoes();
    criaMenus();
}

void VisualizadorGrafo::setModelo(GrafoNome *modelo)
{
    m_grafo = modelo;
    atualizaVisualizacao();
}

GrafoNome* VisualizadorGrafo::getModelo()
{
    return m_grafo;
}

void VisualizadorGrafo::apagaGrafo()
{
    deletaDesenhos();
}

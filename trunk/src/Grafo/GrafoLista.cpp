#include "GrafoLista.h"

int GrafoLista::aresta(unsigned deIdVertice, unsigned paraIdVertice) const
{
    if(m_vertices.existeElemento(deIdVertice) && m_vertices.existeElemento(paraIdVertice))
    {
        for(unsigned i = 0; i < m_g[deIdVertice].size() ; i++)
        {
            if(m_g[deIdVertice][i].first == paraIdVertice)
            {
                return m_g[deIdVertice][i].second;
            }
        }
    }
    return -1;
}


/**
 * @brief
 *  Constroe um grafo utilizando lista de adjacencia
 * @param fabricaVertice - Vertice que sera utilizado para
 * criar novos vertices
 * @param fabricaAresta - Aresta que sera utilizada para
 * criar novas arestas.
 * OBs.: As fábricas são deletadas pelo destrutor do grafo.
 */
GrafoLista::GrafoLista(VerticeGrafo* fabricaVertice, ArestaGrafo* fabricaAresta)
{
    if(fabricaVertice != 0x0)
        m_fabricaVertice = fabricaVertice;
    else
        m_fabricaVertice = new VerticeGrafo;

    if(fabricaAresta != 0x0)
        m_fabricaAresta = fabricaAresta;
    else
        m_fabricaAresta = new ArestaGrafo;
}


/**
 * @brief
 *  Deleta todas arestas e vertices criados, e as
 * fabricas definidas.
 */
GrafoLista::~GrafoLista()
{
    for(int i = 0, max = m_vertices.maiorIndice() ; i <= max ; i++)
    {
        if(m_vertices.existeElemento(i))
        {
            delete m_vertices[i];
        }
    }

    for(int i = 0, max = m_arestas.maiorIndice() ; i <= max ; i++)
    {
        if(m_arestas.existeElemento(i))
        {
            delete m_arestas[i];
        }
    }

    delete m_fabricaVertice;
    delete m_fabricaAresta;
}

Grafo *GrafoLista::novoGrafo() const
{
    return new GrafoLista();
}

unsigned GrafoLista::novoVertice()
{
    return novoVertice(m_fabricaVertice->novoVertice());
}

unsigned GrafoLista::novoVertice(VerticeGrafo *novoVertice)
{
    if(novoVertice == 0x0) return 0;
    if(novoVertice->grafo() != 0x0)
    {
        cout << "Erro ao criar vertice, ele já pertence a um outro grafo" << endl;
        return 0;
    }

    novoVertice->setId(m_vertices.proximoID());
    novoVertice->setGrafo(this);

    m_vertices.adicionaElemento(novoVertice);

    // Se novo vertice esta em uma nova posição
    if(novoVertice->id() >= m_g.size())
    {
        m_g.push_back(vector< pair<unsigned , unsigned> >());
        m_invG.push_back(vector< pair<unsigned , unsigned> >());
    }else // Se novo vertice esta em uma posição não utilizada
    {
        m_g[novoVertice->id()].clear();
        m_invG[novoVertice->id()].clear();
    }
    return novoVertice->id();
}

void GrafoLista::criaVertices(unsigned numVertices)
{
    while(numVertices--)
    {
        novoVertice();
    }
}

int GrafoLista::novaAresta(unsigned deIdVertice, unsigned paraIdVertice, float custo)
{
    // Cria aresta
    ArestaGrafo *nAresta = m_fabricaAresta->novaAresta();
    nAresta->setAresta(deIdVertice , paraIdVertice , custo , 0 , 0x0);// 0 , 0x0 -> definido depois

    // Tenta adicionar
    if(novaAresta(nAresta) >= 0)
        return nAresta->id();

    delete nAresta;
    return -1;
}

int GrafoLista::novaAresta(ArestaGrafo *novaAresta)
{
    if(novaAresta == 0x0) return -1;
    if(novaAresta->grafo() != 0x0)
    {
        cout << "Erro ao adicionar nova aresta ao grafo, aresta ja pertence a outro grafo" << endl;
        return -1;
    }

    unsigned de = novaAresta->de(),
            para = novaAresta->para();

    // Se a aresta é valida
    if(m_vertices.existeElemento(de) && m_vertices.existeElemento(para) && aresta(de, para) == -1)
    {
        novaAresta->setId(m_arestas.proximoID());
        novaAresta->setGrafo(this);

        // Adiciona relacao
        m_g[de].push_back(make_pair( para , novaAresta->id() ));
        m_invG[para].push_back(make_pair( de , novaAresta->id() ));

        // Adiciona
        m_arestas.adicionaElemento(novaAresta);

        return novaAresta->id();
    }
    return -1;
}

bool GrafoLista::deletaVertice(unsigned idVertice)
{
    if(m_vertices.existeElemento(idVertice))
    {
        unsigned i , j , u, v, idAresta;
        m_vertices.removeElemento(idVertice);

        // Remove arestas predecesoras do vertice
        for( i = 0 ; i < m_invG[idVertice].size(); i++) // Para todos u predecessores de idVertice
        {
            u = m_invG[idVertice][i].first;

            for(j = 0 ; j < m_g[u].size() ;j++) // Para todos sucessores de u
            {
                // Se o j-esimo sucessor de u for idVertice, exclui aresta
                if(m_g[u][j].first == idVertice)
                {
                    idAresta = m_g[u][j].second;
                    // Apaga aresta
                    m_arestas.removeElemento(idAresta);
                    // Apaga relacao entre os vertices
                    m_g[u].erase(m_g[u].begin() + j);
                    break;
                }
            }
        }
        m_invG[idVertice].clear();

        // Remove arestas sucessoras
        for( i = 0 ; i < m_g[idVertice].size() ; i++) // Para todos v sucessores de idVertice
        {
            v = m_g[idVertice][i].first;
            for(j = 0; j < m_invG[v].size() ; j++)
            {
                // Se o j-esimo predecessor de v é idVertice, apaga aresta
                if(m_invG[v][j].first == idVertice)
                {
                    idAresta = m_invG[v][j].second;
                    // Apaga aresta
                    m_arestas.removeElemento(idAresta);
                    // Apaga relacao entre os vertices
                    m_invG[v].erase(m_invG[v].begin() + j);
                    break;
                }
            }
        }
        m_g[idVertice].clear();

        return true;
    }
    return false;
}

bool GrafoLista::deletaAresta(unsigned idAresta)
{
    if(m_arestas.existeElemento(idAresta))
    {
        unsigned u = m_arestas[idAresta]->de(),
            v = m_arestas[idAresta]->para(),
            i;

        // Apaga relacao do sucessor
        for(i = 0; i < m_g[u].size() ; i++) // Para todos sucessores de u
        {
            if(m_g[u][i].first == v) // Se o i-esimo sucessor de u for v
            {
                // Apaga relacao
                m_g[u].erase( m_g[u].begin() + i);
                break;
            }
        }

        // Apaga relacao do predecessor
        for( i = 0 ; i < m_invG[v].size() ; i++)// Para todos os predecessores de v
        {
            if(m_invG[v][i].first == u) // Se o i-esimo predecessor de v for u
            {
                // apaga relacao
                m_invG[v].erase(m_invG[v].begin() + i);
                break;
            }
        }

        m_arestas.removeElemento(idAresta);
        return true;
    }
    return false;
}

bool GrafoLista::deletaAresta(unsigned de, unsigned para)
{
    int idAresta = aresta(de , para);
    if(idAresta >= 0 )
    {
        return deletaAresta(idAresta);
    }
    return false;
}

bool GrafoLista::setCustoAresta(unsigned idAresta, float custo)
{
    if(m_arestas.existeElemento(idAresta))
    {
        m_arestas[idAresta]->setCusto(custo);
        return true;
    }
    return false;
 }

unsigned GrafoLista::idMaiorVertice() const
{
    return m_vertices.maiorIndice();
}

unsigned GrafoLista::idMaiorAresta() const
{
    return m_arestas.maiorIndice();
}

unsigned GrafoLista::idProximoVertice() const
{
    return m_vertices.proximoID();
}

unsigned GrafoLista::idProximaAresta() const
{
    return m_arestas.proximoID();
}

bool GrafoLista::existeVertice(unsigned idVertice) const
{
    return m_vertices.existeElemento(idVertice);
}

bool GrafoLista::existeAresta(unsigned idAresta) const
{
    return m_arestas.existeElemento(idAresta);
}

bool GrafoLista::existeAresta(unsigned de, unsigned para) const
{
    return aresta(de, para) != -1;
}

unsigned GrafoLista::numVertices() const
{
    return m_vertices.tamanho();
}

unsigned GrafoLista::numArestas() const
{
    return m_arestas.tamanho();
}

int GrafoLista::numPredecessores(unsigned idVertice) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_invG[idVertice].size();
    }
    return -1;
}

int GrafoLista::predecessor(unsigned idVertice, unsigned i) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_invG[idVertice][i].first;
    }
    return -1;
}

float GrafoLista::custoPredecessor(unsigned idVertice, unsigned i) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_arestas[m_invG[idVertice][i].second]->custo();
    }
    return 0.f;
}

int GrafoLista::idArestaPredecessor(unsigned idVertice, unsigned i) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_invG[idVertice][i].second;
    }
    return -1;
}

int GrafoLista::numSucessores(unsigned idVertice) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_g[idVertice].size();
    }
    return -1;
}

int GrafoLista::sucessor(unsigned idVertice, unsigned i) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_g[idVertice][i].first;
    }
    return -1;
}

float GrafoLista::custoSucessor(unsigned idVertice, unsigned i) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_arestas[m_g[idVertice][i].second]->custo();
    }
    return 0.f;
}

int GrafoLista::idArestaSucessor(unsigned idVertice, unsigned i) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_g[idVertice][i].second;
    }
    return -1;
}

list<VerticeGrafo*>::const_iterator GrafoLista::verticeBegin() const
{
    return m_vertices.begin();
}

list<VerticeGrafo*>::iterator GrafoLista::verticeBegin()
{
    return m_vertices.begin();
}

list<VerticeGrafo*>::const_iterator GrafoLista::verticeEnd() const
{
    return m_vertices.end();
}

list<VerticeGrafo*>::iterator GrafoLista::verticeEnd()
{
    return m_vertices.end();
}


list<ArestaGrafo*>::const_iterator GrafoLista::arestaBegin() const
{
    return m_arestas.begin();
}

list<ArestaGrafo*>::iterator GrafoLista::arestaBegin()
{
    return m_arestas.begin();
}

list<ArestaGrafo*>::const_iterator GrafoLista::arestaEnd() const
{
    return m_arestas.end();
}

list<ArestaGrafo*>::iterator GrafoLista::arestaEnd()
{
    return m_arestas.end();
}

const VerticeGrafo *GrafoLista::vertice(unsigned idVertice) const
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_vertices[idVertice];
    }
    return 0x0;
}

VerticeGrafo *GrafoLista::vertice(unsigned idVertice)
{
    if(m_vertices.existeElemento(idVertice))
    {
        return m_vertices[idVertice];
    }
    return 0x0;
}

const ArestaGrafo *GrafoLista::aresta(unsigned idAresta) const
{
    if(m_arestas.existeElemento(idAresta))
    {
        return m_arestas[idAresta];
    }
    return 0x0;
}

ArestaGrafo *GrafoLista::aresta(unsigned idAresta)
{
    if(m_arestas.existeElemento(idAresta))
    {
        return m_arestas[idAresta];
    }
    return 0x0;
}

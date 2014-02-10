#include "GrafoNome.h"
#include <climits>
#include <sstream>

GrafoNome::GrafoNome(const string &nome, Grafo *g)
{
    m_nome = nome;
    m_grafo = g;
}

/**
    @brief - Este construtor constroe um grafo nomeado pegando
    a estrutura de um grafo nao nomeado e os nomes de um grafo
    nomeado, para que o novo grafo seja construido corretamente
    os IDs dos vertices e das arestas tem que ser os mesmos
    no grafo de nomes e no grafo da estrutura, se algum id
    estiver faltando, sera atribuido um nome padrao.
        Obs.: O grafo estrutura sera utilizado pelo no grafo
    nome, a refrencia ao grafo estrutura nao deve ser utilizada
    e nem destruida apos a utilização nesse construtor.
    @param Grafo *gEstrutura - É o grafo que sera manipulado pelo
    novo GrafoNome.
    @param const GrafoNome *gNomes - É o grafo que sera utilizado
    para nomear os vertices do novo GrafoNome.
**/
GrafoNome::GrafoNome(Grafo *gEstrutura, const GrafoNome *gNomes)
{
    // Define o grafo da estrutura
    m_grafo = gEstrutura;

    m_nomeArestas = gNomes->m_nomeArestas;
    m_nomeVertices = gNomes->m_nomeVertices;
}

GrafoNome::~GrafoNome()
{
    delete m_grafo;
}

const Grafo *GrafoNome::grafo() const
{
    return m_grafo;
}

void GrafoNome::criaVertices(unsigned numVertices)
{
    while(numVertices--)
    {
        novoVertice();
    }
}

pair<const string& , int> GrafoNome::novoVertice(string nome)
{
    unsigned id_vertice = m_grafo->novoVertice();

    if(nome == "")
    {
        stringstream ss;
        ss << 'V' << id_vertice;
        nome = ss.str();
    }


    pair<const string& , int> resp( m_nomeVertices.setNome(id_vertice, nome) , id_vertice );

    return resp;
}

/**
    Retorna o ID da nova aresta, e altera o nome da aresta por referencia
caso o nome nao possa ser registrado, um outro nome sera inserido, o novo
nome sera retornado por referencia.
    Se o ID da aresta for -1, a aresta não pode ser definida.
**/
pair<const string& , int> GrafoNome::novaAresta(unsigned de, unsigned para, float custo, string nome)
{
    int id_aresta = m_grafo->novaAresta(de, para, custo);

    if(id_aresta != -1)
    {
        if(nome == "")
        {
            stringstream ss;
            ss << 'A' << id_aresta;
            nome = ss.str();
        }

        pair<const string& , int> resp(m_nomeArestas.setNome(id_aresta , nome) , id_aresta);
        return resp;
    }


    pair<const string& , int> respNul (GerenciadorNomes::stringNula() , id_aresta);
    return respNul;
}

pair<const string& , int> GrafoNome::novaAresta(const string &de, const string &para, float custo, string nome)
{
    int id_de = m_nomeVertices.id(de),
        id_para = m_nomeVertices.id(para);
    if(id_de == -1 )
    {
        cout << "Erro ao criar nova aresta, vertice " << de << " de origem nao encontrado" << endl;

        pair<const string& , int> respNull( GerenciadorNomes::stringNula() , -1);
        return respNull;
    }
    if(id_para == -1)
    {
        cout << "Erro ao criar nova aresta, vertice " << para << " de destino nao encontrado" << endl;
        pair<const string& , int> respNull( GerenciadorNomes::stringNula() , -1);
        return respNull;
    }

    return novaAresta(id_de , id_para , custo , nome);
}

bool GrafoNome::deletaVertice(unsigned idVertice)
{
    return m_grafo->deletaVertice(idVertice);
}

bool GrafoNome::deletaVertice(const string &vertice)
{
    int id_vertice = m_nomeVertices.id(vertice);

    if(id_vertice != -1)
        return m_grafo->deletaVertice(id_vertice);

    return false;
}

bool GrafoNome::deletaAresta(unsigned idAresta)
{
    return m_grafo->deletaAresta(idAresta);
}

bool GrafoNome::deletaAresta(const string &aresta)
{
    int id_aresta = m_nomeArestas.id(aresta);

    if(id_aresta != -1)
    {
        return m_grafo->deletaAresta(id_aresta);
    }

    return false;
}

bool GrafoNome::deletaAresta(unsigned de, unsigned para)
{
    return m_grafo->deletaAresta(de, para);
}

bool GrafoNome::deletaAresta(const string &de, const string &para)
{
    int id_de = m_nomeVertices.id(de),
             id_para = m_nomeVertices.id(para);

    if(id_de != -1 && id_para != -1)
    {
        return m_grafo->deletaAresta(id_de, id_para);
    }

    return false;
}

bool GrafoNome::setNome(const string &nome)
{
    m_nome = nome;
    return true;
}

/** Define um nome para o vertice
  retornas o novo nome definido para o vertice,
  o nome definido pode ser diferente do nome passado
  por parametro, isso acontece quando o nome passado
  por parametro ja pertence a outro vertice, nesse
  caso o nome sofre algumas modificações para que não
  fique igual ao nome ja existente, o nome final
  atribuido ao vertice, modificado ou nao, é retornado.
**/
const string &GrafoNome::setNomeVertice(unsigned idVertice, const string &nome)
{
    if(m_grafo->existeVertice(idVertice))
    {
        return m_nomeVertices.setNome(idVertice , nome);
    }

    return GerenciadorNomes::stringNula();
}

const string & GrafoNome::setNomeVertice(const string &vertice, const string &nome)
{
    int id_vertice = m_nomeVertices.id(vertice);

    if(id_vertice != -1)
        return m_nomeVertices.setNome(id_vertice, nome);

    return GerenciadorNomes::stringNula();
}

const string& GrafoNome::setNomeAresta(unsigned idAresta, const string &nome)
{
    if(m_grafo->existeAresta(idAresta))
        return m_nomeArestas.setNome(idAresta , nome);

    return GerenciadorNomes::stringNula();
}

const string & GrafoNome::setNomeAresta(const string &aresta, const string &nome)
{
    int id_aresta = m_nomeArestas.id(aresta);

    if(id_aresta != -1)
        return m_nomeArestas.setNome(id_aresta, nome);

    return GerenciadorNomes::stringNula();
}

const string &GrafoNome::nome() const
{
    return m_nome;
}

const string &GrafoNome::nomeVertice(unsigned idVertice) const
{
    if(m_grafo->existeVertice(idVertice))
        return m_nomeVertices.nome(idVertice);

    return GerenciadorNomes::stringNula();
}

const string &GrafoNome::nomeAresta(unsigned idAresta) const
{
    if(m_grafo->existeAresta(idAresta))
        return m_nomeArestas.nome(idAresta);

    return GerenciadorNomes::stringNula();
}

int GrafoNome::idVertice(const string &vertice) const
{
    return m_nomeVertices.id(vertice);
}

int GrafoNome::idAresta(const string &aresta) const
{
    return m_nomeArestas.id(aresta);
}

unsigned GrafoNome::idMaiorVertice() const
{
    return m_grafo->idMaiorVertice();
}

unsigned GrafoNome::idMaiorAresta() const
{
    return m_grafo->idMaiorAresta();
}

bool GrafoNome::existeVertice(unsigned idVertice) const
{
    return m_grafo->existeVertice(idVertice);
}

bool GrafoNome::existeVertice(const string &vertice) const
{
    int id_vertice = m_nomeVertices.id(vertice);
    if(id_vertice != -1)
    {
        return m_grafo->existeVertice(id_vertice);
    }
    return false;
}

bool GrafoNome::existeAresta(unsigned idAresta) const
{
    return m_grafo->existeAresta(idAresta);
}

bool GrafoNome::existeAresta(const string &aresta) const
{
    int id_aresta = m_nomeArestas.id(aresta);
    if(id_aresta != -1)
    {
        return m_grafo->existeAresta(id_aresta);
    }
    return false;
}

unsigned GrafoNome::numVertices() const
{
    return m_grafo->numVertices();
}

unsigned GrafoNome::numArestas() const
{
    return m_grafo->numArestas();
}

int GrafoNome::numPredecessores(unsigned idVertice) const
{
    return m_grafo->numPredecessores(idVertice);
}

int GrafoNome::predecessor(unsigned idVertice, unsigned i) const
{
    return m_grafo->predecessor(idVertice , i);
}

float GrafoNome::custoPredecessor(unsigned idVertice, unsigned i) const
{
    return m_grafo->custoPredecessor(idVertice , i);
}

unsigned GrafoNome::idArestaPredecessor(unsigned idVertice, unsigned i) const
{
    return m_grafo->idArestaPredecessor(idVertice , i);
}

int GrafoNome::numSucessor(unsigned idVertice) const
{
    return m_grafo->numSucessores(idVertice);
}

int GrafoNome::sucessor(unsigned idVertice, unsigned i) const
{
    return m_grafo->sucessor(idVertice , i);
}

float GrafoNome::custoSucessor(unsigned idVertice, unsigned i) const
{
    return m_grafo->custoSucessor(idVertice , i );
}

int GrafoNome::idArestaSucessor(unsigned idVertice, unsigned i) const
{
    return m_grafo->idArestaSucessor(idVertice , i);
}

list<VerticeGrafo*>::const_iterator GrafoNome::verticeBegin() const
{
    return m_grafo->verticeBegin();
}

list<VerticeGrafo*>::const_iterator GrafoNome::verticeEnd() const
{
    return m_grafo->verticeEnd();
}

list<ArestaGrafo*>::const_iterator GrafoNome::arestaBegin() const
{
    return m_grafo->arestaBegin();
}

list<ArestaGrafo*>::const_iterator GrafoNome::arestaEnd() const
{
    return m_grafo->arestaEnd();
}

const VerticeGrafo *GrafoNome::vertice(unsigned idVertice) const
{
    return m_grafo->vertice(idVertice);
}

const ArestaGrafo *GrafoNome::aresta(unsigned idAresta) const
{
    return m_grafo->aresta(idAresta);
}


ostream & operator << (ostream &os, const GrafoNome &gn)
{
    list<ArestaGrafo*>::const_iterator la;
    unsigned u, v, a;

    os << "Grafo " << gn.nome() << ":" << endl;
    for(la = gn.arestaBegin(); la != gn.arestaEnd() ; la++)
    {
        u = (*la)->de();
        v = (*la)->para();
        a = (*la)->id();

        os << "( " << u << " , " << gn.nomeVertice(u)
           << " ) -- ( " <<
             (*la)->custo() << " , " << a << " , " << gn.nomeAresta(a)
           << " ) --> ( " <<
              v << " , " << gn.nomeVertice(v) << " )"
           << endl;
    }

    return os;
}


GrafoNome * inverso(const GrafoNome *g)
{
    return new GrafoNome(inverso(g->grafo()), g);
}

#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "GerenciadorElementos.h"
#include <vector>

using namespace std;


/**
 * @brief
 *  GrafoLista é um tipo de grafo que utiliza
 * lista de adjacencia, esta classe foi criada
 * a partir de uma antiga classe onde era utilizado
 * templates para definir um tipo associado a
 * cada vertice. Nesta implementação é possivel
 * que informações adicionais sejam associadas
 * a cada vertice e a cada aresta, para isso existe
 * duas formas:
 * 1ª - Os vertices e arestas são utilizados como
 * fábricas, essas fábricas são definidas no construtor
 * da classe, informações adicionais podem ser inseridas
 * criando uma nova classe derivada do VerticeGrafo ou
 * da ArestaGrafo e passando uma instancia da classe
 * derivada para o contrutor do Grafo (Solução utilizada
 * para implementa classe Automato).
 * 2º - É associado um ID inteiro a cada aresta e a
 * cada vértice, utilizando o GerenciadoElementos,
 * desta forma é possivel associar informações a cada
 * vertice ou aresta externamente pelos IDs (solução
 * utilizada para implementar classe GrafoNome)
 *  Quando o grafo é destruido todas as arestas e vertices
 * são deletados, inclusive as fábricas.
 */
class GrafoLista : public Grafo
{
protected:

    VerticeGrafo * m_fabricaVertice;
    ArestaGrafo * m_fabricaAresta;

    // Armazena arestas
    GerenciadorElementos <ArestaGrafo*> m_arestas;

    // Armazena vertices
    GerenciadorElementos <VerticeGrafo*> m_vertices;

    // Armazena a relação entre os vertices e as arestas
    //                   destino     id da aresta
    vector< vector< pair< unsigned , unsigned > > > m_g;
    vector< vector< pair< unsigned , unsigned > > > m_invG;

    // Indexacao das arestas nas relacoes (cada pair indexa 1 aresta nas duas lista)
    //          i-esimo g  ,  i-esimo invG
//    vector< pair< unsigned , unsigned > > m_indAresta; nao deu certo porque os indices das listas mudam ao deletar as arestas

    int aresta(unsigned deIdVertice, unsigned paraIdVertice) const;

public:
    GrafoLista(VerticeGrafo* fabricaVertice = 0x0, ArestaGrafo* fabricaAresta = 0x0);
    virtual ~GrafoLista();

    Grafo * novoGrafo() const;

    unsigned novoVertice();

    unsigned novoVertice(VerticeGrafo* novoVertice);

    void criaVertices(unsigned numVertices);

    int novaAresta(unsigned deIdVertice, unsigned paraIdVertice, float custo);

    int novaAresta(ArestaGrafo *novaAresta);

    bool deletaVertice(unsigned idVertice);

    bool deletaAresta(unsigned idAresta);

    bool deletaAresta(unsigned de, unsigned para);

    bool setCustoAresta(unsigned idAresta, float custo);

    unsigned idMaiorVertice() const;

    unsigned idMaiorAresta() const;

    unsigned idProximoVertice() const;

    unsigned idProximaAresta() const;

    bool existeVertice(unsigned idVertice) const;

    bool existeAresta(unsigned idAresta) const;

    bool existeAresta(unsigned de, unsigned para) const;

    unsigned numVertices() const;

    unsigned numArestas() const;

    int numPredecessores(unsigned idVertice) const;

    int predecessor(unsigned idVertice, unsigned i) const;

    float custoPredecessor(unsigned idVertice, unsigned i) const;

    int idArestaPredecessor(unsigned idVertice, unsigned i) const;

    int numSucessores(unsigned idVertice) const;

    int sucessor(unsigned idVertice, unsigned i) const;

    float custoSucessor(unsigned idVertice, unsigned i) const;

    int idArestaSucessor(unsigned idVertice, unsigned i) const;

    list<VerticeGrafo*>::const_iterator verticeBegin() const;
    list<VerticeGrafo*>::iterator verticeBegin();

    list<VerticeGrafo*>::const_iterator verticeEnd() const;
    list<VerticeGrafo*>::iterator verticeEnd();

    list<ArestaGrafo*>::const_iterator arestaBegin() const;
    list<ArestaGrafo*>::iterator arestaBegin();

    list<ArestaGrafo*>::const_iterator arestaEnd() const;
    list<ArestaGrafo*>::iterator arestaEnd();

    const VerticeGrafo* vertice(unsigned idVertice) const;
    VerticeGrafo* vertice(unsigned idVertice);

    const ArestaGrafo* aresta(unsigned idAresta) const;
    ArestaGrafo* aresta(unsigned idAresta);

};

#endif // GRAFOLISTA_H

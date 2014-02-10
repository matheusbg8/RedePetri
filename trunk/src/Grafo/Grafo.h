#ifndef GRAFO_H
#define GRAFO_H

#include "ArestaGrafo.h"
#include "VerticeGrafo.h"
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include "Matriz.h"

using namespace std;


/**
 * @brief
 *  A interface grafo é utilizada para
 * padronizar todas as implementações de grafos.
 */
class Grafo
{
public:

    virtual ~Grafo(){}

    virtual Grafo * novoGrafo() const = 0;

    /**
     * @brief Cria um novo vertice no grafo
     *
     * @return unsigned - ID do vertice criado
     */
    virtual unsigned novoVertice() = 0;

    virtual unsigned novoVertice(VerticeGrafo* vertice) = 0;

    virtual void criaVertices(unsigned numVertices) = 0;

    /**
     * @brief Cria uma nova aresta no grafo
     *
     * @param deIdVertice - ID do vertice de origem da aresta
     * @param paraIdVertice - ID do vertice de destino da aresta
     * @param custo - Custo da aresta
     * @return unsigned - ID da aresta criada, -1 se algo der errado.
     */
    virtual int novaAresta(unsigned deIdVertice, unsigned paraIdVertice, float custo) = 0;

    virtual int novaAresta(ArestaGrafo *novaAresta) = 0;

    /**
     * @brief Deleta um vertice
     *
     * @param idVertice - ID do vertice que sera deletado
     * @return bool - true se foi deletado com sucesso, false
     * caso contrario.
     */
    virtual bool deletaVertice(unsigned idVertice) = 0;


    /**
     * @brief Deleta uma aresta do grafo
     *
     * @param idAresta - ID da aresta que sera deletada
     * @return bool - true se foi deletado com sucesso,
     * false caso contrario, se a aresta nao existe
     * false tambem e retornado.
     */
    virtual bool deletaAresta(unsigned idAresta) = 0;

    /**
     * @brief Deleta uma aresta do grafo
     *
     * @param de - ID do vertice de origem.
     * @param para - ID do vertice de destino.
     * @return bool - true se deletou com sucesso,
     * false caso contrario, se a aresta nao existe
     * false tambem e retornado.
     */
    virtual bool deletaAresta(unsigned de , unsigned para) = 0;



    /**
     * @brief  Define o custo de uma aresta
     *
     * @param idAresta - ID da aresta
     * @param custo - Custo que sera definido
     * @return bool - true se conseguiu definir, false caso contrario.
     */
    virtual bool setCustoAresta(unsigned idAresta, float custo) = 0;

    virtual unsigned idMaiorVertice() const = 0;

    virtual unsigned idMaiorAresta() const = 0;

    virtual unsigned idProximoVertice() const = 0;

    virtual unsigned idProximaAresta() const = 0;

    virtual bool existeVertice(unsigned idVertice) const = 0;

    virtual bool existeAresta(unsigned idAresta) const = 0;

    virtual bool existeAresta(unsigned de, unsigned para) const = 0;

    /**
     * @brief Consulta o numero de vertices
     *
     * @return unsigned - Numero de vertices no grafo
     */
    virtual unsigned numVertices() const = 0;


    /**
     * @brief Consulta o numero de arestas do grafo
     *
     * @return unsigned - Numero de arestas do grafo
     */
    virtual unsigned numArestas() const = 0;


    /**
     * @brief Consulta o numero de predecessores de um vertice
     *
     * @param idVertice - ID do vertice que esta sendo
     * consultado
     * @return unsigned - Numero de Predecessores que o
     * vertice consultado possui, ou -1 se o vertice
     * nao existe.
     */
    virtual int numPredecessores(unsigned idVertice) const = 0;


    /**
     * @brief Consulta um predecessor do vertice
     *
     * @param idVertice - ID do vertice que esta sendo consultado
     * @param i - i-esimo vertice, posicao do vertice predecessor
     * @return unsigned - ID do i-esimo vertice predecessor do
     * vertice cosultado, -1 se algo der errado.
     */
    virtual int predecessor(unsigned idVertice, unsigned i) const = 0;


    virtual float custoPredecessor(unsigned idVertice, unsigned i) const = 0;

    virtual int idArestaPredecessor(unsigned idVertice, unsigned i) const = 0;

    /**
     * @brief Consulta numero de sucessor de um vertice
     *
     * @param idVertice - ID do vertice que sera consultado
     * @return unsigned - Numero de sucessores do vertice
     * consultado, ou -1 se o vertice nao existe.
     */
    virtual int numSucessores(unsigned idVertice) const = 0;


    /**
     * @brief Consulta um sucessor de um vertice
     *
     * @param idVertice - ID do vertice que sera consultado
     * @param i - i-esimo vertice sucessor
     * @return unsigned - ID do i-esimo sucessor do vertice
     * consultado, -1 se algo der errado.
     */
    virtual int sucessor(unsigned idVertice, unsigned i) const = 0;


    virtual float custoSucessor(unsigned idVertice, unsigned i) const = 0;

    virtual int idArestaSucessor(unsigned idVertice, unsigned i) const = 0;

    // Acesso aos vertices e as aretas do grafo

    virtual list<VerticeGrafo*>::const_iterator verticeBegin() const = 0;
    virtual list<VerticeGrafo*>::iterator verticeBegin() = 0;

    virtual list<VerticeGrafo*>::const_iterator verticeEnd() const = 0;
    virtual list<VerticeGrafo*>::iterator verticeEnd() = 0;


    virtual list<ArestaGrafo*>::const_iterator arestaBegin() const = 0;
    virtual list<ArestaGrafo*>::iterator arestaBegin() = 0;

    virtual list<ArestaGrafo*>::const_iterator arestaEnd() const = 0;
    virtual list<ArestaGrafo*>::iterator arestaEnd() = 0;

    virtual const VerticeGrafo* vertice(unsigned idVertice) const = 0;
    virtual const ArestaGrafo* aresta(unsigned idAresta) = 0;

};

// Operações nos grafos
Grafo * inverso(const Grafo *g);

void imprimeGrafo(const Grafo *grafo);

Grafo *criaGrafoArvore(const Grafo *g, vector<unsigned> &precedencias, vector<float> &custos);
Grafo *criaGrafo(const Grafo *g, vector<unsigned> &precedencias, vector<float> &distancia);

// Buscas
void buscaProfundidade(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas);
void buscaProfundidade(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas, stack<unsigned> &verticesVisitados);
void buscaProfundidadeInversa(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas, stack<unsigned> &verticesVisitados);

void buscaLargura(const Grafo *g , unsigned inicio, vector<unsigned> &ordemVisitas, vector<float> &distancia);

void buscaArticulacoes(const Grafo *g, list<unsigned> &articulacoes);

void alcance(const Grafo *g , unsigned idVerticeInicio, stack <unsigned> &verticesAlcancados);

void alcance(const Grafo *g , unsigned idVerticeInicio, queue <unsigned> &verticesAlcancados);

void buscaComponentes(const Grafo *g , vector<unsigned> &componentes);

void buscaComponentesForte(const Grafo *g , vector<unsigned> &componente);

void dijkstra(const Grafo *g , unsigned ini, vector<unsigned> &pre, vector<float> &dist);

void floydWarshall(const Grafo *g , Matriz<unsigned> &precedencia, Matriz<float> &matrizCustos);

void prim(const Grafo *g, unsigned idVerticeRaiz, vector<unsigned> &precedencia, vector<float> &custo);

#endif // GRAFO_H


// TESTES DO GRAFO

/*
#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(5);

    g.novaAresta(0 , 1 , 1.1f);
    g.novaAresta(0 , 2 , 1.2f);
    g.novaAresta(0 , 3 , 1.3f);
    g.novaAresta(2 , 3 , 1.4f);
    g.novaAresta(2 , 4 , 1.5f);

    g.novaAresta(3 , 0 , 1.6f);
    g.novaAresta(3 , 1 , 1.7f);
    g.novaAresta(3 , 2 , 1.8f);
    g.novaAresta(3 , 4 , 1.9f);

    g.novaAresta(4 , 0 , 1.9f);

    unsigned idAresta = g.novaAresta(4 , 1 , 1.9f);

    g.deletaVertice(3);

    g.deletaAresta(idAresta);

    imprimeGrafo(&g);

    return 0;
}
*/


// Teste de inversao do grafo

/*
#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(10);

    g.novaAresta(0 , 1 , 1.f);

    g.novaAresta(0 , 2 , 1.f);

    g.novaAresta(0 , 8 , 1.f);

    g.novaAresta(0 , 9 , 1.f);

    g.deletaVertice(3);
    g.deletaVertice(4);

    g.deletaVertice(6);
    g.deletaVertice(7);

    imprimeGrafo(&g);
    Grafo *inv = inverso(&g);
    imprimeGrafo(inv);
    delete inv;

    return 0;
}
*/


// TESTE buscaProfunda e buscaLargura
/*
#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(5);

    g.novaAresta(0 , 3 , 1.f);
    g.novaAresta(0 , 2 , 1.f);
    g.novaAresta(0 , 1 , 1.f);
    g.novaAresta(1 , 3 , 1.f);
    g.novaAresta(3 , 2 , 1.f);
    g.novaAresta(3 , 4 , 1.f);

    vector<unsigned> visitas;
    vector<float> dist;

    buscaProfundidade(&g, 0 , visitas);
//    buscaLargura(&g, 0 , visitas , dist);

    cout << "Vertice\t|\tOrdVisitas" << endl;

    for(unsigned i = 0 ; i < visitas.size() ; i++)
    {
        if(g.existeVertice(i))
        {
            cout << i << "\t|\t" << visitas[i];
  //          cout << "\tdist " << dist[i];
            cout << endl;
        }
    }
    return 0;
}

//  Resp busca em largura:
//Vertice	|	OrdVisitas
//0	|	1	dist 0
//1	|	4	dist 1
//2	|	3	dist 1
//3	|	2	dist 1
//4	|	5	dist 2
// Resp Busca em Profundidade:
//Vertice	|	OrdVisitas
//0	|	1
//1	|	2
//2	|	5
//3	|	3
//4	|	4
*/


// Teste articulações

/*
#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(14);

    g.novaAresta(0 , 2 , 1.f);
    g.novaAresta(2 , 0 , 1.f);

    g.novaAresta(0 , 3 , 1.f);
    g.novaAresta(3 , 0 , 1.f);

    g.novaAresta(0 , 1 , 1.f);
    g.novaAresta(1 , 0 , 1.f);

    g.novaAresta(0 , 4 , 1.f);
    g.novaAresta(4 , 0 , 1.f);

    g.novaAresta(1 , 5 , 1.f);
    g.novaAresta(5 , 1 , 1.f);

    g.novaAresta(1 , 6 , 1.f);
    g.novaAresta(6 , 1 , 1.f);

    g.novaAresta(3 , 4 , 1.f);
    g.novaAresta(4 , 3 , 1.f);

    g.novaAresta(3 , 6 , 1.f);
    g.novaAresta(6 , 3 , 1.f);

//    g.novaAresta(3 , 7 , 1.f);
//    g.novaAresta(7 , 3 , 1.f);

    g.novaAresta(3 , 9 , 1.f);
    g.novaAresta(9 , 3 , 1.f);

    g.novaAresta(3 , 10 , 1.f);
    g.novaAresta(10 , 3 , 1.f);

    g.novaAresta(5 , 6 , 1.f);
    g.novaAresta(6 , 5 , 1.f);

    g.novaAresta(7 , 8 , 1.f);
    g.novaAresta(8 , 7 , 1.f);

    g.novaAresta(8 , 13 , 1.f);
    g.novaAresta(13 , 8 , 1.f);

    g.novaAresta(9 , 10 , 1.f);
    g.novaAresta(10 , 9 , 1.f);

    g.novaAresta(9 , 11 , 1.f);
    g.novaAresta(11 , 9 , 1.f);

    g.novaAresta(9 , 12 , 1.f);
    g.novaAresta(12 , 9 , 1.f);

    g.novaAresta(10 , 12 , 1.f);
    g.novaAresta(12 , 10 , 1.f);

    list<unsigned> articulacoes;
    list<unsigned>::iterator i;

    buscaArticulacoes(&g , articulacoes);

    cout << "Articulacoes: ";
    for( i = articulacoes.begin(); i != articulacoes.end() ; i++)
    {
        cout << (*i) << ' ';
    }
    cout << endl;


    return 0;
}

// Resp
// Articulacoes: 0 9 3 8


*/


// Teste componentes

/*
#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(7);

    g.novaAresta(0 , 1 , 1.f);
    g.novaAresta(1 , 0 , 1.f);

    g.novaAresta(1 , 2 , 1.f);
    g.novaAresta(2 , 1 , 1.f);

    g.novaAresta(3 , 4 , 1.f);
    g.novaAresta(4 , 3 , 1.f);

    g.novaAresta(3 , 5 , 1.f);
    g.novaAresta(5 , 3 , 1.f);

    vector<unsigned> componentes;
    list<VerticeGrafo*>::iterator i;

    buscaComponentes(&g , componentes);

    cout << "Vertice\t|\tComponente:" << endl;
    for( i = g.verticeBegin(); i != g.verticeEnd() ; i++)
    {
        cout << (*i)->id() << "\t|\t" << componentes[(*i)->id()] << endl;
    }
    cout << endl;


    return 0;
}

//  Resp:
//Vertice	|	Componente:
//0	|	1
//1	|	1
//2	|	1
//3	|	2
//4	|	2
//5	|	2
//6	|	3

*/


// Teste de componentes fortemente conexo

/*

#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(9);

    g.novaAresta(0 , 1 , 1.f);
    g.novaAresta(1 , 2 , 1.f);
    g.novaAresta(2 , 0 , 1.f);

    g.novaAresta(2 , 4 , 1.f);
    g.novaAresta(4 , 5 , 1.f);

    g.novaAresta(6 , 7 , 1.f);
    g.novaAresta(7 , 8 , 1.f);
    g.novaAresta(8 , 6 , 1.f);

    vector<unsigned> componentes;
    list<VerticeGrafo*>::iterator i;

    buscaComponentesForte(&g , componentes);

    cout << "Vertice\t|\tComponente:" << endl;
    for( i = g.verticeBegin(); i != g.verticeEnd() ; i++)
    {
        cout << (*i)->id() << "\t|\t" << componentes[(*i)->id()] << endl;
    }
    cout << endl;

    return 0;
}

//Vertice	|	Componente:
//0	|	3
//1	|	3
//2	|	3
//3	|	2
//4	|	3
//5	|	3
//6	|	1
//7	|	1
//8	|	1

*/

// Teste dijkstra

/*
#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(4);

    g.novaAresta(0 , 1 , 1.f);
    g.novaAresta(0 , 2 , 3.f);
    g.novaAresta(1 , 2 , 1.f);
    g.novaAresta(1 , 2 , 3.f);
    g.novaAresta(2 , 1 , 1.f);
    g.novaAresta(2 , 3 , 1.f);


    vector<unsigned> precendencia;
    vector<float> distancias;

    dijkstra(&g, 0 , precendencia , distancias);

    cout << "Caminho de 0 para 3 : ";

    unsigned i = 3;
    while(precendencia[i] != i)
    {
        cout << i << " <- ";
        i = precendencia[i];
    }
    cout << i << endl;
    cout << "Distancia: " << distancias[3] << endl;


    return 0;
}

// Resp:
// Caminho de 0 para 3 : 3 <- 2 <- 1 <- 0
// Distancia: 3

*/


// Teste FloydWarshall


/*

#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(9);

    g.novaAresta(0 , 1 , 1.f);
    g.novaAresta(0 , 0 , 5.f);

    g.novaAresta(1 , 2 , 2.f);
    g.novaAresta(1 , 3 , 3.f);
    g.novaAresta(2 , 6 , 2.f);
    g.novaAresta(2 , 5 , 3.f);
    g.novaAresta(3 , 4 , 4.f);
    g.novaAresta(3 , 5 , 1.f);
    g.novaAresta(3 , 7 , 1.f);
    g.novaAresta(4 , 8 , 1.f);
    g.novaAresta(5 , 8 , 2.f);
    g.novaAresta(5 , 3 , 1.f);
    g.novaAresta(6 , 8 , 4.f);

    g.novaAresta(8 , 2 , 4.f);
    g.novaAresta(7 , 0 , 4.f);

    Matriz<unsigned> precendencia;
    Matriz<float> distancias;

    floydWarshall(&g , precendencia , distancias);

    unsigned u, v, i, tamVetores = g.idMaiorVertice()+1;
    for(u = 0 ; u < tamVetores ; u++)
    {
        if(g.existeVertice(u))
        for(v = 0 ; v < tamVetores ; v++)
        {
            if(g.existeVertice(v))
            {
                cout << "Menor caminho de " << u << " para " << v << ": ";
                i = v;
                while(precendencia(u,i) != i)
                {
                    cout << i << " <- ";
                    i = precendencia(u ,i);
                }
                cout << i << endl;
                cout << "Distancia: " << distancias(u , v) << endl << endl;

            }
        }
    }

    return 0;
}

Menor caminho de 0 para 0: 0
Distancia: 5

Menor caminho de 0 para 1: 1 <- 0
Distancia: 1

Menor caminho de 0 para 2: 2 <- 1 <- 0
Distancia: 3

Menor caminho de 0 para 3: 3 <- 1 <- 0
Distancia: 4

Menor caminho de 0 para 4: 4 <- 3 <- 1 <- 0
Distancia: 8

Menor caminho de 0 para 5: 5 <- 3 <- 1 <- 0
Distancia: 5

Menor caminho de 0 para 6: 6 <- 2 <- 1 <- 0
Distancia: 5

Menor caminho de 0 para 7: 7 <- 3 <- 1 <- 0
Distancia: 5

Menor caminho de 0 para 8: 8 <- 5 <- 3 <- 1 <- 0
Distancia: 7

Menor caminho de 1 para 0: 0 <- 7 <- 3 <- 1
Distancia: 8

Menor caminho de 1 para 1: 1
Distancia: inf

Menor caminho de 1 para 2: 2 <- 1
Distancia: 2

Menor caminho de 1 para 3: 3 <- 1
Distancia: 3

Menor caminho de 1 para 4: 4 <- 3 <- 1
Distancia: 7

Menor caminho de 1 para 5: 5 <- 3 <- 1
Distancia: 4

Menor caminho de 1 para 6: 6 <- 2 <- 1
Distancia: 4

Menor caminho de 1 para 7: 7 <- 3 <- 1
Distancia: 4

Menor caminho de 1 para 8: 8 <- 5 <- 3 <- 1
Distancia: 6

Menor caminho de 2 para 0: 0 <- 7 <- 3 <- 5 <- 2
Distancia: 9

Menor caminho de 2 para 1: 1 <- 0 <- 7 <- 3 <- 5 <- 2
Distancia: 10

Menor caminho de 2 para 2: 2
Distancia: inf

Menor caminho de 2 para 3: 3 <- 5 <- 2
Distancia: 4

Menor caminho de 2 para 4: 4 <- 3 <- 5 <- 2
Distancia: 8

Menor caminho de 2 para 5: 5 <- 2
Distancia: 3

Menor caminho de 2 para 6: 6 <- 2
Distancia: 2

Menor caminho de 2 para 7: 7 <- 3 <- 5 <- 2
Distancia: 5

Menor caminho de 2 para 8: 8 <- 5 <- 2
Distancia: 5

Menor caminho de 3 para 0: 0 <- 7 <- 3
Distancia: 5

Menor caminho de 3 para 1: 1 <- 0 <- 7 <- 3
Distancia: 6

Menor caminho de 3 para 2: 2 <- 8 <- 5 <- 3
Distancia: 7

Menor caminho de 3 para 3: 3
Distancia: inf

Menor caminho de 3 para 4: 4 <- 3
Distancia: 4

Menor caminho de 3 para 5: 5 <- 3
Distancia: 1

Menor caminho de 3 para 6: 6 <- 2 <- 8 <- 5 <- 3
Distancia: 9

Menor caminho de 3 para 7: 7 <- 3
Distancia: 1

Menor caminho de 3 para 8: 8 <- 5 <- 3
Distancia: 3

Menor caminho de 4 para 0: 0 <- 7 <- 3 <- 5 <- 2 <- 8 <- 4
Distancia: 14

Menor caminho de 4 para 1: 1 <- 0 <- 7 <- 3 <- 5 <- 2 <- 8 <- 4
Distancia: 15

Menor caminho de 4 para 2: 2 <- 8 <- 4
Distancia: 5

Menor caminho de 4 para 3: 3 <- 5 <- 2 <- 8 <- 4
Distancia: 9

Menor caminho de 4 para 4: 4
Distancia: inf

Menor caminho de 4 para 5: 5 <- 2 <- 8 <- 4
Distancia: 8

Menor caminho de 4 para 6: 6 <- 2 <- 8 <- 4
Distancia: 7

Menor caminho de 4 para 7: 7 <- 3 <- 5 <- 2 <- 8 <- 4
Distancia: 10

Menor caminho de 4 para 8: 8 <- 4
Distancia: 1

Menor caminho de 5 para 0: 0 <- 7 <- 3 <- 5
Distancia: 6

Menor caminho de 5 para 1: 1 <- 0 <- 7 <- 3 <- 5
Distancia: 7

Menor caminho de 5 para 2: 2 <- 8 <- 5
Distancia: 6

Menor caminho de 5 para 3: 3 <- 5
Distancia: 1

Menor caminho de 5 para 4: 4 <- 3 <- 5
Distancia: 5

Menor caminho de 5 para 5: 5
Distancia: inf

Menor caminho de 5 para 6: 6 <- 2 <- 8 <- 5
Distancia: 8

Menor caminho de 5 para 7: 7 <- 3 <- 5
Distancia: 2

Menor caminho de 5 para 8: 8 <- 5
Distancia: 2

Menor caminho de 6 para 0: 0 <- 7 <- 3 <- 5 <- 2 <- 8 <- 6
Distancia: 17

Menor caminho de 6 para 1: 1 <- 0 <- 7 <- 3 <- 5 <- 2 <- 8 <- 6
Distancia: 18

Menor caminho de 6 para 2: 2 <- 8 <- 6
Distancia: 8

Menor caminho de 6 para 3: 3 <- 5 <- 2 <- 8 <- 6
Distancia: 12

Menor caminho de 6 para 4: 4 <- 3 <- 5 <- 2 <- 8 <- 6
Distancia: 16

Menor caminho de 6 para 5: 5 <- 2 <- 8 <- 6
Distancia: 11

Menor caminho de 6 para 6: 6
Distancia: inf

Menor caminho de 6 para 7: 7 <- 3 <- 5 <- 2 <- 8 <- 6
Distancia: 13

Menor caminho de 6 para 8: 8 <- 6
Distancia: 4

Menor caminho de 7 para 0: 0 <- 7
Distancia: 4

Menor caminho de 7 para 1: 1 <- 0 <- 7
Distancia: 5

Menor caminho de 7 para 2: 2 <- 1 <- 0 <- 7
Distancia: 7

Menor caminho de 7 para 3: 3 <- 1 <- 0 <- 7
Distancia: 8

Menor caminho de 7 para 4: 4 <- 3 <- 1 <- 0 <- 7
Distancia: 12

Menor caminho de 7 para 5: 5 <- 3 <- 1 <- 0 <- 7
Distancia: 9

Menor caminho de 7 para 6: 6 <- 2 <- 1 <- 0 <- 7
Distancia: 9

Menor caminho de 7 para 7: 7
Distancia: inf

Menor caminho de 7 para 8: 8 <- 5 <- 3 <- 1 <- 0 <- 7
Distancia: 11

Menor caminho de 8 para 0: 0 <- 7 <- 3 <- 5 <- 2 <- 8
Distancia: 13

Menor caminho de 8 para 1: 1 <- 0 <- 7 <- 3 <- 5 <- 2 <- 8
Distancia: 14

Menor caminho de 8 para 2: 2 <- 8
Distancia: 4

Menor caminho de 8 para 3: 3 <- 5 <- 2 <- 8
Distancia: 8

Menor caminho de 8 para 4: 4 <- 3 <- 5 <- 2 <- 8
Distancia: 12

Menor caminho de 8 para 5: 5 <- 2 <- 8
Distancia: 7

Menor caminho de 8 para 6: 6 <- 2 <- 8
Distancia: 6

Menor caminho de 8 para 7: 7 <- 3 <- 5 <- 2 <- 8
Distancia: 9

Menor caminho de 8 para 8: 8
Distancia: inf
*/


// Teste prim()

/*

#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main()
{
    GrafoLista g;
    g.criaVertices(5);

    g.novaAresta(0 , 1 , 2.f);
    g.novaAresta(1 , 0 , 2.f);

    g.novaAresta(0 , 4 , 1.f);
    g.novaAresta(4 , 0 , 1.f);

    g.novaAresta(1 , 2 , 2.f);
    g.novaAresta(2 , 1 , 2.f);

    g.novaAresta(1 , 3 , 3.f);
    g.novaAresta(3 , 1 , 3.f);

    g.novaAresta(1 , 4 , 3.f);
    g.novaAresta(4 , 1 , 3.f);

    g.novaAresta(2 , 3 , 4.f);
    g.novaAresta(3 , 2 , 4.f);

    g.novaAresta(3 , 4 , 1.f);
    g.novaAresta(4 , 3 , 1.f);

    vector<unsigned> precendencia;
    vector<float> custo;

    prim(&g, 0 , precendencia , custo);

    unsigned u, tamVetores = g.idMaiorVertice()+1;
    for(u = 0 ; u < tamVetores ; u++)
    {
        cout << precendencia[u] << " <- " << custo[u] << " -> " << u << endl;
    }

    return 0;
}

// Resp
//0 <- inf -> 0
//0 <- 2 -> 1
//1 <- 2 -> 2
//4 <- 1 -> 3
//0 <- 1 -> 4

*/

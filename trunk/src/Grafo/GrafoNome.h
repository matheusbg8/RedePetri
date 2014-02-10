#ifndef GRAFONOME_H
#define GRAFONOME_H

#include "Grafo.h"
#include "GrafoLista.h"
#include "GerenciadorNomes.h"
#include <string>
#include <map>
using namespace std;

class GrafoNome
{
private:

    // Vertices
    GerenciadorNomes m_nomeVertices;

    // Arestas
    GerenciadorNomes m_nomeArestas;

    // Grafo
    string m_nome;

    Grafo * m_grafo;

public:
    GrafoNome(const string &nome = string(), Grafo* g = new GrafoLista());

    GrafoNome(Grafo *gEstrutura , const GrafoNome *gNomes);

    ~GrafoNome();

    const Grafo* grafo() const;

    void criaVertices(unsigned numVertices);

    pair<const string& , int> novoVertice(string nome = "");

    pair<const string& , int> novaAresta(unsigned de, unsigned para, float custo, string nome = "");
    pair<const string& , int> novaAresta(const string& de , const string& para, float custo, string nome = "");

    bool deletaVertice(unsigned idVertice);
    bool deletaVertice(const string &vertice);

    bool deletaAresta(unsigned idAresta);
    bool deletaAresta(const string& aresta);

    bool deletaAresta(unsigned de, unsigned para);
    bool deletaAresta(const string& de, const string& para);

    bool setNome(const string& nome);

    const string &setNomeVertice(unsigned idVertice , const string& nome);
    const string &setNomeVertice(const string &vertice , const string& nome);

    const string &setNomeAresta(unsigned idAresta,const string& nome);
    const string &setNomeAresta(const string& aresta,const string& nome);

    const string& nome() const;

    const string & nomeVertice(unsigned idVertice) const;

    const string& nomeAresta(unsigned idAresta) const;

    int idVertice(const string& vertice) const;

    int idAresta(const string& aresta) const;

    unsigned idMaiorVertice() const;

    unsigned idMaiorAresta() const;

    bool existeVertice(unsigned idVertice) const;
    bool existeVertice(const string& vertice) const;

    bool existeAresta(unsigned idAresta) const;
    bool existeAresta(const string& aresta) const;

    unsigned numVertices() const;

    unsigned numArestas() const;

    int numPredecessores(unsigned idVertice) const;

    int predecessor(unsigned idVertice, unsigned i) const;

    float custoPredecessor(unsigned idVertice, unsigned i) const;

    unsigned idArestaPredecessor(unsigned idVertice, unsigned i) const;

    int numSucessor(unsigned idVertice) const;

    int sucessor(unsigned idVertice, unsigned i) const;

    float custoSucessor(unsigned idVertice, unsigned i) const;

    int idArestaSucessor(unsigned idVertice, unsigned i) const;

    list<VerticeGrafo*>::const_iterator verticeBegin() const;
    list<VerticeGrafo*>::const_iterator verticeEnd() const;


    list<ArestaGrafo*>::const_iterator arestaBegin() const;
    list<ArestaGrafo*>::const_iterator arestaEnd() const;

    const VerticeGrafo* vertice(unsigned idVertice) const;
    const ArestaGrafo* aresta(unsigned idAresta) const;

};

// Operações nos grafos
ostream & operator << (ostream &os , const GrafoNome& gn);
GrafoNome * inverso(const GrafoNome *g);

#endif // GRAFONOME_H


// Teste GrafoNome
/*

#include <iostream>
#include "GrafoNome.h"

using namespace std;

int main()
{
    GrafoNome gn("Grafo de Teste");

    gn.novoVertice("Bage");
    gn.novoVertice("Santa Maria");
    gn.novoVertice("Porto Alegre");
    gn.novoVertice("Caçapava");
    gn.novoVertice("Canguçu");
    gn.novoVertice("Pelotas");
    gn.novoVertice("Rio Grande");

    gn.novaAresta("Bage", "Caçapava" , 2.f, "BR 153");
    gn.novaAresta("Bage", "Pelotas" , 4.f, "BR 153");

    gn.novaAresta("Caçapava", "Santa Maria" , 2.f);
    gn.novaAresta("Caçapava", "Porto Alegre" , 6.f);
    gn.novaAresta("Caçapava", "Canguçu" , 1.f);


    gn.novaAresta("Canguçu", "Pelotas" , 3.f);

    gn.novaAresta("Pelotas", "Rio Grande" , 1.f);

    GrafoNome *inv_gn = inverso(&gn);

    cout << gn << endl << (*inv_gn);
}


// Resp
//Grafo Grafo de Teste:
//( 0 , Bage ) -- ( 2 , 0 , BR 153 ) --> ( 3 , Caçapava )
//( 0 , Bage ) -- ( 4 , 1 , BR 153 (1) ) --> ( 5 , Pelotas )
//( 3 , Caçapava ) -- ( 2 , 2 , A2 ) --> ( 1 , Santa Maria )
//( 3 , Caçapava ) -- ( 6 , 3 , A3 ) --> ( 2 , Porto Alegre )
//( 3 , Caçapava ) -- ( 1 , 4 , A4 ) --> ( 4 , Canguçu )
//( 4 , Canguçu ) -- ( 3 , 5 , A5 ) --> ( 5 , Pelotas )
//( 5 , Pelotas ) -- ( 1 , 6 , A6 ) --> ( 6 , Rio Grande )

//Grafo :
//( 3 , Caçapava ) -- ( 2 , 0 , BR 153 ) --> ( 0 , Bage )
//( 5 , Pelotas ) -- ( 4 , 1 , BR 153 (1) ) --> ( 0 , Bage )
//( 1 , Santa Maria ) -- ( 2 , 2 , A2 ) --> ( 3 , Caçapava )
//( 2 , Porto Alegre ) -- ( 6 , 3 , A3 ) --> ( 3 , Caçapava )
//( 4 , Canguçu ) -- ( 1 , 4 , A4 ) --> ( 3 , Caçapava )
//( 5 , Pelotas ) -- ( 3 , 5 , A5 ) --> ( 4 , Canguçu )
//( 6 , Rio Grande ) -- ( 1 , 6 , A6 ) --> ( 5 , Pelotas )

*/

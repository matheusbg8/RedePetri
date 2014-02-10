#include "ModeloGrafoSimples.h"
#include <iostream>
using namespace std;



ModeloGrafoSimples::ModeloGrafoSimples()
{
    m_numArestas = 0;
}

unsigned ModeloGrafoSimples::numeroVertices()
{
    return g.size();
}

QString ModeloGrafoSimples::nome()
{
    return QString("Grafo");
}

unsigned ModeloGrafoSimples::marcacao(unsigned id)
{
    if(id < g.size())
        return m_marcacao[id];
    printf("ModeloGrafoSimple:: Erro ao acessar marcacao, id invalido\n");
    return 0;
}

QString ModeloGrafoSimples::nomeVerticeQt(unsigned id)
{
    return QString("%1").arg(id);
}

unsigned ModeloGrafoSimples::numeroAdjacentes(unsigned id)
{
    if( id < g.size())
        return g[id].size();
    cout << "ModeloGraficoSimples:: Erro au acessa numero de adjavcentes, id invalido" << endl;
    return 0;
}

unsigned ModeloGrafoSimples::adjacente(unsigned i, unsigned verticeID)
{
    if( verticeID < g.size() && i < g[verticeID].size())
        return g[verticeID][i];
    cout << "ModeloGrafoSimples::Erro ao acessa adjacente" << endl;
    return 0;
}

float ModeloGrafoSimples::custoAdjacente(unsigned i, unsigned verticeID)
{
    return 1.f;
}

string ModeloGrafoSimples::nomeAdjacente(unsigned i, unsigned verticeID)
{
    return string();
}

void ModeloGrafoSimples::carrega(FILE *arq)
{
// Entrada:
// n vertice  n aresta
// u v
    apagaGrafo();
    if(arq != 0x0)
    {
        int N, M, i, u , v;

        fscanf(arq, "%d %d", &N, &M);
        g.resize(N);
        m_marcacao.resize(N);
        m_numArestas = M;

        for(i = 0 ; i < M ; i++)
        {
            fscanf(arq, "%d %d", &u, &v);
            g[u].push_back(v);
        }
    }
}

void ModeloGrafoSimples::salva(FILE *arq)
{
    if(arq != 0x0)
    {
        int i, j;
        fprintf(arq , "%d %d\n" , g.size() , m_numArestas);
        for(i = 0; i < g.size(); i++)
        {
            for(j =0 ; j < g[i].size(); j++)
            {
                fprintf(arq, "%d %d\n", i , g[i][j]);
            }
        }
    }
}

bool ModeloGrafoSimples::setMarcacao(unsigned id, unsigned marcacao)
{
    if(id < g.size())
    {
        m_marcacao[id] = marcacao;
        return true;
    }
    printf("ModeloGrafoSimples::Erro ao definir macacao, vertice invalido\n");
    return false;
}

void ModeloGrafoSimples::apagaGrafo()
{
    int i;
    for(i = 0 ; i < g.size() ; i++)
    {
        g[i].clear();
    }
    g.clear();
    m_marcacao.clear();
    m_numArestas = 0;
}

bool ModeloGrafoSimples::editavel()
{
    return false;
}

unsigned ModeloGrafoSimples::novoVertice()
{
    return 0;
}

bool ModeloGrafoSimples::atribuiNome(unsigned vID, string nome)
{
    return false;
}

bool ModeloGrafoSimples::apagaVertice(unsigned vID)
{
    return false;
}

void ModeloGrafoSimples::novaAresta(unsigned u, unsigned v, float custo, string nome)
{

}

bool ModeloGrafoSimples::apagaAresta(unsigned uID, unsigned vID)
{
    return false;
}

bool ModeloGrafoSimples::modeloCompleto()
{
    return false;
}


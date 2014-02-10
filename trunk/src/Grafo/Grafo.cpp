#include "Grafo.h"

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits> // Caracteristicas dos inteiros (utilizado maior int)
#include <cfloat> // Caracteristicas dos floats (utilizado maior float como infinito)
#include <cmath>

using namespace std;

Grafo * inverso(const Grafo *g)
{
    if(g == 0x0)
        return 0x0;

    Grafo *r = g->novoGrafo();

    unsigned u, i, numAdj, maiorID = g->idMaiorVertice();
    r->criaVertices(maiorID + 1);

    for(u = 0 ; u <= maiorID ; u++ )
    {
        if(g->existeVertice(u))
        {
            numAdj = g->numSucessores(u);
            for(i = 0 ; i < numAdj ; i++ )
                r->novaAresta(g->sucessor(u, i) , u , g->custoSucessor(u,i));
        }else
        {
            r->deletaVertice(u);
        }
    }

    return r;
}


void imprimeGrafo(const Grafo *grafo)
{
    int numVertices = grafo->numVertices(),
        numArestas = grafo->numArestas();

    cout << "Grafo "<< numVertices << " vertices " << numArestas << " arestas" << endl;

    for(list<ArestaGrafo*>::const_iterator i = grafo->arestaBegin() ; i != grafo->arestaEnd() ; i++)
    {
        cout << (*i)->de() << " -" << (*i)->custo() << "-> " << (*i)->para() << endl;
    }
/*
    for(list<VerticeGrafo*>::const_iterator i = grafo->verticeBegin() ; i!= grafo->verticeEnd() ;i++)
    {
        cout << "Vertice " << (*i)->id() << ':' << endl;
        cout << "NumSucessores: " << grafo->numSucessores((*i)->id()) << endl;
        cout << "NumPredecessores: " << grafo->numPredecessores((*i)->id()) << endl;
    }
*/
}

Grafo *criaGrafoArvore(const Grafo *g, vector<unsigned> &precedencias, vector<float> &custos)
{
    Grafo *g_r = g->novoGrafo();

    g_r->criaVertices(precedencias.size());

    for(unsigned v = 0 ; v < precedencias.size() ;v++)
    {
        // Se v nao e a raiz
        if(precedencias[v] != v)
        {
            g_r->novaAresta(precedencias[v] , v , custos[v]);
        }
        // Se o vertice v nao e alcancavel, ele nao pertence a arvore
        else if(precedencias[v] == UINT_MAX)
        {
            g_r->deletaVertice(v);
        }
    }

    return g_r;
}

Grafo *criaGrafo(const Grafo *g, vector<unsigned> &precedencias, vector<float> &distancia)
{
    Grafo *g_r = g->novoGrafo();
    float custo;

    g_r->criaVertices(precedencias.size());
    for(unsigned v = 0 ; v < precedencias.size() ;v++)
    {
        // Se v nao e a raiz
        if(precedencias[v] != v)
        {
            custo = distancia[precedencias[v]];
            if(custo == INFINITY) // Se o precedente for a raiz
                custo = distancia[v];
            else
                custo -= distancia[v];

            g_r->novaAresta(precedencias[v] , v , custo);
        }
        // Se o vertice v nao e alcancavel, ele nao pertence a arvore
        else if(precedencias[v] == UINT_MAX)
        {
            g_r->deletaVertice(v);
        }
    }

    return g_r;
}

void buscaProfundidade(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas)
{
    // Se o vertice nao existe
    if(!g->existeVertice(idVerticeInicio))
        return;

    stack<unsigned> pilha;
    unsigned u, v , visita = 1;

    // Redimensiona tamanho dos vetores
    int tamVetores = g->idMaiorVertice()+1,
        i;

    ordemVisitas.resize(tamVetores, 0 );

    pilha.push(idVerticeInicio);

    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();

        if(ordemVisitas[u] != 0) // Elimina algumas buscas desnecessarias
            continue;

        ordemVisitas[u] = visita++;

        // Para todo v i-esimo adjacentes a u (predecessores visinhos)
        for(i = 0 ; i < g->numSucessores(u) ;i++)
        {
            v = g->sucessor(u , i);

            // Se v nao foi visitado
            if(ordemVisitas[v] == 0)
            {
                pilha.push(v);
            }
        }
    }
}

/*
  Realiza busc em profundidade, recebe o vetor ordemVisitas que deve ser pre
 inicializado com zero e seu tamanho deve ser >= idMaiorVertice+1 do
 grafo, a medida que a busca é realizada, os vertices visitados sao inseridos
 na pilha e a ordem da visita é colocado na posicao do vetor equivalente
 ao id do vertice no grafo.
   Se o vetor de ordem de visita nao for inicializado com zero a busca
pode nao visitar todos os vertices, se o tamanho do vetor ordemVisitas for
menor que idMaiorVertice + 1 , ele sera redimensionado.
*/
void buscaProfundidade(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas, stack<unsigned> &verticesVisitados)
{
    // Se o vertice nao existe
    if(!g->existeVertice(idVerticeInicio))
        return;

    stack<unsigned> pilha;
    unsigned u, v , visita = 1;

    // Redimensiona tamanho dos vetores
    unsigned tamVetores = g->idMaiorVertice()+1;
    int i;

    if(ordemVisitas.size() < tamVetores)
    {
        ordemVisitas.resize(tamVetores, 0);
    }

    pilha.push(idVerticeInicio);

    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();

        if(ordemVisitas[u] != 0) // Elimina algumas buscas desnecessarias
            continue;

        ordemVisitas[u] = visita++;
        verticesVisitados.push(u);

        // Para todo v i-esimo adjacentes a u (predecessores visinhos)
        for(i = 0 ; i < g->numSucessores(u) ;i++)
        {
            v = g->sucessor(u , i);

            // Se v nao foi visitado
            if(ordemVisitas[v] == 0)
            {
                pilha.push(v);
            }
        }
    }
}

void buscaProfundidadeInversa(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas, stack<unsigned> &verticesVisitados)
{
    // Se o vertice nao existe
    if(!g->existeVertice(idVerticeInicio))
        return;

    stack<unsigned> pilha;
    unsigned u, v , visita = 1;

    // Redimensiona tamanho dos vetores
    unsigned tamVetores = g->idMaiorVertice()+1;

    int i;

    if(ordemVisitas.size() < tamVetores)
    {
        ordemVisitas.resize(tamVetores, 0);
    }

    pilha.push(idVerticeInicio);

    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();

        if(ordemVisitas[u] != 0) // Elimina algumas buscas desnecessarias
            continue;

        ordemVisitas[u] = visita++;
        verticesVisitados.push(u);

        // Para todo v i-esimo adjacentes a u (predecessores visinhos)
        for(i = 0 ; i < g->numPredecessores(u) ;i++)
        {
            v = g->predecessor(u , i);

            // Se v nao foi visitado
            if(ordemVisitas[v] == 0)
            {
                pilha.push(v);
            }
        }
    }
}

void buscaLargura(const Grafo *g , unsigned idVerticeInicio, vector<unsigned> &ordemVisitas, vector<float> &distancia)
{
    // Se o vertice nao existe
    if(!g->existeVertice(idVerticeInicio))
        return;

    queue<unsigned> fila;
    unsigned u, v , visita = 1;

    // Redimensiona tamanho dos vetores
    int tamVetores = g->idMaiorVertice()+1,
        i;

    ordemVisitas.resize(tamVetores, 0);
    distancia.resize(tamVetores, FLT_MAX);


    fila.push(idVerticeInicio);

    distancia[idVerticeInicio] = 0.f;
    ordemVisitas[idVerticeInicio] = visita++;


    while(!fila.empty())
    {
        u = fila.front();
        fila.pop();

        // Para todo v i-esimo adjacentes a u (predecessores visinhos)
        for(i = 0 ; i < g->numSucessores(u) ;i++)
        {
            v = g->sucessor(u , i);

            // Se v nao foi visitado
            if(ordemVisitas[v] == 0)
            {
                ordemVisitas[v] = visita++;
                distancia[v] = distancia[u] + g->custoSucessor(u, i);
                fila.push(v);
            }
        }
    }
}

list<unsigned> *t_list1;
list<unsigned> *t_list2;
vector<unsigned> *t_vector1;
vector<unsigned> *t_vector2;
const Grafo *t_g;
unsigned t_unsigned;

/*
  Este algoritmo encontra os vertices de articulacao
de um grafo não direcionado, ele encontra as artiulacoes
analisando a arvore de busca em profundidade,
ele verifica se um vertice da arvore possui
uma aresta para um vertice que se encontra
em um nivel da arvore assima do dele, essa
aresta é chamada de aresta de retorno (volta
para o vertice de nivel superior da arvore),
se o vertice não possui essa aresta, ele
é o unico caminho até os vertices abaixo dele
sendo então uma articulação (ou vertice de corte)
  Obs.: As folhas da arvore da busca em profundidade
nunca são articulações, a raiz precisa de um
tratamento especial, ela só é uma articulação
se ela possuir mais de um filho.
*/

unsigned _buscaArticulacoes(unsigned idVertice)
{
    // t_vector1 - vetor de visitas
    // t_unsigned - numero da visita
    // t_g - Grafo explorado
    // t_list - Lista de vertices articulados

    unsigned m, // Menor arvore de retorno dos vertices de niveis mais baixos
            min, // Meu menor
            v;
    int i;

    // Recebe o ID da arvore
    (*t_vector1)[idVertice] = t_unsigned;

    // Define como menor atual
    min = t_unsigned;

    // Incrementa os ids de arvores
    t_unsigned++;

    // Para todos v adjacentes a idVertice
    for( i = 0 ; i < t_g->numSucessores(idVertice) ; i++)
    {
        v = t_g->sucessor(idVertice , i);

        // Se v ainda nao foi visitado, ele pertence a arvore da busca em prof.
        if((*t_vector1)[v] == 0)
        {
            m = _buscaArticulacoes(v); // Pega a menor arvore de v

            // Se v nao consegue voltar para um vertice
            // que esta a um nivel acima do meu na arvore
            if( m >= (*t_vector1)[idVertice])
            {// entao só existe o caminho idVertice -> v
             // para chegar em v, entao eu sou um
             // vertice de corte
                t_list1->push_back(idVertice);
            }else if( m < min)
            {
            // Se v consegue volta para um vertice superior,
            // eu tambem consigo passando por v
                min = m;
            }

        // Se v ja foi visitado primeiro que eu
        }else if( (*t_vector1)[v] < min)
        {   // Entao idVertice -> v é uma aresta de retorno
            // que retorna para um vertice que esta a um
            // nivel superior ao meu
            min = (*t_vector1)[v];
        }
    }
    return min;
}

/*
   A busca de articulações deve ser aplicada a grafos nao
dirigidos.

    Aplicavel a Grafos não direcionados
*/
void buscaArticulacoes(const Grafo *g, list<unsigned> &articulacoes)
{
    unsigned maiorID = g->idMaiorVertice()+1;
    vector<unsigned> visitas(maiorID , 0);

    t_g = g;
    t_list1 = &articulacoes;
    t_vector1 = &visitas;
    t_unsigned = 1;

    for(unsigned i = 0 ; i < maiorID ; i++)
    {
        if(g->existeVertice(i) && visitas[i] == 0 && g->numSucessores(i) > 0)
        {
            _buscaArticulacoes(i);

            if(!articulacoes.empty())
                articulacoes.erase(--articulacoes.end());
        }
    }

    t_g = 0x0;
    t_list1 = 0x0;
    t_vector1 = 0x0;
    t_unsigned = 0;
}

/*
    Faz uma busca percorrendo todos os vertices
alcancaveis a partir do vertice idVerticeInicio
e insere na pilha verticesAlcancados
*/
void alcance(const Grafo *g , unsigned idVerticeInicio, stack <unsigned> &verticesAlcancados)
{
    // Se o vertice nao existe
    if(!g->existeVertice(idVerticeInicio))
        return;

    // Redimensiona tamanho dos vetores
    int tamVetores = g->idMaiorVertice()+1,
            i;

    stack<unsigned> pilha;
    vector<char> visitado(tamVetores, false);
    unsigned u, v;

    pilha.push(idVerticeInicio);

    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();

        if(visitado[u]) // Elimina algumas buscas desnecessarias
            continue;

        verticesAlcancados.push(u);
        visitado[u] = true;

        // Para todo v i-esimo adjacentes a u (predecessores visinhos)
        for(i = 0 ; i < g->numSucessores(u) ;i++)
        {
            v = g->sucessor(u , i);

            // Se v nao foi visitado
            if(!visitado[v])
            {   // Agenda visita :)
                pilha.push(v);
            }
        }
    }
}

/*
    Faz uma busca percorrendo todos os vertices
alcancaveis a partir do vertice idVerticeInicio
e insere na pilha verticesAlcancados
*/
void alcance(Grafo *g , unsigned idVerticeInicio, queue <unsigned> &verticesAlcancados)
{
    // Se o vertice nao existe
    if(!g->existeVertice(idVerticeInicio))
        return;

    // Redimensiona tamanho dos vetores
    int tamVetores = g->idMaiorVertice()+1,
            i;

    stack<unsigned> pilha;
    vector<char> visitado(tamVetores, false);
    unsigned u, v;

    pilha.push(idVerticeInicio);

    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();

        if(visitado[u]) // Elimina algumas buscas desnecessarias
            continue;

        verticesAlcancados.push(u);
        visitado[u] = true;

        // Para todo v i-esimo adjacentes a u (predecessores visinhos)
        for(i = 0 ; i < g->numSucessores(u) ;i++)
        {
            v = g->sucessor(u , i);

            // Se v nao foi visitado
            if(!visitado[v])
            {   // Agenda visita :)
                pilha.push(v);
            }
        }
    }
}

/*
    Encontra os componentes de um grafo
não dirigido.

    Aplicavel a Grafos não direcionados
*/
void buscaComponentes(const Grafo *g , vector<unsigned> &componentes)
{
    unsigned idComponente = 0,
            maiorID = g->idMaiorVertice()+1,
            u;

    list<VerticeGrafo*>::const_iterator lu;
    stack<unsigned> pilha;

    componentes.clear();
    componentes.resize(maiorID, 0);

    // Para cada vertice u do grafo
    for(lu = g->verticeBegin() ; lu != g->verticeEnd() ; lu++)
    {
        u = (*lu)->id();
        // Se o vertice não possui componente
        if(componentes[u] == 0)
        {
            alcance(g , u , pilha);
            while(!pilha.empty())
            {
                componentes[pilha.top()] = idComponente;
                pilha.pop();
            }
            idComponente++;
        }
    }
}

void buscaComponentesForte(const Grafo *g , vector<unsigned> &componente)
{
    stack<unsigned> pilha;
    list<VerticeGrafo*>::const_iterator lu;
    unsigned u, id = 1 , tamVetor = g->idMaiorVertice()+1;

    vector<unsigned> visitas(tamVetor, 0);

    componente.clear();
    componente.resize(tamVetor , 0);

    for(lu = g->verticeBegin() ; lu != g->verticeEnd() ; lu++)
    {
        u = (*lu)->id();
        if(visitas[u] == 0)
        {
            buscaProfundidade(g, u , visitas , pilha);
        }
    }

    visitas.clear();
    visitas.resize(tamVetor, 0);

    stack<unsigned> novoComponente;
    id = 1;
    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();
        if(visitas[u] == 0)
        {
            buscaProfundidadeInversa(g, u , visitas , novoComponente);
            while(!novoComponente.empty())
            {
                componente[novoComponente.top()] = id;
                novoComponente.pop();
            }
            id++;
        }
    }
}


/*
    Calcula menor caminho de um vertice para todos os outros
aplicavel a qualquer grafo que não possua ciclo com aresta negativa.
*/
void dijkstra(const Grafo *g , unsigned ini, vector<unsigned> &pre, vector<float> &dist)
{
    unsigned u, v,
          tamVetor = g->idMaiorVertice()+1;

    int i;

    char visitas[tamVetor];

    float peso;

    // Inicializa visitas
    for(u = 0 ; u < tamVetor ; u++)
    {
         visitas[u] = 0;
    }

    dist.clear();
    dist.resize(tamVetor, INFINITY); // Inicializa distancias com infinito

    pre.clear();
    pre.resize(tamVetor, UINT_MAX);


    // Pilha prioridade com custo para chegar no vertice e o indice do vertice
    priority_queue<
    pair<float, unsigned>,
    vector<pair<float, unsigned> >,
    greater< pair<float, unsigned> >  > pilha;

    dist[ini] = 0.f; // Vertice inicial da busca
    pre[ini] = ini; // Predecessor do inicio é ele mesmo

    pilha.push(make_pair(dist[ini],ini));

    while(!pilha.empty())
    {
        u = pilha.top().second;
        pilha.pop();

        if(visitas[u])
            continue;

        visitas[u] = 1;

        for(i = 0; i < g->numSucessores(u) ; i++)
        {
            v = g->sucessor(u,i);
            peso = dist[u] + g->custoSucessor(u,i); // Distancia de ini ate v passando por u

            if(dist[v] > peso)
            {
                dist[v] = peso;
                pre[v] = u;
                pilha.push(make_pair(dist[v], v));
            }
        }
    }
}

/*
  Encontra o menor caminho de todos para todos,
complexidade O ( V^3 ), na verdade V^3 + V^2 + V + A
V num Vertice
A num arestas
*/
void floydWarshall(const Grafo *g , Matriz<unsigned> &precedencia , Matriz<float> &matrizCustos)
{
    unsigned u, v ,k;
    int i;
    float s;
    unsigned tamMatriz = g->idMaiorVertice()+1;

    matrizCustos.apagar();
    matrizCustos.redim(tamMatriz , tamMatriz , INFINITY);

    precedencia.apagar();
    precedencia.redim(tamMatriz, tamMatriz , 0);

    // Inicializa matriz precedencia
    for(u = 0 ; u < tamMatriz ; u++)
    {
        for(v = 0 ; v < tamMatriz ; v++)
        {
            // Inicialmente ninguem tem precedente
            precedencia(u,v) = v;
        }
    }

    // Converte grafo de lista pra grafo de adjacencia
    for(u = 0 ; u < tamMatriz; u++)
    {
        if(g->existeVertice(u))
        for(i = 0; i < g->numSucessores(u) ; i++)
        {
            v = g->sucessor(u , i );
            matrizCustos(u , v ) = g->custoSucessor(u, i);
            precedencia(u , v) = u;
        }
    }

    // Algoritmo floyd
    for(k = 0 ; k < tamMatriz ; k++)
    {
        if(g->existeVertice(k))
        for(u = 0 ; u < tamMatriz ; u++)
        {
            if(g->existeVertice(u))
            for(v = 0 ; v < tamMatriz ; v++)
            {
                if(u == v) continue;

                s = matrizCustos(u ,k) + matrizCustos(k , v);

                // Se existe um caminho menor de i para j passando por k
                if(s < matrizCustos(u ,v))
                {  // Salva o menor caminho
                    matrizCustos(u ,v) = s;
                    precedencia(u ,v ) = precedencia(k ,v );
                }
            }
        }
    }
}

/**
    @brief - Encontra a arvore geradora minima de um grafo não dirigido.
    @param Grafo* g - Grafo que sera pesquisado.
    @param unsigned idVerticeRaiz - ID do veertice que sera a raiz da
    arvore geradora minima MST.
    @param vector<unsigned> &precedencia - São as relações de precedencia
    dos vertices na arvore geradora minima, precedencia[u] é o id do vertice
    que chega em u na MST.
    @param vector<float> &custo - São os custos das arestas da arvore
    geradora minima, custo[u] é o custo para o vertice precedencia[u]
    chegar em u.
**/
void prim(const Grafo* g, unsigned idVerticeRaiz, vector<unsigned> &precedencia , vector<float> &custo)
{
    if(!g->existeVertice(idVerticeRaiz)) return;

    unsigned u,v,
            tamVetor = g->idMaiorVertice()+1;

    int i;

    // A franja armazena a relação dos
    // vertices que são candidatos para
    // entrar na arvore com vertice os
    // vertices que estao na arvore
    // a aresta u <-> frj[u] é uma
    // aresta de corte atual do grafo
    unsigned frj[tamVetor];

    float p;

    // pilha <cuso , vertice> o topo é vertice de menor custo para entrar na arvore
    priority_queue<
    pair<float, unsigned>,
    vector<pair<float, unsigned> >,
    greater< pair<float, unsigned> >  > pilha;

    // Inicialmente ninguem esta na arvore, ninguem tem franja
    precedencia.clear();
    precedencia.resize(tamVetor, UINT_MAX);

    custo.clear();
    custo.resize(tamVetor, INFINITY);

    for(u = 0 ; u < tamVetor; u++)
    {
        frj[u] = UINT_MAX; // UINT_MAX = sem precedencia
    }

    // Apenas idVerticeRaiz esta na arvore, e é a raiz
    precedencia[idVerticeRaiz] = idVerticeRaiz;

    // Atualiza franja e custo dos vertices com relação a raiz
    // Para todos v adjacentes da raiz
    for(i = 0; i < g->numSucessores(idVerticeRaiz) ; i++)
    {
        v = g->sucessor(idVerticeRaiz,i);
        p = g->custoSucessor(idVerticeRaiz,i);

        custo[v] = p;
        frj[v] = 0;
        pilha.push(make_pair(p, v));
    }

    while(!pilha.empty())
    {
        u = pilha.top().second; // pega o vertice que vai entra pra arvore (aquele com menor custo)
        pilha.pop();

        if(precedencia[u] != UINT_MAX) continue; // Elimina vertices repetidos que tiveram seus custos re ajustados por outro vertice.

        // Aresta esta na arvore u <- cust[u] -> pre[u]
        precedencia[u] = frj[u];

        // Atuliza os vertices alcançaveis por u, que agora ja esta na arvore
        for( i = 0; i < g->numSucessores(u) ; i++)
        {
            v = g->sucessor(u,i);
            p = g->custoSucessor(u, i);

            if(precedencia[v] == UINT_MAX)
            {
                if(frj[v] == UINT_MAX || custo[v] > p) // Define ou re-ajusta custo do vertice
                {
                    custo[v] = p;
                    frj[v] = u;
                    pilha.push(make_pair(p, v));
                }
            }
        }
    }
}

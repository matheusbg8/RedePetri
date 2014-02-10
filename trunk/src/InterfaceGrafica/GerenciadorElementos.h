#ifndef GERENCIADORELEMENTOS_H
#define GERENCIADORELEMENTOS_H

#include <vector>
#include <list>
#include <stack>
#include <iostream>
using namespace std;

template <class Tipo>
/**
 * @brief
 *      Esta calasse faz o gerenciamento de elementos
 * indexados, gerencia a criação e exclusão de elementos
 * atribuindo um ID para cada elemento.
 *      Cada elemento é indexado em um vector, quando um
 * elemento é excluido, os IDs dos outros elementos
 * não são alterados, desta forma um buraco na sequencia
 * de IDs é gerado, para tapar os buracos de endexacao
 * é utilizado uma pilha com as posicoes dos buracos,
 * quando novos elementos sao criados, e atribuido o
 * id de um buraco.
 *  Para associar alguma informação indexada pelos indices
 * dos elementos gerenciados por essa classe, é necessario
 * cria um vector do tamanho idMaiorElemento() + 1, desta
 * forma é garantido que o vector cobre todos os IDs dos
 * elemenetos, embora algumas posições não serão utilizadas
 * por causa dos buracos, o GerenciadorElementos tenta
 * sempre reduzir o tamanhos dos buracos com a pilha.
*/
class GerenciadorElementos
{
private:
    typedef typename std::list<Tipo> TList;
    typedef typename TList::iterator iterator;

public:
    typedef typename TList::const_iterator const_iterator;

private:

    vector< pair<iterator, bool> > m_indElemento; // Indexacao dos elementos

    list<Tipo> m_elementos;
    mutable stack<int> m_proximos;
    int m_numElementos;

public:

    GerenciadorElementos();


    int proximoID() const;

    int adicionaElemento(const Tipo &valor);
    int adicionaElemento(const Tipo &valor, int id);

    void removeElemento(unsigned id);
    void apagaTudo();

    int tamanho() const;
    int maiorIndice() const;

    Tipo & operator[](int id);
    const Tipo & operator[](int id) const;

    bool existeElemento(unsigned id) const;

    /**
     * @brief
     *  Retorna interador para o inicio da lista de elementos
     * @return const list<Tipo>::iterator - Iterador para lisa de elementos
     */
    iterator begin()
    {
        return m_elementos.begin();
    }

    const_iterator begin() const
    {
        return m_elementos.begin();
    }

    /**
     * @brief
     *  Retorna interador para depois do fm da lista de elementos
     * @return const list<Tipo>::iterator - iterador
     */
    iterator end()
    {
        return m_elementos.end();
    }

    const_iterator end() const
    {
        return m_elementos.end();
    }

};
#include "GerenciadorElementos.cpp"

#endif // GERENCIADORELEMENTOS_H


/*

#include <iostream>
using namespace std;

#include "GerenciadorElementos.h"

// Teste do gerenciamento de elementos
int main()
{
    GerenciadorElementos<int> t;
    int i;

    for(i = 0 ; i < 10; i++)
    {
        t.adicionaElemento(i);
    }

    t.removeElemento(3);
    t.removeElemento(8);
    t.removeElemento(5);
    t.removeElemento(9);

    t.adicionaElemento(11);
    t.adicionaElemento(12, 15);
    t.adicionaElemento(13);
    t.adicionaElemento(14);
    t.adicionaElemento(15);
    t.adicionaElemento(16);
    t.adicionaElemento(17);
    t.adicionaElemento(18);
    t.adicionaElemento(19);
    t.adicionaElemento(20,24);
    t.adicionaElemento(21);


    cout << "Tamanho: " << t.tamanho() << endl;
    for(i= 0; i<= t.maiorIndice(); i++)
    {
        cout << "ID " << i << " : ";
        if(t.existeElemento(i))
        {
            cout <<  t[i] << endl;
        }else
        {
            cout << "Vazio" << endl;
        }
    }
    cout << "Proximo ID: " << t.proximoID() << endl;

    cout << "Teste dos iteradores" << endl;
    for( list<int>::iterator i = t.begin() ; i != t.end() ; i++)
    {
        cout << (*i) << endl;
    }
}
*/

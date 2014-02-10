#ifndef GERENCIADORNOMES_H
#define GERENCIADORNOMES_H

#include <string>
#include <vector>
#include <map>

using namespace std;

/**
  @brief - Esta classe faz o gerenciador de nome de elementos,
  ela mapeia um nome para um undigned ID, e um  ID para
  um nome.
   Os IDs são indexados utilizando um vector por contiguidade fisica
   e os nomes são mapeados por uma arvore binaria da std::map.
   Os elementos são inseridos utilizando o metodo setNome(id, nome).
**/
class GerenciadorNomes
{
public:
    typedef map<string , unsigned > MMAp;
    typedef pair<MMAp::iterator , bool > PMiB;

private:
/*
  Sobre os interadores serem armazenados no vector, pq q da cero
Retirado da documentacao:
  Map has the important property that inserting a new element
 into a map does not invalidate iterators that point to existing
 elements. Erasing an element from a map also does not invalidate
 any iterators, except, of course, for iterators that actually
 point to the element that is being erased.
*/

    // Indexacao dos elementos do mapa
    vector< pair<MMAp::iterator, bool> > m_nome;
    // iterator aponta para elemento do map,
    // bool indica se iterator esta apontando  ou nao

    // Mapa de nome de cada elemento
    MMAp m_mapaNome;

    // String vazia utilizada para retorna quando
    // elemento nao tem nome atribuido
    static string strNula;

public:
    GerenciadorNomes();    

    GerenciadorNomes(const GerenciadorNomes & gn);

    const GerenciadorNomes & operator = (const GerenciadorNomes & gn);

    const string &setNome(unsigned id, const string& nome);

    const string& nome(unsigned id) const;

    int id(const string& nome) const;

    void apaga(unsigned id);

    void apaga(const string& nome);

    static const string & stringNula();
};

#endif // GERENCIADORNOMES_H


// Teste GerenciadorNomes

/*

#include <iostream>
#include <GerenciadorNomes.h>

using namespace std;

int main()
{
    GerenciadorNomes gn;

    cout << "Adicionado " << gn.setNome(9, string("Carro")) << endl;

    cout << "Adicionado " << gn.setNome(5, string("Ola")) << endl;

    cout << "Adicionado " <<  gn.setNome(9, string("Cachorro")) << endl;

    cout << "Adicionado " << gn.setNome(1, string("Ola")) << endl;

    cout << "Adicionado " << gn.setNome(3, string("Ola")) << endl;

    cout << "Adicionado " << gn.setNome(4, string("Deletado")) << endl;

    cout << "Adicionado " << gn.setNome(6, string("ID Deletado")) << endl;

    cout << "Adicionado " << gn.setNome(3, string("Casa")) << endl;

    gn.apaga(2);
    gn.apaga(100);
    gn.apaga("jshdas");
    gn.apaga("Deletado");
    gn.apaga(6);

    for(unsigned i = 0 ; i < 15 ; i++)
        cout << "Nome do id " << i << " = (" << gn.nome(i) << ")" << endl;
    return 0;
}


// Resp
//Adicionado Carro
//Adicionado Ola
//Adicionado Cachorro
//Adicionado Ola (1)
//Adicionado Ola (2)
//Adicionado Deletado
//Adicionado ID Deletado
//Adicionado Casa
//Nome do id 0 = ()
//Nome do id 1 = (Ola (1))
//Nome do id 2 = ()
//Nome do id 3 = (Casa)
//Nome do id 4 = ()
//Nome do id 5 = (Ola)
//Nome do id 6 = ()
//Nome do id 7 = ()
//Nome do id 8 = ()
//Nome do id 9 = (Cachorro)
//Nome do id 10 = ()
//Nome do id 11 = ()
//Nome do id 12 = ()
//Nome do id 13 = ()
//Nome do id 14 = ()
*/

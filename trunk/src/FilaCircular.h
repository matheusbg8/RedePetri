#ifndef FILACIRCULAR_H
#define FILACIRCULAR_H

template< typename Tipo= int>
class FilaCircular
{
    int m_ini, m_fim;
    int m_tam;
    int m_numElementos;

    Tipo *m_fila;
public:
    FilaCircular(int tamanho= 10);
    ~FilaCircular();

    void push(const Tipo &elemento);
    Tipo pop();

    Tipo top() const;
    Tipo elemento(int i) const;
    Tipo elemento(int i,int aPartirElemento) const;

    int idTopo() const;
    int idElemento(int i, int aPartirElemento) const;
    int numElementosAtraz(int idElemento) const;

    bool vazia() const;
    bool cheia() const;

    int numElementos() const;
    int tamanho() const;
};

#include "FilaCircular.cpp"

#endif // FILACIRCULAR_H



/*
// Teste fila circular

#include <iostream>
#include "FilaCircular.h"

using namespace std;

int main(int argc, char *argv[])
{
    int i , j;
    FilaCircular <int> buffer(4);

    for(i = 0 ; i < 10; i++)
    {
        buffer.push(i);

        cout << "topo " << buffer.top() << " Num Elementos " << buffer.numElementos() << " vazio " << buffer.vazia() << " cheio " << buffer.cheia() << endl;
        for(j = 0 ; j < buffer.numElementos() ; j++)
        {
            cout << j << " : " << buffer.elemento(j) << endl;
        }
    }

    for(i = 0 ; i < 12; i++)
    {
        cout << "topo " << buffer.top() << " Num Elementos " << buffer.numElementos() << " vazio " << buffer.vazia() << " cheio " << buffer.cheia() << endl;
        buffer.pop();
    }
}

// Respoata esperada
topo 0 Num Elementos 1 vazio 0 cheio 0
0 : 0
topo 0 Num Elementos 2 vazio 0 cheio 0
0 : 0
1 : 1
topo 0 Num Elementos 3 vazio 0 cheio 0
0 : 0
1 : 1
2 : 2
topo 0 Num Elementos 4 vazio 0 cheio 1
0 : 0
1 : 1
2 : 2
3 : 3
topo 1 Num Elementos 4 vazio 0 cheio 1
0 : 1
1 : 2
2 : 3
3 : 4
topo 2 Num Elementos 4 vazio 0 cheio 1
0 : 2
1 : 3
2 : 4
3 : 5
topo 3 Num Elementos 4 vazio 0 cheio 1
0 : 3
1 : 4
2 : 5
3 : 6
topo 4 Num Elementos 4 vazio 0 cheio 1
0 : 4
1 : 5
2 : 6
3 : 7
topo 5 Num Elementos 4 vazio 0 cheio 1
0 : 5
1 : 6
2 : 7
3 : 8
topo 6 Num Elementos 4 vazio 0 cheio 1
0 : 6
1 : 7
2 : 8
3 : 9
topo 6 Num Elementos 4 vazio 0 cheio 1
topo 7 Num Elementos 3 vazio 0 cheio 0
topo 8 Num Elementos 2 vazio 0 cheio 0
topo 9 Num Elementos 1 vazio 0 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0

*/

/*

// Teste 2 fila crcular


#include <iostream>
#include "FilaCircular.h"

using namespace std;

int main(int argc, char *argv[])
{
    int i , j, id=0;
    FilaCircular <int> buffer(5);

    for(i = 0 ; i < 8; i++)
    {
        buffer.push(i);

        cout << "topo " << buffer.top() << " Num Elementos " << buffer.numElementos() << " vazio " << buffer.vazia() << " cheio " << buffer.cheia() << endl;
        for(j = 0 ; j < buffer.numElementos() ; j++)
        {
            cout << j << " : " << buffer.elemento(j) << endl;
        }

        if(i%3==0)
        {
            cout << buffer.numElementosAtraz(id) << " Novos elementos desde a ultima verificacao" << endl;
            for(j = 1; j<= buffer.numElementosAtraz(id); ++j)
            {
                cout << "NOVO ELEMENTO " << buffer.elemento(id,j) << endl;
            }
            id = buffer.idElemento(buffer.numElementosAtraz(id),id);
        }
    }

    for(i = 0 ; i < 9; i++)
    {
        cout << "topo " << buffer.top() << " Num Elementos " << buffer.numElementos() << " vazio " << buffer.vazia() << " cheio " << buffer.cheia() << endl;
        buffer.pop();
    }
}

topo 0 Num Elementos 1 vazio 0 cheio 0
0 : 0
0 Novos elementos desde a ultima verificacao
topo 0 Num Elementos 2 vazio 0 cheio 0
0 : 0
1 : 1
topo 0 Num Elementos 3 vazio 0 cheio 0
0 : 0
1 : 1
2 : 2
topo 0 Num Elementos 4 vazio 0 cheio 0
0 : 0
1 : 1
2 : 2
3 : 3
3 Novos elementos desde a ultima verificacao
NOVO ELEMENTO 1
NOVO ELEMENTO 2
NOVO ELEMENTO 3
topo 0 Num Elementos 5 vazio 0 cheio 1
0 : 0
1 : 1
2 : 2
3 : 3
4 : 4
topo 1 Num Elementos 5 vazio 0 cheio 1
0 : 1
1 : 2
2 : 3
3 : 4
4 : 5
topo 2 Num Elementos 5 vazio 0 cheio 1
0 : 2
1 : 3
2 : 4
3 : 5
4 : 6
3 Novos elementos desde a ultima verificacao
NOVO ELEMENTO 4
NOVO ELEMENTO 5
NOVO ELEMENTO 6
topo 3 Num Elementos 5 vazio 0 cheio 1
0 : 3
1 : 4
2 : 5
3 : 6
4 : 7
topo 3 Num Elementos 5 vazio 0 cheio 1
topo 4 Num Elementos 4 vazio 0 cheio 0
topo 5 Num Elementos 3 vazio 0 cheio 0
topo 6 Num Elementos 2 vazio 0 cheio 0
topo 7 Num Elementos 1 vazio 0 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0
topo 0 Num Elementos 0 vazio 1 cheio 0

*/


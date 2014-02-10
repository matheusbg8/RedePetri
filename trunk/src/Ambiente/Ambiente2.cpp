#include "Ambiente2.h"

Ambiente2::Ambiente2()
{
    m_nodos.push_back(0x0);
}

NodoAmbiente2 *Ambiente2::nodo(const string &nome)
{
    map<string , unsigned>::iterator ln = m_mapaNodos.find(nome);
    unsigned idNodo = ln->second;

    //Verifica se foi encontrado
    if( ln  == m_mapaNodos.end())
    {
        // não foi
        return 0x0;
    }

    return m_nodos[idNodo];
}

unsigned Ambiente2::adiciona(NodoAmbiente2 *novoNodo, bool forcado)
{
    const string nome = novoNodo->nome();
    if(!nodo(nome))
    {
        unsigned id = m_nodos.size();
        m_nodos.push_back(novoNodo);
        return id;
    }
    return 0;
}

#include "FilaCircular.h"

template < typename Tipo>
FilaCircular<Tipo>::FilaCircular(int tamanho)
{
    m_fila = new Tipo[tamanho];
    m_tam = tamanho;
    m_numElementos = 0;
    m_ini = 0;
    m_fim = -1;
}

template < typename Tipo>
FilaCircular<Tipo>::~FilaCircular()
{
    if(m_fila != 0x0)
        delete [] m_fila;
    m_fila = 0x0;
}

template < typename Tipo>
void FilaCircular<Tipo>::push(const Tipo &elemento)
{
    m_fim = (m_fim+1)%m_tam;
    m_fila[m_fim] = elemento;

    if(m_numElementos == m_tam)
        m_ini = (m_ini+1)%m_tam;
    else
        m_numElementos ++;
}

template < typename Tipo>
Tipo FilaCircular<Tipo>::pop()
{
    if(m_numElementos == 0)
        return Tipo();

    int k = m_ini;
    m_ini = (m_ini+1)%m_tam;
    m_numElementos--;
    return m_fila[k];
}

template < typename Tipo>
Tipo FilaCircular<Tipo>::top() const
{
    if(m_numElementos == 0)
        return Tipo();
    else
        return m_fila[m_ini];
}

template < typename Tipo>
Tipo FilaCircular<Tipo>::elemento(int i) const
{
    if(i >= m_tam)
        return Tipo();

    return m_fila[ (m_ini + i)%m_tam];
}

template < typename Tipo>
Tipo FilaCircular<Tipo>::elemento(int i, int aPartirElemento) const
{
    if(i >= m_tam || aPartirElemento > m_tam)
        return Tipo();

    return m_fila[ (aPartirElemento + i)%m_tam];
}

template < typename Tipo>
int FilaCircular<Tipo>::idTopo() const
{
    return m_ini;
}

template < typename Tipo>
int FilaCircular<Tipo>::idElemento(int i, int aPartirElemento) const
{
    return (aPartirElemento + i)%m_tam;
}

template < typename Tipo>
int FilaCircular<Tipo>::numElementosAtraz(int idElemento) const
{
    if(idElemento >= m_tam || idElemento < 0 || idElemento == m_fim || m_fim < 0)
    {
        return 0;
    }
    if(m_fim > idElemento)
    {
        return m_fim - idElemento;
    }else if(m_fim < idElemento)
    {
        return m_tam-idElemento + m_fim;
    }
}

template < typename Tipo>
bool FilaCircular<Tipo>::vazia() const
{
    return (m_numElementos == 0);
}

template < typename Tipo>
bool FilaCircular<Tipo>::cheia() const
{
    return m_numElementos == m_tam;
}

template < typename Tipo>
int FilaCircular<Tipo>::numElementos() const
{
    return m_numElementos;
}

template < typename Tipo>
int FilaCircular<Tipo>::tamanho() const
{
    return m_tam;
}

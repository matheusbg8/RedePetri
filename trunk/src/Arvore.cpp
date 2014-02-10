#include "Arvore.h"

Arvore::Arvore()
{
    m_pai = 0x0;
    m_dado = 0x0;
}

Arvore::~Arvore()
{
    for(int i = 0 ; i < m_filhos.size() ; i++)
    {
        delete m_filhos[i];
    }
    m_filhos.clear();
}

void Arvore::adicionaFilho(Arvore *filho)
{
    filho->m_pai = this;
    m_filhos.push_back(filho);
}

bool Arvore::temPredecessor()
{
    return m_pai != 0x0;
}

bool Arvore::temFilhos()
{
    return m_filhos.size() > 0;
}

int Arvore::numFilhos()
{
    return m_filhos.size();
}

Arvore *Arvore::filho(int i)
{
    if(i >= 0 && i < m_filhos.size())
        return m_filhos[i];
    return 0x0;
}

Arvore *Arvore::predecessor()
{
    return m_pai;
}


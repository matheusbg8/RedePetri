#ifndef ARVORE_H
#define ARVORE_H

#include <vector>
using namespace std;

class Arvore
{
protected:
    void *m_dado;
    Arvore *m_pai;
    vector< Arvore * > m_filhos;

public:
    Arvore();
    ~Arvore();
    void adicionaFilho(Arvore *filho);
    bool temPredecessor();
    bool temFilhos();
    int numFilhos();
    Arvore *filho(int i);
    Arvore *predecessor();
};

#endif // ARVORE_H

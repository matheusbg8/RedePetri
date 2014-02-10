#ifndef AMBIENTE2_H
#define AMBIENTE2_H

#include <map>
#include <vector>

#include "IAmbiente.h"
#include "NodoAmbiente2.h"

using namespace std;

class Ambiente2: public IAmbiente
{

protected:

    map<string, unsigned> m_mapaNodos;
    vector<NodoAmbiente2> m_nodos;

    NodoAmbiente2 * nodo(const string& nome);

    unsigned adiciona(NodoAmbiente2* novoNodo, bool forcado = true);
public:
    Ambiente2();

    // Interface do ambiente
    unsigned variavel(const string &nome, const string& valor);
    unsigned pergunta(const string &nome, const string& expressao);
    unsigned acao(const string &nome, const string& instrucoes);

    bool removeNodo(const string &nome);
    bool removeNodo(unsigned id);

    bool executaAcao(const string &nome);
    bool executaAcao(unsigned id);

    bool avaliaPergunta(const string &nome);
    bool avaliaPergunta(unsigned id);

    Literal* avaliaVariavel(const string &nome);
    Literal* avaliaVariavel(const string &nome);
};

#endif // AMBIENTE2_H

#ifndef NODOAMBIENTE2_H
#define NODOAMBIENTE2_H


#include <string>
using namespace std;

enum TipoNodoAmbiente2
{
    NODO_INVALIDO,
    NODO_AMBIENTE,
    NODO_PERGUNTA,
    NODO_VARIAVEL,
    NODO_ACAO
};

class Ambiente2;
class AcaoAmbiente;
class PerguntaAmbiente;
class VariavelAmbiente;

class NodoAmbiente2
{
protected:
    string m_nome;
    virtual TipoNodoAmbiente2 tipoNodo() = 0;
public:

    NodoAmbiente2(const string& nome);

    const string& nome() const;

    bool ehAmbiente();
    bool ehPergunta();
    bool ehVariavel();
    bool ehAcao();

    Ambiente2* ambiente();
    AcaoAmbiente* acao();
    PerguntaAmbiente* pergunta();
    VariavelAmbiente* variavel();
};

#endif // NODOAMBIENTE2_H

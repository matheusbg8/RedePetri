#ifndef MODELOGRAFO_H
#define MODELOGRAFO_H


#include <QString>
#include <vector>

using namespace std;

class ModeloGrafo
{
public:

    virtual unsigned numeroVertices() = 0;
    virtual QString nome() = 0;
    virtual QString nomeVerticeQt(unsigned id) = 0;
    virtual unsigned marcacao(unsigned id)= 0;
    virtual unsigned numeroAdjacentes(unsigned id)= 0;
    virtual unsigned adjacente(unsigned i, unsigned verticeID)= 0;
    virtual float custoAdjacente(unsigned i, unsigned verticeID)= 0;
    virtual string nomeAdjacente(unsigned i, unsigned verticeID)= 0;

    /* Edicao */
    virtual bool editavel() = 0;

    virtual unsigned novoVertice() = 0;
    virtual bool atribuiNome( unsigned vID, string nome) = 0;
    virtual bool apagaVertice( unsigned vID) = 0;
    virtual void novaAresta(unsigned u, unsigned v, float custo, string nome = string())= 0;
    virtual bool apagaAresta(unsigned uID, unsigned vID) = 0;

    virtual bool modeloCompleto() = 0;

};

#endif // MODELOGRAFO_H

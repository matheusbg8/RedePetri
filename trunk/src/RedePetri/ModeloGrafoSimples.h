#ifndef MODELOGRAFOSIMPLES_H
#define MODELOGRAFOSIMPLES_H

#include "ModeloGrafo.h"
#include <vector>
#include <QString>
#include <cstdio>


/**
 * @brief
 *  Esta é uma representação simples de um grafo.
 */
class ModeloGrafoSimples : public ModeloGrafo
{
private:
    vector< vector < int > > g;  /** Estrtura do grafo com lista de adjacencias */
    vector< unsigned > m_marcacao;  /** Marcação de cada vértice */
    int m_numArestas;  /** Número total de arestas */
public:
    ModeloGrafoSimples();

    /* Implementação da interface */
    unsigned numeroVertices();
    QString nome();
    unsigned marcacao(unsigned id);
    QString nomeVerticeQt(unsigned id);
    unsigned numeroAdjacentes(unsigned id);
    unsigned adjacente(unsigned i, unsigned verticeID);
    float custoAdjacente(unsigned i, unsigned verticeID);
    string nomeAdjacente(unsigned i, unsigned verticeID);


    /* Salvar e Carregar */
    void carrega(FILE *arq);
    void salva(FILE *arq);

    bool setNome(unsigned id,const QString &nome);
    bool setMarcacao(unsigned id, unsigned marcacao);


    /* Manipulação */
    void apagaGrafo();

    bool editavel();

    unsigned novoVertice();

    bool atribuiNome(unsigned vID, string nome);

    bool apagaVertice(unsigned vID);

    void novaAresta(unsigned u, unsigned v, float custo, string nome);

    bool apagaAresta(unsigned uID, unsigned vID);

    bool modeloCompleto();

};

#endif // MODELOGRAFOSIMPLES_H

#ifndef CAMBIENTE_H
#define CAMBIENTE_H

#include "DAmbiente.h"
#include "Ambiente.h"
#include "DAmbiente.h"
#include <list>
#include "VisualizacaoAmbiente.h"
using namespace std;


/**
 * @brief Esta classe é utilizada para controlar
 * o Ambiente, ela é responsavel por manter a
 * consistencia dos dados entre o modelo, classe
 * Ambiente, e as visualizações, como a classe DAmbiente.
 *
 */
class CAmbiente
{
protected:
    // Lista de todas visualizações do ambiente
    list<VisualizacaoAmbiente*> m_visualizacoes;

    // Modelo que esta sendo controlado
    Ambiente *m_modelo;

    static const string m_nomeNaoEncontrado;

    void removeVariavelVisualizacao(unsigned id);
    void removeAcaoVisualizacao(unsigned id);
    void removePerguntaVisualizacao(unsigned id);

    void atualizaVisualizacao(VisualizacaoAmbiente *visualizacao);

public:
    CAmbiente();
    ~CAmbiente();

    void iniciaControleAmbiente();

    /* Definicao e configuracao do controlador */
    void addVisualizacao(VisualizacaoAmbiente *visualizacao);
    void removeVisualizacao(VisualizacaoAmbiente *visualizacao);
    bool possuiVisualizacoes();

    void setModelo(Ambiente *modelo);

    const Ambiente *modelo() const;

    /* Edicao e Criacao do ambinete */
    void setNomeAmbiente(const string &nome);
    int novaVariavel(const string &nome, const string &valor);
    int novaPergunta(const string &nome, const string &valor);
    int novaAcao(const string &nome, const string &valor);
    bool setVariavel(int id, const string &valor);
    void removeVariavel(unsigned id);
    void removePergunta(unsigned id);
    void removeAcao(unsigned id);

    /* Consulta ao modelo */
    int idNodo(const string &nome);
    const string& nomeNodo(unsigned id);
    const Literal * getVariavel(unsigned id);
    bool ehVariavel(int idNodo);
    const NodoAmbiente* getNodo(unsigned id);

    /* Comunicacao com o modelo */
    bool avaliaPergunta(int id);
    bool executaAcao(int id);

};

#endif // CAMBIENTE_H

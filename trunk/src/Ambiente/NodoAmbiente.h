#ifndef NODOAMBIENTE_H
#define NODOAMBIENTE_H

#include "GerenciadorNomes.h"
#include <string>
#include <iostream>
#include "Grafo.h"
using namespace std;


enum TipoNodoAmbiente
{
    NODO_INVALIDO,
    NODO_AMBIENTE,
    NODO_PERGUNTA,
    NODO_VARIAVEL,
    NODO_ACAO,
    NODO
};

// Essas classes incluem NodoAmbiente
class Ambiente;
class VariavelAmbiente;
class PerguntaAmbiente;
class AcaoAmbiente;

/**
 * @brief
 *  Esta classe representa um nodo do ambiente
 *  Um nodo do ambiente é uma estrutura generiaca
 * que pode ser uma variavel, uma pergunta, uma acao
 * ou até mesmo um ambiente.
 *  Cada nodo pode ter nodos filhos, e a principal
 * função de um nodo é gerenciar seus filhos.
 *  O gerenciamento é feito através de um mapeamento
 * do nome do nodo para o seu identificador.
 *  Todos os nodos são armazenados pelo Ambiente,
 * e o Ambiente é sempre o Nodo mais alto da hierarquia,
 * é o único nodo que não tem um nodo pai, ninguem o mapeia
 * e seu identificador é sempre 0.
 *   Todos os nodos possui uma referencia ao nodo Ambiente.
 *   Quando um nodo é destruido, todos os nodos filhos
 * são deletados, se o ambiente for destruido, todos os
 * nodos são deletados.
 *  A relação entre os nodos é feita através de um grafo,
 * o que permite ter multiplos mapementos para um mesmo
 * nodo.
 *  A navegação entre os nodos pode ser feita através do
 * caracter '.' entre os nomes dos nodos.
 */
class NodoAmbiente
{
private:
    Ambiente *m_ambiente;

protected:
    string m_nome;

    bool executandoDestrutor;

    unsigned m_id;

    // Nao pode ser utilizado Gerenciador de Nomes
    // aqui devido aos buracos, os IDs sao gerados
    // no ambiente e sao unicos para todas variaveis
    // existentes
    map<string, unsigned> m_mapaNodos;

    Ambiente* ambiente();

    string encontraNomeDisponivel(const string & nome);

    string registraMapeamento(const string & nome, unsigned id);

    NodoAmbiente* getNodoDireto(const string &nomeNodo);
    const NodoAmbiente* getNodoDireto(const string &nomeNodo) const;

    // Reflections
    VariavelAmbiente* getVariavelDireto(const string &nomeNodo);
    PerguntaAmbiente* getPerguntaDireto(const string &nomeNodo);
    AcaoAmbiente* getAcaoDireto(const string &nomeNodo);

    // Este metodo é chamado apenas pelos outros nodos
    string renomeiaNodo(NodoAmbiente* nodo , const string &novoNome);
public:

    NodoAmbiente(string nome);
    virtual ~NodoAmbiente();

    NodoAmbiente *getNodo(const string &nome);
    const NodoAmbiente *getNodo(const string &nome) const;

    // Reflections
    VariavelAmbiente* getVariavel(string nome);
    VariavelAmbiente* getVariavel(unsigned id);
    VariavelAmbiente* variavel();

    PerguntaAmbiente* getPergunta(string nome);
    PerguntaAmbiente* getPergunta(unsigned id);
    PerguntaAmbiente* pergunta();

    AcaoAmbiente* getAcao(string nome);
    AcaoAmbiente* getAcao(unsigned id);
    AcaoAmbiente* acao();

    bool possuiAmbiente() const;

    bool addNodo(NodoAmbiente *novoNodo);

    NodoAmbiente *addNodo(string nome);

    VariavelAmbiente* addVariavel(string nome, string valor);
    PerguntaAmbiente* addPergunta(string nome, string pergunta);
    AcaoAmbiente* addAcao(string nome, string acao);

    bool removeNodo(NodoAmbiente *nodo);
    bool removeNodo(const string &nomeNodo);

    const string& nome() const;

    virtual const string &setNome(string nome);

    unsigned id() const;

    virtual TipoNodoAmbiente tipoNodo() const;

    friend class VariavelAmbiente;
    friend class Ambiente; // Utilizado para definir o ambiente de forma privada
};

#endif // NODOAMBIENTE_H

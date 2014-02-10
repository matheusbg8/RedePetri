#ifndef AMBIENTE_H
#define AMBIENTE_H

#include "VariavelAmbiente.h"
#include "PerguntaAmbiente.h"
#include "AcaoAmbiente.h"

#include "GerenciadorNomes.h"
#include "GrafoLista.h"

#include <map>
using namespace std;


/**
 * @brief
 *  A classe ambiente representa todos os sensores
 * e atuadores que possam existir em um ambiente,
 * esses sonsores e atuadores são discritos por um
 * conjunto de váriaveis e perguntas.
 *  OBs.: Quando um Ambiente é destruido, todas as
 * variaveis e perguntas referente ao ambiente também
 * são destruidas.
 */

// Uma aresta significa que uma variavel mapeia outra variavel
// Um vertice é uma variavel
// Ambiente sempre possui id 0
class Ambiente: public NodoAmbiente
{
protected:

    vector<NodoAmbiente*> m_nodos; /** Possui todos os nodos do ambiente */

    GrafoLista m_grafo;

    bool registraNodo(NodoAmbiente *nodo);
    CAmbiente *m_controle;

public:
    Ambiente(string nome);
    virtual ~Ambiente();

    void setControle(CAmbiente* controle);
    CAmbiente *controle();

    NodoAmbiente *getNodo(unsigned id);
    const NodoAmbiente *getNodo(unsigned id) const;

    NodoAmbiente *getNodo(const string &nome);
    const NodoAmbiente *getNodo(const string &nome) const;

    int idMaiorNodo() const;

    VariavelAmbiente *getVariavel(unsigned id);
    PerguntaAmbiente *getPergunta(unsigned id);
    AcaoAmbiente *getAcao(unsigned id);


    VariavelAmbiente *getVariavel(string nome);
    PerguntaAmbiente *getPergunta(string nome);
    AcaoAmbiente *getAcao(string nome);

    bool pergunta(string nomePergunta);
    bool pergunta(unsigned id);

    void imprimeAmbiente();

    const Grafo * grafo() const;

    // Interface NodoAmbiente
    TipoNodoAmbiente tipoNodo();

    friend class NodoAmbiente;
    friend class VariavelAmbiente;
};

#endif // AMBIENTE_H


/** @todo - Um problema acontece nesse teste, Machado é
* criado primeiramente como um nodo em Matheus.Machado.Dos...
* agora esta sendo criado um Machado no nodo Matheus
* como váriavel, o nodo não pode ser criado, porque já
* existe 1 nodo Machado, então é criado uma variavel
* com nome Machado_1 como variavel, só que o programador
* que chamou o metodo não foi avisado da alteração do nome,
* essa ação deve ser reavaliada se deve continuar assim
* mas com algum aviso, ou se simplemente deve ser impedido
* a criação do novo nodo.
**/

//// Teste VariavelAmbiente

//#include"Ambiente.h"

//int main()
//{
//    Ambiente a("Teste");

//    a.addVariavel("Matheus.Machado.Dos.Santos", "\"teste\"");
//    a.addVariavel("Casa.Bola.Moeda", "tRuE");
//    a.addVariavel("Casa.Dedo", ".34");
//    a.addVariavel("Matheus.Machado", "Hello");

//    cout << a.getVariavel("Matheus.Machado.Dos.Santos")->literal() << endl;
//    cout << a.getVariavel("Casa.Bola.Moeda")->literal() << endl;
//    cout << a.getVariavel("Casa.Dedo")->literal() << endl;
//    cout << a.getVariavel("Matheus.Machado_1")->literal() << endl;

//    a.imprimeAmbiente();
//}

// Saida desejada:
//LString "teste"
//LBooleano true
//LNumero 0.34
//LVariavel Hello
//( Teste ,  , 0 )  --> ( Matheus ,  , 1)
//( Matheus ,  , 1 )  --> ( Machado ,  , 2)
//( Machado ,  , 2 )  --> ( Dos ,  , 3)
//( Dos ,  , 3 )  --> ( Santos ,  , 4)
//( Teste ,  , 0 )  --> ( Casa ,  , 5)
//( Casa ,  , 5 )  --> ( Bola ,  , 6)
//( Bola ,  , 6 )  --> ( Moeda ,  , 7)
//( Casa ,  , 5 )  --> ( Dedo ,  , 8)
//( Matheus ,  , 1 )  --> ( Machado_1 ,  , 9)


/*
#include"Ambiente.h"

int main()
{
    Ambiente a("Teste");

    a.addVariavel(new VariavelAmbiente("Y1" , "false"));
    a.addVariavel(new VariavelAmbiente("Y2" , "false"));

    VariavelAmbiente *nova = new VariavelAmbiente("Y1", "compartilhado");

    // Sem Conflito
    a.get("Y1")->addVariavel(new VariavelAmbiente("Y1", "true"));

    // Resolve conflito Y1.Y1 -> Y1.Y1_1
    a.get("Y1")->addVariavel(nova);

    // Conflito Y1.Y1 == Y1.Y1 -> Y1.Y1_1 == Y1.Y1_1 -> Y1.Y1_2
    a.get("Y1")->addVariavel(new VariavelAmbiente("Y1", "true"));

    // Sem conflito
    a.get("Y1")->addVariavel(new VariavelAmbiente("Y1_1_1", "true"));


    // Sem conflito
    a.get("Y2")->addVariavel(new VariavelAmbiente("Y1_1", "true"));

    a.get("Y2")->addVariavel(new VariavelAmbiente("Y1_1_2", "true"));

    // Conflito Y2.Y1_1 (Y2 Y1).Y1_1 -> (Y2 Y1).Y1_1_1 == Y1.Y1_1_1 -> (Y2 Y1).Y1_1_2
    // (Y2 Y1).Y1_1_2 == Y2.Y1_2 -> (Y2 Y1).Y1_1_3
    a.get("Y2")->addVariavel(nova);

    nova->setValor("shared");
    nova->setNome("Machado");

    a.imprimeVariaveis();

    delete nova;

    cout << "Novo ambiente:" <<  endl;

    a.imprimeVariaveis();
}
*/



//#include"Ambiente.h"

//int main()
//{
//    Ambiente a("Teste");

//    a.addVariavel("Matheus.Machado.Dos.Santos", "teste");
//    a.addVariavel("Casa.Bola.Moeda", "ola");
//    a.get("Casa.Bola")->setValor("Olaa222");
//    a.addVariavel("Casa.Dedo", "te");

////    a.addVariavel( new VariavelAmbiente("Matheus", "1"));
////    a.get("Matheus")->addVariavel( new VariavelAmbiente("Machado", "2"));
////    a.get("Matheus.Machado")->addVariavel( new VariavelAmbiente("dos", "3"));
////    a.get("Matheus.Machado.dos")->addVariavel( new VariavelAmbiente("Santos", "4"));

//    a.imprimeVariaveis();
//}

#ifndef VARIAVELAMBIENTE_H
#define VARIAVELAMBIENTE_H

#include "GerenciadorNomes.h"
#include <string>
#include <iostream>
#include "Grafo.h"
#include "NodoAmbiente.h"
#include "LivroLiterais.h"
using namespace std;

// Ambiente inclui VariavelAmbiente.h
class Ambiente;

/**
 * @brief
 *  Esta classe é utilizada para armazenar uma
 * variavel do ambiente, ela pode ser composta
 * por outras variaveis e representa um nodo no ambiente.
 * Obs.: Quando uma variavel é detruida, todas
 * as variaveis que a compoem também são destruidas
 * e as referencias dos pais para averiavel é eliminada
 */
class VariavelAmbiente: public NodoAmbiente
{
protected:
    string m_valor;
    Literal *m_literal;

    static LivroLiterais m_livroLiterais;
public:

    VariavelAmbiente(string nome, string valor);
    virtual ~VariavelAmbiente();

    bool removeVariavel(VariavelAmbiente *variavel);
    bool removeVariavel(const string &nomeVariavel);

    const string& nome() const;
    const string& valor() const;
    const Literal *literal() const;

    void setValor(const string &valor);
    virtual const string &setNome(const string& nome);

    unsigned id() const;

    // Interface NodoAmbiente
    TipoNodoAmbiente tipoNodo() const;
};

#endif // VARIAVELAMBIENTE_H



//// Teste VariavelAmbiente

//#include"Ambiente.h"

//int main()
//{
//    Ambiente a("Teste");

//    a.addVariavel("Matheus.Machado.Dos.Santos", "teste");
//    a.addVariavel("Casa.Bola.Moeda", "ola");
//    a.getVariavel("Casa.Bola.Moeda")->setValor("Olaa222");
//    a.addVariavel("Casa.Dedo", "te");

//    cout << a.getVariavel("Casa.Bola.Moeda")->literal() << endl;

////    a.addVariavel( new VariavelAmbiente("Matheus", "1"));
////    a.get("Matheus")->addVariavel( new VariavelAmbiente("Machado", "2"));
////    a.get("Matheus.Machado")->addVariavel( new VariavelAmbiente("dos", "3"));
////    a.get("Matheus.Machado.dos")->addVariavel( new VariavelAmbiente("Santos", "4"));

//    a.imprimeAmbiente();
//}

#ifndef LIVROLITERAIS_H
#define LIVROLITERAIS_H

#include<list>

#include "Literal.h"

using namespace std;

/**
 * @brief
 *  Esta classe é utilizada para construir
 * os literais, a função dela é receber um
 * conjunto de caracter e construir um novo
 * literal a partir desses caracteres e um
 * conjunto de literais pre definidos.
 */
class LivroLiterais
{
protected:
    list<Literal*> m_literais;
public:
    LivroLiterais();
    ~LivroLiterais();

    bool vazio();

    void addLiteral(Literal * fabrica);

    Literal * novoLiteral(istream &expressao);
    Literal * novoLiteral(const char *expressao, unsigned *numCaracteresLidos);

    bool interpreta(const char *expressao, list<Literal*> &literais);
};

#endif // LIVROLITERAIS_H

//// Teste Literais

//#include <iostream>
//#include "LivroLiterais.h"
//#include "LiteralBooleano.h"
//#include "LiteralGenerico.h"
//#include "LiteralNumero.h"
//#include "LiteralOperador.h"
//#include "LiteralString.h"
//#include "LiteralVariavel.h"

//using namespace std;

//int main()
//{

//    LivroLiterais livro;

//    list<Literal *> literais;
//    list<Literal *>::iterator li;

//    // A ordem dos literais é a ordem
//    // que os testes de interpretação serao
//    // realizados
//    // Deichar LiteralVariavel como ultimo
//    // teste.
//    livro.addLiteral(LiteralGenerico::fabrica());
//    livro.addLiteral(LiteralOperador::fabrica());
//    livro.addLiteral(LiteralNumero::fabrica());
//    livro.addLiteral(LiteralString::fabrica());
//    livro.addLiteral(LiteralBooleano::fabrica());
//    livro.addLiteral(LiteralVariavel::fabrica());

//    livro.interpreta("\"\tt\t\"* e +\"\" / \" =\" \t\n\n TrUeFALSEMachado=((casa.a_24-34.5+true))/.8-false\"oi\"", literais);

//    cout << "Literais Interpretados:" << endl;
//    for(li = literais.begin() ; li != literais.end() ; li++)
//    {
//        cout << *li << endl;
//    }
//}
// Saida esperada
//Literais Interpretados:
//LString "	t	"
//LOperador *
//LVariavel e
//LOperador +
//LString ""
//LOperador /
//LString " ="
//LBooleano true
//LBooleano false
//LVariavel Machado
//LOperador =
//LGenerico (
//LGenerico (
//LVariavel casa.a_24
//LOperador -
//LNumero 34.5
//LOperador +
//LBooleano true
//LGenerico )
//LGenerico )
//LOperador /
//LNumero 0.8
//LOperador -
//LBooleano false
//LString "oi"


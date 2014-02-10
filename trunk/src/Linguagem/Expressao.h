#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#include "Literal.h"
#include "LivroLiterais.h"
//#include "CAmbiente.h"
#include <list>

class CAmbiente;

/**
 * @brief
 *  Esta classe é responsável por executar
 * uma expressão na ordem correta, baseado
 * no algoritmo Shunting-yard proposto por
 * Edsger Dijkstra.
 */
class Expressao
{
protected:
    list<Literal*> m_expressao;

    CAmbiente *m_controleAmbiente;

    // Utilizado para interpretar uma expressao
    // transformar caracters em literais
    static LivroLiterais m_livroLiterais;

    list<Literal*> m_literais;

    void processaExpressao(istream & is);
    void apagaExpressao();

    void carregaLivroDeLiterais();

    bool transformaInFixEmPosFix(list<Literal *> &entrada, list<Literal *> &saida);

    // Resolucao de variave
    list<Literal*> m_coletorLiterais;
    const Literal *resolve(const Literal *A);

    void desalocaLiteraisResolvidos();

    // Execucao das operacoes
    Literal *executaOP(LiteralOperador *op, Literal* A, Literal *B);

    // Execucao das operacoes
    Literal *opIgual(const Literal *A, const Literal *B);
    Literal *opDiferente(const Literal* A, const Literal *B);
    Literal *opMaior(const Literal* A, const Literal *B);
    Literal *opMenor(const Literal* A,const Literal *B);
    Literal *opMaiorIgual(const Literal* A, const  Literal *B);
    Literal *opMenorIgual(const Literal* A, const Literal *B);
    Literal *opAnd(const Literal* A, const Literal *B);
    Literal *opOr(const Literal* A, const Literal *B);
    Literal *opNegado(const Literal* A, const Literal *B);
    Literal *opSoma(const Literal* A, const Literal *B);
    Literal *opSubtracao(const Literal* A, const Literal *B);
    Literal *opMultiplicacao(const Literal* A, const Literal *B);
    Literal *opDivisao(const Literal* A, const Literal *B);
    Literal *opAtribuicao(const Literal* A,const Literal *B);

public:
    Expressao();
    ~Expressao();

    bool setExpressao(const string &expressao);
    bool setExpressao(const char *expressao);

    void imprimeLiterais();

    bool avaliaExpressao(CAmbiente *ambiente);
};

#endif // EXPRESSAO_H

// Teste Expressao

//#include "Linguagem/Expressao.h"
//#include "Ambiente.h"
//#include <iostream>
//#include <string>

//using namespace std;

//int main()
//{
//    Ambiente amb("Ambiente de teste");
//    amb.addVariavel("A", "true");
//    amb.addVariavel("B", "false");
//    amb.addVariavel("C", "6");

//    Expressao e;
//    string expressao("(!A && !B) || (C == 10-2*2)");
//    e.setExpressao(expressao);
//    if(e.avaliaExpressao(&amb))
//    {
//        cout << "Expressao valida" << endl;
//    }else
//    {
//        cout << "Expressao não validada" << endl;
//    }
//}


// Primeiro teste:

//#include "Linguagem/Expressao.h"
//#include <iostream>
//#include <string>

//using namespace std;

//int main()
//{
//    Expressao e;

//    string expressao("439 *+/ == (33 >= \"Casa\") casa.endereco");

//    e.setExpressao(expressao);

//    e.imprimeLiterais();
//}


//#include "Linguagem/Expressao.h"
//#include "Ambiente.h"
//#include <iostream>
//#include <string>

//using namespace std;

//int main()
//{
//    Ambiente amb("Ambiente de teste");
//    amb.addVariavel("Machado", "8");
//    amb.addVariavel("Narizinho", "7");

//    Expressao e;
//    string expressao(" Machado + ( Narizinho == \"indefinido\" )");
//    e.setExpressao(expressao);

//    e.avaliaExpressao(&amb);
//}


//#include "Linguagem/Expressao.h"
//#include "Ambiente.h"
//#include <iostream>
//#include <string>

//using namespace std;

//int main()
//{
//    Ambiente amb("Ambiente de teste");
//    amb.addVariavel("Machado", "\"Inde\"");
//    amb.addVariavel("Narizinho", "\"finido\"");
//    amb.addVariavel("OResultado", "0");

//    Expressao e;
//    string expressao("OResultado = Machado + Narizinho == \"Indefinidos\" ");
//    e.setExpressao(expressao);

//    e.imprimeLiterais();
//    e.avaliaExpressao(&amb);

//    cout << amb.getVariavel("OResultado")->literal() << endl;
//}

// Resultado esperado:
//Expressao:
//LVariavel OResultado
//LVariavel Machado
//LVariavel Narizinho
//LOperador +
//LString "Indefinidos"
//LOperador ==
//LOperador =
//Resultado LBooleano true
//LBooleano false

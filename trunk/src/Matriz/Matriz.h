#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <cstdio>
#include <iostream>


using namespace std;

template < typename Tipo = short int>
/**
 * @brief Esta classe representa uma matriz generica
 * possibilitando que diversas operações possam ser reliazadas.
 *   Dependendo da operação utilizada, o tipo generico passado
 * no parametro do template deve ter alguns operadores definidos.
 *   Nas operações de comparação é exigido que o tipo generico
 * tenha o operador de igualde (=) e o operador menor (<)
 * definidos.
 *  Nas operações aritmesticas, o tipo generico deve ter os operadores
 * aritmeticos ( * , / , - , + , % ) definidos, dependendo da operação
 * que sera realizada.
 */
class Matriz
{
	private:
        vector < vector < Tipo > > m_matriz;
        unsigned m_numeroLinhas;
        unsigned m_numeroColunas;

	public :

        Matriz(unsigned numeroLinhas , unsigned numeroColunas , const Tipo& valor = Tipo());

		Matriz(const Matriz &N);

		Matriz( Matriz *N);

        ~Matriz();

        void redim(unsigned numeroLinhas , unsigned numeroColunas, const Tipo &val = 0);
        Matriz &apagar();
		Matriz & operator = (const Matriz & N);

        bool mesmoTamanho(const Matriz &matriz) const;

        bool operator == (const Matriz & N) const;
        bool operator != (const Matriz & N) const;

        bool operator >= (const Matriz & N) const;
        bool operator < (const Matriz & N) const;
        bool operator <= (const Matriz & N) const;
        bool operator > (const Matriz & N) const;

        Matriz &operator += (const Matriz & N);
        Matriz &operator += (const Tipo & v);

        Matriz &operator -= (const Matriz & N);
        Matriz &operator -= (const Tipo & v);

        Matriz &operator *= (const Tipo & v);

        Matriz operator + (const Matriz & N) const;
        Matriz operator + (const Tipo & v) const;

        Matriz operator - (const Matriz & N) const;
        Matriz operator - (const Tipo & v) const;

        Matriz operator - () const;

        Matriz operator * (const Matriz & N) const;

        Tipo & operator () ( unsigned i , unsigned j);

        const Tipo & operator () ( unsigned i , unsigned j) const;

        Matriz & transposta();
		Tipo somatorio();

        Tipo cofator(int ei , int ej);

        Tipo det();

        Matriz coluna( unsigned k) const;
        Matriz linha( unsigned k) const;

        int numeroLinhas() const;
        int numeroColunas() const;

        void exclui_linha( unsigned i);
        void exclui_coluna( unsigned j );

        Matriz submatriz(unsigned iIni , unsigned jIni , unsigned iFim , unsigned jFim);

        void multiplica_linha( unsigned k , const Tipo &val);
		void multiplica_coluna( int k , const Tipo & val);

    //    void trocaLinha(int i, int j);
    //    void trocaColuna(int i, int j);

        void gaus();
		void imprime();

		template< class T>
        friend ostream & operator << (ostream & os , const Matriz<T> &m_numeroLinhas);

};


// Operações sobre a matriz

template< class Tipo>
Matriz <Tipo> transposta(const Matriz<Tipo> *N);

#include "Matriz.cpp"


#endif // MATRIZ_H

/*
// TESTE MATRIZ

#include "Matriz.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Matriz <int> A(3,3), B(3,3);

    A(0,0) = 1; A(1,0) = 4; A(2,0) =7;
    A(0,1) = 2; A(1,1) = 5; A(2,1) =8;
    A(0,2) = 3; A(1,2) = 6; A(2,2) =9;

    B(0,0) = 0; B(1,0) = 3; B(2,0) =6;
    B(0,1) = 1; B(1,1) = 4; B(2,1) =7;
    B(0,2) = 2; B(1,2) = 5; B(2,2) =8;

    cout << "Teste do -" << endl;
    Matriz<int> C(A - B);
    cout << C << endl;
    cout << C - 2 << endl;

    cout << "Teste do +" << endl;
    Matriz<int> D(C + C);
    cout << D << endl;
    cout << D + 2 << endl;

    cout << "Teste do *" << endl
         << A
         << "*" << endl
         << B
         << "=" << endl
         << A * B << endl;

    cout << "Teste >" << endl;
    cout << A << " > " << endl << B << endl;
    cout << " ----> " << (A > B) << endl;

    cout << "Teste <" << endl;
    cout << A << " < " << endl << B << endl;
    cout << " ----> " << (A < B) << endl;

    cout << "Teste de Transposta" << endl
         << A << endl
         << "Transposta =" << endl
         << transposta(A);

    cout << "Teste do apagar()" << endl
         << A.apagar() << endl;

    Matriz<int> E(3,3);
    E(0,0) = 1; E(1,0) = 2; E(2,0) =3;
    E(0,1) = 0; E(1,1) = -1; E(2,1) =4;
    E(0,2) = -3; E(1,2) = 0; E(2,2) =1;

    cout << E << endl;
    E.transposta();
    cout << E << endl;

    cout << "Teste de cofator." << endl
         << E << endl
         << "Cofat 00 = "
         << E.cofator(0,0) << endl
         << "Cofat 21 = "
         << E.cofator(2,1) << endl
         << "Cofat 11 = "
         << E.cofator(1,1) << endl;

    return 0;
}

*/

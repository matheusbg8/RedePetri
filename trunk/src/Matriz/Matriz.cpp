
#include "Matriz.h"

template < typename Tipo>
/**
 * @brief Construtor da Matriz.
 *
 * @param numeroLinhas - Numero de linhas.
 * @param numeroColunas - Numero de colunas.
 * @param valor - Valor inicial dos elementos da matriz.
 */
Matriz<Tipo>::Matriz(unsigned numeroLinhas=0, unsigned numeroColunas=0 , const Tipo &valor)
{
    // Redimensiona Matriz
    m_matriz.resize(numeroLinhas);
    for (unsigned i = 0; i < numeroLinhas; i ++)
        m_matriz[i].resize(numeroColunas, valor);

    // Define numero de linhas e colunas
    m_numeroLinhas = numeroLinhas;
    m_numeroColunas = numeroColunas;
}


template < typename Tipo>
/**
 * @brief Construtor de cópia por referencia.
 *
 * @param N - Matriz que sera copiada.
 */
Matriz<Tipo>::Matriz(const Matriz &N) // Por referencia
{
    // Copia matriz
	m_matriz = N.m_matriz;

    // Define numero de linhas e colunas
    m_numeroLinhas = N.m_numeroLinhas;
    m_numeroColunas = N.m_numeroColunas;
}

template < typename Tipo>
/**
 * @brief Construtor de cópia por ponteiro.
 *
 * @param N - Matriz que seta copiada.
 */
Matriz<Tipo>::Matriz( Matriz *N) // Por Endereço
{
    // Copia matriz
    m_matriz = N->m_matriz;

    // Define numero de linhas e colunas
    m_numeroLinhas = N->m_numeroLinhas;
    m_numeroColunas = N->m_numeroColunas;
}

template < typename Tipo>
Matriz<Tipo>::~Matriz()
{
//    printf("Md ( %d x %d)\n", m_numeroLinhas, m_numeroColunas);
}

template < typename Tipo>
/**
 * @brief Altera o numero de linhas e colunas da matriz.
 *
 * @param pm - Novo número de linhas.
 * @param pn - Novo número de colunas.
 * @param val - Valor padrão dos novos elementos.
 */
void Matriz<Tipo>::redim(unsigned numeroLinhas , unsigned numeroColunas, const Tipo &val )
{
    // Se não for o tamanho atual
    if(numeroLinhas == m_numeroLinhas && numeroColunas == m_numeroColunas)
		return ;

    // Define numero de linhas e de colunas
    m_numeroLinhas = numeroLinhas;
    m_numeroColunas = numeroColunas;

    // Redimensiona matriz
    m_matriz.resize(numeroLinhas);
    unsigned i;
    for ( i = 0; i < m_numeroLinhas; i ++)
        m_matriz[i].resize(numeroColunas, val);
}

template < typename Tipo>
/**
 * @brief Deleta a matriz, removendo todos seus elementos.
 *
 */
Matriz<Tipo> &Matriz<Tipo>::apagar()
{
    // Apaga a matriz
    for (unsigned i = 0; i < m_numeroLinhas; i ++)
		m_matriz[i].clear();
	m_matriz.clear();

    // Deefine numero de linhas
    m_numeroLinhas = 0;
    m_numeroColunas = 0;
    return *this;
}

template < typename Tipo>
/**
 * @brief Operador de atribuição.
 *
 * @param N - Matriz que sera copiada.
 * @return - Referencia da matriz.
 */
Matriz<Tipo> & Matriz<Tipo>::operator = (const Matriz & N)
{
    // Copia matriz
	m_matriz = N.m_matriz;

    // Define numero de linhas e colunas
    m_numeroLinhas = N.m_numeroLinhas;
    m_numeroColunas = N.m_numeroColunas;
    return *this;
}

template < typename Tipo>
bool Matriz<Tipo>::mesmoTamanho(const Matriz &matriz) const
{
    return m_numeroLinhas == matriz.m_numeroLinhas &&
           m_numeroColunas == matriz.m_numeroColunas;
}

template < typename Tipo>
/**
 * @brief Operação de comparação de igualdade.
 *
 * @param N - Matriz que sera comparada.
 * @return bool - True se todos os elementos forem
 * iguais, false caso contrario.
 */
bool Matriz<Tipo>::operator == (const Matriz & N) const
{
    unsigned i, j;
    for(i = 0 ; i < m_numeroLinhas ; i++)
    {
        for(j = 0 ; j < m_numeroColunas ; j++)
        {
            // Se for diferente
            if(! (m_matriz[i][j] == N.m_matriz[i][j]) )
                return false;
        }
    }
    return true;
}

template < typename Tipo>

/**
 * @brief Operador de comparação de diferença.
 *
 * @param N - Matriz que sera comparada
 * @return bool - True se for diferente, false se for igual.
 */
bool Matriz<Tipo>::operator != (const Matriz & N) const
{
    return ! ((*this) == N);
}

template < typename Tipo>
/**
 * @brief Operador de comparação >=
 *  Este operador é o operador base dos operadores
 * ( < , <= , > ).
 *
 * Obs.: As duas matriz tem que ter o mesmo
 * número de linhas e colunas, caso contrario,
 * false sera retornado.
 *
 * @param N - Matriz que sera comparada.
 * @return bool - True se todos elementos da matriz
 * for >= que os da matriz N.
 */
bool Matriz<Tipo>::operator >= (const Matriz & N) const
{
    if(m_numeroLinhas == N.m_numeroLinhas &&
      m_numeroColunas == N.m_numeroColunas)
    {
        unsigned i , j;
        for ( i = 0; i < m_numeroLinhas; i ++)
            for ( j = 0; j < m_numeroColunas; j ++)
                if(m_matriz[i][j] < N.m_matriz[i][j])
                    return false;
        return true;
    }
	else
	{
        printf("Erro ao comparar matriz com op >= , dimenssoes diferentes\n" );
        return false;
	}
}


template < typename Tipo>
/**
 * @brief Operador de comparação <
 *
 * Obs.: As duas matriz tem que ter o mesmo
 * número de linhas e colunas, caso contrario,
 * false sera retornado.
 *
 * @param N - Matriz que sera comparada.
 * @return bool - True se todos elementos da matriz
 * for < que os da matriz N, false caso contrario.
 */
bool Matriz<Tipo>::operator < (const Matriz & N) const
{
    // a < b -> not ( a >= b )
    if(m_numeroLinhas == N.m_numeroLinhas && m_numeroColunas == N.m_numeroColunas)
        return ! ( (*this) >=  N );
	else
	{
		printf("Erro ao comparar matriz com op < , dimenssoes diferentes\n" );
		return false;				
	}
}

template < typename Tipo>
/**
 * @brief Operador de comparação <=
 *
 * Obs.: As duas matriz tem que ter o mesmo
 * número de linhas e colunas, caso contrario,
 * false sera retornado.
 *
 * @param N - Matriz que sera comparada.
 * @return bool - True se todos elementos da matriz for
 * <= que todos elementos da matriz N, false caso contrario.
 */
bool Matriz<Tipo>::operator <= (const Matriz <Tipo> &N) const
{
    // (a <= b) -> (b >= a)
    if(m_numeroLinhas == N.m_numeroLinhas && m_numeroColunas == N.m_numeroColunas)
        return N >= *this;
	else
    {
		printf("Erro ao comparar matriz com op <= , dimenssoes diferentes\n" );
		return false;				
	}
}


template < typename Tipo>
/**
 * @brief Operador de comparação >.
 *
 * Obs.: As duas matriz tem que ter o mesmo
 * número de linhas e colunas, caso contrario,
 * false sera retornado.
 *
 * @param N - Matriz que sera comparada.
 * @return bool - True de todos elementos da matriz for
 * > que todos elementos da matriz N, false caso contrario.
 */
bool Matriz<Tipo>::operator > (const Matriz <Tipo> & N) const
{
    // ( a > b) --> not ( b >= a )
    // ( a >= b) --> (b >= a) --> not ( b >= a) --> (b < a) --> (a > b)
    if(m_numeroLinhas == N.m_numeroLinhas && m_numeroColunas == N.m_numeroColunas)
        return ! (N >= *this);
	else
	{
		printf("Erro ao comparar matriz com op > , dimenssoes diferentes\n" );
		return false;				
	}
}


template < typename Tipo>
/**
 * @brief Operador de incremento.
 * Incrementa cada elemento da matriz com respectivo elemento
 * da matriz N.
 * @param N - Matriz que sera utilizada para incrementada.
 * @return Matriz& - Referencia pra matriz já incrementada.
 */
Matriz<Tipo> & Matriz<Tipo>::operator += (const Matriz & N)
{
    if(m_numeroLinhas != N.m_numeroLinhas || m_numeroColunas != N.m_numeroColunas )
    {
        printf("Erro, soma de matriz com dimensões diferentes\n" );
        return *this;
    }
    unsigned i , j;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
            m_matriz[i][j] += N.m_matriz[i][j];
    return *this;
}


template < typename Tipo>
/**
 * @brief Operador de incremento
 *
 * @param v - Valor que sera incrementado em todos elementos da matriz.
 * @return Matriz & - Referencia da matriz incrementada.
 */
Matriz<Tipo> & Matriz<Tipo>::operator += (const Tipo & v)
{
    unsigned i , j;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
            m_matriz[i][j] += v;
    return *this;
}

template < typename Tipo>
/**
 * @brief Operador de decremento.
 *  Decrementa elemento a elemento com seus
 * respectivos elementos da matriz N.
 *  O numero de linhas e colunas tem que ser igual
 * das duas matriz.
 * @param N - Matriz que sera usada para decrementar.
 * @return Matriz &Matriz<Tipo>
 */
Matriz<Tipo> & Matriz<Tipo>::operator -= (const Matriz & N)
{
    if(m_numeroLinhas != N.m_numeroLinhas || m_numeroColunas != N.m_numeroColunas )
    {
        printf("Erro, subtracao de matriz com dimensões diferentes\n" );
        return *this;
    }
    unsigned i , j;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
            m_matriz[i][j] -= N.m_matriz[i][j];
    return *this;
}

template < typename Tipo>

/**
 * @brief Operador de decremento.
 *  Decrementa cada elemento da matriz
 * utilizando o valor v.
 *
 * @param v - Valor utilizado para decrementar na matriz.
 * @return Matriz & - Referencia da matriz decrementada.
 */
Matriz<Tipo> &Matriz<Tipo>::operator -=(const Tipo &v)
{
    unsigned i , j;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
            m_matriz[i][j] -= v;
    return *this;
}


template < typename Tipo>
/**
 * @brief Operador de multiplicacao e atribuicao.
 *
 * Multiplica cada elemento da matriz pelo valor v.
 *
 * @param v - Valor utilizado para multiplicar na matriz.
 * @return Matriz & - Referencia da matriz decrementada.
 */
Matriz<Tipo> &Matriz<Tipo>::operator *=(const Tipo &v)
{
    unsigned i , j;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
            m_matriz[i][j] *= v;
    return *this;
}

template < typename Tipo>
/**
 * @brief Operador soma.
 *
 * @param N - Matriz que sera somada.
 * @return Matriz - Resultado da soma entre as duas matriz.
 */
Matriz<Tipo> Matriz<Tipo>::operator + (const Matriz <Tipo> & N) const
{
    Matriz<Tipo> R(*this);
    R += N;
    return R;
}

template < typename Tipo>
Matriz <Tipo> Matriz<Tipo>::operator + (const Tipo & v) const
{
    Matriz <Tipo> R(*this);
    R += v;
    return R;
}

template < typename Tipo>
Matriz<Tipo> Matriz<Tipo>::operator - (const Matriz <Tipo> & N) const
{
    Matriz<Tipo> R(*this);
    R -= N;
    return R;
}

template < typename Tipo>
Matriz <Tipo> Matriz<Tipo>::operator - (const Tipo & v) const
{
    Matriz <Tipo> R(*this);
    R -= v;
    return R;
}

template< typename Tipo>
Matriz<Tipo> Matriz<Tipo>::operator -() const
{
    Matriz <Tipo> r(m_numeroLinhas,m_numeroColunas);
    unsigned i ,j;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
			r.m_matriz[i][j]= -m_matriz[i][j];
	return r;
}

template < typename Tipo>
Matriz<Tipo> Matriz<Tipo>::operator * (const Matriz & N) const
{// Para REDUZIR o numero de TEMPORARIOS e aumentar o desempenho, é importante
 //que a definição deste operador retorne apenas R, por isso o apagar().
    Matriz R(m_numeroLinhas , N.m_numeroColunas);

    if(m_numeroColunas != N.m_numeroLinhas)
    {
        printf("Erro - Multiplicação de matriz com dimensões invalidas\n" );
        R.apagar();
        return R; // Retorna matriz vazia (retorna R para reduzir temps)
    }

    unsigned i , j,k;

    for ( j = 0; j < N.m_numeroColunas; j ++)
        for ( i = 0; i < m_numeroLinhas; i ++)
            for ( k = 0; k < m_numeroColunas; k ++)
                R(i,j) += m_matriz[i][k] * N.m_matriz[k][j];
    return R;
}

template < typename Tipo>
Tipo & Matriz<Tipo>::operator () ( unsigned i , unsigned j)
{
    if( i < m_numeroLinhas && j < m_numeroColunas )
		return m_matriz[i][j];
	else
        printf("Erro ao acessar o elemento inxistente (%d %d) (%d %d)\n", i , j , m_numeroLinhas , m_numeroColunas);
    return m_matriz[0][0];
}

template < typename Tipo>
const Tipo &Matriz<Tipo>::operator ()(unsigned i, unsigned j) const
{
    if( i < m_numeroLinhas && j < m_numeroColunas )
        return m_matriz[i][j];
    else
        printf("Erro ao acessar o elemento inxistente (%d %d) (%d %d)\n", i , j , m_numeroLinhas , m_numeroColunas);
    return m_matriz[0][0];
}

template < typename Tipo>
Matriz<Tipo>& Matriz<Tipo>::transposta()
{
// Swap bit a bit
// a ^= b;
// b ^= a;
// a ^= b;
    unsigned i , j;
//    Tipo swap;
    for ( i = 0; i < m_numeroColunas; i ++)
        for ( j = i+1; j < m_numeroColunas; j ++)
        {
            m_matriz[j][i] ^= m_matriz[i][j];
            m_matriz[i][j] ^= m_matriz[j][i];
            m_matriz[j][i] ^= m_matriz[i][j];
//            swap = M[j][i];
//            M[j][i] = M[i][j];
//            M[i][j] = swap;
        }
    return (*this);
}

template < typename Tipo>
Tipo Matriz<Tipo>::somatorio()
{
    unsigned i , j;
    Tipo soma = 0;
    for ( i = 0; i < m_numeroLinhas; i ++)
        for ( j = 0; j < m_numeroColunas; j ++)
			soma += m_matriz[i][j];
    return soma;
}


template <typename Tipo>
/**
 * @brief Calcula o cofator de um elemento da matriz
 * utilizado para calcular o determinante de uma triz
 * quadrada de ordem n
 * @todo - Ainda não foi terminada a implementação desse metodo.
 * @param ei - linha do elemento que sera calculado o cofator
 * @param ej - coluna do elemento que sera calculado o cofator
 * @return - Cofator do elemento ei, ej.
 */
Tipo Matriz<Tipo>::cofator(int ei,int ej)
{
/*
  11 12 13 14 15
  21 22 23 24 25
  31 32 33 34 35
  41 42 43 44 45
  51 52 53 54 55

  C11

  22 23 24 25
  32 33 34 35
  42 43 44 45
  52 53 54 55

    C11

    33 34 35
    43 44 45
    53 54 55




  11 22 33
  12 23 31
  13 21 32

  11 23 32
  12 21 33
  13 22 31

  22 33
  23


*/
    Tipo pri , sec , soma = 0;
    unsigned i, j, ki,kj;
    for(j = 0; j < m_numeroColunas; j++)
    {
        pri = 1, sec =1;
        for(i = 0; i < m_numeroLinhas ; i++)
        {   ki = i , kj = (i+j)%m_numeroColunas;
            if(ei != ki && ej != kj)
            {
                pri *= m_matriz[ki][kj];
                printf("p%d ",m_matriz[ki][kj] );
            }
            kj = (m_numeroColunas-i+j)%m_numeroColunas;
            if(ei != ki && ej != kj)
            {
                sec *= m_matriz[ki][kj];
                printf("s%d |",m_matriz[ki][kj] );
            }
        }
        printf("\n");
        soma += pri - sec;
    }
    printf("\n\n");
    if((ei+ej) %2) soma *=-1;
    return soma;
}

template <typename Tipo>
/**
 * @brief Calcula o determinante da matriz.
 *
 * Obs.: A matriz deve ser quadrada, caso contrario
 * um valor aleatorio sera retornado e uma mensagem
 * de erro sera impressa.
 *
 * @return Tipo - Determinante da matriz.
 */
Tipo Matriz<Tipo>::det()
{
/*
    a11 a12 a13
    a21 a22 a23
    a31 a32 a33

    prim = a11 * a22 * a23
*/
}

template < typename Tipo>
Matriz<Tipo> Matriz<Tipo>::coluna( unsigned k) const
{
    Matriz R(m_numeroLinhas ,1);
    for (unsigned i = 0; i < m_numeroLinhas; i ++)
        R(i , 0) = m_matriz[i][k];
	return R;
}

template < typename Tipo>
Matriz<Tipo> Matriz<Tipo>::linha( unsigned k) const
{
    Matriz R(1 , m_numeroColunas);
    for (unsigned i = 0; i < m_numeroColunas; i ++)
		R(0 , i) = (*this)(k,i);			
	return R;
}

template < typename Tipo>
int Matriz<Tipo>::numeroLinhas() const
{
    return m_numeroLinhas;
}
template < typename Tipo>
int Matriz<Tipo>::numeroColunas() const
{
    return m_numeroColunas;
}

template < typename Tipo>
void Matriz<Tipo>::exclui_linha( unsigned i)
{
    if( i < m_numeroLinhas )
	{
		m_matriz.erase( m_matriz.begin()+ i);
        m_numeroLinhas--;
	}
	else
		printf("Erro ao Exclui linha da matriz, linha invalida\n" );				
}

template < typename Tipo>
void Matriz<Tipo>::exclui_coluna(unsigned j )
{
    if( j < m_numeroColunas)
	{
        for (unsigned i = 0; i < m_numeroLinhas; i ++)
			m_matriz[i].erase( m_matriz[i].begin() + j);
        m_numeroColunas--;
	}else
		printf("Erro ao excluir coluna da matriz, coluna invalida\n" );				
}

template < typename Tipo>
Matriz<Tipo> Matriz<Tipo>::submatriz(unsigned iIni , unsigned jIni , unsigned iFim , unsigned jFim)
{
    unsigned t;
	if(iIni > iFim) {t = iIni; iIni = iFim; iFim = t;}
	if(jIni > jFim) {t = jIni; jIni = jFim; jFim = t;}
    if(iFim < m_numeroLinhas && jFim < m_numeroColunas)
	{
		int i , j, mR = iFim - iIni , nR = jFim - jIni;
		Matriz R(mR , nR);
		for ( i = 0; i < mR; i ++)
			for ( j = 0; j < nR; j ++)
				R(i , j) = (*this)(i+iIni , j+jIni);
		return R;
	}else
	{
		printf("Erro Submatriz inexitestente\n" );
		return Matriz (1 ,1);
	}
}
template < typename Tipo>
void Matriz<Tipo>::multiplica_linha( unsigned k , const Tipo &val)
{
    if(k > m_numeroLinhas)
	{
		printf("Erro ao multiplicar linha, a linha não existe na matriz\n" );
		return;
	}
    for (int i = 0; i < m_numeroColunas; i ++)
		m_matriz[k][i] *= val;
}
template < typename Tipo>
void Matriz<Tipo>::multiplica_coluna( int k , const Tipo & val)
{
    if(k > m_numeroColunas)
	{
		printf("Erro ao multiplicar coluna, a coluna não existe na matriz\n" );
		return;
	}
    for (int i = 0; i < m_numeroColunas; i ++)
		m_matriz[i][k] *= val;
}
// 1 2 1 ; 3 2 1 ; 1 2 1 
/*
1 2 1
3 2 1 -3/1 * l0 
1 2 1 -1/1 * l0

1  2  1 -2/4 * l1
0 -4 -2
0  0  0

1  0  0
0  1  0.5
0  0  0
*/
template < typename Tipo>
/**
 * @brief Aplica o metodo de gaus jordan na matriz.
 * @todo - Implementar este metodo.
 */
void Matriz<Tipo>::gaus()
{

}

template < typename Tipo>
void Matriz<Tipo>::imprime()
{
	int i , j;
	for ( i = 0; i < m_matriz.size(); i ++)
	{
		for ( j = 0; j < m_matriz[0].size(); j ++)
			printf(" %3d" , (*this)(i,j));
		printf("\n" );
	}
}

template<class Tipo>
ostream & operator << (ostream & os , const Matriz<Tipo> &m)
{
    if(m.m_numeroLinhas <= 0 || m.m_numeroColunas <= 0)
    {
        os << "Imprimindo Matriz Vazia." << endl;
        return os;
    }

    unsigned i , j;
    for ( i = 0; i < m.m_numeroLinhas; i ++)
	{
        for ( j = 0; j < m.m_numeroColunas; j ++)
			os << '\t' << m.m_matriz[i][j];
		os << endl;
	}
	return os;
}




template< class Tipo>
/**
 * @brief Calcula a transposta da matriz N
 *
 * @param N - Matriz N
 * @return Matriz - Nova matriz traspostada.
 */
Matriz <Tipo> transposta(const Matriz<Tipo> &N)
{
    Matriz<Tipo> R(N);
    R.transposta();
    return R;
}

#ifndef REDEPETRI_H
#define REDEPETRI_H

#include <cstdio>
#include <cstdlib>

#include <string>
#include <queue>
#include <vector>
#include <cmath>

#include "Matriz.h"
#include "Lugar.h"
#include "Transicao.h"
#include "Arco.h"
#include "GerenciadorElementos.h"
#include "GrafoNome.h"

using namespace std;

#define INF 99999999
#define NULO -1

#define iMAX 15
#define jMAX 15
#define xMAX 1000
#define yMAX 1000

#define MatrizSI Matriz<short>
#define VVectorSI vector< vector < short > > 


/**
 * @brief Esta classe é uma estrutura utilizada para representar uma
 * rede de petri, ela permite que a rede seja criada dinâmicamente
 * e que algumas análises e algumas operações sejam realizadas.
 *
 * Os componentes da rede, lugares e transições, são indexados,
 * cada componente possui dois indices:
 *\li O indice relacionado ao seu tipo - Esse indice é contado
 * e atribuido apenas paras os componentes do mesmo,
 * eles são chamados de tID (indicice das transições) e
 * pID (indice dos lugares).
 *\li O indice global - Este indice é atribuido a cada componente
 * independente do seu tipo, chamado de gID (indice global).
 */
class RedePetri{
protected:
    static bool produzLog;
	public:
// Propriedades da Rede


/* ======= Atributos ========= */
	/* Matriz de Incidencia */
    Matriz <short int> C; /**< Matriz de Incidencia */

	/* Matriz de precedentes */
    Matriz <short int> Pre;  /**< Matriz de precedentes */

	/* Matriz de posteriores */
    Matriz <short int> Pos;  /**< Matriz de posteriores*/

    /* Marcacao */
    Matriz <short int> M;  /**< Marcacao */

    /* Vetor de lugares */
    GerenciadorElementos < Lugar* > P;  /**< Vetor de lugares */

    /* Vetor de transicoes */
    GerenciadorElementos< Transicao* > T; /**< Armazenamento das transições*/

    GerenciadorElementos< Arco* > A; /**< Armazenamento das transições*/

    /* Vetor de mapeamento dos indices */
    GerenciadorElementos <ComponentePetri*> V; /**< Vetor de mapeamento dos indices */

    /* Numero de Arcos */
        int N_Arcos; /**< Numero de Arcos */

        /* Ciclo de execucao atual da rede */
        int Ciclo_Atual; /**< Ciclo de execucao atual da rede */

    // Somatorio dos arcos de entrada - arcos de saida de todas transições
        int CustoTotal;

/* ======== Métodos ========== */

        /** Construtor **/
        RedePetri(int nP =1 , int nT = 1):C(1,1),Pre(1,1),Pos(1,1),M(1,1)
		{
			inicializa(nP, nT);
		}

                /* Inicializacao */
		void inicializa(int nLugar , int nTransicao);

/* ========= Edição =============== */

		/* Dimensiona rede para um novo numero de lugares/transições */
        void Dimensiona_Rede(int nTransicao , int nLugar);

		/* Atualiza IDs */
        void Atualiza_IDs();

        /* Remove um arco de um Lugar para uma Transicao*/
        void Remove_Arco_PT(int de, int para);

        /* Remove um arco de uma Transição para um Lugar*/
        void Remove_Arco_TP(unsigned de, unsigned para);

		/* Novo arco de um Lugar para uma Transição */
        int Novo_Arco_PT( int de , int para , int custo);

		/* Novo arco de um Transição para um Lugar */
        int Novo_Arco_TP( int de , int para , int custo);

        /* Novo arco de um Componente para outro */
        void Novo_Arco(ComponentePetri *De , ComponentePetri *Para , int custo);

		/* Novo arco de um ID global para outro */
		void Novo_Arco(int de , int para , int custo);

		/* Cria um novo Lugar na rede */
        int Novo_Lugar();

		/* Cria uma nova Transição na rede */
        int Nova_Transicao();

		/* Exclui o Lugar P da rede */
		void Exclui_Lugar(int p);

		/* Exclui a Transição t da rede */
		void Exclui_Transicao(int t);

        /* Exclui um arco a partir de um ID */
        bool Exclui_Arco(unsigned id);

        /* Exclui um arco que liga uma transição a um lugar */
        bool Exclui_Arco_TP(int de, int para);

        /* Exclui um arco que liga um lugar a uma transição */
        bool Exclui_Arco_PT(int de, int para);

		/* Exclui o Objeto de ID global gID */
		void Exclui(int gID);

		/* Remove todos arcos da Rede */
		void Exclui_Todos_Arcos();

        /* Apaga todos Lugares, Transições e arcos da rede */
		void Reinicia_Rede();

		/* Insere pFichas no lugar de ID pId */ 
        void Inserir_Fichas(int p, int pFichas);

        void Define_Peso(unsigned idArco, unsigned peso);

        string &Informacao_Transicao(unsigned t);

        void Define_Nome_Transicao(unsigned t , string nome);

		/* Adiciona uma nova condição a Transição */
		void Nova_Condicao(int t, string Var , string Val);

		/* Adiciona uma nova ação a transição */
		void Nova_Acao( int t , string Var , string Val);

        bool Define_Informacao_Ficha(unsigned p, unsigned ficha, string info);

        const string & Informacao_Ficha(unsigned p, unsigned ficha);


/* ========== Simulação =================== */

		/* Verifica se uma transição de Id t esta sensibilizada */
		bool Sensibilizado(int t);

		/* Atuliza informações sobre sensibilização das transições
              Necessario a execução para cada ciclo da rede */
		void Verifica_Todas_Sencibilizacoes();

		/* Executa uma transição de ID t */
		bool Executa_Transicao(int t);

/* ========== Informação ================== */

		/* Retorna o numero de Lugares + Transições que existe na rede */
        int Numero_Vertices() const;

		/* Retorna o número de Transições que existe na rede */
        int Numero_Transicoes() const;

		/* Retorna o número de Luageres que existe na Rede */
        int Numero_Lugares() const;

		/* Retorna o número de lugares que existe na rede */
        int Numero_Arcos() const;

        int Numero_Fichas(int p) const;

		/* Retorna o ID do lugar precedente de menor ID da transição de ID t
               Se não existir precedente retorna -1 */
        int Precedente_T(int t) const;

		/* Retorna o ID da transição com menor ID, precedente do lugar de ID "p" 
				Se não existir precedente retorna -1*/
        int Precedente_P(int p) const;

		/* Retorna o menor ID global, precedente de um Objeto com ID global "gID" 
				Se não existir precedente retorna -1*/
        int Precedente(int gID) const;

        bool existeLugar(int p) const;

        bool existeTransicao(int t) const;

        bool existeArco(int a) const;

        const Lugar &lugar(int id) const;

        int Custo_PT(unsigned p, unsigned t) const;

        int Custo_TP(unsigned t, unsigned p) const;

        int Custo_Arco(unsigned id) const;

        list<Lugar*>::iterator lugarBegin();
        list<Lugar*>::iterator lugarEnd();

        list<Transicao*>::iterator transicaoBegin();
        list<Transicao*>::iterator transicaoEnd();

        list<Arco*>::iterator arcoBegin();
        list<Arco*>::iterator arcoEnd();


/* ========== Entrada / Saída ============= */

		void imprime_incidencia();

		void imprime_pos();

		void imprime_pre();

		void imprime_marcacao();

/* ============ XML =========== */
		void Extrai_VarVal(const char *p , char *Var , char *Val);

//		void Extrai_Objeto(const char * p , Objeto &R);

		int XML_palavra( FILE *arq , char *p );

		void XML_Transicao(FILE *arq);

		void XML_Lugar(FILE *arq);

		void XML_Arco(FILE *arq);

		void Carrega_XML(const char * arq_nome);

		void Gera_XML(const char *Nome_Arq = 0x0);

		void Gera_Base_XML(const char *Nome_Arq);

/* ========== Analise ========= */

		bool Simula_Sensibilizacao(int t, MatrizSI &sM);

		MatrizSI Simula_Execucao(int t, MatrizSI &sM);

		void Nome_Marcacao( MatrizSI &M, char *Nome);

        void arvore(GrafoNome &grafo);

        bool Enumera(GrafoNome &grafo, unsigned limVertices);
//		void Enumera(Grafo <MatrizSI> &g);

		void Analisa_Conflitos_Estruturais(VVectorSI & Conf_Efet);

		void Analisa_Conflitos_Efetivos(VVectorSI &Conf_Efet , VVectorSI &Conf_Est);

		void Analisa_Conflitos(VVectorSI &Conf_Efet , VVectorSI &Conf_Est);

		void Analisa_Paralelismos_Estruturais(VVectorSI &Para_Est);

		void Analisa_Paralelismos_Efetivos(VVectorSI &Para_Efet , VVectorSI &Para_Est);

		void Analisa_Paralelismos(VVectorSI &Para_Efet , VVectorSI &Para_Est);

};

#endif // REDEPETRI_H

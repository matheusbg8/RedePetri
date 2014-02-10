#include "RedePetri.h"
#include "Arvore.h"

#define Arredonda(val) val - (int)(val) > 0.5 ? (int)(val) + 1 : (int)(val)

bool RedePetri::produzLog = false;
/**
 * @brief Metodo de inicialização da rede de petri.
 *
 * @param nLugar - Numero de lugar que inicialmente a rede tera.
 * @param nTransicao - Numero de transições que inicialmente a rede tera.
 */
void RedePetri::inicializa(int nLugar , int nTransicao)
{
//	printf("Inicializando rede normal\n" );
	Dimensiona_Rede(nLugar , nTransicao);
	Ciclo_Atual = 0;
	N_Arcos = 0;
	CustoTotal = 0;
}

// Redimensiona a rede para nVertices
/**
 * @brief Redimensiona as matrizes de representação
 * da rede.
 * @param nLugar - Numero de lugares.
 * @param nTransicao - Numero de transições
 */
void RedePetri::Dimensiona_Rede(int nLugar, int nTransicao)
{
    if( nLugar != C.numeroLinhas() || nTransicao != C.numeroColunas() )
	{
		Pre.redim(nLugar , nTransicao);
		Pos.redim(nLugar , nTransicao);
		C.redim(nLugar , nTransicao);
		M.redim(nLugar , 1);
		Ciclo_Atual = 0;
	}
}

/**
 * @brief Realiza a atualização dos indices
 * dos lugares e das transições da rede.
 *
 */
void RedePetri::Atualiza_IDs()
{
    /// @deprecated
    printf("Erro - Atualizacao de IDs nao esta amis disponivel\n");

    /*
	int i , p , t, nLugar = P.size() , nTransicao = T.size();

	for (p=0,t=0, i = 0; i < V.size(); i ++)
	{
		if( p < nLugar)
        {
            P[p].ID = i;
			V[i].Tipo = LUGAR;
            V[i].ID = p++;
		}else if( t < nTransicao)
		{
            T[t].ID = i;
			V[i].Tipo = TRANSICAO;
            V[i].ID = t++;
		}
    }
    */
}


/**
 * @brief
 *  Remove um arco de um lugar para uma transição
 * @param de - id local do lugar origem do arco.
 * @param para - id local da transição de destino do arco.
 */
void RedePetri::Remove_Arco_PT(int de, int para)
{
    // Se o elemento não existe
    if(!P.existeElemento(de) || !T.existeElemento(para))
    {
        printf("Erro, Remove Arco invalido, Transicao ou Lugar inexistente\n" );
        return;
    }

    // Se realmente o arco existe
    if(Pre(de,para) != 0)
    {
        Pre(de, para) = 0;
        C(de , para ) = Pos(de,para);
        N_Arcos--;
        Ciclo_Atual = 0;
    }
}


/**
 * @brief
 *  Remove um arco de uma transição para um lugar
 * @param de - id local da transição de origem.
 * @param para - id local do lugar de destino.
 */
void RedePetri::Remove_Arco_TP(unsigned de, unsigned para)
{
    // Se os elementos existem
    if(!T.existeElemento(de) || !P.existeElemento(para))
    {
        printf("Erro, Remove Arco invalido, Transicao ou Lugar inexistente\n" );
        return;
    }

    // Se o arco realmente existe
    if(Pos(para,de) != 0)
    {
        Pos(para, de) = 0;
        C(para , de ) = - Pre(para , de);
        N_Arcos--;
        Ciclo_Atual = 0;
    }
}

/**
 * @brief Adiciona um novo arco.
 *
 * @param de - ID global de origem.
 * @param para - ID global destino.
 * @param custo - Custo em fichas desse arco.
 */
void RedePetri::Novo_Arco(int de , int para , int custo)
{
    // Se elementos existem
    if(V.existeElemento(de) && V.existeElemento(para))
    {
        if(V[de]->tipo() == LUGAR && V[para]->tipo() == TRANSICAO)
        {
            Lugar *lugar = (Lugar*) V[de];
            Transicao *transicao = (Transicao*) V[para];

            Novo_Arco_PT(lugar->lID, transicao->lID, custo);
        }else if(V[de]->tipo() == TRANSICAO && V[para]->tipo() == LUGAR)
        {
            Transicao *transicao = (Transicao*) V[de];
            Lugar *lugar = (Lugar*) V[para];

            Novo_Arco_TP(transicao->lID, lugar->lID, custo);
        }else
        {
            printf("Erro ao adicionar arco na rede, arco para componentes iguais não é permitido\n");
        }
    }
	else
		printf("Erro ao adicionar arco, ID invalido\n" );		
}


/* Adiciona um arco do Lugar de , para Transicao para*/
/* O ( 1 )  */
int RedePetri::Novo_Arco_PT( int de , int para , int custo)
{
    if(!P.existeElemento(de) || !T.existeElemento(para))
	{
		printf("Erro, Novo Arco invalido, Transicao ou Lugar inexistente\n" );
        return -1;
	}

    if(C(de,para) == 0)
        N_Arcos++;

    Pre(de, para) = custo;
	C(de , para ) = Pos(de,para) - Pre(de , para);
	Ciclo_Atual = 0;

    Arco *novoArco = new Arco(this, ARCO_PT, de, para, custo);
    int id = A.adicionaElemento(novoArco);
    novoArco->setID(id);
    return id;
}

int RedePetri::Novo_Arco_TP( int de , int para , int custo)
{
    if(!T.existeElemento(de) || !P.existeElemento(para))
	{
		printf("Erro, Novo Arco invalido, Transicao ou Lugar inexistente\n" );
        return -1;
	}

    if(C(para,de) == 0)
        N_Arcos++;

    Pos(para, de) = custo;
	C(para , de ) = Pos(para,de) - Pre(para , de);
	Ciclo_Atual = 0;

    Arco *novoArco = new Arco(this, ARCO_TP, de, para, custo);
    int id = A.adicionaElemento(novoArco);
    novoArco->setID(id);
    return id;

}

/* Adiciona um arco da Transição de , para Lugar para*/
/* O ( 1 )  */

void RedePetri::Novo_Arco(ComponentePetri *De , ComponentePetri *Para , int custo)
{
    Novo_Arco(De->gID ,Para->gID, custo);
}


/**
 * @brief
 *  Cria um novo lugar na rede
 * @return int - ID do novo lugar criado.
 */
int RedePetri::RedePetri::Novo_Lugar()
{
    Lugar *novoLugar = new Lugar();

    // Registro no grupo de lugares
    novoLugar->lID = P.adicionaElemento(novoLugar);

    // Registro no grupo de objetos
    novoLugar->gID = V.adicionaElemento(novoLugar);

    // A rede só é redimensionada quando não tiver mais espaço para novos elementos
    if(novoLugar->lID >= C.numeroLinhas())
    {
        Dimensiona_Rede(novoLugar->lID+1 , C.numeroColunas());
    }

    return novoLugar->lID;
}

int RedePetri::Nova_Transicao()
{
    Transicao *novaTransocao = new Transicao();

    // Registro no grupo de Transições
    novaTransocao->lID = T.adicionaElemento(novaTransocao);

    // Registro no grupo de Objetos
    novaTransocao->gID = V.adicionaElemento(novaTransocao);

    // A rede só é redimensionada quando não tiver mais espaço para novos elementos
    if(novaTransocao->lID >= C.numeroColunas())
    {
        Dimensiona_Rede(C.numeroLinhas() , novaTransocao->lID + 1);
    }

    return novaTransocao->lID;
}


/**
 * @brief
 *  Exclui um lugar da rede.
 * @param p - ID do lugar que será excluido
 */
/*
  Ao remover um lugar, a sua representação na rede
não é removida, ela é apenas anulada, eliminando
todos os arcos associados a esse lugar. Foi tomada
esta decisão para evitar uma atualização de todos
os indices dos lugares existentes na rede.
*/
void RedePetri::Exclui_Lugar(int p)
{
    // Se o lugar é válido
    if(P.existeElemento(p))
    {
        Lugar *lugar = P[p];

        // Remove registro local do lugar
        P.removeElemento(p);

        // Remove registro global do lugar
        V.removeElemento(lugar->gID);

        // Remove todos os arcos que possuem relação com o lugar
        for(int i = 0 ; i < C.numeroColunas(); i++)
        {
            Pre(p,i) = 0;
            Pos(p,i) = 0;
            C(p,i) = 0;
        }

        // Apaga todas as fichas
        M(p,0) = 0;

        // Ciclo de cimulação reiniciado
		Ciclo_Atual = 0;

        // Desaloca o lugar
        delete lugar;
    }else
		printf("Erro ao excluir Lugar, lugar inexistente\n" );		
}


/**
 * @brief
 *  Exclui uma transição da rede
 * @param t - ID da transição que sera excluida
 */
/*
  Ao remover uma transição, a sua representação na rede
não é removida, ela é apenas anulada, eliminando
todos os arcos associados a essa transição. Foi tomada
esta decisão para evitar uma atualização de todos
os indices das transições existentes na rede.
*/
void RedePetri::Exclui_Transicao(int t)
{
    // Se existe a transição
    if(T.existeElemento(t))
	{
        Transicao * transicao = T[t];

        // Remove registro local da transição
        T.removeElemento(t);

        // Remove registro global da transição
        V.removeElemento(transicao->gID);

        // Remove todos os arcos assciados a transição excluida
        for(int i = 0 ; i < C.numeroColunas() ; i++)
        {
            Pre(i,t) = 0;
            Pos(i,t) = 0;
            C(i , t) = 0;
        }

		Ciclo_Atual = 0;

        // Deleta transição
        delete transicao;
    }else
        printf("Erro ao excluir Transição, transição inexistente\n" );
}

bool RedePetri::Exclui_Arco(unsigned id)
{
    if(A.existeElemento(id))
    {
        Arco *a = A[id];
        switch(a->tipo())
        {
        case ARCO_PT:
            Exclui_Arco_PT(a->de(),a->para());
            break;
        case ARCO_TP:
            Exclui_Arco_TP(a->de(),a->para());
            break;
        }

        A.removeElemento(id);
        delete a;
    }
}


/**
 * @brief
 *  Exclui um arco que liga uma Transição a um lugar
 * @param de - ID local da transição
 * @param para - ID local do lugar
 * @return bool - True se o arco foi excluido, ou false caso contrario.
 */
bool RedePetri::Exclui_Arco_TP(int de, int para)
{
    /// @todo - implementa a remocao do arco indexado
    if(!T.existeElemento(de) || !P.existeElemento(para))
    {
        printf("Erro, Exclui Arco invalido, Transicao ou Lugar inexistente\n" );
        return false;
    }

    if(Pos(para,de) != 0)
    {
        Pos(para, de) = 0;
        C(para , de ) = - Pre(para , de);
        N_Arcos--;
        Ciclo_Atual = 0;
    }
}

bool RedePetri::Exclui_Arco_PT(int de, int para)
{
    /// @todo - implementa a remocao do arco indexado
    if(!P.existeElemento(de) || !T.existeElemento(para))
    {
        printf("Erro, Exclui Arco invalido, Transicao ou Lugar inexistente\n" );
        return false;
    }

    if(Pre(de, para) != 0x0)
    {
        Pre(de, para) = 0;
        C(de , para ) = Pos(de,para);
        N_Arcos--;
        Ciclo_Atual = 0;
    }
}


/**
 * @brief
 *  Exclui um ComponentePetri da rede
 * @param gID - ID global do componente
 */
void RedePetri::Exclui(int gID)
{
    if(V.existeElemento(gID))
	{
        if(V[gID]->tipo() == TRANSICAO)
        {
            Transicao *transicao = (Transicao*) V[gID];
            Exclui_Transicao(transicao->lID);
        }
        else if( V[gID]->tipo() == LUGAR)
        {
            Lugar *lugar = (Lugar*) V[gID];
            Exclui_Lugar(lugar->gID);
        }
	}else
        printf("Erro ao excluir vertice, gID invalido\n" );
}

void RedePetri::Exclui_Todos_Arcos()
{
	int i , j;
    for ( i = 0; i < C.numeroLinhas(); i ++)
    {
        for ( j = 0; j < C.numeroColunas(); j ++)
		{
			Pos(i,j)= 0;
			Pre(i,j)= 0;
			C(i,j)= 0;
		}
    }
	Ciclo_Atual = 0;
	N_Arcos = 0;
}

void RedePetri::Reinicia_Rede()
{
    // Desaloca todos componentes da rede
    for(int i = 0 ; i <= V.maiorIndice() ; i++)
    {
        if(V.existeElemento(i))
        {
            delete V[i];
        }
    }

    // Apaga registros
    P.apagaTudo();
    T.apagaTudo();
    V.apagaTudo();

    // Apaga representação da rede
    Pre.apagar();
	Pos.apagar();
	C.apagar();
    M.apagar();

	Ciclo_Atual = 0;
	N_Arcos = 0;
}

// Insere fichas em um vértice
void RedePetri::Inserir_Fichas(int p, int pFichas)
{
    if(P.existeElemento(p))
	{
		M(p,0) = pFichas;
        P[p]->fichas.resize(pFichas);
		Ciclo_Atual = 0;
	}else
        printf("Erro, insercao de ficha em lugar invalido\n" );

}

void RedePetri::Define_Peso(unsigned idArco, unsigned peso)
{
    if(!A.existeElemento(idArco)) return;

    Arco *arco = A[idArco];
    unsigned de = arco->de(), para = arco->para();

    arco->setPeso(peso);

    switch(arco->tipo())
    {
    case ARCO_PT:
        Pre(de, para) = peso;
        C(de , para ) = Pos(de,para) - Pre(de , para);
    break;
    case ARCO_TP:
        Pos(para, de) = peso;
        C(para , de ) = Pos(para,de) - Pre(para , de);
    }
    Ciclo_Atual = 0;
}

string &RedePetri::Informacao_Transicao(unsigned t)
{
    if(T.existeElemento(t))
    {
        Transicao *transicao = T[t];
        return transicao->info;
    }

    printf("Erro ao acessar informação da transicao, ID inválido\n");
    return T[t]->info;
}

void RedePetri::Define_Nome_Transicao(unsigned t, string nome)
{
    if(T.existeElemento(t))
    {
        T[t]->setNome(nome);
    }
}

void RedePetri::Nova_Condicao(int t, string Var , string Val)
{
    if(T.existeElemento(t))
	{
        Transicao *transicao = T[t];
        transicao->CondVar.push_back(Var);
        transicao->CondVal.push_back(Val);
		Ciclo_Atual = 0;
	}else
		printf("Erro, nova condicao invalida, a transicao nao existe.\n" );
}

void RedePetri::Nova_Acao( int t , string Var , string Val)
{
    if( T.existeElemento(t))
	{
        Transicao *transicao = T[t];
        transicao->AcaoVar.push_back(Var);
        transicao->AcaoVal.push_back(Val);
		Ciclo_Atual = 0;
	}else
        printf("Erro, nova acao invalida, a transicao nao existe.\n" );
}

bool RedePetri::Define_Informacao_Ficha(unsigned p, unsigned ficha, string info)
{
    if(P.existeElemento(p))
    {
        Lugar *lugar = P[p];
        if(ficha >=0 && ficha < lugar->fichas.size())
        {
            lugar->fichas[ficha] = info;
            return true;
        }
    }
    return false;
}


/**
 * @brief
 *  Acessa a informação de uma ficha de um determinado lugar.

 * @param p - ID do lugar que possui a ficha.
 * @param ficha - ID da ficha.
 * @return string - Informações da ficha.
 */
const string & RedePetri::Informacao_Ficha(unsigned p, unsigned ficha)
{
    if(P.existeElemento(p) )
    {
        Lugar *lugar = P[p];
        if(ficha >=0 && ficha < lugar->fichas.size())
        {
            printf("Retornando informacao da ficha\n");
            return lugar->fichas[ficha];
        }
        else
            printf("Erro ao acessa informacao da ficha, informacao faltando");
    }
    printf("Erro acesso a informacao de ficha inválida\n");
    return P[p]->fichas[ficha];
}

/* Verifica se é possivel disparar transição t*/
bool RedePetri::Sensibilizado(int t)
{
    if(produzLog)
        printf("RedePetri:: Sesibilizado(%d)\n", t);

    if(T.existeElemento(t))
	{
        Transicao *transicao = T[t];

        if(Ciclo_Atual != 0 && transicao->Ciclo_Sensibilizado == Ciclo_Atual )
            return transicao->Sensibilizado;
		else
		{
            transicao->Ciclo_Sensibilizado = Ciclo_Atual;
            return transicao->Sensibilizado = ( M >= Pre.coluna(t) ); // Verifica se ta sensibilisado
		}
	}
	else
		printf("Erro ao verificar sensibilizacao de transicao, a transicao não existe\n" );
    return false;
}

bool RedePetri::Executa_Transicao(int t)
{
	if( Sensibilizado(t) )
	{
		M = M + C.coluna(t);
		Ciclo_Atual ++;
        return true;
	}
    return false;
}


/**
 * @brief
 *
 * @return int - Número de componentes da Rede.
 */
int RedePetri::Numero_Vertices() const
{
    return V.tamanho();
}

int RedePetri::Numero_Transicoes() const
{
    return T.tamanho();
}
		
int RedePetri::Numero_Lugares() const
{
    return P.tamanho();
}

int RedePetri::Numero_Arcos() const
{
    return N_Arcos;
}

int RedePetri::Numero_Fichas(int p) const
{
    if(!P.existeElemento(p))
    {
        printf("Erro ao consultar numero de fchas, indice do lugar invalido\n");
        return 0;
    }
    return M(p,0);
}


/* Retorna ID do precedente ou -1 se não houver precedente */
int RedePetri::Precedente_T(int t) const
{
    if(T.existeElemento(t))
	{
        for (int p = 0; p < Pre.numeroLinhas(); p ++)
			if( Pre(p , t) > 0)
				return p;
	}
	else
		printf("Erro ao obter precedente, transicao invalida\n" );		
	return -1;
}

/* Retorna ID do precedente ou -1 se não houver precedente */
int RedePetri::Precedente_P(int p) const
{
    if(P.existeElemento(p))
	{
        for (int t = 0; t < C.numeroColunas(); t ++)
			if( Pos(p , t) > 0)
				return t;
	}
	else
		printf("Erro ao obter precedente, lugar invalida\n" );
	return -1;
}

/* Retorna gID do precedente ou -1 se não houver precedente */
int RedePetri::Precedente(int gID) const
{
	int id;
    if(V.existeElemento(gID))
    {
        if(V[gID]->tipo() == TRANSICAO)
		{
            Transicao *transicao = (Transicao*) V[gID];
            id = Precedente_T(transicao->lID);
            if(id != -1)
            {
                return P[id]->gID;
            }
            return id;
		}
        else if( V[gID]->tipo() == LUGAR)
		{
            Lugar *lugar = (Lugar*) V[gID];
            id = Precedente_P(lugar->lID);
            if(id != -1)
            {
                return T[id]->gID;
            }
            return id;
		}
    }
	else
		printf("Erro ao obter precedentem, gID inválido\n" );
    return -1;
}

bool RedePetri::existeLugar(int p) const
{
    return P.existeElemento(p);
}

bool RedePetri::existeTransicao(int t) const
{
    return T.existeElemento(t);
}

bool RedePetri::existeArco(int a) const
{
    return A.existeElemento( a);
}

const Lugar &RedePetri::lugar(int id) const
{
    if(P.existeElemento(id))
    {
        printf("Erro ao acessar Lugar, id inválido!\n");
//        return o que ?
    }

    return *(P[id]);
}

/**
 * @brief
 *  Retorna o custo do arco que liga uma transição a um lugar.
 * @param p - ID do lugar
 * @param t - ID da transição
 * @return int - Custo do arco (Numero de fichas)
 */
int RedePetri::Custo_PT(unsigned p, unsigned t) const
{
    if(P.existeElemento(p) && T.existeElemento(t))
    {
        return Pre(p,t);
    }
    return 0;
}

/**
 * @brief
 *  Retorna o custo do arco que liga um lugar a uma transição.
 * @param t - ID da transição
 * @param p - ID do lugar
 * @return int - Custo do arco (Numero de fichas)
 */
int RedePetri::Custo_TP(unsigned t, unsigned p) const
{
    if(P.existeElemento(p) && T.existeElemento(t))
    {
        return Pos(p,t);
    }
    return 0;
}

int RedePetri::Custo_Arco(unsigned id) const
{
    if(A.existeElemento(id))
    {
        return A[id]->peso();
    }
    return 0;
}

list<Lugar*>::iterator RedePetri::lugarBegin()
{
    return P.begin();
}

list<Lugar*>::iterator RedePetri::lugarEnd()
{
    return P.end();
}

list<Transicao*>::iterator RedePetri::transicaoBegin()
{
    return T.begin();
}

list<Transicao*>::iterator RedePetri::transicaoEnd()
{
    return T.end();
}

list<Arco*>::iterator RedePetri::arcoBegin()
{
    return A.begin();
}

list<Arco*>::iterator RedePetri::arcoEnd()
{
    return A.end();
}

/* Imprime todas as arestas do grafo */
void RedePetri::imprime_incidencia()
{
	printf("Matriz Incidencia ( p x t ):\n" );
	C.imprime();
}

void RedePetri::imprime_pos()
{
	printf("Matriz Lugar Posterior Transicao ( p x t ):\n" );
	Pos.imprime();
}

void RedePetri::imprime_pre()
{
	printf("Matriz Lugar Precedente Transicao ( p x t):\n" );
	Pre.imprime();
}

void RedePetri::imprime_marcacao()
{
	printf("Marcacao %d:\n" , Ciclo_Atual);
	M.imprime();
}

// ============= RedePetriAnalise ============================================================

bool RedePetri::Simula_Sensibilizacao(int t, MatrizSI &sM)
{
        if(T.existeElemento(t))
        {
                return sM >= Pre.coluna(t);
        }
        else
                printf("Erro ao simular sensibilizacao de transicao, a transicao não existe\n" );
        return false;
}

MatrizSI RedePetri::Simula_Execucao(int t, MatrizSI &sM)
{
    if(T.existeElemento(t))
    {
        MatrizSI rM(sM.numeroLinhas() , sM.numeroColunas());
        rM = sM + C.coluna(t);
        return rM;
    }
    printf("Erro ao simular execução, transição não existe\n");
    return MatrizSI();
}


void RedePetri::Nome_Marcacao( MatrizSI &M, char * Nome)
{
    short i, p = 0;

    for ( i = 0; i < M.numeroLinhas(); i ++)
    {
        if( M(i , 0 ) )
        {
            p+= sprintf( Nome+p , "p%d" , i);
            if(M(i , 0) > 1)
                    p+= sprintf(Nome+p, "^%d", M(i,0));
        }
    }
}

/*
    Este metodo calcula o grafo de alcançabilidade da rede,
    e realiza um redução de estados infinitos com a tecnica
    do pseudo infinito.
*/
void RedePetri::arvore(GrafoNome &grafo)
{

//    Grafo<Matriz<short> > grafoAlcance;
//    Enumera(grafoAlcance); // Calcula a alcansabilidade da rede


//    if(produzLog)
//        printf("RedePetri:Arvore()\n");

//    if(N_Arcos == 0)
//        return ;

//// Fila utilizada pela busca
//// first é o indice do estado antecessor
//// second é o indice do estado atual
//    queue < pair<int , int> > Fila;

//// string utilizada para armazenar o nome do estado atual
//    char nome[40];

//    MatrizSI sM(1,1);
//    MatrizSI aM(1,1);
//    MatrizSI tM(1,1);

//// Adiciona o estado inicial
//// Copia o 1º nodo do grafo de alcance pro grafo final
//    grafo.novoVerticeD(grafoAlcance[0]);
//    grafo.atribuiNome(0 , grafoAlcance.nomeVertice(0));
//

// Adiciona o indice do vertice(estado inicial) na fila de busca
// sem antecessor é consideredo indice -1
//    Fila.push( pair(-1 , 0) );

//    int t , p,
//    i = 0,j,
//    sID, // ID da marcação atual
//    aID, // ID do antecessor de sID
//    tID, // Id da marcação encontrada após disparo
//    cont = 0 , maxCont = Numero_Transicoes() * Numero_Lugares()*10;

//    while(!Fila.empty() && cont < maxCont)
//    {
//        // Pega o ID do estado atual
//        aID = Fila.front().first;
//        sID = Fila.front().second;

//        // Pega a matriz de marcacao do estado atual
//        sM = grafo[sID];

//        for ( t = 0; t <= T.maiorIndice(); t ++)
//        {
//            if(!T.existeElemento(t)) continue;
//            // Para todas transicoes com ID t existentes na rede de petri


//            if(Simula_Sensibilizacao(t, sM)) // Verifica se é posivel disparar t
//            {

//                tM = Simula_Execucao(t, sM); // Calcula o disparo de t

//                tID = grafo.localizaVertice(tM);

//                if( tID == -1)
//                {
//                    // Vertice não encontrado
//                    Nome_Marcacao(tM , nome);
//                    cont ++;

//                    // Adiciona nova marcação no grafo e na pilha de busca
//                    tID = grafo.novoVerticeD(tM);
//                    grafo.atribuiNome(tID, nome);
//                    Fila.push(tID);
//                }

//                if(tID != sID)
//                    grafo.novaAresta(sID , tID , 1.f);
//                else
//                    printf("=========== Igual no disparo de t%d\n", t);
//            }
//        }
//        Fila.pop();
//    }
//        if(grafo.numeroVertices() <= 1)
//                return grafo;

//        grafo.imprimeGrafoNome();

//        int comp = G.Busca_Componente_Forte();

//        G.imprime_nome();
//        printf("O Grafo possui %d componentes fortemente conexo.\n" , comp);

/*        if(cont == maxCont)
        {
        printf("A enumeração terminou por que foi atingido o numero maximo de %d marcações\n", maxCont);
        }else
        {
                Desenha_Grafo <MatrizSI> (G , screen , 0 , 0 , screen->w , screen->h );
        }
*/
}


/**
 * @brief
 *  Enumer todos os possiveis estados a serem alcançados
 * pela rede a partir do estado atual.
 * @param grafo - Grafo com todos os estados encontrados.
 * @param limVertices - Numero de vértices que serão explorados.
 * @return bool - true se todos os estados foram explorados,
 * false caso o limite foi atingido.
 */
bool RedePetri::Enumera(GrafoNome &grafo, unsigned limVertices)
{
    if(produzLog)
        printf("RedePetri:Enumera()\n");

    pair<string , int>  insercao;
    vector< MatrizSI* > marcacoes;

    queue <short int> Fila;
    char nome[100];

    // Se a rede não possui arcos
    if(N_Arcos == 0)
        return true;

    MatrizSI sM(1,1);
    MatrizSI tM(1,1);

    Nome_Marcacao(M , nome); //Gera um nome em função da matriz

    insercao = grafo.novoVertice(nome);

    marcacoes.resize(insercao.second+1);
    marcacoes[insercao.second] = new MatrizSI(M);

    Fila.push(insercao.second);

    int t,
    sID, // ID da marcação atual
    tID, // Id da marcação encontrada após disparo
    numVertices = 0;

    while(!Fila.empty() && numVertices < limVertices)
    {
        // Pega o primeiro
        sID = Fila.front();
        Fila.pop();

        cout << "Visitando:" << (*marcacoes[sID]) << endl;

        for ( t = 0; t <= T.maiorIndice(); t ++)
        {
            if(T.existeElemento(t) && Simula_Sensibilizacao(t, *marcacoes[sID]))
            {
                cout << "Dispara " << t << ":" << endl;

                // Calcula o disparo de t
                tM = Simula_Execucao(t, *marcacoes[sID]);

                cout << tM << endl;

                //Verifica se foi possivel disparar a transição t
                if(tM.numeroColunas() > 0 && tM.numeroLinhas() > 0)
                {
                    // Pega o nome da marcacao
                    Nome_Marcacao(tM, nome);

                    cout << "Nome: " << nome << endl;

                    // Procura o vertice com o nome
                    tID = grafo.idVertice(nome);

                    // Se nao tem vertice com esse nome
                    if( tID == -1)
                    {
                        cout << "Novo vertice" << endl;

                        // Novo vertice
                        numVertices ++;

                        // Adiciona novo vertce com o nome da marcacao
                        insercao = grafo.novoVertice(nome);
                        tID = insercao.second;

                        if(tID >= marcacoes.size())
                            marcacoes.resize((tID+1)*2);

                        marcacoes[tID] = new MatrizSI(tM);

                        // Agenda visita para o novo vertice
                        Fila.push(tID);
                    }

                    if(tID != sID)
                    {
                        cout << "Nova aresta" << endl;
                        grafo.novaAresta(sID , tID , 1.f, T[t]->getNome());
                    }
                    else
                        printf("=========== Igual no disparo de t%d\n", t);
                }
            }
        }
    }

//        if(grafo.numeroVertices() <= 1)
//                return grafo;

    for(unsigned i = 0 ; i < marcacoes.size() ;i++)
    {
        delete marcacoes[i];
    }

    cout << grafo << endl;

    // Verifica se explorou todos os estados da rede
    if(Fila.empty())
        return true;

    return false;

//        int comp = G.Busca_Componente_Forte();

//        G.imprime_nome();
//        printf("O Grafo possui %d componentes fortemente conexo.\n" , comp);

/*        if(cont == maxCont)
        {
        printf("A enumeração terminou por que foi atingido o numero maximo de %d marcações\n", maxCont);
        }else
        {
                Desenha_Grafo <MatrizSI> (G , screen , 0 , 0 , screen->w , screen->h );
        }
*/

}

void RedePetri::Analisa_Conflitos_Estruturais(VVectorSI & Conf_Efet)
{
    int t , p;
    Conf_Efet.resize(P.maiorIndice()+1);

    for ( p = 0; p <= P.maiorIndice(); p ++)
    {
        if(P.existeElemento(p))
        {
            for ( t = 0; t <= T.maiorIndice(); t ++)
            {
                if(Pre(p,t) != 0)
                    Conf_Efet[p].push_back(t);
            }
        }
    }
}

void RedePetri::Analisa_Conflitos_Efetivos(VVectorSI &Conf_Efet , VVectorSI &Conf_Est)
{
    int p , t;
    Conf_Efet.resize(P.maiorIndice()+1);
    for ( p = 0; p < Conf_Est.size(); p ++)
    {
        if(Conf_Est[p].size() > 1)
        {
            for (t = 0; t < Conf_Est[p].size(); t ++)
            {
                if(Sensibilizado(Conf_Est[p][t]))
                    Conf_Efet[p].push_back(Conf_Est[p][t]);
            }
        }
    }
}

void RedePetri::Analisa_Conflitos(VVectorSI &Conf_Efet , VVectorSI &Conf_Est)
{
    int p , t;

    Analisa_Conflitos_Estruturais(Conf_Est);

    for ( p = 0; p < Conf_Efet.size(); p ++)
    {
        if(Conf_Est[p].size() > 1)
        {
            printf("Conflito Estrutura no lugar p%d com :", p);
            for ( t = 0; t < Conf_Est[p].size(); t ++)
                printf(" t%d", Conf_Est[p][t]);
            printf("\n");
        }
    }

    Analisa_Conflitos_Efetivos(Conf_Efet , Conf_Est);

    for ( p = 0; p < Conf_Efet.size(); p ++)
    {
        if(Conf_Efet[p].size() > 1)
        {
            printf("Conflito Efetivo no lugar p%d com :", p );
            for ( t = 0; t < Conf_Efet[p].size(); t ++)
                    printf(" t%d", Conf_Efet[p][t] );
            printf("\n" );

        }
    }
}

void RedePetri::Analisa_Paralelismos_Estruturais(VVectorSI &Para_Est)
{
    Para_Est.resize( P.maiorIndice() +1);
    int p , t ;
    for ( p = 0; p < Pre.numeroLinhas(); p ++)
    {
        for ( t = 0; t < Pre.numeroColunas(); t ++)
        {
            if(Pre(p, t) == 0)
                Para_Est[p].push_back(t);
        }
    }
}

void RedePetri::Analisa_Paralelismos_Efetivos(VVectorSI &Para_Efet , VVectorSI &Para_Est)
{
    Para_Efet.resize( P.maiorIndice()+1 );
    int p , t;
    for ( p = 0; p < Para_Est.size(); p ++)
    {
        if(Para_Est[p].size() > 1)
        for ( t = 0; t < Para_Est[p].size(); t ++)
        {
            if(Sensibilizado(Para_Est[p][t]))
                Para_Efet[p].push_back(Para_Est[p][t]);
        }
    }
}

// Paralelismo =  !Conflito
void RedePetri::Analisa_Paralelismos(VVectorSI &Para_Efet , VVectorSI &Para_Est)
{
    int p , t;

    Analisa_Paralelismos_Estruturais(Para_Est);

    for ( p = 0; p < Para_Est.size(); p ++)
    {
        if(Para_Est[p].size() > 1)
        {
            printf("Paralelismo Estrutura no lugar p%d com :", p);
            for ( t = 0; t < Para_Est[p].size(); t ++)
                printf(" t%d", Para_Est[p][t]);
            printf("\n");
        }
    }

    Analisa_Paralelismos_Efetivos(Para_Efet , Para_Est);

    for ( p = 0; p < Para_Efet.size(); p ++)
    {
        if(Para_Efet[p].size() > 1)
        {
            printf("Paralelismo Efetivo no lugar p%d com :", p );
                for ( t = 0; t < Para_Efet[p].size(); t ++)
                    printf(" t%d", Para_Efet[p][t] );
            printf("\n" );
        }
    }

}

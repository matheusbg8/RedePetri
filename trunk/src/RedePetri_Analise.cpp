bool RedePetri::Simula_Sensibilizacao(int t, MatrizSI &sM)
{
	if(t >= 0 && t < T.size() )
	{
		return sM >= Pre.coluna(t);
	}
	else
		printf("Erro ao simular sensibilizacao de transicao, a transicao não existe\n" );
	return false;
}

MatrizSI RedePetri::Simula_Execucao(int t, MatrizSI &sM)
{
	MatrizSI rM(sM.numeroLinhas() , sM.numeroColunas());
	rM = sM + C.coluna(t);
	return rM;
}

void RedePetri::Enumera()
{
	if(N_Arcos == 0)
		return;

	G.Apagar_Grafo();
	queue <short int> Fila;
	char nome[300];

	MatrizSI sM;
	MatrizSI tM;

	G.Novo_Vertice(M);
	Nome_Marcacao(M , nome);
	G.Atribui_Nome(0, nome);

	Fila.push(0);

	int t , p,
        i = 0,j,
        sID , tID,
        cont = 0 , maxCont = Numero_Transicoes() * Numero_Lugares()*10;

	while(!Fila.empty() && cont < maxCont)
	{
		sID = Fila.front();
		sM = G[sID];

		for ( t = 0; t < T.size(); t ++)
		{
			if(Simula_Sensibilizacao(t, sM)) // Verifica se é posivel disparar t
			{
				tM = Simula_Execucao(t, sM); // Calcula o disparo de t

				tID = G.Localiza( tM ); // Localiza o vertice

				if( tID == -1)
				{ // Vertice não encontrado
					Nome_Marcacao(tM , nome);
					cont ++;
					tID = G.Novo_Vertice(tM);
					G.Atribui_Nome(tID, nome);
					Fila.push(tID);
				}
				G.Nova_ArestaID(sID , tID , 1.0);
			}
		}
		Fila.pop();
	}

	if(G.Numero_Vertices() <= 1)
		return;

	int comp = G.Busca_Componente_Forte();
	
	G.imprime_nome();
	printf("O Grafo possui %d componentes fortemente conexo.\n" , comp);
	
/*
	if(cont == maxCont)
	{
	printf("A enumeração terminou por que foi atingido o numero maximo de %d marcações\n", maxCont);
	}else
	{
		Desenha_Grafo <MatrizSI> (G , screen , 0 , 0 , screen->w , screen->h );
	}		
*/

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

void RedePetri::Analisa_Conflitos_Estruturais(VVectorSI & Conf_Efet)
{
	int t , p;
	Conf_Efet.resize(P.size());

	for ( p = 0; p < P.size(); p ++)
		for ( t = 0; t < T.size(); t ++)
			if(Pre(p,t) != 0)
				Conf_Efet[p].push_back(t);
}

void RedePetri::Analisa_Conflitos_Efetivos(VVectorSI &Conf_Efet , VVectorSI &Conf_Est)
{
	int p , t;
	Conf_Efet.resize(P.size());
	for ( p = 0; p < Conf_Est.size(); p ++)
		if(Conf_Est[p].size() > 1)
			for ( t = 0; t < Conf_Est[p].size(); t ++)
				if(Sensibilizado(Conf_Est[p][t]))
					Conf_Efet[p].push_back(Conf_Est[p][t]);
}		

void RedePetri::Analisa_Conflitos(VVectorSI &Conf_Efet , VVectorSI &Conf_Est)
{
	int p , t;

	Analisa_Conflitos_Estruturais(Conf_Est);

	for ( p = 0; p < P.size(); p ++)
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
	
	for ( p = 0; p < P.size(); p ++)
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
	Para_Est.resize( P.size() );
	int p , t ;
	for ( p = 0; p < P.size(); p ++)
		for ( t = 0; t < T.size(); t ++)
			if(Pre(p, t) == 0)
				Para_Est[p].push_back(t);				
}
void RedePetri::Analisa_Paralelismos_Efetivos(VVectorSI &Para_Efet , VVectorSI &Para_Est)
{
	Para_Efet.resize( P.size() );
	int p , t;
	for ( p = 0; p < Para_Est.size(); p ++)
		if(Para_Est[p].size() > 1)
			for ( t = 0; t < Para_Est[p].size(); t ++)
				if(Sensibilizado(Para_Est[p][t]))
					Para_Efet[p].push_back(Para_Est[p][t]);
}

// Paralelismo =  !Conflito
void RedePetri::Analisa_Paralelismos(VVectorSI &Para_Efet , VVectorSI &Para_Est)
{
	int p , t;

	Analisa_Paralelismos_Estruturais(Para_Est);

	for ( p = 0; p < P.size(); p ++)
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
	
	for ( p = 0; p < P.size(); p ++)
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

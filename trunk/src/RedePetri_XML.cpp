bool str_comp ( char *a, const char *b)
{
	while(*a == *b && *a != 0)
	{ a ++; b++; }
	if(*a == 0 && *b == 0)
		return true;
	else
		return false;
}


void RedePetri::Extrai_VarVal(const char *p , char *Var , char *Val)
{
	while(*p == ' ') p++;
	while(*p != '=')
	{
		*Var = *p;
		Var++; p++;
	}
	*Var = 0;
	p++;
	while(*p == ' ') p++;
	while(*p != 0)
	{
		*Val = *p;
		Val++; p++;
	}
	*Val = 0;
}

void RedePetri::Extrai_Objeto(const char * p , Objeto &R)
{
	while(*p != 0)
	{
		if(*p == 't')
		{
			R.Tipo = TRANSICAO;
			R.ID = atoi(++p);
		}
		else if(*p == 'p')
		{
			R.Tipo = LUGAR;
			R.ID = atoi(++p);
		}else if(R.Tipo == INDEFINIDO && *p >= 48 && *p <= 58)
		{
			int id = atoi(p);
			if(id < V.size() )
				R = V[id];				
		}
		p++;
	}
}

int RedePetri::XML_palavra( FILE *arq , char *p )
{
	if( arq == 0x0)
		return -1;

	int ind = 0;
	char c;
	while( (c = fgetc(arq) ) != -1)
	{
		if( c == '<' || c == '>')
		{
			if(ind > 0)
			{
				p[ind++] = 0;
				return ind;
			}
		}else if(c != 10 && c != '/' && c != ' ' && c != '\t' && c != 0)
			p[ind++] = c;
	}
	return -1;
}



void RedePetri::XML_Transicao(FILE *arq)
{
	char p[100], var[40] , val[40];
	int X = 0, Y =0 , ID = -1;
	Objeto Obj;

	while( 	XML_palavra(arq, p) )
	{
		if(str_comp(p, "gID"))
		{
			XML_palavra(arq,p); // Numero
			ID = atoi(p);
			XML_palavra(arq,p); // FIm
		}
		if(str_comp(p, "ID"))
		{
			XML_palavra(arq,p); // Obj
			Extrai_Objeto(p , Obj);
			XML_palavra(arq,p); // FIm
		}
		else if(str_comp(p, "Condicao"))
		{
			XML_palavra(arq,p);// Condição
			Extrai_VarVal(p , var , val);
			Nova_Condicao(Obj.ID , var , val);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p,  "Acao"))
		{
			XML_palavra(arq,p);// Acao
			Extrai_VarVal(p , var , val);
			Nova_Acao(Obj.ID , var , val);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p, "X"))
		{
			XML_palavra(arq,p);// Valor
			X = atoi(p);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p, "Y"))
		{
			XML_palavra(arq,p);// Valor
			Y = atoi(p);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p, "Transicao")) // Fim Transicao
		{
			if( Obj.Tipo == TRANSICAO && Obj.ID >=0 && Obj.ID < T.size() )
				Salva_Pos_T( Obj.ID, X , Y);
			else
				printf("Erro ao ler XML, definição de transição invalida" );										
			break;
		}
	}
}

void RedePetri::XML_Lugar(FILE *arq)
{
	char p[100];
	int X = 0 , Y = 0 ,Num_Fichas = 0, gID;
	Objeto Obj;
	while( 	XML_palavra(arq, p) )
	{
		if( str_comp(p, "gID"))
		{
			XML_palavra(arq,p); // Numero
			gID = atoi(p);
			XML_palavra(arq,p); // FIm
		}
		if( str_comp(p, "ID"))
		{
			XML_palavra(arq,p); // Obj
			Extrai_Objeto(p , Obj);
			XML_palavra(arq,p); // FIm
		}
		else if(str_comp(p, "Fichas"))
		{
			XML_palavra(arq,p);// NFichas
			Num_Fichas = atoi(p);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p, "X"))
		{
			XML_palavra(arq,p);// Valor
			X = atoi(p);
			XML_palavra(arq,p);// Fim
		}
		else if( str_comp(p, "Y"))
		{
			XML_palavra(arq,p);// Valor
			Y = atoi(p);
			XML_palavra(arq,p);// Fim
		}
		else if( str_comp(p,  "Lugar")) // Fim Lugar
		{
			if(Obj.Tipo == LUGAR && Obj.Tipo >= 0 && Obj.Tipo < P.size())
			{
				Salva_Pos_P(Obj.ID, X , Y);
				Inserir_Fichas(Obj.ID, Num_Fichas);
			}else
				printf("Erro ao ler XML, Definição de lugar invalida\n" );
				
			break;
		}
	}
}

void RedePetri::XML_Arco(FILE *arq)
{
	char p[100];
	Objeto De , Para;
	int Peso = 0;
	while( 	XML_palavra(arq, p) )
	{
		if(str_comp(p,  "De"))
		{
			XML_palavra(arq,p); // ID De
			Extrai_Objeto(p , De);
			XML_palavra(arq,p); // FIm
		}
		else if(str_comp(p, "Para"))
		{
			XML_palavra(arq,p);// ID Para
			Extrai_Objeto(p , Para);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p, "Peso"))
		{
			XML_palavra(arq,p);// Valor
			Peso = atoi(p);
			XML_palavra(arq,p);// Fim
		}
		else if(str_comp(p, "Arco")) // Fim Arco
		{
			if(De.ID != -1 && Para.ID != -1)
				Novo_Arco(De , Para , Peso);
			else
				printf("Erro ao ler XML, definição de arco invalida\n" );
				
			break;
		}
	}
}

void RedePetri::Carrega_XML(const char * arq_nome)
{
	FILE *arq = fopen(arq_nome , "r" );
	if(!arq)
	{
		printf("Erro ao abrir arquivo %s\n" , arq_nome);
		return ;
	}
	char p[100];
	int NTransicao = -1, NLugar = -1, NArcos = -1;
	printf("Lendo XML\n" );
	Reinicia_Rede();
	while(XML_palavra( arq , p ) != -1)
	{
		if(str_comp(p, "NumeroTransicoes"))
		{
			XML_palavra( arq , p );
			NTransicao = atoi(p);
			if(NLugar != -1)
				Dimensiona_Rede(NLugar , NTransicao);
			XML_palavra( arq , p );
		}
		else if (str_comp(p, "NumeroLugar"))
		{
			XML_palavra( arq , p );
			NLugar = atoi(p);
			if(NTransicao != -1)
				Dimensiona_Rede(NLugar , NTransicao);
			XML_palavra( arq , p );
		}
		else if (str_comp(p, "NumeroArco"))
		{
			XML_palavra( arq , p );
			NArcos = atoi(p);
			XML_palavra( arq , p );
		}
		else if (str_comp(p, "Transicao"))
		{
			XML_Transicao(arq);
		}
		else if (str_comp(p, "Lugar"))
		{
			XML_Lugar(arq);
		}
		else if (str_comp(p, "Arco"))
		{
			XML_Arco(arq);
		}
	}
	if (N_Arcos != NArcos)
		printf("Ocorreu um erro ao ler XML, Número de arcos não confere\n" );
		
	fclose(arq);
}


void RedePetri::Gera_XML(const char *Nome_Arq) //Nome_Arq pŕe inicializado com 0x0
{
	
	FILE *arq;
	if(!(arq = fopen(Nome_Arq , "w") ))
	{
		printf("Erro ao salvar o arquivo %s\n", Nome_Arq );
		return;
	}

	fprintf(arq , "<?xml version=\"1.0\"?>\n");
	fprintf(arq , "<RedePetri>\n");
	fprintf(arq , "\t<NumeroTransicoes> %d </NumeroTransicoes>\n", Numero_Transicoes());
	fprintf(arq , "\t<NumeroLugar> %d </NumeroLugar>\n", Numero_Lugares());
	fprintf(arq , "\t<NumeroArco> %d </NumeroArco>\n", Numero_Arcos());

	int i,j,k;

	for ( i = 0; i < P.size(); i ++)
	{
		fprintf(arq , "\t<Lugar>\n");
		fprintf(arq , "\t\t<gID> %d </gID>\n" , P[i].ID);
		fprintf(arq , "\t\t<ID> p%d </ID>\n" , i);
		if(P[i].Desenhado)
		{
			fprintf(arq , "\t\t<X> %d </X>\n" , P[i].x);
			fprintf(arq , "\t\t<Y> %d </Y>\n" , P[i].y);
		}

		fprintf(arq , "\t\t<Fichas> %d </Fichas>\n" , M(i,0));
		fprintf(arq , "\t</Lugar>\n");
	}
	for ( i = 0; i < T.size(); i ++)
	{
		fprintf(arq , "\t<Transicao>\n");
		fprintf(arq , "\t\t<gID> %d </gID>\n" , T[i].ID);
		fprintf(arq , "\t\t<ID> t%d </ID>\n" , i);
		if(T[i].Desenhado)
		{
			fprintf(arq , "\t\t<X> %d </X>\n" , T[i].x);
			fprintf(arq , "\t\t<Y> %d </Y>\n" , T[i].y);
		}

		if((k = T[i].CondVar.size()) > 0)
			for ( j = 0; j < k; j ++)
				fprintf(arq , "\t\t<Condicao> %s = %s </Condicao>\n",
                           T[i].CondVar[j].c_str() , T[i].CondVal[j].c_str() );
		if((k = T[i].AcaoVar.size()) > 0)
			for ( j = 0; j < k; j ++)
				fprintf(arq , "\t\t<Acao> %s = %s </Acao>\n",
                           T[i].AcaoVar[j].c_str() , T[i].AcaoVal[j].c_str() );
		fprintf(arq , "\t</Transicao>\n");
	}

	for ( i = 0; i < P.size(); i ++)
		for ( j = 0; j < T.size(); j ++)
		{
			if( Pre(i , j ) > 0)
			{
				fprintf(arq , "\t<Arco>\n");
				fprintf(arq , "\t\t<De> p%d </De>\n" , i);
				fprintf(arq , "\t\t<Para> t%d </Para>\n" , j);
				fprintf(arq , "\t\t<Peso> %d </Peso>\n" , Pre(i,j));
				fprintf(arq , "\t</Arco>\n");
			}
			if( Pos(i , j ) > 0)
			{
				fprintf(arq , "\t<Arco>\n");
				fprintf(arq , "\t\t<De> t%d </De>\n" , j);
				fprintf(arq , "\t\t<Para> p%d </Para>\n" , i);
				fprintf(arq , "\t\t<Peso> %d </Peso>\n" , Pos(i,j));
				fprintf(arq , "\t</Arco>\n");
			}
		}
	fprintf(arq , "</RedePetri>\n");
	fclose(arq);
}


void RedePetri::Gera_Base_XML(const char *Nome_Arq)
{
	FILE *arq;
	if(!(arq = fopen(Nome_Arq , "w") ))
	{
		printf("Erro ao salvar o arquivo %s\n", Nome_Arq );
		return;
	}

	fprintf(arq , "<?xml version=\"1.0\"?>\n");
	fprintf(arq , "<BaseRegras>\n");

	int t,i,k, regra = 1;

	for ( t = 0; t < T.size(); t ++)
	{
		if(T[t].CondVar.size() > 0 || T[t].AcaoVar.size() > 0)
		{
			fprintf(arq , "\t<Regra%03d>\n", regra);
			if((k = T[t].CondVar.size()) > 0)
				for ( i = 0; i < k; i ++)
					fprintf(arq , "\t\t<Condicao> %s = %s </Condicao>\n",
	                           T[t].CondVar[i].c_str() , T[t].CondVal[i].c_str() );
			if((k = T[t].AcaoVar.size()) > 0)
				for ( i = 0; i < k; i ++)
					fprintf(arq , "\t\t<Acao> %s = %s </Acao>\n",
	                           T[t].AcaoVar[i].c_str() , T[t].AcaoVal[i].c_str() );
			fprintf(arq , "\t</Regra%03d>\n", regra++);
		}
	}
	fprintf(arq , "</BaseRegras>\n");
	fclose(arq);
}



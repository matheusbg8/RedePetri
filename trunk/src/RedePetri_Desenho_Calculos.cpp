void RedePetri_Desenho::Calcula_Arco_TP(int t , int p , Arco &A )
{
	if( p < 0 || p >= P.size() || t < 0 || t >= T.size()  )
	{
		printf("Erro ao Calcular Arco, transicao ou lugar invalido\n" );
		return;
	}

	Calcula_Trajetoria(T[t].x ,T[t].y , P[p].x , P[p].y , A);

	Calcula_CorteRetaCirc( A[A.N_Pontos()-2].x , A[A.N_Pontos()-2].y,
                           A[A.N_Pontos()-1].x , A[A.N_Pontos()-1].y,
                           Raio, A[A.N_Pontos()-1].x , A[A.N_Pontos()-1].y);
}

void RedePetri_Desenho::Calcula_Arco_PT(int p, int t , Arco &A)
{
	if( p < 0 || p >= P.size() || t < 0 || t >= T.size()  )
	{
		printf("Erro ao Calcular Arco, transicao ou lugar invalido\n" );
		return;
	}


	Calcula_Trajetoria(P[p].x ,P[p].y , T[t].x , T[t].y , A);

	Calcula_IntersecRet( A[ A.N_Pontos() -2].x , A[ A.N_Pontos() -2].y,
                         A[ A.N_Pontos() -1].x , A[ A.N_Pontos() -1].y ,
						 T[t].x - TRANSICAO_LARGURA/2 , T[t].y - TRANSICAO_ALTURA/2,
						 T[t].x + TRANSICAO_LARGURA/2,T[t].y + TRANSICAO_ALTURA/2,
						 A[ A.N_Pontos()-1].x , A[ A.N_Pontos()-1].y);

}

void RedePetri_Desenho::Calcula_CorteRetaCirc( short rx1, short ry1 , short rx2, short ry2,
                        				       short raio,short &px ,short &py)
{
	float
	//Vetor Cartesianos
	vx = rx1 - rx2,
	vy = ry1 - ry2,
	rho = sqrt(vx *vx + vy*vy),
	senoTheta = vy / rho,
	cossenoTheta = vx / rho;
	px = raio * cossenoTheta + rx2;
	py = raio * senoTheta + ry2;
}

void RedePetri_Desenho::Calcula_IntersecRet( short rx1, short ry1 , short rx2, short ry2,
                                             short qx1, short qy1 , short qx2 , short qy2,
                                             short &px ,short &py)
{
	float
	//Vetor Cartesianos
	vx = rx1 - rx2,
	vy = ry1 - ry2;
	
	if(ry1 > ry2)
		py = qy2;
	else
		py = qy1;

	px = rx1 + vx * (py - ry1)/vy;

	if(px < qx1 || px > qx2)
	{
		if(rx1 > rx2)
			px = qx2;
		else
			px = qx1;
		py = ry1 + vy * (px - rx1)/vx;
	}
/*
	if( (px < qx1 || px > qx2) &&
	    (py < qy1 || py > qy2) )
	{
		printf("Erro ao calcular intercecção reta com retangulo, não há intersecção\n" );
		px = 0; py = 0;
	}
*/	
}

float RedePetri_Desenho::Calcula_Angulo( int x1, int y1 , int x2 , int y2)
{
	if( x1 == x2) x2++;
	float
	vx = x1 - x2,
	vy = y1 - y2,
	
	rho = sqrt(vx *vx + vy*vy),
	senoTheta = vy / rho,
	cossenoTheta = vx / rho,
	theta = acos(abs(cossenoTheta));
	
    if ( cossenoTheta < 0 & senoTheta >=0 ) // 2º quadrante
        theta = PI - theta;
    else if ( cossenoTheta < 0 & senoTheta < 0 ) // 3º quadrante
        theta += PI;
    else if( cossenoTheta >= 0 && senoTheta < 0) // 4º quadrante
        theta = 2.0 * PI - theta;
	// senao 1º quadrante (nam precisa fazer nada)
		
	return theta;
}

char RedePetri_Desenho::Encontra_Direcao(int oi , int oj , int di , int dj)
{
	if( oi > di && oj == dj)
		return N;
	else if(oi == di && oj < dj)
		return L;
	else if(oi < di && oj == dj)
		return S;
	else if(oi == di && oj > dj)
		return O;
	else if(oi > di && oj < dj)
		return NE;
	else if(oi < di && oj < dj)
		return SE;
	else if(oi < di && oj > dj)
		return SO;
	else if(oi > di && oj > dj)
		return NO;
}

char soma_circular( char val , char val2, char tam )
{
	val += val2;
	if( val >= tam)
		val = 0;
	else if( val < 0)
		val = tam-1;
	return val;
}

void imprime_d(char d)
{
	switch(d)
	{
		case 0:	printf("Norte\n" );	break;
		case 1:	printf("Nordeste\n" );	break;
		case 2:	printf("Leste\n" );	break;
		case 3:	printf("Suldeste\n" );	break;
		case 4:	printf("Sul\n" );	break;
		case 5:	printf("Suldoeste\n" );	break;
		case 6:	printf("Oeste\n" );	break;
		case 7:	printf("Noroeste\n" );	break;
		default: printf("Indefinido\n" ); break;
	}
}
char RedePetri_Desenho::Inverte_Direcao(char d)
{
	switch(d)
	{
		case N:  return S; break;
		case S:  return N; break;
		case L:  return O; break;
		case O:  return L; break;
		case NO:  return SE; break;
		case SE:  return NO; break;
		case NE:  return SO; break;
		case SO:  return NO; break;
		default: printf("Erro ao inverter direcao, direcao indefinida\n" );
				return N;
		break;		
	}
}

char RedePetri_Desenho::Encontra_Caminho(int oi , int oj , char d , char da)
{
	char s = 1;
	char r = 1;
	char di = d; // direcao inicial
	int i;
	da = Inverte_Direcao(da); // direcao antiga
	for (int i = 0; i < 3; i ++)
	{
		if(d != da && !Md_Ocupada(oi + tp[d].y ,  oj + tp[d].x) )
			return d;
		else
		{				
			d = soma_circular(di , r*s , 8);
			s*= -1;
			if(s>0) r++;
		}
	}
	r= 0;
	d = Inverte_Direcao(da);
	
	for (i = 0; i < 8; i ++)
	{
		if(!Md_Ocupada(oi + tp[d].y ,  oj + tp[d].x) )
			return d;
		else
		{				
			d = soma_circular(di , r*s , 8);
			s*= -1;
			if(s>0) r++;
		}
	}

	return di;/* Não foi possivel encontrar caminho desocupado */
}

void RedePetri_Desenho::Calcula_Trajetoria(int x1 , int y1 , int x2 , int y2 , Arco &A)
{
/*	printf("N (%d,%d)\n" , tp[N].x , tp[N].y);
	printf("NE(%d,%d)\n" , tp[NE].x , tp[NE].y);
	printf("L (%d,%d)\n" , tp[L].x , tp[L].y);
	printf("SE(%d,%d)\n" , tp[SE].x , tp[SE].y);
	printf("S (%d,%d)\n" , tp[S].x , tp[S].y);
	printf("SO(%d,%d)\n" , tp[SO].x , tp[SO].y);
	printf("O (%d,%d)\n" , tp[O].x , tp[O].y);
	printf("NO(%d,%d)\n" , tp[NO].x , tp[NO].y);
*/

	short oi ,oj,	di , dj;
	ConvertePosMat(x1 , y1 , oi , oj);
	ConvertePosMat(x2 , y2 , di , dj);
	A.Exclui_Todos_Pontos();
	Ponto Atual(oi , oj);

	char d,da;
	da = Encontra_Direcao(Atual.x , Atual.y , di , dj);
	da = Encontra_Caminho(Atual.x , Atual.y , da , da);
//	printf("Inicio" );
//	imprime_d(da);
	A.Novo_Ponto(x1 , y1);
	int ss;
	while(Atual.x != di || Atual.y != dj)
	{
		d = Encontra_Direcao(Atual.x , Atual.y , di , dj);
		if(abs(Atual.x - di) >1 || (Atual.y - dj) > 1)
			d = Encontra_Caminho(Atual.x , Atual.y , d , da);
		if(d != da)
		{
//			imprime_d(d);
			ConverteMatPos(Atual.x , Atual.y , oi , oj);
			A.Novo_Ponto(oi , oj);
			if(A.N_Pontos() > 7)
				break;		
			da = d;
		}
		// Pq estamos usando x como i e y como j
		Atual.x += tp[d].y;
		Atual.y += tp[d].x;	
			
		if((Atual.x < 0 || Atual.x >= iMAX) && ( Atual.y < 0 || Atual.y >= jMAX))
			break;
	}
	A.Novo_Ponto( x2 , y2);
}


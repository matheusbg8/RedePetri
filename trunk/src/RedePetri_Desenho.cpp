void RedePetri_Desenho::AtualizaImagemDeExibicao()
{
	blit(img, screen , pVx , pVy , VIEW_X, VIEW_Y , VIEW_W, VIEW_H);
}

void RedePetri_Desenho::Inicializa_Desenho()
{
	igRede = this; // Referencia global da rede
	
	Inicializa_Allegro();
	
	Inicializa_Cores();

	int i , j;

	// Posições de visualizacao da imagem
	pVx = (img->w - screen->w) / 2;
	pVy = (img->h - screen->h) / 2;

	ObjSelecionado.ID = 0;
	ObjSelecionado.Tipo = TRANSICAO;
	Grade_Ativado = GRADE_ATIVADO;
	Imprime_Md_Ativado = true;
	Alinhamento_Automatico = ALINHAMENTO_AUTOMATICO;
	ExecucaoAutomatica = EXECUCAO_AUTOMATICA;

	
	Raio = 10;	
}

void FecharTudo()
{
	allegro_exit();
	exit(-1);
}

void RedePetri_Desenho::Inicializa_Allegro()
{
	allegro_init();
	install_mouse();
	install_keyboard();
	install_timer();
	
	set_color_depth(COLOR_BITS );

	if(install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, 0)<0){
		printf("ERRO ao inicializar SOM\n");
	}

	if (set_gfx_mode(VIDEO_CARD, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y) < 0)
	{
		printf("Erro ao inicializar o modo grafico\n");
		return ;
	}

	rectfill(screen, 0, 0, screen->w, screen->h, 0xffffff);
	show_os_cursor(2);
	img = create_bitmap( IMGW , IMGW);
	rectfill(img, 0, 0, img->w, img->h, 0xffffff);
	set_close_button_callback(FecharTudo);
}

void RedePetri_Desenho::Inicializa_Cores()
{
	cor[0] = 0xff8e00 ;	/*Laranja*/
	cor[1] = 0xffe700 ;	/*Amarelo*/
	cor[2] = 0x10ff00 ;  /*Verde Claro*/
	cor[3] = 0x008417 ;	/*Verde Escuro*/
	cor[4] = 0x00fff6 ;	/*Azul Claro*/
	cor[5] = 0x000fff ;	/*Azul*/
	cor[6] = 0xa800ff ;	/*Roxo*/
	cor[7] = 0xfd00ff ;	/*Roza*/
	cor[8] = 0xff0000 ;	/*Vermelho*/
}

void RedePetri_Desenho::Desalloca()
{
	allegro_exit();
}

void RedePetri_Desenho::Desenha_Rede()
{
	rectfill(img ,0 , 0,  xMAX , yMAX , 0xffffff);

	if(Grade_Ativado)
		Desenha_Grade();

	Desenha_Arcos();
	
	for (int i = 0; i < V.size(); i ++)
		Desenha_Vertice(i);
}

void RedePetri_Desenho::Desenha_Transicao(int t , int Cor)
{
	if(t >= 0 && t < T.size() )
	{
		if(!T[t].Desenhado) Calcula_Posicao(T[t].ID);
		if(T[t].Desenhado)
		{
			int x1 = T[t].x - TRANSICAO_LARGURA/2,
				y1 = T[t].y - TRANSICAO_ALTURA/2 ,
				x2 = T[t].x + TRANSICAO_LARGURA/2,
				y2 = T[t].y + TRANSICAO_ALTURA/2;

			rectfill(img, x1 , y1 , x2 , y2 , Cor);
			rect(img, x1 , y1 , x2 , y2 , 0x0);
			textprintf_ex( img , font, x2 + 3 , y1 , 0x0000ff, -1, "t%d", t);
		}else
			printf("Erro ao desenhar Transição, Transição sem posição definida\n" );			
	}else
		printf("Erro ao desenhar Transição, Transição Invalida\n" );		
}

void RedePetri_Desenho::Desenha_Lugar(int p , int Cor)
{
	if(p >= 0 && p < P.size() )
	{
		if(!P[p].Desenhado) Calcula_Posicao(P[p].ID);
		if(P[p].Desenhado)
		{
			circlefill(img, P[p].x , P[p].y , Raio , Cor);
			circle(img, P[p].x , P[p].y , Raio , 0x0); // Contorno
			textprintf_ex( img , font, P[p].x-5 , P[p].y-5 , 0x000000, -1, "%d", M(p,0));
			textprintf_ex( img , font, P[p].x+ 15, P[p].y+5 , 0x0000ff, -1, "p%d", p);
		}else
			printf("Erro ao desenhar lugar, lugar sem posição definida\n" );			
	}else
		printf("Erro ao desenhar Lugar , Lugar Invalido\n" );		
}

void RedePetri_Desenho::Desenha_Vertice(int gID)
{
	if(gID >= 0 && gID < V.size() )
	{
		if(V[gID].Tipo == TRANSICAO)
			if(Sensibilizado(V[gID].ID))
				Desenha_Transicao(V[gID].ID , 0x00ffff);
			else
				Desenha_Transicao(V[gID].ID , 0x00ff00);
		else if(V[gID].Tipo == LUGAR)
			if(M(V[gID].ID, 0) > 0)
				Desenha_Lugar(V[gID].ID , 0xe0cA4f);
			else
				Desenha_Lugar(V[gID].ID , 0xffff00);
	}else
		printf("Erro ao desenhar Vertice, Vertice invalido\n" );		
}
 
/* Explora a rede, realizando chamadas para func( u , v)*/
void RedePetri_Desenho::Desenha_Arcos( )
{
	int t, p;
	Arco A;
	for ( p = 0; p < P.size(); p ++)
		for ( t = 0; t < T.size(); t ++)
		{
			if(Pre(p,t) > 0)
			{
				Calcula_Arco_PT(p , t , A);
				Desenha_Seta(A , Pre(p,t) , cor[t%N_CORES] );
			}
			if(Pos(p,t) > 0)
			{
				Calcula_Arco_TP(t , p , A);
				Desenha_Seta(A, Pos(p,t) , cor[t%N_CORES] );
			}
		}
}


void RedePetri_Desenho::Desenha_Seta( Arco & A , int custo , int cor)
{
	int np = A.N_Pontos();
	if(np <= 0 )
	{
		printf("Erro ao desenhar seta, arco sem pontos\n" );
		return;		
	}
	int x1 = A[0].x,
		y1 = A[0].y,
		x2, y2, i;

	for ( i = 1; i < np; i ++)
	{
		x2 = A[i].x; y2= A[i].y;
		fastline(img , x1 , y1, x2 , y2 , cor);		
		circlefill(img , x2,y2, 2 , cor);
		x1 = x2; y1 = y2;
	}
	x1 = A[A.N_Pontos() -2].x;
	y1 = A[A.N_Pontos() -2].y;
	if(custo != -1 && custo != 1)
		textprintf_ex( img , font, (x1 + x2)/2 + 8 , (y1 + y2)/2 , 0x000000, -1, "%d", custo);

	float theta = Calcula_Angulo( x1 , y1 , x2 , y2);
	int tx1,tx2,tx3,ty1,ty2,ty3;

	tx1 = x2;
	ty1 = y2;
	tx2 = SETA_COMPRIMENTO * cos( theta + SETA_ABERTURA ) + tx1;
	ty2 = SETA_COMPRIMENTO * sin( theta + SETA_ABERTURA ) + ty1;
	tx3 = SETA_COMPRIMENTO * cos( theta - SETA_ABERTURA ) + tx1;
	ty3 = SETA_COMPRIMENTO * sin( theta - SETA_ABERTURA ) + ty1;	
	
	triangle(img, tx1 , ty1 , tx2 , ty2 , tx3 , ty3 , cor);
	// Contorno
	fastline(img , tx1, ty1 , tx2 , ty2 , 0x0); 
	fastline(img , tx2, ty2 , tx3 , ty3 , 0x0); 
	fastline(img , tx3, ty3 , tx1 , ty1 , 0x0);
}

void RedePetri_Desenho::Desenha_Seta(BITMAP *bmp, int x1 , int y1 , int x2, int y2 , int custo, int cor)
{
		line(bmp , x1 , y1, x2 , y2 , cor);
		if(custo != -1 && custo != 1)
			textprintf_ex( bmp , font, (x1 + x2)/2 + 8 , (y1 + y2)/2 , 0x000000, -1, "%d", custo);
	float theta = Calcula_Angulo( x1 , y1 , x2 , y2);
	int tx1,tx2,tx3,ty1,ty2,ty3;
	
	tx1 = x2;
	ty1 = y2;
	tx2 = SETA_COMPRIMENTO * cos( theta + SETA_ABERTURA ) + tx1;
	ty2 = SETA_COMPRIMENTO * sin( theta + SETA_ABERTURA ) + ty1;
	tx3 = SETA_COMPRIMENTO * cos( theta - SETA_ABERTURA ) + tx1;
	ty3 = SETA_COMPRIMENTO * sin( theta - SETA_ABERTURA ) + ty1;	
	
	triangle(bmp, tx1 , ty1 , tx2 , ty2 , tx3 , ty3 , cor);
	// Contorno
	fastline(bmp , tx1, ty1 , tx2 , ty2 , 0x0); 
	fastline(bmp , tx2, ty2 , tx3 , ty3 , 0x0); 
	fastline(bmp , tx3, ty3 , tx1 , ty1 , 0x0);
}

void RedePetri_Desenho::Desenha_Grade()
{
	int i;
	for (i = 1; i <= iMAX; i ++)
		vline(img , i * Ey , 0 , IMGW , 0x808080);

	for ( i = 1; i <= jMAX; i ++)
		hline(img , 0 , i * Ex , IMGH , 0x808080);
}

/*
void RedePetri_Desenho::Desenha_Enumeracao( vector < MatrizSI > &vM , vector< Enumeracao > &Enum)
{
	short gm = vM.size() + 3 ,
		  nv = vM.size() ,
		  posi[nv], posj[nv],
          de, i, j, a, ponto=0, t,
          px1 , py1 , px2 , py2;

	bool visitado[nv],
		 desenhado[nv],
	     Grade[gm][gm];

	float ex = VIEW_W /gm,
		  ey = VIEW_H /gm;

	queue<short> Fila;

	rectfill(screen , VIEW_X , VIEW_Y , VIEW_X +VIEW_W , VIEW_Y + VIEW_H , 0xffffff);

	for ( i = 0; i < nv; i ++)
	{
		visitado[i] = false;
		desenhado[i] = false;
		Fila.push(i);
		for ( j = 0; j < nv; j ++)
			Grade[i][j] = false;
	}

	Grade[gm/2][gm/2] = true;
	posi[0] = gm/2;
	posj[0] = gm/2;
	desenhado[0]= true;
	
	while(!Fila.empty())
	{
		a = Fila.front();
		visitado[a] = true;
		Fila.pop();
		
		if(!desenhado[a])
		{
			while(Grade[i][j])
			{ i = rand()%(gm-1); j = rand()%(gm-2);}
			posi[a] = i;        posj[a] = j;
			Grade[i][j] = true; desenhado[a] = true;
		}
		for ( i = 0; i < Enum[a].de.size(); i ++)
		{
			de = Enum[a].de[i];
			t = Enum[a].t[i];
			
			if(!desenhado[de])
			for (j = ponto++; ponto != j; ponto = (ponto+1)%8)
			{
				if(posi[a] + tp[ponto].y < gm && posj[a] + tp[ponto].x < gm)
				if(!Grade[posi[a] + tp[ponto].y][posj[a] + tp[ponto].x] )
				{
					posi[de] = posi[a] + tp[ponto].y;
					posj[de] = posj[a] + tp[ponto].x;
					Grade[posi[de]][posj[de]] = true;
					desenhado[de] = true;
					break;
				}
			}

			px2 = posj[a] *ex + VIEW_X; py2 = posi[a] *ey + VIEW_Y;
			px1 = posj[de]*ex + VIEW_X; py1 = posi[de]*ey + VIEW_Y;
			
			Calcula_CorteRetaCirc( px1, py1 , px2, py2 , 20 , px2 , py2);
			Desenha_Seta(screen , px1 , py1, px2 , py2 , -1 ,cor[de%N_CORES]);
		    textprintf_ex(screen, font, (px1 + px2)/2 + 8 , (py1 + py2)/2 ,
                           cor[de%N_CORES], -1, "t%d", t);

			if(!visitado[de])
				Fila.push(de);
		}
	}
	
	char Nome[20];
	for ( i = 0; i < nv; i ++)
	{
		Nome_Marcacao(vM[i] , Nome);
		px1 = posj[i] *ex + VIEW_X; py1 = posi[i] *ey + VIEW_Y;
		circlefill( screen , px1 , py1 , 20, 0xff4e4e);
		circle( screen , px1 , py1 , 20, 0x0);
		textout_ex(screen, font, Nome, px1 - 15, py1 - 4 , 0x0, -1); 

	}
}
*/




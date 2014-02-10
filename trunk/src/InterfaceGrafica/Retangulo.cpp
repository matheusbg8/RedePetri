#include "Retangulo.h"
#include "SegmentoBasico.h"

int Retangulo::retangulo_id =0;

void Retangulo::inicializaRetangulo()
{
    retangulo_mid = retangulo_id;
    m_tipoDesenho = TD_RETANGULO;
    retangulo_id++;
    setCorFundo(Cor::verde);
    setNome(QString("Retangulo %1").arg(retangulo_mid));
}

Retangulo::Retangulo(Container *pai):Desenho(pai)
{
    inicializaRetangulo();
    rPonto p(50, 50);
    defineRetangulo(p,30,10);
}

Retangulo::Retangulo(rPonto posicao, int largura, int altura, Container *pai):Desenho(pai)
{
    inicializaRetangulo();
    defineRetangulo(posicao,largura,altura);

}

Desenho *Retangulo::novaInstancia() const
{
    return copiaRetangulo();
}

Retangulo *Retangulo::copiaRetangulo() const
{
    Retangulo * r = new Retangulo();
    copiaMeusParametros(r);
    return r;
}

void Retangulo::defineRetangulo(rPonto p, int largura, int altura)
{
    defineDesenho(p , largura,altura);
}

rPonto Retangulo::posicaoLigacao(const rPonto &pInicialReta)
{
    // Se por acaso a reta estiver dentro do retangulo, não existe interseccao
    if(m_espaco.contemrPonto(pInicialReta)) return m_espaco.posicao();

    return SegmentoBasico(pInicialReta, m_espaco.centro()).intercecao(m_espaco);

    // Precisava copia tudo? Achei que fico mais legal pra calcula a intersceção
    int rtngl_x1 = m_espaco.x(), // Posicao X inferior esquerdo do retangulo
        rtngl_y1 = m_espaco.y(), // Posicao Y inferior esquerdo do retangulo
        rtngl_x2 = m_espaco.x() + m_espaco.largura(), // Posicao X superior direito do retangulo
        rtngl_y2 = m_espaco.y() + m_espaco.altura(), // Posicao Y superior direito do retangulo
        rt_x2 = pInicialReta.x(), // Xinicial da reta
        rt_y2 = pInicialReta.y(), // Yinicial da reta
        rt_x1 = (rtngl_x1 + rtngl_x2)/2, // XFinal da reta (centro do retangulo)
        rt_y1 = ( rtngl_y1 + rtngl_y2)/ 2, // YFinal da reta (centro do retangulo)
        rt_vx = rt_x2 - rt_x1, // Vetor X da reta
        rt_vy = rt_y2 - rt_y1, // Vetor Y da reta
        resp_x , resp_y;

    // Calcula interseccao com retas horizontais da borda do retangulo
    if(rt_y2 > rt_y1)
        resp_y = rtngl_y2;
    else
        resp_y = rtngl_y1;

    if(rt_vy != 0)        
        resp_x = rt_x1 + rt_vx* (resp_y - rt_y1)/ rt_vy;
    else resp_x = 999999; // infinito (divisao por zero!!)

    if(resp_x > rtngl_x2 || resp_x < rtngl_x1)
    {// Intersec. com retas erradas, calc. intersec. com retas verticais da borda do retang.
        if(rt_x2 > rt_x1)
            resp_x = rtngl_x2;
        else
            resp_x = rtngl_x1;

        resp_y = rt_y1 + rt_vy * (resp_x - rt_x1) / rt_vx;
    }
    return rPonto(resp_x, resp_y);

// Conversão entre float e int, por enquanto
// não esta dando problema, mas seria interessante que apenas int
// ou apenas float seja utilizado.
/** @todo - Redefinir a classe ponto de forma que diminua os truncamentos
 * de float para int
*/
}

void *Retangulo::getSuper()
{
    return this;
}


/*
void Retangulo::desenha()
{
    Desenho::desenha();
    rPonto p = globalP();
    int x = p.x() , y = p.y();

    glBegin(GL_POLYGON);
        glColor3f(corFundo.r(),corFundo.g(),corFundo.b());
        glVertex2i(x           , y          );
        glVertex2i(x           , y + dAltura);
        glVertex2i(x + dLargura, y + dAltura);
        glVertex2i(x + dLargura, y          );
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(corFundo.r(),corFundo.g(),corFundo.b());
        glVertex2i(x           , y          );
        glVertex2i(x           , y + dAltura);
        glVertex2i(x + dLargura, y + dAltura);
        glVertex2i(x + dLargura, y          );
        glVertex2i(x           , y          );
        glEnd();
}
*/

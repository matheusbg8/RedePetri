#include "Triangulo.h"
#include <QGLWidget>
#include <iostream>
using namespace std;
void Triangulo::inicializaTrinagulo(rPonto p1, rPonto p2, rPonto p3)
{
    setCorFundo(Cor::azul);
    setCorBorda(Cor::preto);
    m_tipoDesenho = TD_TRIANGULO;
    setNome(QString("Triangulo %1").arg(id()));
    defineTriangulo(p1,p2,p3);
    setVisivel(true);
}


Triangulo::Triangulo(Container *pai ):Desenho(pai),
    t(rPonto(0,0),rPonto(0,0),rPonto(0,0))
{
    rPonto p1(30 , 50), p2(50 , 10), p3(10 , 10);
    inicializaTrinagulo(p1,p2,p3);
}


Triangulo::Triangulo(rPonto p1, rPonto p2, rPonto p3, Container *pai ):Desenho(pai),
    t(rPonto(0,0),rPonto(0,0),rPonto(0,0))
{
    inicializaTrinagulo(p1,p2,p3);
}


Desenho *Triangulo::novaInstancia() const
{
    return novoTriangulo();
}

Triangulo *Triangulo::novoTriangulo() const
{
    Triangulo *t = new Triangulo(p1(),p2(),p3());
    copiaMeusParametros(t);
    return t;
}

/**
  Realiza chamadas de funções do OpenGL para desenha o triangulo,
  esse método so pode ser chamado se estiver no periodo de redesenho,
  para que os desenhos sejam redesenhados, chame o método DesenhoMestre::redesenha()
**/

void Triangulo::desenha()
{
//    Desenho::desenha();
    rPonto gl = minhaPosicaoGlobal();
    rPonto p1 = t.p1(), p2 = t.p2(), p3 = t.p3();

    int glx = gl.x(), gly = gl.y(),
        p1x = p1.x() + glx , p1y = p1.y() + gly,
        p2x = p2.x() + glx , p2y = p2.y() + gly,
        p3x = p3.x() + glx , p3y = p3.y() + gly;

    glBegin(GL_POLYGON);
        glColor3f(m_corFundo.r(),m_corFundo.g(),m_corFundo.b());
        glVertex2f(p1x, p1y);
        glVertex2f(p2x, p2y);
        glVertex2f(p3x, p3y);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(m_corBorda.r(),m_corBorda.g(),m_corBorda.b());
        glVertex2f(p1x, p1y);
        glVertex2f(p2x, p2y);
        glVertex2f(p3x, p3y);
        glVertex2f(p1x, p1y);
    glEnd();

}

void imprimerPonto(rPonto p)
{
    cout << "(" << p.x() << "  , " << p.y() << ")";
}

void Triangulo::defineTriangulo(rPonto p1, rPonto p2, rPonto p3)
{
    t.defineTriangulo(p1,p2,p3);
    RetanguloBasico r = t.retangulo();

    rPonto rPosicao = r.posicao();
 //    cout << "Definindo triangulo -> largura = " << r.largura() << " altura = " << r.altura() << endl;
    defineDesenho(rPosicao , r.largura() , r.altura());

    p1 = p1 - rPosicao;
    p2 = p2 - rPosicao;
    p3 = p3 - rPosicao;

    t.defineTriangulo(p1,p2,p3);

}

void Triangulo::rotaciona(double ang)
{
    rPonto p1 = t.p1(), p2 = t.p2(), p3 = t.p3();
    rPonto centro( (p1.x() + p2.x() + p3.x()) / 3, ( p1.y() + p2.y() + p3.y())/ 3);
    rPonto np1(p1), np2(p2), np3(p3);
    cout << "Rotacionando triangulo" << endl;


    rotacionarPonto(centro, &np1, ang);
    rotacionarPonto(centro, &np2, ang);
    rotacionarPonto(centro, &np3, ang);

    rPonto gp = minhaPosicaoGlobal();
    np1 = np1 + gp;
    np2 = np2 + gp;
    np3 = np3 + gp;

    defineTriangulo(np1, np2, np3);
}

/**
  Verifica se o ponto P esta dentro do triangulo,
  se sim retorna true, se não false
**/
bool Triangulo::contemrPonto(const rPonto &p)
{
    rPonto pMinhaRefrencia = converteMeuReferencial(p);
    if(t.contemrPonto(pMinhaRefrencia))
    {
        return true;
    }
    return false;
}

/**
  Retorna o centro do triangulo
**/
rPonto Triangulo::centro() const
{
    return converteReferencialPai(t.centro());
}

rPonto Triangulo::p1() const
{
    return posicaoLocal() + t.p1();
}

rPonto Triangulo::p2() const
{
    return posicaoLocal() + t.p2();
}

rPonto Triangulo::p3() const
{
    return posicaoLocal() + t.p3();
}

void *Triangulo::getSuper()
{
    return this;
}



#include "Segmento.h"

#include <iostream>
#include <QtOpenGL>
#include "TrianguloBasico.h"

using namespace std;


void Segmento::inicializaSegmento()
{
    m_tipoDesenho = TD_SEGMENTO;
    setNome(QString("Segmento %1").arg(id()));
    m_espesura = 3.0f;
    setCorFundo(Cor::vermelho);
    setCorBorda(Cor::preto);
}

Segmento::Segmento(rPonto p1 ,rPonto p2, Container *pai):Desenho(pai)
{
    inicializaSegmento();
    defineSegmento(p1, p2);
}

Segmento::~Segmento()
{
}

void Segmento::desenha()
{
//    Desenho::desenha();
    rPonto gp = minhaPosicaoGlobal();

    float glX = gp.x(), glY = gp.y(),
            p1x = m_p1.x() + glX , p1y = m_p1.y() + glY,
            p2x = m_p2.x() + glX , p2y = m_p2.y() + glY,
            p3x = m_p3.x() + glX , p3y = m_p3.y() + glY,
            p4x = m_p4.x() + glX , p4y = m_p4.y() + glY;

    glBegin(GL_POLYGON);
        glColor3f(m_corFundo.r(),m_corFundo.g(),m_corFundo.b());
        glVertex2f(p1x, p1y);
        glVertex2f(p2x, p2y);
        glVertex2f(p4x, p4y);
        glVertex2f(p3x, p3y);
    glEnd();

     glBegin(GL_LINE_STRIP);
        glColor3f(m_corBorda.r(),m_corBorda.g(),m_corBorda.b());
        glVertex2f(p1x, p1y);
        glVertex2f(p2x, p2y);
        glVertex2f(p4x, p4y);
        glVertex2f(p3x, p3y);
        glVertex2f(p1x, p1y);
    glEnd();
}

bool Segmento::contemrPonto(const rPonto &p) const
{
    if(!Desenho::contemrPonto(p))
        return false;

    rPonto pMRef = converteMeuReferencial(p);

    float base = m_espesura, // É a espesura do segmento
        altura = m_direcao.mod(),
        areaSegmento = base*altura; // pois segmento é um retangulo rotacionado

//    cout << "Area Segmento " << areaSegmento << endl;
    TrianguloBasico
            t1(pMRef,m_p1,m_p2),
            t2(pMRef,m_p2,m_p4),
            t3(pMRef,m_p4,m_p3),
            t4(pMRef,m_p3,m_p1);
    float areaTraianguloSeg = t1.area() + t2.area() + t3.area() + t4.area();

    if(produzLog)
        cout << "Area triangulos Segmento " << areaTraianguloSeg << endl;

    if(areaSegmento+5.0f >= areaTraianguloSeg)
    {
        return true;
    }
    return false;
}

void Segmento::setSegmento(rPonto p1, rPonto p2)
{
    defineSegmento(p1, p2);
}

void Segmento::defineSegmento(rPonto p1, rPonto p2)
{
    if(p1 == p2)
    {
        cout << "Segmento:: Erro, definicao de segmento invalida!!!" << endl;
        return;
    }
    m_direcao = p2 - p1; // Pega direção do segmento

    // Pega vetores ortogonais ao vetor de direcao e econtra 2 primeiros pontos to segmento
    m_p1 = p1 + m_direcao.ortoAntiHorario().uni() * (m_espesura/2.f);
    m_p2 = p1 + m_direcao.ortoHorario().uni() * (m_espesura/2.f);

    // Encontra 2 ultimos pontos que forma o segmento
    m_p3 = m_p1 + m_direcao;
    m_p4 = m_p2 + m_direcao;

    int vx[4] = {m_p1.x() , m_p2.x() , m_p3.x() , m_p4.x() },
        vy[4] = {m_p1.y() , m_p2.y() , m_p3.y() , m_p4.y() },
        mx = vx[0], Mx = vx[0], my =vy[0] , My = vy[0] , i;

    // Encontra menor x menor y maior x e maior y dos pontos que forma o segmento
    for(i = 1; i < 4 ; i++)
    {
        if(Mx < vx[i])
            Mx = vx[i];

        if(mx > vx[i])
            mx = vx[i];

        if(My < vy[i])
            My = vy[i];

        if(my > vy[i])
            my = vy[i];
    }
    rPonto posicao(mx,my);
//    cout << "Segmento posicoa = " << posicao << endl;
    defineDesenho(posicao, Mx - mx, My - my);

    m_p1 -= posicao;
    m_p2 -= posicao;
    m_p3 -= posicao;
    m_p4 -= posicao;

}

void Segmento::setEspesura(float espesura)
{
    m_espesura = espesura;
}


bool Segmento::mouseMovendo(MouseEvento *e)
{
    Desenho::mouseMovendo(e);
}

bool Segmento::mousePrecionado(MouseEvento *novoMouseEvento)
{
    Desenho::mousePrecionado(novoMouseEvento);
}

void *Segmento::getSuper()
{
    return this;
}


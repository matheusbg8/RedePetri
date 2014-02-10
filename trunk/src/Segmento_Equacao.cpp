#include "Segmento.h"

#include <iostream>
#include <QtOpenGL>

using namespace std;


void Segmento::inicializaSegmento()
{
    setNome(QString("Segmento %1").arg(id()));
    largura = 5;
    altura = 5;
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
    int glX = gp.x(), glY = gp.y(),
            p1x = segSuperior.getP1().x() + glX , p1y = segSuperior.getP1().y() + glY,
            p2x = segSuperior.getP2().x() + glX , p2y = segSuperior.getP2().y() + glY,
            p3x = segInferior.getP1().x() + glX , p3y = segInferior.getP1().y() + glY,
            p4x = segInferior.getP2().x() + glX , p4y = segInferior.getP2().y() + glY;

    glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,0.0);
        glVertex2i(p1x, p1y);
        glVertex2i(p2x, p2y);
        glVertex2i(p4x, p4y);
        glVertex2i(p3x, p3y);
    glEnd();

     glBegin(GL_LINE_STRIP);
        glColor3f(0.0,0.0,0.0);
        glVertex2i(p1x, p1y);
        glVertex2i(p2x, p2y);
        glVertex2i(p4x, p4y);
        glVertex2i(p3x, p3y);
        glVertex2i(p1x, p1y);
    glEnd();
}

bool Segmento::contemrPonto(rPonto p)
{
    p = converteMeuReferencial(p);
    if(segInferior.dentroDoRetangulo(p))
    {
//        SegmentoBasico::imprimePRelativo(segInferior.posicaoRelativarPonto(p));
//        SegmentoBasico::imprimePRelativo(segSuperior.posicaoRelativarPonto(p));
        if(segInferior.posicaoRelativarPonto(p) != segSuperior.posicaoRelativarPonto(p))
        {
            return true;
        }
        return false;
//        return true;
    }
    return false;
}

void Segmento::setSegmento(rPonto p1, rPonto p2)
{
    defineSegmento(p1, p2);
}

void Segmento::defineSegmento(rPonto p1, rPonto p2)
{
    segSuperior.setSegmento(p1,p2);

    defineDesenho(segSuperior.getPosicaoRetangulo(), segSuperior.getLarguraRetangulo(),segSuperior.getAlturaRetangulo());
    p1.setX(0); p1.setY(0);
    p2 = p2 - m_posicaoDesenho;

    SegmentoBasico::EM_FUNCAO_DE func = segSuperior.getEmFuncaoDe();
    if(func == SegmentoBasico::EM_FUNCAO_DE_X)
    {
        segInferior.setSegmento(rPonto(p1.x() - 3, p1.y()) , rPonto(p2.x() - 3, p2.y()));
        segSuperior.setSegmento(rPonto(p1.x() + 3, p1.y()) , rPonto(p2.x() + 3, p2.y()));
    }else if(func == SegmentoBasico::EM_FUNCAO_DE_Y)
    {
        segInferior.setSegmento(rPonto(p1.x(), p1.y() - 1) , rPonto(p2.x(), p2.y() - 1));
        segSuperior.setSegmento(rPonto(p1.x(), p1.y() + 1) , rPonto(p2.x(), p2.y() + 1));
    }
}

Desenho * Segmento::mousePrecionado(MouseEvento *e, bool *algumaReacao)
{
//    defineSegmento();
}


void Segmento::mouseMovendo(MouseEvento *e)
{
    Desenho::mouseMovendo(e);
}


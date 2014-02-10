#include "TrianguloBasico.h"
#include "RetanguloBasico.h"
#include "Utilidades.h"
#include "math.h"

#include <iostream>

using namespace std;

TrianguloBasico::TrianguloBasico(rPonto p1, rPonto p2, rPonto p3)
{
    defineTriangulo(p1,p2,p3);
}

/**
    Define as dimensões de um Triangulo a partir de 3 pontos

    Complexidade: O(1) -> 3 raiz quadrdada
**/
void TrianguloBasico::defineTriangulo(rPonto p1, rPonto p2, rPonto p3)
{
    int p1x = p1.x() , p1y = p1.y(),
        p2x = p2.x() , p2y = p2.y(),
        p3x = p3.x() , p3y = p3.y();

    minX = p1x;
    minY = p1y;
    maxX = minX;
    maxY = minY;

    if( maxY < p2y)
        maxY = p2y;

    if( maxY < p3y)
        maxY = p3y;

    if( minX > p2x)
        minX = p2x;

    if( minX > p3x)
        minX = p3x;

    if( maxX < p2x)
        maxX = p2x;

    if( maxX < p3x)
        maxX = p3x;

    if( minY > p2y)
        minY = p2y;

    if( minY > p3y)
        minY = p3y;

// Calculo de area pelo perimetro médio

    float ladoA = Utilidades::calculaDistancia(p1,p2),
          ladoB = Utilidades::calculaDistancia(p2,p3),
          ladoC = Utilidades::calculaDistancia(p3,p1);
    mPerimetro =  ladoA + ladoB + ladoC;

    // Fórmula do perimetro médio de Heron de Alexandria
//    float semiPerimetro = mPerimetro/2;
//    // Area quadrada
//    mArea = semiPerimetro * ( semiPerimetro - ladoA) *
//            (semiPerimetro - ladoB) *
//            (semiPerimetro - ladoC);

// Calculo de area pelo determinante medio
    mArea = (p1.x()*p2.y() + p1.y()*p3.x() + p2.x()*p3.y() - p2.y()*p3.x() - p3.y()*p1.x() - p1.y()*p2.x())/ 2.f;
    if(mArea < 0) mArea = -mArea;

    this->mP1 = p1;
    this->mP2 = p2;
    this->mP3 = p3;

}

/**
  Recebe um ponto e retorna true se ele estiver dentro do triangulo.
**/
bool TrianguloBasico::contemrPonto(const rPonto &p) const
{
/*
    /\
   /  \
  / .  \
 /______\

*/
    if(retangulo().contemrPonto(p))
    {
        TrianguloBasico A(mP1,mP2,p), B(mP1,mP3,p), C(mP2,mP3,p);

        if(Utilidades::igual(area(), A.area() + B.area() + C.area()))
        {
            return true;
        }
    }
    return false;
}

/**
  Retorna a area do Triângulo
**/
float TrianguloBasico::area() const
{
    // Pelo perimetro medio
//    return sqrt(mArea);
    // Pelo determinante medio
    return mArea;
}

/**
  Retorna a area quadrada do Triângulo
**/
float TrianguloBasico::areaQuadrada() const
{
    // Pelo perimetro medio
//    return mArea;
    // Pelo determinante medio
    return mArea * mArea;
}

/**
  Retorna o perimetro do Triângulo
**/
float TrianguloBasico::perimetro() const
{
    return mPerimetro;
}

/**
  Retorna o retangulo cuja o triangula esta inscrito
**/
RetanguloBasico TrianguloBasico::retangulo() const
{
    return RetanguloBasico(rPonto(minX,minY) ,maxX -minX, maxY - minY);
}

/**
  Retorna o ponto 1 que forma o triangulo
**/
rPonto TrianguloBasico::p1() const
{
    return mP1;
}

/**
  Retorna o ponto 2 que forma o triangulo
**/
rPonto TrianguloBasico::p2() const
{
    return mP2;
}

/**
  Retorna o ponto 3 que forma o triangulo
**/
rPonto TrianguloBasico::p3() const
{
    return mP3;
}

rPonto TrianguloBasico::centro() const
{
    rPonto psoma = mP1+mP2+mP3;
    return rPonto( psoma.x()/3.0 , psoma.y() / 3.0);
}

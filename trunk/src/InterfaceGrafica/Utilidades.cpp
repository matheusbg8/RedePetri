#include "Utilidades.h"
#include <cmath>

Utilidades::Utilidades()
{
}

float Utilidades::calculaAngulo(rPonto centro, rPonto p)
{
    int x1 = centro.x() , y1 = centro.y(),
        x2 = p.x()      , y2 = p.y();

    if( x1 == x2) x2++;

    float
    vx = x1 - x2,
    vy = y1 - y2,

    rho = sqrt(vx *vx + vy*vy),
    senoTheta = vy / rho,
    cossenoTheta = vx / rho,
    theta = acos(abs(cossenoTheta)),
    PI = 3.141592654;

    if ( cossenoTheta < 0 && senoTheta >=0 ) // 2º quadrante
        theta = PI - theta;
    else if ( cossenoTheta < 0 && senoTheta < 0 ) // 3º quadrante
        theta += PI;
    else if( cossenoTheta >= 0 && senoTheta < 0) // 4º quadrante
        theta = 2.0 * PI - theta;

    // senao 1Âº quadrante (nam precisa fazer nada)

    return theta;
}

float Utilidades::abs(float val)
{
    if(val < 0)
    {
        return -val;
    }
    return val;
}

float Utilidades::calculaDistancia(rPonto p1, rPonto p2)
{
    return sqrt( distanciaQuadrada(p1,p2) );
}

float Utilidades::distanciaQuadrada(rPonto p1, rPonto p2)
{
    float p1x = p1.x() , p1y = p1.y(),
          p2x = p2.x() , p2y = p2.y(),
          dx = p1x - p2x,
          dy = p1y - p2y;

    return dx*dx + dy*dy;
}

bool Utilidades::igual(float numA, float numB, float prec)
{
    if( abs(numA - numB) <= prec)
    {
        return true;
    }
    return false;
}

int Utilidades::mod(int num)
{
    if(num<0)
        return -num;
    return num;
}

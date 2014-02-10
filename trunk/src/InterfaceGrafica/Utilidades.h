#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Ponto.h"
typedef Ponto<float> rPonto;

class Utilidades
{
public:
    Utilidades();
    static float calculaAngulo(rPonto centro, rPonto p);
    static float abs(float val);
    static float calculaDistancia(rPonto p1, rPonto p2);
    static float distanciaQuadrada(rPonto p1, rPonto p2);
    static bool igual(float numA, float numB, float prec = 1e-3);
    static int mod(int num);
};

#endif // UTILIDADES_H

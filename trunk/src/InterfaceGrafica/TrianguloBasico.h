#ifndef TRIANGULOBASICO_H
#define TRIANGULOBASICO_H

#include "RetanguloBasico.h"

class TrianguloBasico
{
private:
    float mArea; // Area Qudrada
    float mPerimetro;
    float minX, maxX , minY, maxY;
    rPonto mP1;
    rPonto mP2;
    rPonto mP3;

public:
    TrianguloBasico(rPonto p1, rPonto p2, rPonto p3);
    void defineTriangulo(rPonto p1, rPonto p2, rPonto p3);
    bool contemrPonto(const rPonto &p) const;
    float area() const;
    float areaQuadrada() const;
    float perimetro() const;
    RetanguloBasico retangulo() const;
    rPonto p1() const;
    rPonto p2() const;
    rPonto p3() const;
    rPonto centro() const;

};

#endif // TRIANGULOBASICO_H

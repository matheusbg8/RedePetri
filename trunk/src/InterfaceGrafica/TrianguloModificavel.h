#ifndef TRIANGULOMODIFICAVEL_H
#define TRIANGULOMODIFICAVEL_H

#include "DesenhoComposto.h"
#include "Triangulo.h"
#include "CirculoBasico.h"

class TrianguloModificavel : public DesenhoComposto
{
private:
    Triangulo *t;
    Circulo *c1;
    Circulo *c2;
    Circulo *c3;
    short circuloClicado;
    void inicializaTrianguloModificavel(rPonto p1, rPonto p2 , rPonto p3);
public:
    TrianguloModificavel(rPonto p1= rPonto(10,10), rPonto p2 = rPonto(30,30), rPonto p3 = rPonto(50,10), Container *m_pai = 0x0);
    TrianguloModificavel(Container *m_pai);
    void mousePrecionadoComposto(Desenho *d, MouseEvento *e);
    bool mouseMovendo(MouseEvento *e);
};

#endif // TRIANGULOMODIFICAVEL_H

#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "TrianguloBasico.h"
#include "Desenho.h"

class Triangulo : public Desenho
{
private:
    TrianguloBasico t;
    void inicializaTrinagulo(rPonto p1, rPonto p2, rPonto p3);
public:
    Triangulo(rPonto p1 , rPonto p2 , rPonto p3 , Container *m_pai = 0x0);
    Triangulo(Container *m_pai = 0x0);

    Desenho *novaInstancia() const;

    Triangulo *novoTriangulo() const;


    bool contemrPonto(const rPonto& p);
    void defineTriangulo(rPonto p1 , rPonto p2 , rPonto p3);
    void rotaciona(double ang);
    void desenha();

    rPonto centro() const;
    rPonto p1() const;
    rPonto p2() const;
    rPonto p3() const;

    void* getSuper();
};

#endif // TRIANGULO_H

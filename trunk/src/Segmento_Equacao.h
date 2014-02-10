#ifndef SEGMENTO_H
#define SEGMENTO_H

#include "Desenho.h"
#include "SegmentoBasico.h"

class Segmento : public Desenho
{
    SegmentoBasico segSuperior;
    SegmentoBasico segInferior;

    rPonto p1;
    rPonto p2;
    rPonto *refP1;
    rPonto *refP2;

    float vx , vy;
    float m ,n;
    int mx, my;  // menor x , menor y
    int Mx, My;  // maior x , maior y
    int largura;
    int altura;
    bool maisHorizontal; // Define se o segmento é mais vertical(false) ou mais horizontal (true)

    void inicializaSegmento();

public:
    Segmento(rPonto p1 = rPonto(10,10) , rPonto p2 = rPonto(50,80), Container *m_pai = 0x0);
    ~Segmento();
    void desenha();
    bool contemrPonto(rPonto p);
    void setSegmento(rPonto p1, rPonto p2);
    void defineSegmento(rPonto p1 , rPonto p2);
    Desenho *mousePrecionado(MouseEvento *e, bool *algumaReacao);
    void mouseMovendo(MouseEvento *e);

};

#endif // SEGMENTO_H

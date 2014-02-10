#ifndef SEGMENTO_H
#define SEGMENTO_H

#include "Desenho.h"
#include "SegmentoBasico.h"

class Segmento : public Desenho
{
    rPonto m_p1;
    rPonto m_p2;

    rPonto m_p3;
    rPonto m_p4;

    rPonto m_direcao;
    rPonto m_posicao;

    float m_espesura;

    void inicializaSegmento();

public:
    Segmento(rPonto p1 = rPonto(10,10) , rPonto p2 = rPonto(50,80), Container *m_pai = 0x0);
    ~Segmento();
    void desenha();
    bool contemrPonto(const rPonto &p) const;
    void setSegmento(rPonto p1, rPonto p2);
    void defineSegmento(rPonto p1 , rPonto p2);

    void setEspesura(float espesura);

    bool mouseMovendo(MouseEvento *e);
    bool mousePrecionado(MouseEvento *novoMouseEvento);

    void *getSuper();

};

#endif // SEGMENTO_H

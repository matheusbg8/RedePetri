#ifndef SEGMENTOAJUSTAVEL_H
#define SEGMENTOAJUSTAVEL_H

#include "DesenhoComposto.h"
#include "Segmento.h"
#include "CirculoBasico.h"

class SegmentoAjustavel : public DesenhoComposto
{
protected:
    Segmento *m_segmento;
    Circulo *m_inicio;
    Circulo *m_fim;

    Desenho *m_ligaA;
    Desenho *m_ligaB;

public:
    SegmentoAjustavel();

    void defineSegmento(const rPonto &inicio, const rPonto &fim, int espesura = 4);
    void mousePrecionadoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);
    void mouseMovendoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);
    void mouseSoltoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);

    void ligaA(Desenho *d);
    void ligaB(Desenho *d);

    void eventoAlteracaoPosicao(Desenho *desenho, rPonto novaPosicao);

    virtual void* getSuper();
};

#endif // SEGMENTOAJUSTAVEL_H

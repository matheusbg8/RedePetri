#ifndef POLIGONO_H
#define POLIGONO_H
#include <list>
#include "DesenhoComposto.h"
#include "Segmento.h"
#include "Retangulo.h"

class Poligono : public DesenhoComposto
{
protected:
    Retangulo *ret1;
    Retangulo *ret2;

    list <Segmento*> Segmentos;
public:
    Poligono(Container *m_pai);
    void mousePrecionadoComposto(Desenho *d, MouseEvento *e);
    void mouseMovendoComposto(Desenho *d, MouseEvento *e);
    void mousesoltoComposto(Desenho *d, MouseEvento *e);

    void * getSuper();
};

#endif // POLIGONO_H

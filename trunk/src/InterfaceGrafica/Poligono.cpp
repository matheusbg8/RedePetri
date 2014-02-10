#include "Poligono.h"
#include "iostream"
using namespace std;

Poligono::Poligono(Container *pai):DesenhoComposto(pai)
{
    ret1 = new Retangulo(rPonto(10,10),10 ,10);
    ret2 = new Retangulo(rPonto(50,50),10,10);
    novaComposicao(ret1);
    novaComposicao(ret2);

    m_tipoDesenho = TD_POLIGONO;
}

void Poligono::mousePrecionadoComposto(Desenho *d, MouseEvento *e)
{
    if(d == ret1)
    {
        cout << "Clicado no retangulo 1" << endl;
        mousePrecionado(e);
    }
    else
    {
        cout << "Clicado no retangulo 2" << endl;
        mousePrecionado(e);
    }
}

void Poligono::mouseMovendoComposto(Desenho *d, MouseEvento *e)
{
    mouseMovendo(e);
}

void Poligono::mousesoltoComposto(Desenho *d, MouseEvento *e)
{
    mouseSolto(e);
}

void *Poligono::getSuper()
{
    return this;
}

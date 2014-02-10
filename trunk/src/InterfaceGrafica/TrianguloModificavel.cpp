#include "TrianguloModificavel.h"
#include <iostream>
using namespace std;

void TrianguloModificavel::inicializaTrianguloModificavel(rPonto p1, rPonto p2 , rPonto p3)
{
    m_tipoDesenho = TD_TRIANGULO;
    t = new Triangulo(p1,p2,p3);
    novaComposicao(t);

    c1 = new Circulo(3, t->p1());
    novaComposicao(c1);

    c2 = new Circulo(3, t->p2());
    novaComposicao(c2);

    c3 = new Circulo(3,t->p3());
    novaComposicao(c3);

    circuloClicado = 0;
}

TrianguloModificavel::TrianguloModificavel(rPonto p1, rPonto p2, rPonto p3, Container *pai):
    DesenhoComposto(pai)
{
    inicializaTrianguloModificavel(p1,p2,p3);
}
TrianguloModificavel::TrianguloModificavel(Container *pai):
    DesenhoComposto(pai)
{
    inicializaTrianguloModificavel(rPonto(10,10), rPonto(30,30), rPonto(50,10));
}

void TrianguloModificavel::mousePrecionadoComposto(Desenho *d, MouseEvento *e)
{
    if(d == c1)
    {
        cout << "Clicado no circulo 1" << endl;
        setEscutaMouseMovendo(true);
        setEscutaMouseSolto(true);
        circuloClicado =1;
    }else if( d == c2)
    {
        cout << "Clicado no circulo 2" << endl;
        setEscutaMouseMovendo(true);
        setEscutaMouseSolto(true);
        circuloClicado =2;
    }else if (d == c3)
    {
        cout << "Clicado no circulo 3" << endl;
        setEscutaMouseMovendo(true);
        setEscutaMouseSolto(true);
        circuloClicado =3;
    }else
    {
        cout << "Clicado no triangulo" << endl;
        circuloClicado = 0; // Clicado no Triangulo
        mousePrecionado(e);
    }
}

bool TrianguloModificavel::mouseMovendo(MouseEvento *e)
{
    rPonto meuReferencial = converteMeuReferencial(e->posicaoLocal());
    cout << "------- Triangulo::mouseMovendo!"<< endl;
    switch(circuloClicado)
    {
    case 0:
        cout << "-----Movendo no triangulo" << endl;
        Container::mouseMovendo(e);
    break;
    case 1:
        c1->setPosicaoLocal(meuReferencial);
        t->defineTriangulo(meuReferencial,c2->getCentro(), c3->getCentro());
//        t->setPosicao(meuReferencial);
        cout << "-----Movendo no circulo 1" << endl;
    break;
    case 2:
        cout << "-----Movendo no circulo 2" << endl;
    break;
    case 3:
        cout << "-----Movendo no circulo 3" << endl;
    break;
    }
}


#include "meuobjeto.h"
#include <cmath>

MeuObjeto::MeuObjeto(int raio, rPonto p)
{
    this->raio = raio;
    posicao = p;
}

void MeuObjeto::desenha()
{
    float px= posicao.x(),py = posicao.y(),
            x , y;

    glBegin(GL_POLYGON);
        glColor3f(0,0,1);
        for (int i = 1; i <= 100; i+=5)
        {
            x = px + raio*sin(2*3.1415927 * i/100.0);
            y = py + raio*cos(2*3.1415927 * i/100.0);
            glVertex2f(x, y);
        }
    glEnd();
}

void MeuObjeto::setPosicao(rPonto p)
{
    posicao = p;
}


bool MeuObjeto::contemrPonto(rPonto p)
{
    float mx = posicao.x() , my = posicao.y(),
            x = p.x() , y = p.y();
    if( x*x + y*y < mx*mx + my*my)
        return true;
    return false;
}

void MeuObjeto::cliqueEvento(rPonto p)
{
    return;
}

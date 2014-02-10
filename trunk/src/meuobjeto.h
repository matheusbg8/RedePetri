#ifndef MEUOBJETO_H
#define MEUOBJETO_H

#include <QGLWidget>

#include "Desenho.h"


class MeuObjeto
{
private:
    float raio;
    rPonto posicao;
public:
    MeuObjeto(int raio, rPonto p);
    void desenha();
    void setPosicao(rPonto p);
    bool contemrPonto(rPonto p);
    void cliqueEvento(rPonto p);


};

#endif // MEUOBJETO_H

#ifndef MCIRCULO_H
#define MCIRCULO_H

#include <QGLWidget>

#include "Desenho.h"

class Circulo : public Desenho
{
private:
    float m_raio;
    void inicializaCirculo();
public:
    Circulo(Container *m_pai = 0x0);
    Circulo(int raio, rPonto p, Container *m_pai = 0x0);
    virtual ~Circulo();


    /* Interface Desenho */
    Desenho *novaInstancia() const;

    Circulo *copiaCirculo() const;


//    void novoDesenho(Desenho *d);
    void desenha();
    bool contemrPonto(const rPonto &p);
    bool mousePrecionado(MouseEvento *e);
    bool mouseMovendo(MouseEvento *e);
    void defineCirculo(int raio ,const rPonto& p);

    void setCentro(const rPonto &posicao);
    rPonto getCentro();
    void *getSuper();

    float raio();

    virtual rPonto posicaoLigacao(const rPonto &pInicialReta);
};

#endif // MCIRCULO_H

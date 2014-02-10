#ifndef RETANGULO_H
#define RETANGULO_H

#include <QGLWidget>

#include"Desenho.h"

class Retangulo : public Desenho
{
private:
    void inicializaRetangulo();
    static int retangulo_id;
    int retangulo_mid;

public:
    Retangulo(Container *m_pai = 0x0);
    Retangulo(rPonto posicao, int largura, int altura, Container *m_pai = 0x0);
    virtual ~Retangulo(){};

    Desenho* novaInstancia() const;

    Retangulo *copiaRetangulo() const;

    void defineRetangulo(rPonto p, int largura, int altura);
//    void desenha();

    virtual rPonto posicaoLigacao(const rPonto &pInicialReta);

    void * getSuper();
};

#endif // RETANGULO_H

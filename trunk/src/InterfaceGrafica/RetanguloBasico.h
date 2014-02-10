#ifndef RETANGULOBASICO_H
#define RETANGULOBASICO_H

#include "Utilidades.h"


/**
 * @brief
 *  Esta classe representa um retangulo, possui uma largura,
 * uma altura e uma posição X Y no plano.
 */
class RetanguloBasico
{
    float m_largura;
    float m_altura;
    rPonto m_posicao;
public:

    RetanguloBasico(rPonto posicao = rPonto(), float largura = 0.0f, float altura = 0.0f);
    RetanguloBasico(rPonto p1, rPonto p2);

    void defineRetangulo(rPonto posicao, float largura, float altura);
    void defineRetangulo(rPonto p1, rPonto p2);

    void setX(float x);
    void setY(float y);

    void setPosicao(const rPonto &novaPosicao);
    void setAltura(int novaAltura);
    void setLargura(int novaLargura);

    float area()const ;
    float areaQuadrada() const;
    float perimetro() const;
    bool contemrPonto(const rPonto &p) const;

    float x() const;
    float y() const;

    void ajusta(const rPonto& ponto);

    const rPonto& posicao() const;
    float largura() const;
    float altura() const;
    const rPonto& p1() const;
    rPonto p2() const;

    rPonto pontoInferiorDireito() const;
    rPonto pontoInferiorEsquerdo() const;
    rPonto pontoSuperiorDireito() const;
    rPonto pontoSuperiorEsquerdo() const;

    rPonto centro() const;

};

#endif // RETANGULOBASICO_H

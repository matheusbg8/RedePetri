#include "RetanguloBasico.h"

RetanguloBasico::RetanguloBasico(rPonto posicao, float largura, float altura)
{
    defineRetangulo(posicao , largura, altura);
}
RetanguloBasico::RetanguloBasico(rPonto p1, rPonto p2)
{
    defineRetangulo(p1,p2);
}

/**
    Define o retangulo a partir de uma posição (canto inferior esquerdo),
    uma largura e uma altura
 **/
void RetanguloBasico::defineRetangulo(rPonto posicao, float largura, float altura)
{
    this->m_posicao = posicao;
    this->m_altura = altura;
    this->m_largura = largura;
}

void RetanguloBasico::defineRetangulo(rPonto p1, rPonto p2)
{
    int p1x = p1.x() , p1y = p1.y(),
        p2x = p2.x() , p2y = p2.y();
    int minX, minY, maxX, maxY;

    if(p1x > p2x)
    {
        maxX = p1x;
        minX = p2x;
    }else
    {
        maxX = p2x;
        minX = p1x;
    }

    if(p1y > p2y)
    {
        maxY = p1y;
        minY = p2y;
    }else
    {
        maxY = p2y;
        minY = p1y;
    }
    defineRetangulo(rPonto(minX,minY),maxX - minX, maxY - minY);
}

void RetanguloBasico::setX(float x)
{
    m_posicao.setX(x);
}

void RetanguloBasico::setY(float y)
{
    m_posicao.setY(y);
}

void RetanguloBasico::setPosicao(const rPonto &novaPosicao)
{
    m_posicao = novaPosicao;
}

void RetanguloBasico::setAltura(int novaAltura)
{
    m_altura = novaAltura;
}

void RetanguloBasico::setLargura(int novaLargura)
{
    m_largura = novaLargura;
}

/**
    Calcula a area do retangulo
 **/
float RetanguloBasico::area() const
{
    return m_largura * m_altura;
}

/**
    Realiza chamada de area() e eleva ao quadrado
 **/
// Pra que q eu uso a area quadrada mesmo?
float RetanguloBasico::areaQuadrada() const
{
    float marea = area();
    return marea*marea;
}

/**
    Calcula o perimetro do retangulo
 **/
float RetanguloBasico::perimetro() const
{
    return 2*m_altura + 2*m_largura;
}

/**
  Verifica se o ponto esta dentro do retangulo,
  retorna true se o ponto estiver dentro,
  false se estiver fora
 **/
bool RetanguloBasico::contemrPonto(const rPonto& p) const
{
    float p1x = m_posicao.x(), p1y = m_posicao.y(),
          p2x = p1x + m_largura, p2y = p1y + m_altura,
          px = p.x() , py = p.y();

    if(px >= p1x && px <= p2x &&
       py >= p1y && py <= p2y)
    {
        return true;
    }
    return false;
}

float RetanguloBasico::x() const
{
    return m_posicao.x();
}

float RetanguloBasico::y() const
{
    return m_posicao.y();
}


/**
 * @brief
 *  Ajusta a largura e o comprimento do retangulo para conter o ponto
 * @param ponto
 */
void RetanguloBasico::ajusta(const rPonto &ponto)
{    
    if(ponto.x() < m_posicao.x())
    {
        m_posicao.setX(ponto.x());
    }else if( ponto.x() > m_posicao.x() + m_largura)
    {
        m_largura += ponto.x() - m_posicao.x();
    }

    if(ponto.y() < m_posicao.y())
    {
        m_posicao.setY(ponto.y());
    }else if( ponto.y() > m_posicao.y() + m_altura)
    {
        m_largura += ponto.y() - m_posicao.y();
    }
}

/**
  Retorna a posicao do retangulo
**/
const rPonto &RetanguloBasico::posicao() const
{
    return m_posicao;
}

/**
  Retorna a largura do retangulo
**/
float RetanguloBasico::largura() const
{
    return m_largura;
}

/**
  Retorna a altura do retangulo
**/
float RetanguloBasico::altura() const
{
    return m_altura;
}

const rPonto &RetanguloBasico::p1() const
{
    return posicao();
}

rPonto RetanguloBasico::p2() const
{
    rPonto p = posicao() + rPonto(largura(), altura());
    return p;
}

rPonto RetanguloBasico::pontoInferiorDireito() const
{
    return posicao() + rPonto(largura() , 0);
}

rPonto RetanguloBasico::pontoInferiorEsquerdo() const
{
    return posicao();
}

rPonto RetanguloBasico::pontoSuperiorDireito() const
{
    return posicao() + rPonto(largura() , altura());
}

rPonto RetanguloBasico::pontoSuperiorEsquerdo() const
{
    return posicao() + rPonto(0 , altura());
}

rPonto RetanguloBasico::centro() const
{
    return m_posicao + rPonto( m_largura/2, m_altura/2);
}

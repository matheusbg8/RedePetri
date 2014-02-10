#include "SegmentoBasico.h"

#include <iostream>
#include <QtOpenGL>

using namespace std;

float absoluto(float v)
{
    if(v < 0)
    {
        return -v;
    }
    return v;
}

void SegmentoBasico::inicializaSegmento()
{
    emFuncaoDe = EM_FUNCAO_INDEFINIDO;
}

SegmentoBasico::SegmentoBasico(rPonto p1 , rPonto p2)
{
    inicializaSegmento();
    defineSegmento(p1, p2);
}

/**
     Verifica em que posicao o ponto esta em relacao ao segmento,
    ele pode estar:

        * Acima da reta - PONTO_SUPERIOR
        * Abaixo da reta -PONTO_INFERIOR
        * Na reta -       PONTO_CONTIDO

      [Colocar desenho de conveções utilizadaz para SUPERIOR e INFERIOR]
**/

SegmentoBasico::POSICAO_RELATIVA_PONTO SegmentoBasico::posicaoRelativarPonto(rPonto p)
{
    int px = p.x(), py = p.y();
    float espVal;

    switch(emFuncaoDe)
    {
    case EM_FUNCAO_DE_X:
        // x = m * y + n
        espVal = m * py + n;
 //       cout << "espVal " << espVal << " px " << px << endl;
 //       cout << "m = " << m << endl;
        if(espVal == px)
        {
            return PONTO_CONTIDO;
        }else if( px > espVal)
        {
            return PONTO_SUPERIOR;
        }else
            return PONTO_INFERIOR;
    break;
    case EM_FUNCAO_DE_Y:
        // y = m*x + n
        espVal = m * px + n;
  //      cout << "espVal " << espVal << " py " << py << endl;
        if(espVal == py)
        {
            return PONTO_CONTIDO;
        }else if( py > espVal)
        {
            return PONTO_SUPERIOR;
        }else
            return PONTO_INFERIOR;
    break;
    case EM_FUNCAO_INDEFINIDO:
        cout << "SegmentoBasico::posicaoRelativarPonto - Erro, segmento não definido" << endl;
        return PONTO_INDEFINIDO;
    break;
    default:
        return PONTO_INDEFINIDO;
    break;
    }
    return PONTO_INDEFINIDO;
}

/**
    Verifica se um ponto pertence ao segmento
**/
bool SegmentoBasico::contemrPonto(rPonto p)
{
    /* Equacao reduzida da reta
        x = ( vx/vy ) * y + (x1 - vx/vy * y1 )
        m = vx / vy
        n = x1 - vx/vy * y1
        x = m *y + n
   */
    if(dentroDoRetangulo(p))
    {
        int px = p.x(), py = p.y();

        switch(emFuncaoDe)
        {
        case EM_FUNCAO_DE_X:
            // x = m * y + n
            cout << "vx " << vx << " vy " << vy << endl;
            cout << "mx " << m << " nx " << n << endl;
            if(m * py + n == px) // como resolver a precisao da igualdade? Precisa?
            {
                return true;
            }
            return false;
        break;
        case EM_FUNCAO_DE_Y:
            // y = m*x + n
            if(m * px + n == py)
            {
                return true;
            }
            return false;
        break;
        case EM_FUNCAO_INDEFINIDO:
            cout << "SegmentoBasico::contemrPonto - Erro, segmento não definido" << endl;
        break;
        default:
            return false;
        break;
        }
    }
    return false;
}

/**
  Utiliza o metodo defineSegmento();
**/
void SegmentoBasico::setSegmento(rPonto p1, rPonto p2)
{
    defineSegmento(p1, p2);
}


SegmentoBasico::EM_FUNCAO_DE SegmentoBasico::getEmFuncaoDe()
{
    return emFuncaoDe;
}

rPonto SegmentoBasico::getP1()
{
    return rPonto(p1x,p1y);
}

rPonto SegmentoBasico::getP2()
{
    return rPonto(p2x, p2y);
}


rPonto SegmentoBasico::getPosicaoRetangulo()
{
    return rPonto(mx, my);
}

int SegmentoBasico::getLarguraRetangulo()
{
    return Mx - mx;
}

int SegmentoBasico::getAlturaRetangulo()
{
    return My - my;
}

/**
   Define o segmento, calculando a sua equação de acordo
   com os pontos que o definem
**/
void SegmentoBasico::defineSegmento(rPonto p1, rPonto p2)
{
    p1x = p1.x(), p1y = p1.y(),
    p2x = p2.x(), p2y = p2.y();

    vx = p1x - p2x;
    vy = p1y - p2y;

    if(p1x > p2x)
    {
        Mx = p1x;
        mx = p2x;
    }else{
        Mx = p2x;
        mx = p1x;
    }

    if(p1y > p2y)
    {
        My = p1y;
        my = p2y;
    }else
    {
        My = p2y;
        my = p1y;
    }
    if(absoluto(vx) > absoluto(vy))
    {
//        emFuncaoDe = EM_FUNCAO_DE_Y;
        cout << "Em funcao de Y" << endl;
        m = vy/ vx;
        cout << " m " << m << endl;
        n = p1y - p1x * m;
    }else
    {
//        cout << "Em funcao de X" << endl;
        emFuncaoDe = EM_FUNCAO_DE_X;
        m = vx/ vy;
        n = p1x - p1y * m;
    }

}

/** Verifica se um ponto esta dentro do retangulo formato
  pelos pontos que definem o segmento
    Obs.: Se o ponto estiver na borda do retangulo, ele é
    considerado dentro do retangulo
**/
bool SegmentoBasico::dentroDoRetangulo(rPonto &p)
{
    int px = p.x() , py = p.y();
    if(px >= mx && px <= Mx &&
       py >= my && py <= My )
    {
        return true;
    }
    return false;
}

void SegmentoBasico::imprimePRelativo(SegmentoBasico::POSICAO_RELATIVA_PONTO p)
{
    switch(p)
    {
    case PONTO_SUPERIOR:
        cout << "rPonto Superior" << endl;
        break;
    case PONTO_INFERIOR:
        cout << "rPonto Inferior" << endl;
        break;
    case PONTO_CONTIDO:
        cout << "rPonto Contido" << endl;
        break;
    case PONTO_INDEFINIDO:
        cout << "rPonto Indefinido" << endl;
        break;
    }
}


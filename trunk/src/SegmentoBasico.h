#ifndef MSEGMENTO_H
#define MSEGMENTO_H


#include "Utilidades.h"

class SegmentoBasico
{
public:
    enum EM_FUNCAO_DE{
        EM_FUNCAO_DE_X,
        EM_FUNCAO_DE_Y,
        EM_FUNCAO_INDEFINIDO
    };

    enum POSICAO_RELATIVA_PONTO
    {
        PONTO_SUPERIOR,
        PONTO_INFERIOR,
        PONTO_CONTIDO,
        PONTO_INDEFINIDO
    };

private:
    rPonto p1;
    rPonto p2;
    EM_FUNCAO_DE emFuncaoDe;

    int p1x, p1y,
        p2x, p2y;
    float vx , vy;
    float m ,n;
    int mx, my;  // menor x , menor y
    int Mx, My;  // maior x , maior y
    int largura;
    int altura;
    bool maisHorizontal; // Define se o segmento é mais vertical(false) ou mais horizontal (true)

 /* Equacao reduzida da reta
     x = ( vx/vy ) * y + (x1 - vx/vy * y1 )
     m = vx / vy
     n = x1 - vx/vy * y1
     x = m *y + n
*/
    void defineSegmento(rPonto p1 , rPonto p2);
    void inicializaSegmento();

public:

    SegmentoBasico(rPonto p1 = rPonto(10,10), rPonto p2 = rPonto(20,20));
    bool contemrPonto(rPonto p);
    POSICAO_RELATIVA_PONTO posicaoRelativarPonto(rPonto p);

    void setSegmento(rPonto p1, rPonto p2);
    EM_FUNCAO_DE getEmFuncaoDe();
    rPonto getP1();
    rPonto getP2();
    rPonto getPosicaoRetangulo();
    int getLarguraRetangulo();
    int getAlturaRetangulo();

    bool dentroDoRetangulo(rPonto &p);
    static void imprimePRelativo(POSICAO_RELATIVA_PONTO p);
protected:

};

#endif // MSEGMENTO_H

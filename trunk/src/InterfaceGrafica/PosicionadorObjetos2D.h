#ifndef POSICIONADOROBJETOS2D_H
#define POSICIONADOROBJETOS2D_H

#include "Ponto.h"
#include <vector>

#include "Grafo.h"

using namespace std;

typedef Ponto<float> rPonto;

class PosicionadorObjetos2D
{
private:
    rPonto m_minCampo;
    rPonto m_maxCampo;

    float m_larguraCampo;
    float m_alturaCampo;

    vector<rPonto> m_pontos;

    float m_areaCampo;
    float m_tamMola;

    vector< vector < char > > g;  /**< Grafo */

    rPonto pontoAleatorio();

public:
    PosicionadorObjetos2D(const rPonto &minCampo,const rPonto &maxCampo, unsigned numObjetos);

    bool setObjeto(unsigned id, const rPonto &ponto);
    void setDistanciaVertice(float dist);

    bool ligado(unsigned idA, unsigned idB);
    bool ligaObjeto(unsigned idA, unsigned idB);
    bool desligaObjeto(unsigned idA, unsigned idB);

    void calculaPosicoes();

    unsigned getNumObjetos();
    float getDistanciaVertice();

    const rPonto & getPosicao(unsigned id);

};

#endif // POSICIONADOROBJETOS2D_H

#include "PosicionadorObjetos2D.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

rPonto PosicionadorObjetos2D::pontoAleatorio()
{
    rPonto r(5.0f + m_minCampo.x() + rand()%((int) (m_maxCampo.x() - m_minCampo.x() - 10.0f)),
             5.0f + m_minCampo.y() + rand()%((int) (m_maxCampo.y() - m_minCampo.y() - 10.0f)));
    return r;
}

PosicionadorObjetos2D::PosicionadorObjetos2D(const rPonto &minCampo,const rPonto &maxCampo, unsigned numObjetos)
{
    unsigned i, j;

    srand(time(NULL));

    m_tamMola = 30.f;
    m_minCampo = minCampo;
    m_maxCampo = maxCampo;
    m_larguraCampo = maxCampo.x() - minCampo.x();
    m_alturaCampo = maxCampo.y() - minCampo.y();
    m_areaCampo = m_larguraCampo * m_alturaCampo;

    cout << maxCampo << minCampo << endl;
    cout << m_larguraCampo << m_alturaCampo << endl;

    m_pontos.resize(numObjetos);
    g.resize(numObjetos);

    for(i = 0 ; i < g.size() ; i++)
    {
        g[i].resize(g.size());
        m_pontos[i] = pontoAleatorio();
    }

    for(i = 0 ; i < g.size() ; i++)
        for(j = 0 ; j < g.size() ; j++)
            g[i][j] = 0;

}

bool PosicionadorObjetos2D::setObjeto(unsigned id, const rPonto &ponto)
{
    if(id < m_pontos.size())
    {
        m_pontos[id] = ponto;
        return true;
    }
    return false;
}

void PosicionadorObjetos2D::setDistanciaVertice(float dist)
{
    m_tamMola = dist;
}

bool PosicionadorObjetos2D::ligado(unsigned idA, unsigned idB)
{
    if(idA < g.size() && idB < g.size())
        return g[idA][idB];
    return 0;
}

bool PosicionadorObjetos2D::ligaObjeto(unsigned idA, unsigned idB)
{
    if(idA < g.size() && idB < g.size())
    {
        g[idA][idB] = 1;
        g[idB][idA] = 1;
        return true;
    }
    return false;
}

bool PosicionadorObjetos2D::desligaObjeto(unsigned idA, unsigned idB)
{
    if(idA < g.size() && idB < g.size())
    {
        g[idA][idB] = 0;
        g[idB][idA] = 0;
        return true;
    }
    return false;
}

void PosicionadorObjetos2D::calculaPosicoes()
{
    if(g.size() == 0) return;

    int numVertices = g.size(), i, j;
    rPonto  forca(0.0f,0.0f), // Forca resultante
            r(0.0f,0.0f),   // Vetor direcional entre particulas
            velocidade[numVertices];

    float cargaParticula = 300.f, cElastica = 0.1f,
          atrito = 0.45f, energiaCinetica =9999.0f,   massa = 10.0f,
          minEnergCinetica = 3.0f *numVertices, cargaCampoLateral = 1600.f;
    int numInteracoes = 0;

    while(energiaCinetica > minEnergCinetica && numInteracoes < 500)
    {
        energiaCinetica = 0.0f;

        for(i = 0 ; i < numVertices ; i++)// Calcula forca resultante de cada particula
        {
            forca = rPonto(0.0f,0.0f);

            // Columb's para o limite do campo de visão
            // Max
            forca +=  (cargaCampoLateral/distanciaH(m_pontos[i],m_maxCampo)) * rPonto(-1.0,0.0);
            forca +=  (cargaCampoLateral/distanciaV(m_pontos[i],m_maxCampo)) * rPonto(0.0,-1.0);
            // Min
            forca +=  (cargaCampoLateral/distanciaH(m_pontos[i],m_minCampo)) * rPonto(1.0,0.0);
            forca +=  (cargaCampoLateral/distanciaV(m_pontos[i],m_minCampo)) * rPonto(0.0,1.0);

            for( j = 0 ; j < numVertices ; j++)
            {
                if(i != j)
                {
                    r = m_pontos[i] - m_pontos[j];
//                    cout << r << " mod = " << r.mod() << " uni = " << r.uni() << endl;
                    // Columb's Law, cargaParticula é (k*q1*q2) !
                    forca +=  (cargaParticula/r.mod()) * r.uni();

                    // Hooke's law
                    if(g[i][j] == 1 )// verifica se estão ligados
                    {
                        forca += (-cElastica*(r.mod()- m_tamMola)) * r.uni();
                    }
                }
            }
            velocidade[i] = ( velocidade[i] + forca) * atrito;
            velocidade[i] = forca * atrito;
            m_pontos[i] += velocidade[i];

            energiaCinetica += massa * velocidade[i].mod2();

            if(m_pontos[i].x() < m_minCampo.x() || m_pontos[i].x() > m_maxCampo.x() ||
               m_pontos[i].y() < m_minCampo.y() || m_pontos[i].y() > m_maxCampo.y())
            {
                velocidade[i] = rPonto(0.f,0.f);
                m_pontos[i] = pontoAleatorio();
            }
        }
        numInteracoes++;
    }
}

const rPonto &PosicionadorObjetos2D::getPosicao(unsigned id)
{
    return m_pontos[id];
}

float PosicionadorObjetos2D::getDistanciaVertice()
{
    return m_tamMola;
}

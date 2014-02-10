#include "ArestaGrafo.h"

ArestaGrafo::ArestaGrafo()
{
    m_de = 0;
    m_para = 0;
    m_custo = 1.f;
    m_id = 0;
    m_grafo = 0x0;
}

ArestaGrafo* ArestaGrafo::novaAresta()
{
    return new ArestaGrafo();
}

void ArestaGrafo::setAresta(unsigned de, unsigned para, float custo, unsigned id, Grafo *grafo)
{
    m_de = de;
    m_para = para;
    m_custo = custo;
    m_id = id;
    m_grafo = grafo;
}

void ArestaGrafo::setDe(unsigned id)
{
    m_de = id;
}

void ArestaGrafo::setPara(unsigned id)
{
    m_para = id;
}

void ArestaGrafo::setCusto(float custo)
{
    m_custo = custo;
}

void ArestaGrafo::setId(unsigned id)
{
    m_id = id;
}

void ArestaGrafo::setGrafo(Grafo *grafo)
{
    m_grafo = grafo;
}

unsigned ArestaGrafo::de() const
{
    return m_de;
}

unsigned ArestaGrafo::para() const
{
    return m_para;
}

float ArestaGrafo::custo() const
{
    return m_custo;
}

unsigned ArestaGrafo::id() const
{
    return m_id;
}

Grafo *ArestaGrafo::grafo()
{
    return m_grafo;
}

const Grafo *ArestaGrafo::grafo() const
{
    return m_grafo;
}

#include "VerticeGrafo.h"

VerticeGrafo::VerticeGrafo()
{
    m_id = 0;
    m_grafo = 0x0;
}

/**
 * @brief
 *  Utilizado como contrutor da classe,
 * constroe um novo vértice.
 * @param id - id do vertice
 * @param grafo - Grafo ao qual overtice pertence
 * @return VerticeGrafo - Vertice criado
 */
VerticeGrafo *VerticeGrafo::novoVertice() const
{
    return new VerticeGrafo();
}

void VerticeGrafo::setId(unsigned id)
{
    m_id = id;
}

void VerticeGrafo::setGrafo(Grafo *grafo)
{
    m_grafo = grafo;
}

unsigned VerticeGrafo::id() const
{
    return m_id;
}

Grafo *VerticeGrafo::grafo()
{
    return m_grafo;
}

const Grafo *VerticeGrafo::grafo() const
{
    return m_grafo;
}

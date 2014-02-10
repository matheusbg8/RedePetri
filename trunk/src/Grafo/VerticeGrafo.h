#ifndef VERTICEGRAFO_H
#define VERTICEGRAFO_H

class Grafo;


/**
 * @brief
 *  Esta classe é utilizada para armazenar informações
 * sobre um vértice do grafo. Um vértice só pode ser
 * construido por outro vértice, o vertice principal
 * pode ser acessado pelo método estatico fabrica()
 * o vertice retornado por fabrica() nunca deve ser
 * deletado.
 *  Esta classe pode ser extendida através da herança,
 * permitindo que mais informações possam ser armazenadas
 * nos vértices, a classe derivada deve re-implementar
 * o metodo novoVertice(), retornando a classe derivada e não
 * a classe base.
*/
class VerticeGrafo
{
protected:
    unsigned m_id;
    Grafo *m_grafo;

public:
    VerticeGrafo();

    virtual VerticeGrafo *novoVertice() const;
    virtual ~VerticeGrafo(){}

    void setId(unsigned id);
    void setGrafo(Grafo *grafo);

    unsigned id() const;
    Grafo *grafo();
    const Grafo *grafo() const;

};

#endif // VERTICEGRAFO_H

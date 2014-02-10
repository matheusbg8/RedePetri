#ifndef ARESTAGRAFO_H
#define ARESTAGRAFO_H

class Grafo;


/**
 * @brief
 *
 *  Esta classe pode ser extendida através da herança,
 * permitindo que mais informações possam ser armazenadas
 * nas aresta, a classe derivada deve re-implementar
 * o metodo novaAresta(), retornando a classe derivada e não a
 * classe base.
 */
class ArestaGrafo
{
protected:
    unsigned m_de;
    unsigned m_para;
    float m_custo;
    unsigned m_id;
    Grafo *m_grafo;

public:
    ArestaGrafo();

    // Metodo utilizado quando usando aresta como fabrica
    virtual ArestaGrafo* novaAresta();
    virtual ~ArestaGrafo(){}

    void setAresta(unsigned de, unsigned para, float custo, unsigned id, Grafo *grafo);
    void setDe(unsigned id);
    void setPara(unsigned id);
    void setCusto(float custo);
    void setId(unsigned id);
    void setGrafo(Grafo *grafo);

    unsigned de() const;
    unsigned para() const;
    float custo() const;

    unsigned id() const;
    Grafo *grafo();
    const Grafo* grafo() const;
};

#endif // ARESTAGRAFO_H

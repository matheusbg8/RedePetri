#ifndef ARCO_H
#define ARCO_H

#include "IRedepetri.h"

enum TipoArco
{
    ARCO_PT, /**< Lugar - Transicao */
    ARCO_TP  /**< Transicao - Lugar */
};

class RedePetri;

class Arco
{
private:
    unsigned m_peso;
    unsigned m_de;
    unsigned m_para;
    TipoArco m_tipo;
    IRedePetri *m_redePetri;
    unsigned m_id;
    RedePetri *m_rede;
public:
    Arco(RedePetri *rede, TipoArco tipoArco, unsigned de, unsigned para, unsigned peso =1);

    void setPeso(unsigned peso);
    bool setRede(RedePetri *rede);
    bool setID(unsigned id);
    void setArco(TipoArco tipo , unsigned de, unsigned para, unsigned peso = 1);

    unsigned id() const;
    unsigned de() const;
    unsigned para() const;
    unsigned peso() const;
    TipoArco tipo() const;

};

#endif // ARCO_H

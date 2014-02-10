#ifndef COMPONENTEPETRI_H
#define COMPONENTEPETRI_H

#include "ComponentePetri.h"
#include "ControladorRede.h"

//#include "RedePetri.h"
class RedePetri;


/** Interface dos componentes petri **/
class DComponentePetri
{
protected:
    unsigned m_IDCP;

public:
    DComponentePetri()
    {
        m_IDCP = 0;
    }

    unsigned getIDCP()
    {
        return m_IDCP;
    }


    /**
     * @brief
     *  Retorna o ID especifico do componente no modelo de rede petri
     * @return unsigned - Indice do componente
     */
    void setIDCP(unsigned id)
    {
        m_IDCP = id;
    }

    /**
     * @brief
     *   Define a RedePetri que o componente pertence
     * @param redePetri - RedePetri que o componente pertence
     * @return bool - True se a definição foi realizada, false caso contrario
     */
    virtual bool setControle(ControladorRede *redePetri) = 0;



    /**
     * @brief
     *  Retorna o modelo de RedePetri no qual o componente e esta contido
     * ou retorna 0x0 se não estiver em nenhuma rede petri
     * @return RedePetri - Referencia para a rede petri
     */
    virtual ControladorRede* getControlador() = 0;


    /**
     * @brief
     *  Verifica se a componente petri é uma transição
     * @return bool - True se é uma transição, false se não é.
     */
    virtual bool ehTransicao() = 0;

    /**
     * @brief
     *    verifica se a componente petri é um lugar.
     * @return bool - True se é transição, false caso contrario.
     */
    virtual bool ehLugar() = 0;


    /**
     * @brief
     *    Verfica se a componente petri é um arco
     * @return bool - True se é arco, false caso contrario.
     */
    virtual bool ehArco() = 0;

};

#endif // COMPONENTEPETRI_H

#ifndef COMUNICADORREDEPETRI_H
#define COMUNICADORREDEPETRI_H

#include "IVRedePetri.h"
#include "ComunicadorTCP.h"

/**
 * @brief
 *  A classe ComunicadorRedePetri é uma visualização
 * de rede de petri que envia todos os acontecimentos
 * da rede para outros programas usando mensagens
 * TCP/IP
 */
class ComunicadorRedePetri : public IVRedePetri
{
private:
    ComunicadorTCP m_comunicador;

public:
    ComunicadorRedePetri(const char *ip, int porta);
    ComunicadorRedePetri();

    // Interface de visualizacao da rede de petri

    // Edicao
    void dNovoLugar(unsigned id);
    void dNovaTransicao(unsigned id);
    void dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso);
    void dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso);

    void dDeletaTransicao(unsigned id);
    void dDeletaLugar(unsigned id);
    void dDeletaArco(unsigned id);

    void dSetPesoArco(unsigned id, unsigned peso);

    void dSetFichas(unsigned id, unsigned numFichas);

    // Consulta
    unsigned dPesoArco(unsigned id);
    unsigned dFichas(unsigned id);

    // Controle
    void dExecutaTransicao(unsigned id);

};

#endif // COMUNICADORREDEPETRI_H

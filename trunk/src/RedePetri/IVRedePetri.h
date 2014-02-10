#ifndef IVREDEPETRI_H
#define IVREDEPETRI_H

class IVRedePetri
{
public:
    // Edicao
    virtual void dNovoLugar(unsigned id) = 0;
    virtual void dNovaTransicao(unsigned id) = 0;
    virtual void dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso) = 0;
    virtual void dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso) = 0;

    virtual void dDeletaTransicao(unsigned id) = 0;
    virtual void dDeletaLugar(unsigned id) = 0;
    virtual void dDeletaArco(unsigned id) = 0;

    virtual void dSetPesoArco(unsigned id, unsigned peso) = 0;

    virtual void dSetFichas(unsigned id, unsigned numFichas) = 0;

    // Consulta
    virtual unsigned dPesoArco(unsigned id) = 0;
    virtual unsigned dFichas(unsigned id) = 0;

    // Controle
    virtual void dExecutaTransicao(unsigned id) = 0;
};

#endif // IVREDEPETRI_H

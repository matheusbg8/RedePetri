#ifndef IREDEPETRI_H
#define IREDEPETRI_H

class IRedePetri
{
public:

    // Edicao
    virtual unsigned novoLugar() = 0;
    virtual unsigned novaTransicao() = 0;
    virtual unsigned novoArcoPT(unsigned de, unsigned para, unsigned peso) = 0;
    virtual unsigned novoArcoTP(unsigned de, unsigned para, unsigned peso) = 0;

    virtual bool deletaTransicao(unsigned id) = 0;
    virtual bool deletaLugar(unsigned id) = 0;
    virtual bool deletaArco(unsigned id) = 0;

    virtual bool setPesoArco(unsigned id, unsigned peso) = 0;

    virtual bool setFichas(unsigned id, unsigned numFichas) = 0;

    // Consulta
    virtual unsigned pesoArco(unsigned id) const = 0;
    virtual unsigned idArcoPT(unsigned de, unsigned para) const = 0;
    virtual unsigned idArcoTP(unsigned de, unsigned para) const = 0;

    virtual unsigned fichas(unsigned id) const = 0;

    virtual bool sensibilizado(unsigned id) const = 0;

    // Modelo
    virtual bool executaTransicao(unsigned id) = 0;
};

#endif // IREDEPETRI_H

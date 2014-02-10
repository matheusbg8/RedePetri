#ifndef DCOMPONENTEPETRI_H
#define DCOMPONENTEPETRI_H

class RedePetri;

// Tipos possiveis de componente petri
enum TipoComponentePetri
{   TRANSICAO,
    LUGAR,
    ARCO,
    INDEFINIDO
};

class ComponentePetri
{
private:
    int gID;  /**< ID global do Objeto */

    virtual TipoComponentePetri meuTipoComponentePetri() = 0;

public:
    ComponentePetri(int IDGlobal=-1);
    virtual ~ComponentePetri();

    int getIDGlobal() const;
    TipoComponentePetri tipo();

    friend class RedePetri;
};

#endif // DCOMPONENTEPETRI_H

#ifndef DREDEAMBIENTE_H
#define DREDEAMBIENTE_H

#include <Container.h>

class DRedeAmbiente : public Container
{
public:
    DRedeAmbiente();

public slots:
    void novoLugar();
    void novaTransicao();
};

#endif // DREDEAMBIENTE_H

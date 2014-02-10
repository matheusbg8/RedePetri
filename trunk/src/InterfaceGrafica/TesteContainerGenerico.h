#ifndef TESTECONTAINERGENERICO_H
#define TESTECONTAINERGENERICO_H

#include <QObject>
#include "ContainerGenerico.h"


class TesteContainerGenerico :
        public QObject,
        public ContainerGenerico
{

    Q_OBJECT
protected:

    QMenu* m_mnus[4];

    int m_idTipoDesenhoFoco;
    int m_idDesenhoFoco;

public:
    TesteContainerGenerico();

    void criaMenus();

    void mousePrecionado(MouseEvento *me, int idTipoDesenho, int idDesenho);
    void mouseSolto(MouseEvento *me, int idTipoDesenho, int idDesenho);
    int ligacao(int deId, int deIdTipo, int paraId, int paraIdTipo);

public slots:
    void novoObjetoT1();
    void novoObjetoT2();
    void novoObjetoT3();
    void deletaObjeto();

};

#endif // TESTECONTAINERGENERICO_H

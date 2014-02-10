#ifndef VISUALIZADORGRAFO_H
#define VISUALIZADORGRAFO_H

#include "Container.h"
#include <vector>
#include "ModeloGrafo.h"
#include "GrafoNome.h"

class VisualizadorGrafo : public QObject, public Container
{
    Q_OBJECT
private:
    static Cor m_cores[48];
    GrafoNome *m_grafo;

    QMenu *mnuFundo;

    QAction *actApagaGrafo;

    void criaAcoes();
    void criaMenus();
    void inicilizaCores(Cor a, Cor b, Cor c, unsigned numCores =48);

    void atualizaVisualizacao();

protected:

    virtual bool mousePrecionado(MouseEvento *novoMouseEvento);

public:
    VisualizadorGrafo(Container *pai= 0x0);

    void setModelo(GrafoNome *modelo);

    GrafoNome *getModelo();

private slots:
    void apagaGrafo();
};



#endif // VISUALIZADORGRAFO_H

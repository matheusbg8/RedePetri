#ifndef DGRAFO_H
#define DGRAFO_H

#include <QObject>
#include "Container.h"
#include "DAresta.h"
#include "DVertice.h"
#include "Grafo.h"

class DGrafo :public QObject, public Container
{
    Q_OBJECT
public:

    DGrafo(Grafo *grafo = 0x0);
    ~DGrafo();

    void removeDesenho(Desenho *d);

    void novoDesenho(Desenho *d, bool avisaFilho = true);


protected:

    list<DAresta *> m_arestas;
    list<DVertice*> m_vertices;

    bool mousePrecionado(MouseEvento *novoMouseEvento);

    Grafo *m_grafo;

private:
    static unsigned grafoID;
    unsigned m_grafoID;

    QMenu *mnuFundo;

    QAction *actNovoVertice;
    QAction *actNovaAresta;
    QAction *actImprimeDados;

    void criaAcoes();
    void criaMenus();

private slots:
    void novaAresta();
    void novoVertice();
    void imprimeDados();
    void buscaComponentes();
    void buscaProfundidade();
    void buscaLargura();

};

#endif // DGRAFO_H

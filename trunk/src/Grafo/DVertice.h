#ifndef DVERTICE_H
#define DVERTICE_H

#include "CirculoBasico.h"
#include "Grafo.h"

class DVertice: public QObject, public Circulo
{
    Q_OBJECT
private:

    QMenu *mnuFundo;

    QAction *actDeleta;


    void criaAcoes();
    void criaMenus();

    void inicializaDVertice();

private slots:
    void deleta();

protected:
    Grafo *m_grafo;

    int m_grafoID;

    bool m_marcacaoVisivel;

    bool mousePrecionado(MouseEvento *e);

public:
    DVertice(Grafo *grafo);
    ~DVertice();
    int idGrafo();

};

#endif // DVERTICE_H

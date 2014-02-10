#ifndef DARESTA_H
#define DARESTA_H

#include "Seta.h"
#include "Grafo.h"
#include "DVertice.h"

class DAresta: public QObject, public Seta
{
    Q_OBJECT
private:
    // Manipulação do modeloGrafo
    void removeOrigem();
    void removeDestino();
    void defineOrigem(DVertice *vertice);
    void defineDestino(DVertice *vertice);

    QMenu *mnuFundo;
    QAction *actDeleta;

    void criaAcoes();
    void criaMenus();

protected:
    Grafo *m_grafo;
    int m_grafoID;

    float m_custo;

    DVertice *m_origem;
    DVertice *m_destino;

    void desenha();

    bool aceitaLigacaoIni(Desenho *desenho);
    bool aceitaLigacaoFim(Desenho *desenho);

private slots:
    void deleta();

public:
    DAresta(Grafo *grafo);

    void setCusto(float custo);


    int idGrafo();
};

#endif // DARESTA_H

#ifndef AREADESENHO_H
#define AREADESENHO_H

#include "Container.h"

class AreaDesenho : public QObject, public Container
{
    Q_OBJECT
private:
    void iniciaAreaDesenho();
    void criaAcoes();
    void criaMenus();

    QMenu *mnu;

    QAction *novoSegmentoAct;
    QAction *novoCirculoAct;
    QAction *novoTrianguloAct;
    QAction *novoTrianguloModificavelAct;
    QAction *novoRetanguloAct;
    QAction *novoSetaAct;
    QAction *novaRedePetriAct;
    QAction *actNovoAmbiente;
    QAction *actNovoGrafo;
    QAction *actNovoJogador;
    QAction *actContainerGenerico;


private slots:
    void novoSegmento();
    void novoCirculo();
    void novoTriangulo();
    void novoTrianguloModificavel();
    void novoRetangulo();
    void novoSeta();
    void novaRedePetri();
    void novoAmbiente();
    void novoGrafo();
    void novoJogadorRede();
    void novoTesteContainerGenerico();


    void novoDesenho(Desenho *d, bool avisaFilho = true);

public:
    AreaDesenho(rPonto posicao = rPonto(10.0,10.0),int largura = 100, int altura = 100, Container *m_pai = 0x0);
    bool mousePrecionado(MouseEvento *e);

    void * getSuper();

};

#endif // AREADESENHO_H

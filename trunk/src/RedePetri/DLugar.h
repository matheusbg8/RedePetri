#ifndef DLUGAR_H
#define DLUGAR_H

#include "CirculoBasico.h"
#include "DComponentePetri.h"
#include "Lugar.h"
#include "ControladorRede.h"


/**
 * @brief
 *  Esta classe representa um lugar de uma rede de petri, desenhado na tela,
 * herdando as propriedades do Circulo.
 */
class DLugar : public QObject, public Circulo, public DComponentePetri
{
    Q_OBJECT
public:

    DLugar();
    ~DLugar();

    bool setFichas(int numFichas);
    void dSetFichas(unsigned numFichas);
    unsigned fichas();

     void desenha();

    void setNome(QString nome);

    // Iterface ComponentePetri
    bool setControle(ControladorRede *controladorRede);
    ControladorRede* getControlador();
    bool ehTransicao();
    bool ehLugar();
    bool ehArco();

protected:
    RedePetri *m_redePetri; /**< Rede Petri que o Lugar esta inserido */
    ControladorRede *m_controlador;

public slots:
    void novoArco();
    void deleta();
    void adicionaFicha();
    void removeFicha();
private:
    void iniciaDLugar();

    //= Popup menus do Qt ==
    QMenu *mnu;

    QAction *novoArcoAct;
    QAction *deletaAct;
    QAction *actADDFicha;
    QAction *actRMVFicha;
    QAction *actExecuta;
    QAction *actNovoArco;

    unsigned m_numFichas;

    void criaAcoes();
    void criaMenus();
    // ===================

    bool mousePrecionado(MouseEvento *e);

    friend class DRedePetri;
};

#endif // DLUGAR_H

#ifndef DTRANSICAO_H
#define DTRANSICAO_H

#include "Retangulo.h"
#include "RedePetri.h"
#include "DComponentePetri.h"

class DTransicao :public QObject,  public Retangulo, public DComponentePetri
{
    Q_OBJECT
public:
    DTransicao();
    ~DTransicao();

    virtual void desenha();

    void setNome(QString m_nome);

    // Interface ComponentePetri
    bool setControle(ControladorRede * controlador);
    ControladorRede * getControlador();
    bool ehTransicao();
    bool ehLugar();
    bool ehArco();
    string &informacao();

protected:

    ControladorRede *m_controlador;
    string m_informacao;

private:
    void inicializaDTransicao();
    bool mousePrecionado(MouseEvento *novoMouseEvento);

    QMenu *mnu;
    QAction *actDeleta;
    QAction *actExecuta;
    QAction *actNovoArco;

    void criaAcoes();
    void criaMenus();

public slots:
    void deleteta();
    void executa();
    void novoArco();

};

#endif // DTRANSICAO_H

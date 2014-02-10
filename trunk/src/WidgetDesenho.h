#ifndef WIDGETDESENHO_H
#define WIDGETDESENHO_H

#include <QGLWidget>

#include "CirculoBasico.h"
#include "Retangulo.h"
#include "Segmento.h"
#include "Triangulo.h"
#include "Container.h"
#include "DesenhoComposto.h"
#include "Seta.h"
#include "DRedePetri.h"


/**
    Classe principal responsavel pelo desenho dos objetos na tela
**/

class WidgetDesenho : public QGLWidget, DesenhoMestre
{
    Q_OBJECT
private:
    void inicializa();

    void converteQtMouseEvento(MouseEvento *me, QMouseEvent *qme);
    rPonto ultimoMouse;
    Desenho* movendo;
    Seta *teste;
    QMenu *mnuFundo;

    QAction *novaTransicaoAct;
    QAction *novoLugarAct;
    QAction *novoArcoAct;
    QAction *alinharAct;

    void criaAcoes();
    void criaMenus();

    // Implementação dos metodos virtuais do DesenhoMestre
    void desenhoSelecionado(Desenho *desenho);

    void ativarRastriamentoDoMouse(bool simNao);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void ajustaDesenho(rPonto P);

    void setSelecionado(Desenho *desenho);

public:
    explicit WidgetDesenho(QWidget *parent = 0);

    void comando(string cmd);

    // Implementação dos metodos virtuais do DesenhoMestre
    void desenhaTexto(int x, int y, const QString &str, const QFont &font);

    void redesenha();

    int altura();

    int largura();

    QWidget * getWidget();

signals:
    void mousePressSignal(QMouseEvent *event);


    /**
     * @brief
     *  Este sinal é gerado sempre que um desenho
     * for focado pelo usuario.
     * @param desenho - Desenho que esta focado
     */
    void desenhoEmFoco(Desenho *desenho);


    /**
     * @brief
     *  Esse sinal é gerado sempre que um desenho
     * sofrer um evento do usuario.
     * @param desenho - Desenho que sofreu evento.
     */
    void atualizaDesenho(Desenho *desenho);

public slots:
    void novoCirculo();
    void novoRetangulo();
    void novoDesenho();
    void novaTransicao();
    void novoArco();
    void novoLugar();
    void novaRedePetri();
    void carregaXMLSimples();
    void carregaGrafoModeloSimples();
    void carregaGrafo();
    void alinharDesenhos();

};

#endif // WIDGETDESENHO_H

#ifndef JANELA_PRINCIPAL_H
#define JANELA_PRINCIPAL_H

#include <QMainWindow>
#include "Desenho.h"
#include "ui_JanelaPrincipal.h"

namespace Ui {
    class JanelaPrincipal;
}

class JanelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit JanelaPrincipal(QWidget *parent = 0);
    ~JanelaPrincipal();

private slots:
    void on_linhaComando_editingFinished();
    void desenhoEmFoco(Desenho * desenho);
    void atulizaDesenho(Desenho * desenho);
    void on_pbTransicao_clicked();

private:
    Ui::JanelaPrincipal *ui;
    void criaMenus();

    QMenu *mnuArquivo;

    QAction *actCarregaXMLSimples;
    QAction *actCarregaGrafoModeloSimples;
    QAction *actCarregaGrafo;
    QAction *actCarregaPNML;

};

#endif // JANELA_PRINCIPAL_H

/*

#include <QtGui/QApplication>
#include "JanelaPrincipal.h"
#include "WidgetProgramacao.h"

#include <iostream>

using namespace std;

#include "RetanguloBasico.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    JanelaPrincipal w;
    w.show();
    return a.exec();
}
*/

#ifndef WIDGETPROGRAMACAO_H
#define WIDGETPROGRAMACAO_H

#include <QDockWidget>
#include <DRedePetri.h>

namespace Ui {
class WidgetProgramacao;
}

class WidgetProgramacao : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit WidgetProgramacao(QWidget *parent = 0);
    ~WidgetProgramacao();
    void editaInfoTransicao(DTransicao *transicao);
    void editaInfoFicha(DLugar *lugar, int idFicha);
    
private slots:
    void on_pbOK_clicked();

    void on_pbCancelar_clicked();

private:
    Ui::WidgetProgramacao *ui;
    DLugar *m_lugarEditando;
    unsigned m_idFicha;
    DTransicao *m_transicaoEditando;
};

#endif // WIDGETPROGRAMACAO_H

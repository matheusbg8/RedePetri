#ifndef DIALOGGRAFOCOBERTURA_H
#define DIALOGGRAFOCOBERTURA_H

#include <QDialog>

namespace Ui {
class DialogGrafoCobertura;
}

class DialogGrafoCobertura : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogGrafoCobertura(QWidget *parent = 0, int *limiteVertices = 0x0);
    ~DialogGrafoCobertura();
    
private slots:
    void on_btOk_accepted();

private:
    Ui::DialogGrafoCobertura *ui;
    int *m_limiteVertices;
};

#endif // DIALOGGRAFOCOBERTURA_H

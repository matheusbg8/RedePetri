#ifndef DNOVOAMBIENTE_H
#define DNOVOAMBIENTE_H

#include "Ambiente.h"

#include <QDialog>

namespace Ui {
class DNovoAmbiente;
}

class DNovoAmbiente : public QDialog
{
    Q_OBJECT
protected:
    Ambiente **m_resultado;
public:
    explicit DNovoAmbiente(Ambiente **resultado, QWidget *parent = 0);
    ~DNovoAmbiente();
    
private slots:
    void on_btOkCancel_accepted();

private:
    Ui::DNovoAmbiente *ui;
};

#endif // DNOVOAMBIENTE_H

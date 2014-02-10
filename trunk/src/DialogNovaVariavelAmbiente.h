#ifndef DIALOGNOVAVARIAVELAMBIENTE_H
#define DIALOGNOVAVARIAVELAMBIENTE_H

#include <QDialog>

#include "DVariavelAmbiente.h"

namespace Ui {
class DialogNovaVariavelAmbiente;
}

class DialogNovaVariavelAmbiente : public QDialog
{
    Q_OBJECT

protected:
    VariavelAmbiente **m_resultado;
public:
    explicit DialogNovaVariavelAmbiente(VariavelAmbiente **resultado, QWidget *parent = 0);
    ~DialogNovaVariavelAmbiente();
    
private slots:
    void on_btOkCancel_accepted();

private:
    Ui::DialogNovaVariavelAmbiente *ui;
};

#endif // DIALOGNOVAVARIAVELAMBIENTE_H

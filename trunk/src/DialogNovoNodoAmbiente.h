#ifndef DIALOGNOVONODOAMBIENTE_H
#define DIALOGNOVONODOAMBIENTE_H

#include <QDialog>
#include <NodoAmbiente.h>

namespace Ui {
class DialogNovoNodoAmbiente;
}

class DialogNovoNodoAmbiente : public QDialog
{
    Q_OBJECT
private:
    NodoAmbiente **m_nodo;

    bool dadosCompleto();

public:
    explicit DialogNovoNodoAmbiente(NodoAmbiente **nodo, QWidget *parent = 0);
    ~DialogNovoNodoAmbiente();
    
private slots:

    void on_buttonBoxOk_accepted();

    void on_lineEditNome_editingFinished();

    void on_lineEditValorNodo_editingFinished();

    void on_comboBoxTipoNodo_currentIndexChanged(int index);

private:
    Ui::DialogNovoNodoAmbiente *ui;
};

#endif // DIALOGNOVONODOAMBIENTE_H

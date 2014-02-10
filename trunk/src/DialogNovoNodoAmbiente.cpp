#include "DialogNovoNodoAmbiente.h"
#include "ui_DialogNovoNodoAmbiente.h"
#include "VariavelAmbiente.h"
#include "PerguntaAmbiente.h"
#include "AcaoAmbiente.h"

DialogNovoNodoAmbiente::DialogNovoNodoAmbiente(NodoAmbiente **nodo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNovoNodoAmbiente)
{
    ui->setupUi(this);
    m_nodo = nodo;
}

DialogNovoNodoAmbiente::~DialogNovoNodoAmbiente()
{
    delete ui;
}

void DialogNovoNodoAmbiente::on_buttonBoxOk_accepted()
{
    switch(ui->comboBoxTipoNodo->currentIndex())
    {
    case 0:
        // Variavel
        *m_nodo = new VariavelAmbiente(ui->lineEditNome->text().toStdString(),ui->lineEditValorNodo->text().toStdString());
    break;
    case 1:
        // Pergunta
        *m_nodo = new PerguntaAmbiente(ui->lineEditNome->text().toStdString(),ui->lineEditValorNodo->text().toStdString());
    break;
    case 2:
        // Acao
        *m_nodo = new AcaoAmbiente(ui->lineEditNome->text().toStdString(),ui->lineEditValorNodo->text().toStdString());
    break;
    default:
        *m_nodo = 0x0;
    break;
    }
}

bool DialogNovoNodoAmbiente::dadosCompleto()
{
    if(ui->lineEditNome->text() == "")
        return false;

    if(ui->lineEditValorNodo->text() == "")
        return false;

    if(ui->comboBoxTipoNodo->currentIndex() == -1)
        return false;

    return true;

}

void DialogNovoNodoAmbiente::on_lineEditNome_editingFinished()
{
    if(dadosCompleto())
        ui->buttonBoxOk->setEnabled(true);
    else
        ui->buttonBoxOk->setEnabled(false);
}

void DialogNovoNodoAmbiente::on_lineEditValorNodo_editingFinished()
{
    if(dadosCompleto())
        ui->buttonBoxOk->setEnabled(true);
    else
        ui->buttonBoxOk->setEnabled(false);
}

void DialogNovoNodoAmbiente::on_comboBoxTipoNodo_currentIndexChanged(int index)
{
    if(dadosCompleto())
        ui->buttonBoxOk->setEnabled(true);
    else
        ui->buttonBoxOk->setEnabled(false);
}

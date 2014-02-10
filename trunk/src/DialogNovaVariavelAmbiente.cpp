#include "DialogNovaVariavelAmbiente.h"
#include "ui_DialogNovaVariavelAmbiente.h"

DialogNovaVariavelAmbiente::DialogNovaVariavelAmbiente(VariavelAmbiente **resultado, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNovaVariavelAmbiente)
{
    ui->setupUi(this);
    m_resultado = resultado;
    (*m_resultado) = 0x0;
}

DialogNovaVariavelAmbiente::~DialogNovaVariavelAmbiente()
{
    delete ui;
}

void DialogNovaVariavelAmbiente::on_btOkCancel_accepted()
{
    // Se for dado um OK, a variavel de ambiente sera criada
    (*m_resultado) = new VariavelAmbiente(ui->leNome->text().toLocal8Bit().constData() ,
                                           ui->leValor->text().toLocal8Bit().constData());

}

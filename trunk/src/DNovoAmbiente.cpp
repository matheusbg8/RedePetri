#include "DNovoAmbiente.h"
#include "ui_DNovoAmbiente.h"

DNovoAmbiente::DNovoAmbiente(Ambiente **resultado, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DNovoAmbiente)
{
    m_resultado = resultado;
    ui->setupUi(this);
}

DNovoAmbiente::~DNovoAmbiente()
{
    delete ui;
}

void DNovoAmbiente::on_btOkCancel_accepted()
{
    *m_resultado = new Ambiente(ui->leNomeAmbiente->text().toLocal8Bit().constData());
}

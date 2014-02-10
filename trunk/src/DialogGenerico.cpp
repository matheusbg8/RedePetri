#include "DialogGenerico.h"
#include "ui_DialogGenerico.h"

DialogGenerico::DialogGenerico(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGenerico)
{
    ui->setupUi(this);
}

DialogGenerico::~DialogGenerico()
{
    delete ui;
}

void DialogGenerico::setPergunta(QString pergunta)
{
    ui->labelPergunta->setText(pergunta);
}

QString DialogGenerico::resposta()
{
    return m_resposta;
}

void DialogGenerico::on_buttonBoxOK_accepted()
{
    m_resposta = ui->lineEditResposta->text();
    ui->lineEditResposta->clear();
}

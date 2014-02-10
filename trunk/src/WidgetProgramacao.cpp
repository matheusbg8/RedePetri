#include "WidgetProgramacao.h"
#include "ui_WidgetProgramacao.h"

WidgetProgramacao::WidgetProgramacao(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::WidgetProgramacao)
{
    ui->setupUi(this);
    m_lugarEditando = 0x0;
    m_transicaoEditando = 0x0;
}

WidgetProgramacao::~WidgetProgramacao()
{
    delete ui;
}


void WidgetProgramacao::editaInfoTransicao(DTransicao *transicao)
{
    m_lugarEditando = 0x0;
    m_transicaoEditando = transicao;
}

void WidgetProgramacao::editaInfoFicha(DLugar *lugar, int idFicha)
{
    m_transicaoEditando = 0x0;
    m_lugarEditando = lugar;
    m_idFicha = idFicha;
    //ui->ptCodigo->setPlainText(QString(lugar->getInfoFicha(idFicha).c_str()));
}

void WidgetProgramacao::on_pbOK_clicked()
{
    if(m_lugarEditando)
    {
//        m_lugarEditando->setInfoFicha(m_idFicha, string(ui->ptCodigo->toPlainText().toLocal8Bit().constData()));
        cout << "Atribuido informacao a ficha: " << ui->ptCodigo->toPlainText().toLocal8Bit().constData() << endl;
        close();
    }
}

void WidgetProgramacao::on_pbCancelar_clicked()
{
    m_transicaoEditando = 0x0;
    m_lugarEditando = 0x0;
    close();
}

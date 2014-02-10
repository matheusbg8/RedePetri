#include "DialogGrafoCobertura.h"
#include "ui_DialogGrafoCobertura.h"


/**
 * @brief
 *
 * @param parentm - Pai do Dialog
 * @param limiteVertices - Ponteiro para o limite de vertices
 * do usuario. Se o usuario não estabelecer o limite, -1 é retornado.
 */
DialogGrafoCobertura::DialogGrafoCobertura(QWidget *parent, int *limiteVertices) :
    QDialog(parent),
    ui(new Ui::DialogGrafoCobertura)
{
    ui->setupUi(this);
    m_limiteVertices = limiteVertices;
    *m_limiteVertices = -1;
}

DialogGrafoCobertura::~DialogGrafoCobertura()
{
    delete ui;
}


/**
 * @brief
 *  Defini o limite digitado na interface como retorno do Dialog
 */
void DialogGrafoCobertura::on_btOk_accepted()
{
    *m_limiteVertices = ui->leNumVertices->text().toInt();
}

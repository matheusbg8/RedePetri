#include "ConfiguracaoAmbienteROS.h"
#include "ui_ConfiguracaoAmbienteROS.h"

ConfiguracaoAmbienteROS::ConfiguracaoAmbienteROS(list<string> &listaTopicos, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ConfiguracaoAmbienteROS),
    m_topicos(listaTopicos)
{
    ui->setupUi(this);

    list<string>::iterator i;
    for(i = listaTopicos.begin() ; i != listaTopicos.end() ; i++)
        ui->listWidgetTopicos->addItem(i->c_str());

    listaTopicos.clear();
}

ConfiguracaoAmbienteROS::~ConfiguracaoAmbienteROS()
{
    delete ui;
}

void ConfiguracaoAmbienteROS::on_pushButtonAdiciona_clicked()
{
    foreach( QListWidgetItem * i , ui->listWidgetTopicos->selectedItems())
    {
        ui->listWidgetTopicosMonitorados->addItem(i->text());
        delete i;
    }
}

void ConfiguracaoAmbienteROS::on_buttonBoxAceita_accepted()
{
    for(int i = 0 ; i < ui->listWidgetTopicosMonitorados->count() ; i++)
    {
        m_topicos.push_back(ui->listWidgetTopicosMonitorados->item(i)->text().toStdString());
    }
}

void ConfiguracaoAmbienteROS::on_pushButtonRemove_clicked()
{
    foreach( QListWidgetItem * i , ui->listWidgetTopicosMonitorados->selectedItems())
    {
        ui->listWidgetTopicos->addItem(i->text());
        delete i;
    }
}

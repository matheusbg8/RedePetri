#ifndef CONFIGURACAOAMBIENTEROS_H
#define CONFIGURACAOAMBIENTEROS_H

#include <QDialog>
#include <QStringListModel>
#include <list>
using namespace std;

namespace Ui {
class ConfiguracaoAmbienteROS;
}

class ConfiguracaoAmbienteROS : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfiguracaoAmbienteROS(list<string>& listaTopicos, QWidget *parent = 0);
    ~ConfiguracaoAmbienteROS();

protected:
    list<string> &m_topicos;

private slots:
    void on_pushButtonAdiciona_clicked();

    void on_buttonBoxAceita_accepted();

    void on_pushButtonRemove_clicked();

private:
    Ui::ConfiguracaoAmbienteROS *ui;
};

#endif // CONFIGURACAOAMBIENTEROS_H

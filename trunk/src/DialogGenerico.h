#ifndef DIALOGGENERICO_H
#define DIALOGGENERICO_H

#include <QDialog>

namespace Ui {
class DialogGenerico;
}

class DialogGenerico : public QDialog
{
    Q_OBJECT
private:
    QString m_resposta;
public:
    explicit DialogGenerico(QWidget *parent = 0);
    ~DialogGenerico();
    
    void setPergunta(QString pergunta);
    QString resposta();

private slots:
    void on_buttonBoxOK_accepted();

private:
    Ui::DialogGenerico *ui;
};

#endif // DIALOGGENERICO_H

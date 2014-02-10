#ifndef DVARIAVEL_H
#define DVARIAVEL_H


#include "VariavelAmbiente.h"
#include "CirculoBasico.h"


/**
 * @brief
 *  Esta classe é a representação gráfica de uma variavel de ambiente
 */
class DVariavelAmbiente: public QObject , public Circulo
{
    Q_OBJECT
private:
    QMenu *mnuFundo;
    QAction *actDeleta;
    QAction *actNovaVariavel;

    void criaMenus();
    void criaAcoes();

protected:
    QString m_valor;

    unsigned m_id;

    bool mousePrecionado(MouseEvento *novoMouseEvento);
public slots:

    void deleta();
    void novaVariavel();

public:
    DVariavelAmbiente(int idVariavel,QString nome, QString valor = QString());

    void setValor(QString valor);
    const QString & valor() const;


    void desenha();
};

#endif // DVARIAVELAMBIENTE_H

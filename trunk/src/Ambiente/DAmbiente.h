#ifndef DAMBIENTE_H
#define DAMBIENTE_H

#include "Container.h"
#include "DVariavelAmbiente.h"
#include <QDomNode>

class CAmbiente;

class DAmbiente :public QObject, public Container
{
    Q_OBJECT

private:
    QMenu *mnuFundo;

    QAction *actNovaVariavel;
    QAction *actNovaPergunta;
    QAction *actCriaReferencia;
    QAction *actGeraXML;
    QAction *actDeleta;

    void criaAcoes();
    void criaMenus();

    void adicionaVariavelXML(QDomDocument *documento , QDomElement* pai, unsigned idVariavel);
protected:
    vector<DVariavelAmbiente*> m_variaveis;
    CAmbiente *m_controleAmbiente;

    bool mousePrecionado(MouseEvento *novoMouseEvento);

    void adicionaVariavelRaiz();

private slots:
    void novaVariavel();
    void novaPergunta();
    void criaReferencia();
    void geraXML();
    void deleta();

public:
    DAmbiente();
    ~DAmbiente();

    CAmbiente* controle();

    void setControleAmbiente(CAmbiente *controle);

    // Visualização das variaveis
    bool addVariavel(unsigned idVarPai, const VariavelAmbiente *novaVariavel);
    bool removeVariavel(unsigned varId);

    void apagaTudo();

    bool setNomeVariavel(unsigned idVar, QString nome);
    void setNome(QString nome);

    bool setValor(unsigned idVar , QString valor);

};

#endif // DAMBIENTE_H

#ifndef VISUALIZADORPROPRIEDADES_H
#define VISUALIZADORPROPRIEDADES_H

#include <QTreeWidget>
#include "DLugar.h"
#include "DTransicao.h"
#include "DArco.h"
#include "DRedePetri.h"
#include "DVariavelAmbiente.h"



/**
 * @brief Esta classe é utilizada para visualização
 * das propriedades de qualquer desenho, ela é uma
 *  QTreeWidget do Qt.
 * Funcionamento:
 *   A classe possui um unico metodo chamado
 * visualizaDesenho(Desenho *desenho) utilizado
 * para alterar os desenhos que são visualizados.
 *   Internamente existem dois metodos, o para inserir
 * a as pripriedades do desenho inseriDesenho(),
 * e outro para detectar alteração em alguma
 * propriedade alteracaoDesenho(). Para manter
 * a compatibilidade com quaquer desenho é necessario
 * implementar esses dois metodos para cada desenho
 * que sera possivel de ser visualizado.
 *   Fluxo de execulção:
 *  O metodo visualizaDesenho() é chamado, ele verifica
 * que tipo de desenho é o que esta sendo visualizado
 * dependendo do tipo um metodo de serir desenho é chamado,
 * a verificação do tipo de desenho é feita atraves do
 * metodo tipoDesenho() dos Desenhos.
 *
 */
class VisualizadorPropriedades : public QTreeWidget
{
    Q_OBJECT
public:
    explicit VisualizadorPropriedades(QWidget *parent = 0);
    void visualizaDesenho(Desenho *desenho);

private:
    void inseriDesenho(QTreeWidgetItem *raiz, Desenho *desenho);
    bool alteracaoDesenho(QTreeWidgetItem *itemAlterado, int coluna);

    void inseriLugar(QTreeWidgetItem *raiz,DLugar *lugar);
    bool alteracaoLugar(QTreeWidgetItem *itemAlterado, int coluna);

    void inseriTransicao(QTreeWidgetItem *raiz,DTransicao *transicao);
    bool alteracaoTransicao(QTreeWidgetItem *itemAlterado, int coluna);

    void inseriArco(QTreeWidgetItem *raiz, DArco *arco);
    bool alteracaoArco(QTreeWidgetItem *itemAlterado, int coluna);

    void inseriRedePetri(QTreeWidgetItem *raiz, DRedePetri *redePetri);
    bool alteracaoRedePetri(QTreeWidgetItem *itemAlterado, int coluna);

    void inseriVariavelAmbiente(QTreeWidgetItem *raiz, DVariavelAmbiente *variavelAmbiente);
    bool alteracaoVariavelAmbiente(QTreeWidgetItem *itemAlterado, int coluna);

    bool contem(QTreeWidgetItem *item, QString texto);


    Desenho *desenhoVisualizado;

signals:
    
public slots:
    void alteracaoItem(QTreeWidgetItem *itemAlterado, int coluna);
    void duploClique(QTreeWidgetItem *itemClicado, int coluna);

};

#endif // VISUALIZADORPROPRIEDADES_H

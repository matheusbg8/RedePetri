#ifndef DARCO_H
#define DARCO_H

#include "Seta.h"
#include "DComponentePetri.h"
#include "RedePetri.h"

/**
 * @brief
 *  DArco representa representa a interface gráfica de um
 * unico arco de uma rede de petri, geralmente instanciado
 * dentro de uma DRedePetri, a classe DArco possui um referencia
 * para o modelo de dados da Rede Petri.
 *  A classe Darco herdando as propriedades e o comportamento
 * de uma seta, os metodos aceitaLigacaoIni(Desenho *desenho)
 * e ligacaoFim(Desenho *desenho) são chamados sempre quando
 * existir uma tentativa de estabelecer uma ligação com algum
 * outro desenho, esses metodos decidem se a ligação ocorrera
 * ou não, dependendendo do seu retorno, se for true, a ligação
 * sera estabelecida, caso contrario a ligação sera ignorada.
 *
 */
class DArco :public QObject, public Seta, public DComponentePetri
{
    Q_OBJECT
public:

    DArco();
    ~DArco();

    void setPeso(int custo);
    int getPeso() const;
    void dSetPeso(unsigned peso);
    unsigned dPeso();

    DComponentePetri *getOrigem();
    DComponentePetri *getDestino();

    void desenha();

    void setFake(bool simNao);
    bool fake();

// Interface ComponentePetri
    bool setControle(ControladorRede *controlador);

    ControladorRede * getControlador();

    bool ehTransicao();

    bool ehLugar();

    bool ehArco();

protected:

    ControladorRede *m_controlador;

    int m_peso;
    bool m_fake;

    // Sobrescrita dos metodos virtuais da seta
    bool aceitaLigacaoIni(Desenho *desenho);
    bool aceitaLigacaoFim(Desenho *desenho);

private:
    void inicializaDArco();

    DComponentePetri * pegaComponente(Desenho *desenho);
    void removeComponenteIni();
    void removeComponenteFim();

    void atualizaCustoEmModDados();

 // Menus do Qt
    QMenu *mnu;
    QAction *actDeleta;

    bool mousePrecionado(MouseEvento *novoMouseEvento);

    DComponentePetri *m_cmpOrigem;
    DComponentePetri *m_cmpDestino;


    void criaAcoes();
    void criaMenus();

public slots:
    void deleta();

};

#endif // DARCO_H

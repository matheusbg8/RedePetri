#ifndef DESENHOMESTRE_H
#define DESENHOMESTRE_H

#include "Desenho.h"
class Container;


/**
 * @brief
 *  O desenho mestre funciona como uma interface dos desenhos com a interface grafica do Qt
 * ele contem a widget onde o desenho sera desenhado e tambem repassa os eventos de mouse e
 * teclado do Qt para os desenhos.
 * para os desenhos
 */
class DesenhoMestre
{
private:
    Container *m_containerPrincipal;  /**< Container principal, que contem todos os outros desenhos */

    list<Desenho*> m_selecionados;  /**< Desenhos que estão selecionado */
    Desenho *m_desenhoSelecionado;  /**< Ultimo desenho selecionado */
    Desenho *m_desenhoRastriandoMouse;

    /** @todo Revisar o MestreGloal da classe do DeenhoMestre, existe a nessecidade dele existir mesmo? **/
    static DesenhoMestre *mestreGlobal; /// Desenho Mestre padrão @todo - Revisar esta estrategia (não utilizada por enquanto)

    /**
     * @brief
     *  Metodo para avisar widget que um desenho foi selecionado
     */
    virtual void desenhoSelecionado(Desenho *desenho);

    /**
     * @brief
     *  Avisa a interface para gerar/não gerar eventos do mouse movendo
     * mesmo que ele não esteja com um botão precionado.
     * @param simNao - true gera, false não gera.
     */
    virtual void ativarRastriamentoDoMouse(bool simNao);

protected:

    // Tratamento de eventos
    void novoMouseEvento(MouseEvento *mouseEvento);

    // Tratamento de desenhos
    void desenha();

    // Inicialização
    void inicializaDesenhoMestre();

public:

    /**
     * @brief
     *  Metodo utilizado para avisar interface que é necessario re-desenhar os desenhos
     */
    virtual void redesenha(); // desenha todos desenhos


    /**
     * @brief
     *  Metodo utilizado para avisar interface que precisa desenha texto na tela
     * @param x
     * @param y
     * @param str
     * @param font
     */
    virtual void desenhaTexto(int x, int y, const QString & str, const QFont & font = QFont() );


    /// @todo - Estudar uma forma de criar popupMenus e pegar altura e largura da janela de forma independente da interface grafica.

    /**
     * @brief
     *  Metodo para pegar a altura da widget
     * @return int - Altura
     */
    virtual int altura();

    /**
     * @brief
     *  Metodo para pegar a largura da widget
     * @return int
     */
    virtual int largura();

    /**
     * @brief
     *  Este metodo foi criado temporariamente para possibilitar a contrução
     * de popup menus dentro dos desenhos.
     * @return QWidget
     */
    virtual QWidget * getWidget();


    DesenhoMestre();
    ~DesenhoMestre();

    void rastriarMouse(Desenho *desenho);
    void paraRastriamentoMouse();

    void novoDesenho(Desenho *d);

    void novoDesenhoEmPrincipal(Desenho *d);

    void setTamanho(int largura, int altura);

    Desenho * selecionado();

    const list<Desenho*> & selecionados();

    void setSelecionado(Desenho *desenho);

    static DesenhoMestre * getMestreGlobal();

};

#endif // DESENHOMESTRE_H

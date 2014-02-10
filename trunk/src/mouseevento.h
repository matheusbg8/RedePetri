#ifndef MOUSEEVENTO_H
#define MOUSEEVENTO_H


#include "Utilidades.h"

enum BotaoMouse {
    NENHUM_BOTAO,     // 0x00   b00
    BOTAO_DIREITO,    // 0x01   b01
    BOTAO_ESQUERDO,   // 0x02   b10
    BOTAO_MEIO        // 0x03   b11
};


enum EventoMouse{
    NENHUM_EVENTO,
    MOUSE_PRECIONADO,
    MOUSE_SOLTO,
    MOUSE_CLIQUE,
    MOUSE_MOVENDO
};

enum DistrbuicaoMouseEvento
{
    DISTRIBUI_TODOS,              // Distribui para todos desenhos sem restrição
    DISTRIBUI_GEOMETRICO,         // Distribui apenas para os desenhos que contem a posição do mouse quando o evento foi gerado
    DISTRIBUI_PRIMEIRO_GEOMETRICO // Distribui apenas para o primeiro desenho que satisfazer a condição geometrica de cima
};



/**
 * @brief
 * Esta classe representa um evento gerado pelo mouse,
 * um evento só é gerado quando um botão do mouse
 * é precionado.
 * Esta classe possui:
 * \li O botão que foi utilizado do mouse
 * \li O tipo do evento, informa como o evento foi gerado,
 * se algum botão do mouse foi precionado, se foi solto ou
 * se esta precionado e o mouse esta se movimentando.
 * \li A posição em que o mouse estava quando o evento foi gerado.
 * Esta posição esta representada de três formas.
 * \li a posição local, que esta sempre com referencial na posição do
 * desenho pai, o Container do desenho.
 * \li a posição global, esta sempre com referencia ao canto
 * inferior esquerdo da tela.
 * \li a posição de janela, que utiliza o eixo Y invertido,
 * o X é a distancia do inicio lateral esquerdo da tela, e o
 * Y é a distancia do inicio superior da tela com relação
 * ao ponto onde o evento foi gerado. Este sistema de referencia
 * foi necessário para posicionar os popupMenus.
 * botão precionado.
 *
 */
class MouseEvento
{
private:
    BotaoMouse m_botao;
    EventoMouse m_evento;
    rPonto m_pLocal;
    rPonto m_pGlobal;
    QPoint m_pJanelaGlobal;
public:
    MouseEvento(BotaoMouse botao = NENHUM_BOTAO, EventoMouse evento = NENHUM_EVENTO ,rPonto pLocal = rPonto(), rPonto pGlobal = rPonto(), QPoint pJanela = QPoint());
    MouseEvento(const MouseEvento &mouseEvento);

    void setEvento(EventoMouse evento);
    void setBotao(BotaoMouse botao);
    void setPosicaoLocal(const rPonto & posicaoLocal);
    void setPosicaoGlobal(const rPonto &posicaoGlobal);
    void setPosicaoJanela(const QPoint &posicaoJanela);

    const rPonto &posicaoLocal();
    const rPonto &posicaoGlobal();
    const QPoint &posicaoJanela();
    const EventoMouse & evento();
    const BotaoMouse & botao();
};

#endif // MOUSEEVENTO_H

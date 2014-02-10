#include "mouseevento.h"

MouseEvento::MouseEvento(BotaoMouse botao, EventoMouse evento ,rPonto pLocal, rPonto pGlobal, QPoint pJanela)
{
    this->m_botao = botao;
    this->m_evento = evento;
    this->m_pLocal = pLocal;
    this->m_pGlobal = pGlobal;
    this->m_pJanelaGlobal = pJanela;
}

MouseEvento::MouseEvento(const MouseEvento &mouseEvento)
{
    this->m_botao = mouseEvento.m_botao;
    this->m_evento = mouseEvento.m_evento;
    this->m_pLocal = mouseEvento.m_pLocal;
    this->m_pGlobal = mouseEvento.m_pGlobal;
    this->m_pJanelaGlobal = mouseEvento.m_pJanelaGlobal;
}

void MouseEvento::setEvento(EventoMouse mouseEvento)
{
    this->m_evento = mouseEvento;
}

void MouseEvento::setBotao(BotaoMouse botao)
{
    this->m_botao = botao;
}

void MouseEvento::setPosicaoLocal(const rPonto &posicaoLocal)
{
    this->m_pLocal = posicaoLocal;
}

void MouseEvento::setPosicaoGlobal(const rPonto &posicaoGlobal)
{
    this->m_pGlobal = posicaoGlobal;
}

void MouseEvento::setPosicaoJanela(const QPoint &posicaoJanela)
{
    this->m_pJanelaGlobal = posicaoJanela;
}


/**
 * @brief
 * Retorna a posição local de onde o mouse estava quando o evento foi gerado
 *
 * @return const rPonto - Posição local
 */
const rPonto & MouseEvento::posicaoLocal()
{
    return m_pLocal;
}

const rPonto & MouseEvento::posicaoGlobal()
{
    return m_pGlobal;
}

const EventoMouse & MouseEvento::evento()
{
    return m_evento;
}

const BotaoMouse & MouseEvento::botao()
{
    return m_botao;
}

const QPoint & MouseEvento::posicaoJanela()
{
    return m_pJanelaGlobal;
}



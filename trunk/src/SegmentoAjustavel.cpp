#include "SegmentoAjustavel.h"

SegmentoAjustavel::SegmentoAjustavel()
{
    m_inicio = new Circulo(3,rPonto(10.0f,10.0f));
    m_inicio->setCorFundo(Cor::verde);
    m_inicio->setNome("Inicio Segmento");

    m_fim = new Circulo(3,rPonto(50.0f,50.0f));
    m_fim->setCorFundo(Cor::verde);
    m_fim->setNome("Fim Segmento");

    m_segmento = new Segmento(rPonto(10.0f,10.0f), rPonto(50.0f,50.0f));
    m_segmento->setCorFundo(Cor::vermelho);
    m_segmento->setNome("Segmento");

    novaComposicao(m_segmento);
    novaComposicao(m_fim);
    novaComposicao(m_inicio);

    m_ligaA = 0x0;
    m_ligaB = 0x0;

    setDesenhaFundo(false);
}

void SegmentoAjustavel::defineSegmento(const rPonto &inicio, const rPonto &fim, int espesura)
{
    rPonto mInicio = converteMeuReferencial(inicio),
           mFim = converteMeuReferencial(fim);

    m_inicio->setCentro(mInicio);
    m_fim->setCentro(mFim);
    m_segmento->defineSegmento(mInicio,mFim);

//    ajustaComponentes();
}

void SegmentoAjustavel::mousePrecionadoComposto(Desenho *desenho, MouseEvento *mouseEvento)
{
    if(desenho == m_segmento)
    {
        mousePrecionado(mouseEvento);
    }
}

void SegmentoAjustavel::mouseMovendoComposto(Desenho *desenho, MouseEvento *mouseEvento)
{
    if(desenho == m_fim)
    {
        defineSegmento(converteReferencialPai(m_inicio->getCentro()), mouseEvento->posicaoLocal());

    }else if(desenho == m_segmento)
    {
        mouseMovendo(mouseEvento);
    }else if(desenho == m_inicio)
    {
        defineSegmento(mouseEvento->posicaoLocal() , converteReferencialPai(m_fim->getCentro()));
    }
}

void SegmentoAjustavel::mouseSoltoComposto(Desenho *desenho, MouseEvento *mouseEvento)
{
    if(desenho == m_segmento)
    {
        mouseSolto(mouseEvento);
    }else

    if(desenho == m_fim)
    {
        Desenho *lig = m_pai->getDesenho(mouseEvento->posicaoLocal(), this);
        if(lig != 0x0)
        {
            cout << "SOLTO EM CIMA DO DESENHO " << lig->getNome().toStdString() << endl;
            ligaB(lig);
        }else
            cout << "SOLTO EM CIMA DE NENHUM DESENHO" << endl;

    }else

    if(desenho == m_inicio)
    {
        Desenho *lig = m_pai->getDesenho(mouseEvento->posicaoLocal(), this);
        if(lig != 0x0)
        {
            ligaA(lig);
        }
    }
}


void SegmentoAjustavel::ligaA(Desenho *d)
{
    if(m_ligaA != 0x0)
        m_ligaA->removeEscuta(this);

    m_ligaA = d;
    m_ligaA->novaEscuta(this);
}

void SegmentoAjustavel::ligaB(Desenho *d)
{
    if(m_ligaB != 0x0)
        m_ligaB->removeEscuta(this);

    m_ligaB = d;
    m_ligaB->novaEscuta(this);
}

void SegmentoAjustavel::eventoAlteracaoPosicao(Desenho *desenho, rPonto novaPosicao)
{
    cout << "DegmentoAjustavel(" << getNome().toStdString() << "):: eventoAlteracaoPosicao("
         << desenho->getNome().toStdString() << ")\n";
    if(desenho == m_ligaB)
       defineSegmento(converteReferencialPai(m_inicio->getCentro()), novaPosicao);
    if(desenho == m_ligaA)
        defineSegmento(novaPosicao, converteReferencialPai(m_fim->getCentro()));
}

void *SegmentoAjustavel::getSuper()
{
    return this;
}

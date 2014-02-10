#include "DAresta.h"

void DAresta::removeOrigem()
{
    // Se meu modelo é valido
    if(m_grafo != 0x0)
    {
        // Se eu possuo origem e destino
        if(m_origem != 0x0 && m_destino != 0x0)
        {
            // E garantido que se eu tiver origem e destino
            // eu tbm tenho um ID da aresta no grafo

            m_grafo->deletaAresta(m_grafoID);
            m_grafoID = -1;
        }

        m_origem = 0x0;
        return ;
    }

    cout << "DAresta::removeOrigem - Erro modelo invalido" << endl;

}

void DAresta::removeDestino()
{
    // Se meu modelo é valido
    if(m_grafo != 0x0)
    {
        // Se eu possuo origem e destino
        if(m_origem != 0x0 && m_destino != 0x0)
        {
            // Se eu tenho origem e destino
            // e garantido que tenho um ID

            m_grafo->deletaAresta(m_grafoID);
        }

        m_destino = 0x0;
        return ;
    }

    cout << "DAresta::removeDestino - Erro modelo invalido" << endl;
}

void DAresta::defineOrigem(DVertice *vertice)
{
    if(m_origem != 0x0)
        removeOrigem();

    m_origem = vertice;

    if(m_origem != 0x0 && m_destino != 0x0 && m_grafo != 0x0)
    {   // Se eu tenho origem e destino,
        // eu represento uma aresta no grafo
        if(m_origem->idGrafo() >= 0 && m_destino->idGrafo() >= 0)
            m_grafoID = m_grafo->novaAresta(m_origem->idGrafo() , m_destino->idGrafo() , m_custo);
    }
}

void DAresta::defineDestino(DVertice *vertice)
{
    // Se eu ja tenho um destino
    if(m_destino != 0x0)
        removeDestino(); // remove ele

    // Define novo destino
    m_destino = vertice;

    if(m_destino != 0x0 && m_origem != 0x0 && m_grafo != 0x0)
    {   // Se eu tenho origem e destino
        // eu tenho uma aresta no grafo

        if(m_origem->idGrafo() > 0 && m_destino->idGrafo() > 0)
            m_grafoID = m_grafo->novaAresta(m_origem->idGrafo() , m_destino->idGrafo(), m_custo);
    }
}

void DAresta::criaAcoes()
{
    actDeleta = new QAction("Deleta" , this);
    QObject::connect(actDeleta, SIGNAL(triggered()), this , SLOT(deleta()));
}

void DAresta::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(actDeleta);
}

void DAresta::desenha()
{
    Seta::desenha();

    if(m_custo != 1)
    {
        rPonto posicaoDesenho ( (fim->posicaoLocal() - inicio->posicaoLocal()) /2.f);
        posicaoDesenho += posicaoDesenho.ortoAntiHorario().uni()*10.f + inicio->posicaoLocal();

        desenhaTexto(QString("%1").arg(m_custo), posicaoDesenho, QFont("Times",12,QFont::Bold));
    }
}

bool DAresta::aceitaLigacaoIni(Desenho *desenho)
{
    // Se não for para desconectar
    if(desenho != 0x0)
    {
        if(desenho->tipoDesenho() == TD_VERTICE)
        {
            defineOrigem((DVertice*) desenho);
            return true;
        }
        return false;
    }

    // É para desconectar o aresta do vertice
    removeOrigem();
    return true;

}

bool DAresta::aceitaLigacaoFim(Desenho *desenho)
{
    if(desenho != 0x0)
    {
        if(desenho->tipoDesenho() == TD_VERTICE)
        {
            defineDestino((DVertice*) desenho);
            return true;
        }
        // Se for outro desenho qualquer
        return false;
    }
    removeDestino();
    return true;
}

void DAresta::deleta()
{
    delete this;
}


DAresta::DAresta(Grafo *grafo)
{
    // Define o tipo de desenho
    m_tipoDesenho = TD_ARESTA;

    // Origem destino e custo
    m_origem = 0x0;
    m_destino = 0x0;
    m_custo = 1.f;

    //Grafo
    m_grafo = grafo;

    criaAcoes();
    criaMenus();
}

void DAresta::setCusto(float custo)
{
    m_custo = custo;
    // Se eu pertenco a uma aresta do grafo
    if(m_grafoID > 0)
    {
        m_grafo->setCustoAresta(m_grafoID , m_custo);
    }
}


/**
 * @brief Retorna o id da aresta
 *
 * @return int - ID da aresta ou -1 se
 * se ainda não representa uma aresta no
 * grafo.
 * Obs.: Uma DAresta só pertence a uma
 * aresta no grafo se ela possui um vertice
 * de origem e de destino.
 */
int DAresta::idGrafo()
{
    return m_grafoID;
}

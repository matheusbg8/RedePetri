#include "TesteContainerGenerico.h"

#include "CirculoBasico.h"


TesteContainerGenerico::TesteContainerGenerico()
{
    m_idDesenhoFoco = -1;
    m_idTipoDesenhoFoco = -1;


    Circulo *c = 0x0;

    c = new Circulo(20, rPonto(30,30));
    c->setCorFundo(Cor::verde);
    c->setIdDesenhoVisivel(true);

    adicionaDesenhoNaFabrica(c,0,0);

    c = new Circulo(10, rPonto(30,30));
    c->setCorFundo(Cor::amarelo);
    c->setNomeVisivel(true);
    c->setIdDesenhoVisivel(true);

    adicionaDesenhoNaFabrica(c,1,0);

    c = new Circulo(15, rPonto(30,30));
    c->setCorFundo(Cor::azul);
    c->setNomeVisivel(true);
    c->setIdDesenhoVisivel(true);

    adicionaDesenhoNaFabrica(c,2,1);

    criaMenus();

}

void TesteContainerGenerico::criaMenus()
{
    QAction *acao;

    m_mnus[0] = new QMenu(widget());
    m_mnus[1] = new QMenu(widget());
    m_mnus[2] = new QMenu(widget());
    m_mnus[3] = new QMenu(widget());


    acao = new QAction("Novo ObjetoT1" , this);
    QObject::connect(acao , SIGNAL(triggered()),this, SLOT(novoObjetoT1()));
    m_mnus[0]->addAction(acao);

    acao = new QAction("Novo ObjetoT2" , this);
    QObject::connect(acao , SIGNAL(triggered()),this, SLOT(novoObjetoT2()));
    m_mnus[0]->addAction(acao);

    acao = new QAction("Novo ObjetoT3" , this);
    QObject::connect(acao , SIGNAL(triggered()),this, SLOT(novoObjetoT3()));
    m_mnus[0]->addAction(acao);

    acao = new QAction("Deleta Objeto" , this);
    QObject::connect(acao , SIGNAL(triggered()),this, SLOT(deletaObjeto()));
    m_mnus[1]->addAction(acao);
    m_mnus[2]->addAction(acao);
    m_mnus[3]->addAction(acao);

}

void TesteContainerGenerico::mousePrecionado(MouseEvento *me, int idTipoDesenho, int idDesenho)
{
    m_idTipoDesenhoFoco = idTipoDesenho;
    m_idDesenhoFoco = idDesenho;

    if(me->botao() == BOTAO_DIREITO)
    {
        m_mnus[idTipoDesenho+1]->exec( me->posicaoJanela()  );
    }

}

void TesteContainerGenerico::mouseSolto(MouseEvento *me, int idTipoDesenho, int idDesenho)
{
}


/**
 * @brief
 *
 * @param deId
 * @param deIdTipo
 * @param paraId
 * @param paraIdTipo
 * @return int - Retorna -1 para aceitar a ligacao e gerar um ID automatico,
 * -2 para não permititir a ligacao.
 * valores >= 0 para aceitar a ligacao e atribuir ao ID do arco o número retornado.
 */
int TesteContainerGenerico::ligacao(int deId, int deIdTipo, int paraId, int paraIdTipo)
{
    cout << "Ligacao de " << deId  << " tipo " << deIdTipo << " para " << paraId << " tipo " << paraIdTipo << endl;
    return -1;
}

void TesteContainerGenerico::novoObjetoT1()
{
    novoDesenho(0);
}

void TesteContainerGenerico::novoObjetoT2()
{
    novoDesenho(1);
}

void TesteContainerGenerico::novoObjetoT3()
{
//    novoDesenho(2);
    novoArco();
}

void TesteContainerGenerico::deletaObjeto()
{
    deletaDesenho(m_idTipoDesenhoFoco, m_idDesenhoFoco);
}

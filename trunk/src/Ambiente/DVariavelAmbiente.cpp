#include "DVariavelAmbiente.h"

#include "DialogNovaVariavelAmbiente.h"
#include "DAmbiente.h"
#include "CAmbiente.h"

void DVariavelAmbiente::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(actNovaVariavel);
    mnuFundo->addAction(actDeleta);
}

void DVariavelAmbiente::criaAcoes()
{
    actNovaVariavel = new QAction("Nova Variavel", this);
    QObject::connect(actNovaVariavel ,SIGNAL(triggered()), this, SLOT(novaVariavel()) );

    actDeleta = new QAction("Deleta", this);
    QObject::connect(actDeleta ,SIGNAL(triggered()), this, SLOT(deleta()));
}

bool DVariavelAmbiente::mousePrecionado(MouseEvento *novoMouseEvento)
{
    if(novoMouseEvento->botao() == BOTAO_DIREITO)
    {
        mnuFundo->exec(novoMouseEvento->posicaoJanela());
        return true;
    }else
    {
        return Circulo::mousePrecionado(novoMouseEvento);
    }
}

void DVariavelAmbiente::deleta()
{
    if(m_pai == 0x0) return;

    ((DAmbiente*) m_pai)->controle()->removeVariavel(m_id);
}

void DVariavelAmbiente::novaVariavel()
{
//    if(m_pai == 0x0) return;

//    VariavelAmbiente *novaVar = 0x0;
//    DialogNovaVariavelAmbiente criaVar(&novaVar , widget());

//    criaVar.exec();

//    if(novaVar != 0x0)
//    {
//        ((DAmbiente*) m_pai)->controle()->novaVariavel(m_id , novaVar);
//    }

 }


DVariavelAmbiente::DVariavelAmbiente(int idVariavel,QString nome, QString valor ):
    Circulo(10 ,rPonto(15,15),0x0)
{
    setNome( nome);

    m_valor = valor;
    m_id = idVariavel;

    criaAcoes();
    criaMenus();

    m_tipoDesenho = TD_VARIAVEL_AMBIENTE;

    setNomeVisivel(true);
    setCorFundo(Cor(162.f/255.f , 197.f/255.f , 240/255.f));

}

void DVariavelAmbiente::setValor(QString valor)
{
    m_valor = valor;
}

const QString &DVariavelAmbiente::valor() const
{
    return m_valor;
}

void DVariavelAmbiente::desenha()
{
    desenhaTexto(m_valor,rPonto(-10,-20));

    Circulo::desenha();
}

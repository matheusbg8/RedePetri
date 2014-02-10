#include "DesenhoMestre.h"
#include "Container.h"
#include "AreaDesenho.h"

#include <iostream>
using namespace std;

DesenhoMestre* DesenhoMestre::mestreGlobal = 0x0;

void DesenhoMestre::desenhoSelecionado(Desenho *desenho)
{
    cout << "ERRO 1" << endl;
}

void DesenhoMestre::ativarRastriamentoDoMouse(bool simNao)
{
    cout << "ERRO 2" << endl;
}

void DesenhoMestre::novoMouseEvento(MouseEvento *mouseEvento)
{
    m_containerPrincipal->novoMouseEvento(mouseEvento);
    redesenha();
}

void DesenhoMestre::desenha()
{
    m_containerPrincipal->desenha();
}

void DesenhoMestre::inicializaDesenhoMestre()
{
    if(mestreGlobal == 0x0)
    {
        mestreGlobal = this;
    }

    if(m_containerPrincipal == 0x0)
    {
        m_containerPrincipal = new AreaDesenho(rPonto(0.f, 0.f), 400, 400);
        m_containerPrincipal->setMestre(this);
    }
}

void DesenhoMestre::redesenha()
{
    cout << "ERRO 3" << endl;
}

void DesenhoMestre::desenhaTexto(int x, int y, const QString &str, const QFont &font)
{
    cout << "ERRO 4" << endl;
}

int DesenhoMestre::altura()
{
    cout << "ERRO 5" << endl;
}

int DesenhoMestre::largura()
{
    cout << "ERRO 6" << endl;
}

QWidget *DesenhoMestre::getWidget()
{
    cout << "ERRO 7" << endl;
}

DesenhoMestre::DesenhoMestre()
{
    /*
     A inicialização do desenho mestre deve ser feito
     depois da inicialização da classe derivada, nesse
     caso WidgetDesenho, o metodo inicializaDesenhoMestre
     deve ser chamado no contrutor.
     Motivo:
        Quando o desenho mestre vai construir o container
     principal (na inicialização), a AreaDeDesenho precisa
     da QWidget para criar os popup menus, que ainda não
     esta disponível, pois a widget ainda não esta construida.
    */

    // Inicialização desses atributos para
    // evitar problemas se eventualmente o metodo
    // inicializaDesenhoMestre() for chamado mais
    // de uma vez
    m_containerPrincipal = 0x0;
    m_desenhoSelecionado = 0x0;
    m_desenhoRastriandoMouse = 0x0;

}

DesenhoMestre::~DesenhoMestre()
{
    delete m_containerPrincipal;
}


/**
 * @brief
 *  Ativa o rastriamento do mouse para um desenho
 * Esse desenho vai receber varios eventos de mouseMovento,
 * mesmo que o mouse não esteja com nenhum botão precionado.
 *  Quando ocorre um rastriamento, nenhum outro objeto recebe
 * eventos do mouse, o fim do rastriamento só acaba quando chamado
 * o metodo paraRastriamentoMouse().
 * @param desenho - Desenho que vai rastria o mouse.
 */
void DesenhoMestre::rastriarMouse(Desenho *desenho)
{
    cout << "Ativando rastriamento" << endl;
    ativarRastriamentoDoMouse(true);
    if(m_desenhoRastriandoMouse == 0x0)
    {
        m_desenhoRastriandoMouse = desenho;
        return;
    }
    cout << "Erro ao ativar rastriamento do mouse, já avia um desenho rastriando" << endl;
}


/**
 * @brief
 *  Encerra o rastriamento do mouse, fazendo com que os eventos do mouse
 * voltem a ser distribuidos normalmente entre os objetos.
 */
void DesenhoMestre::paraRastriamentoMouse()
{
    ativarRastriamentoDoMouse(false);
    m_desenhoRastriandoMouse = 0x0;
    cout << "Rastriamento desativado!" << endl;
}

void DesenhoMestre::novoDesenho(Desenho *d)
{
    if(m_desenhoSelecionado != 0x0)
    {
        m_desenhoSelecionado->novoDesenho(d);
    }else
    {
        if(m_containerPrincipal != 0x0)
            m_containerPrincipal->novoDesenho(d);
        else
        {
            cout << "Não foi possivel criar novo desenho, falta o desenho do desenho mestre" << endl;
            delete d;
        }
    }
}

void DesenhoMestre::novoDesenhoEmPrincipal(Desenho *d)
{
    if(m_containerPrincipal != 0x0)
    {
        m_containerPrincipal->novoDesenho(d);
        return;
    }
    cout << "DesenhoMestre:: Erro ao adicionar desenho em prinicpal, desenhomestre se desenho principal" << endl;
    return;
}

void DesenhoMestre::setTamanho(int largura, int altura)
{
    m_containerPrincipal->defineDesenho(rPonto(0.f,0.f), largura , altura);
}


Desenho * DesenhoMestre::selecionado()
{
    return m_desenhoSelecionado;
}

const list<Desenho *> &DesenhoMestre::selecionados()
{
    return m_selecionados;
}

void DesenhoMestre::setSelecionado(Desenho *desenho)
{
    m_desenhoSelecionado = desenho;

    // Avisa a interface que um desenho foi selecionado
    desenhoSelecionado(desenho);
}


// Implementaçao do contrutor utilizando o padrão singleton
DesenhoMestre * DesenhoMestre::getMestreGlobal()
{
    return DesenhoMestre::mestreGlobal;
}

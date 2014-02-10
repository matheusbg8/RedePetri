#include "DesenhoComposto.h"
#include "Retangulo.h"
#include "Segmento.h"
#include <iostream>
#include <climits>


using namespace std;

int DesenhoComposto::desenhoComposto_id =0;

DesenhoComposto::DesenhoComposto(Container *pai):Container(rPonto(10,10),10,10,pai)
{
    iniciaDesenhoComposto();
}


/**
 * @brief
 *  Destroi os desenhos componentes.
 */
DesenhoComposto::~DesenhoComposto()
{
    // Destroi os componentes
    list<Desenho*>::iterator i;

    while(!componentes.empty())
    {
        if(produzLog)
        cout << "DesenhoComposto(" << getNome().toStdString() << " :: deletandoComponente( "
             << (*i)->getNome().toStdString() << ")\n";
        i = componentes.begin();
        delete(*i); // filhos.remove( *i ) sera chamado pelo metodo removeDesenho() do container
                    // Não se preocupe o desenho sera removido da lista antes de ser destruido
                    // Pelo destrutor da componente
    }
}


/**
 * @brief
 *  Adiciona uma nova composição ao desenho, este desenho fara parte do desenho composto
 * @param desenho - Novo deseho
 * @param avisaFilho - true se o desenho filho deve ser avisado que faz parte
 * do desenho composto, por padrão esse parametro é true.
 */
void DesenhoComposto::novaComposicao(Desenho *desenho, bool avisaFilho)
{
    if(desenho != 0x0 )// Se o desenho é valido
    {
        // Se eu não sou o pai, ou se eu sou o pai e o desenho não é uma componente( nesse caso ele é filho normal)
        if(desenho->pai() != this  || ( /* (implicito) m_pai == pai &&*/ !desenho->componente()) ) // Se o novo não é componente
        {
            if(produzLog)
            cout << "Nova componente em " << m_nome.toStdString() << endl;

            componentes.push_back(desenho);

            /// @todo - Fazer com que todos desenhos pais sejam ouvintes de seus desenho filhos automaticamente.
//            desenho->novoOuvinteDesenhoEvento(this);

            if(avisaFilho)
                desenho->setComponente(this, false); // novoDesenho(this) sera chamado!

            ajustaDesenho(desenho); // Ajusta o seu tamanho para o novo desenho

        }
    }
}


/**
 * @brief
 *  Remove um componente do desenho, o desenho removido não é desalocado
 * @param desenho - Desenho que sera removido
 */
void DesenhoComposto::removeComposicao(Desenho *desenho)
{
    componentes.remove(desenho);
    desenho->setPai(0x0);
}

/**
 * @brief
 *  O desenho que se quer remover pode ser uma composição, se não for,
 * removeDesenho() do container sera chamado.
 * @param d
 */
void DesenhoComposto::removeDesenho(Desenho *d)
{
    if(d->componente())
    {
        removeComposicao(d);
    }else
    {
        Container::removeDesenho(d);
    }
}

bool DesenhoComposto::contemComponente(Desenho *desenho)
{
    list<Desenho *>::iterator i;
    for( i = componentes.begin() ; i != componentes.end() ; i++)
    {
        if( (*i) == desenho)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief
 *      Verifica se o desenho contem o ponto. A verificação é feita primeiro nos desenhos componentes
 * depois, se nenhum desenho componente contem o ponto, o contemPonto da Container é chamada e uma verificação
 * dos filhos é realizada.
 * @param p
 * @return bool
 */
bool DesenhoComposto::contemrPonto(const rPonto &p)
{
    rPonto pMRef = converteMeuReferencial(p); // Transformando para o referencial interno

    list<Desenho*>::iterator i;
    for(i = componentes.begin() ; i != componentes.end() ; ++i)
    {
        if((*i)->visivel() && (*i)->contemrPonto(pMRef))
        {
            return true;
        }
    }

    return false;
}

/**
    Recebe um evento do mouse, verifica se tem algum desenho envolvido, entre os
desenhos da lista, se sim, realiza chamadas a o metodo mouseEventoComposto()
passando o desenho evolvido e o mouse evento.
    distribuicao - Maneira como sera verificado o envolvimento de um desenho com o MouseEvento
    lista - Lista de desenhos que sera verificado, se nenhuma lista for passa, sera usada a lista
de filhos do DesenhoComposto.

    Comportamento padrão dos desenhos aos mouseEventos:
  Um Desenho só recebera um evento do mouse se eles etiver escutando a esse evento,
as escutas podem ser habilitadas usando os metodos:
     setEscutaMouseEvento(bool simOuNao)
     setEscutaMouseMovendo(bool simOuNao)
     setEscutaMousePrecionado(bool simOuNao)
     setEscutaMouseSolto(bool simOuNao)
  Por padrão os desenhos são inicializados com escuta habilitada para mousePrecionado e desabilitado
para mouseMovendo e mouseSolto.
  Geralmente o evento mousePrecionado é distribuido apenas para o primeiro desenho que conter a posicao
do mouse quando o evento foi gerado, quando um desenho recebe esse evento, automaticamente ele fica
habilitado para escutar os eventos mouseMovendo() e mouseSolto(), estas habilitacões são feitas
no método mouseEventoComposto.
**/


/**
 * @brief
 *  Este metodo é chamado quando o DesenhComposto sofre um evento do mouse, ele verifica se
 * existe algum desenho componente que contem este ponto onde o evento foi gerado, se sim,
 * o metodo mouseEventoComposto é chamado com o desenhos componente envolvido no evento e o evento.
 * @param mouseEvento - Evento que o DesenhoComposto esta sofrendo
 * @param distribuicao - Maneira de como o evento sera propagado
 * @param lista - Lista dos desenhos que serao verificados, se nenhuma lista for passada, sera usado a lista
 * dos desenhos componentes.
 * @return bool
 */
bool DesenhoComposto::novoMouseEvento(MouseEvento *mouseEvento)
{
    bool algumDesenhoEnvolvido = false;
    if(produzLog)
    cout << "---------------------------DesenhoComposto( "
            << getNome().toStdString() << "):: novoMouseEvento" << endl;

    rPonto posicaoLocal = converteMeuReferencial(mouseEvento->posicaoLocal());

    list<Desenho*>::reverse_iterator i;
    for(i = componentes.rbegin() ; i != componentes.rend() && !algumDesenhoEnvolvido ; ++i)
    {
        // Se o desenho e visivel e esta escutando eventos do mouse
        if((*i)->visivel() && (*i)->escutaMouseEvento(mouseEvento)) // Se o desenho esta escutando tal evento
        {
            if(mouseEvento->evento() == MOUSE_MOVENDO || (*i)->contemrPonto(posicaoLocal))
            {
                mouseEventoComposto(mouseEvento, *i);
                algumDesenhoEnvolvido = true;
            }
        }
    }

    if(algumDesenhoEnvolvido)
    { // Essas atribuições é necessario para que os desenhos
      // componentes recebam os eventos de mouse
        if(mouseEvento->evento() == MOUSE_PRECIONADO)
        {
            setEscutaMouseSolto(true);
            setEscutaMouseMovendo(true);
        }else if( mouseEvento->evento() == MOUSE_SOLTO)
        {
            setEscutaMouseSolto(false);
            setEscutaMouseMovendo(false);
        }
    }
    return algumDesenhoEnvolvido;
}


/**
 * @brief
 *  Este método é utilizado para que o desenhoComposto ajuste seu tamanho de acordo
 * com a posição de seus desenhos componentes, dependendo da situação, pode ocorrer
 * uma translação de todos os desenhos.
 */
void DesenhoComposto::ajustaComponentes(Desenho *execao)
{
    if(produzLog)
    cout << "DesenhoComposto(" << m_nome.toStdString()
         << ")::ajustaComponentes()" << endl;

    int mx = INT_MAX, // menor X
        my = INT_MAX, // menor Y
        Mx = INT_MIN,  // Maior X
        My = INT_MIN,  // Maior Y
        dmx, // Desenho menor X
        dmy, // Desenho menor Y
        dMx, // Desenho Maior X
        dMy; // Desenho Maior Y

    rPonto dp; // Desenho Posicao

    list<Desenho*>::iterator i;
    for(i = componentes.begin(); i != componentes.end() ; i++)
    {
        dp = converteReferencialPai( (*i)->posicaoLocal() );
        dmx = dp.x(), dmy = dp.y();
        dMx = dmx + (*i)->largura() , dMy = dmy + (*i)->altura();

        if(mx > dmx)  mx = dmx;
        if(Mx < dMx)  Mx = dMx;
        if(my > dmy)  my = dmy;
        if(My < dMy)  My = dMy;
    }

    // Testa se existe componentes, se alguma delas definiu alguma posição
    if(mx == INT_MAX && my == INT_MAX && Mx == INT_MIN && My == INT_MIN)
        return;
    // Obs.: O metodo size() da list não é uma boa, ele é O(N) para usar em compontentes.size()

    // Nova posição do desenho com 10, 5 de cada lado, de folga.
    rPonto novaPosicaoDesenho( mx, my);

    // Calculando vetor de translacao das compontes
    rPonto translacao(posicaoLocal() - novaPosicaoDesenho);

    // Define novas dimenções do desenho com 5 de folga
    defineDesenho(novaPosicaoDesenho, Mx-mx , My-my);

    // Verifica se exeste necessidade de translação
    if(translacao.x() > 0.5f && translacao.y() > 0.5f)
    {
        transladaComponentes(translacao, execao);
    }
}

/**
  Recebe um mouseEvento gerado em cima de um desenho composto.
   Obs.: mouseEvento posicao local é referente ao referencial do pai.
**/
bool DesenhoComposto::mouseEventoComposto(MouseEvento *mouseEvento, Desenho *desenho)
{
    if(produzLog)
    cout << "DesenhComposto :: mouseEventoCompoto( " << desenho->getNome().toStdString() << " ) " << endl;
    switch(mouseEvento->evento())
    {
    case MOUSE_PRECIONADO:
        desenho->setEscutaMouseMovendo(true);
        desenho->setEscutaMouseSolto(true);
        desenho->setEscutaMousePrecionado(false);

        if(produzLog)
        cout << " DesenhoComposto :: mousePrecionadoComposto( " <<
                desenho->getNome().toStdString() << " )" << endl;
        mousePrecionadoComposto(desenho , mouseEvento);
        break;
    case MOUSE_SOLTO:
        desenho->setEscutaMouseSolto(false);
        desenho->setEscutaMouseMovendo(false);
        desenho->setEscutaMousePrecionado(true);

        if(produzLog)
        cout << " DesenhoComposto :: mouseSoltoComposto( " <<
                desenho->getNome().toStdString() << " )" << endl;
        mouseSoltoComposto(desenho , mouseEvento);
        break;
    case MOUSE_CLIQUE:
        break;
    case MOUSE_MOVENDO:
        if(produzLog)
        cout << " DesenhoComposto :: mouseMovendoComposto( " <<
                desenho->getNome().toStdString() << " )" << endl;
        mouseMovendoComposto(desenho , mouseEvento);
        break;
    }
    return true;
}

/**
 * @brief
 *      Este metodo é chamado quando um evento do mouse ocorre devido ao precionamento
 * de um botão, e esse evento atingiu um desenho composto, se nada for especificado para
 * esse desenho, a reação do desenhoComposto sera a mesma de um desenho comum.
 * @param d - Desenho Componente envolvido no evento
 * @param e - Evento gerado pelo mouse
 */
void DesenhoComposto::mousePrecionadoComposto(Desenho *d, MouseEvento *e)
{
    mousePrecionado(e);
}

/**
 * @brief
 *      Este metodo é chamado quando um evento do mouse ocorre devido a botão que foi
 * solto, se este metodo não for escrito por outra classe, ele reage como um Desenho.
 * @param d - Desenho Componente envolvido no evento
 * @param e - Evento gerado pelo mouse
 */
void DesenhoComposto::mouseSoltoComposto(Desenho *d, MouseEvento *e)
{
    mouseSolto(e);
}


/**
 * @brief
 *      Este metodo é chamado quando um evento do mouse ocorre, se este metodo
 * não for escrito por outra classe, ele reage como um Desenho.
 * @param d - Desenho Componente envolvido no evento
 * @param e - Evento gerado pelo mouse
 */
void DesenhoComposto::mouseMovendoComposto(Desenho *d, MouseEvento *e)
{
    mouseMovendo(e);
}


/**
 * @brief
 *  Translada todos os desenhos componentes em direção ao vetor de translação,
 * com execão do desenho componente execão.
 * @param translacao - Vetor que indica a direção da translação.
 * @param execao - Desenho componente que não sera transladado.
 */
void DesenhoComposto::transladaComponentes(rPonto &translacao, Desenho *execao)
{
    if(produzLog)
    cout << "DesenhoComposto(" << m_nome.toStdString()
         << ")::transladaComponentes(" << translacao <<")\n";

    list<Desenho*>::iterator i;
    for(i = componentes.begin() ; i != componentes.end() ; i++)
    {
        if( (*i) != execao)
            (*i)->translada(translacao);
    }
}

/**
 * @brief
 *      Desenha primeiramente os desenhos componentes, depois chama o desenha() do
 * container para que os desenhos filhos possam ser desenhados
 */
void DesenhoComposto::desenha()
{
    Desenho::desenha();
    desenhaComponentes();
    desenhaFilhos();
}

void DesenhoComposto::iniciaDesenhoComposto()
{
    desenhocompotos_mid = desenhoComposto_id;
    setNome(QString("DesenhoComposto %1").arg(desenhocompotos_mid));
    desenhoComposto_id++;
    setEscutaMouseMovendo(true);
    setEscutaMouseSolto(true);
    setEscutaMousePrecionado(true);
}

void DesenhoComposto::desenhaComponentes()
{
    list<Desenho*>::iterator i;
    for(i = componentes.begin() ; i != componentes.end() ; i++)
    {
        if((*i)->visivel())
            (*i)->desenha();
    }
}

int DesenhoComposto::getDesenhoCompostoID()
{
    return desenhocompotos_mid;
}

void *DesenhoComposto::getSuper()
{
    return this;
}

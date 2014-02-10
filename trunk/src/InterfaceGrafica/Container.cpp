//
#include "Container.h"

using namespace std;
#include <iostream>

int Container::container_id = 0;

Container Container::paiDeTodos(rPonto(0,0) , 10,10,0x0);

void Container::iniciaContainer()
{
    container_mid = container_id;
    container_id++;
    setNome(QString("Container %1").arg(container_mid));
    setNomeVisivel(true);
}


Container::Container(Container *pai):Desenho(rPonto(10,10),100,100, pai)
{
    iniciaContainer();
}

Container::Container(rPonto p, int largura, int altura, Container *pai):Desenho(p,largura,altura, pai)
{
    iniciaContainer();
}


/**
 * @brief
 *  O destrutor do Container chama o destrutor de todos seus desenhos filhos.
 */
Container::~Container()
{
    deletaDesenhos();
}

/**
    Este metodo cria novo desenho dentro do contaner,
  esse desenho recebera os eventos do container.
**/
void Container::novoDesenho(Desenho *desenho, bool avisaFilho)
{
    if(desenho != 0x0 )// Se o desenho é valido
    {
        if(desenho->pai() != this || ( /* (implicito) m_pai == pai &&*/ desenho->componente()) ) // Se o novo desenho não é meu filho
        {
            if(produzLog)
                cout << "Novo desenho em " << m_nome.toStdString() << endl;

            filhos.push_back(desenho);
//            filhos.push_front(desenho);

            /// @todo - Fazer com que todos desenhos pais sejam ouvintes de seus desenho filhos automaticamente.
//            desenho->novoOuvinteDesenhoEvento(this);
            if(avisaFilho)
                desenho->setPai(this, false);

            ajustaDesenho(desenho); // Ajusta o seu tamanho para o novo desenho

//            if(m_desenhoMestre != 0x0)
//                m_desenhoMestre->redesenha();
        }
    }
}


/**
 * @brief
 *      Remove um desenho filho da lista de filhos do Container,
 *    o desenho filho ficara sem pai.
 * @param d - Filho que sera removido.
 */
void Container::removeDesenho(Desenho *d)
{
    cout << "Container::removendoDesenho(" << d->getNome().toStdString() << ")" << endl;


    filhos.remove(d);
    d->setPai(0x0);
    cout << "Container::removendoDesenho(" << d->getNome().toStdString() << ") - Concluido" << endl;
}

/**
  Faz uma busca linear O(n) e verifica se o Container contem o desenho
**/
bool Container::contemDesenho(Desenho *desenho)
{
    list<Desenho *>::iterator i;
    for(i = filhos.begin() ; i != filhos.end() ; i++)
    {
        if((*i) == desenho)
        {
            return true;
        }
    }
    return false;
}

/*
void Container::setNome(QString nome)
{
    Desenho::setNome(nome);
}
*/
void Container::deletaDesenhos()
{
    cout << "Container::Deletando " << m_nome.toStdString() << endl;
    list<Desenho*>::iterator i;
    while(!filhos.empty())
    {
         i = filhos.begin();
        delete(*i); // destrutor do filho solicitara a sua remoção do container pai.
         // O desenho filho se encarrega de chamar o metodo remove desenho do container e remover
         // da lista o desenho destruido
    }
}

/**
    Distribui um evento do mouse para todos os desenhos filhos
        mouseEvento - Evento que sera distribuido
        distribuicao - Tipo de distribuição
            DISTRIBUI_TODOS               - Distribui para todos desenhos sem restricao
            DISTRIBUI_GEOMETRICO,         - Distribui apenas para os desenhos que contem a posicao do mouse quando o evento foi gerado
            DISTRIBUI_PRIMEIRO_GEOMETRICO - Distribui apenas para o primeiro desenho que satisfazer a condicao geometrica
 **/

bool Container::novoMouseEvento(MouseEvento *mouseEvento)
{
    bool eventoPropagado = false; // Booleano que indica se o evento foi propagado para algum desenho ou não

    if(produzLog)
        cout << "Container ( " << getNome().toStdString() << "):: novoMouseEvento( )" << endl;

    // Converte a posição local do evento para o referencial do container
    // para que esse evento possa ser repassado para os desenhos internos do
    // container

    rPonto posicaoLocal = converteMeuReferencial(mouseEvento->posicaoLocal());
    MouseEvento novoEvento(*mouseEvento);
    novoEvento.setPosicaoLocal(posicaoLocal);

    // Se eu tenho desenhos dentro
    if(!filhos.empty())
    {

        // Para cada desenho, comecando pelo fim
        // porque a ordem que os desenhos sao desenhados
        // começa pelo inicio, o ultimo desenho desenhado é
        // que esta mais em cima.
        list<Desenho*>::reverse_iterator i;
        for(i = filhos.rbegin() ; i != filhos.rend() && !eventoPropagado ; ++i)
        {
            // Se o desenho e visivel e esta escutando eventos do mouse
            if((*i)->visivel() && (*i)->escutaMouseEvento(mouseEvento)) // Se o desenho esta escutando tal evento
            {
                if(novoEvento.evento() == MOUSE_MOVENDO || (*i)->contemrPonto(novoEvento.posicaoLocal()))
                {
                    if((*i)->novoMouseEvento(&novoEvento))
                        eventoPropagado = true;
                }
            }
        }
    }


    if(escutaMouseEvento(mouseEvento))
    {
        if(eventoPropagado == true)
        {
            setEscutaMouseMovendo(true);
            setEscutaMouseSolto(true);
            setEscutaMousePrecionado(true);

            /* Não propaga mais o evento,pois ja foi propagado 1 vez
            Porem as escutas devem ser ativadas para que os eventos
            possam ser transmitidos para os desenhos filhos
            */
            if(produzLog)
                cout << "Evento foi propagado" << endl;

        }else
        {// Caso contrario, sempre propaga para mim mesmo
            return Desenho::novoMouseEvento(mouseEvento);
        }
    }
    return eventoPropagado;
}


void Container::ajusta()
{
    int mx = 9999, // menor X
        my = 9999, // menor Y
        Mx = -9999,  // Maior X
        My = -9999,  // Maior Y
        dmx, // Desenho menor X
        dmy, // Desenho menor Y
        dMx, // Desenho Maior X
        dMy; // Desenho Maior Y

    rPonto dp; // Desenho Posicao

    list<Desenho*>::iterator i;
    for(i = filhos.begin(); i != filhos.end() ; i++)
    {
        dp = converteReferencialPai( (*i)->posicaoLocal() );
        dmx = dp.x(), dmy = dp.y();
        dMx = dmx + (*i)->largura() , dMy = dmy + (*i)->altura();

        if(mx > dmx)  mx = dmx;
        if(Mx < dMx)  Mx = dMx;
        if(my > dmy)  my = dmy;
        if(My < dMy)  My = dMy;
    }
    if(mx == -9999 && my == -9999 && Mx == 9999 && My == 9999)
        return;

    rPonto translacao(mx - m_espaco.x(), my - m_espaco.y());

    defineDesenho(rPonto(mx,my), Mx-mx , My-my);

    transladaFilhos(translacao);
}


/**
 * @brief
 *    Ajusta o container para que ele consiga conter o seu desenho filho.
 *    O ajuste pode alterar a largura e o comprimento do Container, assim como pode
 * alterar a sua própria posição, neste caso, a posição de todos os desenhos
 * filhos são alteradas de forma que suas posições globais continuem a mesma.
 *    Este ajuste garante que todos desenhos que estavam contido antes da chamada do
 * metodo continuem contidos.
 * @param d - Desenho que o container esta se adaptando, se este desenho não for
 * filho do container, ele não se ajustara a ele.
 */
void Container::ajustaDesenho(Desenho *desenho)
{
    if(produzLog)
        cout << "Desenho " << getNome().toStdString() << " se ajustando para " << desenho->getNome().toStdString() << endl;

    if(desenho->pai() == this) // Se for meu filho
    {
        // Pega a posição do desenho com referencia no pai (eu)
        rPonto pontoTeste = converteReferencialPai(desenho->posicaoLocal()),
               vetorTranslacao;

        // Pega o vetor de translação dos desenhos
        vetorTranslacao = Desenho::ajustaDesenho(pontoTeste);

        /*
          IMPORTANTE !
            O Desenho que provocou a mudança no container devido a sua alteração
        geometrica deve ser sempre transladado primeiro, caso contrario, um outro
        desenho vai gerar um sinal (devido sua translação), e um novo ajuste podera
        ser realizado, neste caso, o primeiro desenho continuara fora da area do
        container, o que gerara um novo sinal, um novo ajuste, isso se repetira em
        um loop recursivo que ocasinaria uma falha de sgmentação por estouro de pilha
        de função.
        */

        // Verifica se é necessario transladar os desenhos para manter posição global
        if(vetorTranslacao != rPonto(0.0,0.0))
        {
            desenho->translada(vetorTranslacao); // Translada primeiro causador do ajuste
            transladaFilhos(vetorTranslacao, desenho); //Ajusta os desenhos para nova posição do container (Compensação do deslocamento)
        }

        // Calcula da posição superior direita do desenho
        pontoTeste += rPonto(desenho->largura() , desenho->altura());

        vetorTranslacao = Desenho::ajustaDesenho(pontoTeste);
        if(vetorTranslacao != rPonto(0.0,0.0))
        {
            desenho->translada(vetorTranslacao);// Translada primeiro causador do ajuste
            transladaFilhos(vetorTranslacao, desenho); //Ajusta os desenhos para nova posição do container (COmpensação do deslocamento)
        }
    }else
        cout << "Erro ajuste de desenho com pais diferente" << endl;

//    redesenha();
//    Sleep(100);

}


/**
 * @brief
 *  Redimensiona a largura, altura ou posição do container para que ele possa conter um ponto,
 * garantindo que ele continue contendo os mesmos desenhos de antes, sua area não diminui.
 * @param ponto - Ponto que o container se ajustara para conter.
 * @return rPonto - Vetor inverso ao deslocamento dado pelo container para se ajustar.
 */
rPonto Container::ajustaDesenho(const rPonto &ponto)
{
    rPonto vetorTranslacao = Desenho::ajustaDesenho(ponto);

    if(vetorTranslacao != rPonto(0.0,0.0))
        transladaFilhos(vetorTranslacao); //Ajusta os desenhos para nova posição do container
                                          // de forma com que os filhos continue com a mesma
                                          // posição global.
    return vetorTranslacao;
}


/**
 * @brief
 *  Este metodo faz com que a posição de todos desenhos filhos
 * sejam alinhadas.
 */
void Container::alinhar()
{
    int
    dx = largura()/numFilhos(),
    dy = altura()/numFilhos();

    list<Desenho*>::iterator i;
    for(i = filhos.begin() ; i != filhos.end() ; i++)
    {
        if((*i)->tipoDesenho() != TD_ARCO && (*i)->tipoDesenho() != TD_SETA)
        {
            (*i)->setPosicao(rPonto((float) dx*((int)(*i)->x()/dx), (float) dy*((int) (*i)->y()/ dy)));
        }
    }
}


/**
 * @brief
 *  Translada todos vetores filhos, menos o desenho execao.
 * @param vetor - Vetor de translacao que sera aplicado a cada desenho
 * @param execao - Desenho que não sofrera translacao.
 */
void Container::transladaFilhos(const rPonto &vetor, const Desenho *execao)
{
    list<Desenho*>::iterator i;
    for(i = filhos.begin() ; i != filhos.end() ; i++)
    {
        if((*i) != execao)
        {
            (*i)->translada(vetor);
        }
    }
}


/**
 * @brief
 *  Translada todos os desenhos filhos com execao dos desenhos que estão na lista de execao.
 * @param vetor - Vetor de translação que sera aplicado aos desenhos filhos
 * @param execao - Lista de desenhos que não sofreram a translação
 */
void Container::transladaFilhos(const rPonto &vetor, list<Desenho *> &execao)
{
    list<Desenho*>::iterator i;
    list<Desenho*>::iterator j;
    bool taNaLista;
    for( i = filhos.begin() ; i != filhos.end() ; i++)
    {
        taNaLista = false;
        for(j = execao.begin() ; j != execao.end() ; j++)
        {
            if( (*i) == (*j))
                taNaLista = true;
        }
        if(! taNaLista)
        {
            (*i)->translada(vetor);
        }
    }
}


/**
 * @brief
 *  Realiza uma operação de translação em todos os os desenhos filhos
 * @param vetor
 * @param execao
 */
void Container::transladaFilhos(const rPonto &vetor)
{
    list<Desenho*>::iterator i;
    for(i = filhos.begin() ; i != filhos.end() ; i++)
    {
        (*i)->translada(vetor);
    }
}


/**
 * @brief
 * Este metodo implementa uma reação do container quando um de seus desenhos
 * filhos sofre uma alteração de posição.
 * @param desenho - Desenho que sofreu a alteração.
 * @param novaPosicao - Nova posição que o desenho se encontra.
 */
void Container::eventoAlteracaoPosicao(Desenho *desenho)
{
    ajustaDesenho(desenho);
}


/**
 * @brief
 * Este metodo implementa uma reação do container quando um de seus desenhos
 * filhos sofre uma alteração de largura.
 * @param desenho - Desenho que sofreu a alteração.
 * @param novaPosicao - Nova largura do desenho.
 */
void Container::eventoAlteracaoLargura(Desenho *desenho)
{
    ajustaDesenho(desenho);
}

/**
 * @brief
 * Este metodo implementa uma reação do container quando um de seus desenhos
 * filhos sofre uma alteração de altura.
 * @param desenho - Desenho que sofreu a alteração.
 * @param novaPosicao - Nova altura do desenho.
 */
void Container::eventoAlteracaoAltura(Desenho *desenho)
{
    ajustaDesenho(desenho);
}


/**
 * @brief
 *  Desenha todos os desenhos filhos
 */
void Container::desenha()
{
    if(visivel())
    {
        Desenho::desenha();
        desenhaFilhos();
    }
}


/**
 * @brief
 *  Desenha todos os desenhos filhos que estão
 * com o atributo visivel = true.
 */
void Container::desenhaFilhos()
{
    if(!filhos.empty())
    {
        list <Desenho*>::iterator i;
        for( i = filhos.begin() ; i != filhos.end(); i++)
        {
            if((*i)->visivel())
                (*i)->desenha();
        }
    }
}


/**
 * @brief
 *      Retorna o número de filhos do Container.
 * @return int
 */
int Container::numFilhos()
{
    // Obs.: size() em std::list tem complexidade linear!!
    // lento
    return filhos.size();
}


/**
 * @brief
 *      Retorna o ID do container, cada Container possui um ID que é
 * atribuido no momento que ele é criado, não existe dois Containers com o mesmo ID.
 * @return int - ID do Container.
 */
int Container::getContainerID()
{
    return container_mid;
}

void *Container::getSuper()
{
    return this;
}


/**
 * @brief
 *     Define o desenho mestre, que faz a inetrface entre os desenhos e a
 * widget do Qt. Quando um desenho mestre é definido a um Container, automaticamente
 * esse DesenhoMestre é definido para seus filhos.
 * @param desenhoMestre - Desenho mestre que sera definido.
 */
void Container::setMestre(DesenhoMestre *desenhoMestre)
{
    if(filhos.size() > 0)
    {
        list<Desenho*>::iterator i;
        for(i = filhos.begin() ; i != filhos.end() ; ++i)
        {
            (*i)->setMestre(desenhoMestre);
        }
    }
    Desenho::setMestre(desenhoMestre);
}


/**
 * @brief
 *  Este metodo coloca todos os desenhos do container que possuem o ponto
 * na lista passada por parametro.
 * @param ponto - Ponto que sera testado
 * @param lista - Lista que sera preenchida com os desenhos que contem
 * o ponto.
 */
void Container::getDesenho(const rPonto &ponto, list<Desenho *> &lista)
{
    getDesenho(ponto, 0x0, lista);
}


/**
 * @brief
 *  Este metodo coloca todos os desenhos do container, com execao
 * da execao, na lista passada por parametro.
 * @param ponto - Ponto que sera testado.
 * @param execao - Desenho excluido dos testes.
 * @param lista - Lista que sera preenchido com os desenhos que
 * contem o ponto.
 */
void Container::getDesenho(const rPonto &ponto, Desenho *execao, list<Desenho *> &lista)
{
    list<Desenho*>::iterator i;
    for(i = filhos.begin(); i != filhos.end(); i++)
    {
        if((*i) != execao && (*i)->contemrPonto(ponto))
        {
            lista.push_back((*i));
        }
    }
}


/**
 * @brief
 *  Retorna o desenho com id especificado
 * @param id - Id do desenho
 * @return Desenho - Desenho com o ID
 */
Desenho *Container::getDesenho(unsigned id)
{
    unsigned j=0;
    list<Desenho*>::iterator i = filhos.begin();
    while(j != id && i != filhos.end())
    {
        i++;
        j++;
    }
    return (*i);
}


/**
 * @brief
 *  Retorna o primeiro desenho que contem o ponto, ou zero se nenhum desenho for encontrado.
 * @param ponto - Ponto com referencial no container.
 * @return Desenho - Desenho que contem o ponto, ou 0 se nenhum desenho for encontrado.
 */
Desenho *Container::getDesenho(const rPonto &ponto)
{
    list<Desenho*>::iterator i;

    for(i = filhos.begin(); i != filhos.end(); i++)
    {
        if( (*i)->contemrPonto(ponto))
        {
            return (*i);
        }
    }
    return 0x0;
}


/**
 * @brief
 *  Funciona da mesma forma que quegDesenho(), porem com uma exceção,
 * a busca sera feita em todos desenhos filhos do container, menos
 * o da exceção.
 * @param ponto - Ponto que sera testado na busca.
 * @param excecao - Desenho excluido da busca.
 * @return Desenho - Desenho encontrado, ou zero se nenhum foi encontrado.
 */
Desenho *Container::getDesenho(const rPonto &ponto, Desenho *excecao)
{
    list<Desenho*>::iterator i;
    for(i = filhos.begin(); i != filhos.end(); i++)
    {
        if((*i) != excecao && (*i)->contemrPonto(ponto))
        {
            return (*i);
        }
    }
    return 0x0;
}


/**
 * @brief
 *  Remove a seleção de todos os desenhos filhos do container
 */
void Container::removeSelecaoFilhos()
{
    list<Desenho*>::iterator i;
    for( i = filhos.begin() ; i != filhos.end(); i++)
    {
        (*i)->setSelecionado(false);
    }
}

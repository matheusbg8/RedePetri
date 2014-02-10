#include "ListaDesenhos.h"

#define paraCada(elemento, lista) for(elemento = lista.begin() ; elemento != lista.end() ; elemento++)
#define para1Cada(elemento, lista, primeiro)  for( elemento = lista.begin(), primeiro = (*elemento).first ; elemento != lista.end() ; ++elemento , primeiro = (*elemento).first )
#define para2Cada(elemento, lista, primeiro, segundo)  for( elemento = lista.begin(), primeiro = (*elemento).first , segundo = (*elemento).second ; elemento != lista.end() ; ++elemento , primeiro = (*elemento).first , segundo = (*elemento).second )

bool listaDesenhoComparaElemento(const ListaDesenhos::elemento & a, const ListaDesenhos::elemento &b)
{return a.first < b.first;}

/**
 * @brief Constroi a lista de desenhos
 *
 * @param desalocaDesenhos - Define o padrão do comportamento da lista,
 * quando ela for destruido, se os desenhos vão ser desalocados ou não.
 *
 */
ListaDesenhos::ListaDesenhos(bool desalocaDesenhos):
    m_lista(listaDesenhoComparaElemento)
{
    m_desalocaPadrao = desalocaDesenhos;
}


/**
 * @brief Construtor de cópia.
 *
 * @param lista - lista que sera copiada.
 */
ListaDesenhos::ListaDesenhos(const ListaDesenhos &lista)
{
    m_lista = lista.m_lista;
    m_desalocaPadrao = lista.m_desalocaPadrao;
}


/**
 * @brief Destrutor da lista
 * desaloca todos os desenhos que foram adicionados com a opção de
 * desalocar.
 *
 */
ListaDesenhos::~ListaDesenhos()
{
    lista_base::iterator i;
    bool desalocar;
    Desenho *desenho;
    para2Cada(i , m_lista, desenho, desalocar)
    {
        if( desalocar ) // Se for para desalocar o desenho
        {
            delete desenho; // Desaloca
        }
    }
}


/**
 * @brief Informação do tamanho da lista.
 *
 * @return int - Numero de elementos da na lista.
 */
int ListaDesenhos::tamanho() const
{
    return m_lista.size();
}


/**
 * @brief retorna informação se a lista desaloca os desenhos
 * por padrão.
 *
 * @return bool
 */
bool ListaDesenhos::desalocaPadrao()
{
    return m_desalocaPadrao;
}


/**
 * @brief Adiciona um elemento na lista
 *
 * @param desenho - Desenho que sera adicionado
 * @param desalocar - Informa se o desenho que esta
 * sendo adicionado deve ser desalocado ou não, quando
 * a lista for destruida. Se nenhum informação for passada
 * sera usada a opção padrão definida no contrutor da lista.
 */
void ListaDesenhos::adiciona(Desenho *desenho, bool desalocar)
{
    m_lista.insert(make_pair(desenho, desalocar));
}


/**
 * @brief Mesma coisa que adiciona().
 *
 * @param desenho - Desenho que sera adicionado
 */
void ListaDesenhos::adiciona(Desenho *desenho)
{
    adiciona(desenho,m_desalocaPadrao);
}


/**
 * @brief Remove um desenho da lista
 *   Neste caso o desenho não sera desalocado, apenas
 * sera removido da lista.
 * @param desenho - Desenho que sera removido.
 */
void ListaDesenhos::remove(Desenho *desenho)
{
    m_lista.erase(make_pair(desenho,false));

}


/**
 * @brief
 *   Verifica de a lista contem o desenho
 * @param desenho - Desenho que sera testado
 * @return bool - true se o desenho esta dentro da lista,
   false - se o desenho não estiver dentro da lista.
 */
bool ListaDesenhos::contem(Desenho *desenho) const
{
    /// @todo - Pesquisar a utilização do metodo find do std:set
//    if((m_lista.find( make_pair(desenho, false))).operator *() == 0x0)
//            return false;
    return true;


}

/**
 * @brief Retorna uma lista com todos desenhos que contem um ponto
 *
 * @param p - Ponto que sera testado
 * @return ListaDesenhos - Lista com os desenhos que contem o ponto.
 */
ListaDesenhos ListaDesenhos::contemPonto(const rPonto &p)
{
    ListaDesenhos listaResposta; // Lista com os desenhos que contem o ponto
    lista_base::iterator i;
    Desenho *desenho;

    para1Cada(i , m_lista, desenho)
    {
        if(desenho->contemrPonto(p))
            listaResposta.adiciona(desenho);
    }
    return listaResposta;
}


/**
 * @brief Retorna uma lista com todos elemento selecionados.
 *
 * @return ListaDesenhos - Lista de elementos selecionados.
 */
ListaDesenhos ListaDesenhos::selecionados()
{
    ListaDesenhos listaResposta;
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        if(desenho->selecionado())
            listaResposta.adiciona(desenho);
    }
    return listaResposta;
}

void ListaDesenhos::setMovendo(bool movendo)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setMovendo(movendo);
    }
}

void ListaDesenhos::setSelecionado(bool selecionado)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setSelecionado(selecionado);
    }
}

/**
 * @brief Chama o metodo desenha() de todos desenhos da lista.
 *
 */
void ListaDesenhos::desenha()
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->desenha();
    }
}

void ListaDesenhos::setPosicao(const rPonto &novaPosicao)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setPosicao(novaPosicao);
    }
}

void ListaDesenhos::setPosicaoLocal(const rPonto &posicaoLocal)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setPosicaoLocal(posicaoLocal);
    }
}

void ListaDesenhos::setPosicaoGlobal(const rPonto &posicaoGlobal)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setPosicaoGlobal(posicaoGlobal);
    }
}

void ListaDesenhos::setLargura(int novaLargura)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setLargura(novaLargura);
    }
}

void ListaDesenhos::setAltura(int novaAltura)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setAltura(novaAltura);
    }
}

void ListaDesenhos::setVisivel(bool visivel)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setVisivel(visivel);
    }
}

void ListaDesenhos::setCorFundo(const Cor &cor)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setCorFundo(cor);
    }
}

void ListaDesenhos::setCorBorda(const Cor &cor)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->setCorFundo(cor);
    }
}

bool ListaDesenhos::novoMouseEvento(MouseEvento *e)
{
    lista_base::iterator i;
    Desenho *desenho;
    para1Cada(i , m_lista, desenho)
    {
        desenho->novoMouseEvento(e);
    }
}






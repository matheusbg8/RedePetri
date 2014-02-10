#ifndef LISTADESENHOS_H
#define LISTADESENHOS_H

#include <set>
#include <utility>

#include "Desenho.h"

using namespace std;

/**
 * @brief
 *  Esta classe é responsavel por armazenar uma lista
 * de desenhos, ela permite que uma operação seja realizada
 * em todos os desenhos contidos na lista.
 *   Ela utiliza internamente o std:set, grupo da biblioteca padrão c++.
 */
class ListaDesenhos
{
public:
    typedef pair< Desenho *, bool > elemento;
protected:
    typedef set <elemento,bool(*)(const elemento&,const elemento&)> lista_base;

    lista_base m_lista; /**< lista de elementos */
    bool m_desalocaPadrao; /**< Informação padrão de desalocar ou não os elemntos */
public:

    ListaDesenhos(bool desalocaDesenhos = false);
    ListaDesenhos(const ListaDesenhos &lista);
    ~ListaDesenhos();

    /* --------- Informções -------- */
    int tamanho() const;
    bool desalocaPadrao();

    /* -- Operações sobre a lista -- */
    void adiciona(Desenho *desenho, bool desalocar);
    void adiciona(Desenho *desenho);
    void remove(Desenho* desenho);
    bool contem(Desenho* desenho) const;


    /*- Operações de seleções de desenhos -*/
    ListaDesenhos contemPonto(const rPonto &p);
    ListaDesenhos selecionados();

    /*- Operações sobre os desenhos -*/
    void setMovendo(bool movendo);
    void setSelecionado(bool selecionado);
    void desenha();
    void setPosicao(const rPonto & novaPosicao);
    void setPosicaoLocal(const rPonto & posicaoLocal);
    void setPosicaoGlobal(const rPonto & posicaoGlobal);
    void setLargura(int novaLargura);
    void setAltura(int novaAltura);
    void setVisivel( bool visivel);
    void setCorFundo(const Cor &cor);
    void setCorBorda(const Cor &cor);

    bool novoMouseEvento(MouseEvento *e);

};

#endif // LISTADESENHOS_H

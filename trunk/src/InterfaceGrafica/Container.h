#ifndef CONTAINER_H
#define CONTAINER_H

#include "Desenho.h"
#include "Retangulo.h"

/**
         Esta classe é a única classe que pode conter desenhos,
    ela pose conter qualquer tipo de desenho, inclusive um
    outro Container.
**/
class Container : public Desenho
{
private:
    void iniciaContainer();

protected:
    list<Desenho*> filhos;         // Foi utilizado std::list ao invez de QList por causa do reverse_interator
    list<Desenho> desenhoSelecionados;

    static int container_id;
    int container_mid;

    static Container paiDeTodos;

    void desenhaFilhos();

    virtual void eventoAlteracaoPosicao(Desenho *desenho);
    virtual void eventoAlteracaoLargura(Desenho *desenho);
    virtual void eventoAlteracaoAltura(Desenho *desenho);

public:

    Container(Container *m_pai = 0x0);
    Container(rPonto p = rPonto(10,10), int largura = 100, int altura = 100, Container *m_pai = 0x0);
    virtual ~Container();

    // Operações com desenhos
    virtual void novoDesenho(Desenho *d, bool avisaFilho = true);
    virtual void removeDesenho(Desenho *d);
    bool contemDesenho(Desenho *desenho);

//    virtual void setNome(QString nome);

    void deletaDesenhos();

    // Sinais e eventos
    virtual bool novoMouseEvento(MouseEvento *novoMouseEvento);

    void ajusta();
    void ajustaDesenho(Desenho *desenho);
    rPonto ajustaDesenho(const rPonto &ponto);

    void alinhar();

    void transladaFilhos(const rPonto &vetor, const Desenho* execao);
    void transladaFilhos(const rPonto &vetor, list<Desenho *> &execao);
    void transladaFilhos(const rPonto &vetor);

    int numFilhos();

    // Desenhos
    void desenha();

    int getContainerID();
    virtual void *getSuper();

    void setMestre(DesenhoMestre *m_desenhoMestre);

    void getDesenho(const rPonto &ponto, list<Desenho*> &lista);
    void getDesenho(const rPonto &ponto, Desenho *execao, list<Desenho*> &lista);

    Desenho* getDesenho(unsigned id);
    Desenho* getDesenho(const rPonto &ponto);
    Desenho* getDesenho(const rPonto &ponto, Desenho *excecao);

    static Container * getPaiDeTodos();

    // Seleção
    void removeSelecaoFilhos();

};



#endif // CONTAINER_H

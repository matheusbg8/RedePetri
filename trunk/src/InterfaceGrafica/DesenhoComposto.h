#ifndef DESENHOCOMPOSTO_H
#define DESENHOCOMPOSTO_H

#include "Container.h"

/**
         Esta classe é um tipo de container que aceita novos desenhos de duas formas,
     uma é como um container comum, o novo desenhos simplesmente fica dentro desse desenho (contido),
     e a outra é como um componente, neste caso o novo desenho faz parte do DesenhoComposto, como
     se fosse um desenho só. As reações dos Desenhos componentes são determinadas pelo DesenhoComposto
     e geralmente geram efeitos sobre o proprio DesenhoComposto.
**/
class DesenhoComposto : public Container
{
public:
    DesenhoComposto(Container *m_pai = 0x0);
    virtual ~DesenhoComposto();

    void novaComposicao(Desenho *desenho, bool avisaFilho = true);
    void removeComposicao(Desenho *desenho);
    void removeDesenho(Desenho *d);
    bool contemComponente(Desenho *desenho);

    bool contemrPonto(const rPonto &p);

    bool novoMouseEvento(MouseEvento *mouseEvento);

    void ajustaComponentes(Desenho *execao);

    bool mouseEventoComposto(MouseEvento *novoMouseEvento, Desenho *desenho);
    virtual void mousePrecionadoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);
    virtual void mouseSoltoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);
    virtual void mouseMovendoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);

    void transladaComponentes(rPonto &translacao, Desenho *execao);

    int getDesenhoCompostoID();

    virtual void *getSuper();

    void desenha();

protected:
    static int desenhoComposto_id;
    int desenhocompotos_mid;
    void iniciaDesenhoComposto();
    list <Desenho *> componentes; /**  Lista de componentes do desenho */
    void desenhaComponentes();
};

#endif // DESENHOCOMPOSTO_H

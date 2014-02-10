#ifndef SETA_H
#define SETA_H

#include "Segmento.h"
#include "Triangulo.h"
#include "CirculoBasico.h"
#include "DesenhoComposto.h"
#include "DesenhoDeLigacao.h"

/**
 * @brief
 *   Esta classe representa uma seta, ela pode ser utilizada para ligar
 * dois desenhos com os metodos setLigacaoIni(Desenho *desenho) e
 * void setLigacaoFim(Desenho *desenho). O comportamento da seta
 * ao ligarse com um desenho é determinado pelos metodos virtuais
 * ligacaoIni(Desenho* desenho) e ligacaoFim(Desenho* desenho),
 * toda vez que uma ponta da seta é arrasta para cima de um desenho
 * esses metodos são chamados, por padrão eles simplesmente aceitão
 * a ligação com o desenho.
 */
class Seta :
        public DesenhoComposto,
        public DesenhoDeLigacao
{
private:
    void inicializaSeta();

protected:
    Segmento *seg;
    Triangulo *triangulo;

    QString m_nomeSeta;

    Circulo *inicio;
    Circulo *fim;

    float m_comprimentoPonta;
    float m_aberturaPonta;

    Desenho *m_ligFim;
    Desenho *m_ligIni;

    bool m_rastriandoMouse;

    virtual void eventoAlteracaoPosicao(Desenho *desenho);
    virtual void eventoAlteracaoAltura(Desenho *desenho);
    virtual void eventoAlteracaoLargura(Desenho *desenho);

    virtual void eventoDeletando(Desenho *desenho);

    virtual bool aceitaLigacaoIni(Desenho* desenho);
    virtual bool aceitaLigacaoFim(Desenho* desenho);

    void desenhaNome();

public:
    Seta(Container *m_pai = 0x0);
    ~Seta();

    Desenho* novaInstancia() const;

    void defineSeta(const rPonto &pIni, const rPonto &pFim);
    void desenha();

    void novoDesenho(Desenho *d, bool avisaFilho);

    void mousePrecionadoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);
    void mouseSoltoComposto(Desenho *desenho, MouseEvento *novoMouseEvento);
    void mouseMovendoComposto(Desenho *desenho, MouseEvento *mouseEvento);

    bool setLigacaoIni(Desenho *desenho);
    bool setLigacaoFim(Desenho *desenho);

    rPonto posicaoInicial() const;
    rPonto posicaoFinal() const;

    void setNomeSeta(QString nome);

    const Desenho* getLigacaoIni() const;
    const Desenho* getLigacaoFim() const;

    void *getSuper();

    void setSelecionado(bool m_selecionado);

    void comecaRastriamentoFim();
    void comecaRastriamentoInicio();
};

#endif // SETA_H






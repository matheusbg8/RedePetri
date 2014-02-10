#ifndef DESENHO_H
#define DESENHO_H

#include<QtCore>
#include<QtGui>
#include<list>
using namespace std;
#include "mouseevento.h"
#include "Cor.h"
#include "sinal.h"

#include "Definicoes.h"
#include "DesenhoMestre.h"
#include "RetanguloBasico.h"
#include "Utilidades.h"
#include "Evento.h"
#include "TipoDesenho.h"

class Container;
class DesenhoComposto;

class DesenhoMestre;


/**
 \brief Esta é a classe base dos desenhos, suas principais funções são:
\li Determinar quanto de espaço um desenho precisa para ser desenhado (a largura e altura
ocupada pelo desenho).
\li Determina reações básicas a eventos do mouse ou teclado.

-Quando um desenho é clicado, ele é selecionado, o foco do desenhoMestre
muda para esse desenho.\n
-Quando um desenho recebe um movimento do mouse, e este desenho está selecionado,
 a sua posição é alterada para a posição do mouse, até um evento de mouseSolto
for recebido.\n
-Quando o metodo novoDesenho(Desenho *d) é chamado, o novo desenho é repassado
para seu desenho pai, se não houver um desenho pai, esse novo desenho é deletado.
 **/

class Desenho
{
public:
    // Construtores e destrutores
        Desenho(Container *pai = 0x0);
        Desenho(rPonto p , int largura , int altura , Container *m_pai = 0x0);
        virtual ~Desenho();

        /* Interface (deveria ser vitual pura) */
        /* Fabrica */
        virtual Desenho * novaInstancia() const;
protected:
        virtual void copiaMeusParametros(Desenho *d) const;
public:

        /* Metodos de deseho */
        void atualizaVizualizacao();
        virtual void desenha();

        /* Metodo de compatibilidade com containers */
        virtual void novoDesenho(Desenho *d, bool avisaFilho = true);


        /* Metodos de manipulação geometrica */
        bool desenhoContemrPonto(const rPonto &ponto);
        virtual bool contemrPonto(const rPonto &p) const;
        virtual void rotaciona(double ang);
        void translada(const rPonto deslocamento);

        virtual rPonto posicaoLigacao(const rPonto &pInicialReta);

        void defineDesenho(const rPonto &posicao , int largura, int altura );
        void defineDesenho(const RetanguloBasico &retangulo);

        void setX(float XLocal);
        void setY(float YLocal);

        virtual void setPosicao(const rPonto & novaPosicao);
        virtual void setPosicaoLocal(const rPonto & posicaoLocal);
        virtual void setPosicaoGlobal(const rPonto & posicaoGlobal);
        virtual void setLargura(int novaLargura);
        virtual void setAltura(int novaAltura);

        const rPonto &posicaoLocal() const;
        int altura() const;
        int largura() const;

        float x();
        float y();

        virtual void alinhar();

        /* Metodos de tratamento de Sinais e Eventos */
        virtual bool novoMouseEvento(MouseEvento *e);

        /* Metodos de acesso a Propriedades */

        /* Identificador do desenho */
        int id();

        int idDesenho() const;
        void setIdDesenho(int id);

        int idTipoDesenho() const;
        void setIdTipoDesenho(int id);

        int faixaIndexacao() const;
        void setFaixaIndexacao(int faixa);

        bool idDesenhoVisivel() const;
        void setIdDesenhoVisivel(bool simNao);

        /* COR */
        virtual void setCorFundo(const Cor &cor);
        const Cor& corFundo() const;

        virtual void setCorBorda(const Cor &cor);
        const Cor& corBorda() const;

        void setDesenhaFundo(bool simNao);
        bool desenhaFundo() const;

        /* Visibilidade */
        void setVisivel( bool visivel);
        bool visivel() const;

        /*  Nome */
        virtual void setNome(QString nome);
        const QString& getNome() const;

        void setNomeVisivel(bool sinNao);
        bool nomeVisivel() const;

        void setTextoCentro(const string &texto);
        void setTextoCentroVisivel( bool simNao);

        const string textoCentro() const;
        bool textoCentroVisivel() const;

        void setTextoInferior(const string &texto);
        void setTextoInferiorVisivel(bool simNao);

        const string & textoInferior() const;
        bool textoInferiorVisivel() const;

        /* Seleção(foco) */
        virtual void setSelecionado( bool selecionado);
        bool selecionado();

        /* Movimentação */
        virtual void setMovendo( bool movendo);
        bool estaMovendo();

        /* Tipo de desenho e transformações */
        TipoDesenho tipoDesenho();
        virtual void * getSuper();

        /* Metodos de acesso a hirarquia de desenhos */
        virtual void setMestre(DesenhoMestre* mestre);
        void setPai(Container *pai, bool avisaPai = true);
        void setComponente(DesenhoComposto *pai, bool avisaPai);

        Container *pai();
        DesenhoMestre * desenhoMestre();

        bool componente();

        static Desenho* getPaiDeTodos();

        /* Eventos do Mouse */
        void setEscutaMousePrecionado(bool simOuNao);
        void setEscutaMouseSolto(bool simOuNao);
        void setEscutaMouseMovendo(bool simOuNao);
        void setEscutaMouseEvento(bool simOuNao);

        bool escutaMousePrecionado();
        bool escutaMouseSolto();
        bool escutaMouseMovendo();
        bool escutaMouseEvento(MouseEvento *e);


        /* Tratamento de Sinais e Eventos */
        void geraSinal(bool simNao);
        bool geraSinal();

        bool estaEscutando(Desenho *desenho);
        void novaEscuta(Desenho *d);
        void removeEscuta(Desenho *d, bool remocaoDupla = true);
        void removeTodasEscutas();


protected:
    static const bool produzLog = false;

    /* Metodos de desenho */
    void desenhaContainer();
    void desenhaTexto(QString txt,const rPonto &p, const QFont &font = QFont());
    void desenhaNome();
    void desenhaIdDesenho();
    void redesenha();

    /* Geometrico e conversões */
    rPonto minhaPosicaoGlobal() const;
    rPonto converteReferenciaGlobal(const rPonto &pMeuReferencia) const;
    rPonto converteMeuReferencial(const rPonto &pReferenciaDoPai) const;
    rPonto converteReferencialPai(const rPonto &pMeuReferencial) const;
    rPonto referencialP() const;

    virtual rPonto ajustaDesenho(const rPonto &pRefPai);

    /* Eventos do Mouse */
    virtual bool mousePrecionado(MouseEvento *novoMouseEvento);
    virtual bool mouseSolto(MouseEvento *e);
    virtual bool mouseMovendo(MouseEvento *e);

    /* Sinais e Eventos */
    void geraSinal(TipoSinal tipoSinal);

    virtual void eventoAlteracaoPosicao(Desenho *desenho );
    virtual void eventoAlteracaoLargura(Desenho *desenho );
    virtual void eventoAlteracaoAltura(Desenho *desenho );
    virtual void eventoAlteracaoSelecao(Desenho *desenho );
    virtual void eventoDeletando(Desenho *desenho);

    void distribuiSinal(const Sinal &sinal, list<Desenho *> &listaDistribuicao);
    void novoSinal(const Sinal &sinal);

    /* Hierarquia de desenhos */
    void setComponente(bool simNao);

    /* Compatibilidade com Qt*/
    QWidget* widget();

/*Vai para utilidades */    void rotacionarPonto(rPonto &centro, rPonto *p, double ang);

/* Atributos */
    bool movendo;  /**< Determina se o desenho esta movendo ou não */

    /* Controle de desenhos */
    static int desenho_id;  /**< Controle de ids dos desenhos*/
    int desenho_mid;        /**< ID especifico do desenho */

    /* Tipo do desenho (usado para transformação) */
    TipoDesenho m_tipoDesenho;  /**< Determina o tipo do desenho */

    /* Identificacao */
    int m_idTipoDesenho;
    int m_idDesenho;
    int m_faixaIndexacao;
    bool m_idDesenhoVisivel;
    string m_textoInferior;
    string m_textoCentro;

    /* Geometrico */
    RetanguloBasico m_espaco;  /**< Define a posição e o espaço que o desenho ocupa na tela */

    /* COR */
    Cor m_corFundo; /**< Informa a cor de fundo do desenho */
    Cor m_corBorda;  /**< Informa a cor da borda do desenho */
    bool m_desenhaFundo;

    /* Visibilidade */
    bool m_visivel; /**< Informa se o desenho é visivel ou não */    
    bool m_textoCentroVisivel;  /**< Informa de vai ser renderizado o texto central do desenho */
    bool m_textoInferiorVisivel;  /**< Informa se vai ser renderizado o texto inferior do desenho */

    /* Nome */
    bool m_nomeVisivel;  /**< Determina se o nome do desenho é visivel ou não */
    QString m_nome;      /**< Nome do desenho. */

    /* Seleção Foco */
    bool m_selecionado;  /**< Determina se o desenho esta selecionado pelo usuario ou não */

    /* Eventos do Mouse */
    bool escutaEventoMousePrecionado; /**< Escuta ou nao escuta um evento de mouse precionado */
    bool escutaEventoMouseSolto; /**< Escuta ou nao os evento mouse solto */
    bool escutaEventoMouseMovendo; /**< Escuta ou nao os eventos de mouse movendo */
    rPonto dDifPosicaoLocalClique;  /**< Utilizado para corrigir posição de clique com o mouse */

    /* Sinais e Eventos */
    list<Desenho*> m_escutas;  /**< Lista de todos os desenhos que estão me escutando */
    bool m_geraSinal;

    /* Hierarquia de desenhos */
    DesenhoMestre *m_desenhoMestre; /**< Desenho mestre deste desenho. */
    Container *m_pai;                /**< Desenho pai. */
    bool m_componente;  /**< Determina se o desenho é parte de um desenho composto ou não */

private:
    void inicializaDesenho(const rPonto &posicao, int largura, int altura, Container *pai);

    bool f_distribuindoSinal;  /**< Flag utilizada para indicar se esta sendo propagado sinal para escutas*/
    list<Desenho*> listaDesenhosTemporarios;  /**< Lista utilizada para armazenar desenhos temporariamente */
};

#endif // DESENHO_H

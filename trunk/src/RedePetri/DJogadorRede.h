#ifndef DJOGADORREDE_H
#define DJOGADORREDE_H


#include "ContainerGenerico.h"
#include <JogadoRrede.h>
#include <Ambiente.h>
#include <EscutaJogadorRede.h>
#include <VisualizacaoAmbiente.h>
#include "DNodo.h"
#include "DRedePetri.h"

class DJogadorRede :
        public QObject,
        public EscutaJogadorRede,  // Recebe alteracoes do jogador
        public ContainerGenerico
{
    Q_OBJECT
private:
    enum ElementosGraficosJogadorrede
    {
        jrARCO = 0,
        jrVARIAVEL = 1,
        jrPERGUNTA = 2,
        jrACAO = 3,
        jrGATILHO = 4
    };

    CAmbiente *m_CAmbiente;
    ControladorRede *m_controleRede;
    DRedePetri *m_visualizacaoRede;
    JogadorRede *m_jogador;
    QTimer *m_relogio;

    bool m_redesenhaACadaAlteracao; // Redesenha a cada alteracao do ambiente ou do jogador

    bool m_execucaoTemporizada; // Ativa a a execucao do jogador a cada intervalo de tempo

    void iniciaDJogadorRede();
    void iniciaContainerGenerico();

    // Acoes
    QAction *actExecuta;
    QAction *actNovoElemento;
    QAction *actInicia;
    QAction *actNovaVariavel;
    QAction *actNovaPergunta;
    QAction *actNovaAcao;
    QAction *actAmbienteExterno;
    QAction *actAmbienteExternoROS;
    QAction *actDeletaElemento;
    QAction *actNovaRelacao;
    QAction *actExecucaoAutomatica;
    QAction *actExecucaoTemporizada;
    QAction *actCarregaXML;
    QAction *actGeraXML;
    QAction *actExecutaElemento;
    QAction *actAlteraValor;

    // Menu
    QMenu *mnuFundo, *mnuElementosGraficos;

    int m_idDesenhoFoco, m_idTipoDesenhoFoco;

    void criaAcoes();
    void criaMenus();

public:
    DJogadorRede();
    ~DJogadorRede();


// Interface de escuta do ambiente
    // Criacao
    void novaVariavel(unsigned idNodo, const string& nome,  const string& valor);
    void novaPergunta(unsigned idNodo, const string& nome, const string& valor);
    void novaAcao(unsigned idNodo, const string& nome, const string& valor);

    // Alteracao
    void alteracaoNome(const string &nome);
    bool alteracaoValor(unsigned idNodo, const string& valor);

    // Remocao
    void removeVariavel(unsigned idNodo);
    void removePergunta(unsigned idNodo);
    void removeAcao(unsigned idNodo);
    void removeRelacao(unsigned idRelacao);
    void removeTudo();

// Interface JogadorRede

    void novaTransicao(unsigned id);
    void removeTransicao(unsigned id);
    void novaRelacaoPergunta(unsigned idTransicao, unsigned idPergunta, int idRelacao);
    void novaRelacaoAcao(unsigned idTransicao, unsigned idAcao, int idRelacao);
    void reiniciaJogadorRede();

// Interface Containet Generico

    void mousePrecionado(MouseEvento *me, int idTipoDesenho , int idDesenho);
    void mouseSolto(MouseEvento *me, int idTipoDesenho , int idDesenho);
    int ligacao(int deId, int deIdTipo, int paraId,int paraIdTipo);


public slots:
    void inicia();
    void novoElemento();
    void executa();
    void novaVariavel();
    void novaPergunta();
    void novaAcao();
    void iniciaComunicacaoAmbienteExterno();
    void iniciaComunicacaoAmbienteExternoROS();
    void deletaElemento();
    void novaRelacao();
    void execucaoAutomatica();
    void execucaoTemporizada();
    void geraXML();
    void carregaXML();
    void executaElemento();
    void alteraValor();

};

#endif // DJOGADORREDE_H

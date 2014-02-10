#ifndef JOGADORREDE_H
#define JOGADORREDE_H

#include "IVRedePetri.h"
#include "ControladorRede.h"
#include "CAmbiente.h"
#include "VisualizacaoAmbiente.h"
#include "EscutaJogadorRede.h"
#include "GerenciadorElementos.h"

/**
 * @brief
 *  Esta classe é utilizada como um motor de inferencia
 * paras  redes de petri, ela é responsavel pelas
 * associações do ambiente com o modelo de Rede de Petri.
 *  Sua função é fazer com que a rede evolua conforme
 * as informações do ambiente, através de condições lógicas
 * sobre as váriaveis de ambiente. Uma tabela que relaciona
 * as transições com um conjunto de condições é armazenada
 * internamente, a cada modificação do ambiente, o JogadorRede
 * requisita todas as transições sensibilizadas do modelo
 * de Rede de Petri e executa todas as condições associadas
 * a essas transições, todas as condições que forem satisfeitas
 * pelas variaveis de ambiente são disparadas.
 *  Quando uma transição é disparada, uma ação associada aquela
 * transição também é executada pelo JogadorRede, essa ação
 * pode ser repassada para o Ambiente, ou pode ser
 * um conjunto de instruções (operações) realizadas pelo
 * JogadorRede no ambiente alterando diretamente o estado do Ambiente.
 */
class JogadorRede:
        public IVRedePetri,
        public VisualizacaoAmbiente
{
private:
    enum TipoRelacao
    {
        jrRELACAO_ACAO,
        jrRELACAO_PERGUNTA
    };

    vector // Indice representa o ID da transicao
    <
       pair
       <
         list< unsigned > , // Condicoes
         list< unsigned >   // Acoes
       >
    > m_mapaTransicao;

    bool m_execucaoAutomatica;

    GerenciadorElementos < pair<
                            unsigned , // Transicao de origem
                            pair < TipoRelacao, // Tipo Ligacao
                           list<unsigned>::iterator > > // Destino
                        > m_indexacaoRelacoes; // Indexa as relacoes entre transicao e condicao ou acao

    list<EscutaJogadorRede*> m_visualizacoes;

    ControladorRede *m_controladorRede;
    CAmbiente *m_controleAmbiente;

    void atualizaEscuta(EscutaJogadorRede *escuta);

public:
    JogadorRede();
    ~JogadorRede();

    void iniciaJogadorRede();

    void setControladorRede(ControladorRede * controlador);
    void setControladorAmbiente(CAmbiente * ambiente);

    void loop();

    int relacionaPergunta( int idTransicao, int idPergunta);
    int relacionaAcao( int idTransicao, int idAcao);
    bool removeRelacao( int idRelacao);

    void adicionaEscuta(EscutaJogadorRede * escuta);
    void removeEscuta(EscutaJogadorRede *escuta);

    const vector // Indice representa o ID da transicao
    <
       pair
       <
         list< unsigned > , // Condicoes
         list< unsigned >   // Acoes
       >
    > & relacoes() const;


    bool execucaoAutomatica() const;
    void setExecucaoAutomatica(bool simNao);

    /* Interface visualizacao RP  */
    // Edicao
    void dNovoLugar(unsigned id);
    void dNovaTransicao(unsigned id);
    void dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso);
    void dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso);

    void dDeletaTransicao(unsigned id);
    void dDeletaLugar(unsigned id);
    void dDeletaArco(unsigned id);

    void dSetPesoArco(unsigned id, unsigned peso);

    void dSetFichas(unsigned id, unsigned numFichas);

    // Consulta
    unsigned dPesoArco(unsigned id);
    unsigned dFichas(unsigned id);

    // Controle
    void dExecutaTransicao(unsigned id);


    /* Interface do Ambiente */
    /*
     * Esta interface serve para avisar o jogador da rede
     * de todos os acontecimentos do ambiente.
    */

    // Criacao
    void novaVariavel(unsigned idNodo, const string& nome, const string& valor);
    void novaPergunta(unsigned idNodo, const string& nome, const string& valor);
    void novaAcao(unsigned idNodo, const string& nome, const string& valor);

    // Alteracao
    void alteracaoNome(const string&nome);
    bool alteracaoValor(unsigned idNodo, const string& valor);

    // Remocao
    void removeVariavel(unsigned idNodo);
    void removePergunta(unsigned idNodo);
    void removeAcao(unsigned idNodo);
    void removeTudo();

};

#endif // JOGADORREDE_H

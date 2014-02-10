#ifndef ESCUTAJOGADORREDE_H
#define ESCUTAJOGADORREDE_H

#include "VisualizacaoAmbiente.h"

/**
 * @brief
 *  Esta é a interface de comunicação do jogador
 * da rede. Ela é responsável por avisar todas as
 * classes dos eventos que ocorrem no jogador,
 * que são, uma nova transicao foi criada,
 * uma transicao foi removida, e uma transicao
 * foi disparada
 *
 */
class EscutaJogadorRede: public VisualizacaoAmbiente
{
 public:

    /**
     * @brief
     *  Este metodo é chamado toda vez que um transicao é criada no modelo.
     * @param id - ID da transicao criada no modelo
     */
    virtual void novaTransicao(unsigned id) = 0;


    /**
     * @brief
     *  Este metodo é chamado toda vez que uma transicao é removida do modelo
     * @param id - ID da trabsicao removida do modelo
     */
    virtual void removeTransicao(unsigned id) = 0;


    /**
     * @brief
     *  Este metodo é chamado toda vez que é associado uma relação
     * entre uma transicao e uma pergunta
     * @param idTransicao - id relacao
     * @param idPergunta - id da pergunta
     */
    virtual void novaRelacaoPergunta(unsigned idTransicao, unsigned idPergunta, int idRelacao) = 0;

    /**
     * @brief
     *  Este metodo é chamado toda vez que é associado uma relação
     * entre uma transicao e uma acao.
     * @param idTransicao - id relacao
     * @param idAcao - ID da acao.
     */
    virtual void novaRelacaoAcao(unsigned idTransicao, unsigned idAcao, int idRelacao) = 0;


    /**
     * @brief
     *  Este metodo é chamado no momento do registro de escuta,
     * é utilizado para deicha a escuta em um estado zerado,
     * sem nenhum elemento.
     */
    virtual void reiniciaJogadorRede() = 0;


    // === Interface Ambiente ====

    // Criacao
    /**
     * @brief
     *  Metodo chamado quando uma novavariavel é criado no ambiente
     * @param id - id da variavel criada.
     * @param nome - nome da variavel criada.
     * @param valor - valor da variavel criada.
     */
    virtual void novaVariavel(unsigned idNodo, const string& nome, const string& valor) = 0;


    /**
     * @brief
     *  Metodo chamado quando uma pergunta é criada
     * @param id - ID da pergunta criada.
     * @param nome - Nome da pergunta criada.
     * @param valor Valor da variavel criada.
     */
    virtual void novaPergunta(unsigned idNodo, const string& nome, const string& valor) = 0;


    /**
     * @brief
     *  Metodo chamado quando uma nova acao é criada.
     * @param id - ID da acao criada.
     * @param nome - Nome da acao criada.
     * @param acao - Valor da acao criada.
     */
    virtual void novaAcao(unsigned idNodo, const string& nome, const string& valor) = 0;

    // Alteracao
    /**
     * @brief
     *  Metodo chamado quando o modelo observado sofre uma alteracao de nome
     * @param nome - Novo nome do modelo
     */
    virtual void alteracaoNome(const string&nome) = 0;

    /**
     * @brief
     *  Metodo chamado quando algum nodo do ambiente é alterado.
     *  O valor é interpretado como uma condição se o nodoAmbiente for
     * uma pergunta, uma instrucao, se o nodoAmbiente for uma Acao e
     * o valor de uma variavel se o nodo for uma Variavel.
     * @param id - ID do nodo.
     * @param valor - Novo valor do nodo.
     * @return bool -
     */
    virtual bool alteracaoValor(unsigned idNodo,const string& valor) = 0;


    // Remocao

    /**
     * @brief
     *  Método chamado quando uma variavel é removida do ambiente.
     * @param idNodo - ID da variável.
     */
    virtual void removeVariavel(unsigned idNodo) = 0;

    /**
     * @brief
     *  Método chamado quando uma pergunta é removida do ambiente.
     * @param idNodo - ID da pergunta.
     */
    virtual void removePergunta(unsigned idNodo) = 0;


    /**
     * @brief
     *  Método chamado quando uma ação é removida do ambiente.
     * @param idNodo - ID da açao removida.
     */
    virtual void removeAcao(unsigned idNodo) = 0;


    /**
     * @brief
     *  Metodo chamado quando uma relacao foi removida do jogador
     * da rede.
     * @param idRelacao - ID da relacao que foi removida.
     */
    virtual void removeRelacao(unsigned idRelacao) = 0;

    /**
     * @brief
     *  Metodo chamado quando todos nodos do ambiente foram apagados
     */
    virtual void removeTudo() = 0;

};

#endif // ESCUTAJOGADORREDE_H

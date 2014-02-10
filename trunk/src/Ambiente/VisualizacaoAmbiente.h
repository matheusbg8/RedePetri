#ifndef VISUALIZACAOAMBIENTE_H
#define VISUALIZACAOAMBIENTE_H

#include<string>

using namespace std;


/**
 * @brief
 *  Esta classe abstrata é a interface de
 * comunicacao do ambiente com os outros
 * objetos, ela preve uma interface para
 * todos os possiveis acontecimentos no
 * ambiente
 */
class VisualizacaoAmbiente
{
public:
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
     *  Metodo chamado quando todos nodos do ambiente foram apagados
     */
    virtual void removeTudo() = 0;
};


#endif // VISUALIZACAOAMBIENTE_H

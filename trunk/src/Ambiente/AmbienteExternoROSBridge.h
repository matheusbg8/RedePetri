#ifndef AMBIENTEEXTERNOROSBRIDGE_H
#define AMBIENTEEXTERNOROSBRIDGE_H


#include "ROSBridge/ROSBridge.h"
#include "VisualizacaoAmbiente.h"
#include "CAmbiente.h"
#include <map>

class AmbienteExternoROSBridge:
        public EscutaRosBridge,
        public VisualizacaoAmbiente
{
protected:
    RosBridge m_ros;
    CAmbiente *m_controleAmbiente;
    map<string , int> m_mapaTopico2ID;
    map<int , string> m_mapaID2Topico;
    static string vazia;

    void configuraAmbienteROS();
    void registraNodo(int id, const string &nome);

    const string &nomeNodo(int id, bool *monitorado = 0x0) const;
    int idNodo(const string & nome) const;
public:
    AmbienteExternoROSBridge();


    void inicia(CAmbiente *controelAmbiente);


    // Interface com Ambiente
    // Criacao
    /**
     * @brief
     *  Metodo chamado quando uma novavariavel é criado no ambiente
     * @param id - id da variavel criada.
     * @param nome - nome da variavel criada.
     * @param valor - valor da variavel criada.
     */
    void novaVariavel(unsigned idNodo, const string& nome, const string& valor);


    /**
     * @brief
     *  Metodo chamado quando uma pergunta é criada
     * @param id - ID da pergunta criada.
     * @param nome - Nome da pergunta criada.
     * @param valor Valor da variavel criada.
     */
    void novaPergunta(unsigned idNodo, const string& nome, const string& valor);


    /**
     * @brief
     *  Metodo chamado quando uma nova acao é criada.
     * @param id - ID da acao criada.
     * @param nome - Nome da acao criada.
     * @param acao - Valor da acao criada.
     */
    void novaAcao(unsigned idNodo, const string& nome, const string& valor);

    // Alteracao
    /**
     * @brief
     *  Metodo chamado quando o modelo observado sofre uma alteracao de nome
     * @param nome - Novo nome do modelo
     */
    void alteracaoNome(const string&nome);

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
    bool alteracaoValor(unsigned idNodo,const string& valor);


    // Remocao

    /**
     * @brief
     *  Método chamado quando uma variavel é removida do ambiente.
     * @param idNodo - ID da variável.
     */
    void removeVariavel(unsigned idNodo);

    /**
     * @brief
     *  Método chamado quando uma pergunta é removida do ambiente.
     * @param idNodo - ID da pergunta.
     */
    void removePergunta(unsigned idNodo);


    /**
     * @brief
     *  Método chamado quando uma ação é removida do ambiente.
     * @param idNodo - ID da açao removida.
     */
    void removeAcao(unsigned idNodo);

    /**
     * @brief
     *  Metodo chamado quando todos nodos do ambiente foram apagados
     */
    void removeTudo();


    // Interface com ROSBridge

    void conectado();
    void desconectado();
    void recebidoMsg(const MensagemROS & msg);
};

#endif // AMBIENTEEXTERNOROSBRIDGE_H

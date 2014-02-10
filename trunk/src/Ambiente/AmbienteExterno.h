#ifndef AMBIENTEEXTERNO_H
#define AMBIENTEEXTERNO_H

#include"ComunicadorTCP.h"
#include "VisualizacaoAmbiente.h"
#include "CAmbiente.h"

/**
 * @brief
 *  Esta classe é responsavel pela comunicacao do ambiente
 * com o mundo externo através de mensagens TCP/IP
 */
class AmbienteExterno:
        public VisualizacaoAmbiente,
        public EscutaComunicadorTCP
{
protected:
    ComunicadorTCP m_comunicador;
    CAmbiente *m_controleAmbiente;
public:
    AmbienteExterno(const char *ip, int porta);
    ~AmbienteExterno();

    bool inicia(CAmbiente *controleAmbiente);

    // Criacao
    void novaVariavel(unsigned idNodo, const string& nome, const string& valor);
    void novaPergunta(unsigned idNodo, const string& nome, const string& valor);
    void novaAcao(unsigned idNodo, const string& nome, const string& valor);

    // Alteracao
    void alteracaoNome(const string&nome);
    bool alteracaoValor(unsigned idNodo,const string& valor);

    // Remocao
    void removeVariavel(unsigned idNodo);
    void removePergunta(unsigned idNodo);
    void removeAcao(unsigned idNodo);
    void removeTudo();

    // Interface Escuta ComunicadorTCP
    void novaMensagem(istream &msg);
    void conexaoPerdida();
};

#endif // AMBIENTEEXTERNO_H

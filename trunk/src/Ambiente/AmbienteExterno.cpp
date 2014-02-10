#include "AmbienteExterno.h"

AmbienteExterno::AmbienteExterno(const char *ip, int porta)
{
    m_comunicador.conecta(ip,porta);
    m_controleAmbiente = 0x0;
}

AmbienteExterno::~AmbienteExterno()
{
    cout << "Destruindo ambient externo" << endl;

    if(m_controleAmbiente != 0x0)
    {
        m_controleAmbiente->removeVisualizacao(this);
        m_controleAmbiente = 0x0;
    }
}

bool AmbienteExterno::inicia(CAmbiente *controleAmbiente)
{
    cout << "Iniciando Ambiente externo TCP" << endl;
    if(m_comunicador.conectado())
    {
        m_controleAmbiente = controleAmbiente;
        controleAmbiente->addVisualizacao(this);
        m_comunicador.adcionaEscuta(this);
        return true;
    }
    cout << "Erro ao iniciar ambiente externo, nao foi possivel estabelecer conexao" << endl;
}


/**
 * @brief
 *  Metodo chamado quando uma novavariavel é criado no ambiente
 * @param id - id da variavel criada.
 * @param nome - nome da variavel criada.
 * @param valor - valor da variavel criada.
 */
void AmbienteExterno::novaVariavel(unsigned idNodo, const string &nome, const string &valor)
{
    m_comunicador.envia() << " NovaVariavel " << idNodo << " " << nome << " " << valor;
    m_comunicador.enviaPacote();

}

/**
 * @brief
 *  Metodo chamado quando uma pergunta é criada
 * @param id - ID da pergunta criada.
 * @param nome - Nome da pergunta criada.
 * @param valor Valor da variavel criada.
 */
void AmbienteExterno::novaPergunta(unsigned idNodo, const string &nome, const string &valor)
{
    m_comunicador.envia() << " NovaPergunta " << idNodo << " " << nome << " " << valor;
    m_comunicador.enviaPacote();

}

/**
 * @brief
 *  Metodo chamado quando uma nova acao é criada.
 * @param id - ID da acao criada.
 * @param nome - Nome da acao criada.
 * @param acao - Valor da acao criada.
 */
void AmbienteExterno::novaAcao(unsigned idNodo, const string &nome, const string &valor)
{
    m_comunicador.envia() << " NovaAcao " << idNodo << " " << nome << " " << valor;
    m_comunicador.enviaPacote();

}

/**
 * @brief
 *  Metodo chamado quando o modelo observado sofre uma alteracao de nome
 * @param nome - Novo nome do modelo
 */
void AmbienteExterno::alteracaoNome(const string &nome)
{
    m_comunicador.envia() << " AlteracaoNome " << nome;
    m_comunicador.enviaPacote();

}

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
bool AmbienteExterno::alteracaoValor(unsigned idNodo, const string &valor)
{
    m_comunicador.envia() << " AlteracaoValor " << idNodo << " " << valor;
    m_comunicador.enviaPacote();

}

/**
 * @brief
 *  Método chamado quando uma variavel é removida do ambiente.
 * @param idNodo - ID da variável.
 */
void AmbienteExterno::removeVariavel(unsigned idNodo)
{
    m_comunicador.envia() << " RemoveVariavel " << idNodo;
    m_comunicador.enviaPacote();

}

/**
 * @brief
 *  Método chamado quando uma pergunta é removida do ambiente.
 * @param idNodo - ID da pergunta.
 */
void AmbienteExterno::removePergunta(unsigned idNodo)
{
    m_comunicador.envia() << " RemovePergunta " << idNodo;
    m_comunicador.enviaPacote();
}


/**
 * @brief
 *  Método chamado quando uma ação é removida do ambiente.
 * @param idNodo - ID da açao removida.
 */
void AmbienteExterno::removeAcao(unsigned idNodo)
{
    m_comunicador.envia() << " RemoveAcao " << idNodo;
    m_comunicador.enviaPacote();
}

/**
 * @brief
 *  Metodo chamado quando todos nodos do ambiente foram apagados
 */
void AmbienteExterno::removeTudo()
{
    m_comunicador.envia() << " RemoveTudo";
    m_comunicador.enviaPacote();
}

void AmbienteExterno::novaMensagem(istream &msg)
{
    string cmd, nome, valor;
    int i;

    while(!msg.eof())
    {
        msg >> cmd;
        cout << "Recebeu comando " << cmd << endl;

        if(cmd == "NV") // Nova variavel
        {
            msg >> nome >> valor;
            m_controleAmbiente->novaVariavel(nome, valor);
        }else if( cmd == "AV") // Alteracao valor
        {
            msg >> i >> valor;
            m_controleAmbiente->setVariavel(i , valor);
        }else if( cmd == "NP") // Nova Pergunta
        {
            msg >> nome >> valor;
            m_controleAmbiente->novaPergunta(nome, valor);
        }else if( cmd == "NA") // Nova Acao
        {
            msg >> nome >> valor;
            m_controleAmbiente->novaAcao(nome, valor);
        }else if(cmd == "RV")
        {
            msg >> i;
            m_controleAmbiente->removeVariavel(i);
        }else if(cmd == "RP")
        {
            msg >> i;
            m_controleAmbiente->removePergunta(i);
        }else if(cmd == "RA")
        {
            msg >> i;
            m_controleAmbiente->removeAcao(i);
        }
    }
}

void AmbienteExterno::conexaoPerdida()
{
    cout << "Conexao com ambiente externo perdida" << endl;


    // Se mata, não existe outra referencia para desalocacao no codigo
//    delete this;
}

#include "AmbienteExternoROSBridge.h"
#include "ROSBridge/ROSBridgeJSON.h"
#include "ConfiguracaoAmbienteROS.h"

string AmbienteExternoROSBridge::vazia;

void AmbienteExternoROSBridge::configuraAmbienteROS()
{
    bool ok;
    QString endereco = QInputDialog::getText(0x0, QString("Configuracao ROSBridge"), QString("Endereco:"), QLineEdit::Normal, "ws://localhost:9090", &ok);
    endereco = endereco.trimmed();
    if (ok && !endereco.isEmpty())
    {
        string ip;
        int porta;
        if (endereco.contains(QRegExp(QLatin1String(":([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{1,4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$"))))
        {
            QStringList splitted = endereco.split(':');
            porta = splitted.takeLast().toUInt();
            ip = splitted.join(":").toStdString();
        }
        else
        {
            ip = endereco.toStdString();
            porta = 80;
        }
        cout << "IP: " << ip << " porta " << porta << endl;

        m_ros.conecta(ip, porta);
    }
}

void AmbienteExternoROSBridge::registraNodo(int id, const string& nome)
{
    m_mapaTopico2ID.insert(make_pair(nome , id));
    m_mapaID2Topico.insert(make_pair(id, nome));
}

const string &AmbienteExternoROSBridge::nomeNodo(int id, bool *monitorado) const
{
    map<int, string>::const_iterator i = m_mapaID2Topico.find(id);

    if(i == m_mapaID2Topico.end())
    {
        if(monitorado != 0x0)
            *monitorado = false;
        return vazia;
    }
    if(monitorado != 0x0)
        *monitorado = true;

    return i->second;
}

int AmbienteExternoROSBridge::idNodo(const string &nome) const
{
    map<string , int>::const_iterator i = m_mapaTopico2ID.find(nome);
    if(i == m_mapaTopico2ID.end())
        return -1;
    return i->second;
}

AmbienteExternoROSBridge::AmbienteExternoROSBridge()
{
    configuraAmbienteROS();
}

void AmbienteExternoROSBridge::inicia(CAmbiente *controelAmbiente)
{
    list<string> lista;

    // Consulta a lista de topicos
    m_ros.listaTopicos(lista);

    // Pergunta quais topicos seram munitorados
    ConfiguracaoAmbienteROS d(lista);
    d.exec();

    m_controleAmbiente = controelAmbiente;

    // Se registrando no ROS
    m_ros.adicionaEscuta(this);

    // Cria os topicos no ambiente
    list<string>::iterator i;
    for(i = lista.begin() ; i != lista.end() ; i++)
    {
        // Acessa o topico subcribe
        m_ros.escutaTopico(*i);

        (*i).erase(0,1); // Remove a barra do topico '/' (nao pode existir variaveis que comecem com barra pqsao identificadas como operador de divisao

        // Variavel
        registraNodo(
        m_controleAmbiente->novaVariavel((*i),"false"),
        *i );

        // Acoes
        m_controleAmbiente->novaAcao("Ativa_" + *i , (*i) + "=true");
        m_controleAmbiente->novaAcao("Desativa_" + *i , (*i) + "=false");

        // Perguntas
        m_controleAmbiente->novaPergunta(*i + "_Atiado", *i+"==true");
        m_controleAmbiente->novaPergunta(*i + "_Desativado", *i+"==false");
    }

    // Se registrando no ambiente
    m_controleAmbiente->addVisualizacao(this);
}

void AmbienteExternoROSBridge::novaVariavel(unsigned idNodo, const string &nome, const string &valor)
{
}

void AmbienteExternoROSBridge::novaPergunta(unsigned idNodo, const string &nome, const string &valor)
{
}

void AmbienteExternoROSBridge::novaAcao(unsigned idNodo, const string &nome, const string &valor)
{
}

void AmbienteExternoROSBridge::alteracaoNome(const string &nome)
{
}

bool AmbienteExternoROSBridge::alteracaoValor(unsigned idNodo, const string &valor)
{
    bool monitorando;
    string nome;
    nome = nomeNodo(idNodo, &monitorando);

    if(monitorando)
    {
        m_ros.publica(nome, "{\"data\": " +valor+"}");
    }
}

void AmbienteExternoROSBridge::removeVariavel(unsigned idNodo)
{
}

void AmbienteExternoROSBridge::removePergunta(unsigned idNodo)
{
}

void AmbienteExternoROSBridge::removeAcao(unsigned idNodo)
{
}

void AmbienteExternoROSBridge::removeTudo()
{
}

void AmbienteExternoROSBridge::conectado()
{
}

void AmbienteExternoROSBridge::desconectado()
{
}

void AmbienteExternoROSBridge::recebidoMsg(const MensagemROS &msg)
{
    string str;
    str = msg.origem();

    if(str.at(0)=='/')
        str.erase(0,1);

    int id = idNodo(str);

    if(id < 0)
        return;

    // Considerando que todas msgs possuem o campo data
    string stdMsg = ROSBridgeJSON::JSONextraiCampoBool(msg.msg(),string("data"));
    m_controleAmbiente->setVariavel(id,stdMsg);
}

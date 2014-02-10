#include "DJogadorRede.h"
#include <DRedePetri.h>
#include "DialogGenerico.h"
#include "AmbienteExterno.h"
#include "CirculoBasico.h"
#include "Ambiente/AmbienteExternoROSBridge.h"

void DJogadorRede::iniciaDJogadorRede()
{
    m_jogador = 0x0;
    m_CAmbiente = 0x0;
    m_controleRede = 0x0;
    m_visualizacaoRede = 0x0;
    m_idDesenhoFoco = -1;
    m_idTipoDesenhoFoco = -1;
    m_redesenhaACadaAlteracao = true;
    m_execucaoTemporizada = false;
    m_relogio = new QTimer(this);

    QObject::connect(m_relogio, SIGNAL(timeout()), this, SLOT(executa()));

    iniciaContainerGenerico();
    criaAcoes();
    criaMenus();
}

void DJogadorRede::iniciaContainerGenerico()
{
    Seta *s = 0x0;

    s = new Seta();
    s->setNomeVisivel(false);
    defineSeta(s, jrARCO , 0);

    Circulo *c = 0x0;

    c = new Circulo( 10 , rPonto(30,30));
    c->setCorFundo(Cor::azul);
    c->setTextoCentroVisivel(true);
    c->setTextoCentro(string("V"));
    c->setTextoInferiorVisivel(true);
    c->setNomeVisivel(true);
    adicionaDesenhoNaFabrica(c, jrVARIAVEL, 1);

    c = new Circulo( 15 , rPonto(30,30));
    c->setCorFundo(Cor::verde);
    c->setTextoCentroVisivel(true);
    c->setTextoCentro(string("?"));
    c->setNomeVisivel(true);
    adicionaDesenhoNaFabrica(c, jrPERGUNTA, 1);

    c = new Circulo( 15 , rPonto(30,30));
    c->setCorFundo(Cor::amarelo);
    c->setTextoCentroVisivel(true);
    c->setTextoCentro(string("A"));
    c->setNomeVisivel(true);
    adicionaDesenhoNaFabrica(c, jrACAO, 1);

    Retangulo *r = new Retangulo(rPonto(30,30),40,10);
    r->setCorFundo(Cor::verde);
    r->setNomeVisivel(true);
    adicionaDesenhoNaFabrica(r, jrGATILHO, 2);
}

void DJogadorRede::criaAcoes()
{
    actExecuta = new QAction("Executa" , this);
    QObject::connect(actExecuta, SIGNAL(triggered()), this, SLOT(executa()));

    actNovoElemento = new QAction("Novo Elemento" , this);
    QObject::connect(actNovoElemento, SIGNAL(triggered()), this, SLOT(novoElemento()));

    actNovaVariavel = new QAction("Nova Variavel" , this);
    QObject::connect(actNovaVariavel, SIGNAL(triggered()), this, SLOT(novaVariavel()));

    actNovaPergunta = new QAction("Nova Pergunta" , this);
    QObject::connect(actNovaPergunta, SIGNAL(triggered()), this, SLOT(novaPergunta()));

    actNovaAcao = new QAction("Nova Acao" , this);
    QObject::connect(actNovaAcao, SIGNAL(triggered()), this, SLOT(novaAcao()));

    actAmbienteExterno = new QAction("Comunicacao com Ambiente Externo" , this);
    QObject::connect(actAmbienteExterno, SIGNAL(triggered()), this, SLOT(iniciaComunicacaoAmbienteExterno()));

    actAmbienteExternoROS = new QAction("Comunicacao com Ambiente ROS" , this);
    QObject::connect(actAmbienteExternoROS, SIGNAL(triggered()), this, SLOT(iniciaComunicacaoAmbienteExternoROS()));

    actDeletaElemento = new QAction("Deleta" , this);
    QObject::connect(actDeletaElemento, SIGNAL(triggered()), this, SLOT(deletaElemento()));

    actNovaRelacao = new QAction("Nova Relacao" , this);
    QObject::connect(actNovaRelacao, SIGNAL(triggered()), this, SLOT(novaRelacao()));

    actInicia = new QAction("Inicializa Jogador" , this);
    QObject::connect(actInicia, SIGNAL(triggered()), this, SLOT(inicia()));

    actExecucaoAutomatica = new QAction("At/Des. exec auto", this);
    QObject::connect(actExecucaoAutomatica, SIGNAL(triggered()), this, SLOT(execucaoAutomatica()));

    actExecucaoTemporizada = new QAction("At/Des. exec temp", this);
    QObject::connect(actExecucaoTemporizada, SIGNAL(triggered()), this, SLOT(execucaoTemporizada()));

    actCarregaXML = new QAction("Carrega XML", this);
    QObject::connect(actCarregaXML, SIGNAL(triggered()), this, SLOT(carregaXML()));

    actGeraXML = new QAction("Gera XML", this);
    QObject::connect(actGeraXML, SIGNAL(triggered()), this, SLOT(geraXML()));

    actExecutaElemento = new QAction("Executa", this);
    QObject::connect(actExecutaElemento, SIGNAL(triggered()), this, SLOT(executaElemento()));

    actAlteraValor = new QAction("Altera Valor", this);
    QObject::connect(actAlteraValor, SIGNAL(triggered()), this, SLOT(alteraValor()));

}

void DJogadorRede::criaMenus()
{
    mnuFundo = new QMenu(widget());

    mnuFundo->addAction(actInicia);

    mnuFundo->addAction(actExecuta);

    mnuFundo->addAction(actNovaRelacao);

    mnuFundo->addAction(actNovaVariavel);
    mnuFundo->addAction(actNovaPergunta);
    mnuFundo->addAction(actNovaAcao);

    mnuFundo->addAction(actAmbienteExterno);
    mnuFundo->addAction(actAmbienteExternoROS);

    mnuFundo->addAction(actExecucaoAutomatica);
    mnuFundo->addAction(actExecucaoTemporizada);

    mnuFundo->addAction(actNovoElemento);

    mnuFundo->addAction(actGeraXML);
    mnuFundo->addAction(actCarregaXML);

    mnuElementosGraficos = new QMenu(widget());
    mnuElementosGraficos->addAction(actDeletaElemento);
    mnuElementosGraficos->addAction(actExecutaElemento);
    mnuElementosGraficos->addAction(actAlteraValor);

}

DJogadorRede::DJogadorRede()
{
    setNome("Jogador da Rede");
    setNomeVisivel(true);

    iniciaDJogadorRede();
}

DJogadorRede::~DJogadorRede()
{
    if(m_jogador != 0x0)
        delete m_jogador;
    m_jogador = 0x0;
}

/**
 * @brief
 *  Metodo chamado quando uma novavariavel é criado no ambiente
 * @param id - id da variavel criada.
 * @param nome - nome da variavel criada.
 * @param valor - valor da variavel criada.
 */
void DJogadorRede::novaVariavel(unsigned idNodo, const string& nome, const string& valor)
{
    if(novoDesenho(jrVARIAVEL, idNodo) == idNodo)
    {
        Desenho *d = desenho(jrVARIAVEL, idNodo);
        d->setNome(nome.c_str());
        d->setTextoInferior(valor);

        if(m_redesenhaACadaAlteracao)
            redesenha();
    }else
    {
        cout << "Jogador da rede, Erro ao criar variavel, conflito de IDs" << endl;
    }
}

/**
 * @brief
 *  Metodo chamado quando uma pergunta é criada
 * @param id - ID da pergunta criada.
 * @param nome - Nome da pergunta criada.
 * @param valor Valor da variavel criada.
 */
void DJogadorRede::novaPergunta(unsigned idNodo, const string& nome, const string& valor)
{
    if(novoDesenho(jrPERGUNTA, idNodo) == idNodo)
    {
        desenho(jrPERGUNTA, idNodo)->setNome(nome.c_str());
        if(m_redesenhaACadaAlteracao)
            redesenha();

    }else
    {
        cout << "Jogador Rede : Erro ao criar pergunta, conflito de IDs" << endl;
    }
}

/**
 * @brief
 *  Metodo chamado quando uma nova acao é criada.
 * @param id - ID da acao criada.
 * @param nome - Nome da acao criada.
 * @param valor - Valor da acao criada.
 */
void DJogadorRede::novaAcao(unsigned idNodo, const string& nome, const string& valor)
{
    if(novoDesenho(jrACAO, idNodo) == idNodo)
    {
        desenho(jrACAO, idNodo)->setNome(nome.c_str());
        if(m_redesenhaACadaAlteracao)
            redesenha();
    }else
    {
        cout << "Jogador Rede: Erro ao criar acao, conflito de IDs" << endl;
    }
}

void DJogadorRede::alteracaoNome(const string &nome)
{
}

/**
 * @brief
 *  Metodo chamado quando algum nodo do ambiente é alterado.
 * @param id - ID do nodo.
 * @param valor - Novo valor do nodo.
 * @return bool -
 */
bool DJogadorRede::alteracaoValor(unsigned idNodo, const string& valor)
{
    if(m_CAmbiente->ehVariavel(idNodo) && desenho(jrVARIAVEL, idNodo))
    {
        desenho(jrVARIAVEL, idNodo)->setTextoInferior(valor);
        if(m_redesenhaACadaAlteracao)
            redesenha();
    }
}

/**
 * @brief
 *  Método chamado quando uma variavel é removida do ambiente.
 * @param idNodo - ID da variável.
 */
void DJogadorRede::removeVariavel(unsigned idNodo)
{
    deletaDesenho(jrVARIAVEL, idNodo);
    if(m_redesenhaACadaAlteracao)
        redesenha();
}

/**
 * @brief
 *  Método chamado quando uma pergunta é removida do ambiente.
 * @param idNodo - ID da pergunta.
 */
void DJogadorRede::removePergunta(unsigned idNodo)
{
    deletaDesenho(jrPERGUNTA, idNodo);
    if(m_redesenhaACadaAlteracao)
        redesenha();
}

/**
 * @brief
 *  Método chamado quando uma ação é removida do ambiente.
 * @param idNodo - ID da açao removida.
 */
void DJogadorRede::removeAcao(unsigned idNodo)
{
    deletaDesenho(jrACAO, idNodo);
    if(m_redesenhaACadaAlteracao)
        redesenha();
}

void DJogadorRede::removeRelacao(unsigned idRelacao)
{
    deletaDesenho(jrARCO, idRelacao);
}

void DJogadorRede::removeTudo()
{
}

void DJogadorRede::novaTransicao(unsigned id)
{
    if(novoDesenho(jrGATILHO, id) != id)
    {
        cout << "DJogador rede:: Erro ao criar transicao, conflito de IDs" << endl;
    }else
    {
        Desenho *d = desenho(jrGATILHO , id);
        d->setNome(QString("t%1").arg(id));
    }
}

void DJogadorRede::removeTransicao(unsigned id)
{
    deletaDesenho(jrGATILHO, id);
}

void DJogadorRede::novaRelacaoPergunta(unsigned idTransicao, unsigned idPergunta, int idRelacao)
{
    if(novaSeta(idTransicao, jrGATILHO, idPergunta, jrPERGUNTA , idRelacao) != idRelacao)
    {
        cout << "DJogadorRede:: Erro ao criar relacao com pergunta, conflito de IDs" << endl;
    }
}

void DJogadorRede::novaRelacaoAcao(unsigned idTransicao, unsigned idAcao, int idRelacao)
{
    if(novaSeta(idTransicao , jrGATILHO , idAcao, jrACAO , idRelacao) != idRelacao)
    {
        cout << "DJogador:: Erro ao criar relacao com acao, conflito de IDs" << endl;
    }
}

void DJogadorRede::reiniciaJogadorRede()
{
}

void DJogadorRede::mousePrecionado(MouseEvento *me, int idTipoDesenho, int idDesenho)
{
    if(idTipoDesenho == -1 && idDesenho == -1)
    {
        if(me->botao() == BOTAO_DIREITO)
        {
            mnuFundo->exec(me->posicaoJanela());
        }
    }else if(idTipoDesenho >= 0 && me->botao() == BOTAO_DIREITO)
    {
        m_idTipoDesenhoFoco = idTipoDesenho;
        m_idDesenhoFoco = idDesenho;
        mnuElementosGraficos->exec(me->posicaoJanela());
    }
}

void DJogadorRede::mouseSolto(MouseEvento *me, int idTipoDesenho, int idDesenho)
{
}

int DJogadorRede::ligacao(int deId, int deIdTipo, int paraId, int paraIdTipo)
{
    if(deIdTipo == jrGATILHO && paraIdTipo == jrPERGUNTA)
    {
        // O Arco é criado apos a chamada deste metodo em todas visualizacoes
        // atraves do esquema de escuta
        m_jogador->relacionaPergunta(deId, paraId);
    }else if( deIdTipo == jrGATILHO && paraIdTipo == jrACAO)
    {
        m_jogador->relacionaAcao(deId , paraId);
    }else
    {
        cout << "Jogador rede:: Erro, a ligacao nao e permitida" << endl;
    }
    return -2; // Nao cria o arco, ele sera criado apos alteracao do modelo atravez da interface de escuta do jogador da rede
}

void DJogadorRede::inicia()
{
    if(m_jogador != 0x0) return;

    // Cria um jogador da rede
    m_jogador = new JogadorRede;

    // Cria uma rede de petri
    DRedePetri *rede = new DRedePetri;
    m_visualizacaoRede = rede;

    m_controleRede = rede->controlador();

    // Cria um ambiente
    m_CAmbiente = new CAmbiente;

    // Coloca a interface grafica da nova rede no meu container
    pai()->novoDesenho(rede);

    // Define a rede que o jogador vai controlar
    m_jogador->setControladorRede(rede->controlador());

    // Define o controlador de ambiente do jogador da rede
    m_jogador->setControladorAmbiente(m_CAmbiente);

    // Adiciona essa interface grafica como escuta do jogador
    m_jogador->adicionaEscuta(this);
}

void DJogadorRede::novoElemento()
{
    // Codigo de teste
    m_CAmbiente->novaVariavel("M1", "true");
    int acaoDesliga =  m_CAmbiente->novaAcao("Desliga_M1", "M1=false"),
        acaoLiga = m_CAmbiente->novaAcao("Liga_M1", "M1=true"),
        pergunta = m_CAmbiente->novaPergunta("M1_Ligado", "M1==true");

    m_controleRede->novaTransicao();
    m_controleRede->novaTransicao();

    m_jogador->relacionaPergunta(0, pergunta);
    m_jogador->relacionaAcao(0,acaoDesliga);


    m_jogador->relacionaAcao(1,acaoLiga);

}

void DJogadorRede::executa()
{
    m_jogador->loop();
    if(m_execucaoTemporizada) redesenha();
}

void DJogadorRede::novaVariavel()
{
    DialogGenerico d;
    d.setPergunta("Digite o Nome da Varivael");

    if(!d.exec())
        return;

    string nome(d.resposta().toLocal8Bit().constData());

    d.setPergunta(QString() + "Digite o valor incial da variavel " + nome.c_str());

    if(!d.exec())
        return;

    string valor(d.resposta().toLocal8Bit().constData());

    cout << "Nova variavel nome " << nome << " valor inicial " << valor << endl;
    m_CAmbiente->novaVariavel(nome, valor);
//    m_CAmbiente->novaVariavel(nome, );
}

void DJogadorRede::novaPergunta()
{
    DialogGenerico d;
    d.setPergunta("Digite o Nome da Pergunta");

    if(!d.exec())
        return;

    string nome(d.resposta().toLocal8Bit().constData());

    d.setPergunta(QString() + "Digite a expressao logica da pergunta " + nome.c_str());

    if(!d.exec())
        return;

    string valor(d.resposta().toLocal8Bit().constData());

    cout << "Nova pergunta nome " << nome << " valor inicial " << valor << endl;
    m_CAmbiente->novaPergunta(nome, valor);
}

void DJogadorRede::novaAcao()
{
    DialogGenerico d;
    d.setPergunta("Digite o Nome da Acao");

    if(!d.exec())
        return;

    string nome(d.resposta().toLocal8Bit().constData());

    d.setPergunta(QString() + "Digite a expressao da acao " + nome.c_str());

    if(!d.exec())
        return;

    string valor(d.resposta().toLocal8Bit().constData());

    cout << "Nova pergunta nome " << nome << " valor inicial " << valor << endl;
    m_CAmbiente->novaAcao(nome, valor);
}

void DJogadorRede::iniciaComunicacaoAmbienteExterno()
{
    AmbienteExterno *amb = new AmbienteExterno("localhost", 12346);
    amb->inicia(m_CAmbiente);
    m_redesenhaACadaAlteracao = true; // Utilizado para redezenhar quando surgir alteracao do ambiente externo
}

void DJogadorRede::iniciaComunicacaoAmbienteExternoROS()
{
    AmbienteExternoROSBridge *amb = new AmbienteExternoROSBridge;
    amb->inicia(m_CAmbiente);
    m_redesenhaACadaAlteracao = true; // Utilizado para redezenhar quando surgir alteracao do ambiente externo
}

void DJogadorRede::deletaElemento()
{
    switch(m_idTipoDesenhoFoco)
    {
    case jrGATILHO:
        cout << "DJogadorrede:: Erro, o jogador nao pode remover uma transicao" << endl;
        break;
    case jrARCO:
        m_jogador->removeRelacao(m_idDesenhoFoco);
        break;
    case jrVARIAVEL:
        m_CAmbiente->removeVariavel(m_idDesenhoFoco);
        break;
    case jrPERGUNTA:
        m_CAmbiente->removePergunta(m_idDesenhoFoco);
        break;
    case jrACAO:
        m_CAmbiente->removeAcao(m_idDesenhoFoco);
        break;
    }

    m_idTipoDesenhoFoco = -1;
    m_idDesenhoFoco = -1;
}

void DJogadorRede::novaRelacao()
{
    novoArco();
}

void DJogadorRede::execucaoAutomatica()
{
    if(m_jogador->execucaoAutomatica())
    {
        m_jogador->setExecucaoAutomatica(false);
    }else
    {
        m_jogador->setExecucaoAutomatica(true);
    }
}

void DJogadorRede::execucaoTemporizada()
{
    if(!m_execucaoTemporizada)
    {
        m_relogio->start(200);
        m_execucaoTemporizada = true;
    }else
    {
        m_relogio->stop();
        m_execucaoTemporizada = false;
    }
}

void DJogadorRede::geraXML()
{

    FILE *arq;
    QString nomeArquivo = QFileDialog::getSaveFileName(widget(), "Salvar XML", QString(),"XML (*.xml)");
    arq = fopen((nomeArquivo.toStdString().c_str()), "w+");

    if(arq != 0x0)
    {
        unsigned i =0;
        QDomDocument d;
        QDomNode raiz;

        QDomElement e = d.createElement("JogadorRede");

        e.setAttribute("Nome" , m_nome);
        raiz = d.appendChild(e);

        m_visualizacaoRede->geraXML(d, raiz);

        const Ambiente *ambiente = m_CAmbiente->modelo();

        const VariavelAmbiente* var;
        const PerguntaAmbiente* per;
        const AcaoAmbiente* acao;
        const NodoAmbiente *nodo;

        for(i = 0; i <= ambiente->idMaiorNodo(); i++)
        {
            nodo = ambiente->getNodo(i);
            if(nodo != 0x0)
            {
                switch(nodo->tipoNodo())
                {
                    case NODO_ACAO:
                        e = d.createElement("Acao");
                        acao = (const AcaoAmbiente*) nodo;

                        e.setAttribute("Nome", QString(acao->nome().c_str()) );
                        e.setAttribute("Acao", QString(acao->acao().c_str()) );
                        e.setAttribute("X", desenho(jrACAO, i)->posicaoLocal().x() );
                        e.setAttribute("Y", desenho(jrACAO, i)->posicaoLocal().y() );
                        raiz.appendChild(e);
                    break;
                    case NODO_PERGUNTA:
                        e = d.createElement("Pergunta");
                        per = (const PerguntaAmbiente*) nodo;

                        e.setAttribute("Nome", QString(per->nome().c_str()) );
                        e.setAttribute("Pergunta", QString(per->pergunta().c_str()) );
                        e.setAttribute("X", desenho(jrPERGUNTA, i)->posicaoLocal().x() );
                        e.setAttribute("Y", desenho(jrPERGUNTA, i)->posicaoLocal().y() );
                        raiz.appendChild(e);
                    break;

                    case NODO_VARIAVEL:
                        e = d.createElement("Variavel");
                        var = (const VariavelAmbiente*) nodo;

                        e.setAttribute("Nome", QString(var->nome().c_str()) );
                        e.setAttribute("Valor", QString(var->valor().c_str()) );
                        e.setAttribute("X", desenho(jrVARIAVEL, i)->posicaoLocal().x() );
                        e.setAttribute("Y", desenho(jrVARIAVEL, i)->posicaoLocal().y() );
                        raiz.appendChild(e);
                    break;

                }
            }
        }


        // Posicoes das transicoes no Jogador da Rede
        const Desenho *des;
        for(i = 0; i <= maiorIndice(jrGATILHO); i++)
        {
            des = desenho(jrGATILHO, i);
            if(des != 0x0)
            {
                e = d.createElement("Transicao");
                e.setAttribute("ID", i );
                e.setAttribute("X", des->posicaoLocal().x() );
                e.setAttribute("Y", des->posicaoLocal().y() );
                raiz.appendChild(e);
            }
        }

        // Relacoes
        const vector // Indice representa o ID da transicao
        <
           pair
           <
             list< unsigned > , // Condicoes
             list< unsigned >   // Acoes
           >
        > relacoes = m_jogador->relacoes();

        for( i = 0 ; i < relacoes.size() ; i++)
        {
            if(!relacoes[i].first.empty())
            {

                const list<unsigned> &lista = relacoes[i].first;
                list<unsigned>::const_iterator li;

                for( li = lista.begin() ; li != lista.end() ; li++ )
                {
                    e = d.createElement("Relacao");
                    e.setAttribute("Transicao", i );
                    e.setAttribute("Pergunta", QString(ambiente->getNodo(*li)->nome().c_str()) );
                    raiz.appendChild(e);
                }
            }

            if(!relacoes[i].second.empty())
            {
                const list<unsigned> &lista = relacoes[i].second;
                list<unsigned>::const_iterator li;

                for( li = lista.begin() ; li != lista.end() ; li++ )
                {
                    e = d.createElement("Relacao");
                    e.setAttribute("Transicao", i );
                    e.setAttribute("Acao", QString(ambiente->getNodo(*li)->nome().c_str()) );
                    raiz.appendChild(e);
                }
            }
        }

        QTextStream Qs(arq);
        d.save(Qs,4);
        fclose(arq);
    }else cout << "Problema ao abrir xml" << endl;
}

void DJogadorRede::carregaXML()
{
    QString nomeArquivo = QFileDialog::getOpenFileName(widget(), "Abrir xml", QString(), "XML (*.xml)" );
    if(!nomeArquivo.isNull())
    {
        m_controleRede->deletaTudo();

        // Abrindo arquivo
        QDomDocument doc;
        QFile file(nomeArquivo);

        if (!file.open(QIODevice::ReadOnly))
            return;
        if (!doc.setContent(&file)) // Montando arvore
        {
            file.close();
            return;
        }
        file.close(); // Fechando arquivo

        // Transformando raiz da arvore XML
        QDomElement docElem = doc.documentElement();

        // Verifica se a raiz e valida
        if(docElem.tagName() != "JogadorRede")
        {
            cout << "Erro ao carregar XML JogadorRede , XML inlegivel" << endl;
            return;
        }

        // Carrega a Rede de Petri
        QDomNode nodo = docElem.firstChild();
        while(!nodo.isNull())
        {
            QDomElement e = nodo.toElement();
            if(!e.isNull())
            {
                if(e.tagName() == "RedePetri")
                    m_visualizacaoRede->carregaXML(e);
            }
            nodo = nodo.nextSibling();
        }

        // Carrega Ambiente e Relacoes
        int id;
        QString nome,valor;
        float X, Y;

        nodo = docElem.firstChild();
        while(!nodo.isNull())
        {
            QDomElement e = nodo.toElement();
            cout << "Lendo tag " << e.tagName().toStdString() << endl;
            if(!e.isNull())
            {
                if(e.tagName() == "Variavel")
                {
                    // Nao estamos tratando o fado do xml estar errado (faltando atributos)
                    nome = e.attributeNode(QString("Nome")).value();
                    valor = e.attributeNode(QString("Valor")).value();
                    X = e.attributeNode(QString("X")).value().toFloat();
                    Y = e.attributeNode(QString("Y")).value().toFloat();
                    id = m_CAmbiente->novaVariavel(nome.toStdString(),valor.toStdString());

                    desenho(jrVARIAVEL, id)->setPosicao(rPonto(X,Y));
                }
                else if(e.tagName() == "Acao")
                {
                    // Nao estamos tratando o fado do xml estar errado (faltando atributos)
                    nome = e.attributeNode(QString("Nome")).value();
                    valor = e.attributeNode(QString("Acao")).value();
                    X = e.attributeNode(QString("X")).value().toFloat();
                    Y = e.attributeNode(QString("Y")).value().toFloat();
                    id = m_CAmbiente->novaAcao(nome.toStdString(),valor.toStdString());

                    desenho(jrACAO, id)->setPosicao(rPonto(X,Y));
                }
                else if(e.tagName() == "Pergunta")
                {
                    // Nao estamos tratando o fado do xml estar errado (faltando atributos)
                    nome = e.attributeNode(QString("Nome")).value();
                    valor = e.attributeNode(QString("Pergunta")).value();
                    X = e.attributeNode(QString("X")).value().toFloat();
                    Y = e.attributeNode(QString("Y")).value().toFloat();
                    id = m_CAmbiente->novaPergunta(nome.toStdString(),valor.toStdString());

                    desenho(jrPERGUNTA, id)->setPosicao(rPonto(X,Y));
                }
                else if(e.tagName() == "Transicao")
                {
                    // Nao estamos tratando o fado do xml estar errado (faltando atributos)
                    id = e.attributeNode(QString("ID")).value().toInt();
                    X = e.attributeNode(QString("X")).value().toFloat();
                    Y = e.attributeNode(QString("Y")).value().toFloat();

                    desenho(jrGATILHO, id)->setPosicao(rPonto(X,Y));
                }
                else if(e.tagName() == "Relacao")
                {
                    QDomAttr atributo;
                    int idNodoAmbiente;
                    id = e.attributeNode(QString("Transicao")).value().toInt();

                    atributo = e.attributeNode(QString("Pergunta"));
                    if(!atributo.isNull())
                    {
                        idNodoAmbiente = m_CAmbiente->idNodo(atributo.value().toStdString());
                        if(idNodoAmbiente >=0)
                            m_jogador->relacionaPergunta(id,idNodoAmbiente);
                    }
                    else
                    {
                    atributo = e.attributeNode(QString("Acao"));
                    if(!atributo.isNull())
                    {
                        idNodoAmbiente = m_CAmbiente->idNodo(atributo.value().toStdString());
                        if(idNodoAmbiente >=0)
                            m_jogador->relacionaAcao(id,idNodoAmbiente);
                    }
                    }
                }
            }
            nodo = nodo.nextSibling();
        }
    }
}

void DJogadorRede::executaElemento()
{
    if(m_idDesenhoFoco >= 0 && m_idTipoDesenhoFoco == jrACAO)
    {
        m_CAmbiente->executaAcao(m_idDesenhoFoco);
    }
}

void DJogadorRede::alteraValor()
{
    if(m_idTipoDesenhoFoco != jrVARIAVEL) return;
    DialogGenerico d;

    d.setPergunta("Digite o novo valor de " + desenho(m_idTipoDesenhoFoco,m_idTipoDesenhoFoco)->getNome());

    if(!d.exec())
        return;

    string valor(d.resposta().toLocal8Bit().constData());

    m_CAmbiente->setVariavel(m_idDesenhoFoco, valor);
}

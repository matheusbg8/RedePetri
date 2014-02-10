#include "DAmbiente.h"
#include "DialogNovaVariavelAmbiente.h"
#include "Seta.h"
#include "CAmbiente.h"


DAmbiente::DAmbiente():Container(0x0)
{
    m_controleAmbiente = 0x0;

    m_tipoDesenho = TD_AMBIENTE;

    criaAcoes();
    criaMenus();

    // Adiciona a variavel de ambiente que representa o ambiente
    adicionaVariavelRaiz();
}

DAmbiente::~DAmbiente()
{
//    // Se possui um controlador
//    if(m_controleAmbiente != 0x0)
//    {
//        // Se auto remove do controlador
//        m_controleAmbiente->removeVisualizacao(this);

//        // Se ele não possui mais nenhuma visualizacao
//        if(!m_controleAmbiente->possuiVisualizacoes())
//        {
//            // Deleta o controlador
//            delete m_controleAmbiente;
//        }
//        m_controleAmbiente = 0x0;
//    }
}

CAmbiente *DAmbiente::controle()
{
    return m_controleAmbiente;
}

void DAmbiente::setControleAmbiente(CAmbiente *controle)
{
    m_controleAmbiente = controle;
}


/**
 * @brief
 *  Adiciona uma nova variavel a visualização
 * @param idVarPai
 * @param novaVariavel
 * @return bool
 */
bool DAmbiente::addVariavel(unsigned idVarPai, const VariavelAmbiente *novaVariavel)
{
    // Se possui a vavriavel pai
    if( idVarPai < m_variaveis.size())
    {
        unsigned idNovaVar = novaVariavel->id();
        DVariavelAmbiente *novaVar = new DVariavelAmbiente(idNovaVar , novaVariavel->nome().c_str(), novaVariavel->valor().c_str());

        // Verifica se precisa aloca mais espaço para armazenar nova variavel
        if(idNovaVar >= m_variaveis.size())
        {
            m_variaveis.resize((idNovaVar+1)*2);
        }

        m_variaveis[idNovaVar] = novaVar;

        novoDesenho(novaVar);

        Seta *seta = new Seta();

        novoDesenho(seta);

        seta->setLigacaoIni(m_variaveis[idVarPai]);
        seta->setLigacaoFim(m_variaveis[idNovaVar]);

        return true;
    }else
    {
        cout << "Erro ao adicionar variavel, var pai invalida" << endl;
    }

    return false;
}

bool DAmbiente::removeVariavel(unsigned varId)
{
    // Se possui a variavel
    if(varId < m_variaveis.size())
    {
        // Remove ela
        delete m_variaveis[varId];
        m_variaveis[varId] = 0x0;
        return true;
    }

    return false;
}

void DAmbiente::apagaTudo()
{
    m_variaveis.clear();
    deletaDesenhos();

    adicionaVariavelRaiz();
}

bool DAmbiente::setNomeVariavel(unsigned idVar, QString nome)
{
    if(idVar <   m_variaveis.size())
    {
        m_variaveis[idVar]->setNome(nome);
        return true;
    }
    return false;
}

void DAmbiente::setNome(QString nome)
{
    Desenho::setNome(nome);
    m_variaveis[0]->setNome(nome);
}

bool DAmbiente::setValor(unsigned idVar, QString valor)
{
    if(idVar < m_variaveis.size())
    {
        m_variaveis[idVar]->setValor(valor);
        return true;
    }
    return false;
}

void DAmbiente::criaAcoes()
{
    actNovaVariavel = new QAction("Nova Variavel", this);
    QObject::connect(actNovaVariavel ,SIGNAL(triggered()), this, SLOT(novaVariavel()) );

    actNovaPergunta = new QAction("Nova Pergunta", this);
    QObject::connect((actNovaPergunta), SIGNAL(triggered()) , this, SLOT(novaPergunta()));

    actCriaReferencia = new QAction("Referencia", this);
    QObject::connect((actCriaReferencia), SIGNAL(triggered()) , this, SLOT(criaReferencia()));

    actGeraXML = new QAction("Gera XML", this);
    QObject::connect((actGeraXML), SIGNAL(triggered()) , this, SLOT(geraXML()));

    actDeleta = new QAction("Deleta", this);
    QObject::connect((actDeleta), SIGNAL(triggered()) , this, SLOT(deleta()));

}

void DAmbiente::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(actNovaVariavel);
    mnuFundo->addAction(actNovaPergunta);
    mnuFundo->addAction(actCriaReferencia);
    mnuFundo->addAction(actGeraXML);
    mnuFundo->addAction(actDeleta);
}


/**
 * @brief
 *  Percorre o grafo montando a arvore XML,
 * o grafo deve ser uma arvore, não deve possuir
 * ciclos.
 * @param pai - NodoXML raiz
 * @param idVariavel - Vertice inicial da busca
 */
void DAmbiente::adicionaVariavelXML(QDomDocument *DocXML , QDomElement* pai, unsigned idVariavel)
{
    // Grafo da estrutura de variaveis
    const Grafo *grafo = m_controleAmbiente->modelo()->grafo();

    unsigned i, id , numSucessores = grafo->numSucessores(idVariavel);
    QDomElement novoElemento;

    for( i = 0 ; i < numSucessores ; i++)
    {
        id = grafo->sucessor(idVariavel , i);
        novoElemento = DocXML->createElement("Variavel");
        novoElemento.setAttribute("Nome", m_variaveis[id]->getNome());
        novoElemento.setAttribute("Valor", m_variaveis[id]->valor());
        novoElemento.setAttribute("X", m_variaveis[id]->x());
        novoElemento.setAttribute("Y", m_variaveis[id]->y());
        pai->appendChild(novoElemento);
        adicionaVariavelXML(DocXML , &novoElemento ,  id);
    }
}

bool DAmbiente::mousePrecionado(MouseEvento *novoMouseEvento)
{
    if(novoMouseEvento->botao() == BOTAO_DIREITO)
    {
        mnuFundo->exec(novoMouseEvento->posicaoJanela());
        return true;
    }else
    {
        return Container::mousePrecionado(novoMouseEvento);
    }
}

void DAmbiente::adicionaVariavelRaiz()
{
    // Adiciona a variavel de ambiente que representa o ambiente
    DVariavelAmbiente *varAmbi = new DVariavelAmbiente(0,m_nome);
    novoDesenho(varAmbi);
    m_variaveis.push_back(varAmbi);
}

/**
 * @brief
 *  Cria uma nova variavel no ambiente
 */
void DAmbiente::novaVariavel()
{
//    if(m_controleAmbiente == 0x0)
//        return;

//    VariavelAmbiente *novaVariavel = 0x0;

//    DialogNovaVariavelAmbiente criaVariavel(&novaVariavel, widget());

//    criaVariavel.exec();

//    if(novaVariavel != 0x0)
//    {
//        m_controleAmbiente->novaVariavel(0 , novaVariavel);
//    }
}

void DAmbiente::novaPergunta()
{

}

void DAmbiente::criaReferencia()
{
//    if(m_pai == 0x0)
//        return;

//    DAmbiente *novaReferencia = new DAmbiente;
//    novaReferencia->setControleAmbiente(m_controleAmbiente);
//    m_controleAmbiente->addVisualizacao(novaReferencia);

//    m_pai->novoDesenho(novaReferencia);
}

void DAmbiente::geraXML()
{
    FILE *arq;
    QString nomeArquivo = QFileDialog::getSaveFileName(widget(), "Salvar Ambiente XML", QString(),"XML (*.xml)");
    arq = fopen((nomeArquivo.toStdString().c_str()), "w+");

    // Se o arquivo pode ser aberto ou criado
    if(arq != 0x0)
    {
        QDomDocument d; // DocumentoXML

        // Cria o primeiro elemento do XML
        QDomElement raiz = d.createElement("Amiente");
        raiz.setAttribute("Nome" , m_nome);

        d.appendChild(raiz);

        // Solucao recursiva que percorre o grafo
        // montando a arvore XML
        // Deve ser garantido que o grafo não possui ciclos!!
        // Vertive 0 sempre é o ambiente
        adicionaVariavelXML(&d, &raiz, 0);

        QTextStream Qs(arq);
        d.save(Qs,4);
        fclose(arq);
    }else cout << "Problema ao abrir xml" << endl;
}

void DAmbiente::deleta()
{
    delete this;
}

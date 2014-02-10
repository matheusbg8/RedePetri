#include "DRedePetri.h"
#include <iostream>
#include <QMessageBox>

#include "DLugar.h"
#include "DTransicao.h"
#include "DArco.h"
#include <QtGui>
#include <qobject.h>
#include <cstdio>
#include "DGrafo.h"
#include "VisualizadorGrafo.h"
#include "DialogGrafoCobertura.h"

unsigned DRedePetri::numRedePetri = 0;

void DRedePetri::inicializaDRedePetri()
{
    cout << "Iniciando nova rede de petri" << endl;

    m_visualizacaoTCP = 0x0;

    // Inicializa controle
    m_controleRede = new ControladorRede;
    m_controleRede->setModelo(new RedePetri(1,1));
    m_controleRede->addVisualizacao(this);

    m_tipoDesenho = TD_REDE_PETRI;

    numRedePetri++;
    m_idRedePetri = numRedePetri;

    criaAcoes();
    criaMenus();
    setNome(QString("Rede Petri %1").arg(m_idRedePetri));
}

void DRedePetri::criaAcoes()
{
    novaTransicaoAct = new QAction("Nova Transicao" , this);
    QObject::connect(novaTransicaoAct, SIGNAL(triggered()), this, SLOT(SNovaTransicao()));

    novoLugarAct = new QAction("Novo Lugar" , this);
    QObject::connect(novoLugarAct, SIGNAL(triggered()), this, SLOT(SNovoLugar()));

    novoArcoAct = new QAction("Novo Arco" ,this);
    QObject::connect(novoArcoAct, SIGNAL(triggered()), this, SLOT(SNovoArco()));

    actGeraXMLSimples = new QAction("Gera XML Simples", this);
    QObject::connect(actGeraXMLSimples, SIGNAL(triggered()),this,SLOT(geraXMLSimples()));

    actImprimeRede = new QAction("Imprime Rede", this);
    QObject::connect(actImprimeRede, SIGNAL(triggered()),this,SLOT(imprimeRede()));

    actGeraGrafoCobertura = new QAction("Gera Grafo de Cobertura", this);
    QObject::connect(actGeraGrafoCobertura, SIGNAL(triggered()),this, SLOT(geraGrafoCobertura()));

    actAlinhar = new QAction("Alinhar", this);
    QObject::connect(actAlinhar, SIGNAL(triggered()),this, SLOT(alinhar()));

    actDeleta = new QAction("Deleta", this);
    QObject::connect(actDeleta, SIGNAL(triggered()),this, SLOT(deleta()));

    actNovaVisualizacao = new QAction("Nova Visualizacao", this);
    QObject::connect(actNovaVisualizacao, SIGNAL(triggered()),this, SLOT(novaVisualizacao()));

    actCriaVisualizacaoTCP = new QAction("Cria Visualizacao TCP", this);
    QObject::connect(actCriaVisualizacaoTCP, SIGNAL(triggered()),this, SLOT(criaVisualizacaoTCP()));

    actCarregaXML = new QAction("Carrega XML", this);
    QObject::connect(actCarregaXML, SIGNAL(triggered()),this, SLOT(carregaXMLSimples()));

}

void DRedePetri::criaMenus()
{
    mnuFundo = new QMenu(widget());
    mnuFundo->addAction(novaTransicaoAct);
    mnuFundo->addAction(novoLugarAct);
    mnuFundo->addAction(novoArcoAct);
    mnuFundo->addAction(actGeraXMLSimples);
    mnuFundo->addAction(actCarregaXML);
    mnuFundo->addAction(actImprimeRede);
    mnuFundo->addAction(actGeraGrafoCobertura);
    mnuFundo->addAction(actAlinhar);
    mnuFundo->addAction(actDeleta);
    mnuFundo->addAction(actNovaVisualizacao);
    mnuFundo->addAction(actCriaVisualizacaoTCP);
}


DRedePetri::DRedePetri(Container *pai):Container(rPonto(30,30),100,100,pai)
{
    inicializaDRedePetri();
}

DRedePetri::~DRedePetri()
{
    // Remove o controle de todos os componentes da rede
    // para que ele não tentem mecher no controlador
    // quando forem desalocados.
    // Se esta operacao nao for realizada
    // os componentes graficos tentaram deletar
    // os componentes do modelo usando o controlador
    // mas o controlador pode nao existir mais
    // porque ele pode ser deletada ao
    // chamar o metodo removeVisualizacao neste destrutor

    vector<DLugar*>::iterator il;
    for(il = m_lugares.begin() ; il != m_lugares.end() ; il++)
    {
        // Como é um vector e os IDs sao indexados
        // Esse teste previne buracos na indexacao
        if(*il != 0x0)
            (*il)->setControle(0x0);
    }

    vector<DTransicao*>::iterator it;
    for(it = m_transicoes.begin() ; it != m_transicoes.end() ; it++)
    {
        // Como é um vector e os IDs sao indexados
        // Esse teste previne buracos na indexacao
        if(*it != 0x0)
            (*it)->setControle(0x0);
    }

    vector<DArco*>::iterator ia;
    for(ia = m_arcos.begin() ; ia != m_arcos.end() ; ia++)
    {
        // Como é um vector e os IDs sao indexados
        // Esse teste previne buracos na indexacao
        if(*ia != 0x0)
            (*ia)->setControle(0x0);
    }

    // Se remove do controlador da rede
    // o controlador não precisa ser deletado
    // porque ele se deleta automaticamente
    // quando ele nao possui mais visualizacoes
    m_controleRede->removeVisualizacao(this);

    if(m_visualizacaoTCP != 0x0)
    {
        m_controleRede->removeVisualizacao(m_visualizacaoTCP);
        delete m_visualizacaoTCP;
        m_visualizacaoTCP = 0x0;
    }
}

void DRedePetri::comando(QString cmd)
{
    QStringList cmdList = cmd.split(" ", QString::SkipEmptyParts);

    if(cmdList.at(0) == "novo")
    {
        if(cmdList.at(1) == "lugar")
        {
            cout << "Solicitação para criar novo lugar" << endl;
        }else if( cmdList.at(1) == "transicao")
        {
            cout << "Solicitacao de nova transicao" << endl;
        }
    }else
    {
        cout << "Comando não reconhecido" << endl;
    }
}

bool DRedePetri::mousePrecionado(MouseEvento *e)
{
    if(e->botao() == BOTAO_DIREITO )
    {
        if(produzLog)
            cout << "Posicao " << e->posicaoJanela().x() << " , " << e->posicaoJanela().y() << endl;
        mnuFundo->exec(e->posicaoJanela());
        if(produzLog)
            cout << "Clicado na rede de petri" << endl;

        return true;
    }else
    {
        return Container::mousePrecionado(e);
    }
    return false;
}

void *DRedePetri::getSuper()
{
    return this;
}


/**
 * @brief
 *  Sobrescreve o metodo remove desenho adicionando uma funcionalidade
 * de remover o a referencia da rede aos desenho, após esta operação
 * é chamado o removeDesenho do Container.
 * @param d
 */
void DRedePetri::removeDesenho(Desenho *d)
{
    switch(d->tipoDesenho())
    {
        case TD_LUGAR:
            m_lugares[((DLugar*)  d)->getIDCP()] = 0x0;
        break;
        case TD_TRANSICAO:
            m_transicoes[((DTransicao*) d)->getIDCP()] = 0x0;
        break;
        case TD_ARCO:
            m_arcos[((DArco*) d)->getIDCP()];
        break;
        default:
        break;

    }
    Container::removeDesenho(d);
}

///**
// * @brief
// *  Esse metodo chama o novo desenho da classe inferior Container,
// * somente se o desenho for do tipo TD_LUGAR, TD_TRANSICAO ou
// * TD_ARCO, caso contrario o novo desenho será deletado.
// * Pois este desenho não pode ser aceito.
// * @param d - Novo desenho que será adicionado.
// */
//void DRedePetri::novoDesenho(Desenho *d, bool avisaFilho)
//{

//    TipoDesenho tipo = d->tipoDesenho();
//    if(tipo == TD_LUGAR)
//    {
//        DLugar *lugar = (DLugar*) d->getSuper();
//        lugar->setControle(m_controleRede);

//        m_lugares.push_back(lugar);

//        Container::novoDesenho(d, avisaFilho);
//    }else
//    if(tipo == TD_TRANSICAO)
//    {
//        DTransicao *transicao = (DTransicao*) d->getSuper();
//        transicao->setControle(m_controleRede);

//        m_transicoes.push_back(transicao);
//        Container::novoDesenho(d, avisaFilho);
//    }else
//    if(tipo == TD_ARCO)
//    {
//        DArco *arco = (DArco*) d->getSuper();
//        arco->setControle(m_controleRede);

//        m_arcos.push_back(arco);
//        Container::novoDesenho(d, avisaFilho);
//    }else
//    {
//        QMessageBox msg;
//        msg.setText("Adicao de componente nao permitido");
//        msg.setInformativeText("Adicao de um elemento nao pertencente a classe de elementos da Rede de Petri");
//        msg.setIcon(QMessageBox::Warning);
//        msg.exec();
//        cout << "Adicionando elemento inválido a rede de petri" << endl;
//        delete d;
//    }
//}


/**
 * @brief
 *  Retorna o lugar com id especifico que
 * esta dentro da rede, ou 0x0 se não existir
 * esse lugar.
 * @param id - id do lugar que sera retornado
 * @return DLugar - lugar com o id especifico
 */
DLugar *DRedePetri::getLugar(unsigned id)
{
    if( id < m_lugares.size())
        return m_lugares[id];
    return 0x0;
}


int DRedePetri::novoLugar()
{
    return m_controleRede->novoLugar();
}

/**
 * @brief
 *  Retorna a transicao com id especifico que
 * esta dentro da rede, ou 0x0 se não existir
 * essa transição.
 * @param id - id da transicão que sera retornada
 * @return DTransicao - transição com o id especifico.
 */
DTransicao *DRedePetri::getTransicao(unsigned id)
{
    if( id < m_transicoes.size())
        return m_transicoes[id];
    return 0x0;
}
int DRedePetri::novaTransicao()
{
    return m_controleRede->novaTransicao();
}

DArco *DRedePetri::getArco(unsigned id)
{
    if(id < m_arcos.size())
        return m_arcos[id];
    return 0x0;
}

int DRedePetri::novoArcoPT(int de, int para, int peso)
{
    return m_controleRede->novoArcoPT(de, para , peso);
}

int DRedePetri::novoArcoTP(int de, int para, int peso)
{
    return m_controleRede->novoArcoTP(de, para , peso);
}

unsigned DRedePetri::getNumeroLugar()
{    
    if(m_controleRede != 0x0)
    {
        return m_controleRede->numLugares();
    }
    return 0;
}

unsigned DRedePetri::getNumeroTramsicao()
{
    if(m_controleRede != 0x0)
    {
        return m_controleRede->numTransicoes();
    }
    return 0;
}

unsigned DRedePetri::getNumeroArco()
{
    if(m_controleRede != 0x0)
    {
        return m_controleRede->numArcos();
    }
    return 0;
}

void DRedePetri::setControlador(ControladorRede *controlador)
{
    if(m_controleRede != 0x0)
        m_controleRede->removeVisualizacao(this);

    m_controleRede = controlador;

    if(controlador!= 0x0)
        controlador->addVisualizacao(this);
}

ControladorRede *DRedePetri::controlador()
{
    return m_controleRede;
}

bool DRedePetri::carregaXML(const QString &nomeArquivo)
{
    cout << "Carregando XML Simples" << endl;
    int i, n;
    QFile arq(nomeArquivo);

    if (arq.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDomDocument documentoXML;

        documentoXML.setContent(&arq);

        QDomNodeList listaNodos;
        QDomNamedNodeMap mapaNodos;
        QDomNode nodoXML;

        // Elementos da rede petri
        map<QString,int> mapaNomeID;

        DLugar *lugar;
        DArco *arco;
        DTransicao *transicao;

        // Temporarios
        float X, Y;
        QString str;
        int tInt, id;

        // Carrega Lugares
        listaNodos = documentoXML.elementsByTagName("Lugar");
        n = listaNodos.count();
        for(i = 0 ; i < n; i++)
        {
            nodoXML = listaNodos.item(i);
            mapaNodos = nodoXML.attributes();

            nodoXML = mapaNodos.namedItem("X");
            if(!nodoXML.isNull())
                X = nodoXML.toAttr().value().toFloat();

            nodoXML = mapaNodos.namedItem("Y");
            if(!nodoXML.isNull())
                Y = nodoXML.toAttr().value().toFloat();

            nodoXML = mapaNodos.namedItem("Fichas");
            if(!nodoXML.isNull())
                tInt = nodoXML.toAttr().value().toInt();

            nodoXML = mapaNodos.namedItem("Nome");
            if(!nodoXML.isNull())
                str = nodoXML.toAttr().value();

            id = m_controleRede->novoLugar();
            lugar = getLugar(id);
            mapaNomeID[str] = id;


            lugar->setNome(str);
            lugar->setNomeVisivel(true);
            lugar->setPosicao(rPonto(X, Y));
            lugar->setFichas(tInt);
        }

        // Carrega Transicoes
        listaNodos = documentoXML.elementsByTagName("Transicao");
        n = listaNodos.count();
        for(i = 0 ; i < n; i++)
        {
            nodoXML = listaNodos.item(i);
            mapaNodos = nodoXML.attributes();

            nodoXML = mapaNodos.namedItem("X");
            if(!nodoXML.isNull())
            {
                X = nodoXML.toAttr().value().toFloat();
            }

            nodoXML = mapaNodos.namedItem("Y");
            if(!nodoXML.isNull())
                Y = nodoXML.toAttr().value().toFloat();

            nodoXML = mapaNodos.namedItem("Nome");
            if(!nodoXML.isNull())
                str = nodoXML.toAttr().value();

            id = m_controleRede->novaTransicao();
            transicao = getTransicao(id);
            mapaNomeID[str] = id;

            transicao->setNome(str);
            transicao->setNomeVisivel(true);
            transicao->setPosicao(rPonto(X, Y));
        }

        // Carrega Arcos
        listaNodos = documentoXML.elementsByTagName("Arco");
        n = listaNodos.count();
        for(i = 0 ; i < n; i++)
        {
            nodoXML = listaNodos.item(i);
            mapaNodos = nodoXML.attributes();

            Desenho *de = 0x0, *para = 0x0;
            int custo;

            nodoXML = mapaNodos.namedItem("De");
            if(!nodoXML.isNull())
            {
                str = nodoXML.toAttr().value();
                if(str.at(0) == 'p')
                {
                    de = getLugar(mapaNomeID[str]);
                }else if(str.at(0) == 't')
                {
                    de = getTransicao(mapaNomeID[str]);
                }
            }

            nodoXML = mapaNodos.namedItem("Para");
            if(!nodoXML.isNull())
            {
                str = nodoXML.toAttr().value();
                if(str.at(0) == 'p')
                {
                    para = getLugar(mapaNomeID[str]);
                }else if(str.at(0) == 't')
                {
                    para = getTransicao(mapaNomeID[str]);
                }
            }

            nodoXML = mapaNodos.namedItem("Custo");
            if(!nodoXML.isNull())
            {
                str = nodoXML.toAttr().value();
                custo = str.toInt();
            }else
                custo = 1;

            nodoXML = mapaNodos.namedItem("Nome");
            if(!nodoXML.isNull())
            {
                str = nodoXML.toAttr().value();
            }else
                str.clear();

            if(de != 0x0 && para != 0x0)
            {
                if(de->tipoDesenho() == TD_LUGAR && para->tipoDesenho() == TD_TRANSICAO )
                    id = novoArcoPT(((DLugar*)de)->getIDCP(), ((DTransicao*)para)->getIDCP(), custo);
                else if (de->tipoDesenho() == TD_TRANSICAO && para->tipoDesenho() == TD_LUGAR)
                    id = novoArcoTP(((DTransicao*)de)->getIDCP(), ((DLugar*)para)->getIDCP(), custo);
                else
                {
                    cout << "Erro ao carregar arco " << str.toStdString() << " pelo XML, arco possui ligacoes invalidas" << endl;
                    continue;
                }
            }else{
                cout << "Erro ao carregar arco " << str.toStdString() << " pelo XML, arco possui ligacoes invalidas" << endl;
                continue;
            }

            mapaNomeID[str] = id;
            arco = getArco(id);

            if(str.size() > 0)
                arco->setNome(str);

//            arco->setPeso(custo); Ja foi definido na criacao do arco

        }

        setNome(nomeArquivo.section('/',-1));
        return true;
    }else
    {
        cout << "Arquivo XML não pode ser lido" << endl;

    }
    return false;
}

bool DRedePetri::carregaXML(QDomElement &elemento)
{
    if(elemento.tagName() != "RedePetri")
    {
        cout << "Erro ao carregar XML RedePetri, nodoXML inlegivel" << endl;
        return false;
    }
    if(!elemento.attributeNode(QString("Nome")).isNull())
        setNome(elemento.attributeNode(QString("Nome")).value());
    else
        setNome(QString("SemNome"));

    cout << "Carregando XML Simples" << endl;
    int i, n;

    QDomNodeList listaNodos;
    QDomNamedNodeMap mapaNodos;
    QDomNode nodoXML;

    // Elementos da rede petri
    map<QString,int> mapaNomeID;

    DLugar *lugar;
    DArco *arco;
    DTransicao *transicao;

    // Temporarios
    float X, Y;
    QString str;
    int tInt, id;

    // Carrega Lugares
    listaNodos = elemento.elementsByTagName("Lugar");
    n = listaNodos.count();
    for(i = 0 ; i < n; i++)
    {
        nodoXML = listaNodos.item(i);
        mapaNodos = nodoXML.attributes();

        nodoXML = mapaNodos.namedItem("X");
        if(!nodoXML.isNull())
            X = nodoXML.toAttr().value().toFloat();

        nodoXML = mapaNodos.namedItem("Y");
        if(!nodoXML.isNull())
            Y = nodoXML.toAttr().value().toFloat();

        nodoXML = mapaNodos.namedItem("Fichas");
        if(!nodoXML.isNull())
            tInt = nodoXML.toAttr().value().toInt();

        nodoXML = mapaNodos.namedItem("Nome");
        if(!nodoXML.isNull())
            str = nodoXML.toAttr().value();

        id = m_controleRede->novoLugar();
        lugar = getLugar(id);
        mapaNomeID[str] = id;


        lugar->setNome(str);
        lugar->setNomeVisivel(true);
        lugar->setPosicao(rPonto(X, Y));
        lugar->setFichas(tInt);
    }

    // Carrega Transicoes
    listaNodos = elemento.elementsByTagName("Transicao");
    n = listaNodos.count();
    for(i = 0 ; i < n; i++)
    {
        nodoXML = listaNodos.item(i);
        mapaNodos = nodoXML.attributes();

        nodoXML = mapaNodos.namedItem("X");
        if(!nodoXML.isNull())
        {
            X = nodoXML.toAttr().value().toFloat();
        }

        nodoXML = mapaNodos.namedItem("Y");
        if(!nodoXML.isNull())
            Y = nodoXML.toAttr().value().toFloat();

        nodoXML = mapaNodos.namedItem("Nome");
        if(!nodoXML.isNull())
            str = nodoXML.toAttr().value();

        id = m_controleRede->novaTransicao();
        transicao = getTransicao(id);
        mapaNomeID[str] = id;

        transicao->setNome(str);
        transicao->setNomeVisivel(true);
        transicao->setPosicao(rPonto(X, Y));
    }

    // Carrega Arcos
    listaNodos = elemento.elementsByTagName("Arco");
    n = listaNodos.count();
    for(i = 0 ; i < n; i++)
    {
        nodoXML = listaNodos.item(i);
        mapaNodos = nodoXML.attributes();

        Desenho *de = 0x0, *para = 0x0;
        int custo;

        nodoXML = mapaNodos.namedItem("De");
        if(!nodoXML.isNull())
        {
            str = nodoXML.toAttr().value();
            if(str.at(0) == 'p')
            {
                de = getLugar(mapaNomeID[str]);
            }else if(str.at(0) == 't')
            {
                de = getTransicao(mapaNomeID[str]);
            }
        }

        nodoXML = mapaNodos.namedItem("Para");
        if(!nodoXML.isNull())
        {
            str = nodoXML.toAttr().value();
            if(str.at(0) == 'p')
            {
                para = getLugar(mapaNomeID[str]);
            }else if(str.at(0) == 't')
            {
                para = getTransicao(mapaNomeID[str]);
            }
        }

        nodoXML = mapaNodos.namedItem("Custo");
        if(!nodoXML.isNull())
        {
            str = nodoXML.toAttr().value();
            custo = str.toInt();
        }else
            custo = 1;

        nodoXML = mapaNodos.namedItem("Nome");
        if(!nodoXML.isNull())
        {
            str = nodoXML.toAttr().value();
        }else
            str.clear();

        if(de != 0x0 && para != 0x0)
        {
            if(de->tipoDesenho() == TD_LUGAR && para->tipoDesenho() == TD_TRANSICAO )
                id = novoArcoPT(((DLugar*)de)->getIDCP(), ((DTransicao*)para)->getIDCP(), custo);
            else if (de->tipoDesenho() == TD_TRANSICAO && para->tipoDesenho() == TD_LUGAR)
                id = novoArcoTP(((DTransicao*)de)->getIDCP(), ((DLugar*)para)->getIDCP(), custo);
            else
            {
                cout << "Erro ao carregar arco " << str.toStdString() << " pelo XML, arco possui ligacoes invalidas" << endl;
                continue;
            }
        }else{
            cout << "Erro ao carregar arco " << str.toStdString() << " pelo XML, arco possui ligacoes invalidas" << endl;
            continue;
        }

        mapaNomeID[str] = id;
        arco = getArco(id);

        if(str.size() > 0)
            arco->setNome(str);

//            arco->setPeso(custo); Ja foi definido na criacao do arco

    }

    return true;

}

bool DRedePetri::geraXML(const QString &nomeArquivo)
{
    FILE *arq;
    arq = fopen((nomeArquivo.toStdString().c_str()), "w+");

    if(arq != 0x0)
    {
        QDomDocument doc;
        QDomNode raiz;
        geraXML(doc, raiz);

        QTextStream Qs(arq);
        doc.save(Qs,4);
        fclose(arq);
        return true;
    }else
    {
        cout << "Problema ao salvar XML RedePetri" << endl;
    }
    return false;
}

bool DRedePetri::geraXML(QDomDocument &doc, QDomNode &raiz)
{
    unsigned i =0;

    QDomNode mRaiz; // Raiz da RedePetri
    QDomElement e = doc.createElement("RedePetri");
    e.setAttribute("Nome" , m_nome);

    if(raiz.isNull())
        raiz = mRaiz = doc.appendChild(e);
    else
        mRaiz = raiz.appendChild(e);

    // Lugares
    DLugar* il;
    for(i = 0; i < m_lugares.size(); i++)
    {
        il = m_lugares[i];
        e = doc.createElement("Lugar");
        e.setAttribute("Nome", il->getNome());
        e.setAttribute("Fichas", il->fichas());
        e.setAttribute("X", il->getCentro().x());
        e.setAttribute("Y", il->getCentro().y());
        mRaiz.appendChild(e);
    }

    // Transições
    DTransicao* it;
    for(i = 0; i < m_transicoes.size(); i++)
    {
        it = m_transicoes[i];
        e = doc.createElement("Transicao");
        e.setAttribute("Nome", it->getNome());
        e.setAttribute("X", it->x());
        e.setAttribute("Y", it->y());
        mRaiz.appendChild(e);
    }

    // Arcos
    DArco* ia;
    DComponentePetri *origem, *destino;
    for(i = 0 ; i < m_arcos.size(); i++)
    {
        ia = m_arcos[i];
        origem = ia->getOrigem(); destino = ia->getDestino();
        if( origem != 0x0 && destino != 0x0)
        {
            e = doc.createElement("Arco");
            e.setAttribute("Nome", ia->getNome());
            e.setAttribute("Custo", ia->getPeso());
            if(origem->ehLugar() && destino->ehTransicao())
            {
                e.setAttribute("De", QString("p%1").arg(origem->getIDCP()));
                e.setAttribute("Para", QString("t%1").arg(destino->getIDCP()));
            }else if(origem->ehTransicao() && destino->ehLugar())
            {
                e.setAttribute("De", QString("t%1").arg(origem->getIDCP()));
                e.setAttribute("Para", QString("p%1").arg(destino->getIDCP()));
            }
            mRaiz.appendChild(e);
        }
    }
}

void DRedePetri::dNovoLugar(unsigned id)
{
    DLugar *novoL = new DLugar;
    novoL->setNome(QString("p%1").arg(id));
    novoL->setIDCP(id);
    novoL->setControle(m_controleRede);

    if(id == m_lugares.size())
    {
        m_lugares.push_back(novoL);
    }else if( id > m_lugares.size())
    {
        m_lugares.resize((id+1)*2, 0x0);
        m_lugares[id] = novoL;
    }else
    {
        dDeletaLugar(id);
        m_lugares[id] = novoL;
    }

    novoDesenho(novoL);
}

void DRedePetri::dNovaTransicao(unsigned id)
{
    DTransicao *novaT = new DTransicao;
    novaT->setNome(QString("t%1").arg(id));
    novaT->setIDCP(id);
    novaT->setControle(m_controleRede);

    if(id == m_transicoes.size())
    {
        m_transicoes.push_back(novaT);
    }else if( id > m_transicoes.size())
    {
        m_transicoes.resize((id+1)*2, 0x0);
        m_transicoes[id] = novaT;
    }else
    {
        dDeletaTransicao(id);
        m_transicoes[id] = novaT;
    }

    novoDesenho(novaT);
}

void DRedePetri::dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso)
{
    DLugar *lugar = getLugar(de);
    DTransicao *transicao = getTransicao(para);

    // Verifica se o Lugar de origem e a transicao de destino existe
    if(lugar == 0x0 || transicao == 0x0)
        return;

    DArco *novoA;

    // Verifica se o arco ja existe
    if(id < m_arcos.size() && m_arcos[id] != 0x0)
    {
        novoA = m_arcos[id];
    }else
    {
        // Cria o arco
        novoA = new DArco;
    }

    novoA->setControle(m_controleRede);
    novoA->setNome(QString("a%1").arg(id));
    novoA->setLigacaoIni(lugar);
    novoA->setLigacaoFim(transicao);
    novoA->setPeso(peso);
    novoA->setFake(false);
    novoA->setIDCP(id);

    // Indexa o arco
    if(id == m_arcos.size())
    {
        m_arcos.push_back(novoA);
    }else if( id > m_arcos.size())
    {
        m_arcos.resize((id+1)*2, 0x0);
        m_arcos[id] = novoA;
    }else
    {
        dDeletaArco(id);
        m_arcos[id] = novoA;
    }

    // Adiciona novo desenho
    novoDesenho(novoA);
}

void DRedePetri::dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso)
{
    DTransicao *transicao = getTransicao(de);
    DLugar *lugar = getLugar(para);

    // Verifica de a transicao de origem e o lugar de destino existem
    if(lugar == 0x0 || transicao == 0x0)
        return;

    DArco *novoA = new DArco;
    novoA->setControle(m_controleRede);
    novoA->setNome(QString("a%1").arg(id));
    novoA->setLigacaoIni(transicao);
    novoA->setLigacaoFim(lugar);
    novoA->setPeso(peso);
    novoA->setIDCP(id);

    if(id == m_arcos.size())
    {
        m_arcos.push_back(novoA);
    }else if( id > m_arcos.size())
    {
        m_arcos.resize((id+1)*2, 0x0);
        m_arcos[id] = novoA;
    }else
    {
        dDeletaArco(id);
        m_arcos[id] = novoA;
    }

    novoDesenho(novoA);
}


/**
 * @brief
 *  Deleta o desenho de uma transicao
 * @param id
 */
void DRedePetri::dDeletaTransicao(unsigned id)
{
    if(id < m_transicoes.size())
    {
        if(m_transicoes[id] != 0x0)
        {
            delete m_transicoes[id];
        }
        m_transicoes[id] = 0x0;
    }
}


/**
 * @brief
 *  Deleta o desenho de um lugar
 * @param id - id do lugar
 */
void DRedePetri::dDeletaLugar(unsigned id)
{
    if(id < m_lugares.size())
    {
        if(m_lugares[id] != 0x0)
        {
            delete m_lugares[id];
        }
        m_lugares[id] = 0x0;
    }
}


/**
 * @brief
 *  Deleta o desenho de um arco
 * @param id - id do arco
 */
void DRedePetri::dDeletaArco(unsigned id)
{
    if(id < m_arcos.size())
    {
        if(m_arcos[id] != 0x0)
        {
            // Se o arco não for fake, ele e deletado
            if(!m_arcos[id]->fake())
                delete m_arcos[id];
            // Se for fake ele continuara existindo apenas na visualizacao que removeu o arco
        }
        m_arcos[id] = 0x0;
    }
}


/**
 * @brief
 *  Define o peso do arco no desenho
 * @param id - id do arco
 * @param peso - novo peso do arco
 */
void DRedePetri::dSetPesoArco(unsigned id, unsigned peso)
{
    DArco *arco = getArco(id);
    if(arco != 0x0)
    {
        // Define o peso do arco apenas no desenho
        arco->dSetPeso(peso);
    }
}


/**
 * @brief
 *  Define o numero de fichas do lugar no desenho
 * @param id - ID do lugar
 * @param numFichas - numero de fichas
 */
void DRedePetri::dSetFichas(unsigned id, unsigned numFichas)
{
    DLugar *lugar = getLugar(id);
    if(lugar != 0x0)
    {
        lugar->dSetFichas(numFichas);
    }
}

unsigned DRedePetri::dPesoArco(unsigned id)
{
    const DArco *arco = getArco(id);
    if(arco != 0x0)
    {
        return arco->getPeso();
    }
    return 0;
}

unsigned DRedePetri::dFichas(unsigned id)
{
    DLugar *lugar = getLugar(id);
    if(lugar != 0x0)
    {
        return lugar->fichas();
    }
    return 0;
}

void DRedePetri::dExecutaTransicao(unsigned id)
{
    // Desenho nao faz nada quando uma transicao e executada
}


/**
 * @brief
 *  Cria uma nova transicao no modelo
 */
void DRedePetri::SNovaTransicao()
{
    // Uma nova transicao é criada no modelo
    // o controlador é avisado, e ele redistribui
    // o comando de nova transicao para todas
    // visualizacoes e para o modelo
    m_controleRede->novaTransicao();
}


/**
 * @brief
 *  Cria um novo arco na visualizacao,
 * o arco é criado no modelo quando uma
 * origem e um destino for definido
 */
void DRedePetri::SNovoArco()
{
    // Este arco criado nao é indexado
    // porque ele nao faz parte do modelo
    // nao possui um ID

    DArco *d = new DArco;
    d->setControle(m_controleRede);
    d->setFake(true);
    d->defineSeta(rPonto(20,20) , rPonto(80,50));
    novoDesenho(d);
}


/**
 * @brief
 *  Cria um novo lugar no modelo
 */
void DRedePetri::SNovoLugar()
{
    m_controleRede->novoLugar();
}

void DRedePetri::novaVisualizacao()
{
    DRedePetri *novaV = new DRedePetri;
    novaV->setControlador(m_controleRede);
    m_pai->novoDesenho(novaV);
}

void DRedePetri::geraXML()
{
    FILE *teste;
    teste = fopen("teste.xml", "w+");

    cout << "======== Teste XML ========" << endl;
    QDomDocument d;

    QFile xml("books.xml");
    if(xml.open(QIODevice::ReadWrite))
    {
        d.setContent(&xml);
        QDomNode n = d.firstChild();
        while (!n.isNull())
        {
            if (n.isElement())
            {
                QDomElement e = n.toElement();
                cout << "Element name: " << e.tagName().toStdString()
                     << ',' << e.attribute("category").toStdString() << endl;

                QDomElement novoE = d.createElement("Aleatorio");
                novoE.setAttribute("Teste" , "HAHAHA");


                QDomText txt = d.createTextNode("Texto de Teste!!!");
                novoE.appendChild(txt);

                e.appendChild(novoE);

                if(e.tagName() == "bookstore")
                {   cout << "BINGO!!" << endl;
                    n = n.firstChild();
                    continue;
                }

                if(e.attribute("category") == "web")
                {
                    e.setAttribute("Web", "www");
                    n = e.firstChild();
                    continue;
                }
                if(e.tagName() == "year")
                {
                    n = e.firstChild();
                    if(n.isText())
                    {
                        QDomText txt = d.createTextNode("texto ano");
                        e.appendChild(txt);
                    }
                }
            }
            if(n.isAttr())
            {
                QDomAttr a = n.toAttr();
                cout << "Attribut name: " << a.name().toStdString()
                     << " value: " << a.value().toStdString() << endl;
            }
            if(n.isCDATASection())
            {
                cout << '1' << endl;
            }
            if(n.isCharacterData())
                cout << '2' << endl;
            if(n.isComment())
                cout << '3' << endl;
            if(n.isDocument())
                cout << '4' << endl;
            if(n.isElement())
                cout << '5' << endl;
            if(n.isEntity())
                cout << '7' << endl;
            if(n.isNotation())
                cout << '7' << endl;
            if(n.isText())
                cout << '8' << endl;
            if(n.isProcessingInstruction())
                cout << '9' << endl;

//            n = n.firstChild();

            n = n.nextSibling();
        }
        QTextStream f(teste);
        d.save(f,5);
    }else cout << "Erro ao abrir xml\n";

    fclose(teste);
    cout << "======== Teste XML FIM=====" << endl;
}

void DRedePetri::geraXMLSimples()
{
    QString nomeArquivo = QFileDialog::getSaveFileName(widget(), "Salvar XML", QString(),"XML (*.xml)");
    geraXML(nomeArquivo);
}

void DRedePetri::carregaXMLSimples()
{
    QString nomeArquivo = QFileDialog::getOpenFileName(widget(), "Abrir xml", QString(), "XML (*.xml)" );
    if(!nomeArquivo.isNull())
    {
        m_controleRede->deletaTudo();

        QDomDocument doc;
        QFile file(nomeArquivo);

        if (!file.open(QIODevice::ReadOnly))
            return;
        if (!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement docElem = doc.documentElement();
        QDomNode nodo = docElem.firstChild();

        while(!nodo.isNull())
        {
            QDomElement e = nodo.toElement();
            if(!e.isNull())
            {
                if(e.tagName() == "RedePetri")
                    carregaXML(e);
                break;
            }
            nodo = nodo.nextSibling();
        }
    }
}

void DRedePetri::imprimeRede()
{
//    m_rede->imprime_incidencia();
//    m_rede->imprime_pos();
//    m_rede->imprime_pre();
//    m_rede->imprime_marcacao();
}

void DRedePetri::geraGrafoCobertura()
{
    if(m_pai != 0x0 && m_controleRede != 0x0)
    {
        int limVerticesExplorados = -1;

        // Dialogo com o usuário
        DialogGrafoCobertura dialogo(widget() , &limVerticesExplorados);
        dialogo.exec();

        if(limVerticesExplorados > 0 )
        {
            // Cria o visualizador de grafos
            VisualizadorGrafo *grafo = new VisualizadorGrafo;
            m_pai->novoDesenho(grafo); // Adiciona ao container pai

            // Cria o grafo (dados)
            GrafoNome *modeloGrafo = new GrafoNome(string("Grafo de Cobertura"));


            // Se não foi possivel explorar todos os vértices devido
            // ao limite imposto
            if(!m_controleRede->modelo()->Enumera(*modeloGrafo, limVerticesExplorados))
            {
                // Avisa o usuario
                QMessageBox msg;
                msg.setText("Gerando Grafo de Cobertura da RP");
                msg.setInformativeText("A busca atingiu o limite de vertices antes de explorar todos os estados da RP");
                msg.setIcon(QMessageBox::Information);
                msg.exec();
            }
            grafo->setModelo(modeloGrafo);
        }
    }

/*    if(m_pai != 0x0)
    {
        Grafo<char> *grafo = new Grafo < char >;
        grafo->novoVertice('a');
        grafo->novoVertice('b');
        grafo->novoVertice('c');
        grafo->novoVertice('d');
        grafo->novoVertice('e');
        grafo->novoVertice('f');
        grafo->novoVertice('g');
        grafo->novoVertice('h');
        grafo->novoVertice('i');
        grafo->novoVertice('j');

        grafo->novaAresta('a', 'b');
        grafo->novaAresta('c','a');
        grafo->novaAresta('d','a');
        grafo->novaAresta('e','a');
        grafo->novaAresta('f','a');
        grafo->novaAresta('g','a');
        grafo->novaAresta('h','a');
        grafo->novaAresta('i','a');
        grafo->novaAresta('j','a');

        DGrafo *vgrafo = new DGrafo;
        m_pai->novoDesenho(vgrafo);
        vgrafo->setModelo(grafo);
    }
*/
}

void DRedePetri::alinhar()
{
    Container::alinhar();
}

void DRedePetri::deleta()
{
    delete this;
}

void DRedePetri::criaVisualizacaoTCP()
{
    m_visualizacaoTCP = new ComunicadorRedePetri("localhost", 12345);
    m_controleRede->addVisualizacao(m_visualizacaoTCP);
}




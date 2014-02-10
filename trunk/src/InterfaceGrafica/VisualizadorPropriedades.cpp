#include "VisualizadorPropriedades.h"
#include "WidgetProgramacao.h"

VisualizadorPropriedades::VisualizadorPropriedades(QWidget *parent) :
    QTreeWidget(parent)
{
    connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)), this,SLOT(alteracaoItem(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this,SLOT(duploClique(QTreeWidgetItem*,int)));
}

void VisualizadorPropriedades::inseriDesenho(QTreeWidgetItem *raiz, Desenho *desenho)
{
    // Ponteiro temporario para apantar para algum item
    QTreeWidgetItem *item;


    item = new QTreeWidgetItem();
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setText(0,QString("Nome"));
    item->setText(1,desenho->getNome());
    raiz->addChild(item);

    QTreeWidgetItem *geometrico = new QTreeWidgetItem(QStringList(QString("Geometrico")));
        item = new QTreeWidgetItem();
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            item->setText(0, QString("X"));
            item->setText(1, QString("%1").arg(desenho->x()));
        geometrico->addChild(item);
        item = new QTreeWidgetItem();
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            item->setText(0, QString("Y"));
            item->setText(1, QString("%1").arg(desenho->y()));
        geometrico->addChild(item);
        item = new QTreeWidgetItem();
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            item->setText(0, QString("Largura"));
            item->setText(1, QString("%1").arg(desenho->largura()));
        geometrico->addChild(item);
        item = new QTreeWidgetItem();
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            item->setText(0, QString("Altura"));
            item->setText(1, QString("%1").arg(desenho->altura()));
        geometrico->addChild(item);

        raiz->addChild(geometrico);
}

bool VisualizadorPropriedades::alteracaoDesenho(QTreeWidgetItem *itemAlterado, int coluna)
{
    if(contem(itemAlterado, "Geometrico"))
    {
        if(contem(itemAlterado, "X"))
        {
            cout << "Alteracao posicao X" << endl;
            desenhoVisualizado->setX(itemAlterado->text(1).toFloat());
            desenhoVisualizado->atualizaVizualizacao();
            return true;
        }else if(contem(itemAlterado, "Y"))
        {
            cout << "Alteracao posicao Y" << endl;
            desenhoVisualizado->setY(itemAlterado->text(1).toFloat());
            desenhoVisualizado->atualizaVizualizacao();
            return true;
        }else if(contem(itemAlterado, "Largura"))
        {
            cout << "Alteracao posicao Largura" << endl;
            desenhoVisualizado->setLargura(itemAlterado->text(1).toInt());
            desenhoVisualizado->atualizaVizualizacao();
            return true;
        }else if(contem(itemAlterado, "Altura"))
        {
            cout << "Alteracao posicao Altura" << endl;
            desenhoVisualizado->setAltura(itemAlterado->text(1).toInt());
            desenhoVisualizado->atualizaVizualizacao();
            return true;
        }
    }else if( contem(itemAlterado, "Nome"))
    {
        desenhoVisualizado->setNome(itemAlterado->text(coluna));
        desenhoVisualizado->atualizaVizualizacao();
        cout << "Alteracao Nome" << endl;
        return true;
    }
    return false;
}

void VisualizadorPropriedades::inseriLugar(QTreeWidgetItem *raiz, DLugar *lugar)
{
    QTreeWidgetItem *numFicha = new QTreeWidgetItem;
    numFicha->setText(0, QString("Numero de Fichas"));
    numFicha->setText(1,QString("%1").arg(lugar->fichas()));

    raiz->addChild(numFicha);

    QTreeWidgetItem *fichas = new QTreeWidgetItem;
    fichas->setText(0, "Fichas");

    if(lugar->fichas() > 0)
    {
    /// @todo - Implementar o disparo de transição transportando a informação da ficha para o lugar resultante, só apos isso, o visualizador podera exibir informações da ficha

        /*
          Comentado até a implementação do movimento da informação das fichas.
        int i, n = lugar->getNumFichas();
        for(i = 0 ; i < n; i++)
        {
            QTreeWidgetItem *infoFicha = new QTreeWidgetItem;
            infoFicha->setText(0, QString("Inf. Ficha %1").arg(i));
            infoFicha->setText(1,QString(lugar->getInfoFicha(i).c_str()));
            infoFicha->setText(2,QString("%1").arg(i));
            fichas->addChild(infoFicha);
        }
        */
    }

    raiz->addChild(fichas);

}

bool VisualizadorPropriedades::alteracaoLugar(QTreeWidgetItem *itemAlterado, int coluna)
{
    if(contem(itemAlterado, "Lugar"))
    {
        // Conversao de tipo garantida se contem lugar
        DLugar *lugar = (DLugar*) desenhoVisualizado;
        return true;
    }
    return false;
}

void VisualizadorPropriedades::inseriTransicao(QTreeWidgetItem *raiz, DTransicao *transicao)
{
    QTreeWidgetItem *infoTransicao = new QTreeWidgetItem;
    QString tInfo(transicao->informacao().c_str());

    infoTransicao->setText(0, QString("Dados"));
    infoTransicao->setText(1, tInfo);

    raiz->addChild(infoTransicao);
}

bool VisualizadorPropriedades::alteracaoTransicao(QTreeWidgetItem *itemAlterado, int coluna)
{
    return false;
}

void VisualizadorPropriedades::inseriArco(QTreeWidgetItem *raiz, DArco *arco)
{
    QTreeWidgetItem *item;
    const Desenho *desenho;

    item = new QTreeWidgetItem();
    item->setText(0, QString("Origem"));

    desenho = arco->getLigacaoIni();
    if(desenho != 0x0)
    {
        item->setText(1, desenho->getNome());
    }else
    {
        item->setText(1, QString("Sem Origem"));
    }
    raiz->addChild(item);

    item = new QTreeWidgetItem();
    item->setText(0, QString("Destino"));

    desenho = arco->getLigacaoFim();
    if(desenho != 0x0)
    {
        item->setText(1, desenho->getNome());
    }else
    {
        item->setText(1, QString("Sem Destino"));
    }

    raiz->addChild(item);

    item = new QTreeWidgetItem();
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setText(0, QString("Custo"));
    item->setText(1, QString("%1").arg(arco->getPeso()));

    raiz->addChild(item);
}

bool VisualizadorPropriedades::alteracaoArco(QTreeWidgetItem *itemAlterado, int coluna)
{
    if(contem(itemAlterado, "Arco"))
    {
        if(contem(itemAlterado, "Custo"))
        {
            DArco *arco = (DArco*) desenhoVisualizado;
            arco->setPeso(itemAlterado->text(1).toInt());
            arco->atualizaVizualizacao();
            cout << "Alteracao de custo do arco" << endl;
        }
        return true;
    }
    return false;
}

void VisualizadorPropriedades::inseriRedePetri(QTreeWidgetItem *raiz, DRedePetri *redePetri)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString("Numero Lugares"));
        item->setText(1, QString("%1").arg(redePetri->getNumeroLugar()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
    raiz->addChild(item);

    item = new QTreeWidgetItem;
        item->setText(0, QString("Numero Transicoes"));
        item->setText(1, QString("%1").arg(redePetri->getNumeroTramsicao()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
    raiz->addChild(item);

    item = new QTreeWidgetItem;
        item->setText(0, QString("Numero Arcos"));
        item->setText(1, QString("%1").arg(redePetri->getNumeroArco()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
        raiz->addChild(item);

}

bool VisualizadorPropriedades::alteracaoRedePetri(QTreeWidgetItem *itemAlterado, int coluna)
{
    return false;
}

void VisualizadorPropriedades::inseriVariavelAmbiente(QTreeWidgetItem *raiz, DVariavelAmbiente *variavelAmbiente)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString("Nome"));
        item->setText(1, QString("%1").arg(variavelAmbiente->getNome()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
    raiz->addChild(item);

    item = new QTreeWidgetItem;
        item->setText(0, QString("Valor"));
        item->setText(1, QString("%1").arg(variavelAmbiente->valor()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
    raiz->addChild(item);
}

bool VisualizadorPropriedades::alteracaoVariavelAmbiente(QTreeWidgetItem *itemAlterado, int coluna)
{
    if(contem(itemAlterado, "Variavel de Ambiemte"))
    {
        if(contem(itemAlterado, "Nome"))
        {
//            DArco *arco = (DArco*) desenhoVisualizado;
//            arco->setCusto(itemAlterado->text(1).toInt());
//            arco->atualizaVizualizacao();
            cout << "Alteracao de custo do arco" << endl;
        }
        return true;
    }
    return false;
}

bool VisualizadorPropriedades::contem(QTreeWidgetItem *item, QString texto)
{
    QTreeWidgetItem *navegador;
    navegador = item;

    while(navegador != 0x0)
    {
        if(navegador->text(0) == texto || navegador->text(1) == texto)
        {
            return true;
        }
        navegador = navegador->parent();
    }
    return false;
}

void VisualizadorPropriedades::alteracaoItem(QTreeWidgetItem *itemAlterado, int coluna)
{
    // Descobre da onde é o item alterado (deve existir soluções melhores que essa, mas essa por enquanto quebra o galho)

    if(alteracaoDesenho(itemAlterado, coluna))
        return;

    if(alteracaoLugar(itemAlterado, coluna))
        return;

    if(alteracaoTransicao(itemAlterado, coluna))
        return;

    if(alteracaoArco(itemAlterado, coluna))
        return;

    if(alteracaoRedePetri(itemAlterado, coluna))
        return;
}

void VisualizadorPropriedades::duploClique(QTreeWidgetItem *itemClicado, int coluna)
{
    cout << "Duplo clique em " << itemClicado->text(coluna).toLocal8Bit().constData() << endl;
    if(contem(itemClicado, "Lugar"))
    {
        DLugar *lugar = (DLugar*) desenhoVisualizado;
        if(itemClicado->columnCount() == 3)
        {
            WidgetProgramacao *wp = new WidgetProgramacao(parentWidget());
            wp->editaInfoFicha(lugar, itemClicado->text(2).toInt());
            wp->show();
        }
    }
}


/**
 * @brief Este metodo muda a visualização da arvore de propriedades para
 * o desenho passado por parametro
 *
 * @param desenho - Desenho que sera visualizado
 */
void VisualizadorPropriedades::visualizaDesenho(Desenho *desenho)
{
    // Apaga visualização anterior
    /// @todo - Confirmar se o metodos clear() da QTreeWidget deleta os itens.
    clear();

    // Salva referencia para o desenho que esta snedo visualizado
    desenhoVisualizado = desenho;

    // Define o numero de colunas
    setColumnCount(2);

    // Define o cabeçalho
    QStringList cabecalho;
    cabecalho << QString("Propriedade") << QString("Valor");
    setHeaderLabels(cabecalho);

    if(desenho == 0x0)
        return;

    // Ponteiro temporario para apantar para algum item
    QTreeWidgetItem *item;

    // Uma lista temporaria de itens
    QList<QTreeWidgetItem *> items;

//    cout << "Atualizando visuzalizacao de propriedades" << endl;

    item = new QTreeWidgetItem((QTreeWidgetItem*)0x0,QStringList(QString("Desenho")));

    // Insere propriedades de um desenho
    inseriDesenho(item, desenho);

    items << item;

    // Insere propriedades especificas de cada desenho
    switch(desenho->tipoDesenho())
    {
        case TD_LUGAR:
            item = new QTreeWidgetItem((QTreeWidgetItem*)0x0,QStringList(QString("Lugar")));
            inseriLugar(item, (DLugar*) desenho);
        break;
        case TD_TRANSICAO:
            item = new QTreeWidgetItem((QTreeWidgetItem*)0x0,QStringList(QString("Transicao")));
            inseriTransicao(item, (DTransicao*) desenho);
        break;
        case TD_ARCO:
            item = new QTreeWidgetItem((QTreeWidgetItem*)0x0,QStringList(QString("Arco")));
            inseriArco(item, (DArco*) desenho);
        break;
        case TD_REDE_PETRI:
            item = new QTreeWidgetItem((QTreeWidgetItem*)0x0,QStringList(QString("Rede Petri")));
            inseriRedePetri(item, (DRedePetri*) desenho);
        break;
        default:
            item = 0x0;
        break;
        case TD_VARIAVEL_AMBIENTE:
            item = new QTreeWidgetItem((QTreeWidgetItem*)0x0,QStringList(QString("Variavel de Ambiemte")));
            inseriVariavelAmbiente(item , (DVariavelAmbiente*) desenho);
        break;
    }

    if(item)
        items << item;

    // Adiciona os itens na Arvore
    insertTopLevelItems(0,items);

    expandAll();
}

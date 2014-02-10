#include "ControladorRede.h"



/**
 * @brief
 *  Atualiza a visualização das fichas do modelo,
 * esse metodo deve ser chamado toda vez que o modelo
 * sofrer uma alteração de fichas
 */
void ControladorRede::atualizaVisualizacaoFichas()
{
    list<Lugar*>::iterator iP;
    list<IVRedePetri*>::iterator visualizacao;

    unsigned id;
    // Para cada lugar P do modelo
    for(iP = m_modelo->lugarBegin(); iP != m_modelo->lugarEnd() ; iP++)
    {
        id = (*iP)->getIDLocal(); // Pega o ID do lugar no modelo

        // Para cada visualizacao do controle
        for(visualizacao = m_visualizacoes.begin() ; visualizacao != m_visualizacoes.end() ; visualizacao++)
            (*visualizacao)->dSetFichas(id,m_modelo->Numero_Fichas(id)); // Define o numero de fichas
    }
}

void ControladorRede::atualizaVisuzalizacao(IVRedePetri *visualizacao)
{
    unsigned id;
    Arco *a;

    // Atualiza Lugares
    list<Lugar*>::iterator iP;
    for(iP = m_modelo->lugarBegin(); iP != m_modelo->lugarEnd() ; iP++)
    {
        id = (*iP)->getIDLocal();
        visualizacao->dNovoLugar(id);
        visualizacao->dSetFichas(id,m_modelo->Numero_Fichas(id));
    }

    // Atualiza Transicoes
    list<Transicao*>::iterator iT;
    for(iT = m_modelo->transicaoBegin(); iT != m_modelo->transicaoEnd() ; iT++)
    {
        id = (*iT)->getIDLocal();
        visualizacao->dNovaTransicao(id);
    }

    // Atualiza Arcos
    list<Arco*>::iterator iA;
    for(iA = m_modelo->arcoBegin(); iA != m_modelo->arcoEnd() ; iA++)
    {
        a = *iA;
        switch(a->tipo())
        {
        case ARCO_PT:
            visualizacao->dNovoArcoPT(a->id(),a->de(),a->para(),a->peso());
        break;
        case ARCO_TP:
            visualizacao->dNovoArcoTP(a->id(),a->de(),a->para(),a->peso());
        break;
        }
    }
}

ControladorRede::ControladorRede()
{
    m_modelo = 0x0;
}

ControladorRede::~ControladorRede()
{
    if(!m_visualizacoes.empty())
    {
        cout << "Erro controlador de rede com visualizacoes" << endl;
    }

    if(m_modelo != 0x0)
    {
        delete m_modelo;
        m_modelo = 0x0;
    }
}

void ControladorRede::setModelo(RedePetri *modelo)
{
    m_modelo = modelo;
}

void ControladorRede::addVisualizacao(IVRedePetri* visualizacao)
{
    if(visualizacao != 0x0)
    {
        m_visualizacoes.push_back(visualizacao);
        atualizaVisuzalizacao(visualizacao);
    }
}


/**
 * @brief
 *  Remove uma visualizacao, se o controlador
 * ficar sem visualizacoes, ele se auto deleta
 * também deleta o modelo.
 * @param visualizacao - Visualização que sera
 * removida.
 */
void ControladorRede::removeVisualizacao(IVRedePetri *visualizacao)
{
    m_visualizacoes.remove(visualizacao);
    if(m_visualizacoes.empty())
    {
        delete this;
    }
}

RedePetri *ControladorRede::modelo()
{
    return m_modelo;
}

const RedePetri *ControladorRede::modelo() const
{
    return m_modelo;
}

unsigned ControladorRede::novoLugar()
{
    unsigned id = m_modelo->Novo_Lugar();

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dNovoLugar(id);
    }
    return id;
}

unsigned ControladorRede::novaTransicao()
{
    unsigned id = m_modelo->Nova_Transicao();

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dNovaTransicao(id);
    }
    return id;
}

unsigned ControladorRede::novoArcoPT(unsigned de, unsigned para, unsigned peso)
{
    unsigned id = m_modelo->Novo_Arco_PT(de,para, peso);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dNovoArcoPT(id,de,para,peso);
    }
    return id;
}

unsigned ControladorRede::novoArcoTP(unsigned de, unsigned para, unsigned peso)
{
    unsigned id = m_modelo->Novo_Arco_TP(de,para, peso);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dNovoArcoTP(id,de,para,peso);
    }

    return id;
}

bool ControladorRede::deletaTransicao(unsigned id)
{
    m_modelo->Exclui_Transicao(id);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dDeletaTransicao(id);
    }
    return true;
}

bool ControladorRede::deletaLugar(unsigned id)
{
    m_modelo->Exclui_Lugar(id);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dDeletaLugar(id);
    }
    return true;
}

bool ControladorRede::deletaArco(unsigned id)
{
    /// @todo
    m_modelo->Exclui_Arco(id);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dDeletaArco(id);
    }
    return true;
}

bool ControladorRede::deletaTudo()
{
    list<int> lista;
    list<int>::iterator i;

    // Deleta Arcos
    list<Arco*>::iterator iA;
    for(iA = m_modelo->arcoBegin(); iA != m_modelo->arcoEnd() ; iA++)
    {
        lista.push_back((*iA)->id());
    }
    for(i = lista.begin(); i != lista.end() ; i++)
    {
        deletaArco(*i);
    }
    lista.clear();

    // Deleta Lugares
    list<Lugar*>::iterator iP;
    for(iP = m_modelo->lugarBegin(); iP != m_modelo->lugarEnd() ; iP++)
    {
        lista.push_back((*iP)->getIDLocal());
    }
    for(i = lista.begin(); i != lista.end() ; i++)
    {
        deletaLugar(*i);
    }
    lista.clear();

    // Deleta Transicoes
    list<Transicao*>::iterator iT;
    for(iT = m_modelo->transicaoBegin(); iT != m_modelo->transicaoEnd() ; iT++)
    {
        lista.push_back((*iT)->getIDLocal());
    }
    for(i = lista.begin(); i != lista.end() ; i++)
    {
        deletaTransicao(*i);
    }

    lista.clear();

    return true;

}

bool ControladorRede::deletaArcoPT(unsigned de, unsigned para)
{
    /// @todo
//    m_modelo->Exclui_Arco_PT(de,para);

//    list<IVRedePetri*>::iterator i;
//    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
//    {
//        IVRedePetri::dDeletaArco()
//        (*i)->dDeletaLugar(id);
//    }
    cout << "Erro deletaArcoPT nao implementado" << endl;
    return false;
}

bool ControladorRede::deletaArcoTP(unsigned de, unsigned para)
{
    /// @todo
//    m_modelo->Exclui_Arco_TP(de,para);

//    list<IVRedePetri*>::iterator i;
//    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
//    {
//        IVRedePetri::dDeletaLugar(id)
//        (*i)->dDeletaLugar(id);
//    }
    cout << "Erro deletaArcoTP nao implementado" << endl;
    return false;
}

bool ControladorRede::setPesoArco(unsigned id, unsigned peso)
{
    m_modelo->Define_Peso(id,peso);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dSetPesoArco(id,peso);
    }

    return true;
}

bool ControladorRede::setPesoArcoPT(unsigned de, unsigned para, unsigned peso)
{
    cout << "Erro setPesoArcoPT nao implementado" << endl;
    /// @todo
    return false;
}

bool ControladorRede::setPesoArcoTP(unsigned de, unsigned para, unsigned peso)
{
    /// @todo
    cout << "Erro setPesoArcoTP nao implementado" << endl;
    return false;
}

bool ControladorRede::setFichas(unsigned id, unsigned numFichas)
{
    m_modelo->Inserir_Fichas(id,numFichas);

    list<IVRedePetri*>::iterator i;
    for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
    {
        (*i)->dSetFichas(id,numFichas);
    }
    return true;
}

unsigned ControladorRede::pesoArco(unsigned id) const
{
    return m_modelo->Custo_Arco(id);
}

unsigned ControladorRede::idArcoPT(unsigned de, unsigned para) const
{
    /// @todo
    cout << "Erro idArcoPT nao implementado" << endl;
    return 0;
}

unsigned ControladorRede::idArcoTP(unsigned de, unsigned para) const
{
    /// @todo
    cout << "Erro idArcoTP nao implementado" << endl;
    return 0;
}

unsigned ControladorRede::fichas(unsigned id) const
{
    return m_modelo->Numero_Fichas(id);
}

bool ControladorRede::sensibilizado(unsigned id) const
{
    return m_modelo->Sensibilizado(id);
}

bool ControladorRede::existeTransicao(unsigned id) const
{
    return m_modelo->existeTransicao(id);
}

bool ControladorRede::existeLugar(unsigned id) const
{
    return m_modelo->existeLugar(id);
}

bool ControladorRede::existeArco(unsigned id) const
{
    return m_modelo->existeArco(id);
}

unsigned ControladorRede::numTransicoes()
{
    return m_modelo->Numero_Transicoes();
}

unsigned ControladorRede::numLugares()
{
    return m_modelo->Numero_Lugares();
}

unsigned ControladorRede::numArcos()
{
    return m_modelo->Numero_Arcos();
}

bool ControladorRede::executaTransicao(unsigned id)
{
    if(m_modelo->Executa_Transicao(id))
    { 
        list<IVRedePetri*>::iterator i;
        for(i = m_visualizacoes.begin(); i!= m_visualizacoes.end(); i++)
            (*i)->dExecutaTransicao(id);

        atualizaVisualizacaoFichas();
        return true;
    }
    return false;
}

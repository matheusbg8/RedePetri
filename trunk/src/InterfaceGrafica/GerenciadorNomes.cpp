
#include "GerenciadorNomes.h"
#include <sstream>
#include <iostream>

bool compStr (const string * a, const string * b)
{return (*a)< (*b);}

string GerenciadorNomes::strNula("");

GerenciadorNomes::GerenciadorNomes()
{

}

GerenciadorNomes::GerenciadorNomes(const GerenciadorNomes &gn)
{
    unsigned maiorID = gn.m_nome.size(),
            i;

    // Nomeia os mesmo elementos do gn
    for(i = 0 ; i < maiorID ; i++)
    {
        // Se elemento esta nomeado
        if(gn.m_nome[i].second == true)
        {
            // Nomeia esse elemento aqui tbm
            setNome(i , m_nome[i].first->first);
        }
    }
}

const GerenciadorNomes &GerenciadorNomes::operator =(const GerenciadorNomes &gn)
{
    unsigned maiorID = gn.m_nome.size(),
            i;

    // Nomeia os mesmo elementos do gn
    for(i = 0 ; i < maiorID ; i++)
    {
        // Se elemento esta nomeado
        if(gn.m_nome[i].second == true)
        {
            // Nomeia esse elemento aqui tbm
            setNome(i , gn.m_nome[i].first->first);
        }
    }
    return *this;
}


/**
 * @brief Cria um novo elemento no mapa de elementos
 * associando um ID a um Nome, como os nomes são utilizados
 * como identificador de elementos, assim como os IDs, eles
 * devem ser unicos, portanto se um novo elemento com
 * o mesmo nome de um elemento já existente for inserido
 * esse novo elemento tera seu nome alterado para se tornar
 * unico, esta alteração sera retornada pelo metodo.
 *  Este metodo também pode ser utilizado para alterar
 * o nome de algum ID, passando um ID ja existente e um
 * novo nome.
 *
 * @param id - ID do elemento
 * @param nome - Nome do elemento
 * @return const string - Nome do elemento adicionado no
 * gerenciador de nomes.
 */
const string& GerenciadorNomes::setNome(unsigned id, const string &nome)
{    
    // Realoca elementos no vetor de indexacao
    if(id >= m_nome.size())
    {
        if(id > 400 && id > m_nome.size()*2)
        {
            // Esta mensagem sera exibido quando existe uma desconfianca de que os
            // IDs não obedecem uma sequencia (talvez esteja acontecendo algum
            // erro de indexacao), devido ao grande buraco causado
            cout << "Gerenciador nome: Quebra muito grande na sequencia de IDs!!" << endl;
        }
        // 2x para evitar varias operacões de realocaão sem nescecidade
        // estrateja utilizado pelo proprio vector quando utilizado o
        // metodo push_back()
        m_nome.resize((id+1)*2, PMiB ( MMAp::iterator() , false));

    }else // Se id ja tem nome
        if(m_nome[id].second == true)
    {
        // Remove elementodo do mapa
        m_mapaNome.erase(m_nome[id].first);
        m_nome[id].second = false;
    }

    unsigned tentativa =1;
    string final;
    PMiB insercao;

    // Tenta Inserir o nome no mapa
    insercao = m_mapaNome.
            insert( pair< const string &, unsigned> (nome , id));

    // Se o nome ja existe
    while(insercao.second == false)
    {
        // Tenta um novo nome
        stringstream ss;
        ss << nome << " (" << tentativa << ')';
        final = ss.str();
        tentativa++;

        // Tenta inserir novo nome
        insercao = m_mapaNome.
                insert( pair< const string &, unsigned> (final , id));
    }

    // Indexa novo nome no vetor
    m_nome[id] = insercao; // copia iterator para first, e bool true para second

    return insercao.first->first;
}

const string &GerenciadorNomes::nome(unsigned id) const
{
    if(id < m_nome.size() && m_nome[id].second == true)
    {
        return (*m_nome[id].first).first;
    }
    return GerenciadorNomes::strNula;
}

int GerenciadorNomes::id(const string &nome) const
{
    MMAp::const_iterator mi = m_mapaNome.find(nome);

    // Se encontrou
    if(mi != m_mapaNome.end())
        return mi->second;

    return -1;
}

void GerenciadorNomes::apaga(unsigned id)
{
    if(id < m_nome.size() && m_nome[id].second == true)
    {
        m_mapaNome.erase(m_nome[id].first);
        m_nome[id].second = false;
    }
}

void GerenciadorNomes::apaga(const string &nome)
{
    int eId = id(nome);
    if(eId != -1)
    {
        apaga((unsigned) eId);
    }
}

const string &GerenciadorNomes::stringNula()
{
    return GerenciadorNomes::strNula;
}

#include "GerenciadorElementos.h"

template<typename Tipo>
GerenciadorElementos<Tipo>::GerenciadorElementos()
{
    m_numElementos = 0;
}

template<typename Tipo>
int GerenciadorElementos<Tipo>::proximoID() const
{
    // Procura na pilha ids que estao em buracos de indexacao
    while(!m_proximos.empty())
    {
        if(!m_indElemento[m_proximos.top()].second)
        {
            return m_proximos.top();
        }else
        {
            m_proximos.pop();
        }
    }

    // Se nao tem nenhum buraco, retorna o proximo id da indexacao
    return m_indElemento.size();
}

template<typename Tipo>
int GerenciadorElementos<Tipo>::adicionaElemento(const Tipo &valor)
{
    int id = proximoID();

    // Verifica se existe espaco para o proximo elemento
    if( id == m_indElemento.size())
    {
        m_elementos.push_front(valor);
        m_indElemento.push_back(make_pair(m_elementos.begin(), true));
    }else if( id < m_indElemento.size())
    {
        m_elementos.push_front(valor);
        m_indElemento[id] = make_pair(m_elementos.begin(), true);
    }else
    {
        cout << "Erro ao adicionar elemento!" << endl;
        return -1;
    }

    m_numElementos++;
    return id;
}

template<typename Tipo>
int GerenciadorElementos<Tipo>::adicionaElemento(const Tipo &valor, int id)
{
    // Verifica se existe espaco para o proximo elemento
    if( id >= m_indElemento.size())
    {
        int i = m_indElemento.size(); // Pega o tamanho antes de redimensionalizar
        m_indElemento.resize( (id+1)*2, make_pair(GerenciadorElementos::iterator(), false));

        // Adiciona buracos gerados na pilha!
        for(i; i < m_indElemento.size() ; i++ )
        {
            if( i != id)
                m_proximos.push(i);
        }
    }else
    {
        // Verifica se o id esta sendo usado
        if(m_indElemento[id].second)
        {
            // Se sim, nao salva elemento retorna -1
            return -1;
        }
    }

    m_elementos.push_front(valor);
    m_indElemento[id] = make_pair(m_elementos.begin(), true);

    m_numElementos++;
    return id;
}

template<typename Tipo>
void GerenciadorElementos<Tipo>::removeElemento(unsigned id)
{
    // Verifica se o elemento existe
    if(existeElemento(id))
    {
        m_elementos.erase(m_indElemento[id].first);
        m_indElemento[id].second = false;

        // Adiciona o espaco desalocado na pilha de buracos
        m_proximos.push(id);
        m_numElementos--;
        return;
    }
    cout << "Erro ao excluir elemento, elemento inexistente, ou indice invpalido" << endl;
}

template<typename Tipo>
/**
 * @brief
 *  Apaga todos os elementos armazendados
 */
void GerenciadorElementos<Tipo>::apagaTudo()
{
    m_elementos.clear();
    m_indElemento.clear();
    m_numElementos =0;

    while(!m_proximos.empty())
        m_proximos.pop();
}

template<typename Tipo>
/**
 * @brief
 *  Retorna o numero de elementos armazenado
 * @return int - Número de elementos armazenado
 */
int GerenciadorElementos<Tipo>::tamanho() const
{
    return m_numElementos;
}


template<typename Tipo>
/**
 * @brief
 *  Retorna o maior indice dos elementos armazenados.
 * @return int
 */
int GerenciadorElementos<Tipo>::maiorIndice() const
{
    return m_indElemento.size()-1;
}

template<typename Tipo>
Tipo & GerenciadorElementos<Tipo>::operator [](int id)
{
    // Se o elemento existe
    if(existeElemento(id))
    {
        return *(m_indElemento[id].first);
    }

    cout << "Erro, acesso a elemento com indice inválido!" << endl;

    return *(m_indElemento[0].first); // O certo seria lançar uma execao
}

template<typename Tipo>
const Tipo & GerenciadorElementos<Tipo>::operator [](int id) const
{
    if(existeElemento(id))
    {
        return *(m_indElemento[id].first);
    }
    cout << "Erro, acesso a elemento com indice inválido!" << endl;

    return *(m_indElemento[0].first); // O certo seria lançar uma execao
}


template<typename Tipo>
bool GerenciadorElementos<Tipo>::existeElemento(unsigned id) const
{
    if(id < m_indElemento.size() && m_indElemento[id].second)
    {
        return true;
    }
    return false;
}

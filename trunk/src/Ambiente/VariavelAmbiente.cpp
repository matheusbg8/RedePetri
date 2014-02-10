#include "VariavelAmbiente.h"
#include "Ambiente.h"
#include <sstream>

#include "LiteralBooleano.h"
#include "LiteralNumero.h"
#include "LiteralString.h"
#include "LiteralVariavel.h"

LivroLiterais VariavelAmbiente::m_livroLiterais;


VariavelAmbiente::VariavelAmbiente(string nome, string valor ):
    NodoAmbiente(nome)
{
    if(m_livroLiterais.vazio())
    {
        m_livroLiterais.addLiteral(LiteralBooleano::fabrica());
        m_livroLiterais.addLiteral(LiteralString::fabrica());
        m_livroLiterais.addLiteral(LiteralNumero::fabrica());
        m_livroLiterais.addLiteral(LiteralVariavel::fabrica());
    }

    m_literal = 0x0;
    // Set valor deve ser chamado apos m_literal = 0x0!!
    // e apos os literais terem sido inicializados
    setValor(valor);

}

/**
 * @brief
 *  Deleta a variavel de ambiente.
 */
VariavelAmbiente::~VariavelAmbiente()
{
    if(m_literal != 0x0)
        delete m_literal;
}


bool VariavelAmbiente::removeVariavel(VariavelAmbiente *variavel)
{
    // Poderia remover pelo ID da variavel tbm (seria mais eficiente)
    // Se for implementado, alterar o destrutor para remover pro id
    // chamando second do iterator map
    return removeNodo(variavel->nome());
}

bool VariavelAmbiente::removeVariavel(const string &nomeVariavel)
{
    return removeNodo(nomeVariavel);
}

const string &VariavelAmbiente::nome() const
{
    return m_nome;
}

const string& VariavelAmbiente::valor() const
{
    return m_valor;
}


/**
 * @brief
 *  Retorna o literal armazenado pela variavel
 * @return Literal
 */

const Literal *VariavelAmbiente::literal() const
{
    return m_literal;
}

void VariavelAmbiente::setValor(const string &valor)
{
    m_valor = valor;

    // Se eu ja possuia um literal
    if(m_literal != 0x0)
        delete m_literal; // deleta

    // Cria um novo
    m_literal = m_livroLiterais.novoLiteral(valor.c_str(), 0x0);
}

const string & VariavelAmbiente::setNome(const string &nome)
{
    // Se nao tem ambiente
    if(m_ambiente == 0x0)
    {   // Variavel é solta, nao depende de ninguem
        m_nome = nome;
        return m_nome;
    }

    // Verifica se o novo nome pode ser definido
    // se existir algum conflito com algum pai
    // o nome é modificado para resolver os conflitos
    string novoNome = encontraNomeDisponivel(nome);


    // Pega o numero de pais da variavel
    int numPais = m_ambiente->m_grafo.numPredecessores(m_id),
            i;
    NodoAmbiente * pai = 0x0;

    // Avisa renomecao para todos pais
    for( i = 0; i < numPais ;i++)
    {
        pai = m_ambiente->getNodo(m_ambiente->m_grafo.predecessor(m_id, i));

        // A renomecao e certa, porque o nome ja foi
        // testado em todos os pais e esta disponivel
        pai->renomeiaNodo(this, novoNome);
    }

    // Finalmente define o novo nome
    m_nome = novoNome;
    return m_nome;
}

unsigned VariavelAmbiente::id() const
{
    return m_id;
}

TipoNodoAmbiente VariavelAmbiente::tipoNodo() const
{
    return NODO_VARIAVEL;
}

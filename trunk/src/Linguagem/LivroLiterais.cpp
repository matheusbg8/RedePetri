#include "LivroLiterais.h"

LivroLiterais::LivroLiterais()
{
}

LivroLiterais::~LivroLiterais()
{
    // OBs.: Os meus literais não precisam
    // ser deletados porque se eles são fábricas
    // eles são declarados de forma estatica
    // pelo proprio literal, e sera desalocado
    // no fim da execução do programa
}

bool LivroLiterais::vazio()
{
    return m_literais.empty();
}


/**
 * @brief
 *  Adiciona uma fabrica de literais no livro
 * para que sejam  identificados.
 *  A ordem que os literais são adicionados
 * é a ordem em que eles são testados.
 * @param fabrica
 */
void LivroLiterais::addLiteral(Literal *fabrica)
{
    if(fabrica != 0x0)
        m_literais.push_back(fabrica);
}


/**
 * @brief
 *  Constroe um literal a partir de uma lista de literais
 * pre determinadas
 * @param expressao - Expressão que sera interpretada
 * @return Literal - Literal criado, ou 0x0 caso nenhum
 * literal consiga interpretar a expressao.
 */
Literal *LivroLiterais::novoLiteral(istream &expressao)
{
    list<Literal*>::iterator li;
    Literal *resultado = 0x0;

    for(li = m_literais.begin() ; li != m_literais.end() ; li++)
    {
        resultado = (*li)->novoLiteral(expressao);
        if(resultado != 0x0)
            break;
    }

    return resultado;
}

Literal *LivroLiterais::novoLiteral(const char *expressao, unsigned *numCaracteresLidos)
{
    list<Literal*>::iterator li;
    Literal *resultado = 0x0;
    unsigned numCarac = 0;

    for(li = m_literais.begin() ; li != m_literais.end() ; li++)
    {
        resultado = (*li)->novoLiteral(expressao, &numCarac);
        if(resultado != 0x0)
            break;
    }

    if(numCaracteresLidos != 0x0)
        *numCaracteresLidos = numCarac;

    return resultado;

}

bool LivroLiterais::interpreta(const char *expressao, list<Literal *> &literais)
{
    const char *navegacao = expressao;
    Literal *novo = 0x0;
    unsigned numCarac;

    while(*navegacao != '\0')
    {
        numCarac = 0;
        novo = novoLiteral(navegacao , &numCarac);

        if(novo != 0x0)
        {
            literais.push_back(novo);
        }else
        {   // Não consegui interpretar toda expressao
            return false;
        }

        navegacao+= numCarac;
        while(*navegacao == ' ' || *navegacao == '\t')
            navegacao++;
    }

    return true;
}

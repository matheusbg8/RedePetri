#include "Expressao.h"

#include "LiteralGenerico.h"
#include "LiteralNumero.h"
#include "LiteralVariavel.h"
#include "LiteralOperador.h"
#include "LiteralString.h"
#include "LiteralBooleano.h"
#include "CAmbiente.h"
#include "Ambiente.h"

#include <stack>
using namespace std;

LivroLiterais Expressao::m_livroLiterais;

/**
 * @brief
 *  Este metodo converte uma expressão
 * infixada em uma istream, numa lista de literais
 * interno m_expressao na forma posfixada.
 * @param is
 */
void Expressao::processaExpressao(istream &is)
{
    list<Literal*> listaLiterais;
    list<Literal*>::iterator il;

    Literal *novoLiteral = 0x0;
    char c;

    // Apaga a expressao anterior
    apagaExpressao();

    // Enquanto existir caracteres na expressao
    while(!is.eof() && c != -1)
    {

        c = is.peek();
        // Se o proximo caracter for branco
        if( c == ' ' || c == '\n' || c == '\t')
        {
            is.get(); // Consome o caracter
            continue;
        }

        // Tenta criar um novo literal
        // com os literais da fabrica
        for(il = m_literais.begin() ; il != m_literais.end() ; il++)
        {
            novoLiteral = (*il)->novoLiteral(is);
            if(novoLiteral != 0x0)
            {
                listaLiterais.push_back(novoLiteral);
                break;
            }
        }

        // Se não for um caracter eof e se não encontrou um literal
        if(c != -1 && novoLiteral == 0x0)
        {
            // Se essas linhas forem executadas
            // nenhum literal foi satisfeito
            // a mensagem é impressa e o caracter
            // problematico é iguinorado (consumido)
            cout << "Expressao::Erro ao fazer parcel (" << (char) is.get() << ')' << endl;
        }else
        {
            novoLiteral = 0x0;
        }
    }

    cout << "Lista de literais detectados" << endl;

    list<Literal*>::iterator li;
    for( li = listaLiterais.begin() ; li != listaLiterais.end() ; li++)
    {
        cout << (*li) << endl;
    }

    if(transformaInFixEmPosFix(listaLiterais, m_expressao) )
    {
        cout << "Resultado " << endl;
        for(li = m_expressao.begin() ; li != m_expressao.end() ; li++)
        {
            cout << (*li) << endl;
        }
    }
}


/**
 * @brief
 *  Este metodo apaga a expressao
 * interna.
 */
void Expressao::apagaExpressao()
{
    list<Literal*>::iterator il;

    for(il = m_expressao.begin() ; il != m_expressao.end() ; il++)
    {
        delete (*il);
    }

    m_expressao.clear();
}


/**
 * @brief
 *  Constroe a fabrica de literais
 */
void Expressao::carregaLivroDeLiterais()
{

    if(m_livroLiterais.vazio())
    {
        m_livroLiterais.addLiteral(LiteralGenerico::fabrica());
        m_livroLiterais.addLiteral(LiteralString::fabrica());
        m_livroLiterais.addLiteral(LiteralBooleano::fabrica());
        m_livroLiterais.addLiteral(LiteralOperador::fabrica());
        m_livroLiterais.addLiteral(LiteralNumero::fabrica());
        m_livroLiterais.addLiteral(LiteralVariavel::fabrica());
    }
}


/**
 * @brief
 *  Este metodo transforma uma expressão literal
 * na notação infixada para a notação polonesa
 * reversa pos fixada utilizando o algoritmo
 * Shunting-yard proposto pelo Holandes
 * Edsger Dijkstra.
 */
bool Expressao::transformaInFixEmPosFix(list<Literal*> &entrada, list<Literal*> &saida)
{
    /// @todo - Deletar literais genericos apos transformação posfixada
    stack<Literal*> pilhaOP;

    // Literais    
    Literal *literal1 = 0x0,
            *literal2 = 0x0;

    LiteralOperador *lOp1 = 0x0,
                    *lOp2 = 0x0;

    LiteralGenerico *lgenerico = 0x0;

    // Para cada literal
    list<Literal*>::iterator il;
    for(il = entrada.begin() ; il != entrada.end() ; il++)
    {
        literal1 = *il;

        // Se o literal é uma variavel numero ou string, poem ele na saida.
        if(literal1->getNumero() || literal1->getString() || literal1->getVariavel() || literal1->getBooleano())
        {
            saida.push_back(literal1);
        }

        // Se for um operador
        else if( ( lOp1 = literal1->getOperador() ) != 0x0)
        {
            // Poem o operador na pilha de operadores, enquanto tiver
            // operadores com precedencia maior do que o que esta sendo inserido
            // desempilha esses operadores e poem na saida.

            while(!pilhaOP.empty())
            {
                // Pega o topo da pilha
                literal2 = pilhaOP.top();
                lOp2 = literal2->getOperador();

                // While there is an operator token, op2, at the top of the stack
                // op1 is left-associative and its precedence is less than or equal to that of op2,
                // or op1 has precedence less than that of op2,
                // Let + and ^ be right associative.
                // Correct transformation from 1^2+3 is 12^3+
                // The differing operator priority decides pop / push
                // If 2 operators have equal priority then associativity decides.

                // Se o topo é um operador e possui precedencia maior ou igual ao novo operador
                if(lOp2 != 0x0 &&
                   (lOp2->precedencia() >= lOp1->precedencia() ) )
                {
                    // Poem operador na saida e remove da pilha de OP
                    saida.push_back(lOp2);
                    pilhaOP.pop(); // Remove do topo
                    lOp2 = 0x0;
                }
                else // Se não tem operadores no topo da pilha com maior ou igual precedencia
                { // Encerra a remoção de operadores
                    break;
                }
            }

            // Empilha o novo operador lido na pilha de operações
            pilhaOP.push(lOp1);
            lOp1 = 0x0;
        }

        // Se for um literal generico (abre parenteses ou fecha parenteses)
        else if( (lgenerico = literal1->getGenerico()) != 0x0 )
        {
            // Se for um literal abre parenteses, poem na pilha de operadores
            if(lgenerico->tipoLiteralGenerico() == LITERAL_GENERICO_ABRE_PARENSES)
            {
                pilhaOP.push(lgenerico);
            }

            // Se for um fecha parenteses
            else if(lgenerico->tipoLiteralGenerico() == LITERAL_GENERICO_FECHA_PARENSES)
            {
                // Desempilha todos operadores até encontar um abre parenteses

                bool pEncontrado = false; // FLAG que indica que parenteses foi encontrado

                // Remove todos operadores da pilha de operadores
                // até encontrar um abre parenteses
                while(! pilhaOP.empty())
                {
                    literal2 = pilhaOP.top();

                    // Se o literal desempilhado for generico e for um abre parenteses
                    if( (lgenerico = literal2->getGenerico() ) != 0x0 &&
                         lgenerico->tipoLiteralGenerico() == LITERAL_GENERICO_ABRE_PARENSES)
                    {
                        // Encerra processo de desempilhamento da pilha de operadores
                        pEncontrado = true;
                        break;
                    }
                    else
                    {
                        // Se não for abre parentes, desempilha para saida
                        saida.push_back(literal2);
                        pilhaOP.pop();
                    }
                }

                // Se um abre parenteses não foi encontrado
                if(!pEncontrado)
                {
                    printf("Parser Erro: faltando um fecha parenteses\n");
                    return false;
                }

                // Desempilha o abre parenteses sem por na saida
                pilhaOP.pop();
            }
            else // Se for um literal indefinido
            {
                printf("Parser Erro: Literal desconhecido\n");
                return false;
            }
        }
    }

    // Se todos os literais ja foram processados
    // Remove todos literais que ainda estao na pilha de operadores
    while(!pilhaOP.empty())
    {
        literal1 = pilhaOP.top();

        // Se for um literal generico
        if(literal1->getGenerico() != 0x0)
        {
            printf("Parser Erro: Parenteses faltando\n");
            return false;
        }

        // Senao poem operador na saida
        saida.push_back(literal1);

        pilhaOP.pop(); // desempilha operador
    }

    return true;
}


/**
 * @brief
 *  Busca o valor de uma variavel no ambiente
 * @param A - Variavel que sera buscada.
 * @return Literal - Valor da variavel.
 */
const Literal *Expressao::resolve(const Literal *A)
{
    if(A == 0x0) return A;
    if(A->tipoLiteral() != LITERAL_VARIAVEL) return A;

    LiteralVariavel *var = (LiteralVariavel*)A;
    const Literal *valor = m_controleAmbiente->getVariavel(m_controleAmbiente->idNodo(var->nome()));

    if(valor == 0x0)
    {
        cout << "Expressao:: Erro ao avaliar expressao, variavel " << var->nome() << " nao encontarda" << endl;
        return 0x0;
    }
    return valor;
}

void Expressao::desalocaLiteraisResolvidos()
{
    list<Literal*>::iterator li;
    for(li = m_coletorLiterais.begin() ; li != m_coletorLiterais.end() ; li++)
    {
        delete *li;
    }
    m_coletorLiterais.clear();
}

Literal *Expressao::executaOP(LiteralOperador *op, Literal* A, Literal *B)
{
    switch(op->operador())
    {
    case OP_IGUAL: return opIgual(A, B);
    case OP_DIFERENTE: return opDiferente(A, B);
    case OP_MAIOR: return opMaior(A, B);
    case OP_MENOR: return opMenor(A, B);
    case OP_MAIOR_IGUAL: return opMaiorIgual(A, B);
    case OP_MENOR_IGUAL: return opMenorIgual(A, B);
    case OP_AND: return opAnd(A, B);
    case OP_OR: return opOr(A, B);
    case OP_NEGADO: return opNegado(A, B);
    case OP_SOMA: return opSoma(A, B);
    case OP_SUBTRACAO: return opSubtracao(A, B);
    case OP_MULTIPLICACAO: return opMultiplicacao(A, B);
    case OP_DIVISAO: return opDivisao(A, B);
    case OP_ATRIBUICAO: return opAtribuicao(A, B);
    }
}


/**
 * @brief
 *  Compara se dois literais são iguais
 * @param A - arg. 1
 * @param B - arg. 2
 * @return Literal - Literal booleano
 * indicando se sao iguais ou nao.
 */
Literal *Expressao::opIgual(const Literal *A, const Literal *B)
{
    // A forma como esses OPs são inplementados
    // são meia maluca mesmo, mas funciona :)
    // opitei por essa solução, enves de espalhar
    // as tarefas entre objetos(extendendo LiteralOperador)
    // , para evitar a construção de mais objetos e fazer
    // mais casts como esse. Então centralizei
    // essas operações na Expressao, e os literais
    // servem unicamente para leitura mesmo.

    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() == ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_STRING:
        resposta =
        ((LiteralString*) A)->valor() == ((LiteralString*) B)->valor();
        break;
        case LITERAL_BOOLEANO:
        resposta =
        ((LiteralBooleano*) A)->valor() == ((LiteralBooleano*) B)->valor();
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opDiferente(const Literal *A, const Literal *B)
{
    // A forma como esses OPs são inplementados
    // são meia maluca mesmo, mas funciona :)
    // opitei por essa solução, enves de espalhar
    // as tarefas entre objetos(extendendo LiteralOperador)
    // , para evitar a construção de mais objetos e fazer
    // mais casts como esse. Então centralizei
    // essas operações na Expressao, e os literais
    // servem unicamente para leitura mesmo.

    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = true;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() != ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_STRING:
        resposta =
        ((LiteralString*) A)->valor() != ((LiteralString*) B)->valor();
        break;
        case LITERAL_BOOLEANO:
        resposta =
        ((LiteralBooleano*) A)->valor() != ((LiteralBooleano*) B)->valor();
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opMaior(const Literal *A, const Literal *B)
{
    // A forma como esses OPs são inplementados
    // são meia maluca mesmo, mas funciona :)
    // opitei por essa solução, enves de espalhar
    // as tarefas entre objetos(extendendo LiteralOperador)
    // , para evitar a construção de mais objetos e fazer
    // mais casts como esse. Então centralizei
    // essas operações na Expressao, e os literais
    // servem unicamente para leitura mesmo.

    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
        cout << "Operador Maior - Erro comparando tipos diferentes" << endl;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() > ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_STRING:
        resposta =
        ((LiteralString*) A)->valor() > ((LiteralString*) B)->valor();
        break;
        default:
            cout << "Operador Maior Erro - operador nao esta preparado para receber literal " << A << endl;
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opMenor(const Literal *A, const Literal *B)
{
    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
        cout << "Operador Menor - Erro comparando tipos diferentes" << endl;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() < ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_STRING:
        resposta =
        ((LiteralString*) A)->valor() < ((LiteralString*) B)->valor();
        break;
        default:
            cout << "Operador Menor Erro - operador nao esta preparado para receber literal " << A << endl;
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opMaiorIgual(const Literal *A, const Literal *B)
{
    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
        cout << "Operador Maior Igual - Erro comparando tipos diferentes" << endl;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() >= ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_STRING:
        resposta =
        ((LiteralString*) A)->valor() >= ((LiteralString*) B)->valor();
        break;
        default:
            cout << "Operador Maior Igual Erro - operador nao esta preparado para receber literal " << A << endl;
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opMenorIgual(const Literal *A, const Literal *B)
{
    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
        cout << "Operador Menor Igual - Erro comparando tipos diferentes" << endl;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() < ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_STRING:
        resposta =
        ((LiteralString*) A)->valor() < ((LiteralString*) B)->valor();
        break;
        case LITERAL_BOOLEANO:
        resposta =
        ((LiteralBooleano*) A)->valor() < ((LiteralBooleano*) B)->valor();
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
 }

Literal *Expressao::opAnd(const Literal *A, const Literal *B)
{
    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
        cout << "Operador And - Erro comparando tipos diferentes" << endl;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() && ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_BOOLEANO:
        resposta =
        ((LiteralBooleano*) A)->valor() && ((LiteralBooleano*) B)->valor();
        break;
        default:
            cout << "Erro operador And, nao esta preparado para trabalhar com o tipo do argumento" << endl;
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opOr(const Literal *A, const Literal *B)
{
    bool resposta = false;

    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        resposta = false;
        cout << "Operador Or - Erro comparando tipos diferentes" << endl;
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
        resposta =
        ((LiteralNumero*) A)->valor() || ((LiteralNumero*) B)->valor();
        break;
        case LITERAL_BOOLEANO:
        resposta =
        ((LiteralBooleano*) A)->valor() || ((LiteralBooleano*) B)->valor();
        break;
        default:
            cout << "Erro operador And, nao esta preparado para trabalhar com o tipo do argumento" << endl;
        break;
        }
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Literal *Expressao::opNegado(const Literal *A, const Literal *B)
{
    A = resolve(A);
    B = resolve(B);

    // Verifica qual é o operador valido
    if(A != 0x0)
    {
        if(A->tipoLiteral() == LITERAL_BOOLEANO)
            return LiteralBooleano::fabrica()->novoLiteral(! ((LiteralBooleano*) A)->valor() );
    }
    else if( B != 0x0)
    {
        if(B->tipoLiteral() == LITERAL_BOOLEANO)
            return LiteralBooleano::fabrica()->novoLiteral(! ((LiteralBooleano*) B)->valor() );
    }
    cout << "Erro no operador negado - Argumento nao sao booleanos, ou eles nao foram definidos" << endl;
    return LiteralBooleano::fabrica()->novoLiteral(false);
}

Literal *Expressao::opSoma(const Literal *A, const Literal *B)
{
    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        return LiteralBooleano::fabrica()->novoLiteral(false);
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
            return LiteralNumero::fabrica()->novoLiteral(
        ((LiteralNumero*) A)->valor() + ((LiteralNumero*) B)->valor() );
        break;
        case LITERAL_STRING:
            return LiteralString::fabrica()->novoLiteral(
        ((LiteralString*) A)->valor() + ((LiteralString*) B)->valor() );
        break;
        }
    }
    return LiteralBooleano::fabrica()->novoLiteral(false);
}

Literal *Expressao::opSubtracao(const Literal *A, const Literal *B)
{
    // Se tiver os dois operadores
    // Resolve ops operadores que sao variaveis
    A = resolve(A);
    B = resolve(B);

    // Se tiver apenas um operador
    if(A == 0x0 && B != 0x0)
    {
        A = B;
        B = 0x0;
    }

    if(A != 0x0 && B == 0x0)
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
            return LiteralNumero::fabrica()->novoLiteral(
            -((LiteralNumero*) A)->valor() );
        break;
        default:
            cout << "Erro op subtracao nao esta preparado para receber literal "<< B << endl;
            return LiteralBooleano::fabrica()->novoLiteral(false);
        break;
        }
    }
    // Se possui os 2 operadores
    // Verifica se os literais são do mesmo tipo
    if(A->tipoLiteral() != B->tipoLiteral())
    {
        cout << "Erro ao subtrair, tipos diferentes" << endl;
        return LiteralBooleano::fabrica()->novoLiteral(false);
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
            return LiteralNumero::fabrica()->novoLiteral(
        ((LiteralNumero*) A)->valor() - ((LiteralNumero*) B)->valor() );
        break;
        default:
            cout << "Erro ao subtrair, tipos não suportados para subtracao" << endl;
            return LiteralBooleano::fabrica()->novoLiteral(false);
        break;
        }
    }
    cout << "Erro ao subtrair, problema desconhecido" << endl;
    return LiteralBooleano::fabrica()->novoLiteral(false);
}

Literal *Expressao::opMultiplicacao(const Literal *A, const Literal *B)
{
    A = resolve(A);
    B = resolve(B);

    // Verifica se os literais possui em o mesmo tipo
    if(!A || !B || A->tipoLiteral() != B->tipoLiteral())
    {
        cout << "Erro ao subtrair, tipos diferentes" << endl;
        return LiteralBooleano::fabrica()->novoLiteral(false);
    }
    else
    {
        switch(A->tipoLiteral())
        {
        case LITERAL_NUMERO:
            return LiteralNumero::fabrica()->novoLiteral(
        ((LiteralNumero*) A)->valor() * ((LiteralNumero*) B)->valor() );
        break;
        default:
            cout << "Erro ao subtrair, tipos não suportados para subtracao" << endl;
            return LiteralBooleano::fabrica()->novoLiteral(false);
        break;
        }
    }
    cout << "Erro ao subtrair, problema desconhecido" << endl;
    return LiteralBooleano::fabrica()->novoLiteral(false);
}

Literal *Expressao::opDivisao(const Literal *A, const Literal *B)
{
    cout << "OPDivisao ainda nao foi implementado na class expressao" << endl;
}


Literal *Expressao::opAtribuicao(const Literal *A, const Literal *B)
{
    bool resposta = false;
    if(A->tipoLiteral() == LITERAL_VARIAVEL && m_controleAmbiente != 0x0)
    {
        stringstream ss;
        string val;
        switch(B->tipoLiteral())
        {
            case LITERAL_NUMERO:
                ss << ((LiteralNumero*) B)->valor();
                ss >> val;
                resposta = true;
            break;
            case LITERAL_STRING:
                ss << '\"' << ((LiteralString*) B)->valor() << '\"';
                ss >> val;
                resposta = true;
            break;
            case LITERAL_BOOLEANO:
                if(((LiteralBooleano*) B)->valor())
                    ss << "true";
                else
                    ss << "false";
                resposta = true;
            break;
            default:
                cout << "Erro Expressao opAtribuicao: Atribuindo valor ilegal a variavel" << endl;
                resposta = false;
            break;
        }
        if(resposta)
        {
            if(! m_controleAmbiente->setVariavel(m_controleAmbiente->idNodo(((LiteralVariavel *)A)->nome()), ss.str()))
            {
                cout << "Erro Expressa opAtribuicao: Variavel nao existe no ambiente" << endl;
                resposta = false;
            }
        }
    }else
    {
        cout << "Erro Expressao opAtribuicao: arg1 do op nao e uma variavel, ou a expressao nao esta associada a um ambiente" << endl;
    }

    return LiteralBooleano::fabrica()->novoLiteral(resposta);
}

Expressao::Expressao()
{
    m_controleAmbiente = 0x0;
    carregaLivroDeLiterais();
}

Expressao::~Expressao()
{
    apagaExpressao();


}

bool Expressao::setExpressao(const string &expressao)
{
    return setExpressao(expressao.c_str());
    /*
    if(expressao.size() > 0)
    {
        stringstream ss;
        ss << expressao;
        processaExpressao(ss);
    }else
    {
        apagaExpressao();
    }
    */

}

bool Expressao::setExpressao(const char *expressao)
{
    list<Literal*> literais;

    // Etapa de interpretacao, os caracteres serao
    // transformados em literais
    if(!m_livroLiterais.interpreta(expressao,literais))
    {
        cout << "Expressao Erro, A expressao nao pode ser interpretada pelo livro de literais" << endl;
        return false;
    }

    list<Literal*>::iterator li;
    cout << "Literais identificados:" << endl;
    for(li = literais.begin() ; li != literais.end() ; li++)
    {
        cout << *li << endl;
    }

    // Etapa de reordenacao dos literais
    // Para a forma prefixada utilizando
    // o algoritmo de dijkstra
    apagaExpressao();

    // Os literais reordenados sao salvos como expressao
    // pronto para serem executados
    if(!transformaInFixEmPosFix(literais, m_expressao))
    {
        cout << "Expressao Erro!, A expressao possui erro de sintaxe, nao pode ser avaliada" << endl;
        apagaExpressao();
        return false;
    }
    imprimeLiterais();
    return true;
}


/**
 * @brief
 *  Este metodo é utilizado apenas para depuração
 * ele imprime os literais indentificados
 * na expressao carregada.
 */
void Expressao::imprimeLiterais()
{
    list<Literal*>::iterator il;
    cout << "Expressao:" << endl;
    for(il = m_expressao.begin() ; il != m_expressao.end() ; il++)
    {
        cout << (*il) << endl;
    }
}

bool Expressao::avaliaExpressao(CAmbiente *ambiente)
{
    if(m_expressao.empty())
    {
        cout << "Erro ao avaliar expressa, expressao sem literais" << endl;
        return false;
    }

    // Define o ambiente das variaveis da expressao
    m_controleAmbiente = ambiente;

    bool resultadoAvaliacao = false;

    // Utilizada para salvar os argumentos dos operadores
    stack<Literal*> pilhaArgumentos;

    // Utilizada para desalocar literais
    // criados pelos operadores executados
    stack<Literal*> coletorLiterais;

    Literal *literalAtual = 0x0;

    // Para todos literais da minha expressao...
    list<Literal*>::iterator li;
    for(li = m_expressao.begin(); li != m_expressao.end(); li++)
    {
        // Pega o proximo literal
        literalAtual = *li;

        // Se o caracter é uma variavel ou uma constante
        if(literalAtual->getVariavel() || literalAtual->getString() || literalAtual->getNumero() || literalAtual->getBooleano())
        {
            // Coloca na pilha de argumentos (São dados que serao processados! :) )
            pilhaArgumentos.push(literalAtual);
        }

        // Se for um operador.
        else if(literalAtual->getOperador())
        {
            LiteralOperador *op = literalAtual->getOperador();
            Literal *A = 0x0, *B = 0x0; // Argumentos

            // Sera que precisa mesmo numero de args? Qual OP tem mais de 2 arg?
//            unsigned numArgsOp = op->numArgumentos();

            // Argumento B
            if(!pilhaArgumentos.empty())
            {
                B = pilhaArgumentos.top();
                    pilhaArgumentos.pop();

            }
            // Argumento A
            if(op->numArgumentos() == 2 && !pilhaArgumentos.empty())
            {
                A = pilhaArgumentos.top();                
                    pilhaArgumentos.pop();
            }

            // Argumento A possui o resultado
            A = executaOP(op, A, B);

            // Se operador falhou
            if(A == 0x0)
            {
                cout << "Expressao Erro: Erro ao avaliar expressao, argumentos do operador invalido" << endl;
                literalAtual = 0x0;
                goto apagaLiterais;
            }

            // Adiciona o resultado da operação no topo da pilha
            // de argumentos
            pilhaArgumentos.push(A);

            // Tada operação produz um novo literal
            // que precisa ser desalocado no fim da execução
            // adiciona resultado no coletor de literais
            coletorLiterais.push(A);
        }
    }

    while(!pilhaArgumentos.empty())
    {
        literalAtual = pilhaArgumentos.top();
        pilhaArgumentos.pop();
        cout << "Resultado " << literalAtual << endl;
    }

    if(literalAtual->tipoLiteral() == LITERAL_BOOLEANO)
    {
        resultadoAvaliacao = ((LiteralBooleano*) literalAtual)->valor();
    }

apagaLiterais:
    // Apaga todos literais do coletor, menos o resultado
    while(!coletorLiterais.empty())
    {
        delete coletorLiterais.top();
        coletorLiterais.pop();
    }

    return resultadoAvaliacao;
}

#include "Automato.h"

Automato::Automato():
    m_estrutura(new VerticeGrafo , new ArestaAutomato)
{
    m_estadoInicial = 0;
}


/**
 * @brief
 *  Cria varios estados com
 * IDs sequenciais e crescente
 * começando do ID 0 até numEstados-1
 * @param numEstados - Numero de
 * estados que sera criado.
 */
void Automato::criaEstados(unsigned numEstados)
{
    m_estrutura.criaVertices(numEstados);
}

bool Automato::setEstadoInicial(unsigned estadoInicial)
{
    if(m_estrutura.existeVertice(estadoInicial))
    {
        m_estadoInicial = estadoInicial;
        return true;
    }

    cout << "Erro ao definir estado inicial do automato, estado nao existe" << endl;
    return false;
}

void Automato::addEstadoFinal(unsigned estado)
{
    m_estadosFinais.push_back(estado);
}

void Automato::removeEstadoFinal(unsigned estado)
{
    m_estadosFinais.remove(estado);
}

void Automato::addEstadoAceitacao(unsigned estado)
{
    m_estadosAceitacao.push_back(estado);
}

void Automato::removeEstadoAceitacao(unsigned estado)
{
    m_estadosAceitacao.remove(estado);
}

void Automato::addAresta(unsigned de, unsigned para, const char *simbulos)
{
    ArestaAutomato *novaAresta = new ArestaAutomato(simbulos);

    // Define de onde, para onde
    novaAresta->setDe(de);
    novaAresta->setPara(para);

    m_estrutura.novaAresta(novaAresta);
}

void Automato::addAresta(ArestaAutomato *aresta)
{
    m_estrutura.novaAresta(aresta);
}


/**
 * @brief
 *  Verifica se uma sequencia de caracteres
 * (palavra) é aceito pelo automato.
 *  Os caracteres são lidos pelo automato,
 * alterando entre seus estados, a leitura
 * termina quando um caracter não consegue
 * satisfazer nenhuma aresta do estado atual
 * do automato, ou quando a sequencia de
 * caracters termina.
 *  Quando a leitura acaba, é verificado
 * se o ultimo estado apos a leitura é
 * um estado final, se for, a palavra é aceita,
 * é retornado o número de caracteres lidos
 * e a palavra extraida pelo automato.
 *  Os caracteres são extraidos pelo automato
 * toda vez que um caracter satisfaz uma
 * transição que leva para um estado de
 * aceitação.
 * @param palavra - Conjunto de caracters
 * que sera lido pelo automato.
 * @param palavraExtraida - Palavra extraida pelo
 * automato.
 * @return int - 0 se a palavra não for aceita
 * num. de caracteres lidos, caso a palavra
 * seja aceita.
*/
int Automato::avalia(const char *palavra, string &palavraExtraida)
{
    if(m_estadosFinais.empty())
    {
        cout << "Erro ao avaliar palavra, automato nao possui estados finais definidos" << endl;
        return 0;
    }

    unsigned estadoAtual = m_estadoInicial,
            numCaracterLidos = 0,
            a, i;

    const char *leitura = palavra; // Ponteiro de leitura

    char caracterAceito = 0; // FLAG

    ArestaAutomato *arestaAtual;

    // Utilizado para percorrer estados finais do automato
    list<unsigned>::iterator li;

    // Limpa palavra extraida
    palavraExtraida.clear();

    // Enquanto nao terminar de ler a palavra
    while(*leitura != '\0')
    {
        caracterAceito = 0;

        // Para todas arestas adjacentes do estadoAtual
        for(i = 0; i < m_estrutura.numSucessores(estadoAtual); i++)
        {
            a = m_estrutura.idArestaSucessor(estadoAtual,i);
            arestaAtual = (ArestaAutomato*) m_estrutura.aresta(a);

            // Se aresta aceita o simbulo atual
            if(arestaAtual->aceitaSimbolo(*leitura))
            {
                // Define o novo estado
                estadoAtual = arestaAtual->para();

                for(li = m_estadosAceitacao.begin(); li != m_estadosAceitacao.end(); li++)
                {
                    // Se o estado de destino é de aceitacao
                    if(*li == estadoAtual)
                    {
                        // Extrai caracter
                        palavraExtraida += *leitura;
                    }
                }

                caracterAceito = 1;
                break;
            }
        }

        // Se nao satisfaz nenhuma aresta,
        // entramos em um deadlock a leitura terminou
        if(caracterAceito == 0)
            break;

        // Se caracter foi lido pelo automato, incrementa
        numCaracterLidos++;
        // Avança para o proximo caracter
        leitura++;
    }

    // Apos a execução do automato, verifica se
    // a palavra é aceita ou não verificando
    // o estado final
    for(li = m_estadosFinais.begin() ; li != m_estadosFinais.end() ; li++)
    {
        // Se atingiu um estado final
        if(estadoAtual == *li)
            return numCaracterLidos;
    }

    // Se o ultimo estado não e final
    // a palavra não é aceita

    // Apaga palavra
    palavraExtraida.clear();
    return 0;
}

string Automato::branco()
{
    return " \n\t";
}

string Automato::letrasMinusculas()
{
    return "abcdefghijklmnopqrstuvyxwz";
}

string Automato::letrasMaiusculas()
{
    return "ABCDEFGHIJKLMNOPQRSTUVYXWZ";
}

string Automato::numeros()
{
    return "1234567890";
}

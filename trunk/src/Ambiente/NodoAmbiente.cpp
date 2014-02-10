#include "NodoAmbiente.h"
#include <sstream>

// Este includes são utilizados
// apenas para o Qt encontrar o
// nome dos metodos
#include "Ambiente.h"

Ambiente *NodoAmbiente::ambiente()
{
    return m_ambiente;
}

string NodoAmbiente::encontraNomeDisponivel(const string &nome)
{
    // Se não possui ambiente, não existe conflito
    if(m_ambiente == 0x0)
        return nome;

    // Pega o numero de pais do nodo
    int numPais = m_ambiente->m_grafo.numPredecessores(m_id),
            i;

    NodoAmbiente *pai = 0x0;
    NodoAmbiente *nodoConflito = 0x0;
    string novoNome = nome;
    unsigned tentativa = 1;

    // Para cada pai, tenta entrar em um acordo do novo nome
    for( i = 0; i < numPais ; i++)
    {
        // Pega um pai
        pai = m_ambiente->getNodo(m_ambiente->m_grafo.predecessor(m_id, i));

        // Verifica se pai aceita novo nome
        nodoConflito = pai->getNodoDireto(novoNome);

        // Se não aceita
        if(nodoConflito != 0x0 && nodoConflito != this)
        {
            // Modifica o nome
            stringstream ss;
            ss << nome << '_' << tentativa;
            novoNome = ss.str();
            tentativa++;

            // Tenta acordo do novo nome com todos pais
            i = -1;
        }
    }
    return novoNome;
}

/**
 * @brief
 *  Ao registrar um mapeamento, uma entrada para o nome do
 * nodo no mapa do nodo pai é criado
 *
 * @param nome - Nome do nodo
 * @param id - Id do nodo
 * @return string - Nome realmente atribuido ao nodo
 */
string NodoAmbiente::registraMapeamento(const string &nome, unsigned id)
{
    unsigned tentativa =1; // Controle de tentativas
    string final = nome; // Nome final

    pair< map<string, unsigned>::iterator , bool >
     insercao; // Pair de insercao do map

    // Tenta Inserir o nome no mapa
    insercao = m_mapaNodos.
            insert( pair< const string &, unsigned> (final , id));

    // Equanto o nome ja existir para outro ID
    while(insercao.second == false && insercao.first->second != id)
    {
        // Tenta um novo nome
        stringstream ss;
        ss << nome << "_" << tentativa;
        final = ss.str();
        tentativa++;

        // Tenta inserir novo nome
        insercao = m_mapaNodos.
                insert( pair< const string &, unsigned> (final , id));
    }

    return final;
}


/**
 * @brief
 *  Retorna o nodo mapeado localmente nesse nodo
 * a partir de seu nome.
 * Esse metodo deve ser utilizado apenas internamente
 * na classe NodoAmbiente.
 * @param nomeNodo - Nomde do nodo
 * @return NodoAmbiente - Nodo encontrado ou 0x0
 */
NodoAmbiente *NodoAmbiente::getNodoDireto(const string &nomeNodo)
{
    // Procura no mapa de nomes se existe um nodo com este nome.
    map<string , unsigned>::iterator ln = m_mapaNodos.find(nomeNodo);

    // Verifica se o nodo foi encontrado
    if( ln  == m_mapaNodos.end())
    {
        // O nodo não foi encontrado
        return 0x0;
    }

    return m_ambiente->getNodo(ln->second);
}

const NodoAmbiente *NodoAmbiente::getNodoDireto(const string &nomeNodo) const
{
    // Procura no mapa de nomes se existe um nodo com este nome.
    map<string , unsigned>::const_iterator ln = m_mapaNodos.find(nomeNodo);

    // Verifica se o nodo foi encontrado
    if( ln  == m_mapaNodos.end())
    {
        // O nodo não foi encontrado
        return 0x0;
    }

    return m_ambiente->getNodo(ln->second);
}

VariavelAmbiente *NodoAmbiente::getVariavelDireto(const string &nomeNodo)
{
    NodoAmbiente *nodo = getNodoDireto(nomeNodo);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_VARIAVEL)
    {
        return (VariavelAmbiente*) nodo;
    }
    return 0x0;
}

PerguntaAmbiente *NodoAmbiente::getPerguntaDireto(const string &nomeNodo)
{
    NodoAmbiente *nodo = getNodoDireto(nomeNodo);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_PERGUNTA)
    {
        return (PerguntaAmbiente*) nodo;
    }
    return 0x0;
}

AcaoAmbiente *NodoAmbiente::getAcaoDireto(const string &nomeNodo)
{
    NodoAmbiente *nodo = getNodoDireto(nomeNodo);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_ACAO)
    {
        return (AcaoAmbiente*) nodo;
    }
    return 0x0;
}

/**
 * @brief
 *  Renomeia uma entrada do mapeamento da variavel
 * @param variavel - Variavel que tera mapeamento renomeado
 * @param novoNome - Novo nome
 * @return string - Novo nome renomeado, talvez modificado
 * para resolver conflito, ou "" se algum erro correr.
 */
string NodoAmbiente::renomeiaNodo(NodoAmbiente *nodo, const string &novoNome)
{
    NodoAmbiente *nodoMapeado = getNodoDireto(nodo->nome());

     // Se o nodo não foi encontrado
     if(nodoMapeado == 0x0)
     {
         cout << "NodoAmbiente:: Erro de mapeamento de nodos!!" << endl;
         return string();
     }

     // Se o nodo for diferente do mapeado
     if(nodo != nodoMapeado)
     {
         if(nodo == getNodoDireto(novoNome))
             return novoNome; // Nao renomeia, ja esta correto

         cout << "NodoAmbiente:: Erro de mapeamento de nodos!!" << endl;
         return string(); // Erro de mapeamento de nodos
     }

     // Apaga o nome antigo do mapa
     m_mapaNodos.erase(nodo->nome());

     // Insere novo nome no mapa
     string nomeFinal =registraMapeamento(novoNome, nodo->m_id);

     return nomeFinal;
}

NodoAmbiente::NodoAmbiente(string nome)
{
    m_nome = nome;
    m_ambiente = 0x0;

    // Esta flag é utilizada para solucionar um problema no destrutor dessa classe
    executandoDestrutor = false;
}

/**
 * @brief
 *  Deleta nodo do ambiente.
 */
NodoAmbiente::~NodoAmbiente()
{
    // Essa flag só pode ser alterada nesta parte do codigo
    // indica que o nodo esta sendo desalocado
    executandoDestrutor = true;

    // Se faz parte de um ambiente
    if(m_ambiente != 0x0 && m_ambiente != this)
    {
        // Se remove de todos pais
        int numPais = m_ambiente->m_grafo.numPredecessores(m_id),
                i;

        NodoAmbiente *pai = 0x0;
        for( i = 0 ; i < numPais ; i++)
        {
            pai = m_ambiente->getNodo(m_ambiente->m_grafo.predecessor(m_id, i));
            if(pai != 0x0)
            {
                pai->removeNodo(m_nome);
            }
        }
        // Ao remover todos os pais
        // não existira nenhuma referencia para este nodo
        // a ação padrao do ultimo pai que for removido
        // é de deletar o filho (eu), porem o filho ja
        // esta sendo destruido aqui, por isso foi necessario
        // a flag executandoDestrutor para evitar um doublefree

        // O mesmo problema ocorreu no desenvolvimento dos desenhos
    }

    // Deleta todos os nodos que estou mapeando do ambiente
    map<string , unsigned>::iterator i;
    for( i = m_mapaNodos.begin() ; i != m_mapaNodos.end() ; i++)
    {
        removeNodo(i->first);
    }
    m_mapaNodos.clear();

    // Se eu não sou o ambiente
    if(m_ambiente != this)
    {
        // Se remove do ambiente
        m_ambiente->m_grafo.deletaVertice(m_id);
        m_ambiente->m_nodos[m_id] = 0x0;
    }// Se eu for o ambiente, m_grafo e m_variaveis nao existem mais

    m_ambiente = 0x0;
}


/**
 * @brief
 *  Retorna um nodo que pode estar local
 * ou em níveis abaixo, a cadeia de nome
 * deve ser formada utiizando o caracter
 * (.) ponto, exemplo:
 *  ROV.Posicao.X -> Retorna o nodo X
 * @param nome - Nome para busca
 * @return NodoAmbiente - Nodo encontrado
 * ou 0x0 caso contrario.
 */
NodoAmbiente *NodoAmbiente::getNodo(const string &nome)
{
    int ini = 0, fim;
    NodoAmbiente *nodoAtual = this;

    // Pega a posicao do primeiro '.' encontrado no nome
    fim = nome.find('.' , ini+1);

    // Enquanto existir um ponto na posição fim
    while(fim != -1)
    {
        // Percorre os nodos no grafo de nodos
        nodoAtual = nodoAtual->getNodoDireto(nome.substr(ini, fim - ini));

        if(nodoAtual == 0x0)
            return nodoAtual;

        // Procura o proximo '.' no nome do nodo
        ini = fim+1;
        fim = nome.find('.' , ini);
    }

    // Acessa o nodo
    return nodoAtual->getNodoDireto(nome.substr(ini));
}

const NodoAmbiente *NodoAmbiente::getNodo(const string &nome) const
{
    int ini = 0, fim;
    const NodoAmbiente *nodoAtual = this;

    // Pega a posicao do primeiro '.' encontrado no nome
    fim = nome.find('.' , ini+1);

    // Enquanto existir um ponto na posição fim
    while(fim != -1)
    {
        // Percorre os nodos no grafo de nodos
        nodoAtual = nodoAtual->getNodoDireto(nome.substr(ini, fim - ini));

        if(nodoAtual == 0x0)
            return nodoAtual;

        // Procura o proximo '.' no nome do nodo
        ini = fim+1;
        fim = nome.find('.' , ini);
    }

    // Acessa o nodo
    return nodoAtual->getNodoDireto(nome.substr(ini));
}

VariavelAmbiente *NodoAmbiente::getVariavel(string nome)
{
    NodoAmbiente *nodo = getNodo(nome);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_VARIAVEL)
    {
        return (VariavelAmbiente*) nodo;
    }
    return 0x0;
}

VariavelAmbiente *NodoAmbiente::getVariavel(unsigned id)
{
    NodoAmbiente *nodo = m_ambiente->getNodo(id);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_VARIAVEL)
    {
        return (VariavelAmbiente*) nodo;
    }
    return 0x0;
}

VariavelAmbiente *NodoAmbiente::variavel()
{
    if(tipoNodo() == NODO_VARIAVEL)
        return (VariavelAmbiente*) this;
    return 0x0;
}

PerguntaAmbiente *NodoAmbiente::getPergunta(string nome)
{
    NodoAmbiente *nodo = getNodo(nome);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_PERGUNTA)
    {
        return (PerguntaAmbiente*) nodo;
    }
    return 0x0;
}

PerguntaAmbiente *NodoAmbiente::getPergunta(unsigned id)
{
    NodoAmbiente *nodo = m_ambiente->getNodo(id);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_PERGUNTA)
    {
        return (PerguntaAmbiente*) nodo;
    }
    return 0x0;
}

PerguntaAmbiente *NodoAmbiente::pergunta()
{
    if(tipoNodo() == NODO_PERGUNTA)
    {
        return (PerguntaAmbiente*) this;
    }
    return 0x0;
}

AcaoAmbiente *NodoAmbiente::getAcao(string nome)
{
    NodoAmbiente *nodo = getNodo(nome);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_ACAO)
    {
        return (AcaoAmbiente*) nodo;
    }
    return 0x0;
}

AcaoAmbiente *NodoAmbiente::getAcao(unsigned id)
{
    NodoAmbiente *nodo = m_ambiente->getNodo(id);
    if(nodo != 0x0 && nodo->tipoNodo() == NODO_ACAO)
    {
        return (AcaoAmbiente*) nodo;
    }
    return 0x0;
}

AcaoAmbiente *NodoAmbiente::acao()
{
    if(tipoNodo() == NODO_ACAO)
    {
        return (AcaoAmbiente*) this;
    }
    return 0x0;
}

bool NodoAmbiente::possuiAmbiente() const
{
    return m_ambiente != 0x0;
}

/**
 * @brief
 *  Ao adicionar um nodo, uma referencia de pai-filho
 * é estabelecida entre os nodos, uma entrada no
 * mapeamento do nodo pai é criado, um vertice
 * representando a nova variavel e uma aresta entre o
 * vertice pai->filho é criado no ambiente, o ambiente
 * passa a conter o novo nodo.
 *
 * @param novoNodo
 * @return bool
 */
bool NodoAmbiente::addNodo(NodoAmbiente *novoNodo)
{
    // Se o nodo é valido
    if(novoNodo == 0x0)
    {
        cout << "NodoAmbiente: Adicionando nodo invalido" << endl;
        return false;
    }

    // Registra novo nodo no ambiente,
    // se ele ja esta registrada nao tem problema
    if(!m_ambiente->registraNodo(novoNodo)) // Aqui um id pode ser gerado para o nodo
    {
        // Se não consegiu registra, tem algo errado
        // com esse nodo, ele nao pode ser utilizado
        return false;
    }

    // Estabelece relacao hierarquica utilizando grafo
    int idAresta = m_ambiente->m_grafo.novaAresta(m_id , novoNodo->m_id, 1.f);
    if(idAresta < 0)
    {
        cout << "NodoAmbiente::Erro ao estabelecer hierarquia" << endl;
        return false;
    }

    // Procura nome disponivel entre todos os pais
    // ja considerando que eu sou um pai (por causa da aresta ja adicionada)
    string novoNome = novoNodo->encontraNomeDisponivel(novoNodo->nome());

    // Adiciona novo nodo ao meu mapeamento
    // Se mesmo assim o meu mapeamento alterar o nome
    if(novoNome != registraMapeamento(novoNome, novoNodo->m_id))
    {
        // Um problema aconteceu ao encontrarNomeDisponivel
        // nao foi considerado o meu mapeamento na busca
        cout << "Erro ao adicionar novo nodo, comflito de nomes nao resolvido" << endl;
    }

    if(novoNome != novoNodo->nome())
    {
        // O nome tem que ser setado apenas apos o mapemaneto
        // do novo nodo, setNome vai renomear todos
        // mapeamentos de todos pais, o mapeamento detecta
        // que o nodo ja foi renomeada neste pai sem problemas
        novoNodo->setNome(novoNome);
    }

    return true;
}


/**
 * @brief
 * Adiciona um nodo no ambiente respeitando a
 * hierarquia do nome, o nome dos nodos são
 * formulados com o caracter '.' ponto, indicando
 * que um nodo contem outro, por exemplo, se
 * o metodo for chamado da seguinte forma:
 *   ambiente.addNodo("casa.cachorro.cor")
 * o método percorre o nodo casa, depois
 * o nodo cachorro que esta dentro do nodo
 * casa e depois o nodo cor, se os nodos
 * não existirem, eles serão criados,
 * o nodo final é retornado.
 *
 * @param nome - Nome do nodo que sera criado
 * @return NodoAmbiente - Nodo criado, ou nodo já existente
 */
NodoAmbiente* NodoAmbiente::addNodo(string nome)
{
    int ini = 0, fim;
    NodoAmbiente *nodoAtual = this;
    NodoAmbiente *nodoAterior = this;
    string subStr;

    // Resolve todos os nodos de '.' a '.'
    // Se o nodo não existir, ele é criado
    fim = nome.find('.' , ini);

    // Este while faz a navegação entre os nodos
    // através do grafo de nodos, conforme a utilizacao
    // do operador '.' do nome do nodo.
    while(fim != -1)
    {
        // Pega nome entre pontos
        subStr = nome.substr(ini, fim - ini);

        // Busca nome do nodo, no nodo atual
        nodoAtual = nodoAtual->getNodoDireto(subStr);

        // Se o nodo não foi encontrado
        if(nodoAtual == 0x0)
        {
            // Cria um novo nodo
            nodoAtual = new NodoAmbiente(subStr);
            nodoAterior->addNodo(nodoAtual);
        }

        // Avança para o proximo nodo
        // que pode te sido criado ou encontrado
        nodoAterior = nodoAtual;

        // Resolve o proximo nome entre pontos
        ini = fim+1;
        fim = nome.find('.' , ini);
    }

    // Pega o ultimo nome da string
    subStr = nome.substr(ini);

    // Tenta encontrar no nodo atual
    nodoAtual = nodoAtual->getNodoDireto(subStr);

    // Se o nodo não existe
    if(nodoAtual == 0x0)
    {   // Ele é criado
        nodoAtual = new NodoAmbiente(subStr);
        nodoAterior->addNodo(nodoAtual);
    }

    // Retorna o nodo criado, ou o nodo que ja existia
    return nodoAtual;
}


/**
 * @brief
 *  Cria uma nova variavel ao ambiente.
 * @param nome - Nome da variavel.
 * @param valor - Valor da variavel.
 * @return bool -
 */
VariavelAmbiente *NodoAmbiente::addVariavel(string nome, string valor)
{
    NodoAmbiente *nodoAtual = this;

    // Posicao do ultimo ponto
    int fim = nome.rfind('.');

    // Se possui ponto
    if(fim != -1)
    {
        // Cria nodos (se necessario) de tudo que vem antes do ultimo ponto
        nodoAtual = addNodo(nome.substr(0 , fim));
    }

    // Se conseguiu criar todos nodos
    if(nodoAtual != 0x0)
    {
        // Cria o utimo nodo com a variavel desejada
        VariavelAmbiente *novaVariavel = new VariavelAmbiente(nome.substr(fim+1) , valor);
        nodoAtual->addNodo(novaVariavel);
        return novaVariavel;
    }

    return 0x0;
}

PerguntaAmbiente *NodoAmbiente::addPergunta(string nome, string pergunta)
{
    NodoAmbiente *nodoAtual = this;

    // Posicao do ultimo ponto
    int fim = nome.rfind('.');

    // Se possui ponto
    if(fim != -1)
    {   // Cria nodos (se necessario) de tudo que vem antes do ponto
        nodoAtual = addNodo(nome.substr(0 , fim));
    }

    // Se conseguiu criar todos nodos
    if(nodoAtual != 0x0)        
    {
        // Cria o utimo nodo
        PerguntaAmbiente *novaPergunta = new PerguntaAmbiente(nome.substr(fim+1) , pergunta);
        nodoAtual->addNodo(novaPergunta);
        return novaPergunta;
    }
    return 0x0;
}

AcaoAmbiente *NodoAmbiente::addAcao(string nome, string acao)
{
    NodoAmbiente *nodoAtual = this;

    // Posicao do ultimo ponto
    int fim = nome.rfind('.');

    // Se possui ponto
    if(fim != -1)
    {   // Cria nodos (se necessario) de tudo que vem antes do ponto
        nodoAtual = addNodo(nome.substr(0 , fim));
    }

    // Se conseguiu criar todos nodos
    if(nodoAtual != 0x0)
    {
        // Cria a nova acao
        AcaoAmbiente *novaAcao = new AcaoAmbiente(nome.substr(fim+1) , acao);
        nodoAtual->addNodo(novaAcao);
        return novaAcao;
    }
    return 0x0;
}

bool NodoAmbiente::removeNodo(NodoAmbiente *nodo)
{
    // Poderia remover pelo ID da variavel tbm (seria mais eficiente)
    // Se for implementado, alterar o destrutor para remover pro id
    // chamando second do iterator map
    return removeNodo(nodo->nome());
}

bool NodoAmbiente::removeNodo(const string &nomeNodo)
{
    NodoAmbiente *nodo = getNodoDireto(nomeNodo);

    if(nodo == 0x0)
        return true;

    // Remove do mapa de nomes
    m_mapaNodos.erase(nomeNodo);

    // Remove relacao hirarquica
    m_ambiente->m_grafo.deletaAresta(m_id , nodo->m_id);
    // Esse tipo de deletacao de aresta nao tem complexidade
    // constante no grafo de lista como no metodo que deleta por ID

    // Verifica se ainda possui alguma referencia
    if(m_ambiente->m_grafo.numPredecessores(nodo->m_id) == 0)
    {
        // Se não tem, e a variavel não estiver sendo destruida
        if(!nodo->executandoDestrutor && m_ambiente != nodo)
        {
            // Deleta nodo
            delete nodo;
        }
    }
    return true;
}

const string &NodoAmbiente::nome() const
{
    return m_nome;
}

const string &NodoAmbiente::setNome(string nome)
{
    // Se nao tem ambiente
    if(m_ambiente == 0x0)
    {   // Nodo é solto, nao depende de ninguem
        m_nome = nome;
        return m_nome;
    }

    // Verifica se o novo nome pode ser definido
    // se existir algum conflito com algum pai
    // o nome é modificado para resolver os conflitos
    string novoNome = encontraNomeDisponivel(nome);


    // Pega o numero de pais do nodo
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

unsigned NodoAmbiente::id() const
{
    return m_id;
}

TipoNodoAmbiente NodoAmbiente::tipoNodo() const
{
    return NODO;
}

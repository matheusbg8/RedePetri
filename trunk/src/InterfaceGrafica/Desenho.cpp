

#include "DesenhoMestre.h"
#include "Desenho.h"
#include <cmath>
#include <iostream>
#include <QtOpenGL>
#include "Matriz.h"
#include "Container.h"
#include "DesenhoComposto.h"

using namespace std;


//static Desenho PaiDeTodos(rPonto(0,0),10,10,0x0);

/**
  Construtor de copia
**/
Desenho::Desenho(Container *pai)
{
    inicializaDesenho(rPonto(10,10), 20 , 20 , pai);
}

Desenho::Desenho(rPonto p , int largura, int altura, Container *pai)
{
    inicializaDesenho(p , largura, altura , pai);
}

/**
 Destrutor, o desenho é desalocado, e a referencia do pai para esse
 desenho é removida
**/
Desenho::~Desenho()
{

    cout << "Desenho::Deletando " << m_nome.toStdString() << endl;

    // Este sinal é disparado para
    // Avisar todos as escutas que eu estou sendo deletado
    geraSinal(SINAL_DELETANDO);
    // É importante gerar esse sinal para que os desenhos
    // parem de usar este desenho como escuta (como o desenho seta)


    if(m_pai != 0x0) // Se meu pai é valido
    {
        m_pai->removeDesenho(this);
        m_pai = 0x0;
    }

    setSelecionado(false);
    m_desenhoMestre = 0x0;
}

Desenho *Desenho::novaInstancia() const
{
    Desenho *d = new Desenho();
    copiaMeusParametros(d);
    return d;
}

void Desenho::copiaMeusParametros(Desenho *d) const
{
    d->defineDesenho(posicaoLocal(),largura(),altura());
    d->setCorBorda(corBorda());
    d->setCorFundo(corFundo());
    d->setDesenhaFundo(desenhaFundo());
    d->setVisivel(visivel());
    d->setNomeVisivel(nomeVisivel());
    d->setNome(nomeVisivel()+"_copia");
    d->setFaixaIndexacao(faixaIndexacao());
    d->setIdTipoDesenho(idTipoDesenho());
    d->setIdDesenhoVisivel(idDesenhoVisivel());
    d->setTextoCentro(textoCentro());
    d->setTextoCentroVisivel(textoCentroVisivel());
    d->setTextoInferior(textoInferior());
    d->setTextoInferiorVisivel(textoInferiorVisivel());
}


/**
 * @brief
 *    Este metodo realiza pinta o desenho na widget utilizando as
 * funções openGL, esse é sobrescrito por outros desenhos de mais alto nivel
 */
void Desenho::desenha()
{
    /// @todo - Metodo de desenhos não deveria ser privado?
//    cout << "Desenho:: Desenha ( " << m_nome.toStdString() << ")"<<endl;
     desenhaContainer();
}

/**
  Desenha um retangulo representando o espaço pelo desenho desse desenho
**/
void Desenho::desenhaContainer()
{
    rPonto posicaoGlobal = minhaPosicaoGlobal();
    int x1 = posicaoGlobal.x() , y1 = posicaoGlobal.y(),
        x2 = x1 + m_espaco.largura(), y2 = y1 + m_espaco.altura();

    // Escolhe a cor do retangulo
    glColor3f(m_corBorda.r(),m_corBorda.g(),m_corBorda.b());

    desenhaNome();


    // Desenha o retangulo com preenchimento
    if(m_desenhaFundo)
    {
        glBegin(GL_POLYGON);
            glColor3f(m_corFundo.r(),m_corFundo.g(),m_corFundo.b());
           glVertex2i(x1, y1);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y1);
         glEnd();
    }

    // Desenha a borda do retangulo
    glBegin(GL_LINE_STRIP);
    glColor3f(m_corBorda.r(),m_corBorda.g(),m_corBorda.b());
        if(m_selecionado)
        {    glColor3f(0.0,0.0,1.0);}
        else
        {    glColor3f(0.0,0.0,0.0);}
        glVertex2i(x1, y1);
        glVertex2i(x1, y2);
        glVertex2i(x2, y2);
        glVertex2i(x2, y1);
        glVertex2i(x1, y1);
        glEnd();
}

void Desenho::desenhaTexto(QString txt, const rPonto &p, const QFont &font)
{
    if(m_desenhoMestre != 0x0)
    {
        rPonto posicaoGlobal = minhaPosicaoGlobal();
        m_desenhoMestre->desenhaTexto(posicaoGlobal.x()+ p.x() , desenhoMestre()->altura() - posicaoGlobal.y() -p.y() , txt, font);
    }else
    {
        cout << "Sem desenho mestre para renderizacaoi de texto" << endl;
    }
}


/**
 * @brief
 *  Desenha o nome do desenho na tela, a cima do desenho, apenas se
 * o nome estiver visivel setNomeVisivel(true) e se o desenho possuir
 * um desenho mestre.
 */
void Desenho::desenhaNome()
{
    // Desenha o nome desse denho
    if(m_desenhoMestre)
    {
        if(m_nomeVisivel)
        {
            rPonto posicaoGlobal = minhaPosicaoGlobal();
            m_desenhoMestre->desenhaTexto(posicaoGlobal.x() , desenhoMestre()->altura() - posicaoGlobal.y() - altura() - 5 , m_nome, QFont("Times",12,QFont::Bold));
        }
        if(m_textoInferiorVisivel)
        {
            desenhaTexto(m_textoInferior.c_str() , rPonto(0, -10));
        }
        if(m_textoCentroVisivel)
        {
            desenhaTexto(m_textoCentro.c_str() , rPonto(m_espaco.altura()/2 -5, m_espaco.largura()/2 -5) );
        }
    }
}

void Desenho::desenhaIdDesenho()
{
    if(m_idDesenhoVisivel)
    {
        desenhaTexto(QString("%1").arg(m_idDesenho),rPonto(0,-10));
    }
}


/**
 * @brief
 *  Atualiza os desenhos mostrados na widget.
 */
void Desenho::atualizaVizualizacao()
{
    redesenha();
}

/** Metodo para adicionar um novo desenho a um container,
 como esse desenho não é um container, ele re-passa o
novo desenho para seu pai, caso não tenha pai, o
 novo desenho sera deletado
**/

/**
 * @brief
 *  Atribui um novo desenho, como um desenho comum não pode
 * ter outros desenhos, esse metodo é repassado para o desenho
 * pai, se o desenho não possuir um pai, o novo desenho sera
 * deletado e uma mensagem sera enviada para a saida padrão.
 * @param d - Novo desenho.
 * @param avisaFilho - Avisa desenho filho do novo pai,
 * por padrão esse parametro é true.
 */
void Desenho::novoDesenho(Desenho *d, bool avisaFilho)
{
    if(m_pai != 0x0)
    {
        m_pai->novoDesenho(d, avisaFilho);
    }else
    {
        cout << "Novo desenho não pode ser criado, não foi encontrado container" << endl;
        delete d;
    }
}

/** Utiliza o metodo contemrPonto do Desenho **/
bool Desenho::desenhoContemrPonto(const rPonto &ponto)
{
    // Chama o metodo contemrPonto do desenho e não de classes derivadas
    return Desenho::contemrPonto(ponto);
}

/** Veirifica o ponto pertence area ocupada pelo desenho deste Desenho **/
bool Desenho::contemrPonto(const rPonto &p) const
{
    return m_espaco.contemrPonto(p);
}

void Desenho::rotaciona(double ang)
{
    cout << "Rotação em desenho basico" << endl;
}

/**
 * @brief
 * Desloca o desenho em X e Y.
 * @param deslocamento - Ponto que representa o deslocamento em X, e Y.
 */
void Desenho::translada(const rPonto deslocamento)
{
    setPosicao(posicaoLocal()+ deslocamento);
}

/**
 * @brief
 *  Este metodo deve ser reescrito pelas classs derivadas, ele retorna um
 * ponto de ligação para uma seta definido como a intersecção de uma reta
 * formado pelo centro do desenho e um ponto, com a borda do desenho.
 * Por padrão esse metodo retorna a posição do desenho.
 * do desenh
 * @param p - Ponto que defne a reta.
 * @return rPonto - Ponto de intersecção no referencial local (do pai do desenho)
 */
rPonto Desenho::posicaoLigacao(const rPonto &pInicialReta)
{
    return m_espaco.posicao();
}

/** Processa o novo MouseEvento, distribuindo enviando ele para um dos metodos:
* mousePrecionado()
* mouseSolto()
* mouseMovendo()
 De acordo com o tipo de evento do MouseEvento
**/


/**
 * @brief
 *  Recebe um evento do mouse
 * @param mouseEvento - Evento recebido
 * @param distribuicao - Tipo de dos
 * @return bool
 */
bool Desenho::novoMouseEvento(MouseEvento *mouseEvento)
{
    if(produzLog)
    cout << "Desenho( " << m_nome.toStdString() << " ) :: novoMouseEvento()"<< endl;
    switch(mouseEvento->evento())
    {
    case MOUSE_PRECIONADO:
        setEscutaMouseMovendo(true);
        setEscutaMouseSolto(true);
        if(produzLog)
        cout << "Desenho( " << m_nome.toStdString() << " ) :: mousePrecionado()"<< endl;
        return mousePrecionado(mouseEvento);
    break;
    case MOUSE_SOLTO:
        setEscutaMouseMovendo(false);
        setEscutaMouseSolto(false);

        if(produzLog)
            cout << "Desenho( " << m_nome.toStdString() << " ) :: mouseSolto()"<< endl;

        return mouseSolto(mouseEvento);
    break;
    case MOUSE_CLIQUE:

        break;
    case MOUSE_MOVENDO:
        if(produzLog)
        cout << "Desenho( " << m_nome.toStdString() << " ) :: mouseMovendo()"<< endl;

        return mouseMovendo(mouseEvento);
        break;
    }
    return true;
}

/**
 * @brief
 *  Define a cor de fundo do desenho
 * @param cor - Cor que sera definida
 */
void Desenho::setCorFundo(const Cor& cor)
{
    m_corFundo = cor;
}

const Cor &Desenho::corFundo() const
{
    return m_corFundo;
}


/**
 * @brief
 *  Define se o fundo do desenho sera desenhado ou não
 * @param simNao - true para desenhar, false para não desenhar
 */
void Desenho::setDesenhaFundo(bool simNao)
{
    m_desenhaFundo = simNao;
}

void Desenho::setCorBorda(const Cor& cor)
{
    m_corBorda = cor;
}

const Cor &Desenho::corBorda() const
{
    return m_corBorda;
}

/**
 * @brief
 *  Este metodo é chamado sempre que um sinal é recebido
 * ele interpreta o sinal e gera um evento dentro do Desenho
 * chamando o metodo que trata esse evento.
 * @param sinal - Sinal que sera interpretado.
 */
void Desenho::novoSinal(const Sinal &sinal)
{
    // Procurei dechar os cases em ordem dos mais frequentemente usados
    switch(sinal.tipo())
    {
    case SINAL_ALTERACAO_POSICAO:
        eventoAlteracaoPosicao(sinal.origem());
    break;
    case SINAL_ALTERACAO_LARGURA:
        eventoAlteracaoLargura(sinal.origem());
    break;
    case SINAL_ALTERACAO_ALTURA:
        eventoAlteracaoAltura(sinal.origem());
    break;
    case SINAL_ALTERACAO_SELECAO:
        /** @todo revisar falha segmentacao aqui
         * Isto esta acontecendo pq esta sendo definida uma
         * escuta invalida para o circulo (deveria ter 2 arcos)
         * escutando, mas tem 1 arco e um objeto indefinido.
         * Acho que tem a ver com as varias visualizacoes de uma mesma
         * rede, pois a falha so ocorre quando estamos visualizando 2 vezes
         * o mesmo modelo.
         */
        eventoAlteracaoSelecao(sinal.origem());
    break;
    case SINAL_DELETANDO:
        eventoDeletando(sinal.origem());
    break;
    case SINAL_INVALIDO:
    default:
        cout << "Desenho( " << m_nome.toStdString() << "):: novoSinal() - Não sabe tratar o sinal." << endl;
    }
}


/**
 * @brief
 * Define a visibilidade do desenho.
 * @param visivel - True- O desenho ser visivel, False- Não sera visivel.
 */
void Desenho::setVisivel(bool visivel)
{
    /** @todo - A verificação se o desenho é visivel ou não
      * para desenhar ou para verificar se contem um ponto é feito
      * pelo container ou pelo desenhoComposto que contem  o desenho
      * e não pelo proprio desenho, ou seja, se o metodo do desenhar()
      * do desenho for chamado, ele sera desenhado mesmo se ele não for
      * visivel, o Container ou Desenho composto que verifica se o
      * desenho é visivel ou não e chama o metodo desenhar se necessario
      * talvez isso tenha que ser mudado para que esse tratamento seja feito
      * dentro do desenho.
    **/

    this->m_visivel = visivel;
}


/**
 * @brief
 *  Define se um desenho esta selecionado ou não, se um desenho
 * for definido como selecionado, essa definição implica na
 * definção de selecionado de todos os desenhos pais, até chegar
 * na raiz da arvore.
 * O desenhoMestre armazena o desenho selecionado de
 * mais baixo nível (o que teve seu metodo chamado).
 * @param selecionado - true para desenho selecionado,
 * false para desenho não selecionado.
 * @param selecaoAcumulativa - Se esse parametro for true,
 * os desenhos que já estavam selecionados, vão continuar
 * selecionado, por padrão esse parametro é sempre false.
 * Obs.: O desenhoMestre não aceita a definição acumulativa
 * de seleção para desenhos que não possuem o mesmo pai, pois
 * eles estão em containers separados, não podem ser selecionados
 * ao mesmo tempo.
 */

void Desenho::setSelecionado(bool selecionado)
{
    // Define a seleção para os pais
    if(selecionado && m_pai != 0x0 && m_pai != this && !m_pai->selecionado())
    {
        m_pai->setSelecionado(true);
    }

    m_selecionado = selecionado;
    geraSinal(SINAL_ALTERACAO_SELECAO);

    // Avisa o desenho mestre da nova seleção
    if(m_desenhoMestre != 0x0)
    {
        if(selecionado)
            m_desenhoMestre->setSelecionado(this);
        else
            m_desenhoMestre->setSelecionado(0x0);
    }
}

void Desenho::setMovendo(bool movendo)
{
    this->movendo = movendo;
}


/**
 * @brief
 *  Define o nome do desenho
 * @param nome - Nome que sera definido
 */
void Desenho::setNome(QString nome)
{
    this->m_nome = nome;
}


void Desenho::setMestre(DesenhoMestre *mestre)
{
    this->m_desenhoMestre = mestre;
}


/**
 * @brief
 *  Este metodo define um novo Container pai
 *para o desenho.
 *
 *  Este metodo remove a sua relção com o antigo
 *pai e estabelece uma nova com seu novo pai.
 *
 * @param pai - Novo Pai
 * @param avisaPai - true para avisar novo pai do desenho, false
 * para não avisar, por default esse parametro é true.
 */
void Desenho::setPai(Container *pai, bool avisaPai)
{
    if( m_pai != pai || (/*(implicito) m_pai == pai &&*/ m_componente))
    {
        Container *antigoPai = m_pai;
        if(antigoPai != 0x0) // Se meu antigo pai existe
        {
            m_pai = 0x0; // Evita loop infinito quando setPai(0x0) é chamado.
            antigoPai->removeDesenho(this); // setPai(0x0) sera chamado
        }

        m_pai = pai;
        setComponente(false);

        if( pai != 0x0 ) // Se o pai é valido
        {
            if(avisaPai)
                m_pai->novoDesenho(this, false);

            setMestre(pai->desenhoMestre()); // Define o mestre do pai, o mesmo meu mestre
        }
    }
}


/**
 * @brief
 *   Define o desenho composto no qual o desenho faz parte.
 * @param pai - Desenho composto que o desenho faz parte.
 * @param avisaPai - true se o DesenhoComposto deve ser avisado
 * do novo desenho componente, por padrão esse parametro é true.
 */
void Desenho::setComponente(DesenhoComposto *pai, bool avisaPai = true)
{
    // Se eu sou eu não sou filho, ou se eu sou filho e não sou uma componente( nesse caso sou um desenho normal )
    if( m_pai != pai || ( /* (implicito) m_pai == pai &&*/ !m_componente)) // Se novo pai é diferente pai atual, evita loop infinito
    {

        Container *antigoPai = m_pai;

        if(antigoPai != 0x0) // Se meu antigo pai existe
        {
            m_pai = 0x0; // Evita loop infinito quando setPai(0x0) é chamado.
            antigoPai->removeDesenho(this); // setPai(0x0) sera chamado
        }

        m_pai = pai;
        setComponente(true);

        if( pai != 0x0) // Se o pai é valido
        {
            if(avisaPai)
                pai->novaComposicao(this,false);

            setMestre(pai->desenhoMestre()); // Define o mestre do pai, o mesmo meu mestre
        }
    }
}

/**
 * @brief
 *  Habilita ou desabilita escuta
 * do mouse sendo precionado.
 * @param simOuNao
 */
void Desenho::setEscutaMousePrecionado(bool simOuNao)
{
    if(produzLog)
    cout << getNome().toStdString() << " ----> escuta mouse PRECIONADO " << simOuNao << endl;
    escutaEventoMousePrecionado = simOuNao;
}

/**
 * @brief
 *  Habilita ou desabilita escuta
 * do mouse sendo solto.
 * @param simOuNao
 */
void Desenho::setEscutaMouseSolto(bool simOuNao)
{
    if(produzLog)
    cout << getNome().toStdString() << " ----> escuta mouse SOLTO " << simOuNao << endl;
    escutaEventoMouseSolto = simOuNao;
}

/**
 * @brief
 *  Habilita ou desabilita escuta
 * do mouse movendo.
 * @param simOuNao
 */
void Desenho::setEscutaMouseMovendo(bool simOuNao)
{
    if(produzLog)
        cout << getNome().toStdString() << " ----> escuta mouse MOVENDO " << simOuNao << endl;
    escutaEventoMouseMovendo = simOuNao;
}


/**
 * @brief
 *  Habilita ou desabilita escuta
 * dos eventos do mouse.
 * @param simOuNao
 */
void Desenho::setEscutaMouseEvento(bool simOuNao)
{
    setEscutaMousePrecionado(simOuNao);
    setEscutaMouseSolto(simOuNao);
    setEscutaMouseMovendo(simOuNao);
}

/**
 * @brief
 *  Retorna true se o desenho esta escutando
 * eventos do mouse sendo precionado
 * @return bool
 */
bool Desenho::escutaMousePrecionado()
{
    return escutaEventoMousePrecionado;
}

/**
 * @brief
 *  Retorna true se o desenho esta escutando
 * eventos do mouse sendo soltado
 * @return bool
 */
bool Desenho::escutaMouseSolto()
{
    return escutaEventoMouseSolto;
}


/**
 * @brief
 *  Retorna true se o desenho esta escutando
 * eventos do mouse movendo
 * @return bool
 */
bool Desenho::escutaMouseMovendo()
{
    return escutaEventoMouseMovendo;
}




/**
 * @brief
 * Retorna a posição do desenho no referencial do seu pai
 * @return rPonto - Posição do desenho no referencial de seu pai.
 */
const rPonto& Desenho::posicaoLocal() const
{
    return m_espaco.posicao();
}


/**
 * @brief
 *  Retorna a altura do desenho
 * @return int
 */
int Desenho::altura() const
{
    return m_espaco.altura();
}

int Desenho::largura() const
{
    return m_espaco.largura();
}


/**
 * @brief
 *  Retorna o ID do desenho.
 * @return int
 */
int Desenho::id()
{
    return desenho_id;
}


/**
 * @brief
 *  Retorna o identificador atribuido ao desenho
 * @return int
 */
int Desenho::idDesenho() const
{
    return m_idDesenho;
}


/**
 * @brief
 *  Define um identificador para o desenho
 * @param id
 */
void Desenho::setIdDesenho(int id)
{
    m_idDesenho = id;
}


/**
 * @brief
 *  Retorna o identificador do tipo do desenho
 * @return int
 */
int Desenho::idTipoDesenho() const
{
    return m_idTipoDesenho;
}


/**
 * @brief
 *  Define o identificador do tipo do desenho
 * @param id
 */
void Desenho::setIdTipoDesenho(int id)
{
    m_idTipoDesenho = id;
}


/**
 * @brief
 *  Retorna a faixa de indexacao do desenho
 * @return int
 */
int Desenho::faixaIndexacao() const
{
    return m_faixaIndexacao;
}


/**
 * @brief
 *  Define a faixa de indexacao de um desenho
 * @param faixa
 */
void Desenho::setFaixaIndexacao(int faixa)
{
    m_faixaIndexacao = faixa;
}

bool Desenho::idDesenhoVisivel() const
{
    return m_idDesenhoVisivel;
}

void Desenho::setIdDesenhoVisivel(bool simNao)
{
    m_idDesenhoVisivel = simNao;
}


/**
 * @brief
 *  Retorna o pai do desenho, ou zero se não existir pai
 * @return Container
 */
Container *Desenho::pai()
{
    return m_pai;
}

DesenhoMestre *Desenho::desenhoMestre()
{
    return m_desenhoMestre;
}


/**
 * @brief
 *  Retorna a posição X do desenho com referencia a posição de seu pai
 * @return float
 */
float Desenho::x()
{
    return m_espaco.x();
}



/**
 * @brief
 *  Retorna a posição Y do desenho com orgem na posição do pai
 * @return float
 */
float Desenho::y()
{
    return m_espaco.y();
}


void Desenho::alinhar()
{
    if(m_pai != 0x0)
    {
        m_pai->alinhar();
    }
}


/**
 * @brief
 *  Retorna o nome do desenho
 * @return QString - Uma string com a cópia do nome.
 */
const QString &Desenho::getNome() const
{
    return m_nome;
}

bool Desenho::estaMovendo()
{
    return movendo;
}


/**
 * @brief
 *  Devolve a informação se o desenho esta selecionado ou não
 * quando um desenho esta selecionado, o foco do usuario esta
 * voltado para ele, as ações do usuario sera aplicada diretamente
 * ao(s) desenho(s) selecionado(s).
 * @return bool - true se o desenho estiver selecionado, false
 * caso contrario.
 */
bool Desenho::selecionado()
{
    return m_selecionado;
}


/**
 * @brief
 *  Retorna a informação se o desenho é visivel ou não. Quando o desenho
 * não é visivel.
 * @return bool - true se o desenho é visivel, false caso contrario.
 * @todo - O metodo responsavel pelo controle dos desenhos visiveis e
 * não visiveis é o novoSinal(), o que parece ser estranho, talves esse
 * contro tenha que ser feito pelo metodo desenhar().
 */
bool Desenho::visivel() const
{
    return m_visivel;
}

/**
 * @brief
 *  Verifica se o fundo do desenho esta sendo desenhado ou não,
 * esta opção pode ser alterada utilizando o metodo setDesenhaFundo()
 * @return bool
 */
bool Desenho::desenhaFundo() const
{
    return m_desenhaFundo;
}


/**
 * @brief
 *  Retorna a informação se o desenho é uma componente do desenho composto
 * ou não.
 * @return bool - true é uma componente, false - não é uma componente
 */
bool Desenho::componente()
{
    return m_componente;
}

TipoDesenho Desenho::tipoDesenho()
{
    return m_tipoDesenho;
}

Desenho * Desenho::getPaiDeTodos()
{
    return 0x0 /*&PaiDeTodos*/;
}

void Desenho::inicializaDesenho(const rPonto &posicao , int largura, int altura, Container *pai)
{
    desenho_mid = desenho_id++; // Pega o ID dos desenhos
    this->m_pai = 0x0;  // Define sem pai

    this->m_desenhoMestre = 0x0; // Sem desenhoMestre
    m_tipoDesenho = TD_DESENHO;
    m_nomeVisivel = false;
   f_distribuindoSinal = false; // FLAG utilizada para gerenciar a distribuicao de sinal

    defineDesenho(posicao , largura , altura);

    setVisivel(true);  // Desenho visivel
    setMovendo(false); // Desenho não se movendo

    geraSinal(true); // Ativa geração de sinais

    setEscutaMousePrecionado(true);
    setEscutaMouseSolto(false);
    setEscutaMouseMovendo(false);

    setNome(QString("Desenho %1").arg(id() ));

    setCorFundo(Cor::branco);
    setCorBorda(Cor::preto);

    setDesenhaFundo(true);

    setFaixaIndexacao(-1);
    setIdTipoDesenho(-1);
    setIdDesenho(-1);

    setIdDesenhoVisivel(false);
    setTextoCentroVisivel(false);
    setTextoInferiorVisivel(false);

    if(pai != 0x0)
        pai->novoDesenho(this);

    setSelecionado(false);
}


/**
 * @brief
 * rfgjeg
 * @param desenho
 * @return bool
 */
bool Desenho::estaEscutando(Desenho *desenho)
{
    list<Desenho *>::iterator i;
    for(i = m_escutas.begin() ; i != m_escutas.end() ; i++)
    {
        if((*i) == desenho)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief
 * Este metodo estabelece uma relação dupla de escuta entre os desenhos,
 * um escuta o que acontece com o outro, é necessario que aligação seja
 * dupla porque, se fosse simples, o dsenho que esta escutando poderia
 * ser deletado, e o desenho escutado não seria avisado, causando um problema
 * quando o desenh escutado gerar um sinal.
 * @param d
 */
void Desenho::novaEscuta(Desenho *d)
{

    if(d != 0x0)
    {
        if(d->tipoDesenho() == TD_INDEFINIDO)
        {
            cout << "PROBLEMA!!" << endl;
        }
        m_escutas.push_back(d);
        d->m_escutas.push_back(this);
    }
}


/**
 * @brief
 *  Remove o desenho da lista de escutas desse desenho.
 * @param d - Desenho que sera removido da lista de escutas.
 */
void Desenho::removeEscuta(Desenho *d, bool remocaoDupla)
{
    cout << "Desenho("<< getNome().toStdString() << ")::removeEscuta(" << d->getNome().toStdString() << ")" << endl;
    cout << "m_escutas.size() = " << m_escutas.size() << endl;
    // Um problema curioso aparece aqui
    // Quando esta sendo distribuido um sinal
    // para todos os desenhos que estão escutando
    // eventualmente um deles pode querer para
    // de escutar esse desenho, se removendo
    // da lista de escuta chamando este metodo.
    // O problema é que ainda não foi distribuido
    // o sinal para todos os desenhos, só que
    // a lista de escutas foi alterada! Isso
    // gera uma falha de segmentação no for
    // do metodo que distribui os sinais, pois
    // o desenhos removido foi extamente o que
    // estava no interador, e por algum motivo
    // a list da STL se perde com esse elemento
    // é removido da lista.
    // Para tratar esse problema, criei uma lista
    // de desenhos temporarios e uma flag que indica
    // quando um sinal esta sendo distribuido
    // Se algum desenho for removido da lista de
    // escutas durante uma distribuição de sinal
    // essa operação não sera realizada, ela sera
    // armazenada e realizada apos o sinal ser
    // propagado para todos os desenhos escutantes.

    /** @todo - Cuidar para que esse problema não se repita
     * em outro lugar do código, como por exemplo na lista
     * de filhos do container.
    **/
    // Tomar cuidado de não usar a lista de desenhos
    // temporarios ao mesmo tempo que outro metodo.

    if(d != 0x0) // Se o desenho é válido
    {
         // Se esta acontecendo uma distribuição de sinal
        if( f_distribuindoSinal )
        {
            listaDesenhosTemporarios.push_back(d);
        }
        else
        {
            m_escutas.remove(d);
            if(remocaoDupla)
                d->removeEscuta(this,false);
        }
    }

    cout << "m_escutas.size() = " << m_escutas.size() << endl;
    cout << "Desenho("<< getNome().toStdString() << ")::removeEscuta(" << d->getNome().toStdString() << ") - Concluido" << endl;

}

void Desenho::removeTodasEscutas()
{
    list<Desenho*>::iterator i;
    while(!m_escutas.empty())
    {
        i = m_escutas.begin();
        removeEscuta(*i);
    }
}


/**
 * @brief
 *  Este metodo retorna um objeto superior a classe desenho,
 * por exemplo, se o tipo de um desenho tipoDesenho(), for Seta
 * quando chamado esse metodo, um ponteiro para a seta sera
 * retornado, esse ponteiro é do tipo void, para que possa
 * ser feito um cast para o tipo especifico, este cast deve
 * ser feito de acordo com o tipo do objeto.
 */
void *Desenho::getSuper()
{
    return this;
}

/**
 * @brief
 * Este metodo distribui um sinal para todos os desenhos que
 * estão escutando esse desenho.
 * @param sinal - Sinal que sera distribuido
 * @param listaDistribuicao - Lista com os desenhos que receberão
 * o sinal.
 */
void Desenho::distribuiSinal(const Sinal &sinal, list<Desenho*> &listaDistribuicao)
{
    // Explicações porque dos temporarios e da flag f_distribuindoSinal
    // esta disponivel no metodo removeEscuta(Desenho*)

    // Se a lista estiver vazia, encerra.
    if(listaDistribuicao.empty())
        return;

    // Define flag para iniciar distribuição de sinais e limpa temporarios
    f_distribuindoSinal = true;

    //Por algum motivo estava dando falha de seg. quando clear() da lista vazia
    if(!listaDesenhosTemporarios.empty())
        listaDesenhosTemporarios.clear();

    list<Desenho*>::iterator i;
    for(i = listaDistribuicao.begin() ; i != listaDistribuicao.end() ; i++)
    { // Esse sinal pode causar a remocao do proximo desenho da lista(Por isso a lisa de temporarios)
        (*i)->novoSinal(sinal);
    }

    // Define fim de distribuição de sinal, e remove temporarios
    f_distribuindoSinal = false;
    // Remove desenhos temporarios gerado pelo metodo removeEscuta
    // durante a distribuição de sinal
    for(i = listaDesenhosTemporarios.begin() ; i != listaDesenhosTemporarios.end() ; i++)
    {
        removeEscuta((*i));
    }
    listaDesenhosTemporarios.clear();

}

/**
 * @brief
 *  Gera um novo sinal e distribui primeiro para o desenho pai
 * e depois para os desenho que estão escutando esse desenho.
 * @param tipoSinal - tipo de sinal que sera gerado.
 * Obs.: A distribuição do sinal é realizada pelo metodo distribuiSinal().
 */
void Desenho::geraSinal(TipoSinal tipoSinal)
{
/*    if(!m_escutas.empty())
    {
        redesenha();
        Sleep(500);
    }*/

    if(m_geraSinal)
    {
        Sinal novo_sinal(tipoSinal, this);

        if(m_pai != 0x0)
            m_pai->novoSinal(novo_sinal);

        distribuiSinal(novo_sinal, m_escutas);
    }
}

void Desenho::geraSinal(bool simNao)
{
    m_geraSinal = simNao;
}


/**
 * @brief
 *  Este metodo é chamado sempre que um desenho que esta sendo escutado sofre uma alteração
 * de posição. Uma escuta para os eventos de desenho pode ser criada com o metodo
 *  novoOuvinteDesenhoEvento.
 * @param desenho - Desenho que sofreu a alteração de posição
 * @param novaPosicao - Nova posição do desenho
 */
void Desenho::eventoAlteracaoPosicao(Desenho *desenho)
{
    // Por padrão um desenho não faz nada com eventos de outros desenhos
}


/**
 * @brief
 *  Este metodo funciona da mesma forma que o metodo eventoAlteracaoPosicao, porem
 * com a alteração da largura.
 * @param desenho - Desenho que sofreu a alteração
 * @param novaLargura - Nova largura do desenho
 */
void Desenho::eventoAlteracaoLargura(Desenho *desenho)
{
    // Por padrão um desenho não faz nada com eventos de outros desenhos
}


/**
 * @brief
 *  Este metodo funciona da mesma forma que o metodo eventoAlteracaoPosicao, porem
 * com a alteração da altura.
 * @param desenho - Desenho que sofreu a alteração
 * @param novaAltura - Nova altura do desenho
 */
void Desenho::eventoAlteracaoAltura(Desenho *desenho)
{
    // Por padrão um desenho não faz nada com eventos de outros desenhos
}


/**
 * @brief
 *  Este metodo deve ser reescrito por uma classe derivada, ele é chamado
 * sempre que um desenho escutado é selecioado ou deselecionado.
 * @param desenho - Desenho que sofreu aleração de seleção.
 * @param seleconado - Informação se o desenho agora esta selecionado ou deselecionado
 */
void Desenho::eventoAlteracaoSelecao(Desenho *desenho)
{
    // Por padrão o desenho não faz nada
}


/**
 * @brief
 *  Este metodo é chamdo sempre quando um desenho que esta sendo escutado
 * for deletado, isso significa que esse desenho nunca mais gerara eventos.
 *
 * .
 * @param desenho - Desenho que esta sendo deletado.
 */
void Desenho::eventoDeletando(Desenho *desenho)
{
    removeEscuta(desenho);

    // Por padrão o desenho não faz nada com escutas que estão sendo
    // deletadas, esse metodo deve ser escrito por uma classe derivada
    // se for necessario.

    // Exemplo: A classe Seta precisa rescrever esse metodo
    // porque ela precisa saber quando um desenho que ela esta
    // ligando foi deletado, para remover essa ligação.
}

/**
 * @brief
 *  Define a posição, largura e altura utilizada pelo desenho
 * @param posicao - Posição do desenho, no referencial do seu pai, ou da janela se não houver pai.
 * @param largura - Largura do desenho
 * @param altura - Altura do desenho
 */
void Desenho::defineDesenho(const rPonto &posicao, int largura, int altura)
{
    if(produzLog)
    cout << "Desenho(" << m_nome.toStdString()
         << ")::defineDesenho(" << posicao
         << " , " << largura << " , " << altura << ")\n";

    /* A definição do desenho deve ser
      atomica, não pode usar setAltura, setLargura
      e setPosicao, pq sinais intermediarios são gerados
      sem que o desenho esteja definido, fazendo com que
      o container se ajuste a um desenho que não existe.
    */

    bool baltura, blargura, bposicao;
    baltura = blargura = bposicao = false;

    if(altura != m_espaco.altura())
    {
        m_espaco.setAltura(altura);
        baltura = true;
    }
    if(largura != m_espaco.largura())
    {
        m_espaco.setLargura(largura);
        blargura = true;
    }
    if(posicao != m_espaco.posicao())
    {
        m_espaco.setPosicao(posicao);
        bposicao = true;
    }
    // Gera sinais apenas depois da definição completa do desenho
    if(blargura) geraSinal(SINAL_ALTERACAO_LARGURA);
    if(baltura) geraSinal(SINAL_ALTERACAO_ALTURA);
    if(bposicao) geraSinal(SINAL_ALTERACAO_POSICAO);
}

void Desenho::setX(float XLocal)
{
    // Se minha posição é diferente da nova
    if(XLocal != m_espaco.x())
    {
        m_espaco.setX(XLocal);
        geraSinal(SINAL_ALTERACAO_POSICAO);
    }
}

void Desenho::setY(float YLocal)
{
    // Se minha posição é diferente da nova
    if(YLocal != m_espaco.y())
    {
        m_espaco.setY(YLocal);
        geraSinal(SINAL_ALTERACAO_POSICAO);
    }
}


/**
 * @brief
 *  Define a posicao do desenho, esta posicao é em relacao ao referencial
 * externo (o referencial do pai, ou da janela se não houver pai)
 * @param novaPosicao - Posição do desenho no referencial de seu pai.
 */
void Desenho::setPosicao(const rPonto & novaPosicao)
{
    // Se minha posição é diferente da nova
    if(novaPosicao != m_espaco.posicao())
    {
        m_espaco.setPosicao(novaPosicao);
        geraSinal(SINAL_ALTERACAO_POSICAO);
    }
}

/**
 * @brief
 *  Chama o metodo setPosicao.
 * @param posicaoLocal - Posicao com relação ao referencial do pai.
 */
void Desenho::setPosicaoLocal(const rPonto & posicaoLocal)
{
    setPosicao(posicaoLocal);
}

/**
 * @brief
 *  Define a posição do desenho, a posição tem que estar
 * no referencial da janela principal (referencial global)
 * @param posicaoGlobal - Posição no referencial global (da janela principal)
 */
void Desenho::setPosicaoGlobal(const rPonto & posicaoGlobal)
{
    setPosicao(posicaoGlobal - minhaPosicaoGlobal());
}

/**
 * @brief
 *  Define a largura do desenho
 * @param largura - Nova largura do desenho
 */
void Desenho::setLargura(int largura)
{
    if(largura != m_espaco.largura())
    {
        m_espaco.setLargura(largura);
        geraSinal(SINAL_ALTERACAO_LARGURA);
    }
}

/**
  Define a altura do desenho
**/
void Desenho::setAltura(int altura)
{
    if(altura != m_espaco.altura())
    {
        m_espaco.setAltura(altura);
        geraSinal(SINAL_ALTERACAO_ALTURA);
    }
}

/**
 * @brief
 *  Define se o nome do desenho sera renderizado na tela ou não.
 * @param sinNao - true para mostrar o nome do desenho, false caso contrario.
 */
void Desenho::setNomeVisivel(bool sinNao)
{
    m_nomeVisivel = sinNao;
}

bool Desenho::nomeVisivel() const
{
    return m_nomeVisivel;
}

void Desenho::setTextoCentro(const string &texto)
{
    m_textoCentro = texto;
}

void Desenho::setTextoCentroVisivel(bool simNao)
{
    m_textoCentroVisivel = simNao;
}

const string Desenho::textoCentro() const
{
    return m_textoCentro;
}

bool Desenho::textoCentroVisivel() const
{
    return m_textoCentroVisivel;
}

void Desenho::setTextoInferior(const string &texto)
{
    m_textoInferior = texto;
}

void Desenho::setTextoInferiorVisivel(bool simNao)
{
    m_textoInferiorVisivel = simNao;
}

const string &Desenho::textoInferior() const
{
    return m_textoInferior;
}

bool Desenho::textoInferiorVisivel() const
{
    return m_textoInferiorVisivel;
}

void Desenho::redesenha()
{
    if(m_desenhoMestre != 0x0)
        m_desenhoMestre->redesenha();
}


/** Retorna a posicao global do objeto **/
rPonto Desenho::minhaPosicaoGlobal() const
{
    return referencialP() + m_espaco.posicao();
}

/** Converte um ponto no referencial do objeto, para o referencial global **/
rPonto Desenho::converteReferenciaGlobal(const rPonto &pMeuReferencia) const
{
    return minhaPosicaoGlobal() + pMeuReferencia;
}

/** Converte um ponto no referencial do pai do objeto, para o referencial do objeto **/
rPonto Desenho::converteMeuReferencial(const rPonto &pReferenciaDoPai) const
{
    return pReferenciaDoPai - m_espaco.posicao();
}

/** Converte um ponto no referencial do objeto, para o referencial do pai do desse objeto**/
rPonto Desenho::converteReferencialPai(const rPonto &pMeuReferencial) const
{
    return m_espaco.posicao() + pMeuReferencial;
}

rPonto Desenho::referencialP() const
{
    if(m_pai != 0x0)
    {
        return m_pai->posicaoLocal() + m_pai->referencialP();
    }
    return rPonto(0,0);
}


/**
 * @brief
 *  Este metodo deve ser reescrito pelas classes derivadas, ele define o comportamento
 * padrão de um desenho quando ocorre um precionamento do mause em cima dele.
 *
 * @param mouseEvento
 */
bool Desenho::mousePrecionado(MouseEvento *mouseEvento)
{
    if(m_desenhoMestre != 0x0) // Se existe desenho mestre
    {
        if(produzLog)
        cout <<"Fui clikado |" << m_nome.toStdString() << "| Local = " <<  mouseEvento->posicaoLocal() <<
              "| global " << mouseEvento->posicaoGlobal()  << endl;

//  Remove a seleção de todos desenhos existente
//        m_desenhoMestre->novoSinal(SINAL_DESELECIONAR_TODOS);

        // Seleção exclusiva par ao pai!!
        if(m_pai != 0x0 && m_pai != this)
            m_pai->removeSelecaoFilhos();

        setSelecionado(true);

        setMovendo(true);
        setEscutaMouseMovendo(true);
        setEscutaMouseSolto(true);

        dDifPosicaoLocalClique = mouseEvento->posicaoLocal() - m_espaco.posicao();
        return true;
    }
    cout << "Erro, Desenho sem desenho mestre!!" << endl;

    return false;
}

bool Desenho::mouseSolto(MouseEvento *e)
{
    setMovendo(false);
    setEscutaMouseSolto(false);
    setEscutaMouseMovendo(false);
    setEscutaMousePrecionado(true);
    if(produzLog)
    cout << "Solto " << getNome().toStdString() << endl;

    return true;
}


/**
  @brief  Este metodo é chamado quando um evento de mouse movendo é gerado em cima do
  desenho.\n
  A reação é alterar a sua posição de acordo com o movimento do mouse,
  chamando o metodo setPosicao().
  @param e - Evento gerado pelo mouse.
**/
bool Desenho::mouseMovendo(MouseEvento *e)
{
    if(movendo && m_desenhoMestre != 0x0)
    {
        if(produzLog)
        cout << "Movendo " << getNome().toStdString() << " | " << e->posicaoLocal()
             << " Global " << e->posicaoGlobal() << endl;
        setPosicao(e->posicaoLocal() - dDifPosicaoLocalClique);

        return true;
    }
    return false;
}

/**
 * @brief
 *  Redimensiona a largura, altura ou posição do desenho para que ele possa
 * conter um ponto, e continue contendo todos os outros pontos de antes
 * da chamada deste metodo.
 * @param ponto - Ponto que o desenho se ajustara, este ponto tem que
 * estar com o referencial do pai do desenho que o metodo é chamado.
 * @return rPonto - Vetor inverso ao deslocamento dado pelo Desenho para
 * se ajustar, se uma alteração de posição do desenho ocorrer, esse vetor
 * indica o sentido contrario da alteração dessa posição, de forma que
 * se o desenho for transladado em direção a esse vetor, ele retornara
 * a posição antiga de antes da chamada deste metodo.
 */
rPonto Desenho::ajustaDesenho(const rPonto &pRefPai)
{
    int px1 = m_espaco.x()   , py1 = m_espaco.y(),  // p1 é ponto inferior esquerdo do desenho
        px2 = px1 + m_espaco.largura() , py2 = py1 + m_espaco.altura(), // p2 é o ponto superior direito do desenho
        mpx = pRefPai.x()              , mpy = pRefPai.y(); // mp é o ponto que esta sendo testado

    // Novos valores de altura, largura e  posição que serão calculados
    int nlarg = m_espaco.largura(),   // Nova largura
        nalt= m_espaco.altura() ,     // Nova altura
        npx = px1 , npy = py1;      // Nova posição

    /*
    cout << "mpx " << mpx << " mpy " << mpy << endl;
    cout << "px1 " << px1 << " py1 " << py1 << endl;
    cout << "px2 " << px2 << " py2 " << py2 << endl;
*/

    // Verifica se o ponto esta fora do desenho pela equerda
    if(mpx < px1)
    {
        // Estou definindo 12 pixel de folga no redim.
        // por causa da seta que possui 10 pixel de folga
        nlarg = m_espaco.largura() + (px1  - mpx) + 12.f;
        npx = mpx -12.f;
    }

    // Verifica se o ponto esta fora do desenho pela direita
    if(mpx > px2)
    {
        // Estou definindo 12 pixel de folga no redim.
        nlarg = m_espaco.largura() + (mpx - px2) +12;
    }

    // Verifica se o o ponto esta fora do desenho por cima
    if(mpy < py1)
    {
        nalt = m_espaco.altura() + (py1  - mpy) +12;
        npy = mpy -12;
    }

    // Verifica se o ponto esta fora do desenho por baixo
    if(mpy > py2)
    {
        nalt = m_espaco.altura() + mpy - py2 +12;
    }

    /*
    cout << nome.toStdString() << " redimensionalizado para ( " << dPosicaoLocal.x() << " , "  << dPosicaoLocal.y()
         << " [ " << dLargura << " , " << dAltura << " ] )" << endl;
    cout << "npx " << npx << " npy " << npy << endl;
    cout << "nalt " << nalt << " nlarg " << nlarg << endl;
*/

    if(npx != px1 || npy != py1 || nlarg != px2-px1 || nalt != py2-py1)
    {

        rPonto p(npx , npy);
//        cout << m_nome.toAscii().constData() << " redimensionalizado " << p << " " << converteReferenciaGlobal(rPonto((float)nlarg,(float)nalt)) << endl;
        defineDesenho(p , nlarg , nalt); // Ajusta novas dimensoes do Desenho

    }
    int dx= 0, dy = 0;

    // Calcula o vetor de translação inverso ao deslocamento do container
    // utilizado para reposicionar os desenhos filhos de forma que suas posições
    // globais continuem a mesma, para o caso dos Containers
    dx = px1 - npx;
    dy = py1 - npy;

    return rPonto(dx,dy);

 //    if(dx != 0 || dy != 0)
    //        transladaFilhos(rPonto(dx, dy)); // Realiza traslação dos filhos
}


void Desenho::rotacionarPonto(rPonto &centro, rPonto *p, double ang)
{
    int cx =centro.x(), cy = centro.y(),
        px = p->x()   , py = p->y();

    px -= cx;
    py -= cy;

    Matriz <float> rotacao(2,2,0);
    Matriz <float> ponto(2,1);

    rotacao(0,0) = cos(ang);
    rotacao(0,1) = sin(ang);
    rotacao(1,0) = -sin(ang);
    rotacao(1,1) = cos(ang);

    ponto(0,0) = px;
    ponto(1,0) = py;

    Matriz <float> resp(rotacao * ponto);

    p->setX( resp(0,0) + cx);
    p->setY( resp(1,0) + cy);
}


int Desenho::desenho_id = 0;




/**
  Verifica se esse Desenho esta habilitado a escutar o tipo de MouseEvento
passado por parametro
**/
bool Desenho::escutaMouseEvento(MouseEvento *e)
{
    switch(e->evento())
    {
    case MOUSE_PRECIONADO:
        return escutaMousePrecionado();
    break;
    case MOUSE_SOLTO:
        return escutaMouseSolto();
    break;
    case MOUSE_MOVENDO:
        return escutaMouseMovendo();
    break;
    case NENHUM_EVENTO:
        return false;
    break;
    }
    return false;
}

/** Este metodo foi criado apenas para compatibilidade
  com o Q_OBJECT do QT, os objetos do qt precisam de
  um pai, pois é ele que desaloca todos objetos dinâmicos
de forma hirarquica, no fim de sua execução.
  Como foi necessario usar Q_OBJECT (slots/sgnal) e tambem
 criação de menus (QMenus) em algumas classes para comunicação
 com a interface grafica, esse metodo foi criado para facilitar
 o acesso a uma QWidget.
    Retorna a Widget do desenho mestre, se o desenho mestre
 não existir, ou ainda não foi definido, retorna a Widget do
 desenhoMestre statico (padrao/global).
  **/
QWidget * Desenho::widget()
{
    // Se desenho mestre existe, retorna widget dele
    if(m_desenhoMestre != 0x0)
    {
        return m_desenhoMestre->getWidget();
    }
    // Retorna widget padrão do desenhoMetre statico
    return DesenhoMestre::getMestreGlobal()->getWidget();
}


/**
 * @brief
 *  Define se o desenho faz parte de um desenho composto ou não.
 * @param simNao - true se faz, false se não faz.
 */
void Desenho::setComponente(bool simNao)
{
    m_componente = simNao;
}

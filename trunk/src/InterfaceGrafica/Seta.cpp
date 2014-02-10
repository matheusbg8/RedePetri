#include "Seta.h"
#include "Utilidades.h"
#include <iostream>
using namespace std;

void Seta::inicializaSeta()
{
    m_tipoDesenho = TD_SETA;
    m_ligFim = m_ligIni = 0x0; // Desconectada
    m_rastriandoMouse = false;

    inicio = new Circulo(5,rPonto());
    fim = new Circulo(5,rPonto());
    seg = new Segmento;
    triangulo = new Triangulo;

    m_comprimentoPonta = 18.f;
    m_aberturaPonta = 5.f;

    inicio->setCorFundo(Cor::verde);
    fim->setCorFundo(Cor::verde);

    // Desativa geração de sinais dos desenhos composto
    inicio->geraSinal(false);
    fim->geraSinal(false);
    seg->geraSinal(false);
    triangulo->geraSinal(false);

    novaComposicao(seg);
    novaComposicao(triangulo);
    novaComposicao(inicio);
    novaComposicao(fim);

    setDesenhaFundo(false);

    defineSeta(rPonto(20,20), rPonto(120,90));
    ajustaComponentes(0x0);
}

Seta::Seta(Container *pai):DesenhoComposto(pai)
{
    inicializaSeta();
}

Seta::~Seta()
{
    cout << "Destruindo seta " << getNome().toStdString() << endl;
}

Desenho *Seta::novaInstancia() const
{
    Seta *s = new Seta();
    copiaMeusParametros(s);
    return s;
}


/**
 * @brief
 *      Define uma seta apartir de dois pontos, esses pontos devem estar
 * com refrencial do desenho pai da seta.
 * @param p1 - Ponto inicial da seta.
 * @param p2 - Ponto final da seta.
 */
void Seta::defineSeta(const rPonto& pIni, const rPonto& pFim)
{
    // Se p1 e p2 forem iguais, ocorre divisão por zero!
    if(pIni == pFim)
    {
        cout << "Seta:: Erro ao definir seta, posicao ini e fim iguais" << endl;
        return;
    }

    // Aqui ocorre o tratamento para achar a posição do canto do retangulo
    RetanguloBasico r(pIni,pFim);
    // Estabelece um folga de espaço de 10 em cada lado da seta.
    r.setPosicao(r.posicao()- 10.f);
    r.setAltura(r.altura() + 20.f);
    r.setLargura(r.largura() + 20.f);

    if(r.largura() > 10000 || r.altura() > 10000 || r.posicao().x() < -10000 || r.y() < -10000)
    {
        cout << "Problema!!" << endl;
        r.setPosicao(rPonto(50,50));
        r.setAltura(20);
        r.setLargura(20);
        return;
    }
    rPonto p1(pIni - r.posicao()), // Converte p1 e p2 pro referencial do retangulo
           p2(pFim - r.posicao());

/*
    float theta = Utilidades::calculaAngulo(p1,p2); // Calcula o angulo do vetor formado pelos 2 pontos
    float       // Calcula os pontos do triangulo
    tx1 = p2.x(),
    ty1 = p2.y(),
    tx2 = m_comprimentoPonta * cos( theta + m_aberturaPonta ) + tx1,
    ty2 = m_comprimentoPonta * sin( theta + m_aberturaPonta ) + ty1,
    tx3 = m_comprimentoPonta * cos( theta - m_aberturaPonta ) + tx1,
    ty3 = m_comprimentoPonta * sin( theta - m_aberturaPonta ) + ty1;
*/
    rPonto  direcaoUni = (p2 - p1).uni(), // Direcao da seta
            inicioPonta = p2 - (direcaoUni * m_comprimentoPonta);

    triangulo->defineTriangulo(p2 , inicioPonta + direcaoUni.ortoHorario() * m_aberturaPonta ,inicioPonta + direcaoUni.ortoAntiHorario() * m_aberturaPonta);

    seg->defineSegmento(p1 , triangulo->centro());

    inicio->setCentro(p1);

    fim->setCentro(p2);

    /* A ultima coisa é definir o desenho, porque
      se ele for definido antes das setas, um sinal sera gerado
      sem que a seta esteja pronta, causando erro indesejado
      (como por exemplo,o ajuste do container, devido a definição fora
      da seta fora da area, sera calculada e definida a posição da seta
      transladada, que sera perdida porque o sinal de definição de desenho
      foi gerado antes da seta estar pronta, substituindo as posições
      da seta translada pela posição antes da translação.)
    */
    defineDesenho(r.posicao(), r.largura(), r.altura());

//    if(m_desenhoMestre != 0x0)
//        m_desenhoMestre->redesenha();
}

void Seta::desenha()
{
//    Desenho::desenha();
    desenhaComponentes();
    desenhaFilhos();

    if(m_nomeSeta.size() > 0)
    {
        rPonto posicaoDesenho ( (fim->posicaoLocal() - inicio->posicaoLocal()) /2.f);
        posicaoDesenho += posicaoDesenho.ortoAntiHorario().uni()*10.f + inicio->posicaoLocal();

        desenhaTexto(m_nomeSeta, posicaoDesenho, QFont("Times",12,QFont::Bold));
    }

}

/**
 * @brief
 *  A seta se comporta como um denho comum, quando
  um novo desenho é adicionado a ela, passa para ou pai, ou deleta
  se não tiver pai.
 * @param d
 * @param avisaFilho
 */
void Seta::novoDesenho(Desenho *d, bool avisaFilho)
{
    Desenho::novoDesenho(d,avisaFilho);
}

void Seta::mousePrecionadoComposto(Desenho *desenho, MouseEvento *mouseEvento)
{
    // Solução temporaria para rastriamento do mouse
    if(m_rastriandoMouse)
    {
        m_rastriandoMouse = false;
        m_desenhoMestre->paraRastriamentoMouse();
        return;
    }

    if(desenho == seg || desenho == triangulo)
    {   // Reage como um desenho normal
        mousePrecionado(mouseEvento);
        return;
    }

    // Desconecta inicio da seta
    if(desenho == inicio)
    {
        setLigacaoIni(0x0);
        return;
    }

    // Desconecta fim da seta
    if(desenho == fim)
    {
         setLigacaoFim(0x0);
         return;
    }
}

void Seta::mouseSoltoComposto(Desenho *desenho , MouseEvento *mouseEvento)
{
    if(desenho == seg || desenho == triangulo)
    { // Reage como um desenho normal
        mouseSolto(mouseEvento);
    }else

    if(desenho == inicio)
    {
        Desenho *lig;
        // Verifica se tem algum desenho onde foi soltado o inicio da seta
        if(m_pai != 0x0)
            lig = m_pai->getDesenho(mouseEvento->posicaoLocal(), this);

        // Estabelece ligação com o desenho onde a seta foi largada
         setLigacaoIni(lig);

    }else

    if(desenho == fim)
    {
        Desenho *lig;
        if(m_pai != 0x0)
            lig = m_pai->getDesenho(mouseEvento->posicaoLocal(), this);

        setLigacaoFim(lig);

//        defineSeta(converteReferencialPai(inicio->getCentro()), mouseEvento->posicaoLocal());
    }
}

void Seta::mouseMovendoComposto(Desenho *desenho , MouseEvento *mouseEvento)
{
    if(desenho == seg || desenho == triangulo)
    { // Reage como um desenho normal
        mouseMovendo(mouseEvento);
    }else

    cout << "Mouse Movendo Seta " << desenho->getNome().toLocal8Bit().constData() << endl;

    if(desenho == inicio)
    {
        rPonto pIni = mouseEvento->posicaoLocal();
        rPonto pFim = converteReferencialPai(fim->getCentro());
        if(m_ligFim != 0x0) pFim = m_ligFim->posicaoLigacao(pIni);
        if(m_ligIni != 0x0) pIni = m_ligIni->posicaoLigacao(pFim);

        cout << "Redefindo inicio seta! " << pIni << " - > " <<  pFim << endl;
        cout << "Posicao Local ME " << mouseEvento->posicaoLocal() << " m posicao " << m_espaco.posicao() << endl;
        defineSeta(pIni, pFim);
    }else

    if(desenho == fim)
    {
        rPonto pIni = converteReferencialPai(inicio->getCentro());
        rPonto pFim = mouseEvento->posicaoLocal();
        if(m_ligFim != 0x0) pFim = m_ligFim->posicaoLigacao(pIni);
        if(m_ligIni != 0x0) pIni = m_ligIni->posicaoLigacao(pFim);

        cout << "Redefindo fim seta! " << pIni << " - > " <<  pFim << endl;
        defineSeta(pIni, pFim);
    }

    cout << "FIM!!" << endl;
}

/**
 * @brief
 *  Este metodo sempre sera chamado quando ocorrer uma tentativa de ligação
 * de um desenho com o inicio da seta, a reação basica é aceitar a ligação,
 * porem esse metodo pode ser rescrito por uma classe superior.
 * @param desenho - Desenho que esta tendo liga com inicio da seta, pode
 * acontecer do desenho ser 0x0, neste caso acontece uma tentativa de
 * desconectar a seta de um desenho.
 * @return bool - True para aceitar a ligação, False caso contrario.
 */
bool Seta::aceitaLigacaoIni(Desenho *desenho)
{
    return true;
}

/**
 * @brief
 *  Este metodo sempre sera chamado quando ocorrer uma tentativa de ligação
 * de um desenho com o final da seta, a reação basica é aceitar a ligação,
 * porem esse metodo pode ser rescrito por uma classe superior para que
 * podendo ser determinado uma restrição nessa ligação.
 * @param desenho - Desenho que esta tendo liga com inicio da seta,
 * pode ser um desenho invalido (0x0), neste caso acontece uma tentativa
 * de desconectar a seta de algum desenho.
 */
bool Seta::aceitaLigacaoFim(Desenho *desenho)
{
    return true;
}

void Seta::desenhaNome()
{
    // Desenha o nome desse denho
    if(m_desenhoMestre!= 0x0 && m_nomeVisivel)
    {
        rPonto posicaoDesenho ( (fim->posicaoLocal() - inicio->posicaoLocal()) /2.f);
        posicaoDesenho += posicaoDesenho.ortoAntiHorario().uni()*10.f + inicio->posicaoLocal();

        desenhaTexto(QString(m_nome), posicaoDesenho, QFont("Times",12,QFont::Bold));
    }
}


/**
 * @brief
 *  Este metodo estabelece uma ligação entre o inicio da seta com um desenho
 * de forma com que o inicio da seta sempre seja alterado para a mesma posição
 * desse desenho, essa ligação é feta atravez das escutas.
 *  A lisgação só é estabelecida se o metodo aceitaLigacaoIni(Desenho *)
 * retornar true.
 * @param desenho - Desenho que sera ligado, pode ser um desenho invalido (0x0),
 * sinal que a ligação quer ser desfeita com o desenho atual.
 * Retorna true se a ligacao foi estabelecida, false caso contrario.
 */
bool Seta::setLigacaoIni(Desenho *desenho)
{
    if( aceitaLigacaoIni(desenho))
    {
        if(m_ligIni != 0x0)
            m_ligIni->removeEscuta(this);

        m_ligIni = desenho;

        if(desenho != 0x0)
        {
            m_ligIni->novaEscuta(this);

            rPonto pFim = converteReferencialPai(fim->getCentro());            
            rPonto pIni = desenho->posicaoLigacao(pFim);

            // Se tem desenho final
            if(m_ligFim != 0x0)
            {   // Atuliza a sua posição pq o inicio mudou de lugar!
                pFim = m_ligFim->posicaoLigacao(pIni);
            }


            defineSeta(pIni , pFim);
        }
        return true;
     }
    return false;
}

/**
 * @brief
 *  Este metodo estabelece uma ligação entre o fim da seta com um desenho
 * de forma com que o fim da seta sempre seja alterado para a mesma posição
 * desse desenho, essa ligação é feta atravez das escutas.
 *  A lisgação só é estabelecida se o metodo aceitaLigacaoFim(Desenho *)
 * retornar true.
 * @param desenho - Desenho que sera ligado.
 * Retorna true se a ligacao foi estabelecida, false caso contrario.
 */
bool Seta::setLigacaoFim(Desenho *desenho)
{
    // Verifica se aceita se ligar com esse desenho
    if(aceitaLigacaoFim(desenho))
    {
        // Se ja estava ligado com outro desenho, remove escuta dele
        if(m_ligFim != 0x0)
            m_ligFim->removeEscuta(this);

        m_ligFim = desenho;

        // Se é um desenho (se não é apenas pra desconectar)
        if(desenho != 0x0)
        {
            rPonto pIni = converteReferencialPai(inicio->getCentro());
            rPonto pFim = desenho->posicaoLigacao(pIni);

            // Se tem desenho inicial
            if(m_ligIni != 0x0)
            {   // Atuliza a sua posição pq o fim mudou de lugar
                pIni = m_ligIni->posicaoLigacao(pFim);
            }

            // A seta começa em ini e termina na posição de ligação do desenho partindo do inicio (geralmente retorna ponto de intercecao da reta começa em ini e termina no centro do desenho destino)
            defineSeta(pIni, pFim);
            m_ligFim->novaEscuta(this);
        }
        return true;
    }
    return false;
}


rPonto Seta::posicaoInicial() const
{ // Atencao, nao pode retornar referencia c++ pq e ponto temporario
    return converteReferencialPai(inicio->posicaoLocal());
}

rPonto Seta::posicaoFinal() const
{
    return converteReferencialPai(fim->posicaoLocal());
}

void Seta::setNomeSeta(QString nome)
{
    m_nomeSeta = nome;
}


/**
 * @brief
 *  Retorna o desenho que esta ligado com o inicio da seta,
 * ou 0x0 se não existir ligação.
 * @return Desenho
 */
const Desenho *Seta::getLigacaoIni() const
{
    return m_ligIni;
}


/**
 * @brief
 *  Retorna o desenho que esta ligado com o final da seta,
 * ou 0x0 se não existir ligação.
 * @return Desenho
 */
const Desenho *Seta::getLigacaoFim() const
{
    return m_ligFim;
}


/**
 * @brief
 *  Este metodo trata a alteração de posição de um
 * desenho que a seta esta escutando, provavelmente
 * existe no maximo 2 desenhos que seta escuta, o
 * Desenho que liga no inicio da Seta, e o Desenho
 * que liga como final da Seta.
 *  A alteração da posição desses desenhos deve ser
 * tratada de forma com que a posição inicial e final
 * da seta seje atualizada para nova posição desses
 * desenhos.
 * @param desenho - Desenho escutado que teve a sua
 * posição alterada.
 * @param novaPosicao - Nova posição do desenho.
 */
void Seta::eventoAlteracaoPosicao(Desenho *desenho)
{
    // Verifica se o desenho alterado é o inicial ou final da seta
    if(desenho == m_ligFim || desenho == m_ligIni)
    {
        if(produzLog)
            cout << "Reposicionando Seta" << endl;

        // Pega a posição final
        rPonto pFim = converteReferencialPai(fim->getCentro());
        rPonto pIni = converteReferencialPai(inicio->getCentro());
        // Pega a nova posição
        if(m_ligFim != 0x0) pFim = m_ligFim->posicaoLigacao(pIni);
        if(m_ligIni != 0x0) pIni = m_ligIni->posicaoLigacao(pFim);
        // Redefine a seta
        defineSeta(pIni, pFim);

        if(produzLog)
            cout << "Seta Reposicionada" << endl;
    }
}

void Seta::eventoAlteracaoAltura(Desenho *desenho)
{
}

void Seta::eventoAlteracaoLargura(Desenho *desenho)
{
}


/**
 * @brief
 *  Quando um desenho que esta sendo escutado por este desenho
 * é deletado, um evento é gerado, e esse metodo é chamdo
 * para tratar esse evento.
 * @param desenho - Desenho que esta sendo deletado.
 */
void Seta::eventoDeletando(Desenho *desenho)
{
    // Se o desenho que esta ligado no inicio da seta for deletado
    if(desenho == m_ligIni)
    {   // Remove a ligação com ele
        setLigacaoIni(0x0);
    }
    // O mesmo para o desenho que esta no fim

    if(desenho == m_ligFim)
    {
        setLigacaoFim(0x0);
    }
    DesenhoComposto::eventoDeletando(desenho);
}

void *Seta::getSuper()
{
    return this;
}

void Seta::setSelecionado(bool selecionado)
{
    if(selecionado)
    {
        if(produzLog)
            cout << "Seta(" << m_nome.toStdString() << ")::setSeleciona(true)" << endl;

        inicio->setVisivel(true);
        fim->setVisivel(true);
    }else
    {
        if(produzLog)
            cout << "Seta(" << m_nome.toStdString() << ")::setSeleciona(false)" << endl;

        inicio->setVisivel(false);
        fim->setVisivel(false);
    }
    DesenhoComposto::setSelecionado(selecionado);
}


/**
 * @brief
 * Chame o rastriamento apenas quando a seta ja estiver sido inserida em um container
 */
void Seta::comecaRastriamentoFim()
{
    setEscutaMouseMovendo(true);

    // Solução temporaria para funcionar o rastriamento
    fim->setEscutaMouseSolto(true);
    fim->setEscutaMouseMovendo(true);
    fim->setEscutaMousePrecionado(false);

    m_rastriandoMouse = true;

    m_desenhoMestre->paraRastriamentoMouse();
    m_desenhoMestre->rastriarMouse(this);
}

void Seta::comecaRastriamentoInicio()
{
    setEscutaMouseMovendo(true);

    // Solução temporaria para funcionar o rastriamento
    inicio->setEscutaMouseSolto(true);
    inicio->setEscutaMouseMovendo(true);
    inicio->setEscutaMousePrecionado(false);

    m_rastriandoMouse = true;

    m_desenhoMestre->paraRastriamentoMouse();
    m_desenhoMestre->rastriarMouse(this);
}


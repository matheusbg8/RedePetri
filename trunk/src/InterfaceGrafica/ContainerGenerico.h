#ifndef CONTAINERGENERICO_H
#define CONTAINERGENERICO_H


#include "Container.h"
#include "GerenciadorElementos.h"
#include "Seta.h"

/**
 * @brief
 * Esta classe é responsável por prover um
 *container generico de desenhos prevendo ligacoes.
 *  A ideia é que esste container possa ser utilizado
 * para representar diversos modelos de dados diferentes,
 * seja um grafo, um automato ou uma rede de petri.
 *  Para permitir a representação de diversos modelos de
 * dados e necessario flexiblidade na descrição dos desenhos
 * e suas funções, para isso é utilizado uma fabrica de desenhos
 * genericos, que deve ser construida antes de iniciar a representação
 * de algum modelo. Esta fábrica permite definir quais os tipos
 * de desenho seram utilizados na representação do modelo, assim
 * como quais funções cada desenho desempenha no modelo atráves
 * de popup menus e os objetos QActions do QT. Também é possível
 * definir qual o canal de indexacao de cada tipo de desenho,
 * permitindo definir quais desenhos são indexados na mesma
 * faixa de IDs, e quais são indexados separados, aumento
 * a flexibilidade de representação de modelos.
 */
class ContainerGenerico:
        public Container
{
private:
    GerenciadorElementos<Desenho*> m_fabricaDesenhos;
    Seta * m_seta;
    bool m_definindoArco;
    Seta * m_setaDefinindo;

//    GerenciadorElementos<Seta*> m_fabricaSetas;

    vector<GerenciadorElementos<Desenho*> > m_indexacao;

public:
    ContainerGenerico();
    virtual ~ContainerGenerico();

    bool adicionaDesenhoNaFabrica(Desenho *d, int idTipoDesenho, int faixaIndexacao);
    bool removeDesenhoFabrica(int idTipoDesenho);

    bool defineSeta(Seta* seta,int idTipoDesenho, int faixaIndexacao);

    const Desenho *getDesenhoGenerico(int idTipoDesenho) const;
    Desenho *getDesenhoGenerico(int idTipoDesenho);

    int novoDesenho(int idTipoDesenho);
    int novoDesenho(int idTipoDesenho, int id);

    int novaSeta(int idDe , int idDeTipo, int idPara, int idParaTipo);
    int novaSeta(int idDe , int idDeTipo, int idPara, int idParaTipo, int idSeta);


    void deletaDesenho(int idTipoDesenho, int id);

    Desenho* desenho(int idTipoDesenho, int id);
    const Desenho* desenho(int idTipoDesenho, int id) const;


    int numDesenhos(int tipoDesenho) const;
    int maiorIndice(int tipoDesenho) const;

    void novoArco();

    // ===== Acoes do mouse == //

    bool novoMouseEvento(MouseEvento *mouseEvento);
    void processaMouseEvento(MouseEvento *me , Desenho *d);

    // ===== Interface =======

    /**
     * @brief
     *  Este metodo é chamado toda vez que um desenho é
     * precisonado por algum botao do mouse.
     * @param me - Evento do mouse gerado no desenho
     * @param idTipoDesenho - Tipo do desenho que sofreo o evento.
     * @param idDesenho - Id do desenho que sofreo o evento.
     */
    virtual void mousePrecionado(MouseEvento *me, int idTipoDesenho , int idDesenho) = 0;

    /**
     * @brief
     *  Este metodo é chamado toda vez que um desenho é
     * solto pelo botao do mouse.
     * @param me - Evento do mouse gerado no desenho
     * @param idTipoDesenho - Tipo do desenho que sofreo o evento.
     * @param idDesenho - Id do desenho que sofreo o evento.
     */
    virtual void mouseSolto(MouseEvento *me, int idTipoDesenho , int idDesenho) = 0;


    /**
     * @brief
     *  Este metodo é chamado toda vez que dois desenhos
     * são ligados por uma seta. A ligação pode ser
     * permitida quando este metodo retorna true, ou
     * pode ser bloqueada quando este metodo retorna false.
     * @param deId - ID do desenho de origem da ligacao
     * @param deIdTipo - ID do tipo do desenho de origem da ligacao.
     * @param paraId - ID do desenho de destino da ligacao.
     * @param paraIdTipo - ID do tipo do desenho de destino da ligacao.
     * @return int - Retorna -1 para aceitar a ligacao e gerar um ID automatico,
     * -2 para não permititir a ligacao.
     * valores >= 0 para aceitar a ligacao e atribuir ao ID do arco o número retornado.
     */
    virtual int ligacao(int deId, int deIdTipo, int paraId,int paraIdTipo) = 0;
};

#endif // CONTAINERGENERICO_H

#ifndef DREDEPETRI_H
#define DREDEPETRI_H

#include <QDomNode>
#include "Container.h"
#include "RedePetri.h"
#include "DLugar.h"
#include "DTransicao.h"
#include "DArco.h"
#include "ControladorRede.h"
#include "IVRedePetri.h"
#include "ComunicadorRedePetri.h"

/**
 * @brief
 *  DRedePetri é uma representação gráfica
 * de uma rede de petri.
 *  A idéia foi separar a interface gráfica
 * dos dados e o modelo matematico das Redes
 * de Petri.
 *  A classe DRedePetri possue uma instancia
 * da classe RedePetri, e apenas a manipula
 * dependendo das ações do usuario em sua
 * representação gráfica.
 *  Cada Transição, Lugar e Arco possuem uma
 * representação gráfica chamada DTransicao,
 * DLugar e DArco, também instanciadas
 * dentro da classe DRedePetri, que auxiliam
 * na manipulação do modelo RedePetri.
 *  Por exemplo, todas as ações que o usuario
 * fizer na representação grafica de um DLugar
 * surtira efeito apenas no lugar do modelo
 * RedePetri que o DLugar representa, o mesmo
 * ocorre com DTransicao e DArco.
 */
class DRedePetri :
        public  QObject, // QObject tem que ser o 1º
        public Container,
        public IVRedePetri
{
    Q_OBJECT
private:
    static unsigned numRedePetri;
    unsigned m_idRedePetri;

    RedePetri *m_rede;
    ControladorRede *m_controleRede;
    ComunicadorRedePetri *m_visualizacaoTCP;

    QMenu *mnuFundo;

    QAction *novaTransicaoAct;
    QAction *novoLugarAct;
    QAction *novoArcoAct;
    QAction *actGeraXMLSimples;
    QAction *actImprimeRede;
    QAction *actGeraGrafoCobertura;
    QAction *actAlinhar;
    QAction *actDeleta;
    QAction *actNovaVisualizacao;
    QAction *actCriaVisualizacaoTCP;
    QAction *actCarregaXML;

    void inicializaDRedePetri();

    vector<DLugar*> m_lugares;  /** Lista com todos lugares da rede */
    vector<DArco*> m_arcos;  /** Lista com todos arcos */
    vector<DTransicao*> m_transicoes; /** Lista com todas transições */

    void criaAcoes();
    void criaMenus();

public:

    DRedePetri(Container *m_pai = 0x0);
    ~DRedePetri();
    void comando(QString cmd);
    bool mousePrecionado(MouseEvento *e);

    void *getSuper();

    void removeDesenho(Desenho *d);

//    void novoDesenho(Desenho *d, bool avisaFilho = true);

    DLugar * getLugar(unsigned id);

    int novoLugar();


    DTransicao * getTransicao(unsigned id);
    int novaTransicao();

    DArco * getArco(unsigned id);
    int novoArcoPT(int de, int para, int peso);
    int novoArcoTP(int de, int para, int peso);

    unsigned getNumeroLugar();
    unsigned getNumeroTramsicao();
    unsigned getNumeroArco();

    void setControlador(ControladorRede *controlador);
    ControladorRede *controlador();


    bool carregaXML(const QString &nomeArquivo);
    bool carregaXML(QDomElement &elemento);

    bool geraXML(const QString &nomeArquivo);
    bool geraXML(QDomDocument & doc, QDomNode &raiz);

    // Iterface da rede de petri
    void dNovoLugar(unsigned id);
    void dNovaTransicao(unsigned id);
    void dNovoArcoPT(unsigned id, unsigned de, unsigned para, unsigned peso);
    void dNovoArcoTP(unsigned id, unsigned de, unsigned para, unsigned peso);

    void dDeletaTransicao(unsigned id);
    void dDeletaLugar(unsigned id);
    void dDeletaArco(unsigned id);

    void dSetPesoArco(unsigned id, unsigned peso);

    void dSetFichas(unsigned id, unsigned numFichas);

    // Consulta
    unsigned dPesoArco(unsigned id);
    unsigned dFichas(unsigned id);

    // Controle
    void dExecutaTransicao(unsigned id);

public slots:
    void SNovaTransicao();
    void SNovoArco();
    void SNovoLugar();
    void novaVisualizacao();
    void geraXML();
    void geraXMLSimples();
    void carregaXMLSimples();
    void imprimeRede();
    void geraGrafoCobertura();
    void alinhar();
    void deleta();
    void criaVisualizacaoTCP();

};

#endif // DREDEPETRI_H

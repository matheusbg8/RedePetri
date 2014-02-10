#ifndef CONTROLADORREDE_H
#define CONTROLADORREDE_H

#include <list>
using namespace std;

#include "RedePetri.h"
#include "IRedepetri.h"
#include "IVRedePetri.h"

// Lembrar de concertar a remocao dos DLugar DTransicao e DArco
// que antes estava no destrutor
// Adapta DRede para usar controlador

/**
 * @brief
 *  Esta classe é responsavel por
 * controlar os modelos de redes de petri
 * ela centraliza todas as operações sobre
 * o modelo e mantem todos os observadores (visualizacoes)
 * atualizados sobre essas operações.
 */
class ControladorRede :public IRedePetri
{
protected:
    RedePetri *m_modelo;
    list<IVRedePetri*> m_visualizacoes;

    void atualizaVisualizacaoFichas();

    void atualizaVisuzalizacao(IVRedePetri *visualizacao);
public:
    ControladorRede();
    ~ControladorRede();

    void setModelo(RedePetri *modelo);
    void addVisualizacao(IVRedePetri* visualizacao);
    void removeVisualizacao(IVRedePetri* visualizacao);

    RedePetri *modelo();
    const RedePetri *modelo() const;

    // Edicao
    unsigned novoLugar();
    unsigned novaTransicao();
    unsigned novoArcoPT(unsigned de, unsigned para, unsigned peso);
    unsigned novoArcoTP(unsigned de, unsigned para, unsigned peso);

    bool deletaTransicao(unsigned id);
    bool deletaLugar(unsigned id);
    bool deletaArco(unsigned id);

    bool deletaTudo();

    bool deletaArcoPT(unsigned de, unsigned para);
    bool deletaArcoTP(unsigned de, unsigned para);

    bool setPesoArco(unsigned id, unsigned peso);

    bool setPesoArcoPT(unsigned de, unsigned para, unsigned peso);
    bool setPesoArcoTP(unsigned de, unsigned para, unsigned peso);

    bool setFichas(unsigned id, unsigned numFichas);

    // Consulta
    unsigned pesoArco(unsigned id) const;
    unsigned idArcoPT(unsigned de, unsigned para) const;
    unsigned idArcoTP(unsigned de, unsigned para) const;

    unsigned fichas(unsigned id) const;

    bool sensibilizado(unsigned id) const;

    bool existeTransicao(unsigned id) const;
    bool existeLugar(unsigned id) const;
    bool existeArco(unsigned id) const;

    unsigned numTransicoes();
    unsigned numLugares();
    unsigned numArcos();

    // Modelo
    bool executaTransicao(unsigned id);
};

#endif // CONTROLADORREDE_H

#ifndef DESENHOGENERICO_H
#define DESENHOGENERICO_H


#include "Desenho.h"

/**
 * @brief
 *  Esta classe é responsável por prover
 * uma interface grafica generiaca que pode
 * se utilizada para representar diversos modelos
 * de dados.
 */
class DesenhoGenerico
{
private:

    int m_faixaIndexacao; // Define a faixa de indeccao
    int m_tipoDesenho; // Armazena o tipo desse desenho generico

    Desenho *m_desenho;

public:
    DesenhoGenerico(Desenho *desenho, int idTipoDesenho = -1);

    int faixaIndexacao() const;
    void setFaixaIndexacao(int faixaIndexacao);

    int tipoDesenho() const;
    void setTipoDesenho(int idTipoDesenho);

    Desenho *novaInstancia() const;

    Desenho* desenho();
    const Desenho* desenho() const;
};

#endif // DESENHOGENERICO_H

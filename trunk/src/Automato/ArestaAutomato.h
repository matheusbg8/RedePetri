#ifndef ARESTAAUTOMATO_H
#define ARESTAAUTOMATO_H

#include <string>

using namespace std;
#include "ArestaGrafo.h"

/**
 * @brief
 *  A aresta do automato define
 * quais os simbolos que são aceitos
 * pela aresta para passar de um estado
 * para o outro em um automato.
 */
class ArestaAutomato:public ArestaGrafo
{
private:
    string m_simbulos;
    bool m_negado;

public:
    ArestaAutomato(const char * simbulosAceitos = "");
    bool aceitaSimbolo(char s);

    void setSimbulosAceitos(const char *simbulos);
    const char * simbulosAceitos() const;

    void setNegado(bool negarAceitacao);

    // Impelmentação da classe ArestaGrafo
    ArestaGrafo* novaAresta();
};

#endif // ARESTAAUTOMATO_H

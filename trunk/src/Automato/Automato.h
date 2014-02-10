#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "ArestaAutomato.h"
#include "GrafoLista.h"

class Automato
{
protected:
    GrafoLista m_estrutura;
    unsigned m_estadoInicial;
    list<unsigned> m_estadosFinais;
    list<unsigned> m_estadosAceitacao;

public:
    Automato();

    void criaEstados(unsigned numEstados);

    bool setEstadoInicial(unsigned estadoInicial);

    void addEstadoFinal(unsigned estado);    
    void removeEstadoFinal(unsigned estado);

    void addEstadoAceitacao(unsigned estado);
    void removeEstadoAceitacao(unsigned estado);

    void addAresta(unsigned de, unsigned para, const char *simbulos);
    void addAresta(ArestaAutomato* aresta);

    int avalia(const char *palavra, string &palavraExtraida);

    // Constantes estaticas
    static string branco();
    static string letrasMinusculas();
    static string letrasMaiusculas();
    static string numeros();

};

#endif // AUTOMATO_H
